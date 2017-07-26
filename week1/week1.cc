/*
 *
 * CAESAR CIPHER
 * simple caesar cipher encryption program.
 * program is self-contained, so no header file was included.
 *
 */
// TODO: these includes don't seem to be working in new environment rn
//       get rid of all the std:: at some point when I figure this out
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

//== DECLARATIONS
int parse(std::string cipher, int shift, std::string plaintext);
std::string encrypt(int shift, std::string plaintext);
void caesar(std::string cipher);

//== DEFINITIONS
#define DEBUG
#define KEYMIN      -1000000000
#define KEYMAX      1000000000
#define TXTMAX      200
#define ALPHA_MOD   26
#define NUM_MOD     10
#define START_ULPHA 0x41        // hex value of 'A'
#define START_LLPHA 0x61        // hex value of 'a'
#define START_NUM   0x30        // hex value of '0'

//== FUNCTIONS

/*
 * int parse(string cipher, int shift, string plaintext)
 * inputs: string cipher - raw input from commandline
           int shift - parsed caesar cipher key
           string plaintext - parsed message to be encrypted
 * returns: int error. 1 = error, 0 = no error
 * notes: main function for executing the caesar cipher encryption
 */
int parse(std::string cipher, int shift, std::string plaintext)
{
  // find the colon position first
  int colon = cipher.find_first_of(":");
#ifdef DEBUG
  std::cout << "colon position: " << colon << std::endl;
#endif
  // -> error if not found
  if (colon == -1) return 1;

  // parse next for key & for the plaintext
  std::string key = cipher.substr(0,colon);
  shift = atoi(key.c_str());
  plaintext = cipher.substr(colon+1,cipher.size()-colon);
#ifdef DEBUG
  std::cout << "key: " << shift << std::endl;
  std::cout << "plaintext: " << plaintext << std::endl;
#endif
  // -> error if boundary conditions not met
  if (shift < KEYMIN || shift > KEYMAX || plaintext.size() > TXTMAX) return 1;

  return 0;
}

/*
 * string encrypt(int shift, string plaintext)
 * inputs: int shift - the caesar cipher key; i.e. number of shifts
           string plaintext - the plaintext parsed from the raw input
 * returns: string of encrypted text (ciphertext)
 * notes: encryption helper function
 */
std::string encrypt(int shift, std::string plaintext)
{
  std::string ciphertext = "";
  int alpha_mod = shift % ALPHA_MOD;
  int num_mod = shift % NUM_MOD;

  // encrypt based on the shift given
  // easy cuz we are in hex :D
  for (char c : plaintext) {
    // if c is a number
    if (c >= '0' && c <= '9') // case 1
    // if c is alphabet
    else if (c >= 'A' && c <= 'Z') // case 2
    else if (c >= 'a' && c <= 'z') // case 3

    // otherwise
    ciphertext += c;
  }

  return ciphertext;
}

/*
 * void caesar(string cipher)
 * inputs: string cipher - raw input from commandline
 * returns: none
 * notes: main function for executing the caesar cipher encryption
 */
void caesar(std::string cipher)
{
  int shift = 0;
  std::string plaintext = "";

  // get all the error checking out of the way first
  int error = parse(cipher, shift, plaintext);
  if (error == 1) {
    std::cout << "bad input!" << std::endl;
    return;
  }

  // if we made it here then we have something encryptable!
  std::string ciphertext = encrypt(shift, plaintext);
  std::cout << "ciphertext: " << ciphertext << std::endl;

  return;
}



int main(void) {
  std::string input;
  std::cout << "Enter input cipher:" << std::endl;
  std::cin >> input;
  caesar(input);

  return 0;
}
