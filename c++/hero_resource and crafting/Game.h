/*Title: Game.h
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: This class defines the game
*/
#ifndef GAME_H //Header guards
#define GAME_H //Header guards

//Includes of required classes
#include "Area.h"
#include "Hero.h"
#include "Item.h"

//Includes of required libraries
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//************************Constants*********************
//GAME CONSTANTS
const int START_AREA = 0; //starting area number
const char DELIMITER = '|'; //delimiter for input file (map file)

class Game {
public:
  // Name: Game(string filename) - Overloaded Constructor
  // Description: Creates a new Game
  // Preconditions: None
  // Postconditions: Initializes all game variables to defaults (constants)
  // including m_myHero (null), mapFile (passed value), craftFile (passed)
  // and starting area (START_AREA)
  Game(string, string);
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated
  //                 in Game
  ~Game();
  // Name: LoadMap()
  // Description: Reads area data from the map file and dynamically
  //             creates Area objects. Inserts each new Area into
  //             m_myMap in the order encountered.
  // Preconditions: m_mapFile is set to a valid filename;
  //             the file exists and is formatted correctly.
  // Postconditions: m_myMap contains all loaded Area pointers;
  //             file stream is closed.
  void LoadMap();
  // Name: LoadCraft()
  // Description: Reads crafting definitions from the craft file and
  //              creates Item objects. Parses each line into an
  //              item name and its requirement list.
  // Preconditions: m_craftFile is set to a valid filename;
  //              the file exists and uses DELIMITER.
  // Postconditions: m_items contains new Item pointers for
  //              every recipe; file stream is closed.
  void LoadCraft();
  // Name: HeroCreation()
  // Description: Prompts the player to enter a hero name and
  //              constructs a new Hero.
  // Preconditions: Standard input (cin) is available.
  // Postconditions: m_myHero points to a newly allocated Hero
  //              with the entered name.
  void HeroCreation();
  // Name: Look()
  // Description: Displays the current Area’s name, description,
  //              and possible exits.
  // Preconditions: m_curArea is a valid index into m_myMap.
  // Postconditions: Current area details are printed to stdout.
  void Look();
  // Name: StartGame()
  // Description: Initializes game flow by loading map and crafting
  //              data, creating the hero, then showing the
  //              starting area and entering the main loop.
  // Preconditions: m_mapFile and m_craftFile are set; files exist.
  // Postconditions: Game state is initialized and Action() is called.
  void StartGame();
  // Name: Action()
  // Description: Presents the player with the main menu
  //              (Look, Move, Use Area, Craft, Inventory, Quit)
  //              and drives game interactions until the player quits.
  // Preconditions: Hero and map are initialized.
  // Postconditions: Continues looping until user selects Quit.
  void Action();
  // Name: Move()
  // Description: Prompts the player for a direction (N/E/S/W),
  //              validates the move, updates m_curArea, and
  //              calls Look() to show the new area.
  // Preconditions: m_curArea is valid; m_myMap contains
  //              adjacent Area pointers.
  // Postconditions: m_curArea is updated to the new area index.
  void Move();
  // Name: CraftItem()
  // Description: Displays all craftable items, prompts for a selection,
  //              and attempts crafting via Hero’s CanCraft/Craft methods.
  // Preconditions: m_items is populated with Item pointers.
  // Postconditions: If crafting succeeds, inventory is
  //              updated; otherwise prints error.
  void CraftItem();
  // Name: UseArea()
  // Description: Prompts the player to choose a search action
  //              (Raw, Natural, Food, Hunt)
  //              and forwards that request to the Hero.
  // Preconditions: Hero exists and has methods Raw/Natural/Food/Hunt.
  // Postconditions: One gather action is performed and the result printed.
  void UseArea();
private:
  Hero* m_myHero; // Hero pointer for Hero (Player)
  vector<Area*> m_areas; // Vector for holding all areas in game
  int m_curArea; // Current area that player (Hero) is in
  vector<Item*> m_items; // Vector of all craftable items
  string m_craftFile; // Name of the input file for the craftable items
  string m_areaFile; // Name of the input file for the 
};

#endif
