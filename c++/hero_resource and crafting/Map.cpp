//*****************************************************************************************
//File:     Map.cpp
//Project:  CMSC 202 Project 5, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     05/01/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play a game that includes a hero who gathers resources and crafting items
//*****************************************************************************************

/*Title: Map.cpp
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: This class defines the Map class
  Map is a templated associative container that stores
  key–value pairs in sorted order using a singly linked
  list, supporting insertion, lookup, update, and removal
  with O(n) traversal.
*/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  Map();
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  ~Map();
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  Map(const Map& other);
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  Map<K,V>& operator=(const Map& other);
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  void Insert(const K& key, const V& value);
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  void Update(const K& key, const V& value);
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  const V& ValueAt(const K& key) const;
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  Node<K,V>* At(const K& key) const;
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  int GetSize() const;
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  bool IsEmpty() const;
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  void Display() const;
  // Name: operator<<
  // Description: Streams all key:value pairs into os, one per line.
  // Preconditions: os is a valid ostream; map is a valid Map<K,V>.
  // Postconditions: os contains serialized map contents;
  //                returns os by reference.
  // PROVIDED
  friend ostream& operator<<(ostream& os, const Map<K, V>& map){
    Node<K,V>* current = map.m_head;
    while (current != nullptr) {
      os << current->GetKey() << ":" << current->GetValue() << endl;
      current = current->GetNext();
    }
    return os;
  }
private:
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
  void Clear();  
  Node<K,V>* m_head; //Pointer to the first node in the Map
  int m_size; //Tracks the size of the Map (number of nodes)
};
#endif

//********IMPLEMENT MAP.CPP HERE DUE TO TEMPLATED CLASS*********


// Name: Map()
// Description: Default constructs an empty map.
// Preconditions: None.
// Postconditions: m_head is set to nullptr; m_size is initialized to 0.
template <typename K, typename V>
Map<K,V>::Map(){
  m_head = nullptr;//starts with no nodes
  m_size = 0;//map size = 0
}
// Name: ~Map()
// Description: Destroys the map, freeing all nodes.
// Preconditions: None.
// Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
template <typename K, typename V>
Map<K,V>::~Map(){
  Clear();//to clean up memory
}
// Name: Map(const Map& other)
// Description: Copy constructor; deep copies another map’s contents.
// Preconditions: other must be a valid Map<K,V>.
// Postconditions: This map contains the same key/value pairs, in order.
template <typename K, typename V>
Map<K,V>::Map(const Map& other){
  m_head = nullptr;//starts with nothing in the map
  m_size = 0;

  // Go through each node in the other map and add it
  Node<K,V>* current = other.m_head;
  while (current != nullptr) {
    // to add each key/value pair to this map
    Insert(current->GetKey(), current->GetValue());
    current = current->GetNext();
  }
}


// Name: operator=(const Map& other)
// Description: Assignment operator; clears this map and deep copies other.
// Preconditions: other is a valid Map<K,V>; self-assignment is handled.
// Postconditions: This map contains a copy of other’s elements.
template <typename K, typename V>
Map<K,V>& Map<K,V>::operator=(const Map& other){
  if (this != &other) {//avoiding assignment to itself
    Clear();  //to delete current nodes

    //going through each node in the other map and add it
    Node<K,V>* current = other.m_head;
    while (current != nullptr) {
      Insert(current->GetKey(), current->GetValue());//inserting the nodes
      current = current->GetNext();//connecting the nodes to the next one
    }
  }
  return *this;
}


 
// Name: Insert(const K& key, const V& value)
// Description: Inserts or updates a key → value pair, keeping
//              nodes ordered by key.
// Preconditions: key and value are valid; map may be empty.
// Postconditions: New node inserted at sorted position, or
//                 existing node’s value updated; m_size adjusted.
template <typename K, typename V>
void Map<K,V>::Insert(const K& key, const V& value) {
  if (m_head == nullptr) {//if empty map enter first node
    m_head = new Node<K,V>(key, value);
    m_size++;
  } else {//if not empty add the node somewhere
    Node<K,V>* temp = m_head;
    Node<K,V>* prevNode = nullptr;

    while (temp != nullptr && temp->GetKey() < key) {//go through each to find where to insert 
      prevNode = temp;
      temp = temp->GetNext();
    }

    if (temp != nullptr && temp->GetKey() == key) {//if that key exists already update value
      temp->SetValue(value);
    } else {//if key does not exist insert new node
      Node<K,V>* newNode = new Node<K,V>(key, value);
      if (prevNode == nullptr) { //insert in beginning
        newNode->SetNext(m_head);
        m_head = newNode;
      } else {
        newNode->SetNext(prevNode->GetNext());// Insert between prevNode and temp
        prevNode->SetNext(newNode);
      }
      m_size++;
    }
  }
}

// Name: Update(const K& key, const V& value)
// Description: Changes the value for an existing key.
// Preconditions: key must exist in the map.
// Postconditions: Corresponding node’s value is set to
//                 value; throws out_of_range if key not found.
template <typename K, typename V>
void Map<K,V>::Update(const K& key, const V& value){
  Node<K,V>* current = m_head;
  while (current != nullptr) {//loop through the nodes of the map
    if (current->GetKey() == key) {//if the key is found
      current->SetValue(value);//change value
      return;
    }
    current = current->GetNext();//if not then move on to next node to check
  }
  throw out_of_range("Key not found");//if does not exist at all throw out_of_range
}


// Name: ValueAt(const K& key) const
// Description: Retrieves a const reference to the value for key.
// Preconditions: key must exist in the map.
// Postconditions: Returns reference to the value;
//                 throws out_of_range if not found.
template <typename K, typename V>
const V& Map<K,V>::ValueAt(const K& key) const{
  Node<K,V>* current = m_head;
  while (current != nullptr) {//loop through the nodes of the map
    if (current->GetKey() == key) {//check if key value matches
      return current->GetValue();//if yes get the value
    }
    current = current->GetNext();//if not move on
  }
  throw out_of_range("Key not found");//if not found throw out of range
}


// Name: At(const K& key) const
// Description: Returns a pointer to the node for key.
// Preconditions: key must exist in the map.
// Postconditions: Returns pointer to the Node<K,V>;
//                 throws out_of_range if not found.
template <typename K, typename V>
Node<K,V>* Map<K,V>::At(const K& key) const{
  Node<K,V>* temp = m_head;
  while (temp != nullptr) {//loop through the nodes of map
    if(temp->GetKey() == key){//if key matches
      return temp;//returns the pointer
    }
    temp = temp->GetNext();//moves on to check the next node

  }
  throw out_of_range("Key not found");//if not found throw out of range
}

// Name: GetSize() const
// Description: Reports the number of key‑value pairs in the map.
// Preconditions: None.
// Postconditions: Returns the value of m_size.
template <typename K, typename V>
int Map<K,V>::GetSize() const{
  return m_size;//returns number of nodes in map
}
// Name: IsEmpty() const
// Description: Checks whether the map contains no elements.
// Preconditions: None.
// Postconditions: Returns true if m_size == 0
//                 (m_head == nullptr); false otherwise.
template <typename K, typename V>
bool Map<K,V>::IsEmpty() const{
  if(m_head == nullptr){//checks if empty
    return true;//returns true if empty
  }
  else{
    return false;
  }
}
// Name: Display() const
// Description: Prints each key:value pair to cout, one per line.
// Preconditions: ostream cout is available.
// Postconditions: Map contents are written to standard output.
template <typename K, typename V>
void Map<K,V>::Display() const{
  Node<K,V>* temp = m_head;
  while (temp != nullptr) {//loops through the nodes of the map
    cout << temp->GetKey()<< ":" << temp->GetValue() << endl;//prints the Key and the value of the node
    temp = temp->GetNext();//moves on to the next node
  }
}


template <typename K, typename V>
void Map<K,V>::Clear(){
  while (m_head != nullptr) {//loops through the nodes of the map
    Node<K,V>* temp = m_head;//saves current node
    m_head = m_head->GetNext();//moves
    delete temp;//frees memory
    temp = nullptr;//to avoid memory leaks
  }
m_size = 0;//sets line count as 0
}
