/* caesar.cc
 * author: connie
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
int parse(std::string cipher, int &shift, std::string &plaintext);
std::string encrypt(int &shift, std::string &plaintext);
void caesar(std::string cipher);

//== DEFINITIONS
//#define DEBUG
#define KEYMIN      -1000000000
#define KEYMAX      1000000000
#define TXTMAX      200
#define ALPHA_MOD   26
#define NUM_MOD     10
#define UALPHA_LEN  0x1a
#define LALPHA_LEN  0x19

// don't really need these
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
int parse(std::string cipher, int &shift, std::string &plaintext)
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
std::string encrypt(int &shift, std::string &plaintext)
{
  std::string ciphertext = "";
  int alpha_shift = shift % ALPHA_MOD;
  int num_shift = shift % NUM_MOD;
  char cipher_c;

  std::cout << "a_shift, n_shift: " << alpha_shift << ", " << num_shift << std::endl;

  // encrypt based on the shift given
  // easy cuz we are in hex :D
  for (char c : plaintext) {
    cipher_c = c;

    // if c is a number
    if (c >= '0' && c <= '9') {
      cipher_c += num_shift;
      if (cipher_c > '9') cipher_c -= NUM_MOD;
      if (cipher_c < '0') cipher_c += NUM_MOD;
    }

    // if c is uppercase alphabet
    else if (c >= 'A' && c <= 'Z') {
      cipher_c += alpha_shift;
      if (cipher_c > 'Z') cipher_c -= UALPHA_LEN;
      if (cipher_c < 'A') cipher_c += UALPHA_LEN;
    }

    // if c is lowercase alphabet
    else if (c >= 'a' && c <= 'z') {
      cipher_c += alpha_shift;
      if (cipher_c > 'z') cipher_c -= LALPHA_LEN;
      if (cipher_c < 'a') cipher_c += LALPHA_LEN;
    }

#ifdef DEBUG
    std::cout << cipher_c << std::endl;
#endif
    // otherwise
    ciphertext += cipher_c;
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


/*
 * for testing purposes
 */
void tests(void) {
  std::cout << "TEST CASE 0: 1:some text" << std::endl;
  caesar("1:some text");
  std::cout << "" << std::endl;

  std::cout << "TEST CASE 1: 0:" << std::endl;
  caesar("0:");
  std::cout << "" << std::endl;

  std::cout << "TEST CASE 2: 55:helllo wORDLD!!!" << std::endl;
  caesar("55:helllo wORDLD!!!");
  std::cout << "" << std::endl;

  std::cout << "TEST CASE 3: -1000000001:no" << std::endl;
  caesar("-1000000001:no");
  std::cout << "" << std::endl;

  std::cout << "TEST CASE 4: " << std::endl;
  caesar("");
  std::cout << "" << std::endl;
}



int main(int argc, char *argv[]) {
  if (argc > 1) tests();

  else {
    std::string input;
    std::cout << "Enter input cipher:" << std::endl;
    std::getline(std::cin,input);
    caesar(input);
  }

  return 0;
}
