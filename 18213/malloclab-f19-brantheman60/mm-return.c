/*
 *  15-213/18-213: Introduction to Computer Systems
 *  Name: Brandon Wang
 *  AndrewID: bcwang
 *
 *  Sources/References:
 *  -The C Programming Language (2nd Edition): Section 8.7
 *    -demonstrated an implementation of a storage allocator
 *  -Computer Systems: A Programmer's Perspective (3rd Edition): Section 9.9
 *    -great resource for understanding VM models, malloc, and free function
 *    implementations
 ******************************************************************************
 *                                   mm.c                                     *
 *           64-bit struct-based implicit free list memory allocator          *
 *                  15-213: Introduction to Computer Systems                  *
 *                                                                            *
 *  ************************************************************************  *
 *                  TODO: insert your documentation here. :)                  *
 *  Overview of the structure of free and allocated blocks
 *  Definition: free and allocated blocks are part of virtual memory in the
 *heap;
 *  a dynamic collection/set of addresses.
 *  Both free and allocated blocks contain a header, footer, and a payload.
 *  However, the free block additionally contains prev and next pointers
 *  (size 8 bytes each) to the previous and next free blocks
 *
 *  Free block:         [ HEADER | PREV | NEXT | PAYLOAD (garbage) | FOOTER ]
 *  Allocated block:    [ HEADER | PAYLOAD | FOOTER ]
 *
 *  Organization and Manipulation of free list:
 *  This program uses an explicit LIFO free list implementation, so the program
 *  only needs to look at free blocks while allocating and sets a new free block
 *  to the head of the list. To search through the free list, a first-fit search
 *  is used, starting from head_of_free
 *  NULL <-- head_of_free <--> free_2 <--> free_3 <--> ... <--> free_n --> NULL
 *  Note: This is not entirely LIFO. For instance, coalesce case 3 does not
 *  set the new block to head_of_free
 *
 *  ************************************************************************  *
 *  ** ADVICE FOR STUDENTS. **                                                *
 *  Step 0: Please read the writeup!                                          *
 *  Step 1: Write your heap checker. Write. Heap. checker.                    *
 *  Step 2: Place your contracts / debugging assert statements.               *
 *  Good luck, and have fun!                                                  *
 *                                                                            *
 ******************************************************************************
 */

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* Do not change the following! */

#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#define memset mem_memset
#define memcpy mem_memcpy
#endif /* def DRIVER */

/* You can change anything from here onward */

/*
 * If DEBUG is defined (such as when running mdriver-dbg), these macros
 * are enabled. You can use them to print debugging output and to check
 * contracts only in debug mode.
 *
 * Only debugging macros with names beginning "dbg_" are allowed.
 * You may not define any other macros having arguments.
 */
#ifdef DEBUG
/* When DEBUG is defined, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(expr) assert(expr)
#define dbg_assert(expr) assert(expr)
#define dbg_ensures(expr) assert(expr)
#define dbg_printheap(...) print_heap(__VA_ARGS__)
#else
/* When DEBUG is not defined, no code gets generated for these */
/* The sizeof() hack is used to avoid "unused variable" warnings */
#define dbg_printf(...) (sizeof(__VA_ARGS__), -1)
#define dbg_requires(expr) (sizeof(expr), 1)
#define dbg_assert(expr) (sizeof(expr), 1)
#define dbg_ensures(expr) (sizeof(expr), 1)
#define dbg_printheap(...) ((void)sizeof(__VA_ARGS__))
#endif

/* Basic constants */

typedef uint64_t word_t;

// Word and header size (bytes)
static const size_t wsize = sizeof(word_t);

// Double word size (bytes)
static const size_t dsize = 2 * wsize;

// Minimum block size (bytes)
static const size_t min_block_size = 2 * dsize;

// Initial heap size (bytes); also equal to 4 KB
static const size_t chunksize = (1 << 12);

// Get allocated bit from header, which flags block as allocated(1) or free(0)
static const word_t alloc_mask = 0x1;

// Get second bit from header, which flags prev block as allocated(1) or free(0)
// static const word_t alloc_mask = 0x2; //still need to >> 1

// Get size from header; don't need last 4 bits b/c already 16-byte aligned
static const word_t size_mask = ~(word_t)0xF;

/* Represents the header and payload of one block in the heap */
typedef struct block {
  /* Header contains size + allocation flag */
  word_t header;
  char payload[0];
} block_t;

/* Global variables */

// Pointer to first block
static block_t *heap_start = NULL;

/* Function prototypes for internal helper routines */

bool mm_checkheap(int lineno);
static void print_heap(int i);

static block_t *extend_heap(size_t size);
static block_t *find_fit(size_t asize);
static block_t *coalesce_block(block_t *block);
static void split_block(block_t *block, size_t asize);

static size_t max(size_t x, size_t y);
static size_t round_up(size_t size, size_t n);
static word_t pack(size_t size, bool alloc);

static size_t extract_size(word_t header);
static size_t get_size(block_t *block);
static size_t get_payload_size(block_t *block);

static bool extract_alloc(word_t header);
static bool get_alloc(block_t *block);

static void write_header(block_t *block, size_t size, bool alloc);
static void write_footer(block_t *block, size_t size, bool alloc);

static block_t *payload_to_header(void *bp);
static void *header_to_payload(block_t *block);
static word_t *header_to_footer(block_t *block);

static block_t *find_next(block_t *block);
static word_t *find_prev_footer(block_t *block);
static block_t *find_prev(block_t *block);

/** MY OWN FUNCTIONS TO DO EXPLICIT/FREE LIST MANAGEMENT **/

// The head node in the free list; the first free block to search
static block_t *head_of_free;

/*
 * get_next_ptr: returns the "next" pointer located in the (free) block's
 *               payload
 */
static void *get_next_ptr(block_t *block) {
  if (block == NULL)
    return NULL;
  void *bp = header_to_payload(block);
  return *(char **)bp;
}

/*
 * get_prev_ptr: returns the "prev" pointer located in the (free) block's
 *               payload
 */
static void *get_prev_ptr(block_t *block) {
  if (block == NULL)
    return NULL;
  void *bp = header_to_payload(block);
  return *(char **)(bp + wsize);
}

/*
 * set_next_ptr: sets the block after "block" in the free list to next_free
 */
static void set_next_ptr(block_t *block, block_t *next_free) {
  if (block == NULL)
    return;
  void *bp = header_to_payload(block);
  *(void **)bp = next_free;
}

/*
 * set_prev_ptr: sets the block previous to "block" in the free list to
 * prev_free
 */
static void set_prev_ptr(block_t *block, block_t *prev_free) {
  if (block == NULL)
    return;
  void *bp = header_to_payload(block);
  *(void **)(bp + wsize) = prev_free;
}

/*
 * insert_in_free: inserts the block in the free list and makes it the new
 *                 head_of_free
 */
static void insert_in_free(block_t *block) {
  set_next_ptr(block, head_of_free);
  set_prev_ptr(head_of_free, block);
  head_of_free = block;
  set_prev_ptr(head_of_free, NULL);
}

/*
 * remove_from_free: takes out the block from the free list, then links the
 * previous and next blocks together, if possible
 */
static void remove_from_free(block_t *block) {
  block_t *next = get_next_ptr(block);
  block_t *prev = get_prev_ptr(block);

  if (prev == NULL && next == NULL) // Case 1: initial heap
    return;
  else if (prev == NULL && next != NULL) // Case 2: head_of_free
  {
    head_of_free = next;
    set_prev_ptr(next, NULL);
  } else if (prev != NULL && prev == NULL) // Case 3: last in list
  {
    set_next_ptr(prev, NULL);
  } else // Case 4: somewhere between head_of_free and last in list
  {
    set_next_ptr(prev, next);
    set_prev_ptr(next, prev);
  }
}

/*
 * print_free: prints all free blocks in the free list and their
 * current/next/prev
 *             addresses
 */
static void print_free() {
  block_t *block;
  printf("Printing the free list:\n");
  for (block = head_of_free; block != NULL; block = get_next_ptr(block)) {
    printf("Curr: %p:: Next: %p, Prev: %p\n", block, get_next_ptr(block),
           get_prev_ptr(block));
  }
  printf("\n");
}

/*
 * mm_init: creates the initial heap, if possible, and sets it initially to
 *          chunksize bytes
 * Input: void
 * Output: bool (whether or not there was an error initializing the heap)
 * Preconditions:
 * Postconditions:
 */
bool mm_init(void) {
  // Create the initial empty heap
  dbg_printf("Creating initial heap...\n");
  word_t *start = (word_t *)(mem_sbrk(2 * wsize));

  if (start == (void *)-1) { // 0xFFFFFFFFFFFFFFFF
    return false;
  }

  /*
   * Prologue and epilogue sets the boundaries of the heap. They will be
   * referenced by the first block (looks immediately before itself for a
   * block footer) and the last block (looks immediately after itself for a
   * header) respectively.
   */

  start[0] = pack(0, true); // Heap prologue (block footer)
  start[1] = pack(0, true); // Heap epilogue (block header)

  // Heap starts with first "block header", currently the epilogue
  heap_start = (block_t *)&(start[1]);
  head_of_free = heap_start;

  // Extend the empty heap with a free block of chunksize bytes
  // Remember, extend_heap runs coalesce!!!
  if (extend_heap(chunksize) == NULL) {
    return false;
  }

  return true;
}

/*
 * malloc: sets size consecutive bytes of free space in the heap as allocated
 *         (must be 16-byte aligned), and returns the header to that block
 *         after setting the header and footer and splitting the remaining
 *         free space if necessary
 * Input: size_t size (number of bytes to allocate in the heap)
 * Output: void *malloc (pointer to the allocated block)
 * Precondition: size > 0 (though function covers the case where size == 0)
 * Postcondition: bp==NULL || ( get_alloc(bp) &&
 *                 get_payload_size(newptr)==size )  (either the block pointer
 *                 is allocated and now has size bytes, or unsuccessful)
 */
void *malloc(size_t size) {
  dbg_printf("Malloc of size %lu\n", size);
  dbg_requires(mm_checkheap(__LINE__));

  size_t asize;      // Adjusted block size
  size_t extendsize; // Amount to extend heap if no fit is found
  block_t *block;
  void *bp = NULL;

  if (heap_start == NULL) // Initialize heap if it isn't initialized
  {
    mm_init();
  }

  if (size == 0) // Ignore spurious request
  {
    dbg_ensures(mm_checkheap(__LINE__));
    return bp;
  }

  // Adjust block size to include overhead and to meet alignment requirements
  asize = round_up(size + dsize, dsize);

  // Search the free list for a fit
  block = find_fit(asize);

  // If no fit is found, request more memory, and then and place the block
  // Remember, extend_heap will call coalesce!
  if (block == NULL) {
    // Always request at least chunksize
    extendsize = max(asize, chunksize);
    block = extend_heap(extendsize);
    if (block == NULL) // extend_heap returns an error
    {
      return bp;
    }
  }

  // The block should be marked as free
  dbg_assert(!get_alloc(block));

  // Mark block as allocated
  size_t block_size = get_size(block);
  write_header(block, block_size, true);
  write_footer(block, block_size, true);

  // Try to split the block if too large
  split_block(block, asize);

  bp = header_to_payload(block);

  dbg_ensures(mm_checkheap(__LINE__));
  dbg_printheap(1);
  return bp; // note it returns the payload, NOT the header
}

/*
 * free: deallocates the inputted allocated block and coalesces the now-freed
 *       block with surrounding freed blocks
 * Input: void *bp (previously allocated block (hopefully) to be freed)
 * Output: void
 * Preconditions: bp != NULL (though function already covers this case) ||
 *                get_alloc(block) (block is currently still allocated)
 * Postconditions: !get_alloc(block) (the previous block or the coalesced
 *                 block it created is now free)
 */
void free(void *bp) {
  dbg_printf("Freeing block at %p\n", payload_to_header(bp));
  dbg_requires(mm_checkheap(__LINE__));

  if (bp == NULL) {
    return;
  }

  block_t *block = payload_to_header(bp);
  size_t size = get_size(block);

  // The block should be marked as allocated
  dbg_assert(get_alloc(block));

  // Mark the block as free
  write_header(block, size, false);
  write_footer(block, size, false);

  // Try to coalesce the block with its neighbors
  block = coalesce_block(block);

  dbg_ensures(mm_checkheap(__LINE__));
  dbg_printheap(0);
}

/*
 * realloc: change the block size at ptr to whatever the given size is
 * Input: void *ptr (pointer to currently allocated (hopefully) block),
 *        size_t size (new size to set the allocated block to)
 * Output: void *newptr (pointer to block)
 * Precondition: size>=0
 * Postconditions: newptr == NULL || ( get_alloc(newptr) &&
 *                 get_payload_size(newptr)==size )  (either the new pointer
 *                 is allocated and now has size bytes, or unsuccessful)
 */
void *realloc(void *ptr, size_t size) {
  block_t *block = payload_to_header(ptr);
  size_t copysize;
  void *newptr;

  // If size == 0, then free block and return NULL
  if (size == 0) {
    free(ptr);
    return NULL;
  }

  // If ptr is NULL, then equivalent to malloc
  if (ptr == NULL) {
    return malloc(size);
  }

  // Otherwise, proceed with reallocation
  newptr = malloc(size);

  // If malloc fails, the original block is left untouched
  if (newptr == NULL) {
    return NULL;
  }

  // Copy the old data
  copysize = get_payload_size(block); // gets size of old payload
  if (size < copysize) {
    copysize = size;
  }
  memcpy(newptr, ptr, copysize);

  // Free the old block
  free(ptr);

  return newptr;
}

/*
 * calloc: essentially malloc(elements*size); allocate space in the heap to
 *         store "elements" consecutive elements, each of size "size"; also
 *         initializes all of the payload bits
 * Input: size_t elements (number of elements to store),
 *        size_t size (size in bytes of each element)
 * Output: void* (generic pointer to the ????, or NULL if unable to calloc
 *         the elements properly)
 * Preconditions: elements>=0,
 *                size>=0,
 *                (elements * size) / elements != size (no overflow)
 *                although this case is covered
 * Postconditions: bp == NULL || get_alloc(bp) (either pointer to allocated
 *                 block is marked allocated or NULL if problem with creating
 *                 space for calloc)
 */
void *calloc(size_t elements, size_t size) {
  void *bp;
  size_t asize = elements * size;

  if (asize / elements != size) {
    // Multiplication overflowed
    return NULL;
  }

  bp = malloc(asize);
  if (bp == NULL) {
    return NULL;
  }

  // Initialize all bits to 0
  memset(bp, 0, asize);

  return bp;
}

/******** The remaining content below are helper and debug routines ********/

/*
 * extend_heap: extends the size of the heap, sets the extended space
 *              as a free block, then coalesces it if necessary
 * Input: size_t size (number of bytes to extend by, though may be rounded up)
 * Output: block_t *block (pointer to the freed block at the end of the heap)
 * Preconditions: size>=0 (if size<0 and round_up(size, dsize)<0,
 *                mem_sbrk(size) will fail)
 * Postconditions: block == NULL || !get_alloc(block) (the last block is freed
 *                 or cannot be extended)
 */
static block_t *extend_heap(size_t size) {
  dbg_printf("Extending heap...\n");
  void *bp;

  // Allocate an even number of words to maintain alignment
  size = round_up(size, dsize);
  if ((bp = mem_sbrk(size)) == (void *)-1) {
    return NULL;
  }

  /*
   * TODO: delete or replace this comment once you've thought about it.
   * Think about what bp represents. Why do we write the new block
   * starting one word BEFORE bp, but with the same size that we
   * originally requested?
   */

  // Initialize free block header/footer
  block_t *block = payload_to_header(bp);
  write_header(block, size, false);
  write_footer(block, size, false);

  // Create new epilogue header
  block_t *block_next = find_next(block);
  write_header(block_next, 0, true);

  // Coalesce in case the previous block was free
  block = coalesce_block(block);
  dbg_ensures(!get_alloc(block));

  return block;
}

/*
 * coalesce_block: AFTER freeing a block, join it with any adjacent freed
 *                 blocks before and after it. Also manages free list.
 * Input: block_t *block (recently freed block)
 * Output: block_t* block (header of the coalesced free block)
 * Preconditions: !get_alloc(block) (block is already freed)
 * Postconditions: !get_alloc(block) (the coalesced block is freed)
 */
static block_t *coalesce_block(block_t *block) {
  dbg_printf("Coalescing...\n");
  dbg_requires(!get_alloc(block));

  size_t size = get_size(block);

  block_t *block_next = find_next(block);
  block_t *block_prev = find_prev(block);

  bool prev_alloc = extract_alloc(*find_prev_footer(block));
  bool next_alloc = get_alloc(block_next);
  dbg_printf("Prev_alloc = %d, Next_alloc = %d\n", prev_alloc, next_alloc);

  if (prev_alloc && next_alloc) // Case 1
  {
    // No need to coalesce, but still need to insert_in_free
    // Also, consider the case where we are at heap_start
    if (block == heap_start) {
      if (block != head_of_free) // block is head of free list
        insert_in_free(block);
    } else {
      insert_in_free(block);
    }
  } else if (prev_alloc && !next_alloc) // Case 2
  {
    size += get_size(block_next);
    write_header(block, size, false);
    write_footer(block, size, false);
    insert_in_free(block);
    remove_from_free(block_next);
  } else if (!prev_alloc && next_alloc) // Case 3
  {
    size += get_size(block_prev);
    write_header(block_prev, size, false);
    write_footer(block_prev, size, false);
    // remove_from_free(block_prev);
    // insert_in_free(block_prev);
    block = block_prev;
  } else if (!prev_alloc && !next_alloc) // Case 4
  {
    /*
    size += get_size(block_next) + get_size(block_prev);
    write_header(block_prev, size, false);
    write_footer(block_prev, size, false);
    remove_from_free(block_prev);
    remove_from_free(block_next);
    block = block_prev;
    insert_in_free(block);
    */

    // SO much easier if we use circular list instead
    size += get_size(block_next) + get_size(block_prev);
    write_header(block_prev, size, false);
    write_footer(block_prev, size, false);
    if (get_next_ptr(block_prev) == block_next)
      // block_prev points to block_next
      remove_from_free(block_next);
    else if (get_next_ptr(block_next) == block_prev)
      // block_next points to block_prev
      remove_from_free(block_next);
    else {
      remove_from_free(block_prev);
      remove_from_free(block_next);
      insert_in_free(block_prev);
    }
    block = block_prev;
  }
  dbg_ensures(!get_alloc(block));

  return block;
}

/*
 * split_block: if allocated space is smaller than free space, convert the
 *              first asize bytes into an allocated block and the remaining
 *              bytes into a free block, all with the correct headers and
 *              footers. Also manages the free list.
 * Input: block_t* block (free space where the allocated block will go),
 *        size_t asize (space to be allocated)
 * Output: void
 * Preconditions: get_alloc(block) (block is allocated),
 *                asize>0
 * Postconditions: get_alloc(block) (block is allocated)
 */
static void split_block(block_t *block, size_t asize) {
  dbg_printf("Splitting block %p\n", block);

  size_t block_size = get_size(block);

  if ((block_size - asize) >= min_block_size) {
    write_header(block, asize, true);
    write_footer(block, asize, true);

    block_t *block_next = find_next(block);
    write_header(block_next, block_size - asize, false);
    write_footer(block_next, block_size - asize, false);

    // Safe to remove now-allocated block from free list?
    if (get_prev_ptr(block) != NULL || get_next_ptr(block) != NULL) {
      remove_from_free(block);
    }
    insert_in_free(block_next);
  }
  remove_from_free(block);
  // dbg_printheap(0);
  dbg_ensures(get_alloc(block));
}

/*
 * find_fit: FIRST-FIT search for a free block to store an allocated block
 *           of size asize using the free list
 * Input: size_t asize (requested size of the allocated block)
 * Output: block_t *block (header of the space to allocate block, or NULL if
 *         no such block was found in the heap)
 * Preconditions: asize>=0
 * Postconditions: block==NULL || !get_alloc(block) (either space is free or
 *                 does not exist)
 */
static block_t *find_fit(size_t asize) {
  block_t *block;
  /*
  for (block = heap_start; get_size(block) > 0; block = find_next(block)) {
    if (!(get_alloc(block)) && (asize <= get_size(block))) {
      return block;
    }
  }
  */

  for (block = head_of_free; block != NULL; block = get_next_ptr(block)) {
    if (asize <= get_size(block))
      return block;
  }

  return NULL; // no fit found
}

/*
 * checkheap: ensures that for every block in the heap, the headers and footers
 *            match, the allocation bits are correct, the sizes are proper, the
 *            free list is correct, no two adjacent blocks are free, etc.
 * Input: int line (can be anything, really)
 * Output: bool (true if heap is currently correct, false if there is an issue)
 * Precondition:
 * Postcondition:
 */
bool mm_checkheap(int line) {
  block_t *block;
  bool prev_alloc = true;

  for (block = heap_start; get_size(block) > 0; block = find_next(block)) {
    if (get_size(find_next(block)) > 0 && // doesn't matter after epilogue
        ((size_t)header_to_payload(block)) % dsize != 0) {
      printf("header is not double-word aligned at address %p\n", &block);
      printf("(size_t) block is %lx", (size_t)block);
      return false;
    }

    // Check that headers and footer match FOR ALL BLOCKS
    size_t hsize = get_size(block);
    size_t fsize = (*header_to_footer(block)) & size_mask;
    bool halloc = get_alloc(block);
    bool falloc = (*header_to_footer(block)) & alloc_mask;
    if ((hsize != fsize) || (halloc != falloc)) {
      printf("Headers and footer do not match at address %p\n", &block);
      return false;
    }

    // Check that the sizes of the header/footer are correct
    if (hsize < 0 || fsize < 0) {
      printf("Size of block is invalid at address %p\n", &block);
      return false;
    }

    // Check that no two adjacent blocks are free
    if (!prev_alloc && !halloc) {
      printf("There are two adjacent free blocks that are not coalesced\n");
      return false;
    } else
      prev_alloc = halloc;
  }

  // Check that the free list is correct
  block_t *next;
  for (block = head_of_free; block != NULL; block = get_next_ptr(block)) {
    // Check that all blocks have an allocated bit of 0
    if (get_alloc(block)) {
      printf("Allocated block in the free list!\n");
      return false;
    }

    // Check that the block address is acceptable
    if ((int)block < (int)mem_heap_lo() || (int)block > (int)mem_heap_hi()) {
      printf("Block at %p is not in the range of the heap\n", next);
      return false;
    }

    // Check that the next and previous blocks are doubly-linked
    next = get_next_ptr(block);
    if (next != NULL && get_prev_ptr(next) != block) {
      printf("current block in free list: %p\n", block);
      printf("get_prev_ptr(get_next_ptr(block)): %p\n", get_prev_ptr(next));
      printf("Adjacent frees' next and prev pointers do not match up\n");
      return false;
    }
  }

  return true;
}
/*
 * print_heap: prints all blocks in the heap
 * Input: int i (whether done allocating or freeing)
 * Output:
*/
static void print_heap(int i) {
  if (i)
    printf("Done allocating:\n");
  else
    printf("Done freeing:\n");

  block_t *block;
  for (block = heap_start; get_size(block) > 0; block = find_next(block)) {
    word_t header = get_size(block) | get_alloc(block);

    printf("Address: %p    ", block);
    printf("Header: %lx    ", header);
    size_t fsize = (*header_to_footer(block)) & size_mask;
    bool falloc = (*header_to_footer(block)) & alloc_mask;
    word_t footer = fsize | falloc;
    printf("Footer: %lx    ", footer);

    printf("SIZE: %zu, ", get_size(block));
    printf("ALLOC STATUS: %d\n", get_alloc(block));
  }
  print_free(); // also print free list
}
/*
 *****************************************************************************
 * The functions below are short wrapper functions to perform                *
 * bit manipulation, pointer arithmetic, and other helper operations.        *
 *                                                                           *
 * We've given you the function header comments for the functions below      *
 * to help you understand how this baseline code works.                      *
 *                                                                           *
 * Note that these function header comments are short since the functions    *
 * they are describing are short as well; you will need to provide           *
 * adequate details within your header comments for the functions above!     *
 *                                                                           *
 *                                                                           *
 * Do not delete the following super-secret(tm) lines!                       *
 *                                                                           *
 * 53 6f 20 79 6f 75 27 72 65 20 74 72 79 69 6e 67 20 74 6f 20               *
 *                                                                           *
 * 66 69 67 75 72 65 20 6f 75 74 20 77 68 61 74 20 74 68 65 20               *
 * 68 65 78 61 64 65 63 69 6d 61 6c 20 64 69 67 69 74 73 20 64               *
 * 6f 2e 2e 2e 20 68 61 68 61 68 61 21 20 41 53 43 49 49 20 69               *
 *                                                                           *
 * 73 6e 27 74 20 74 68 65 20 72 69 67 68 74 20 65 6e 63 6f 64               *
 * 69 6e 67 21 20 4e 69 63 65 20 74 72 79 2c 20 74 68 6f 75 67               *
 * 68 21 20 2d 44 72 2e 20 45 76 69 6c 0a de ba c1 e1 52 13 0a               *
 *                                                                           *
 *****************************************************************************
 */

/*
 * max: returns x if x > y, and y otherwise.
 */
static size_t max(size_t x, size_t y) { return (x > y) ? x : y; }

/*
 * round_up: Rounds size up to next multiple of n
 */
static size_t round_up(size_t size, size_t n) {
  return n * ((size + (n - 1)) / n);
}

/*
 * pack: returns a header reflecting a specified size and its alloc status.
 *       If the block is allocated, the lowest bit is set to 1, and 0 otherwise.
 */
static word_t pack(size_t size, bool alloc) {
  return alloc ? (size | alloc_mask) : size;
}

/*
 * extract_size: returns the size of a given header value based on the header
 *               specification above.
 */
static size_t extract_size(word_t word) { return (word & size_mask); }

/*
 * get_size: returns the size of a given block by clearing the lowest 4 bits
 *           (as the heap is 16-byte aligned).
 */
static size_t get_size(block_t *block) { return extract_size(block->header); }

/*
 * get_payload_size: returns the payload size of a given block, equal to
 *                   the entire block size minus the header and footer sizes.
 */
static word_t get_payload_size(block_t *block) {
  size_t asize = get_size(block);
  return asize - dsize;
}

/*
 * extract_alloc: returns the allocation status of a given header value based
 *                on the header specification above.
 */
static bool extract_alloc(word_t word) { return (bool)(word & alloc_mask); }

/*
 * get_alloc: returns true when the block is allocated based on the
 *            block header's lowest bit, and false otherwise.
 */
static bool get_alloc(block_t *block) { return extract_alloc(block->header); }

/*
 * write_header: given a block and its size and allocation status,
 *               writes an appropriate value to the block header.
 * Preconditions: block != NULL
 * Postconditions: block->header != NULL,
 *                 (alloc && block->header ==  (size | alloc_mask))
 *              || (!alloc && block->header ==  size);
 */
static void write_header(block_t *block, size_t size, bool alloc) {
  dbg_requires(block != NULL);
  block->header = pack(size, alloc);
}

/*
 * write_footer: given a block and its size and allocation status,
 *               writes an appropriate value to the block footer by first
 *               computing the position of the footer.
 * Preconditions: block != NULL, get_size(block) == size, size > 0
 * Postconditions: footerp != NULL
 * TODO: Are there any preconditions or postconditions?
 */
static void write_footer(block_t *block, size_t size, bool alloc) {
  dbg_requires(block != NULL);
  dbg_requires(get_size(block) == size && size > 0);
  word_t *footerp = header_to_footer(block);
  *footerp = pack(size, alloc);
}

/*
 * find_next: returns the next consecutive block on the heap by adding the
 *            size of the block.
 */
static block_t *find_next(block_t *block) {
  dbg_requires(block != NULL);
  dbg_requires(get_size(block) != 0);
  return (block_t *)((char *)block + get_size(block));
}

/*
 * find_prev_footer: returns the footer of the previous block.
 */
static word_t *find_prev_footer(block_t *block) {
  // Compute previous footer position as one word before the header
  return &(block->header) - 1;
}

/*
 * find_prev: returns the previous block position by checking the previous
 *            block's footer and calculating the start of the previous block
 *            based on its size.
 */
static block_t *find_prev(block_t *block) {
  dbg_requires(block != NULL);
  dbg_requires(get_size(block) != 0);
  word_t *footerp = find_prev_footer(block);
  size_t size = extract_size(*footerp);
  return (block_t *)((char *)block - size);
}

/*
 * payload_to_header: given a payload pointer, returns a pointer to the
 *                    corresponding block.
 */
static block_t *payload_to_header(void *bp) {
  return (block_t *)((char *)bp - offsetof(block_t, payload));
}

/*
 * header_to_payload: given a block pointer, returns a pointer to the
 *                    corresponding payload.
 */
static void *header_to_payload(block_t *block) {
  return (void *)(block->payload);
}

/*
 * header_to_footer: given a block pointer, returns a pointer to the
 *                   corresponding footer.
 */
static word_t *header_to_footer(block_t *block) {
  return (word_t *)(block->payload + get_size(block) - dsize);
}
