//*****************************************************************************************
//File:     DoodleGod.cpp
//Project:  CMSC 202 Project 2, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     03/06/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play Doodle God.
//This is extra credit
//*****************************************************************************************

#include "DoodleGod.h"

// Name: DoodleGod() - Default Constructor
// Preconditions - None
// Postconditions - Creates a new DoodleGod and sets default values to 0 for all integers
// Desc: Used to build a new DoodleGod
DoodleGod::DoodleGod() {
    m_myName = " "; //setting values to 0 or empty
    m_attempts = 0;
    m_repeats = 0;
    m_numElements = 0;
}


// Name: DoodleGod(name) - Overloaded constructor
// Preconditions - Requires name
// Postconditions - Creates a new DoodleGod and sets default values to 0 for all integers
// Desc - Used to build a new DoodleGod
DoodleGod::DoodleGod(string name) {
    m_myName = name;//saving the name
    m_attempts = 0;//setting values to 0
    m_repeats = 0;
    m_numElements = 0;
}


// Name: GetName()
// Preconditions - DoodleGod exists
// Postconditions - Returns the name of the DoodleGod
// Desc - Getter for DoodleGod name
string DoodleGod::GetName() {
    return m_myName;//getting the name
}

// Name: SetName(string)
// Preconditions - DoodleGod exists
// Postconditions - Sets name of DoodleGod
// Desc - Allows the user to change the name of the DoodleGod
void DoodleGod::SetName(string name) {
    m_myName = name;//Sets name of DoodleGod
}

// Name: DisplayElements()
// Preconditions - DoodleGod exist
// Postconditions - Displays numbered list of all known elements
// Desc - Returns number of elements known by the DoodleGod
void DoodleGod::DisplayElements() {
    for (int i = 0; i < m_numElements; ++i) { //loops through m_myElements to display all that are known
        if (m_myElements[i] != nullptr) { //makes sure it does not print empty spaces
            cout << i + 1 << ". " << m_myElements[i]->m_name << endl; //accesses the elements name and prints it.
        }
    }
}


// Name: GetNumElements()
// Preconditions - DoodleGod exists
// Postconditions - Returns the integer value of all known elements
// Desc - Returns number of elements known by the DoodleGod
int DoodleGod::GetNumElements() {
    return m_numElements;//returns the number of known elements
}

// Name: CheckElement(Element)
// Preconditions - DoodleGod already has elements, takes a pointer.
// Postconditions - Returns true if DoodleGod has element else false
// Desc - Checks to see if the DoodleGod had identified an element
bool DoodleGod::CheckElement(Element* elem) {
    for (int i = 0; i < m_numElements; i++) { //loops through every stored element in m_myElements
       if (m_myElements[i] != nullptr && m_myElements[i]->m_name == elem->m_name) {//checks if element created already exists or empty
            return true;
        }
    }
    return false;
}

// Name: AddElement(Element)
// Preconditions - DoodleGod exists and new element not already known, takes a pointer
// Postconditions - Adds element to m_myElements
// Desc - Adds element to m_myElements if not known and increases numElements
void DoodleGod::AddElement(Element* elem) {
    if (!CheckElement(elem) && m_numElements < PROJ2_SIZE) { //checks if element is already found or not
        m_myElements[m_numElements] = elem;//adds the element created
        m_numElements++;//to keep track of number of elements found
    }
}

// Name: GetElement(int)
// Preconditions - DoodleGod already has elements and takes in the index where the combined element is located
// Postconditions - Returns element at index
// Desc - Checks to see if the DoodleGod has an element
Element* DoodleGod::GetElement(int index) {
    if (index >= 0 && index < m_numElements) { //checks if index is within the valid range
        return m_myElements[index]; // returns location of element stored there
    }
    return nullptr;//else returns an empty pointer
}

// Name: AddAttempt
// Preconditions - DoodleGod attempts a merge
// Postconditions - Increments every time a merge is attempted
// Desc - Increments attempts
void DoodleGod::AddAttempt() {
    m_attempts++; //Increments every time a merge is attempted
}

// Name: GetAttempts()
// Desc - Returns number of attempts for that DoodleGod
// Preconditions - DoodleGod exists
// Postconditions - Returns total number of attempts
int DoodleGod::GetAttempts() {
    return m_attempts;//return the attempts made
}

// Name: AddRepeat()
// Preconditions - DoodleGod attempts a merge
// Postconditions - Increments every time a merge yields an element already found
// Desc - Increments repeats for every time an element has already been found
void DoodleGod::AddRepeat() {
    m_repeats++;//increments the number of repeats
}


// Name: GetRepeats()
// Preconditions - DoodleGod exists
// Postconditions - Returns total number of repeats
// Desc - Returns number of repeats for that DoodleGod
int DoodleGod::GetRepeats() {
    return m_repeats;//returns the repeats
}
