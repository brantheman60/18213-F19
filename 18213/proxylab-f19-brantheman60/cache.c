/*
 * 15-213/18-213: Introduction to Computer Systems
 * Name: Brandon Wang
 * AndrewID: bcwang
 */

#include "csapp.h"
#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * nodecmp: compare node with the uri
 * Input: cnode_t *node
 *        uri elements
 * Output: int (0 if matches, 1(nonzero) if doesn't)
 */
int nodecmp(cnode_t *node, char *host, char *path, int port)
{
    if(strcmp(node->host, host)) return 1;
    if(strcmp(node->path, path)) return 1;
    if(node->port != port) return 1;
    return 0;
}

/*
 * cache_init: initialize the contents of the cache
 * Input: cache_t *cache
 */
void cache_init(cache_t *cache)
{
    cache->head = NULL;
    cache->tail = NULL;
    cache->node_cnt = 0;
    cache->load = 0;
}

/*
 * free_cache: free the contents of the cache
 * Input: cache_t *cache
 */
void free_cache(cache_t *cache)
{
    if(cache->head != NULL)
        Free(cache->head);
    if(cache->tail != NULL)
        Free(cache->head);
    Free(cache);
}

/*
 * create_node: create a pointer to a new node
 * Input: uri elements
 *        char *payload
 *        int size
 */
cnode_t* create_node(char *host, char *path, int port,
    char *payload, int size)
{
    cnode_t *node = Malloc(sizeof(cnode_t));
    node->prev = NULL;
    node->next = NULL;
    node->size = size;
    node->payload = Malloc(size);
    memcpy(node->payload, payload, size);

    node->host = Malloc(strlen(host) + 1);
    node->path = Malloc(strlen(path) + 1);
    strcpy(node->host, host);
    strcpy(node->path, path);
    node->port = port;
    return node;
}

/*
 * find_node: mache the uri (key) with a cache node
 * Input: cache_t *cache
 *        uri elements
 */
cnode_t* find_node(cache_t *cache, char *host, char* path, int port)
{
    cnode_t *node;
    //begin with tail for optimization
    for(node = cache->tail; node != NULL; node = node->prev)
    {
        if(!nodecmp(node, host, path, port))
            return node;
    }
    return NULL;
}

/*
 * free_node: free the contents of the node
 * Input: cnode_t *node
 */
void free_node(cnode_t *node)
{
    if(node->host != NULL)
        Free(node->host);
    if(node->path != NULL)
        Free(node->path);
    if(node->payload != NULL)
        Free(node->payload);
    Free(node);
}

/*
 * enter_node: add a node to the cache as the most recently used node
 * Input: cache_t *cache
 *        cnode_t *node
 */
void enter_node(cache_t *cache, cnode_t *node)
{
    if(cache->node_cnt == 0) //cache is empty
    {
        cache->head = node;
        cache->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    else //cache is not empty, simply add to the tail
    {
        cache->tail->next = node;
        node->prev = cache->tail;
        node->next = NULL;
        cache->tail = node;
    }
    (cache->load) += (node->size);
    cache->node_cnt++;
}

/*
 * evict_node: remove the head node (LRU node) of the cache
 * Input: cache_t *cache
 */
void evict_node(cache_t *cache)
{
    cnode_t *node = cache->head;
    if(node == NULL) //Case 1: empty
        return;
    else if(node == cache->tail) //Case 2: only node
    {
        cache->head = NULL;
        cache->tail = NULL;
    }
    else //Case 3: not the only node
    {
        (node->next)->prev = NULL;
        cache->head = node->next;
    }
    (cache->load) -= (node->size);
    cache->node_cnt--;
    free_node(node);
}

/*
 * delete_node: remove the node from the cache
 * Input: cache_t *cache
 *        cnode_t *node (must be a part of cache)
 */
void delete_node(cache_t *cache, cnode_t *node)
{
    if(cache->node_cnt == 1)    //Case 1: only one in cache
    {
        cache->head = NULL;
        cache->tail = NULL;
    }
    else if(node->prev == NULL) //Case 2: head
    {
        cache->head = node->next;
        (cache->head)->prev = NULL;
    }
    else if(node->next == NULL) //Case 3: tail
    {
        cache->tail = node->prev;
        (cache->tail)->next = NULL;
    }
    else                        //Case 4: in between
    {
        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;
    }
    (cache->load) -= (node->size);
    cache->node_cnt--;
}

/*
 * cache_check: ensures that the cache is correct at this point
 * Input: cache_t *cache
 * Output: int (1 if correct, 0 if not)
 */
int cache_check(cache_t *cache)
{
    if(cache->node_cnt == 0)
        return 1;
    else if(cache->node_cnt == 1)
    {
        if(cache->head != cache->tail)
        {
            printf("Head should equal tail\n");
            return 0;
        }
        if(cache->head->prev != NULL)
        {
            printf("Head->prev should equal NULL\n");
            return 0;
        }
        if(cache->tail->next != NULL)
        {
            printf("Tail->next should equal NULL\n");
            return 0;
        }
        return 1;
    }
    //else
    int count = 1;
    cnode_t *node;
    for(node = cache->head; node->next != NULL; node = node->next)
    {
        count++;
        if(node != (node->next)->prev)
        {
            printf("next and prev do not match\n");
            return 0;
        }
    }
    if(node != cache->tail)
    {
        printf("last node is not tail\n");
        return 0;
    }
    if(cache->head->prev != NULL)
    {
        printf("head->prev should equal NULL\n");
        return 0;
    }
    if(count != cache->node_cnt)
    {
        printf("wrong value of node_cnt\n");
        return 0;
    }
    return 1;
}

/*
 * Cache_check: exit w/ print statement if cache_check == 0
 * Input: cache_t *cache
 */
void Cache_check(cache_t *cache)
{
    if(!cache_check(cache))
    {
        printf("Error in cache!\n");
        exit(1);
    }
}
