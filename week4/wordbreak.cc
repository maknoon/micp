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
#include <set>

using namespace std;

//== DECLARATIONS
bool wordInDict(string word, vector<string>& dict);
bool wordBreak_RC(string s, vector<string>& dict);
bool wordBreak_DP(string s, vector<string>& dict);

//== DEFINITIONS
//#define DEBUG

//== FUNCTIONS
/*
 * bool wordInDict(string word, vector<string>& dict)
 * inputs: word - word to check
           dict - the dictionary (array of strings) with valid words
 * outputs: True for valid dictionary word, False for invalid word
 * notes: helper function for iterating thru the array
 */
bool wordInDict(string word, vector<string>& dict)
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
 * bool wordBreak_DP(string s, vector<string>& dict)
 * inputs: s - the string to check for a valid "word break"
           dict - the dictionary (array of strings) with valid words
 * outputs: True for valid word break, False for invalid word break
 * notes: the DP implementation that verifies progressive substrings
 */
 bool wordBreak_DP(string s, vector<string>& dict) {
   // we can "memoize" words that are part of compound words in dict
   int slen = s.size();
   set<string> compounds;

   // iterate through string from s(0,1) until the last substring
   for (int i = 0; i < slen; i++) {

     // our current word is already stored in the table
     if (compounds.find(s.substr(0,i)) != compounds.end()) {
       if (i == slen) return true; // end of string & valid word = we are done

       // keep trying to see if next part of string is in compound word
       for (int j = i+1; j < slen; j++) {
         // end of string AND the next part of the string is compound
         if (j == slen && compounds.find(s.substr(i,j)) != compounds.end()) return true;

         // not end of string BUT the string is a word in the dictionary
         // add it to our set of valid compounds
        if (
          compounds.find(s.substr(i,j)) == compounds.end() && wordInDict(s.substr(i,j),dict)
        ) compounds.insert(s.substr(i,j));
       }
     }

     // if our current word is not a compound BUT is a word in the dictionary
     // add it to our set of valid compounds
     else if (wordInDict(s.substr(0,i),dict)) compounds.insert(s.substr(0,i));
   }

   // if we reach this point then there are still parts of string not in dict
   return false;
 }

/*
 * bool wordBreak_RC(string s, vector<string>& dict)
 * inputs: s - the string to check for a valid "word break"
           dict - the dictionary (array of strings) with valid words
 * outputs: True for valid word break, False for invalid word break
 * notes: the recursive implementation that verifies progressive substrings
 */
bool wordBreak_RC(string s, vector<string>& dict)
{
  // base case: if nothing is remaining then we are done
  if (s.size() == 0) return true;

  // iterate through the string from s(0,1) - i.e. the first substring
  for (int i = 1; i <= s.size(); i++) {

    // if substring that we are looking at is in dict, check if next part of
    // the string is also in the dict (either as word or as compound word)
    // by recursing on the remainder of the string
    if (
      wordInDict(s.substr(0,i),dict) && wordBreak_RC(s.substr(i,s.size()-i),dict)
    ) return true;
  }

  // if we reach this point then there are still parts of string not in dict
  return false;
}

/** main function for recursion **/
bool wordBreak(string s, vector<string> dict)
{
  // handle empty cases
  if (s.size() == 0 || dict.size() == 0) return false;

  // word breaks aren't case sensitive
  for (int c = 0; c < s.size(); c++) {
    s[c] = tolower(s[c]);
  }

  return wordBreak_RC(s, dict);
}

void test() {
  // TEST 1 - empty case
  cout << "TEST 1 - EMPTY" << endl;
  string s1 = "";
  vector<string> dict1 = {};
  assert(wordBreak(s1,dict1)==false);
  cout << "test passed" << endl;

  // TEST 2 - valid word break
  cout << "TEST 2 - EXAMPLE youenjoy" << endl;
  string s2 = "youenjoy";
  vector<string> dict2 =  {"pear","salmon","foot","prints","footprints","leave","you","sun","girl","enjoy"};
  assert(wordBreak(s2,dict2)==true);
  cout << "test passed" << endl;

  // TEST 3 - invalid word break
  cout << "TEST 3 - EXAMPLE salmonenjoyapples" << endl;
  string s3 = "salmonenjoyapples";
  assert(wordBreak(s3,dict2)==false);
  cout << "test passed" << endl;

  // TEST 4 - valid word break with capitals
  cout << "TEST 4 - EXAMPLE YouEnjoy" << endl;
  string s4 = "YouEnjoy";
  assert(wordBreak(s4,dict2)==true);
  cout << "test passed" << endl;

  // TEST 5 - valid word break with compound words (beginning)
  vector<string> dict3 =  {"pear","salmon","foot","footprints","leave","you","sun","girl","enjoy"};
  cout << "TEST 5 - EXAMPLE youleavefootprints" << endl;
  string s5 = "youleavefootprints";
  assert(wordBreak(s5,dict3)==true);
  cout << "test passed" << endl;

  // TEST 6 - valid word break with compound words (ending)
  vector<string> dict4 =  {"pear","salmon","footprints","prints","leave","you","sun","girl","enjoy"};
  cout << "TEST 6 - EXAMPLE youleavefootprints" << endl;
  string s6 = "youleavefootprints";
  assert(wordBreak(s6,dict4)==true);
  cout << "test passed" << endl;
}

int main(int argc, char const *argv[]) {
  test();
  return 0;
}
