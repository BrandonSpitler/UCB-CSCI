/*
 * CS:APP Data Lab
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

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Team name: Replace with either:
      Your login ID if working as a one person team
      or, ID1+ID2 where ID1 is the login ID of the first team member
      and ID2 is the login ID of the second team member */
    "830382233",
   /* Student name 1: Replace with the full name of first team member */
   "Taylor Andrews",
   /* Login ID 1: Replace with the login ID of first team member */
   "830382233",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "",
   /* Login ID 2: Login ID of the second team member */
   ""
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
//
// 15 problems, 40 points
// 2 - rating 1
// 5 - rating 2
// 4 - rating 3
// 4 - rating 4


/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/* Shifting 1 by 31 bits yields the largest negative number
   and therefore the minimum value. */
  return 0x01<<31;
}



/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
/* Taking the bitwise complement of 0 yields -1. */
  return ~(0x00);
}


/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int evenBits(void) {
/* 0x55 is binary 01010101. It is shifted a multiple of 8 bits
   to reach the 32 bit size of the computer. The OR statements work
   to concatenate of the various bits. */
  return (0x55<<24) | (0x55<<16) | (0x55<<8) | 0x55;
}



/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
/* In order to build 2^n, 1 is left shifted n bits.
   Next, -1 is added to 2^n. The MSB of x AND this quantity ensures that
   the modification only occurs to negative numbers. Finally,
   x plus either 1 or 0 as is appropriate is shifted by n bits to
   divide. */
  return (x + (((0x01 << n) + ~0x00) & (x >> 31))) >> n;
}



/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
/* Using the fact that a number XOR itself is 0, take the bang of that
   to get 1 if equal and 0 if not equal. */
  return !(x ^ y);
}





/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/* To the get the negative of a Two's Complement binary number
   take the bitwise complement of it and add 1. */
  return ~x + 0x01;
}





/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/* Shifting n by 3 is the equivalent of multiplying n by 8.
   x is then shifted by either 0, 8, 16, or 24 bits and masked
   with 0xFF to extract the correct byte. */
  return (x >> (n << 3)) & 0xFF;
}




/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/* X is shifted 31 bits over to allow for the MSB to be tested
   to see whether it is a 1 (negative) in which case the bang
   operator will return 0.
   Using the bang operator twice on x in conjunction with the bitwise
   AND causes the test to return 0 in the case of 0. */
  return !!x & !(x >> 31);
}





/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
/* First, determine if x and y have the same sign. If they don't, xy-match
   will be a value of 0 and the function will return 1.
   After determining the sign of the sum of x and y, XOR this quantity
   with the sign of x (which equals the sign of y in any potential overflow case).
   If the sign of the sum is different than the sign of x the final AND will evaluate to
   non-zero which the bang operator will convert to 0. */
  int xy_match = ~((x >> 31) ^ (y >> 31));
  int xy_sign = (x + y) >> 31;

  return !(xy_match & ((x >> 31) ^ xy_sign));
}






/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/* The complemented XOR checks if x and y are the same sign.
   If they are the same sign and y is greater than x, the MSB of
   ~y + x will be 1.
   If x and y are the not the same sign then y is only greater
   than x if y is positive and x is negative.
   The double bang operator ensures that the greater than equivalence
   is flipped to less than or equal to.  */
  int same_sign = ~((x >> 31) ^ (y >> 31)) & ((~y + x) >> 31);

  return !!(same_sign | ((x >> 31) & ~(y >> 31)));
}






/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int logicalShift(int x, int n) {
/* This function masks the value of x arithmetically shifted n
   to create a logical shift.
   The final left shift of 1 accounts for the initial 1 used to
   create the mask. */
  return (x >> n) & (~( ((0x01 << 31) >> n) << 1 ));
}





/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4
 */
int leastBitPos(int x) {
/* First, convert x to its negative counterpart. When
   this conversion occurs the least significant 1 bit is
   the only bit in x that will remain the same. By taking the
   AND of x and -x this least significant 1 is the only thing
   that will return a 1. */
  return x & (~x + 1);
}




/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
/* An integer split in two and XOR itself will produce a
   resultant integer with equivalent bit parity. Taking the
   final 1 bit integer AND 1 ensures it returns 1 for odd number
   of zeros. */
  x = ( x >> 0x10 ) ^ x;
  x = ( x >> 0x08 ) ^ x;
  x = ( x >> 0x04 ) ^ x;
  x = ( x >> 0x02 ) ^ x;
  x = ( x >> 0x01 ) ^ x;
  return (x & 0x01);
}





/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
int isPower2(int x) {
/* First, check to make sure x is not 0. Then, check to make sure
   the MSB of x is not 1. If it is 1, x is negative and therefore not
   a power of two.
   x + ~0x00 yields only 1 zero if x is a power of 2. This quantity
   AND x, if x is a power of 2, will produce all zeros. Otherwise it will
   produce a non-zero quantity. */
  return !!x & !(x >> 31) & !(x & (x + ~0x00));
}





/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
/* ~x + 1 is equivalent to -x. -x OR x will always produce a leading
   one whether x is positive or negative to start, except in the case
   of 0. Complementing this quantity has the result of making the MSB
   of any non-zero x equal to 0. If x = 0 the MSB will be set to 1. Shifting
   extracts the MSB. The MSB AND 1 returns 1 for 0, and 0 for any non-zero. */
  return ((~(x | (~x + 0x01))) >> 31) & 0x01;
}
