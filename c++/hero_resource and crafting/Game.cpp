//*****************************************************************************************
//File:     Game.cpp
//Project:  CMSC 202 Project 5, Spring 2025
//Author:   Akanksha Madhu Kiran
//Date:     05/01/2025
//Section:  40/42
//E-mail:   amadhuk1@umbc.edu
//This file helps the user to play a game that includes a hero who gathers resources and crafting items
//*****************************************************************************************

#include "Game.h"

// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including m_myHero (null), mapFile (passed value), craftFile (passed)
// and starting area (START_AREA)
Game::Game(string areaFile, string craftFile) {
    m_areaFile = areaFile;
    m_craftFile = craftFile; 
    m_myHero = nullptr;//initializes all game variables to defaults
}

// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated
//                 in Game
Game::~Game() {
    for(unsigned int i = 0; i < m_areas.size(); i++){//loops though the vector
        delete m_areas[i];//vector is emptied
        m_areas[i] = nullptr;
    }
    for(unsigned int i = 0; i < m_items.size(); i++){//loops though the vector
        delete m_items[i];//vector is emptied
        m_items[i] = nullptr;//for safety of any memory leak
    }
    delete m_myHero;//frees memory of m_myHero
    m_myHero = nullptr;
}

// Name: LoadMap()
// Description: Reads area data from the map file and dynamically
//             creates Area objects. Inserts each new Area into
//             m_myMap in the order encountered.
// Preconditions: m_mapFile is set to a valid filename;
//             the file exists and is formatted correctly.
// Postconditions: m_myMap contains all loaded Area pointers;
//             file stream is closed.
void Game::LoadMap() {
    
    ifstream inFile(m_areaFile);//opens inputed file
    
    if (!inFile.is_open()) {//checks if file is open
        cout << "Error: Could not open area file." << endl;
        return; // exits the void function safely if eroor in opening file
    }

    string location;
    string areaName;
    string message;
    string north, east, south, west;

    while (getline(inFile, location, DELIMITER)&&
        getline(inFile, areaName, DELIMITER)&&
        getline(inFile, message, DELIMITER)&&
        getline(inFile,north,DELIMITER )&&
        getline(inFile,east,DELIMITER )&&
        getline(inFile,south,DELIMITER)&&
        getline(inFile,west,DELIMITER)) { //gets each info in the file including space

        int loc,nor,eas,sou,wes;
        loc = stoi(location);
        nor = stoi(north);
        sou = stoi(south);
        eas = stoi(east);
        wes = stoi(west);

        Area* newArea = new Area(loc, areaName, message, nor, eas, sou, wes);//creates newArea object to keep data from file
        m_areas.push_back(newArea);//adds the area to vector
    }
    inFile.close();//closes file
    if (!m_areas.empty()) {//makes current area 0 is empty
        m_curArea = 0;
    } else{
        m_curArea = START_AREA;//if not empty current area is START_AREA constant
    }
}



// Name: LoadCraft()
// Description: Reads crafting definitions from the craft file and
//              creates Item objects. Parses each line into an
//              item name and its requirement list.
// Preconditions: m_craftFile is set to a valid filename;
//              the file exists and uses DELIMITER.
// Postconditions: m_items contains new Item pointers for
//              every recipe; file stream is closed.
void Game::LoadCraft() {
    ifstream inFile(m_craftFile);//opens inputed file
    if (!inFile.is_open()) {//checks if file can be opened or not
        cout << "Error: Could not open craft file." << endl;
        return; // exits the void function safely
    }

    string createName;
    string requirement1,requirement2,requirement3,requirement4,space;
    
    vector < string > req; 
        while (getline(inFile, createName, DELIMITER)&&
            getline(inFile,requirement1, DELIMITER)&&
            getline(inFile,requirement2, DELIMITER)&&
            getline(inFile,requirement3,DELIMITER )&&
            getline(inFile,requirement4,DELIMITER )&&
            getline(inFile,space)) {  //gets each info in the file including the space

            
            if(requirement1 != "None"){
                req.push_back(requirement1);//only if the requirement is not NONE then it gets added to vector req
            }
            if(requirement2 != "None"){
                req.push_back(requirement2);
            }
            if(requirement3 != "None"){
                req.push_back(requirement3);
            }
            if(requirement4 != "None"){
                req.push_back(requirement4);
            }
            Item* newItem = new Item(createName,req);//creates new Item and adds it to the list
            m_items.push_back(newItem);   
            req.clear();//clears requirements to go to next set of items
        }
        inFile.close();//closes file
    }



// Name: HeroCreation()
// Description: Prompts the player to enter a hero name and
//              constructs a new Hero.
// Preconditions: Standard input (cin) is available.
// Postconditions: m_myHero points to a newly allocated Hero
//              with the entered name.
void Game::HeroCreation() {
    if (m_myHero != nullptr) {
        delete m_myHero;// deleting any previous created hero
        m_myHero = nullptr;
    }
    string name = "";
    cout << "Enter your hero name: ";//asks the hero name
    cin >> name;
    m_myHero = new Hero(name);//creates hero for the new name
}

// Name: Look()
// Description: Displays the current Area’s name, description,
//              and possible exits.
// Preconditions: m_curArea is a valid index into m_myMap.
// Postconditions: Current area details are printed to stdout.
void Game::Look() {
    m_areas[m_curArea]->PrintArea();//prints information of current area
}

// Name: StartGame()
// Description: Initializes game flow by loading map and crafting
//              data, creating the hero, then showing the
//              starting area and entering the main loop.
// Preconditions: m_mapFile and m_craftFile are set; files exist.
// Postconditions: Game state is initialized and Action() is called.
void Game::StartGame() {
    cout << "Welcome to UMBC Runescape!" << endl;
    HeroCreation();// creates hero
    cout << "Hero Name: " << m_myHero->GetName() << "\n" << endl; //writes the hero name
    LoadMap();// loads the inputed map
    LoadCraft();//loads the craftfile
    Look();//looks where the player currently is located
    Action();//begins asking for players decision on what to do
}

// Name: Action()
// Description: Presents the player with the main menu
//              (Look, Move, Use Area, Craft, Inventory, Quit)
//              and drives game interactions until the player quits.
// Preconditions: Hero and map are initialized.
// Postconditions: Continues looping until user selects Quit.
void Game::Action() {
    int choice;
    do{//menu to ask what the player wants to do
        cout << "\n"<<"What would you like to do?" << endl;
        cout << "1. Look" << endl;
        cout << "2. Move" << endl;
        cout << "3. Use Area" << endl;
        cout << "4. Craft Item" << endl;
        cout << "5. Display Inventory" << endl;
        cout << "6. Quit" << endl;
        cin >> choice;

        switch(choice){
            case 1:{
                Look();//to print where player currently is
                break;
            }
            case 2:{
                Move();//to move to a different location
                break;
            }
            case 3:{
                UseArea();//to use area for several options
                break;
            }
            case 4:{
                CraftItem();//to create/craft an item
                break;
            }
            case 5:{
                cout << "******* INVENTORY *******" << endl;
                m_myHero->DisplayInventory();//displays what inventory the player has
                break;
            }
            case 6:{
                cout << "Good bye!"<< endl;//quits the game
                break;
            }
            default: 
                cout << "Invalid input. Please enter a valid value" << endl;
            }
        } while (choice != 6 || cin.fail()); // keeps looping until quit

}


// Name: Move()
// Description: Prompts the player for a direction (N/E/S/W),
//              validates the move, updates m_curArea, and
//              calls Look() to show the new area.
// Preconditions: m_curArea is valid; m_myMap contains
//              adjacent Area pointers.
// Postconditions: m_curArea is updated to the new area index.
void Game::Move() {
    char direction;
    cout << "Which direction? (N E S W)"<< endl;//to ask which direction the person wants to move
    cin >> direction;
    int newArea = m_areas[m_curArea]->CheckDirection(direction);//to check if the directiion enteerd is a valid option
    if (newArea != -1) {
        m_curArea = newArea;//to change the current area to the new area the person moved to
        Look();//to print description of the new place
    } else {
        cout << "Not a valid choice of direction.\n";
    }
}



// Name: CraftItem()
// Description: Displays all craftable items, prompts for a selection,
//              and attempts crafting via Hero’s CanCraft/Craft methods.
// Preconditions: m_items is populated with Item pointers.
// Postconditions: If crafting succeeds, inventory is
//              updated; otherwise prints error.
void Game::CraftItem() {
    int choice;
    cout << "What item would you like to craft?"<< endl;//to ask which item the player wants to craft
    for(unsigned i = 0; i < m_items.size(); i++){
        string itemName = m_items.at(i)->GetName();//to get name of items
        if (!itemName.empty()) { // Check if the item name is not empty and print items that are possible to be created
            cout << i+1 << ". " << itemName << endl;//prints them
            }
        }
      
    
    cin >> choice;
    unsigned size = m_items.size();
    if (choice >= 1 && (unsigned)choice <= size) {//to check if the choice of what to craft is made is valid
        Item* item = m_items[choice - 1];
        if (m_myHero->CanCraft(item->GetReq())) {//to check if requirements of the choice that needs to be crafted are fulfilled
            m_myHero->Craft(item->GetName(), item->GetReq());
            cout << "Crafted: " << item->GetName() << "!";
        } else {
            cout << "Cannot craft " << item->GetName() << ". Missing requirements.";
        }
    } else {
        cout << "Invalid selection." << endl;
    }
}


// Name: UseArea()
// Description: Prompts the player to choose a search action
//              (Raw, Natural, Food, Hunt)
//              and forwards that request to the Hero.
// Preconditions: Hero exists and has methods Raw/Natural/Food/Hunt.
// Postconditions: One gather action is performed and the result printed.

void Game::UseArea() {
    int choice;
    do{//main menu to ask player what to look for
        cout << "What would you like to look for?" << endl;
        cout << "1. Raw Materials (Mining)" << endl;
        cout << "2. Natural Resources (Woodcutting/Foraging)" << endl;
        cout << "3. Food (Fishing/Farming)" << endl;
        cout << "4. Hunt" << endl;
        cin >> choice;

        switch(choice){
            case 1:{
                m_myHero-> Raw();//to look for raw materials
                break;
            }
            case 2:{
                m_myHero-> Natural();//to look for natural resources
                break;
            }
            case 3:{
                m_myHero-> Food();//to look for food
                break;
            }
            case 4:{
                m_myHero-> Hunt();//to hunt
                break;
            }
            default: 
                cout << "Invalid input. Please enter a valid value" << endl;
            }
        } while (choice < 1 || choice > 4 || cin.fail()); // keeps looping until right choice is made

}
