//*****************************************************************************************
//File:     Area.cpp
//Project:  CMSC 202 Project 5, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     05/01/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play a game that includes a hero who gathers resources and crafting items
//*****************************************************************************************

#include "Area.h"
//Name: Area (Overloaded Constructor)
//Precondition: Must have valid input for each part of a area
// First int is the unique identifier for this particular area.
// The first string is the name of the area
// The second string is the description of the area
// The last four ints are the unique identifier for adjacent areas
//     (-1 = no path)
// North, East, South, and West
//Postcondition: Creates a new area
Area::Area(int location, string areaName, string message, int north, int east, int south, int west){
  m_ID = location;
  m_name = areaName;// sets the name of the area
  m_desc = message;
  m_direction[0] = north;//stores the direction for the area.
  m_direction[1] = east;
  m_direction[2] = south;
  m_direction[3] = west;

}
//Name: GetName
//Precondition: Must have valid area
//Postcondition: Returns area name as string
string Area::GetName(){
  return m_name;
}
//Name: GetID
//Precondition: Must have valid area
//Postcondition: Returns area id as int
int Area::GetID(){
  return m_ID;
}
//Name: GetDesc
//Precondition: Must have valid area
//Postcondition: Returns area desc as string
string Area::GetDesc(){
  return m_desc;
}

//Name: CheckDirection
//Precondition: Must have valid area
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the area in that direction
//Postcondition: Returns id of area in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Area::CheckDirection(char myDirection){
    if(myDirection == 'n'|| myDirection == 'N'){ //checks if north
      return m_direction[0];// Returns the ID of the area to the north
    }
    else if(myDirection == 'e'|| myDirection == 'E'){//checks if east
      return m_direction[1];
    }
    else if(myDirection == 's'|| myDirection == 'S'){//checks if south
      return m_direction[2];
    }
    else if(myDirection == 'w'|| myDirection == 'W'){//checks if west
      return m_direction[3];
    }
    else{
      return -1;
    }
  
}
  
//Name: PrintArea
//Precondition: Area must be complete
//Postcondition: Outputs the area name, area desc, then possible exits
void Area::PrintArea(){
  cout << m_name << endl;
  cout << m_desc << endl;//prints the name of area and description
  cout << "Possible Exits: ";


   if (m_direction[0] != -1){
    cout << "N";//prints th possible exists
   }
   if (m_direction[1] != -1){
    cout << "E";
   }
   if (m_direction[2] != -1){
    cout << "S";//prints the possible exits
   }
   if (m_direction[3] != -1) {
    cout << "W";
   }
}