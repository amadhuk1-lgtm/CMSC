//Title: Atbash.h
//Author: Jeremy Dixon
//Date: 4/1/2025
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC
#ifndef ATBASH_H
#define ATBASH_H
#include "Cipher.h"
#include <string>
using namespace std;

class Atbash: public Cipher {
 public:
  // Name: Atbash (Default Constructor)
  // Desc: Constructor to build an empty Atbash Cipher
  // Preconditions - None
  // Postconditions - Creates a Atbash cipher to be encrypted
  Atbash();
  // Name: Atbash (Overloaded Constructor)
  // Desc: Constructor to build a populated Atbash Cipher
  // Preconditions - Pass it the message and isEncrypted
  // Postconditions - Creates a Atbash cipher to be encrypted
  Atbash(string, bool);
  // Name: Atbash (Destructor)
  // Desc: Destructor - Anything specific to Atbash to delete?
  // Preconditions - ~Atbash exists
  // Postconditions - Atbash destroyed
  ~Atbash();
  // Name: Encrypt
  // Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
  // Preconditions - Message exists
  // Postconditions - Reverses the characters. Ignores punctuation.
  void Encrypt();
  // Name: Decrypt
  // Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
  // Preconditions - Message exists
  // Postconditions - Reverses the characters. Ignores punctuation.
  void Decrypt();
  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Atbash in this case)
  string ToString();
  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - c, delimiter, isencrypted, delimiter,
  //                  message, delimiter are returned for output
  string FormatOutput();
};

#endif
