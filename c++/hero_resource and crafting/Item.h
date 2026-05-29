/*Title: Item.h
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: This class defines items (things you can craft)
*/
#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>
using namespace std;

class Item {
public:
  // Name: Item(const string& name, const vector<string>& requirements)
  // Description: Constructs a new Item with the given name and
  //              a list of crafting requirements.
  // Preconditions: ‘name’ must be a valid, non-empty string;
  //                ‘requirements’ must contain valid item names.
  // Postconditions: m_name is initialized to name;
  //                 m_req is initialized to a copy of requirements.
  Item(const string& name, const vector<string>& requirements);
  // Name: GetName()
  // Description: Retrieves the name of this item.
  // Preconditions: None.
  // Postconditions: Returns the value of m_name.
  string GetName() const;
  // Name: GetReq()
  // Description: Retrieves the list of crafting requirements for this item.
  // Preconditions: None.
  // Postconditions: Returns a const reference to m_req
  //                 (the requirements vector).
  const vector<string>& GetReq() const;
private:
  string m_name;        // Name of item
  vector<string> m_req; // Requirements by value
};
#endif
