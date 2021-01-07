/***
 *
 *  15-213/18-213: Introduction to Computer Systems
 *  Name: Brandon Wang
 *  AndrewID: bcwang
 *
 *  Sources:
 *  https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
 *  -understanding how getopt parses arguments in the command line
 *  https://www.cs.cmu.edu/~213/recitations/recitation07-cachelab.pdf
 *  -hints on how to approach and view caches and cache problems
 *  https://www.youtube.com/watch?v=xU0ICkgTLTo
 *  -a clear description of what the dirty bit is; less confusing than lecture
 *
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#define addressSize 64

typedef unsigned long long address_t;

typedef struct {
  int s;
  int b;
  int E;              // E = # of cache lines per set
  int S;              // S = 2^s = # of cache sets in cache
  int B;              // B = 2^b = # of cache bytes per line for block data
  int hits;           // total # of hits
  int misses;         // total # of cold/conflict/capacity misses
  int evicts;         // total # of evictions
  int dirty_in_cache; // # of dirty BITS currently in cache
  int dirty_evicted;  // # of dirty BITS evicted
  int verbose;        // 1 if user wants to see all hits/misses
} cache_vars;         // storage for global variables

typedef struct {
  int dirty_bit; // 1 if block needs to be updated
  int valid_bit; // 1 if block is valid
  int uses;      // how often line is used
  address_t tag; // tag could very well be the entire address
} cache_line;

typedef struct {
  cache_line *lines; // array of E lines
} cache_set;

typedef struct {
  cache_set *sets; // array of S sets
} cache;

cache new_cache(cache_vars properties)
    // create and initialize the cache, sets, and lines
{
  cache newCache;
  newCache.sets = calloc(properties.S, sizeof(cache_set));

  int setIndex, lineIndex;
  for (setIndex = 0; setIndex < properties.S; setIndex++) {
    cache_set newSet;
    newSet.lines = calloc(properties.E, sizeof(cache_line));
    newCache.sets[setIndex] = newSet;

    for (lineIndex = 0; lineIndex < properties.E; lineIndex++) {
      cache_line newLine;
      newLine.dirty_bit = 0;
      newLine.valid_bit = 0;
      newLine.tag = 0;
      newSet.lines[lineIndex] = newLine;
    }
  }
  return newCache;
}

int empty_line_index(cache_set currSet, cache_vars properties)
    // return the index of an empty line
{
  int lineIndex;
  for (lineIndex = 0; lineIndex < properties.E; lineIndex++) {
    if (currSet.lines[lineIndex].valid_bit == 0)
      return lineIndex;
  }

  return -1; // all lines in set are filled
}

int LRU_index(cache_set set, cache_vars properties)
    // returns the index of the LRU / least recent uses
{
  int minUsed = set.lines[0].uses;
  int minUsedIndex = 0;
  int lineIndex;
  for (lineIndex = 1; lineIndex < properties.E; lineIndex++) {
    cache_line line = set.lines[lineIndex];
    if (line.uses < minUsed) {
      minUsed = line.uses;
      minUsedIndex = lineIndex;
    }
  }
  return minUsedIndex;
}

int maximumUses(cache_set set, cache_vars properties)
    // returns the maximum number of line uses in the set
{
  int maxUsed = set.lines[0].uses;

  int lineIndex;
  for (lineIndex = 1; lineIndex < properties.E; lineIndex++) {
    cache_line line = set.lines[lineIndex];
    if (line.uses > maxUsed)
      maxUsed = line.uses;
  }
  return maxUsed;
}

int checkHit(cache_line line, address_t tag)
    // checks if the tag will hit the line
{
  if ((line.valid_bit) && (line.tag == tag))
    return 1; // hit!
  return 0;   // miss!
}

int checkFull(cache_set set, cache_vars properties)
    // checks if all lines in the set are full
{
  int i;
  for (i = 0; i < properties.E; i++)
    if (set.lines[i].valid_bit == 0)
      return 0; // not full!

  return 1; // full!
}

cache_vars run_cache(cache currCache, cache_vars properties, address_t address,
                     int isStoring)
    // runs one input from the trace file
{
  // recall: address has format tag:s:b
  int tagSize = addressSize - properties.s - properties.b;
  address_t inputTag = address >> (properties.s + properties.b);
  address_t noTag = (address << tagSize) >> tagSize; // set the tag bits to 0
  address_t setIndex = noTag >> properties.b;
  if (properties.s + properties.b == 0)
    setIndex = 0;
  cache_set set = currCache.sets[setIndex];

  int lineIndex;
  for (lineIndex = 0; lineIndex < properties.E; lineIndex++) {
    cache_line currLine = set.lines[lineIndex];
    if (checkHit(currLine, inputTag)) // hit!
    {
      currLine.uses++;
      properties.hits++;
      if (isStoring && !currLine.dirty_bit) {
        currLine.dirty_bit = 1;
        properties.dirty_in_cache++;
      }
      if (properties.verbose)
        printf(" hit");
      set.lines[lineIndex] = currLine;

      return properties;
    }
  }

  // miss!
  properties.misses++;
  if (properties.verbose)
    printf(" miss");
  int maxUsed = maximumUses(set, properties);

  // no empty line exists, so must first evict evict_index
  if (checkFull(set, properties)) {
    int evict_index = LRU_index(set, properties);

    properties.evicts++;
    set.lines[evict_index].tag = inputTag;
    set.lines[evict_index].uses = maxUsed + 1;
    if (isStoring) {
      if (set.lines[evict_index].dirty_bit)
        properties.dirty_evicted++;
      else {
        set.lines[evict_index].dirty_bit = 1;
        properties.dirty_in_cache++;
      }
    } else if (!isStoring && set.lines[evict_index].dirty_bit) {
      set.lines[evict_index].dirty_bit = 0;
      properties.dirty_in_cache--;
      properties.dirty_evicted++;
    }
    if (properties.verbose)
      printf(" eviction");
  }
  // an empty line exists to store data
  else {
    int empty_index = empty_line_index(set, properties);
    set.lines[empty_index].tag = inputTag;
    set.lines[empty_index].valid_bit = 1;
    set.lines[empty_index].uses = maxUsed + 1;
    if (isStoring && !set.lines[empty_index].dirty_bit) {
      set.lines[empty_index].dirty_bit = 1;
      properties.dirty_in_cache++;
    }
  }
  return properties;
}

void free_cache(cache currCache, cache_vars properties)
    // free all sets and lines in the entire cache when done
{
  if (currCache.sets == NULL)
    return;

  int setIndex;
  for (setIndex = 0; setIndex < properties.S; setIndex++) {
    cache_set currSet = currCache.sets[setIndex];
    if (currSet.lines != NULL)
      free(currSet.lines);
  }
  free(currCache.sets);
}

int main(int argc, char **argv) {
  cache_vars properties;
  properties.verbose = 0;
  properties.hits = 0;
  properties.misses = 0;
  properties.evicts = 0;
  properties.dirty_in_cache = 0;
  properties.dirty_evicted = 0;

  char *traceName; // name of file to read

  int c;
  while ((c = getopt(argc, argv, "vs:E:b:t:")) != -1) {
    switch (c) {
    case 'v':
      properties.verbose = 1;
      break;
    case 's':
      properties.s = atoi(optarg);
      properties.S = 1 << properties.s; // S = 2^s
      break;
    case 'E':
      properties.E = atoi(optarg); // E
      break;
    case 'b':
      properties.b = atoi(optarg);
      properties.B = 1 << properties.b; // B = 2^b
      break;
    case 't':
      traceName = optarg;
      break;
    default:
      abort();
    }
  }

  if ((properties.S <= 0) || (properties.E <= 0) || (properties.B <= 0) ||
      (traceName == NULL)) {
    printf("Some of the given parameters are invalid\n");
    printSummary(-1, -1, -1, -1, -1);
    return 0;
  }

  FILE *traceFile = fopen(traceName, "r");
  char command;
  address_t address;
  int size; // this value is actually unnecessary to find the required
            // information
  cache currCache = new_cache(properties);

  while (fscanf(traceFile, " %c %llx,%d", &command, &address, &size) != -1) {
    if (properties.verbose)
      printf("%c %llx,%d", command, address, size);

    switch (command) {
    case 'L':
      properties = run_cache(currCache, properties, address, 0);
      break;
    case 'S':
      properties = run_cache(currCache, properties, address, 1);
      break;
    default:
      break;
    }

    if (properties.verbose)
      printf("\n");
  }

  printSummary(properties.hits, properties.misses, properties.evicts,
               properties.dirty_in_cache * properties.B,
               properties.dirty_evicted * properties.B);
  free_cache(currCache, properties);
  return 0;
}
