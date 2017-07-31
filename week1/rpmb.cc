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
#define MASK    0x80  // 0x80 = b10000000
#define SHIFT   7     // shift 7 bits to the highest bit in a byte
#define JAPN    2
#define ENGL    1
#define MALF    0

//== FUNCTIONS
int NumChars(char* begin, char* end)
{
  // the last byte in the string should be where end points to
  // find the previous byte by iterating to it from begin
  char c = end[0];
  char prev = begin[0];
  for (int i = 0; prev != *end; i++) prev = begin[i];

  // CASE 1: HIGH BIT IS HIGH
  // a) 1,1 = Japanese
  // b) 0,1 = malformed
  if ((c & MASK) >> SHIFT) {
    if ((prev & MASK) >> SHIFT) return JAPN;
    else return MALF;
  }

  // CASE 2: HIGH BIT IS LOW
  // a) 1,0 = Japanese
  // b) 0,0 = English
  else {
    if ((prev & MASK) >> SHIFT) return JAPN;
    else return ENGL;
  }

  // should never reach this point, but just in case
  return MALF;
}

/*
 * for testing purposes
 */
void tests(void) {
  // TODO implement cassert library with this
  int result = 0;
  // test case 1: malformed -- not sure how to test

  // test case 2: "english"
  std::string c2 = "english";
  std::cout << "testing: english" << std::endl;
  result = NumChars(&(c2[0]), &(c2[c2.size()-1]));
  std::cout << "Last character is: " << result << std::endl;

  // test case 3: "にほんご"
  std::string c3 = "にほんご";
  std::cout << "testing: にほんご" << std::endl;
  result = NumChars(&(c3[0]), &(c3[c3.size()-1]));
  std::cout << "Last character is: " << result << std::endl;
}


int main(int argc, char *argv[])
{
  if (argc > 1) tests();

  else {
    std::string input; int type = 0;
    std::cout << "Enter a string to test: ";
    std::cin >> input;
    //std::cout << "size of input: " << input.size() << std::endl;
    type = NumChars(&(input[0]), &(input[input.size()-1]));
    std::cout << "Last character of string is: " << type << std::endl;
  }

  return 0;
}
