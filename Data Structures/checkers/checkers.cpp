// /*****************************************                                                                                                                
// ** File:    checkers.cpp                                                                                                                                    
// ** Project: CMSC 341 Project 0, Fall 2025                                                                                                                 
// ** Author:  Akanksha Madhu Kiran                                                                                                                                    
// ** Date:    09/09/2025                                                                                                                                    
// ** E-mail:  amadhuk1@umbc.edu                                                                                                                           
// ** This file contains the implementation of checkers and its Functions                                                                            
// ***********************************************/           
#include "checkers.h"
#include <iostream>
using namespace std;

Checkers::Checkers(){
    m_game = nullptr;//initializes 2d array pointer to null pointer
    m_currPlayer = NONE;//current player as none, game still has not started
    m_whiteDisks = 0;//count of white disks initialize to 0
    m_blackDisks = 0;//count of black disks initialized to 0
    m_numRows = 0;//initialized number of rows to 0
    m_numColumns = 0;//initialized number of columns to 0
}

Checkers::Checkers(int rows, int columns){
    if(rows < DEFBOARDSIZE || columns < DEFBOARDSIZE || rows != columns || rows%2 != 0 || columns%2 != 0){//checking any invalid case of number of rows and columns
        m_numRows = 0;//initialized number of rows to 0
        m_numColumns = 0;//initialized number of columns to 0
        m_game = nullptr;//initializes 2d array pointer to null pointer
        m_currPlayer = NONE;//current player as none, game still has not started
        m_whiteDisks = 0;//count of white disks initialize to 0
        m_blackDisks = 0;//count of black disks initialized to 0
    }
    else{
        allocateBoard(rows, columns);//calls helper function to allocate the 2D game board
        m_currPlayer = BPLAYER;//starting player black
        m_whiteDisks = 0;
        m_blackDisks = 0;
        initBoard();//calls functon to set board squares
        initGame();//calls to place initial pieces onto board
    }
}

Checkers::~Checkers(){
    clear();//to free all dynamically allocated memory
}  

void Checkers::clear(){
    if (!m_game){//checks if board pointer is already null
        m_numRows = 0;//initializes everything to 0
        m_numColumns = 0;
        m_whiteDisks = 0;
        m_blackDisks = 0;
        m_currPlayer = NONE;
        return;
    }

    for (int r = 0; r < m_numRows; r++)//if its not null then deletes dynamically allocated array by looping through array
        delete [] m_game[r];//deleting memory allocated for that row
    delete [] m_game;//deletes array of row pointers

    m_game = nullptr;//sets board pointer to null
    m_whiteDisks = 0;//resets all member variables
    m_blackDisks = 0;
    m_numRows = 0;
    m_numColumns = 0;
    m_currPlayer = NONE; 
}

bool Checkers::initBoard(){
    if (!m_game || m_numRows <= 0 || m_numColumns <= 0){//returns true if board is not allocated
        return true; 
    }
    for (int r = 0; r < m_numRows; r++){//loops through array
        for (int c = 0; c < m_numColumns; c++){
            if ((r + c) % 2 == 0)
                m_game[r][c] = WCELL;//assigns white cell
            else
                m_game[r][c] = BCELL;//assigns black cell
        }
    }
    return true;//to indicate success
}

bool Checkers::initGame(){
    if (!m_game){//to ensure board exists
        return true;
    }
    initBoard(); //resets board to empty

    //White disks top 3 rows (placed on dark squares)
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < m_numColumns; c++){
            if ((r + c) % 2 == 1){
                m_game[r][c] = WDISK;
            }
        }
    }

    // Black disks bottom 3 rows
    for (int r = m_numRows - 3; r < m_numRows; r++){
        for (int c = 0; c < m_numColumns; c++){
            if ((r + c) % 2 == 1){
                m_game[r][c] = BDISK;
            }
        }
    }

    updateDiskCounts();//to count number of white and black disks
    m_currPlayer = BPLAYER;//starting player black.
    return true;
}

bool Checkers::play(pair<int,int> origin, pair<int,int> destination){
    if (!m_game){//checks if board exists
        return false;
    }
    if (!inBounds(origin.first, origin.second) || !inBounds(destination.first, destination.second)){//checks if move is on board
        return false;
    }

    CELL piece = m_game[origin.first][origin.second];//gets piece at origin
    if (piece.empty()){//checks if origin has piece
        return false;
    }

    //ensure it's the current player's piece
    if ((m_currPlayer == WPLAYER && !isWhitePiece(piece)) ||
        (m_currPlayer == BPLAYER && !isBlackPiece(piece))){
            return false;
        }

    if (!validMove(origin,destination)){//to check if move is legal
        return false;
    }

    makeMove(origin,destination);//executes move if valid
    return true;
}




bool Checkers::setGameState(CELL game[], int n, PLAYER player){

    if (!m_game) {//checks if board need to be allocated
        if (m_numRows == 0 || m_numColumns == 0){
            return false;//cannot allocate if dimensions are 0
        }
        allocateBoard(m_numRows, m_numColumns);//allocates board
        initBoard();//initializes blacnk board
    }
    if (n != m_numRows * m_numColumns){
        return false;//if size of array provided does not match board size.
    }

    for (int i = 0; i < m_numRows; ++i){//loops through array
        for (int j = 0; j < m_numColumns; ++j){
            int idx = i * m_numColumns + j;//gets index of 1d array
            //If empty string the cell is left as it is.
            if (game[idx].empty()) {
                //do nothing
            } else {
                m_game[i][j] = game[idx];//copies cell value
            }
        }
    }
    m_currPlayer = player;//sets current player
    updateDiskCounts();//updates count of disks
    return true;
}

void Checkers::reportLostDisks(){
    int white = 0;
    int black = 0;
    for (int r = 0; r < m_numRows; r++) {//loops through board
        for (int c = 0; c < m_numColumns; c++) {
            if (m_game[r][c] == WDISK){
                white++;//increments white disk count
            }
            else if (m_game[r][c] == BDISK){
                black++;//increments black disk counts
        }
    }
    }
    //checks starting number of disks
    int start = (m_numRows == DEFBOARDSIZE ? 12 : 20);
    cout << "White player lost disks: " << (start - white) << endl;//prints number of lost white disks
    cout << "Black player lost disks: " << (start - black) << endl;//prints number of lost black disks
   
}


void Checkers::dumpGame(){
    if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr){//checks if board is valid.
        cout << "  ";//printing spaces for alignment
        for (int k = 0; k < m_numColumns; ++k) cout << k << " ";
        cout << endl;
        for (int i = 0; i < m_numRows; ++i){
            cout << i << " ";
            for (int j = 0; j < m_numColumns; ++j){//looping through each column
                cout << m_game[i][j];//prints character representing cell's content
            }
            cout << endl;//moves to next line
        }
        cout << endl;//adds extra new line
    }
}




//Helper functions

void Checkers::allocateBoard(int rows, int cols){
    m_numRows = rows;//stores number of rows
    m_numColumns = cols;//stores number of columns
    m_game = new CELL*[m_numRows];//allocates an array of pointers
    for (int r = 0; r < m_numRows; r++) { //loops through array of pointers
            m_game[r] = new CELL[m_numColumns];      //for each pointer allocates an array of cell
        }
}


bool Checkers::inBounds(int r, int c) const{//checks if within dimension
    return r >=0 && r < m_numRows && c >=0 && c < m_numColumns;
}


bool Checkers::isEmpty(int r, int c) const{// Checks if a cell is empty (contains a black cell).
    if (!inBounds(r,c)){
        return false;//false if out of bounds
    }
    return m_game[r][c] == BCELL;
}

bool Checkers::isWhitePiece(const CELL &p) const{//checks if piece is white(disk or king)
    return p == WDISK || p == WKING;
}

bool Checkers::isBlackPiece(const CELL &p) const{//checks if piece is black(disk or king)
    return p == BDISK || p == BKING;
}

bool Checkers::isKing(const CELL &p) const{//checks if piece is king
    return p == WKING || p == BKING;
}

void Checkers::updateDiskCounts(){ // Updates the `m_whiteDisks` and `m_blackDisks` member variables.
    int w = 0;
    int b = 0;
    if (!m_game){//check for null board
        m_whiteDisks = 0;
        m_blackDisks = 0; 
        return; 
    }

    for (int i = 0; i < m_numRows; ++i){//loops through entire board
        for (int j = 0; j < m_numColumns; ++j){
            if (isWhitePiece(m_game[i][j])){
                ++w;//increments white disk
            }
            else if (isBlackPiece(m_game[i][j])){
                ++b;//increments black disk
            }
        }
    }
    m_whiteDisks = w;
    m_blackDisks = b;
}

bool Checkers::validMove(pair<int,int> origin, pair<int,int> destination) const{
    int r1 = origin.first;//gets origin row
    int c1 = origin.second;
    int r2 = destination.first; // Gets the destination row.
    int c2 = destination.second;

    if (!inBounds(r1,c1) || !inBounds(r2,c2)){//checks if in the bounds
        return false;
    }
    if (!isEmpty(r2,c2)){//checks if square is empty
        return false;
    }

    CELL piece = m_game[r1][c1];//gets piece at origin
    if (piece.empty()){//to check if piece exists at origin
        return false;
    }

    // non-king pieces move forward only
    int dir = isWhitePiece(piece) ? -1 : 1;//white moves up, decreasing. black moves down , increasing

    // simple diagonal move check
    if (r2 == r1 + dir && abs(c2 - c1) == 1){
        return true;
    }

    // kings can move one step either direction
    if (isKing(piece) && abs(r2 - r1) == 1 && abs(c2 - c1) == 1){
        return true;
    }

    //checks if valid jump
    if (validJump(origin, destination)){
        return true;
    }

    return false;//runs if move invalid
}

bool Checkers::validJump(pair<int,int> origin, pair<int,int> destination) const{
    int r1 = origin.first;//gets origin of row
    int c1 = origin.second;
    int r2 = destination.first;//gets destination of row
    int c2 = destination.second;

    if (!inBounds(r1,c1) || !inBounds(r2,c2)){//checks if in the bounds
        return false;
    }
    if (abs(r2-r1) != 2 || abs(c2-c1) != 2){//jump exactly two squares diagonal
        return false;
    }
    if (!isEmpty(r2,c2)){//destination empty check
        return false;
    }

    int rm = (r1 + r2)/2;
    int cm = (c1 + c2)/2;

    // middle must be opponent piece
    CELL middle = m_game[rm][cm];//gets piece of middle square
    if (middle.empty()){//checks if piece exists
        return false;
    }

    if (m_currPlayer == WPLAYER && isBlackPiece(middle)){
        return true;//capture success
    }
    if (m_currPlayer == BPLAYER && isWhitePiece(middle)){
        return true;//capture success
    }
    return false;
}

void Checkers::capturePiece(int r, int c){
    if (!inBounds(r,c)){//chack if in bounds
        return;
    }

    if (isWhitePiece(m_game[r][c])) {
        if (m_whiteDisks > 0) {
            --m_whiteDisks;//decrement white disk when captured
        }
    } else if (isBlackPiece(m_game[r][c])) {
        if (m_blackDisks > 0){
            --m_blackDisks;//decrements blackdisk when captured
        }
    }
    //restores the empty cell with the correct color
    m_game[r][c] = ((r+c)%2==0 ? WCELL : BCELL);
}

void Checkers::crownKing(int r, int c){//promotes disk to king
    if (!inBounds(r,c)){//checks if in bounds
        return;
    }
    CELL &p = m_game[r][c];//creates refernce to cell
    if (p == WDISK && r == 0){
        p = WKING;//white disk becomes king when it reaches 0
    }
    else if (p == BDISK && r == m_numRows-1){
        p = BKING;//black disk becomes king when reaches last row
    }
}

void Checkers::switchPlayer(){//makes player take turns
    m_currPlayer = (m_currPlayer == BPLAYER ? WPLAYER : BPLAYER);
}

void Checkers::makeMove(pair<int,int> origin, pair<int,int> destination) {
    int r1 = origin.first;
    int c1 = origin.second;
    int r2 = destination.first;
    int c2 = destination.second;

    if (!inBounds(r1,c1) || !inBounds(r2,c2)){//checks if in bounds
        return;
    }

    CELL piece = m_game[r1][c1];// Stores the piece from the origin square.

    m_game[r1][c1] = ((r1 + c1) % 2 == 0 ? WCELL : BCELL);//makes the cell blank with the respective color 

    // if it's a jump, remove captured piece
    if (abs(r2-r1)==2 && abs(c2-c1)==2) {
        int rm = (r1+r2)/2;
        int cm = (c1+c2)/2;
        capturePiece(rm, cm);//calls helper functio to capture piece
    }

    // place piece on destination
    m_game[r2][c2] = piece;

    // crown if reached far row
    crownKing(r2, c2);

    // update counts
    updateDiskCounts();

    // switch turn
    switchPlayer();
}

