//#include <stdio.h>

/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      /* brief description of how your implementation works */
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  3. Function arguments and local variables (no global variables).
  4. Local variables of type int and long
  5. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  6. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  7. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
   */
  long pow2plus1(long x) {
     /* exploit ability of shifts to compute powers of 2 */
     /* Note that the 'L' indicates a long constant */
     return (1L << x) + 1L;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
   */
  long pow2plus4(long x) {
     /* exploit ability of shifts to compute powers of 2 */
     long result = (1L << x);
     result += 4L;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7L, 0xEL) = 0xFFFFFFFFFFFFFFF6L
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
long bitMatch(long x, long y) {
    long bothOne = x & y; //wherever 1s match
    long bothZero = (~x) & (~y); //wherever 0s match
    return ~( (~bothOne) & (~bothZero)); //bothOne | bothZero, by De Morgan's
}
//2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
    long LSB = x & 1L;
    // 111...1 + (0 if LSB=1, 1 if LSB=0)
    return ~(0L) + !LSB;
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
long distinctNegation(long x) {
  /*
   * based off the assumption that returns 0 iff x=0:
   *    return !(!x);
   */
    long negX = ~x + 1L;
    return !!(x ^ negX);
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96L) = 0x20L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
long leastBitPos(long x) {
    //  x     = 101010000
    // ~x     = 010101111
    // ~x + 1 = 010110000
    return x & (~x + 1);
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
*   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
    long xSign = x>>63 & 1L;
    long noRemainder = !(x ^ ((x>>n)<<n));//0 if not divible, 1 if is divisible

    //add 1 to result if negative and x is not divisible by 4
    return (x>>n) + (xSign & !noRemainder);
}
//3
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) {
    //return y if x≠0, return z if x=0
    long yesLeft = ~(0L) + !x;     // 111...1 + (0 if x≠0, 1 if x=0)
    long yesRight = ~(0L) + !(!x); // 111...1 + (1 if x≠0, 0 if x=0)
    return (y & yesLeft) + (z & yesRight);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4L,5L) = 1L.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isLessOrEqual(long x, long y) {
    long xSign = (x>>63L) & 1L;
    long ySign = (y>>63L) & 1L;
    long diffSign = ((y + ~x + 1)>>63) & 1L; //LSB of (y-x)>>63
    //if x=1 and y=0, return 1
    //if x=0 and y=1, return 0
    //all else, return !diffSign (0 if x>y, 1 if x<=y)
    //logically equal to !((!x & (y | diff)) | x&y&diff)
    //                         logicA           logicB
    long logicA = (!xSign) & (ySign | diffSign);
    long logicB = xSign & ySign & diffSign;
    return !(logicA | logicB);
}
//4
/*
 * hexAllLetters - return 1 if the hex representation of x
 *   contains only characters 'a' through 'f'
 *   Example: hexAllLetters(0xabcdefabcdefabcdL) = 1L.
 *            hexAllLetters(0x4031323536373839L) = 0L.
 *            hexAllLetters(0x00AAABBBCCCDDDEEL) = 0L.
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 30
 *   Rating: 4
 */
long hexAllLetters(long x) {
    //CANNOT USE + OPERATOR!!!
    //only have: ! ~ & ^ | << >>
    //a - f has forms: 1010, 1011, 1100, 1101, 1110, 1111
    //  inverted:      0101, 0100, 0011, 0010, 0001, 0000
    //other has forms: 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001
    //  special cases: 1000, 1001
    //  inverted:      0111, 0110

    long two_16 = (0x22L<<8) | 0x22L;
    long two_32 = (two_16<<16) | two_16;
    long two_64 = (two_32<<32) | two_32; //0x2222222222222222
    long four_64 = two_64<<1;            //0x4444444444444444
    long eight_64 = four_64<<1;          //0x8888888888888888

    long fourthOK = !((x & eight_64) ^ eight_64); //1 if 4th bits ok, 0 if not
    long thirdBits = (x=~x) & four_64; //everything inverted!  XXXX & 0100
    long secondBits = x & two_64;                         // XXXX & 0010
    long secondThirdOK = !(thirdBits & (secondBits<<1));  // should be 1 if ok

    return secondThirdOK & fourthOK;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples:
 *    trueThreeFourths(11L) = 8
 *    trueThreeFourths(-9L) = -6
 *    trueThreeFourths(4611686018427387904L) = 3458764513820540928L (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
long trueThreeFourths(long x)
{
    long xSign = x>>63 & 1L;
    long LSB = x & 1L;
    long LSB2 = (x & 2L)>>1;
    long buffer = LSB2 + LSB;

    //First, let additional buffer be LSB2 + LSB. Then, must also...
    //if x<0 and |x| mod 4 = 0, add 0     if x>0 and x mod 4 = 0, add 0
    //if x<0 and |x| mod 4 = 1, add 0     if x>0 and x mod 4 = 1, subtract 1
    //if x<0 and |x| mod 4 = 2, add 1     if x>0 and x mod 4 = 2, add 0
    //if x<0 and |x| mod 4 = 3, add 1     if x>0 and x mod 4 = 3, add 0

    x = x>>2;
    buffer = buffer + (~0) + (xSign | LSB2 | !LSB);
    buffer = buffer + (xSign & LSB2);

    return (x + x + x) + buffer;
}
/*
* bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5L) = 2, bitCount(7L) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
long bitCount(long x) {
    //need the following masks: 0x5555555555555555
    //                          0x3333333333333333
    //                          0x0F0F0F0F0F0F0F0F
    //                          0x00FF00FF00FF00FF
    //                          0x0000FFFF0000FFFF
    //                          0x00000000FFFFFFFF

    long group32 = (1L<<32) + ~0L;                      //0x00000000FFFFFFFF
    long group16 = (group32<<16) ^ group32;             //0x0000FFFF0000FFFF
    long group8 = (group16<<8) ^ group16;               //0x00FF00FF00FF00FF
    long group4 = (group8<<4) ^ group8;                 //0x0F0F0F0F0F0F0F0F
    long group2 = (group4<<2) ^ group4;                 //0x3333333333333333
    long group1 = (group2<<1) ^ group2;                 //0x5555555555555555

    //idea is to use the bits to actually count the number of 1 bits
    //by adding them to find the number of bits per pair, then per
    //groups of 4, then groups of 8, etc.

    //count number of 1s in every group of 2
    long count2 = ((x>>1) & group1) + (x & group1);
    //count number of 1s in every group of 4, etc.
    long count4 = ((count2>>2) & group2) + (count2 & group2);
    long count8 = ((count4>>4) & group4) + (count4 & group4);
    long count16 = ((count8>>8) & group8) + (count8 & group8);
    long count32 = ((count16>>16) & group16) + (count16 & group16);
    long count64 = ((count32>>32) & group32) + (count32 & group32);

    return count64;
}
/*
 * isPalindrome - Return 1 if bit pattern in x is equal to its mirror image
*   Example: isPalindrome(0x0F0F0F0123c480F0F0F0F0L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
long isPalindrome(long x) {
    //need the following masks: 0x5555555555555555
    //                          0x3333333333333333
    //                          0x0F0F0F0F0F0F0F0F
    //                          0x00FF00FF00FF00FF
    //                          0x0000FFFF0000FFFF
    //                          0x00000000FFFFFFFF

    long group32 = (1L<<32) + ~0L;                      //0x00000000FFFFFFFF
    long group16 = (group32<<16) ^ group32;             //0x0000FFFF0000FFFF
    long group8 = (group16<<8) ^ group16;               //0x00FF00FF00FF00FF
    long group4 = (group8<<4) ^ group8;                 //0x0F0F0F0F0F0F0F0F
    long group2 = (group4<<2) ^ group4;                 //0x3333333333333333
    long group1 = (group2<<1) ^ group2;                 //0x5555555555555555

    //idea is very similar to bitCount and uses same masks:
    //break into halves in different ways to reverse the palindrome
    long lower = (long) ((int) x); //takes the lower half of x w/ extra room

    //flip all bits in every group of 2
    long flip2 = ((lower>>1) & group1) + ((lower & group1)<<1);
    //flip all bits in every group of 4, etc.
    long flip4 = ((flip2>>2) & group2) + ((flip2 & group2)<<2);
    long flip8 = ((flip4>>4) & group4) + ((flip4 & group4)<<4);
    long flip16 = ((flip8>>8) & group8) + ((flip8 & group8)<<8);
    long flip32 = ((flip16>>16) & group16) + ((flip16 & group16)<<16);

    //ensure that first half of x equals second half of x
    long equal = !( (x & ~group32) ^ (flip32<<32) );

    return equal;
}
//float
/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
    //single precision: 1 sign bit, 8 exp bits, 23 fraction bits
    int expf = uf & 0x7F800000;
    int expg = ug & 0x7F800000;
    int fracf = uf & 0x007FFFFF;
    int fracg = ug & 0x007FFFFF;

    //even if uf != ug, still match when:
    //  exp = 00000000 and frac = 0...000 (+0/-0)
    //return 1 if both are infinities w/ same sign (not a unique case)
    //return 0 if for either, exp = 11111111 and frac ≠ 0...000 (NaN)

    if(expf == expg)
    {
        if(expf == 0x7F800000 && (fracf && fracg))
            return 0; //NaN

        if(!(expf || fracf || fracg))
            return 1; //+0,-0
    }
    return uf == ug;
}
/*
 * floatScale4 - Return bit-level equivalent of expression 4*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale4(unsigned uf) {
    //printf("**** uf = %x ****\n", uf);
    //single precision: 1 sign bit, 8 exp bits, 23 fraction bits

    int s = uf & 0x80000000,
        exp = uf & 0x7F800000,
        frac = uf & 0x007FFFFF;
    unsigned int R,  //round bit: 1st bit removed
    //             X,  //sticky: OR of other bits
                 G;  //guard bit: LSB of result

    if(exp == 0x7F800000) return uf; //special: NaN and infinities
    if(exp == 0)
    {
        if(frac == 0) return uf; //denormalized: +0/-0
        //else if(frac == 0x00200000)
        //{
        //    return s + 0x00800000;
        //}
        else if (frac >= 0x00200000) //in the range (0.25, 1)
        {

            G = (uf & 0x00400000) >> 22;
            R = (uf & 0x00200000) >> 21;
            //X = (uf & 0x007FFFFF) == 0;
            frac = (uf<<(2-G)) & 0x007FFFFF;

            //if G = 0 and R = 0, <<2 and exp+=0
            //if G = 0 and R = 1, <<2 and exp+=1
            //if G = 1 and R = 0, <<1 and exp+=2
            //if G = 1 and R = 1, <<1 and exp+=2

            if (G) exp += 0x01000000;
            else if(R) exp += 0x00800000;

            //printf("G = %d\nR = %d\n", G, R);
        }
        else frac = frac<<2;
    }
    else //assuming normalized...
    {
        exp = exp + 0x01000000; //increase exp by 2, so quadruples number
        if((exp & 0x7F800000) == 0) exp = 0x7F800000; //cap at 11111111
        if(exp == 0x7F800000)       frac = 0;         //???
    }
    //printf("s = %x\n", s);
    //printf("exp = %x\n", exp);
    //printf("frac = %x\n", frac);
    return s | exp | frac;
}
/*
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatUnsigned2Float(unsigned u) {
    //printf("***u = %ud***\n", u);
    // Normal Case:
    //      000001abcdefghij...b = 1.abcdefghij... * 2^(31 - # of zeroes)
    //      s = 0 (since u is unsigned)
    //      M = 1.abcdefghij...
    //      frac = abcdefghij...
    //      E = 31 - # of zeros
    //      exp = E + 127
    //      form: 0(exp)(frac)
    // Special Case: cannot occur
    // Denormalized: return 0
    unsigned int n = 0,     //place of bit after most leftmost 1 (LSB = 1)
                 nMin24,    //simply n - 24
                 frac = u,  //fractional part
                 //exp = 127; //exp = E + 127
                 exp = 0x3F800000;
    unsigned int R,         //round bit: 1st bit removed
                 X,         //sticky: OR of other bits
                 G;         //guard bit: LSB of result
    if(u==0) return 0;

    //while((frac>=2) & (exp<255) & (n<32))
    while((frac>=2) & (n<32))
    {
        frac = frac>>1;
        //exp++; //caps at exp = 255, but n will be reach cap first
        exp = exp + 0x00800000;
        n++; //caps at 32
    }

    if(n>=23)
    {
        nMin24 = n - 24;
        frac = (u>>(n-23)) & 0x007FFFFF; //leave as remainder
        G = frac & 1; //guard bit: LSB of result
        R = (u>>nMin24) & 1; //round bit: 1st bit removed
        X = (u & ((1<<nMin24) - 1)); //sticky: OR of other bits
        //get last (n-24) bits, equal to 32 - (n-24) = 56 - n shift left

        //printf("G = %d, R = %d, X = %d\n", R, X, G);

        //round up if necessary!
        if( (R && X) | (G && R && !X) )
            frac++;
        //if(frac == 0x00800000) exp++;
        if(frac == 0x00800000) exp = exp + 0x00800000;
    }
    else frac = u<<(23-n);

    frac = frac & 0x007FFFFF;

    //printf("n = %d\nexp = %d\nfrac = %d\n", n, exp, frac);

    //return (exp<<23) | frac;
    return exp | frac;
}
