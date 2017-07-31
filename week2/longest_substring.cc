/* longest_substring.cc
 * author: connie
 *
 * LONGEST SUBSTRING W/O REPEATING CHARACTERS
 * URL:
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 */

// TODO: these includes don't seem to be working in new environment rn
//       get rid of all the std:: at some point when I figure this out
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

//== DECLARATIONS
int greatest_substr(std::string str);

//== DEFINITIONS
//#define DEBUG

//== FUNCTIONS
/*
 * int longest_substr(string str)
 * input: str - the string to evaluate
 * output: int - size of the greatest substring with no repeated chars of str
 * notes: this is the main implementation
 */
 int longest_substr(std::string str)
 {
   // null exception
   if (str == "") return -1;
   // optimize. don't iterate if size is already 1
   if (str.size() == 1) return 1;

   // we want to track our current greatest substring as we iterate
   int start = 0; int end;
   int max = 0;
   // assume that the charset is limited size of ASCII charset
   int charset[128] = {0};

   // iterate thru the string accordingly to find the greatest substring
   for (end = 0; end < str.size(); end++)
   {
#ifdef DEBUG
     std::string greatest_substr = str.substr(start,end);
     std::cout << greatest_substr << std::endl;
#endif
     // go to the next biggest nonrepeating substring in str
     start = std::max(charset[str[end]], start);
     max = std::max(max, end-start+1); // update max if it's smaller by the length of
                                       // str.substr(end,start) aka end-start+1
     charset[str[end]] = end + 1; // update the charset of positions with the end + 1
   }

   // return length of the established greatest substring with nonrepeating chars
   return max;
 }

/*
 * for testing purposes
 */
void tests(void) {
  std::cout << "TEST CASE 0: null == -1" << std::endl;
  assert(longest_substr("")==-1);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 1: z == 1" << std::endl;
  assert(longest_substr("z")==1);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 2: zzzzz == 1" << std::endl;
  assert(longest_substr("zzzzz")==1);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 3: zzZzz == 2" << std::endl;
  assert(longest_substr("zzZzz")==2);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 4: abcabca == 3" << std::endl;
  assert(longest_substr("abcabca")==3);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 5: pwwkew == 3" << std::endl;
  assert(longest_substr("pwwkew")==3);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 6: 5655%0as%L == 5" << std::endl;
  assert(longest_substr("5655%0as%L")==5);
  std::cout << "test passed" << std::endl;

  std::cout << "TEST CASE 7: 123!456 == 7" << std::endl;
  assert(longest_substr("123!456")==7);
  std::cout << "test passed" << std::endl;
}


int main(int argc, char *argv[]) {
  if (argc > 1) tests();

  else {
    std::string input;
    std::cout << "Enter input string: ";
    std::getline(std::cin,input);

    std::cout << "Length of greatest substring: " << longest_substr(input) << std::endl;
  }

  return 0;
}
