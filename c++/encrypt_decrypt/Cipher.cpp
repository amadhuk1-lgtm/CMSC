//*****************************************************************************************
//File:     Cipher.cpp
//Project:  CMSC 202 Project 4, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     04/14/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user in encryption and decryption of a message
//*****************************************************************************************

#include "Cipher.h"

// Name: Cipher (Default Constructor)
// Desc - Stores a message and if it is encrypted (or not)
// Preconditions - None
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher(){
  m_message = "";
  m_isEncrypted = false;
}

// Name: Cipher (Overloaded Constructor)
// Desc - Passed a message and if it is encrypted (or not)
// Preconditions - A message is passed to this constructor, and if it is encrypted
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher(string message, bool isEncrypted){
  m_message = message;
  m_isEncrypted = isEncrypted;
}

// Name: ~Cipher (Destructor)
// Desc - Virtual destructor
// Preconditions - A derived class is being deleted
// Postconditions - A base class is deleted
Cipher::~Cipher(){
}

// Name: Decrypt
// Desc - A purely virtual function to decrypt a message
// Preconditions - The message is not already decrypted
// Postconditions - A message is decrypted based on the child class
void Cipher::Decrypt() {
}


// Name: Encrypt
// Desc - A purely virtual function to encrypt a message
// Preconditions - The message is not already encrypted
// Postconditions - A message is encrypted based on the child class
void Cipher::Encrypt() {
}

// Name: GetMessage
// Desc - Returns the message
// Preconditions - The message exists
// Postconditions - A message is returned
string Cipher::GetMessage(){
    return m_message;
}

// Name: GetIsEncrypted
// Desc - Returns isEncrypted (0 is not encrypted and 1 is encrypted)
// Preconditions - The cipher exists
// Postconditions - A bool is returned
bool Cipher::GetIsEncrypted(){
  return m_isEncrypted;
}

// Name: SetMessage
// Desc - Updates a message
// Preconditions - The message exists
// Postconditions - A message is updated
void Cipher::SetMessage(string message){
    m_message = message;//to update the message
}

// Name: ToggleEncrypted
// Desc - Turns (true to false) or (false to true)
// Preconditions - The cipher exists
// Postconditions - The m_isEncrypted is toggled
void Cipher::ToggleEncrypted(){
    m_isEncrypted = !m_isEncrypted;//to convert the condition of encryption anddecryption every time when changed.
}

// Name: ToString
// Desc - A purely virtual function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned
string Cipher::ToString() {
    return "";
}

// Name: FormatOutput
// Desc - A purely virtual function that returns the formatted data for Output
// Preconditions - The object exists
// Postconditions - The type, message, and key are output
string Cipher::FormatOutput() {
    return "";
}

// Name: Overloaded << Operator
// Desc - Outputs the message
// Preconditions - The object exists
// Postconditions - The message from the object is returned
ostream &operator<<(ostream &output, Cipher &C){
    string msg = C.GetMessage();
    return output << msg;//to return the message part of the loaded file only
}
