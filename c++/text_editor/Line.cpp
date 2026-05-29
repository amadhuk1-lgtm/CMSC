//*****************************************************************************************
//File:     Line.cpp
//Project:  CMSC 202 Project 3, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     03/30/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to make a text document.
//*****************************************************************************************
#include "Line.h"
// Name - Line() - Default constructor
// Desc - Creates an empty line (acts as linked list node)
// Preconditions - None
// Postconditions - Used to create a new line object with m_next as a nullptr
Line::Line(){
      m_next = nullptr;//initiallizing next to nullptr
      m_text = " ";//initializes text to space 
}

// Name - Line(string) - Overloaded constructor
// Desc - Creates a line with the passed value and a nullptr (acts as linked list node)
// Preconditions - None
// Postconditions - Used to create a new line object
Line::Line(string text){
      m_text = text ; // initializing the text to string provided
      m_next = nullptr;  // initializes the next pointer to nullptr
}
  
// Name - Getters and Setters
// Desc - Used to access the private member variables in the line object
// Preconditions - Object exists
// Postconditions - Either returns m_text, m_next or sets m_text or m_next
string Line::GetText(){
      return m_text;//Returns text in node
}


Line* Line::GetNext(){ 
      return m_next; //Returns next line in document
}


void Line::SetText(string text){
      m_text = text ; // Set the text tostring given
}


void Line::SetNext(Line* next){
      m_next = next;  // Set the next pointer to node
}