/* atoi.cc
 * author: connie
 *
 * ATOI
 * Easy atoi implementation using hex value manipulation.
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
void atoi_dummy(int &the_atoi, std::string const& input);

//== DEFINITIONS
// don't really need these
#define START_ULPHA 0x41        // hex value of 'A'
#define START_LLPHA 0x61        // hex value of 'a'
#define START_NUM   0x30        // hex value of '0'

//== FUNCTIONS
int atoi_dummy(int &the_atoi, std::string &input)
{
  // keep track of decimal position
  int decimal = input.size()-1;

  for (char c : input) {
//    std::cout << "decimal spot: " << decimal << std::endl;
    // only take valid numbers
    if (c >= '0' && c <= '9') the_atoi += pow(10,decimal) * (c-'0');
    else return 1;
//    std::cout << "atoi: " << the_atoi << std::endl;
    decimal -= 1;
  }

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
  }

  return 0;
}
