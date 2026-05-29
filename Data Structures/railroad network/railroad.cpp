/*****************************************
** File:    railroad.cpp
** Project: CMSC 341 Project 1, Fall 2025
** Author:  Akanksha Madhu Kiran
** Date:    09/29/2025
** E-mail:  amadhuk1@umbc.edu
** This file contains the Railroad class.
*****************************************/
#include "railroad.h"

//Constructor initializes an empty Railroad
Railroad::Railroad(){
    m_numStations = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

//Destructor ensures all allocated stations are cleared from memory
Railroad::~Railroad(){
    clearNetwork();
}

//Removes all stations and resets the railroad to empty
void Railroad::clearNetwork(){
    Station* curr = m_head;
    while (curr) { //goes through all stations
        Station* temp = curr; 
        curr = curr->m_next;
        delete temp;
    }
    m_head = nullptr; //initialize member variables to 0
    m_tail = nullptr;
    m_numStations = 0;
}

bool Railroad::extendAtHead(int newCode, int passengers) {
    if (newCode < 1 || findStation(newCode)) {
        return false;
    }
    Station* newNode = new Station(newCode, passengers);
    if (m_head == nullptr) {  //if empty list
        m_head = newNode;
        m_tail = newNode;
    }
    else { //Insert before existing head
        newNode->m_next = m_head;
        m_head->m_previous = newNode;
        m_head = newNode;
    }
    m_numStations++;
    return true;
}

//Adds a station at the tail of the list if valid and unique
bool Railroad::extendAtTail(int newCode, int passengers) {
    if (newCode < 1 || findStation(newCode)) { //Invalid or Duplicate
        return false;
    }
    Station* newNode = new Station(newCode, passengers);
    if (m_tail == nullptr) { //if empty list
        m_head = newNode;
        m_tail = newNode;
    }
    else { //add after existing tail
        newNode->m_previous = m_tail;
        m_tail->m_next = newNode;
        m_tail = newNode;
    }
    m_numStations++;
    return true;
}

//Creates a route between stations, adding stations if needed
bool Railroad::makeRoute(list< pair<int,DIRECTION> > route){
    if (route.empty()){ //no route exists
        return false;
    }
    list<pair<int,DIRECTION> >::iterator way = route.begin();
    int startCode = (*way).first; //Starting station
    Station* prevStation = findStation(startCode);
    if (prevStation == nullptr){ //first station must be present
        return false;
    }
    DIRECTION prevDir = (*way).second; //Direction from start
    ++way;

    while (way != route.end()){ //go through route pairs
        int currCode = (*way).first;
        DIRECTION currDir = (*way).second;//make connection between first and second
        Station* currStation = findStation(currCode);
        if (currStation == nullptr) { //add new station if does not exists
            if (!extendAtTail(currCode, DEFNUMPASS)){
                return false;
            }
            currStation = findStation(currCode);
        }

        //check if previous direction already linked elsewhere; TODO: rtd
        Station* linkPtr = nullptr;
        if (prevDir == NORTH) {
            linkPtr = prevStation->m_north;
        } else if (prevDir == SOUTH) {
            linkPtr = prevStation->m_south;
        } else if (prevDir == EAST) {
            linkPtr = prevStation->m_east;
        } else if (prevDir == WEST) {
            linkPtr = prevStation->m_west;
        } 

        if (linkPtr != nullptr && linkPtr != currStation){
            return false;
        }
        //directions linked
        if (prevDir == NORTH) {
            prevStation->m_north = currStation;
        } else if (prevDir == SOUTH) {
            prevStation->m_south = currStation;
        } else if (prevDir == EAST) {
            prevStation->m_east = currStation;
        } else if (prevDir == WEST) {
            prevStation->m_west = currStation;
        }
        prevStation = currStation; //move ahead
        prevDir = currDir;
        ++way;
    }
    return true;
}

int Railroad::travel(list< pair<int,DIRECTION> > route){
    if (route.empty()) { //check if route empty
        return -1;
    }

    list<pair<int,DIRECTION> >::iterator way = route.begin();
    int startCode = (*way).first; //start at the first station
    Station* curr = findStation(startCode);
    if (curr == nullptr) { //check if station exists
        return -1;
    }

    int total = curr->m_passengers;
    list<int> visited; //to keep track of visited stations
    visited.push_back(curr->m_code);
    DIRECTION dir = (*way).second;
    ++way;

    while (way != route.end()) { //to loop through routes
        if (dir == NONE) {
            return total; //stop moving if NONE
        }
        if (dir == NORTH) {
            curr = curr->m_north;
        } else if (dir == SOUTH) {
            curr = curr->m_south;
        } else if (dir == EAST) {
            curr = curr->m_east;
        } else if (dir == WEST) {
            curr = curr->m_west;
        } else {
            return -1;
        }

        if (curr == nullptr) { //check if valid
            return -1;
        }
        total = total + curr->m_passengers;
        dir = (*way).second;
        ++way;
    }
    //to check if I visited the station - to debug
    // cout << "Visited: ";
    // list<int>::iterator it;
    // for (it = visited.begin(); it != visited.end(); ++it) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    return total; //return the total passengers
}


 
bool Railroad::setNumPassengers(int code, int passengers){
    Station* st = findStation(code);
    if (!st){
        return false;
    }
    st->m_passengers = passengers;
    return true;
}

bool Railroad::removeStation(int aCode) {
    Station* removeNode = findStation(aCode);
    if (!removeNode) { //check if station exists
        return false;
    }

    Station* curr = m_head;
    while (curr) { //go through all stations and remove links to the one being removed
        if (curr->m_north == removeNode) {
            curr->m_north = nullptr;
        }
        if (curr->m_south == removeNode) {
            curr->m_south = nullptr;
        }
        if (curr->m_east == removeNode) {
            curr->m_east = nullptr;
        }
        if (curr->m_west == removeNode) {
            curr->m_west = nullptr;
        }

        curr = curr->m_next; //move forward
    }

    if (removeNode->m_previous) {
        removeNode->m_previous->m_next = removeNode->m_next;
    } else {
        //if deleting head
        m_head = removeNode->m_next;
    }

    if (removeNode->m_next) {
        removeNode->m_next->m_previous = removeNode->m_previous;
    } else {
        //if deleting tail
        m_tail = removeNode->m_previous;
    }

    delete removeNode;
    m_numStations--;

    return true;
}


void Railroad::clearAllRoutes(){ //clears all routes
    Station* curr = m_head;
    while (curr) {
        curr->m_north = nullptr;
        curr->m_south = nullptr;
        curr->m_east  = nullptr;
        curr->m_west  = nullptr;
        curr = curr->m_next;
    }
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}

Railroad::Railroad(const Railroad & rhs){ //copy constructor
    m_numStations = 0;
    m_head = nullptr;
    m_tail = nullptr;
    *this = rhs;
}

const Railroad & Railroad::operator=(const Railroad & rhs){ //assignment operator
    if (this == &rhs){
        return *this;
    }
    clearNetwork(); //clears network
    Station* curr = rhs.m_head;
    while (curr) { //to copy each station
        extendAtTail(curr->m_code, curr->m_passengers);
        curr = curr->m_next;
    } 

    Station* rr = rhs.m_head;
    while (rr) { //to copy all routes
        Station* pp = findStation(rr->m_code);

        if (rr->m_north) {
            pp->m_north = findStation(rr->m_north->m_code);
        }
        if (rr->m_south) {
            pp->m_south = findStation(rr->m_south->m_code);
        }
        if (rr->m_east) {
            pp->m_east = findStation(rr->m_east->m_code);
        }
        if (rr->m_west) {
            pp->m_west = findStation(rr->m_west->m_code);
        }

        rr = rr->m_next;
    }

    return *this;
}

Station* Railroad::findStation(int aCode) const {
    Station* curr = m_head;
    while (curr != nullptr) {
        if (curr->m_code == aCode) {
            return curr;
        }
        curr = curr->m_next;
    }
    return nullptr;
}
