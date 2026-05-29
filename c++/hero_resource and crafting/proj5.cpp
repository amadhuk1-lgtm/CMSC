#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
  if( argc != 3) {
    cout << "This requires a map file and a craft file to be loaded." << endl;
    cout << "Usage: ./proj5 proj5_map1.txt proj5_craft.txt" << endl;
  }

  cout << "Loading file: " << argv[1] << endl << endl;

  string mapName = argv[1];
  string craftName = argv[2];
  srand (time(NULL));
  Game g(mapName, craftName);
  g.StartGame();
  return 0;
}
