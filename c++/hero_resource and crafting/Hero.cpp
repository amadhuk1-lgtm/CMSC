//*****************************************************************************************
//File:     Hero.cpp
//Project:  CMSC 202 Project 5, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     05/01/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play a game that includes a hero who gathers resources and crafting items
//*****************************************************************************************

#include "Hero.h"

// Name: Hero(const string& name)
// Description: Constructs a new Hero with the specified name.
// Preconditions: name must be a valid, non‐empty string.
// Postconditions: m_name is initialized; inventory map is empty.
Hero:: Hero(const string& name){
  m_name = name;//sets hero name
}
  
// Name: ~Hero()
// Description: Destructor for Hero.
// Preconditions: None.
// Postconditions: Releases any dynamically allocated items in Hero.
//                 None in this case.
Hero::~Hero(){
}

// Name: GetName()
// Description: Retrieves the hero’s name.
// Preconditions: None.
// Postconditions: Returns the value of m_name.
string Hero::GetName() const {
    return m_name;//gets hero name
}

// Name: SetName(const string& name)
// Description: Updates the hero’s name.
// Preconditions: name must be a valid string.
// Postconditions: m_name is set to the new value.
void Hero::SetName(const string& name) {
  m_name = name;
}


// Name: DisplayInventory()
// Description: Prints the hero’s current inventory using overloaded << operator
// Preconditions: Inventory map has been initialized.
// Postconditions: Inventory contents are displayed.
void Hero::DisplayInventory() const {
  cout << m_inventory << endl;//displays all inventory player has found/created

}


// Name: CollectItem(const string& item)
// Description: If the item exists, in m_inventory, uses Update to increment quantity
//              If the item does not exist in m_inventory, inserts it.
// Preconditions: item must be a valid item name.
// Postconditions: Inventory count for item is incremented by 1.
// Note: Uses try and catch (const out_of_range&) and inserts if caught.
void Hero::CollectItem(const string& item) {
  try {
      int value = m_inventory.ValueAt(item);//gets current quantity of item
      m_inventory.Update(item,value+1);//updates item quantity if found what you already had searched for
    } catch (const out_of_range&) {
        m_inventory.Insert(item,1);//adds the new item you got and says you have 1 of that inventory.
      }
  }
  


// Name: CanCraft(const vector<string>& requirements)
// Description: Iterators through the requirements to see if they have quantity in m_inventory
// Preconditions: Requirements vector populated with item names.
// Postconditions: Returns true if every required item has count ≥1.
// Note: Uses try and catch (const out_of_range&) and returns false if caught.
bool Hero::CanCraft(const vector<string>& requirements) const {
  unsigned int count = 0;
  for(unsigned int i = 0; i < requirements.size(); i++){
      try {
        if(m_inventory.ValueAt(requirements[i]) >= 1){//checks if the requirement is met or not
          count++;
        } 
        }catch (const out_of_range&) {
          return false;//checks if item is found or not

        }
      }
  if (count == requirements.size()){
    return true;//only returns true if all rquirements are satisfied
  } else{
    return false;
  }
}

// Name: Craft(const string& result, const vector<string>& requirements)
// Description: Consumes the listed requirements and adds the
//              crafted "result" (iterates through requirements and Updates)
// Preconditions: Call to CanCraft(requirements) must return true.
// Postconditions: Each requirement’s count is decremented by 1;
//                 Result of crafting is added.
void Hero::Craft(const string& result, const vector<string>& requirements) {
  for(unsigned int i = 0; i < requirements.size(); i++){//loops through the requirements
      int quan = m_inventory.ValueAt(requirements[i]);//gets current quantity of item in the inventory
      m_inventory.Update(requirements[i],quan - 1);//reduces it by 1 to show that you used it to craft something
  }
  try{
    int isThere = m_inventory.ValueAt(result);//gets the quantity of an inventory crafted
    m_inventory.Update(result, isThere + 1);//adds one to the quantity if already exists
    } catch (const out_of_range&) {
    m_inventory.Insert(result, 1);//if it does not exists already it inserts it to the inventory
  }
}


// Name: Raw()
// Description: Simulates mining for raw materials. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random raw material
//                 to inventory or reports none found
void Hero::Raw() {
    Gather(RawProducts,"You searched and found nothing.", "You mined and found some ");//searches for Raw materials and says you found something or not(randomized).
}

// Name: Natural()
// Description: Simulates foraging for natural resources. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random natural resource
//                 or reports none found.
void Hero::Natural() {
  Gather(NaturalProducts,"You searched and found nothing.", "You searched and harvested some ");//searches for Natural resources and says you found something or not(randomized).
}

// Name: Food()
// Description: Simulates gathering food items. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random food item or reports none found.
void Hero::Food() {
  Gather(FoodProducts,"You searched and found nothing.", "You searched and harvested some ");//searches for food and says you found something or not(randomized).
}

// Name: Hunt()
// Description: Simulates hunting for creature drops. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random creature drop
//                 or reports none found.
void Hero::Hunt() {
  Gather(HuntProducts,"You searched and found nothing.", "You went hunting and got some ");//hunts and says you found something or not(randomized).
}

// Name: Gather
// Description: Randomly selects an item from vector products passed.
//              If selection equals list size, prints 'noItemMsg';
//              otherwise prints foundMsg + item and adds it
//              to the hero's inventory.
// Preconditions: 'products' must contain valid item names.
// Postconditions: Inventory is incremented for the selected
//               item if found; message printed.
void Hero::Gather(const vector<string>& products, const string& noItemMsg,
                  const string& foundMsg) {
  unsigned int prod = rand() % (products.size()+1); // Selects a random index
  if(prod == products.size()){//considering the last option as the one where you don't find anything
    cout << noItemMsg << endl; //prints not found message
  }else{
    string key = products[prod]; // Gets the item at the random index
    cout << foundMsg + key << "!" << endl; // Prints the found message
    CollectItem(key); // Adds the item to inventory
  }
}

