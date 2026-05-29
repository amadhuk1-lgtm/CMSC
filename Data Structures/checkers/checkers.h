// /*****************************************                                                                                                                
// ** File:    checkers.h                                                                                                                                    
// ** Project: CMSC 341 Project 0, Fall 2025                                                                                                                 
// ** Author:  Akanksha Madhu Kiran                                                                                                                                    
// ** Date:    09/09/2025                                                                                                                                    
// ** E-mail:  amadhuk1@umbc.edu                                                                                                                           
// ** This file contains the implementation of checkers and its Functions                                                                            
// ***********************************************/     
#ifndef CHECKERS_H
#define CHECKERS_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class

// the following define statemetns are used for graphical representation
#define WDISK   "\033[7mWD\033[0m" // represents white disk
#define BDISK   "\033[7mBD\033[0m" // represents black disk
#define WKING   "\033[7mWK\033[0m" // represents white king
#define BKING   "\033[7mBK\033[0m" // represents black king
#define WCELL   "  "               // represents white cell
#define BCELL   "\033[7m  \033[0m" // represents black cell
#define DEFBOARDSIZE 8             // default board size is 8 x 8
enum PLAYER {WPLAYER, BPLAYER, NONE};
typedef string CELL;

class Checkers{
    public:
    friend class Grader;
    friend class Tester;
    Checkers();
    Checkers(int rows, int columns);
    ~Checkers();
    void clear();
    bool initBoard();   // creates the board
    bool initGame();    // creates the initial state of disks
    // the following creates a board with the provided state of disks
    bool setGameState(CELL game[], int n, PLAYER player);
    bool play(pair<int,int> origin, pair<int,int> destination);
    void dumpGame();  // for debugging purposes
    void reportLostDisks();  // reports current number of lost disks per player
    
    private:
    int m_numRows;// can be any size
    int m_numColumns;//can be any size
    CELL ** m_game;// the 2d structure to store game information
    PLAYER m_currPlayer;
    int m_whiteDisks;//number of current white disks
    int m_blackDisks;//number of current black disks

    /******************************************
    * Private function declarations go here! *
    ******************************************/

 
    void allocateBoard(int rows, int cols);   // allocate memory for board

    bool inBounds(int row, int col) const;    // check if indices are valid
    bool isEmpty(int row, int col) const;     // check if cell is empty

    bool isWhitePiece(const CELL &piece) const;//checks if white piece
    bool isBlackPiece(const CELL &piece) const;//checks if black piece
    bool isKing(const CELL &piece) const;//checks if the piece is king

    bool validMove(pair<int,int> origin, pair<int,int> destination) const;//checks move
    bool validJump(pair<int,int> origin, pair<int,int> destination) const;//checks jump

    void makeMove(pair<int,int> origin, pair<int,int> destination); // executes move
    void capturePiece(int row, int col); // removes captured piece
    void crownKing(int row, int col); // promote disk to king if reached opposite side
    void switchPlayer(); // taking turns between players

    // Disk counting
    void updateDiskCounts();             // counting/updating number of disks
    
};
#endif
