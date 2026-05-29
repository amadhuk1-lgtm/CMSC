//*****************************************************************************************
//File:     Game.cpp
//Project:  CMSC 202 Project 2, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     03/10/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play Doodle God.
//Thi is the extra credit
//*****************************************************************************************

#include "Game.h"
// Name: Game() Default Constructor
// Preconditions - None
// Postconditions - None
// Desc - Empty default constructor
Game::Game() {
    for (int i = 0; i < PROJ2_SIZE; ++i) {
        m_elements[i] = Element(); //initializing array to empty spaces
    }
}

// Name: LoadRecipes
// Preconditions - Requires file with valid element/recipe data
// Postconditions - m_elements is populated with valid recipe data
// Desc - A recipe is what elements are required to merge in order to create a new element
//        For example, if you merge Fire and Earth, you get Lava.
//        Loads each recipe from provided file (Must use getline)
void Game::LoadRecipes() {
    ifstream file("proj2_recipes.txt"); // Open the file to get the elements
    if (file.is_open()) { 
        string name;
        string elem1;
        string elem2;
        int counter = 0;

        while (counter < PROJ2_SIZE) { 
            getline(file, name, ','); // Reading the elements
            getline(file, elem1, ','); 
            getline(file, elem2, '\n');

            if (elem1.empty() && elem2.empty()) { // Creating an element with the name and empty spaces
                Element newElement(name, "", ""); // making a copy
                m_elements[counter] = Element(name, elem1, elem2); // Creating an Element with the name and the combinations made for it
            } else {
                m_elements[counter] = Element(name, elem1, elem2);
            }
            counter++;//checking this for each element in the upcoming lines
        }
        file.close(); // Closing the file
    } 
}


// Name: StartGame()
// Preconditions - None
// Postconditions - Continually checks to see if player has quit
// Desc: 1. Loads all recipes into m_elements (by making elements)
//       2. Asks user for their DoodleGod's name
//          (store in m_myDoodleGod as m_myName)
//       3. Adds Fire, Water, Air, and Earth to Doodle God's known element list
//	      (in m_myDoodleGod)
//       4. Manages the game itself including win conditions continually
//         calling the main menu.
void Game::StartGame() {
    string playerName;
    
    LoadRecipes();// loading the recipes

    GameTitle(); // Displays the title
    cout << PROJ2_SIZE << " recipes loaded." << endl;
    cout << "What is the name of the Doodle God?"<< endl; //asking for the name of the doodle god
    getline(cin, playerName);//storing it in a variable playerName

    m_myDoodleGod.SetName(playerName);// setting the name in m_myDoodleGod, basically saving it


    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_elements[i].m_name == "Air" || m_elements[i].m_name == "Earth" || m_elements[i].m_name == "Fire" || m_elements[i].m_name == "Water") { //so that these elements are added to the known elements
        m_myDoodleGod.AddElement(&m_elements[i]);  // Storing the reference to prevent making unecessary copies
        }
    }
    //the game loop

        MainMenu();
}


// Name: DisplayMyElements()
// Preconditions - Player has elements
// Postconditions - Displays a numbered list of elements
// Desc - Displays the current elements
void Game::DisplayElements() {
    int numElements = m_myDoodleGod.GetNumElements(); // Get the count of known elements

    for (int i = 0; i < numElements; ++i) {
        Element* element = m_myDoodleGod.GetElement(i); //gets back the element from m_myDoodleGod, stores address

        // Checking if the element is valid
        if (element != nullptr && !element->m_name.empty()) {   
            cout << i + 1 << ". " << element->m_name << endl; // displaying the known elements in a format
        }
    }
}


// Name: MainMenu()
// Preconditions - Player has an DoodleGod
// Postconditions - Returns number including exit
// Desc - Displays and manages menu      
int Game::MainMenu() {
    int choice = 0;
    string boardGod[PROJ2_SIZE] = {};//creating an empty array
    bool flag = true;

    while(flag){
    //to keep asking until chosen to quit
        cout << "What would you like to do? "<< endl;
        cout << "1. Display the Doodle God's elements" << endl;
        cout << "2. Attempt to Combine Elements" << endl;
        cout << "3. See Score" << endl;
        cout << "4. Quit"<< endl;
        cin >> choice; //store the choice being made

        switch(choice) {
            case 1:{
                DisplayElements();//to display the elements known that you can use to combine
                break;
            }
            case 2:{
                CombineElements();//to combine elements
                break;
            }
            case 3:{
                CalcScore();//to calculate the score
                break;
            }
            case 4:{
                cout << "Thanks for playing the Doodle God!" << endl;
                flag = false; //to get out of the loop if you end the game
                break;
            }
            default:{
                cout << "Invalid choice. Please enter 1, 2, 3, or 4." << endl; //to check if it is a valid choice and loop through again
                break;
            }
        }
    }
    return 0;
}


// Name: CombineElements()
// Preconditions - DoodleGod is populated with elements
// Postconditions - May add element to DoodleGod's list of elements
// Desc - Attempts to combine known elements
void Game::CombineElements() {
    int selection1 = 0;
    int selection2 = 0;
    RequestElement(selection1); //to ask the user for selection 1
    RequestElement(selection2); //to ask the user for selection 2

    Element* elem1 = m_myDoodleGod.GetElement(selection1 - 1); //storing the pointer that points to element 1 as elem1
    Element* elem2 = m_myDoodleGod.GetElement(selection2 - 1);

    int index = SearchRecipes(elem1->m_name, elem2->m_name); //elem1 and elem2 are pointers and here the string stored in these memories are passed
    if (index != -1) {
        Element* newElement = &m_elements[index]; // Create a copy of the new element

        if (!m_myDoodleGod.CheckElement(newElement)) {  // Check if the element is not already added
            m_myDoodleGod.AddElement(newElement);  // Add the new element

            cout << elem1->m_name << " combined with " << elem2->m_name << " to make " << newElement->m_name << "!" << endl;
            cout << "The Doodle God now knows " << newElement->m_name << "." << endl;
        } 
        else {
            cout << newElement->m_name << " already known." << endl;
            m_myDoodleGod.AddRepeat();  // Increment repeat count
        }
    } else {
        cout << "Nothing happened when you tried to combine " << elem1->m_name << " and " << elem2->m_name << "." << endl;
    }
    m_myDoodleGod.AddAttempt();  // Increment attempt count
}

// Name: RequestElement()
// Preconditions - DoodleGod has elements to try and merge
// Postconditions - Updates choice (pass by reference)
// Desc - Asks user to chose an element to try and merge.
//        Checks to make sure value in range
void Game::RequestElement(int &choice) {
    bool validSelection = true;
    do{//to run it atleats once
        cout << "Which elements would you like to merge?" << endl;//to ask the choice of player of what element they want to merge
        cout << "To list known elements enter -1" << endl;
        cin >> choice;
        if (choice == -1) {
             DisplayElements();//to display elements known
        }else{
            if (choice < 1 || choice > m_myDoodleGod.GetNumElements()) { //to check if choice made is valid
                   cout << "Invalid selection. Please enter valid element numbers." << endl;
            } else{
                validSelection = false;//to not run the loop again if valid selection
            }
            
        }
    }while (validSelection);//to loop through and keep asking until valid choice made
}


// Name: SearchRecipes()
// Preconditions - m_elements is populated
// Postconditions - Returns int index of matching recipe
// Desc - Searches recipes for two strings passed
int Game::SearchRecipes(string elem1, string elem2) {
    int k = -1;
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_elements[i].m_element1 == elem1 && m_elements[i].m_element2 == elem2){ //to search for elements the player entered
            k = i;
        }
        if (m_elements[i].m_element1 == elem2 && m_elements[i].m_element2 == elem1) { //to do the same but in reverse order because its possible
            k = i;
        }
    }
    return k;
}



// Name: CalcScore()
// Preconditions - Doodle God is populated with elements
// Postconditions - None
// Desc - Displays current score for Doodle God
void Game::CalcScore() {
    int totalElements = PROJ2_SIZE;
    string name = m_myDoodleGod.GetName();//to get the name
    int knownElements = m_myDoodleGod.GetNumElements(); //to get the number of elements found by counting in array
    int attempts = m_myDoodleGod.GetAttempts();//to get the number of attempts
    int repeats = m_myDoodleGod.GetRepeats();//to get the number of repeats

    double percentage = (double(knownElements) / totalElements) * 100;//to calcultae the percentage of elements found

    cout << "***The Doodle God***" << endl;
    cout << "The Great Doodle God " << name << endl;
    cout << "The Doodle God has tried to combine " << attempts << " elements" << endl;
    cout << "The Doodle God has repeated attempts " << repeats << " times" << endl;
    cout << "The Doodle God has found " << knownElements << " out of " << totalElements << " elements." << endl;
    cout << "You have completed " << fixed << setprecision(2) << percentage << "%" << " of the elements." << endl;//setting the digits after the decimal point as 2
}

