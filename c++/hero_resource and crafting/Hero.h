/*Title: Hero.h
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: This class defines the hero
*/

#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "Map.cpp"
using namespace std;

//The class that describes the hero!

//Constants
//Things that can be found in an area
const vector<string> RawProducts = {"Copper Ore","Iron Ore","Coal","Gemstone"};
const vector<string> NaturalProducts = {"Log","Oak Log","Flax","Herb"};
const vector<string> FoodProducts = {"Raw Fish","Grain","Vegetable","Meat"};
const vector<string> HuntProducts = {"Bone","Leather","Hide","Claw"};

class Hero {
 public:
  // Name: Hero(const string& name)
  // Description: Constructs a new Hero with the specified name.
  // Preconditions: name must be a valid, non‐empty string.
  // Postconditions: m_name is initialized; inventory map is empty.
  Hero(const string& name);
  // Name: ~Hero()
  // Description: Destructor for Hero.
  // Preconditions: None.
  // Postconditions: Releases any dynamically allocated items in Hero.
  //                 None in this case.
  ~Hero();
  // Name: GetName()
  // Description: Retrieves the hero’s name.
  // Preconditions: None.
  // Postconditions: Returns the value of m_name.
  string GetName() const;
  // Name: SetName(const string& name)
  // Description: Updates the hero’s name.
  // Preconditions: name must be a valid string.
  // Postconditions: m_name is set to the new value.
  void SetName(const string& name);
  // Name: DisplayInventory()
  // Description: Prints the hero’s current inventory using overloaded << operator
  // Preconditions: Inventory map has been initialized.
  // Postconditions: Inventory contents are displayed.
  void DisplayInventory() const;
  // Name: CollectItem(const string& item)
  // Description: If the item exists, in m_inventory, uses Update to increment quantity
  //              If the item does not exist in m_inventory, inserts it.
  // Preconditions: item must be a valid item name.
  // Postconditions: Inventory count for item is incremented by 1.
  // Note: Uses try and catch (const out_of_range&) and inserts if caught.
  void CollectItem(const string& item);
  // Name: CanCraft(const vector<string>& requirements)
  // Description: Iterators through the requirements to see if they have quantity in m_inventory
  // Preconditions: Requirements vector populated with item names.
  // Postconditions: Returns true if every required item has count ≥1.
  // Note: Uses try and catch (const out_of_range&) and returns false if caught.
  bool CanCraft(const vector<string>& requirements) const;
  // Name: Craft(const string& result, const vector<string>& requirements)
  // Description: Consumes the listed requirements and adds the
  //              crafted "result" (iterates through requirements and Updates)
  // Preconditions: Call to CanCraft(requirements) must return true.
  // Postconditions: Each requirement’s count is decremented by 1;
  //                 Result of crafting is added.
  void Craft(const string& result, const vector<string>& requirements);
  // Name: Raw()
  // Description: Simulates mining for raw materials. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random raw material
  //                 to inventory or reports none found.
  void Raw();
  // Name: Natural()
  // Description: Simulates foraging for natural resources. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random natural resource
  //                 or reports none found.
  void Natural();
  // Name: Food()
  // Description: Simulates gathering food items. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random food item or reports none found.
  void Food();
  // Name: Hunt()
  // Description: Simulates hunting for creature drops. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random creature drop
  //                 or reports none found.
  void Hunt();  
private:
  // Name: Gather
  // Description: Randomly selects an item from vector products passed.
  //              If selection equals list size, prints 'noItemMsg';
  //              otherwise prints foundMsg + item and adds it
  //              to the hero's inventory.
  // Preconditions: 'products' must contain valid item names.
  // Postconditions: Inventory is incremented for the selected
  //               item if found; message printed.
  void Gather(const vector<string>& products, const string& noItemMsg,
	      const string& foundMsg);
  string m_name; //Name of the hero
  Map<string,int> m_inventory; //Inventory of items
};
#endif
