//*****************************************************************************************
//File:     Item.cpp
//Project:  CMSC 202 Project 5, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     05/01/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play a game that includes a hero who gathers resources and crafting items
//*****************************************************************************************

#include "Item.h"
  // Name: Item(const string& name, const vector<string>& requirements)
  // Description: Constructs a new Item with the given name and
  //              a list of crafting requirements.
  // Preconditions: ‘name’ must be a valid, non-empty string;
  //                ‘requirements’ must contain valid item names.
  // Postconditions: m_name is initialized to name;
  //                 m_req is initialized to a copy of requirements.
Item::Item(const string& name, const vector<string>& requirements){
  m_name = name;//initializes the name and the requirements
  m_req = requirements;
   
}
  // Name: GetName()
  // Description: Retrieves the name of this item.
  // Preconditions: None.
  // Postconditions: Returns the value of m_name.
string Item::GetName() const {
  return m_name;//gets the name of item
}
  // Name: GetReq()
  // Description: Retrieves the list of crafting requirements for this item.
  // Preconditions: None.
  // Postconditions: Returns a const reference to m_req
  //                 (the requirements vector).
const vector<string>& Item::GetReq() const {
  return m_req;//gets the requirements vector
}