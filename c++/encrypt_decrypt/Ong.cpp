//*****************************************************************************************
//File:     Ong.cpp
//Project:  CMSC 202 Project 4, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     04/14/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to add -ong after every consonant.
//*****************************************************************************************

#include "Ong.h"

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates an Ong cipher to be encrypted
Ong::Ong(): Cipher() {
}

// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates an Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted): Cipher(message, isEncrypted) {
}

// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong() {
}

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char c) {
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U') {//to check if it is a vowel
        return true;
    } else {
        return false;
    }
}
// Name: IsPunct (Helper function)
// Desc: Returns true if punctuation or space
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsPunct(char c) {
    if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?' ||
        c == '(' || c == ')' || c == ':' || c == ';' || c == '\'' || c == '\"') {//to check if it is a punctuation
        return true;
    } else {
        return false;
    }
}

// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt() {
    if (GetIsEncrypted()) {
        cout << "The text has already been encrypted." << endl;
        return; //So that it does not encrypt if already encrypted
    } else {
        string newMessage = "";//empty string
        for (unsigned int i = 0; i < GetMessage().length(); i++) {//loop through the message
            char letter = GetMessage()[i];
            char nextLetter = GetMessage()[i+1];
            if (IsPunct(letter)) {
                newMessage += letter; // to keep punctuation as it is
            } else if (IsVowel(letter)) {
                newMessage += letter; //if vowel keep letter as it is
                if(IsPunct(nextLetter)){//check if next letter is a punctuation then to just print the letter
                   newMessage += ""; 
                } else{
                    newMessage += "-"; //to add a dash if it has no punctuation after
                }
            } else {
                newMessage += letter;
                newMessage += ong; // to add ong- after consonants
                if(IsPunct(nextLetter)){
                   newMessage += ""; 
                } else{
                    newMessage += "-"; // Add a dash after vowels
                }
            }
        }

        SetMessage(newMessage);  // Use the setter from Cipher
        ToggleEncrypted();
    }
}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt() {
    if (!GetIsEncrypted()) {
        cout << "The text has already been decrypted." << endl;
        return; // To check if it is already decrypted so it does not decrypt twice.
    }
    string newMessage = "";
    unsigned int i = 0;

    while (i < GetMessage().length()) {
        char letter = GetMessage()[i];
        char nextLetter = GetMessage()[i+1];
        if (IsPunct(letter)) {
            newMessage += letter; // to keep punctuation or spaces
            if(nextLetter == '-'){//to avoid printing '-' after punctuation in decrypting
                i += 1;
            } else{
                i+=0;
            }
            i++;//to keep moving on

        } else if (IsVowel(letter)) {//to check if vowel
            newMessage += letter;
            if (i + 1 < GetMessage().length() && GetMessage()[i + 1] == '-') {
                i += 2; // to skip the dash after a vowel
            } else {
                i++;
            }
        } else { //to check if it is a consonant
            newMessage += letter;
            if (i + 4 < GetMessage().length() &&
                GetMessage()[i + 1] == ong[0] &&
                GetMessage()[i + 2] == ong[1] &&
                GetMessage()[i + 3] == ong[2]) {
                if(GetMessage()[i + 4] == '-'){
                    i += 5; // to skip over "ong-"
                } else{
                    i += 4; //else to skip over just "ong"
                }
            }else {
                i++;
            }
        }
    }

    SetMessage(newMessage);  //to set the message decrypted
    ToggleEncrypted();  //to change the state of encryption
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString() {
    return "Ong";
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput() {
    stringstream formatMessage;
    formatMessage << 'o' << DELIMITER << GetIsEncrypted() << DELIMITER  << GetMessage() << DELIMITER;//to print the formatted message
    return formatMessage.str();//to return the formatted output
}
