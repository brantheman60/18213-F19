/*
 * 15-213/18-213: Introduction to Computer Systems
 * Name: Brandon Wang
 * AndrewID: bcwang
 *
 * Sources:
 * -Lecture 22: Network Programming Basics
 *  Starter code for main routine
 * -Lecture 23: Concurrent Programming
 *  Starter code for pthread routines
 * -Lecture 24: Synchronization (Basics)
 *  Starter code for pthread routines
 * -Computer Systems - A Programmer's Perspective: Chapter 11
 *  Code for organizing helper functions
 * -tiny.c
 *  code is largely based off of functions in tiny.c
 */

/* Some useful includes to help you get started */

#include "csapp.h"
#include "cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <assert.h>

#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
 * Debug macros, which can be enabled by adding -DDEBUG in the Makefile
 * Use these if you find them useful, or delete them if not
 */
#ifdef DEBUG
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_printf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg_assert(...)
#define dbg_printf(...)
#endif

/*
 * Max cache and object sizes
 * You might want to move these to the file containing your cache implementation
 */
#define MAX_CACHE_SIZE (1024*1024)
#define MAX_OBJECT_SIZE (100*1024)

/* Typedef for convenience */
typedef struct sockaddr SA;

/* List of helper functions */
int parse_uri(char *uri, char *hostname, char *pathname, int *port);
int make_requesthdrs(char *buf, char *hostname, char* port, rio_t *rio);
void serve(int fd);

/*
 * Strings to use for the main headerw.
 * Don't forget to terminate with \r\n!
 */
static const char *header_user_agent = "User-Agent: Mozilla/5.0"
       " (X11; Linux x86_64; rv:3.10.0) Gecko/20191101 Firefox/63.0.1";
static const char *header_connect = "Connection: close";
static const char *header_proxy_connect = "Proxy-Connection: close";
static const char *carr_newl = "\r\n";

static bool verbose = false;
static bool caching = true;
static bool concurr = true;
pthread_mutex_t mutex;
pthread_mutex_t mut;
cache_t *cache; //shared cache; careful using this!

/*
 * parse_uri: decompose uri into host name, path name, and port number
 * Input: char *uri (received uri)
 *        char *hostname (host name (uninitialized))
 *        char *pathname (path name (uninitialized))
 *        int *port (pointer to port number (uninitialized))
 * Output: int (0 if successful, -1 if error)
 */
int parse_uri(char *uri, char *hostname, char *pathname, int *port)
{
    //Check uri begins with http://
    if(uri != strstr(uri, "http://"))
        return -1;
    uri += strlen("http://");

    char *pathbegin = strstr(uri, "/");
    if(!pathbegin) return -1;
    int host_len = (int) (pathbegin - uri);
    strncpy(hostname, uri, host_len);
    hostname[host_len] = '\0';
    strcpy(pathname, pathbegin);

    char *token;
    if((token = strstr(hostname, ":")) != NULL) //port number is included
    {
      *token = '\0'; //break hostname
      *port = atoi(token+1); //break port
      if(*port == 0) return -1;
    }
    else *port = 80; //default port

    dbg_assert(hostname != NULL);
    dbg_assert(pathname != NULL);
    dbg_assert(port != NULL);
    return 0;
}

/*
 * thread_serve: every new client request will spawn a new thread;
 *               thread routine necessary for concurrent proxy
 *               opens and closes the client/server sessions
 * Input: void *vargp (pointer to connfd)
 */
void *thread_serve(void *vargp)
{
    int connfd = *((int*) vargp);
    pthread_detach(pthread_self());
    Free(vargp);
    if(verbose) printf("STARTING thread\n");
    serve(connfd); //begin client/server session
    if(verbose) printf("FINISHED thread\n");
    close(connfd); //end client/server session
    return NULL;
}

/*
 * serve: after establishing a connection with the client, form a (1)
 *        connection with the server acting like the client. Handles data
 *        transfer between the client and the server.
 * Input: int clientfd (buffer descriptor / client port)
 * Output: void
 */
void serve(int clientfd)
{
    char buf_client[MAXLINE] = "", buf_server[MAXLINE] = "",
         uri[MAXLINE] = "";
    char method[MAXBUF] = "", hostname[MAXBUF] = "",
         pathname[MAXBUF] = "", version[MAXBUF] = "";
    int port = 0;
    rio_t rio_client, rio_server;

    //read client request
    rio_readinitb(&rio_client, clientfd);
    if (!rio_readlineb(&rio_client, buf_client, MAXLINE))
    {
        if(verbose) printf("Error with reading client request\n");
        return;
    }
    if(verbose)
      printf("Initial request by client had header: %s\n", buf_client);

    //parse buf_client into GET, URI, and Version
    if (sscanf(buf_client, "%s %s %s", method, uri, version) != 3)
    {
        if(verbose) printf("Error with initial request\n");
        return;
    }
    else if(strcmp(method, "GET") ||
           (strcmp(version, "HTTP/1.0") && strcmp(version, "HTTP/1.1")) )
    {
        if(verbose) printf("Error with initial request\n");
        return;
    }

    //parse uri into hostname (w/o port), pathname, and port number
    if(parse_uri(uri, hostname, pathname, &port) < 0)
    {
        if(verbose) printf("Error with parsing uri\n");
        return;
    }
    if(hostname == NULL || pathname == NULL)
    {
        if(verbose) printf("Error with parsing uri\n");
        return;
    }
    char *port_string = Calloc(5, sizeof(char)); //size of 5 digits
    sprintf(port_string, "%d", port);

    //pass into cache to immediately respond!
    if(caching)
    {
        pthread_mutex_lock(&mutex);
        Cache_check(cache);

        cnode_t *node = find_node(cache, hostname, pathname, port);
        bool found = false;
        if(node != NULL) //cache hit!
        {
            found = true;
            if(verbose)
            {
                printf("Cache hit\n");
                printf("Node host: %s\n", node->host);
                printf("Node path: %s\n", node->path);
                printf("Node port: %d\n", node->port);
            }
            //make node most recently used node
            delete_node(cache, node);
            enter_node(cache, node);

            pthread_mutex_unlock(&mutex);
            rio_writen(clientfd, node->payload, node->size);
            pthread_mutex_lock(&mutex);
        }
        else
        {
            if(verbose) printf("Cache miss\n");
        }

        Cache_check(cache);
        pthread_mutex_unlock(&mutex);
        if(found) return;
    }

    //fill buf_server with response headers
    strcat(buf_server, method);
    strcat(buf_server, " ");
    strcat(buf_server, pathname);
    strcat(buf_server, " HTTP/1.0\r\n");
    if(make_requesthdrs(buf_server, hostname, port_string, &rio_client) < 0)
    {
        if(verbose) printf("Error with request headers\n");
        return;
    }

    //open connection w/ desired server
    int serverfd = open_clientfd(hostname, port_string);
    if(serverfd < 0)
    {
        if(verbose) printf("Error with sending client request\n");
        return;
    }
    //set connection to server and write data to server
    rio_readinitb(&rio_server, serverfd);
    rio_writen(serverfd, buf_server, strlen(buf_server));

    if(verbose)
      printf("Message received by server had header: %s", buf_server);

    //read/send any response data (MAXLINES at a time) from server to client
    buf_server[0] = '\0';
    int read_len = 0;
    char payload[MAX_OBJECT_SIZE] = "";
    int sum = 0;
    while((read_len = rio_readnb(&rio_server, buf_server, MAXLINE)) > 0)
    {
        if(verbose)
          printf("Message sent by server had response: %s", buf_server);

        if(sum + read_len <= MAX_OBJECT_SIZE)
            memcpy(payload + sum, buf_server, read_len);
        sum += read_len;

        if(rio_writen(clientfd, buf_server, read_len) < 0)
        {
            if(verbose) printf("Error with sending server response\n");
            return;
        }

        if(verbose)
          printf("Message received by client had header %s", buf_server);
    }

    //try to stuff the payload in the cache
    if(caching && sum <= MAX_OBJECT_SIZE)
    {
        cnode_t *node = create_node(hostname, pathname, port,
                                   payload, sum);
        pthread_mutex_lock(&mut);
        Cache_check(cache);
        //evict LRU cache nodes until new node can fit
        while(cache->load + node->size > MAX_CACHE_SIZE)
            evict_node(cache);
        enter_node(cache, node);

        if(verbose)
        {
            printf("cache has currently %d objects\n", cache->node_cnt);
            printf("cache has currently %d bytes\n", cache->load);
            printf("Tail host: %s\n", cache->tail->host);
            printf("Tail path: %s\n", cache->tail->path);
            printf("Tail port: %d\n", cache->tail->port);
        }

        Cache_check(cache);
        pthread_mutex_unlock(&mut);
    }

    //Close connection with server
    close(serverfd);
    return;
}

/*
 * make_requesthdrs: form the whole output request message and store in buf
 *                   also prints the input headers!
 * Input: char *buf (buffer, already with GET header, to store headers)
 *        char *hostname (host name)
 *        char *port (port number as string)
 *        rio_t *rio (rio struct with all request headers)
 * Output: int (0 if works properly, 1 if error)
 */
int make_requesthdrs(char *buf, char *hostname, char *port, rio_t *rio)
{
    char buf_tmp[MAXLINE] = "";

    //pass through any other headers
    while(strcmp(buf_tmp, "\r\n"))
    {
        if(rio_readlineb(rio, buf_tmp, MAXLINE) < 0) return -1;
        if(verbose) printf("%s", buf_tmp);
        if( !strcmp(buf_tmp, "\r\n")) //end of request
            break;

        if( !strstr(buf_tmp, "User-Agent") &&
            !strstr(buf_tmp, "Connection") &&
            !strstr(buf_tmp, "Proxy-Connection"))
            strcat(buf, buf_tmp);
    }

    //pass in main headers
    if(!strstr(buf, "Host:"))
    {
        strcat(buf, "Host: ");
        strcat(buf, hostname);
        if(strcmp(port, "80"))
        {
            strcat(buf, ":");
            strcat(buf, port);
        }
        strcat(buf, carr_newl);
    }

    strcat(buf, header_user_agent);
    strcat(buf, carr_newl);
    strcat(buf, header_connect);
    strcat(buf, carr_newl);
    strcat(buf, header_proxy_connect);
    strcat(buf, carr_newl);

    strcat(buf, carr_newl);
    return 0;
}

/*
 * main: initializes and runs as the proxy. Opens a listening socket at the
 *       given port and continuously processes client requests for the
 *       specified server. Currently, the program is a CONCURRENT PROXY.
 * Input: int argc (error if argc != 2 (excluding verbose flag))
 *        char** argv (must contain port number)
 */
int main(int argc, char** argv) {
    //Ignore SIGPIPE signal, which normally would terminate program
    Signal(SIGPIPE, SIG_IGN);

    int ch;
    while((ch = getopt(argc, argv, "vc")) != -1)
    {
      switch (ch) {
      case 'v': // Verbose
        verbose = true;
        break;
      default:
        break;
      }
    }

    int listenfd; //server and client descriptors/ports
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE] = "", client_port[MAXLINE] = "";
    char *port; //port number as string
    pthread_t tid;

    //retreive port number from argument
    if (argc < 2)
    {
        if(verbose) printf("No port number provided\n");
        exit(1);
    }
    port = verbose ? argv[2] : argv[1];
    if(atoi(port) < 1024)
    {
       if(verbose) printf("Port number must be between 1024 and 32768\n");
       exit(1);
    }

    //opens and returns listening socket on portno
    if ( (listenfd = open_listenfd(port)) < 0)
    {
        if(verbose) printf("Error with creating listening socket\n");
        exit(1);
    }

    //initialize cache and mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mut, NULL);
    cache = Malloc(sizeof(cache_t));
    cache_init(cache);

    while (true) {
      clientlen = sizeof(struct sockaddr_storage);
      int *connfdp = Malloc(sizeof(int));
      *connfdp = accept(listenfd, (SA *)&clientaddr, &clientlen);
      getnameinfo((SA *) &clientaddr, clientlen,
                  client_hostname, MAXLINE,
                  client_port, MAXLINE, 0);
      if(verbose)
        printf("Connected to (%s, %s)\n", client_hostname, client_port);

      if(concurr) //concurrent proxy
      {
        int a;
        if ((a = pthread_create(&tid, NULL, thread_serve, connfdp)) != 0)
        {
          printf("ERROR: PTHREAD_CREATE = %d\n", a);
        }
      }
      else //sequential proxy
      {
        serve(*connfdp);
        close(*connfdp);
      }
    }

    free_cache(cache); //should never reach here, but free anyway
    return 0;
}
