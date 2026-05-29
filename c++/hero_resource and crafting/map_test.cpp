#include <iostream>
#include <string>
using namespace std;
#include "Map.cpp"

// To test just map follow these instructions:
//   1. make mtest
//   2. make mtest2
// This tests some of the important functions in Map.
// You should add additional tests to make sure everything in the class works.
// During grading, we will test all functions in the Map class.

int main () {
  try{ //Tries to complete testing.
    //Test 1 - Default Constructor, Insert, and Display
    cout << "Test 1 - Default Constructor, Push, and Display Test" << endl;
    //Test Default Constructor
    Map <int, int> *newMap1 = new Map <int, int>(); //Creates new empty Map
    //Test exception handling (comment out when not used)
    //cout << *newMap1->At(30) << endl;
    //Push 3 nodes into Map
    newMap1->Insert(20, 2); //Inserts first node
    newMap1->Insert(30, 3); //Inserts new last node
    newMap1->Insert(10, 1); //Inserts new first node
    cout << "Should display 10:1 then 20:2 then 30:3" << endl;
    newMap1->Display(); //Displays all three nodes in Map
    cout << "End Test 1 - Constructor, Push, and Display Test" << endl << endl;
    
    //Test 2 - Copy Constructor
    cout << "Test 2 - Copy Constructor Running" << endl;
    //Test Copy constructor
    Map <int,int> *newMap2 = new Map <int,int>(*newMap1); //Calls copy constructor
    newMap2->Display(); //Displays all three nodes in new map
    cout << "size below should match. Location should not" << endl;
    cout << "Source size: " << newMap1->GetSize() << " and Copied size: "
	 << newMap2->GetSize() << endl;
    cout << "Source location: " << &newMap1 << " and Copied location: " << &newMap2 << endl;
    cout << "End Test 2 - Copy Constructor" << endl << endl;
    
    //Test 3 - Overloaded Assignment Operator
    cout << "Test 3 - Overloaded Assignment Operator Running" << endl;
    //Create new Stack using constructor
    Map <int,int> *newMap3 = new Map <int,int>(); //Creates new Map using default constructor
    //Update using overloaded assignment operator
    *newMap3 = *newMap1; //Calls overloaded assignment operator
    newMap3->Display(); //Display all three nodes in map
    cout << "size below should match. Location should not" << endl;
    cout << "Source size: " << newMap1->GetSize() << " and Assigned size: "
	 << newMap3->GetSize() << endl;
    cout << "Source location: " << &newMap1 << " and Assigned location: " << &newMap3 << endl;
    cout << "End Test 3 - Assignment" << endl << endl;
    
    //Test 4 - Test Update
    cout << "Test 4 - Update" << endl;
    cout << "size before: " << newMap1->GetSize() << " " << endl;
    newMap1->Display(); //Displays all three nodes in map before updating them (10:1, 20:2, 30:3)
    newMap1->Update(10,10); //Updates key 10 to value 10
    newMap1->Update(20,20); //Updates key 20 to value 20
    newMap1->Update(30,30); //Updates key 20 to value 30
    cout << "size after: " << newMap1->GetSize() << endl;
    cout << "Should display 10:10 then 20:20 then 30:30" << endl;
    newMap1->Display(); //Displays all three updated values
    cout << "End Test 4 - Update" << endl << endl;
    
    //Test 5 - Test Destructor
    cout << "Test 5 - Test Destructor" << endl;
    cout << "delete newMap1" << endl;
    delete newMap1;
    newMap1 = nullptr;
    cout << "delete newMap2" << endl;
    delete newMap2;
    newMap2 = nullptr;
    cout << "delete newMap3" << endl;
    delete newMap3;
    newMap3 = nullptr;
    cout << "End Test 5 - Destructors" << endl;
  } catch (const out_of_range& e) { //Catches any exceptions thrown from empty Map
    cerr << "Exception caught: " << e.what() << endl; //Displays exception
  }
  return 0;
}
