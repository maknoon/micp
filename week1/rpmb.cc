/* rpmb.cc
 * author: connie
 *
 * REVERSE PARSE MULTI-BYTE
 *
 */

// TODO: these includes don't seem to be working in new environment rn
//       get rid of all the std:: at some point when I figure this out
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>

//== DECLARATIONS
int NumChars(char* begin, char* end);


//== DEFINITIONS
#define MASK    0x80
#define SHIFT   7
#define JAPN    2
#define ENGL    1
#define MALF    0

//== FUNCTIONS
int NumChars(char* begin, char* end)
{
  // we always need to check the previous char as well
  // so find the previous by iterating to it
  char* c = end;
  char* prev = begin;
  while (*prev != end) prev++;

  // CASE 1: HIGH BIT IS HIGH
  if ((c & MASK) >> SHIFT) {
    if ((prev & MASK) >> SHIFT) return JAPN;
    else return MALF;
  }

  // CASE 2: HIGH BIT IS LOW
  else {
    if ((prev & MASK) >> SHIFT) return JAPN;
    else return ENGLISH;
  }

  // should never reach this point
  return MALF;
}

/*
 * for testing purposes
 */
void tests(void) {
  // test case 1: malformed
  // test case 2: "english"
  // test case 3: "にほんご"
}


int main(void)
{
  char* input; int type = 0;
  std::cout << "Enter a string to test: ";
  std::cin >> input;

  type = NumChars(input[0], input[sizeof(input)-1]);
  std::cout << "Last character of string is: " << type << std::endl;

  return 0;
}
