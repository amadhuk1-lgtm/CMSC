//*****************************************************************************************
//File:     TextEditor.cpp
//Project:  CMSC 202 Project 3, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     03/30/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to make a text document.
//*****************************************************************************************
#include "TextEditor.h"

// Name - TextEditor - default constructor
// Desc - Set m_fileName to empty
// Preconditions - None
// Postconditions - Set m_fileName to empty. Creates document (m_editor)
TextEditor::TextEditor(){
    m_fileName = " ";//initializes filename to empty space
}


// Name - MainMenu
// Desc - Displays options:
//        1. Insert Line, 2. Delete Line, 3. Edit Line, 4. Display Document
//        5. Search Word, 6. Save to File, 7. Load from File, 8. Exit
// Preconditions - None
// Postconditions - Returns valid choice (1-8)
int TextEditor::MainMenu(){
  int choice = 0;
  cout << "--- Simple Text Editor ---" << endl;
  cout << "1. Insert Line" << endl;
  cout << "2. Delete Line" << endl;
  cout << "3. Edit Line" << endl;
  cout << "4. Display Document" << endl;
  cout << "5. Search Word" << endl;
  cout << "6. Save to File" << endl;
  cout << "7. Load from File" << endl;
  cout << "8. Exit" << endl;
  cout << "Enter your choice: " ;
  cin >> choice;//takes the choice made by user

  return choice;//returns the choice
}


// Name - GetLineNumber
// Desc - Allows user to choose a specific line number from document.
//        For functions such as DeleteLine and EditLine, the line number must be exact
//            (between 1 and the number of lines in the document)
//        For InsertLine, the line must be between 1 and the number of lines + 1
// Preconditions - Document (m_editor) exists
// Postconditions - Returns line chosen
int TextEditor::GetLineNumber(bool isExact){
  int lineNumber;
  int maxLines = m_editor.GetLineCount();//get total number of lines in document
  do {
    m_editor.DisplayDocument(); // displays current document lines

    cout << "Enter line number: " << endl;
    cin >> lineNumber;
    //checks the validity of line number entered
    if (lineNumber < 1 || (isExact && lineNumber > maxLines) || (!isExact && lineNumber > maxLines + 1)) {
        cout << "Must be between 1 and " << (isExact ? maxLines : maxLines + 1) << endl;
    }
  } while (lineNumber < 1 || (isExact && lineNumber > maxLines) || (!isExact && lineNumber > maxLines + 1));//keeps looping until valid number

  return lineNumber;//returns line number
}


// Name - GetFileName
// Desc - Prompts user for file name. Stores in m_fileName
// Preconditions - None
// Postconditions - Returns file name entered
string TextEditor::GetFileName(){
  cout << "Enter file name: " << endl;
  cin >> m_fileName;//stores file name entered in m_fileName
  return m_fileName;
}


// Name - Start
// Desc - Calls MainMenu. Takes menu response and uses switch statement to
//        call corresponding function (display just calls DisplayDocument)
//        Keeps calling until user enters 8 (quit).
// Preconditions - None
// Postconditions - Keeps asking user what to do until they enter 8 (quit).
void TextEditor::Start(){
  int choice;
  do {
    choice = MainMenu();//displays the menu and asks the choice of user
    switch(choice) {
      case 1:{
        InsertLine();//to insert line
        break;
      }
      case 2:{
        DeleteLine();//to delete line
        break;
      }
      case 3:{
        EditLine();//to edit line
        break;
      }
      case 4:{
        cout << "**Display Document**" << endl;
        m_editor.DisplayDocument();//to display all the lines in the document
        break;
      }
      case 5:{
        SearchDocument();//to search word in document
        break;
      }
      case 6:{
        SaveFile();//to save the current document
        break;
      }
      case 7:{
        LoadFile();//to load file that already has data
        break;
      }
      case 8:{
        cout << "Thank you for using the UMBC Text Editor" << endl;
        break;
      }
      default:{
        cout << "Invalid choice. Please enter 1, 2, 3, 4, 5, 6, 7 or 8." << endl; //to check if it is a valid choice and loop through again
        break;
      }
    } 
  }while (choice != 8);//continue asking choices until valid choice
}


// Name - InsertLine
// Desc - Inserts a new line into the document(m_editor). Asks user where to
//        insert the new line by calling GetLineNumber. Inserts the new line before
//        the line chosen.
// Preconditions - None
// Postconditions - Inserts line into document (m_editor).

void TextEditor::InsertLine() {
  int position;
  int maxLines = m_editor.GetLineCount();//gets total number of lines
  cout << "**Insert Line**" << endl;
  if (maxLines == 0) {
    // If the document is empty start entering the text directly
    position = 1;//to start entering text at first position
    cout << "Enter text: ";
    cin.ignore();
    string text;
    getline(cin, text);//get the text for creating the line
    m_editor.InsertLine(text, position);//insert the line
  } else {
    cout << "Inserts line before chosen line number" << endl;
    int position = GetLineNumber(false);  //Asks the line number where you want to insert line
    cout << "Enter text: ";
    cin.ignore();
    string text;
    getline(cin, text);//gets the text entered
    m_editor.InsertLine(text, position);  //inserts the line at the position
  }
}


// Name - DeleteLine
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        calls GetLineNumber. Then deletes line from document.
// Preconditions - Document has at least one line.
// Postconditions - Removes line from document (m_editor).
void TextEditor::DeleteLine(){
  cout << "**Delete Line**" << endl;
  if (m_editor.GetLineCount() == 0) {//if document is empty
      cout << "Document is empty!" << endl;
  } else {
    int position = GetLineNumber(true);//get line number to delete the line
    m_editor.DeleteLine(position);//delete chosen line
  }
}

// Name - EditLine
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        calls GetLineNumber. Updates the text in the chosen line.
// Preconditions - Document has at least one line.
// Postconditions - Updates line from document (m_editor).
void TextEditor::EditLine(){
  if (m_editor.GetLineCount() == 0) {//if document is empty
    cout << "Document is empty!" << endl;
  } else {
    cout << "**Edit Line**" << endl;
    int position = GetLineNumber(true);//get line number which needs to be edited
    cin.ignore();
    cout << "Enter new text: ";
    string text;
    getline(cin, text);//gets the new text entered
    m_editor.EditLine(position, text);//updates line with new text
  }
}

// Name - SearchDocument
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        asks user which text to search for. Displays all lines that have
//        the matching text.
// Preconditions - Document has at least one line.
// Postconditions - Displays line from document (m_editor).
void TextEditor::SearchDocument(){
  cout << "**Search Document**" << endl;
  if (m_editor.GetLineCount() == 0) {//if document is empty
    cout << "Document is empty!" << endl;
  } else {
    string word;
    cout << "Enter word to search: ";
    cin >> word;//saves the word you need to search for
    m_editor.SearchWord(word);//to find the word to search for
  }
}


// Name - LoadFile
// Desc - Asks user for the file name. Opens file. Inserts lines from file
//        into existing document (m_editor). Appends document (m_editor).
// Preconditions - None
// Postconditions - Inserts text from file into document (m_editor).
void TextEditor::LoadFile(){
  cout << "**Load File**" << endl;
  string filename = GetFileName();//to get the filename to load
  m_editor.LoadFromFile(filename);//to load lines into document
  cout << "File loaded successfully!" << endl;
}


// Name - SaveFile
// Desc - Asks user for the file name. Opens file. Writes out all lines from
//        document (m_editor) to the file.
// Preconditions - None
// Postconditions - Inserts text from document (m_editor) into file.
void TextEditor::SaveFile(){
  cout << "**Save File**" << endl;
  string filename = GetFileName();//get filename to save
  m_editor.SaveToFile(filename);//save lines to the file
  cout << "File saved successfully!" << endl;
}
