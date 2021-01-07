/*
 * Max cache and object sizes
 * You might want to move these to the file containing your cache implementation
 */
#include "csapp.h"
#define MAX_CACHE_SIZE (1024*1024)
#define MAX_OBJECT_SIZE (100*1024)

typedef struct cnode {
    char *host;
    char *path;
    int port;
    char *payload; //where all the data is!
    int size; //size of payload
    struct cnode *prev;
    struct cnode *next;
} cnode_t; //one file/payload in the cache

typedef struct proxy_cache
{
    cnode_t *head; //least recently used node
    cnode_t *tail; //most recently used node
    int node_cnt; //number of nodes
    int load; //total bytes of payload
} cache_t;

int nodecmp(cnode_t *node, char *host, char *path, int port);
void cache_init(cache_t *cache);
void free_cache(cache_t *cache);
cnode_t* create_node(char *host, char* path, int port,
    char *payload, int size);
cnode_t* find_node(cache_t *cache, char *host, char* path, int port);
void free_node(cnode_t *node);
void enter_node(cache_t *cache, cnode_t *node);
void evict_node(cache_t *cache);
void delete_node(cache_t *cache, cnode_t *node);
int cache_check(cache_t *cache);
void Cache_check(cache_t *cache);
