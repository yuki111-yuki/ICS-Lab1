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
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  return ((x ^ sign) + 1) & sign;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int byte = (x >> srcShift) & 0xff;
  int mask = 0xff << dstShift;
  return (x & ~mask) | (byte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0f | (0x0f << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int zeros = ~x;
  int first = zeros & (~zeros + 1);
  int rest = zeros ^ first;
  return rest & (~rest + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int shift = n & 31;
  int left = (32 + (~shift + 1)) & 31;
  int mask = ~(((1 << 31) >> shift) << 1);
  return ((x >> shift) & mask) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int mask = (1 << n) + ~0;
  int remainder = x & mask;
  int half = 1 << (n + ~0);
  int greater = ((half + (~remainder + 1)) >> 31) & 1;
  int equal = !(remainder ^ half);
  int increment = greater | (equal & ((x >> n) & 1));
  return (x + (increment << n)) & ~mask;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int common = x & y;
  int different = x ^ y;
  int average = common + (different >> 1);
  int xSign = x >> 31;
  int ySign = y >> 31;
  int difference = x + (~y + 1);
  int sameSign = ~(xSign ^ ySign);
  int greater = (((~xSign & ySign) |
                  (sameSign & !(difference >> 31))) & 1);
  return average + ((different & 1) & greater);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int d1 = a + (~x + 1);
  int s1 = a ^ x;
  int leAx = (((s1 & a) | (~s1 & d1)) >> 31) | !d1;
  int d2 = x + (~b + 1);
  int s2 = x ^ b;
  int leXb = (((s2 & x) | (~s2 & d2)) >> 31) | !d2;
  int d3 = b + (~x + 1);
  int s3 = b ^ x;
  int leBx = (((s3 & b) | (~s3 & d3)) >> 31) | !d3;
  int d4 = x + (~a + 1);
  int s4 = x ^ a;
  int leXa = (((s4 & x) | (~s4 & d4)) >> 31) | !d4;
  return ((leAx & leXb) | (leBx & leXa)) & 1;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int four = x << 2;
  int product = four + x;
  int recovered = four >> 2;
  int overflowFour = ((!!(recovered ^ x)) << 31) >> 31;
  int overflowAdd = ((four ^ product) & ~(four ^ x)) >> 31;
  int overflow = overflowFour | overflowAdd;
  int sign = x >> 31;
  int signBit = 1 << 31;
  int maxValue = ~signBit;
  int saturated = (sign & signBit) | (~sign & maxValue);
  return (overflow & saturated) | (~overflow & product);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int mask = (1 << 30) + ~0;
  int lowX = x & mask;
  int lowY = y & mask;
  int lowZ = z & mask;
  int highX = x >> 30;
  int highY = y >> 30;
  int highZ = z >> 30;
  int lowXY = lowX + lowY;
  int carryXY = lowXY >> 30;
  lowXY = lowXY & mask;
  int lowXYZ = lowXY + lowZ;
  int carryXYZ = lowXYZ >> 30;
  int carry = carryXY + carryXYZ;
  int high = highX + highY + highZ + carry;
  int positiveOverflow = (! (high >> 31)) & (!!(high >> 1));
  int negativeOverflow = ((high + 2) >> 31) & 1;
  return positiveOverflow | (~negativeOverflow + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exponent = (uf >> 23) & 0xffu;
  unsigned fraction = uf & 0x7fffffu;
  unsigned product;
  unsigned rounded;
  unsigned shift;
  unsigned remainder;
  unsigned half;
  unsigned mask;

  if (exponent == 0xffu)
    return uf;

  if (exponent == 0) {
    product = fraction * 3u;
    rounded = product >> 1;
    remainder = product & 1u;
    if (remainder && (rounded & 1u))
      rounded++;
    if (rounded >= 0x800000u)
      return sign | 0x00800000u | (rounded - 0x800000u);
    return sign | rounded;
  }

  product = (0x800000u | fraction) * 3u;
  shift = (product & 0x02000000u) ? 2u : 1u;
  exponent += shift - 1u;
  rounded = product >> shift;
  mask = (1u << shift) - 1u;
  remainder = product & mask;
  half = 1u << (shift - 1u);
  if (remainder > half || (remainder == half && (rounded & 1u)))
    rounded++;
  if (rounded == 0x1000000u) {
    rounded >>= 1;
    exponent++;
  }
  if (exponent >= 0xffu)
    return sign | 0x7f800000u;
  return sign | (exponent << 23) | (rounded - 0x800000u);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exponent = (uf >> 23) & 0xffu;
  unsigned fraction = uf & 0x7fffffu;
  unsigned mantissa;
  unsigned shift;
  unsigned mask;
  unsigned remainder;
  unsigned half;
  unsigned integral;

  if (exponent == 0xffu)
    return uf;
  if (exponent < 126u)
    return sign;
  if (exponent == 126u) {
    if (fraction == 0)
      return sign;
    return sign | 0x3f800000u;
  }
  if (exponent >= 150u)
    return uf;

  shift = 150u - exponent;
  mantissa = 0x800000u | fraction;
  mask = (1u << shift) - 1u;
  integral = mantissa >> shift;
  remainder = mantissa & mask;
  half = 1u << (shift - 1u);
  uf = uf & ~mask;
  if (remainder > half || (remainder == half && (integral & 1u)))
    uf += 1u << shift;
  return uf;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned ux = x;
  unsigned sign = 0;
  unsigned bit = 0x80000000u;
  int exponent = 31;
  unsigned mantissa;
  unsigned shift;
  unsigned remainder;
  unsigned half;

  if (x == 0)
    return 0;
  if (x < 0) {
    sign = 0x80000000u;
    ux = ~ux + 1u;
  }
  while (!(ux & bit)) {
    bit >>= 1;
    exponent--;
  }
  if (exponent <= 23) {
    mantissa = (ux << (23 - exponent)) & 0x7fffffu;
  } else {
    shift = exponent - 23;
    mantissa = ux >> shift;
    remainder = ux & ((1u << shift) - 1u);
    half = 1u << (shift - 1u);
    if (remainder > half || (remainder == half && (mantissa & 1u)))
      mantissa++;
    if (mantissa == 0x1000000u) {
      mantissa >>= 1;
      exponent++;
    }
    mantissa &= 0x7fffffu;
  }
  return sign | ((exponent + 127) << 23) | mantissa;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1 = 0x55 | (0x55 << 8);
  int mask2 = 0x33 | (0x33 << 8);
  int mask4 = 0x0f | (0x0f << 8);
  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask4 = mask4 | (mask4 << 16);
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask4) + ((x >> 4) & mask4);
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask4 = 0x0f | (0x0f << 8);
  mask4 = mask4 | (mask4 << 16);
  int mask2 = mask4 ^ (mask4 << 2);
  int mask1 = mask2 ^ (mask2 << 1);
  int mask8 = 0xff | (0xff << 16);
  int mask16 = 0xff | (0xff << 8);
  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);
  x = ((x >> 8) & mask8) | ((x & mask8) << 8);
  x = ((x >> 16) & mask16) | (x << 16);
  return x;
}
