/* atoi.cc
 * author: connie
 *
 * ATOI & ITOA
 * Easy atoi & itoa implementation using hex value manipulation.
 * NOT fully implemented, lots of test cases I have not accounted for
 * (See bottom in the tests section for details).
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
int atoi_dummy(int& the_atoi, std::string& input);
int itoa_dummy(std::string& the_itoa, int& the_atoi);

//== DEFINITIONS
// don't really need these
#define START_ULPHA 0x41        // hex value of 'A'
#define START_LLPHA 0x61        // hex value of 'a'
#define START_NUM   0x30        // hex value of '0'

//== FUNCTIONS
/* int atoi_dummy(int& the_atoi, std::string& input)
 * inputs: value to store atoi, input string taken from main function
 * returns: error // 0 if everything ok
 * notes: called it atoi_dummy to distinguish between the system atoi
 */
int atoi_dummy(int &the_atoi, std::string &input)
{
  // keep track of decimal position
  // also check if negative
  int decimal = input.size()-1; int posneg = 0;

  // negative indication MUST be first character in the input
  if (input.at(0) == '-') {
    posneg = 1; decimal -= 1;
    input = input.substr(1,input.size());
  }

  // now go thru the rest of the string and add accordingly
  // ex. "452" = 4 * 10^2 + 5 * 10^1 + 2 * 10^0
  for (char c : input) {
    // std::cout << "decimal spot: " << decimal << std::endl;
    if (c >= '0' && c <= '9') the_atoi += pow(10,decimal) * (c - '0');
    else return 1; // just break if it's an invalid char
    // std::cout << "atoi: " << the_atoi << std::endl;
    decimal -= 1;
  }

  if (posneg == 1) the_atoi *= -1;

  return 0;
}

/* int itoa_dummy(std::string& the_itoa, int& the_atoi)
 * inputs: string to store itoa, input int taken from main function
 * returns: error // 0 if everything ok
 * notes: called it itoa_dummy to distinguish between the system itoa
 */
int itoa_dummy(std::string& the_itoa, int& the_atoi)
{
  int posneg = 0;
  if (the_atoi < 0) { posneg = 1; the_atoi *= -1; }

  while (the_atoi) {
    // std::cout << the_atoi % 10 << std::endl;
    the_itoa.insert(0, 1, (the_atoi % 10) + '0');
    the_atoi /= 10;
  }

  if (posneg == 1) the_itoa.insert(0, 1, '-');

  return 0;
}


/*
 * for testing purposes
 */
void tests(void) {
  // TODO
  // generic tests: null, out of boundary, other characters, white space
  // other tests: 1234, 0239849028, 0.28, 0.028, 2.21
}


int main(int argc, char *argv[]) {
  if (argc > 1) tests();

  else {
    std::string input; int the_atoi = 0;
    std::cout << "Enter input string:" << std::endl;
    std::cin >> input;

    int error = atoi_dummy(the_atoi, input);
    if (error == 1) {
      std::cout << "bad input!" << std::endl;
      return 0;
    }
    std::cout << "atoi: " << the_atoi << std::endl;

    std::string the_itoa = "";
    error = itoa_dummy(the_itoa, the_atoi);
    std::cout << "itoa: " << the_itoa << std::endl;
  }

  return 0;
}
