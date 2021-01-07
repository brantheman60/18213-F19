/***
 *
 *  15-213/18-213: Introduction to Computer Systems
 *  Name: Brandon Wang
 *  AndrewID: bcwang
 *
 *  Sources:
 *  http://csapp.cs.cmu.edu/public/waside/waside-blocking.pdf
 *  -helped me use set up code similar to blocked matrix multiply to set up
 *   and approach transpose_submit
 *
 ***/

/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(size_t M, size_t N, double A[N][M], double B[M][N], double *tmp);
 * A is the source matrix, B is the destination
 * tmp points to a region of memory able to hold TMPCOUNT (set to 256) doubles
 *as temporaries
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 2KB direct mapped cache with a block size of 64 bytes.
 *
 * Programming restrictions:
 *   No out-of-bounds references are allowed
 *   No alterations may be made to the source array A
 *   Data in tmp can be read or written
 *   This file cannot contain any local or global doubles or arrays of doubles
 *   You may not use unions, casting, global variables, or
 *     other tricks to hide array data in other forms of local or global memory.
 */
#include <stdio.h>
#include <stdbool.h>
#include "cachelab.h"
#include "contracts.h"
#define blockA_size 8
#define blockB_size 4
#define blockC_size 4

// size_t TMPCOUNT; //max number of elements in tmp

/* Forward declarations */
static bool is_transpose(size_t M, size_t N, const double A[N][M],
                         const double B[M][N]);
static void trans(size_t M, size_t N, const double A[N][M], double B[M][N],
                  double *tmp);
static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
static const char transpose_submit_desc[] = "Transpose submission";

static void transpose_submit(size_t M, size_t N, const double A[N][M],
                             double B[M][N], double *tmp) {
  // N is number of rows in A
  // M is number of columns in A
  int blockRow, blockCol, row, col;
  int diagIndex; // store diagonal values to save cycles
  double diagVal;

  // Case A: 32 x 32; divide into 4x4 grid of 8x8 blocks
  if (N == 32 && M == 32) {
    for (blockRow = 0; blockRow < N; blockRow += blockA_size)
      for (blockCol = 0; blockCol < M; blockCol += blockA_size)
        for (row = blockRow; row < blockRow + blockA_size; row++) {
          for (col = blockCol; col < blockCol + blockA_size; col++) {
            if (row == col) {
              diagVal = A[row][col];
              diagIndex = row;
            } else
              B[col][row] = A[row][col];
          }
          if (blockRow == blockCol)
            B[diagIndex][diagIndex] = diagVal;
        }
  }
  // Case B: 65x63; approximately break into ??? grid of ??? blocks
  //         careful to not surpass dimensions of A for row and col
  else if (N == 65 && M == 63) {
    for (blockRow = 0; blockRow < N; blockRow += blockB_size)
      for (blockCol = 0; blockCol < M; blockCol += blockB_size)
        for (row = blockRow; (row < blockRow + blockB_size) && (row < N);
             row++) {
          for (col = blockCol; (col < blockCol + blockB_size) && (col < M);
               col++) {
            if (row == col) {
              diagVal = A[row][col];
              diagIndex = row;
            } else
              B[col][row] = A[row][col];
          }
          if (blockRow == blockCol)
            B[diagIndex][diagIndex] = diagVal;
        }
  }
  // Case C: any matrix allowed, so group into 8x8 blocks
  else {
    for (blockRow = 0; blockRow < N; blockRow += blockC_size)
      for (blockCol = 0; blockCol < M; blockCol += blockC_size)
        for (row = blockRow; (row < blockRow + blockC_size) && (row < N);
             row++) {
          for (col = blockCol; (col < blockCol + blockC_size) && (col < M);
               col++) {
            if (row == col) {
              diagVal = A[row][col];
              diagIndex = row;
            } else
              B[col][row] = A[row][col];
          }
          if (blockRow == blockCol)
            B[diagIndex][diagIndex] = diagVal;
        }
  }
}
/*
 * You can define additional transpose functions below. We've defined
 * some simple ones below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
static const char trans_desc[] = "Simple row-wise scan transpose";

/*
 * The following shows an example of a correct, but cache-inefficient
 *   transpose function.  Note the use of macros (defined in
 *   contracts.h) that add checking code when the file is compiled in
 *   debugging mode.  See the Makefile for instructions on how to do
 *   this.
 *
 *   IMPORTANT: Enabling debugging will significantly reduce your
 *   cache performance.  Be sure to disable this checking when you
 *   want to measure performance.
 */
static void trans(size_t M, size_t N, const double A[N][M], double B[M][N],
                  double *tmp) {
  size_t i, j;

  REQUIRES(M > 0);
  REQUIRES(N > 0);

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      B[j][i] = A[i][j];
    }
  }

  ENSURES(is_transpose(M, N, A, B));
}

/*
 * This is a contrived example to illustrate the use of the temporary array
 */

static const char trans_tmp_desc[] =
    "Simple row-wise scan transpose, using a 2X2 temporary array";

static void trans_tmp(size_t M, size_t N, const double A[N][M], double B[M][N],
                      double *tmp) {
  size_t i, j;
  /* Use the first four elements of tmp as a 2x2 array with row-major ordering.
   */
  REQUIRES(M > 0);
  REQUIRES(N > 0);

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      int di = i % 2;
      int dj = j % 2;
      tmp[2 * di + dj] = A[i][j];
      B[j][i] = tmp[2 * di + dj];
    }
  }

  ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions(void) {
  /* Register your solution function */
  registerTransFunction(transpose_submit, transpose_submit_desc);

  /* Register any additional transpose functions */
  registerTransFunction(trans, trans_desc);
  registerTransFunction(trans_tmp, trans_tmp_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
static bool is_transpose(size_t M, size_t N, const double A[N][M],
                         const double B[M][N]) {
  size_t i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; ++j) {
      if (A[i][j] != B[j][i]) {
        return false;
      }
    }
  }
  return true;
}
