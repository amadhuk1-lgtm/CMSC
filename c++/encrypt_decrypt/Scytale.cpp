//*****************************************************************************************
//File:     Scytale.cpp
//Project:  CMSC 202 Project 4, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     04/14/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to encrypt and decrypt.
//*****************************************************************************************

#include "Scytale.h"
#include <sstream>
// Name: Scytale (Default Constructor)
// Desc: Constructor to build an empty Scytale Cipher
// Preconditions - None
// Postconditions - Creates a Scytale cipher
Scytale::Scytale() : Cipher(){
    m_key = 0;

}
// Name: Scytale (Overloaded Constructor)
// Desc: Constructor to build a populated Scytale Cipher
// Preconditions - Pass it the message, isEncrypted, and key (integer)
// Postconditions - Creates a Scytale cipher to be encrypted
Scytale::Scytale(string message, bool isEncrypted, int key): Cipher(message, isEncrypted), m_key(key){
}


// Name: Scytale (Destructor)
// Desc: Destructor - Anything specific part of Scytale to delete?
// Preconditions - ~Scytale exists
// Postconditions - Scytale destroyed
Scytale::~Scytale(){
}

// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void Scytale::Encrypt(){
  const char EXTRA = 'X';
    if (GetIsEncrypted()) {
        cout << "The text has already been encrypted." << endl;
        return; // if already encrypted don't repeat
  }

  string message = GetMessage();//to get the message
  string newMessage = "";
  for (unsigned int i = 0; i < message.length(); i++) { // to go through each character of the message
        newMessage += message[i]; // to add each character to newMessage
        if (message[i] == ')') { // If a closing parenthesis add an 'X'
            newMessage += EXTRA;
        }
    }
  newMessage += EXTRA;// to add an 'X' to the end of the message
  while (newMessage.length() % m_key != 0) {
    newMessage += EXTRA;//to add 'X' until the message length is divisible by m_key
  }
  string nextMessage = "";
  int length = newMessage.length();
  int rows = (length + m_key - 1) / m_key; //to get number of rows ceiling

  for (int col = 0; col < m_key; col++) {//to go through the 2d array
    for (int row = 0; row < rows; row++) {
      int index = row * m_key + col;//to get the index in the original message
      if (index < length) {
        nextMessage += newMessage[index];//to add character to final encrypted message 
      }
    }
  }
  SetMessage(nextMessage);
  ToggleEncrypted(); // to change condition of message
}


// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void Scytale::Decrypt(){
  const char EXTRA = 'X';
    if (!GetIsEncrypted()) {
      cout << "The text has already been decrypted." << endl;
      return; // if already decrypted to not decrypt 
  }

  string message = GetMessage();//to get the message
  string newMessage(message.length(), ' ');// initializing a string of the same length as message

  int length = message.length();//to get length of message
  int rows = (length + m_key - 1) / m_key; // rounding up the no. of rows
  int index = 0;

  for (int col = 0; col < m_key; col++) {//to go through the 2d array
    for (int row = 0; row < rows; row++) { 
      int pos = row * m_key + col;//position in original message
      if (pos < length  && index < length) {//to check if position is valid
        newMessage[pos] = message[index];//placing the character
        index++;
      }
    }
  }
  string finalMessage = "";
  for (unsigned int i = 0; i < newMessage.length(); i++) {//to go through the message
    char ch = newMessage[i];
    if (ch != EXTRA) {//to remove the extra X's
        finalMessage += ch;
    }
  }
  SetMessage(finalMessage);
  ToggleEncrypted(); // to change condition of message
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Scytale in this case)
string Scytale::ToString(){
    return "Scytale";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, key are returned for output
string Scytale::FormatOutput(){
    stringstream formatMessage;
    formatMessage << 's' << DELIMITER << GetIsEncrypted() << DELIMITER  << GetMessage() << DELIMITER << m_key;//to print the formatted message
    return formatMessage.str();//to return the formatted message
}



