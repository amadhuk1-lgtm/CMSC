//Title: Scytale.h
//Author: Jeremy Dixon
//Date: 4/1/2025
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC

#ifndef SCYTALE_H
#define SCYTALE_H
#include "Cipher.h"
#include <istream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Scytale : public Cipher {
public:
  // Name: Scytale (Default Constructor)
  // Desc: Constructor to build an empty Scytale Cipher
  // Preconditions - None
  // Postconditions - Creates a Scytale cipher
  Scytale();
  // Name: Scytale (Overloaded Constructor)
  // Desc: Constructor to build a populated Scytale Cipher
  // Preconditions - Pass it the message, isEncrypted, and key (integer)
  // Postconditions - Creates a Scytale cipher to be encrypted
  Scytale(string, bool, int);
  // Name: Scytale (Destructor)
  // Desc: Destructor - Anything specific part of Scytale to delete?
  // Preconditions - ~Scytale exists
  // Postconditions - Scytale destroyed
  ~Scytale();
  // Name: Encrypt
  // Desc: Letters are placed on a fence rail based on the number of rails
  //       Letters are read from one rail at a time into a single string
  // Preconditions - Message exists
  // Postconditions - A single encrypted string is stored
  void Encrypt();
  // Name: Decrypt
  // Desc: Single encrypted string is pushed back on the rails and reversed
  // Preconditions - Message exists
  // Postconditions - The decrypted string is stored
  void Decrypt();
  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Scytale in this case)
  string ToString();
  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - r, delimiter, isencrypted, delimiter,
  //                  message, delimiter, key are returned for output
  string FormatOutput();
private:
  int m_key; //Number of columns (determines transposition)
};


#endif
