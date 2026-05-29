//*****************************************************************************************
//File:     Atbash.cpp
//Project:  CMSC 202 Project 4, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     04/14/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to encrypt and decrypt messages.
//*****************************************************************************************
#include "Atbash.h"

// Name: Atbash (Default Constructor)
// Desc: Constructor to build an empty Atbash Cipher
// Preconditions - None
// Postconditions - Creates an Atbash cipher to be encrypted
Atbash::Atbash() : Cipher() {
}

// Name: Atbash (Overloaded Constructor)
// Desc: Constructor to build a populated Atbash Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates an Atbash cipher to be encrypted
Atbash::Atbash(string message, bool isEncrypted) : Cipher(message, isEncrypted) {
}

// Name: Atbash (Destructor)
// Desc: Destructor - Anything specific to Atbash to delete?
// Preconditions - ~Atbash exists
// Postconditions - Atbash destroyed
Atbash::~Atbash() {
}

// Name: Encrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Encrypt() {
    if (GetIsEncrypted()) {
        cout << "The text has already been encrypted." << endl;
        return; // Already encrypted, no need to encrypt again so get out of the function
    }

    string newMessage = "";//create an empty string

    for (unsigned int i = 0; i < GetMessage().length(); i++) {//go through the message
        char letter = GetMessage()[i];//variable to store the character

        if (isalpha(letter)) {//if alphabet
            if (isupper(letter)) {// if letter is uppercase
                newMessage += (char)('A' + ('Z' - letter));//to reverse letter
            } 
            else if (islower(letter)) { // if letter is lowercase
                newMessage += (char)('a' + ('z' - letter));//to reverse letter
            }
        } else {
            newMessage += letter;//if punctuation or space keep the same
        }
    }

    SetMessage(newMessage); //set the message
    ToggleEncrypted();      //change condition of text
}

// Name: Decrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Decrypt() {
    if (!GetIsEncrypted()) {
        cout << "The text has already been decrypted." << endl;
        return; // it's already decrypted to get out of function
    }

    string newMessage = "";

    for (unsigned int i = 0; i < GetMessage().length(); i++) {//go through the message
        char letter = GetMessage()[i];//to get each character of message

        if (isalpha(letter)) { // if alphabet
            if (isupper(letter)) { // if letter is uppercase
                newMessage += (char)('A' + ('Z' - letter));//reverse letter
            }
            else if (islower(letter)) { //if letter is lowercase
                newMessage += (char)('a' + ('z' - letter));
            }
        } else {
            newMessage += letter; //if punctuation or space keep the same
        }
    }

    SetMessage(newMessage); 
    ToggleEncrypted();      //to change encryption state
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Atbash in this case)
string Atbash::ToString() {
    return "Atbash";
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter are returned for output
string Atbash::FormatOutput() {
    stringstream formatMessage;
    formatMessage << 'a' << DELIMITER << GetIsEncrypted() << DELIMITER  << GetMessage() << DELIMITER ;//to print the formatted message
    return formatMessage.str();//to return the formatted message
}



