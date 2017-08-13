/* wordbreak.cc
 * author: connie
 *
 * WORD BREAK
 * Given an input string and a dictionary of words,
 * find out if the input string can be segmented into a
 * space-separated sequence of dictionary words.
 *
 */
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>

using namespace std;

//== DECLARATIONS
bool wordInDict(string& word, vector<string>& dict);
bool wordBreak_BF(string& s, vector<string>& dict);

//== DEFINITIONS
//#define DEBUG

//== FUNCTIONS
/*
 * bool wordInDict(string& word, vector<string>& dict)
 * inputs: word - word to check
           dict - the dictionary (array of strings) with valid words
 * outputs: True for valid dictionary word, False for invalid word
 * notes: helper function for iterating thru the array
 */
bool wordInDict(string& word, vector<string>& dict)
{
  if (word.size() == 0) return false;

  // iterate thru dictionary to check if the word is valid
  for (string dictword : dict) {
#ifdef DEBUG
    cout << word << " ?= " << dictword << endl;
#endif
    if (word.compare(dictword) == 0) return true;
  }

  return false;
}

/*
 * bool wordBreak_BF(string& s, vector<string>& dict)
 * inputs: s - the string to check for a valid "word break"
           dict - the dictionary (array of strings) with valid words
 * outputs: True for valid word break, False for invalid word break
 * notes: the brute force solution implementation - runs in O(n x m), where
          n = size of string and m = size of dict
 */
bool wordBreak_BF(string& s, vector<string>& dict)
{
  // handle empty cases
  if (s.size() == 0 || dict.size() == 0) return false;

  // word breaks aren't case sensitive
  for (int c = 0; c < s.size(); c++) {
    s[c] = tolower(s[c]);
  }

  // helper vars for iterating thru s
  string word = "";
  int i = 0;

  // iterate thru the string looking for words
  while (i < s.size()) {
    // build the word starting with each letter in the string
    word += s[i];

    // if word is valid dictionary word, trim s & reset the word
    if (wordInDict(word, dict)) {
      s.erase(0,word.size()); // *WORD BREAK*
      word.clear();
      i = 0; // start from the beginning of the string
    }
    else {
      i++;
      // if we've reached the end of the string without a match, we're done
      if (i == s.size()) return false;
    }
  }

  return true;
}


void test() {
  // TEST 1 - empty case
  cout << "TEST 1 - EMPTY" << endl;
  string s1 = "";
  vector<string> dict1 = {};
  assert(wordBreak_BF(s1,dict1)==false);
  cout << "test passed" << endl;

  // TEST 2 - valid word break
  cout << "TEST 2 - EXAMPLE youenjoy" << endl;
  string s2 = "youenjoy";
  vector<string> dict2 =  {"pear","salmon","foot","prints","footprints","leave","you","sun","girl","enjoy"};
  assert(wordBreak_BF(s2,dict2)==true);
  cout << "test passed" << endl;

  // TEST 3 - invalid word break
  cout << "TEST 3 - EXAMPLE salmonenjoyapples" << endl;
  string s3 = "salmonenjoyapples";
  assert(wordBreak_BF(s3,dict2)==false);
  cout << "test passed" << endl;

  // TEST 4 - valid word break with capitals
  cout << "TEST 4 - EXAMPLE YouEnjoy" << endl;
  string s4 = "YouEnjoy";
  assert(wordBreak_BF(s4,dict2)==true);
  cout << "test passed" << endl;

  // TEST 5 - valid word break with dual words
  cout << "TEST 5 - EXAMPLE youleavefootprints" << endl;
  string s5 = "youleavefootprints";
  assert(wordBreak_BF(s5,dict2)==true);
  cout << "test passed" << endl;
}

int main(int argc, char const *argv[]) {
  test();
  return 0;
}
