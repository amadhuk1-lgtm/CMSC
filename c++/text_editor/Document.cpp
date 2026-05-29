//*****************************************************************************************
//File:     Document.cpp
//Project:  CMSC 202 Project 3, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     03/30/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to make a text document.
//*****************************************************************************************

#include "Document.h"

// Name - Document() - Default constructor
// Desc - Creates an empty Document (linked list)
// Preconditions - None
// Postconditions - Sets m_head to nullptr and m_lineCount = 0
Document::Document(){
  m_head = nullptr; //makes the head a null pointer
  m_lineCount = 0; //makes the number of lines 0
}


// Name - ~Document() - Destructor
// Desc - Removes all lines from Document (removes all nodes from linked list)
// Preconditions - None
// Postconditions - Removes all lines and sets m_head to nullptr
//                  and m_lineCount = 0
Document::~Document(){
  while (m_head != nullptr) {
    //loops through the lines of the document when not empty
    Line* temp = m_head;//stores line as node
    m_head = m_head->GetNext();//points to the next node
    delete temp;//frees memory
    temp = nullptr;//to avoid memory leaks
  }
  m_lineCount = 0;//sets line count as 0
}


// Name - InsertLine(string,int)
// Desc - Inserts a new line (node) into the Document (linked list)
//        Dynamically allocates new line and inserts line in position
//        indicated. Inserts the line **before** the position.
//        For example, if position 1 then inserts a new first line to the Document
// Preconditions - Document exists
// Postconditions - New line inserted into the Document
void Document::InsertLine(string text, int position) {
  if (position < 0 || position > m_lineCount + 1) { //checking validity of the position
      cout << "Invalid position" << endl;
  }
  else{
    Line* newLine = new Line(text);  // creates new line
    if (position == 1) {
        //checks if inserting line in the beginning
        newLine->SetNext(m_head);  //points to the next node
        m_head = newLine;  // considers the new created one is the head(like moving to the next train coach)
    } else {
        Line* current = m_head;
        for (int i = 1; i < position - 1; i++) { 
          //goes through the document to find the node at the position wanted
          current = current->GetNext();//moves to the next node
        }
        newLine->SetNext(current->GetNext());  //points the new created line to the next one
        current->SetNext(newLine);
    }

    m_lineCount++;  // Increments line count as new line is inserted
  }
}

// Name - DeleteLine(int)
// Desc - Deletes a line from the Document at a provided position
//        Deletes the exact line chosen.
//        Indicates the document is empty if the Document has no lines
// Preconditions - Document exists and line exists
// Postconditions - Line removed from Document
void Document::DeleteLine(int position){
  if (m_head == nullptr || position < 1 || position > m_lineCount) { //checks validity of position
      cout << "Invalid position or document is empty!" << endl;
  }
  else{
    Line* temp = m_head;
    if (position == 1) { //if deleting first text, as deleting the initial head
        m_head = m_head->GetNext();
        delete temp;
        temp = nullptr;
    } else {
        Line* prev = nullptr;
        int count = 1;
        while (count < position) {//goes through the document to delete the text in the position
            prev = temp;
            temp = temp->GetNext();
            count++;
        }
        prev->SetNext(temp->GetNext()); //links the nodes around it
        delete temp;//delete the chosen line
        temp = nullptr;
    }
  }
  m_lineCount--;
}


// Name - EditLine(int, string)
// Desc - Edits the text in a specific Line at a provided position (line number).
//        Updates the string in a specific Line. Uses the exact line number.
//        Indicates the document is empty if the Document has no Lines
// Preconditions - Document exists and line exists.
// Postconditions - Line text updated at a provided position
void Document::EditLine(int position, string newText){
  Line* temp = m_head;//starts from the beginning
  int count = 1;
  while (count < position) {//loop through the document to access the text at the position
      temp = temp->GetNext();
      count++;
  }
  temp->SetText(newText);//update text
}
  
  
// Name - DisplayDocument
// Desc - Iterates through the Document and displays all data in Line
//        Indicates the document is empty if the Document has no lines
// Preconditions - Document exists
// Postconditions - Displays all lines in Document
void Document::DisplayDocument(){
  Line* temp = m_head;
  int lineNum = 1;//starts from line 1
  while (temp) {//loop through all lines
      cout << lineNum << ": " << temp->GetText() << endl; //prints texts of lines with numbers
      temp = temp->GetNext();//got to location of next node
      lineNum++;//increments line number
  }
    
}
  
// Name - SearchWord(string)
// Desc - Iterates through the Document and searches for provided text
//        Uses the "find" command in string
//        Returns any complete word or any substring.
//        For example, if you search for 'a' then it will
//           return any line that has an 'a' in any word.
//        Details: https://cplusplus.com/reference/string/string/find/
//        Indicates if string not found
// Preconditions - Document exists
// Postconditions - Indicates line number where found or not
void Document::SearchWord(string word){
  Line* temp = m_head;
  int lineNum = 1;
  bool found = false;
  while (temp != nullptr) { //loop through all lines
      if(temp->GetText().find(word) < temp->GetText().length()){//finds the word and gets the text
        cout << "Word found in line " << lineNum << ": " << temp->GetText() << endl;//print line found and the text of the line
        found = true;
      }
      temp = temp->GetNext();//makes sure it keeps searchng in future lines as well if not found in first line
      lineNum++;
  }
  if (!found) {
      cout << "Word not found in document!" << endl;
  }
}


// Name - SaveToFile(string)
// Desc - Iterates through the Document and saves all lines to
//        provided filename
// Preconditions - Document exists
// Postconditions - Writes all lines in Document to file
void Document::SaveToFile(string filename) {
  ofstream outFile(filename);  //opens output file

  Line* temp = m_head;//starts from the beginning(head)

  while (temp != nullptr) {  //loop through document
      outFile << temp->GetText() << endl;//write text of the node in the file
      temp = temp->GetNext();//go to the next line and keep looping until the end
  }
  outFile.close(); //close file
}

  
// Name - LoadFromFile(string)
// Desc - For each line in the input file, inserts one line
//        into the Document
// Preconditions - Document exists
// Postconditions - Writes all from file to Document
void Document::LoadFromFile(string filename) {
  ifstream inFile(filename);//open input file
  string line;
  int lineNumber = 1;  //begin numbering the lines

  while (getline(inFile, line)) {  //gets each line
      InsertLine(line, m_lineCount + 1);  //inserts line to the file
      lineNumber++;  // increments the line numbers
  }
  inFile.close();//close file
}



  
// Name - GetLineCount();
// Desc - Returns m_lineCount
// Preconditions - Document exists
// Postconditions - Returns m_lineCount
int Document::GetLineCount(){
    return m_lineCount;//returns number of lines in document
}