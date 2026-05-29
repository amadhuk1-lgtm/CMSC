//*****************************************************************************************
//File:     CipherTool.cpp
//Project:  CMSC 202 Project 4, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     04/14/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to encrypt and decrypt messages.
//*****************************************************************************************

#include "CipherTool.h"

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string filename){
    m_filename = filename;
}
// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool(){
    for(unsigned int i = 0; i < m_ciphers.size(); i++){//loops though the vector
        delete m_ciphers[i];//vector is emptied
        m_ciphers[i] = nullptr;
    }
}
// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (a is Atbash, s is Scytale, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
    ifstream inFile(m_filename);//opens inputed file
    string type;
    string tempisEncrypted;
    string message;
    string key;

    while (getline(inFile, type, DELIMITER)&&
        getline(inFile, tempisEncrypted, DELIMITER)&&
        getline(inFile, message, DELIMITER)&&
        getline(inFile,key, '\n')) {  //gets each info in the file

        bool isEncrypted = StringToBoolean(tempisEncrypted);//converts the data in the file to bool as we need true or false for 1 and 0
        
        if(type == "a"){
            Cipher* locate = new Atbash(message,isEncrypted);//calls atbash based on the data in file
             m_ciphers.push_back(locate);//adds the data/message to the vector
        }
        if(type == "s"){
            int keyInt = stoi(key);//to convert integer to string
            Cipher* locate = new Scytale(message,isEncrypted,keyInt);//calls Scytale based on the data in file
            m_ciphers.push_back(locate);//adds the data/message to the vector
        }
        if(type == "o"){
            Cipher* locate = new Ong(message,isEncrypted);//calls Ong based on the data in file
            m_ciphers.push_back(locate);//adds the data/message to the vector
        }
    }
    inFile.close();
}

// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input){
    bool isEncrypted;
    if(input == "0"){
        isEncrypted = false;//if 0 to return false
    }
    else{
        isEncrypted = true;//if anything other than 0 the false
    }
    return isEncrypted;
}
// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
    for(unsigned int i = 0; i < m_ciphers.size(); i++){//to loop thorugh each message in the vector to print one by one
        cout<< i+1 << ". " << m_ciphers[i]->GetMessage() << '('<< m_ciphers[i]->ToString() << ')' << '\n' << endl;//to display the message in a formatted way
    }
}

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool isEncrypted){
    int encryptCounter = 0;
    int decryptCounter = 0;
    for(unsigned int i = 0; i < m_ciphers.size(); i++){//to loop through the ciphers
        if(isEncrypted){
            if(!m_ciphers[i]->GetIsEncrypted()){//to check if it is already encrypted
                m_ciphers[i]->Encrypt();//if not then encrypt
                encryptCounter++;//to keep track of the number of ciphers encrypted
            }     
        }
        else{
            if(m_ciphers[i]->GetIsEncrypted()){//to check if it is encrypted
                m_ciphers[i]->Decrypt();//if it is then decrypt
                decryptCounter++;//to keep track of the number of ciphers dencrypted
            }      
        }
    }
    if(isEncrypted){
        cout << encryptCounter << " ciphers Encrypted"<< endl;//print after encryption
    } else{
        cout << decryptCounter << " ciphers Decrypted"<< endl;//print after decryption
    }
    
    
}
// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
    string newFileName;
    cout << "What would you like to call the export file? " << endl;//to ask the file name you want to upload the message output to
    cin >> newFileName;
    if (newFileName.find(".txt") == string::npos) {// To make sure that the file has a .txt at the end
        newFileName += ".txt";
    }
    ofstream outFile(newFileName);  // To open file

    if (!outFile) {//to just confirm if it opened or not
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (unsigned int i = 0; i < m_ciphers.size(); i++) {//to go through the vector and write the formatted output
        outFile << m_ciphers[i]->FormatOutput() << endl;
    }

    outFile.close();  //to close file
    cout << m_ciphers.size() << " ciphers exported" << endl;//to print the exporting happened
}


// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
    int choice;
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export All Ciphers" << endl;
        cout << "5. Quit" << endl;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {//checks if valid choice made and prints invalid if choice is not valid
            cout << "Invalid input. Please enter a valid value" << endl;
        }
    } while (choice < 1 || choice > 5 || cin.fail()); // keeps looping if invalid choice made

    return choice;
}
// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
    LoadFile();//loads in the file you iput when you run
    int choice;
    do{
        choice = Menu();//displays the menu and asks the choice of user
        switch(choice) {
        case 1:{
            DisplayCiphers();//to display the ciphers
            break;
        }
        case 2:{
            EncryptDecrypt(true);//to encrypt the ciphers
            break;
        }
        case 3:{
            EncryptDecrypt(false);//to decrypt the ciphers
            break;
        }
        case 4:{
            Export();//to export into a file
            break;
        }
        case 5:{
            cout << "Thanks for using UMBC Encryption" << endl;
            break;
        }
    }
    }while (choice != 5);//continue asking choices until quit
}
        
