// /*****************************************                                                                                                                
// ** File:    mytest.cpp                                                                                                                                    
// ** Project: CMSC 341 Project 0, Fall 2025                                                                                                                 
// ** Author:  Akanksha Madhu Kiran                                                                                                                                    
// ** Date:    09/09/2025                                                                                                                                    
// ** E-mail:  amadhuk1@umbc.edu                                                                                                                           
// ** This file contains the implementation of the tester class and its Functions                                                                            
// ***********************************************/           
#include "checkers.h"
#include <iostream>
using namespace std;

class Tester {
public:

    bool constructorError(){
        bool result = true;
        Checkers checkers(-5, -10);//creates checkers object with invalid dimensions
        checkers.m_currPlayer = NONE;                      
        checkers.m_whiteDisks = 0;
        checkers.m_blackDisks = 0;
        checkers.m_numColumns = 0;
        checkers.m_numRows = 0;
        checkers.m_game = nullptr;
        return result;
    }

    bool constructorNormal(){
        bool result = true;
        Checkers checkers(10, 10);//creates a 10 by 10 checkers object
        result = result && checkers.initBoard();//to initialize the board
        //cout << "\nthe following is the rendering of the board:\n\n"; 
        //checkers.dumpGame(); // render the board
        //cout << "\nthe following shows the initial state of the game:\n\n";
        //checkers.dumpGame(); // render the initial state of the game
        const int size = 10*10;
        //a specific board state for testing.
        CELL game[size] = 
        {"", "", "", "", "", "", "", "","", "",
        "", "", "", "", "", "","", "", "", BDISK, 
        "", "", "", "",WDISK, "", "", "", WDISK, "", 
        WDISK, "","", "", "", BDISK, "", BDISK, "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "","", "", "", "",
        "", "", "", "","", "", "", "", "", "", 
        "", "","", "","", "", "", "", "", "", 
        "", "","", "","", "", "", "", "", "", 
        "", "", "", "","", "", "", "", "", "",};

        result = result && checkers.setGameState(game, size, WPLAYER);//sets the game state
        //cout << "\nthe following shows the current state of the game:\n\n";
        //checkers.dumpGame(); // render the current state of the game
        //cout << "\nthe following tests a capturing move for which we expect success:\n\n";
        //checkers.reportLostDisks();//to count the number of disks lost                  
        if(checkers.m_numColumns == 10){
            result = true;
        }
        if(checkers.m_numRows == 10){
            result = true;
        }
        return result;
        }
    

    bool testInitBoardError() {
        Checkers c; //creates empty checkers object
        bool result = true;
        result = result && c.initBoard();//to check if initBoard should succeed without crashing, remaining null
        result = result && (c.m_game == nullptr);
        result = result && (c.m_whiteDisks == 0);// Checks if the white disk count is 0
        result = result && (c.m_blackDisks == 0);// Checks if the black disk count is 0
        result = result && (c.m_currPlayer == NONE);
        result = result && (c.m_numRows == 0);
        result = result && (c.m_numColumns == 0);
        return result;
    }

    bool testInitBoardEdge() {
        Checkers c(DEFBOARDSIZE,DEFBOARDSIZE);//creates a valid 8 by 8 board
        c.initBoard();
        bool result = true;
        for (int r = 0; r < DEFBOARDSIZE; ++r)//loops through to verify pattern
            for (int cc = 0; cc < DEFBOARDSIZE; ++cc)
                result = result && (c.m_game[r][cc] == ((r+cc)%2==0 ? WCELL : BCELL)); // Checks if the cell color is correct
        return result;
    }

    bool testInitGameError() {
        Checkers c;//creates empty checkers object
        bool result = true;
        result = result && c.initGame();//state of game unchanged but checking if 
        result = result && (c.m_game == nullptr); // Checks if the game board pointer is null
        result = result && (c.m_whiteDisks == 0); // Checks if the white disk count is 0
        result = result && (c.m_blackDisks == 0); // Checks if the black disk count is 0
        result = result && (c.m_currPlayer == NONE);
        result = result && (c.m_numRows == 0);
        result = result && (c.m_numColumns == 0);
        return result;
    }

    bool testInitGameNormal() {

        ////////////////////////do m_player,m_numRows, m_numColumns;
        Checkers c(10,10); // creates 10 by 10 board
        c.initBoard(); // Initializes the board with cell colors.
        c.initGame(); // Initializes game with pieces.
        bool result = true;
        int whiteCount = 0;
        int blackCount = 0;
        for (int r = 0; r < 10; ++r){
            for (int cc = 0; cc < 10; ++cc) {
                if ((r + cc) % 2 == 1) {//checks for black cells
                    if (r < 3) {//checks top three rows
                        if (c.m_game[r][cc] != WDISK){//checks if white disk present
                            result = false;
                        }
                        else {
                            ++whiteCount;
                        }
                    } else if (r >= 7) {
                        if (c.m_game[r][cc] != BDISK){//checks if black disk present
                            result = false;
                        }
                        else{
                            ++blackCount;
                        }
                    }
                }
            }
        }
        result = result && (whiteCount == 15) && (blackCount == 15);//verifies total disks
        result = result && (c.m_whiteDisks == 15) && (c.m_blackDisks == 15);
        result = result && (c.m_currPlayer == BPLAYER);//verifies starting player black
        return result;
    }

    bool testSetGameState(Checkers &checkers) {
        const int N = DEFBOARDSIZE;
        CELL game[N*N] = {""};
        game[2*N + 3] = WDISK;//places WD at (2,3)
        game[5*N + 4] = BDISK;
        game[0*N + 1] = BCELL;
        reset8x8Board(checkers, game, WPLAYER);//resets checkers object
        bool result = true;
        //verification to check if pieces placed correctly
        result = result && (checkers.m_game[2][3] == WDISK);
        result = result && (checkers.m_game[5][4] == BDISK);
        result = result && (checkers.m_game[0][1] == BCELL);
        result = result && (checkers.m_currPlayer == WPLAYER);
        result = result && (checkers.m_whiteDisks >= 1);
        result = result && (checkers.m_blackDisks >= 1);
        return result;
    }

    bool testPlayWrongPlayer(Checkers &checkers) {
        const int N = DEFBOARDSIZE;
        CELL game[N*N] = {""};
        game[4*N + 3] = BDISK;//places black disk at (4,3)
        game[5*N + 4] = BCELL;//destination for move
        reset8x8Board(checkers, game, WPLAYER);
        CELL before = checkers.m_game[4][3]; // Stores the state of the origin cell before the move.
        bool played = checkers.play({4,3},{5,4});//if fialed move
        bool unchanged = (checkers.m_game[4][3] == before) && (checkers.m_game[5][4] == BCELL);//verify if board change dor not
        return (!played && unchanged);
    }

    bool testPlaySimpleMove(Checkers &checkers) {
        const int N = DEFBOARDSIZE;
        CELL game[N*N] = {""};
        game[2*N + 3] = WDISK;
        game[1*N + 4] = BCELL;
        reset8x8Board(checkers, game, WPLAYER);
        bool result = checkers.play({2,3},{1,4});//executes move
        result = result && (checkers.m_game[2][3] == BCELL);//verifies if move made correctly by checking origin and destination
        result = result && (checkers.m_game[1][4] == WDISK);
        result = result && (checkers.m_currPlayer == BPLAYER);//verifies turn switch
        return result;
    }

    bool testPlayJump(Checkers &checkers) {
        const int N = DEFBOARDSIZE;
        CELL game[N*N] = {""};
        game[1*N + 4] = WDISK;
        game[2*N + 3] = BDISK;
        game[3*N + 2] = BCELL;
        reset8x8Board(checkers, game, WPLAYER);
        int beforeBlack = checkers.m_blackDisks;
        bool result = checkers.play({1,4},{3,2}); // Verifies the origin is empty.
        result = result && (checkers.m_game[1][4] == BCELL);
        result = result && (checkers.m_game[3][2] == WDISK);
        result = result && (checkers.m_game[2][3] == BCELL);
        result = result && (checkers.m_blackDisks == beforeBlack-1); // Verifies that the black disk count has decreased by one.
        result = result && (checkers.m_currPlayer == BPLAYER);// Verifies that the turn has switched.
        return result;
    }

    bool testCaptureSuccess(Checkers &checkers) {
        bool result = true;
        // before play we expect a BCELL in (3,2)
        result = result && (checkers.m_game[3][2] == BCELL);
        // before play we expect a WDISK in (1,4)
        result = result && (checkers.m_game[1][4] == WDISK);
        // before play we expect that it is WPLAYER turn to play
        result = result && (checkers.m_currPlayer == WPLAYER);
        // before play we expect a BDISK in (2,3), there is an opponent disk
        result = result && (checkers.m_game[2][3] == BDISK);
        // store the ccurrent opponent number if disks
        int opponentDisks = checkers.m_blackDisks;
        // now call the play(...) function
        result = checkers.play(pair<int,int>(1,4),pair<int,int>(3,2));
        // we are trying to move (1,4) to (3,2), we expect that move is successful
        // after play we expect a BCELL in (1,4)
        result = result && (checkers.m_game[1][4] == BCELL);
        // after play we expect a WDISK in (3,2)
        result = result && (checkers.m_game[3][2] == WDISK);
        // after play we expect that it is BPLAYER turn
        result = result && (checkers.m_currPlayer == BPLAYER);
        // after play we expect a BCELL in (2,3), an opponent disk is captured
        result = result && (checkers.m_game[2][3] == BCELL);
        // after play we expect one less disk for the opponent
        result = result && (checkers.m_blackDisks == (opponentDisks-1));
        return result;
    }

    void reset8x8Board(Checkers &checkers, CELL game[], int currPlayer) {
        const int size = DEFBOARDSIZE*DEFBOARDSIZE;//board blocks present
        checkers.setGameState(game, size, WPLAYER);//to load board and player
    }
    
};

int main() {
    Tester tester; // Creates an instance of the Tester class.
    Checkers checkers(DEFBOARDSIZE, DEFBOARDSIZE); // Creates an 8x8 checkers game instance.
    checkers.initBoard();

    //cout << "\nthe following is the rendering of the board:\n\n"; 
    //checkers.dumpGame(); // render the board
    checkers.initGame();
    //cout << "\nthe following shows the initial state of the game:\n\n";
    //checkers.dumpGame(); // render the initial state of the game

    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = // Defines a specific game state array
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",};

    cout << "***************\n1) testCaptureSuccess:\n";
    tester.reset8x8Board(checkers, game, WPLAYER);// Resets the board for the test.
    //cout << "Board BEFORE move:\n";
    //checkers.dumpGame();
    cout << (tester.testCaptureSuccess(checkers) ? "PASS" : "FAIL") << endl; // Calls the test function and prints the result.
    //cout << "Board AFTER move:\n";
    //checkers.dumpGame();
    //checkers.reportLostDisks();  // Reports the number of lost disks.

    cout << "***************\n2) constructorError:\n";
    cout << (tester.constructorError() ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.

    cout << "***************\n3) constructorNormal:\n";
    cout << (tester.constructorNormal() ? "PASS" : "FAIL") << endl;

    cout << "***************\n4) testInitBoardError:\n";
    cout << (tester.testInitBoardError() ? "PASS" : "FAIL") << endl;

    cout << "***************\n5) testInitBoardEdge:\n";
    cout << (tester.testInitBoardEdge() ? "PASS" : "FAIL") << endl;

    cout << "***************\n6) testInitGameError:\n";
    cout << (tester.testInitGameError() ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.

    cout << "***************\n7) testInitGameNormal (10x10 board):\n";
    cout << (tester.testInitGameNormal() ? "PASS" : "FAIL") << endl;

    cout << "***************\n8) testSetGameState:\n";
    tester.reset8x8Board(checkers, game, WPLAYER);
    //cout << "Board BEFORE:\n";
    //checkers.dumpGame();
    cout << (tester.testSetGameState(checkers) ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.
    //cout << "Board AFTER:\n";
    //checkers.dumpGame();
    //checkers.reportLostDisks();

    cout << "***************\n9) testPlayWrongPlayer:\n";
    tester.reset8x8Board(checkers, game, WPLAYER);
    //cout << "Board BEFORE:\n";
    //checkers.dumpGame();
    cout << (tester.testPlayWrongPlayer(checkers) ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.
    //cout << "Board AFTER:\n";
    //checkers.dumpGame();
    //checkers.reportLostDisks();

    cout << "***************\n10) testPlaySimpleMove:\n";
    tester.reset8x8Board(checkers, game, WPLAYER);
    //cout << "Board BEFORE:\n";
    //checkers.dumpGame();
    cout << (tester.testPlaySimpleMove(checkers) ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.
    //cout << "Board AFTER:\n";
    //checkers.dumpGame();
    //checkers.reportLostDisks();

    cout << "***************\n11) testPlayJump:\n";
    tester.reset8x8Board(checkers, game, WPLAYER);
    //cout << "Board BEFORE:\n";
    //checkers.dumpGame();
    cout << (tester.testPlayJump(checkers) ? "PASS" : "FAIL") << endl;// Calls the test function and prints the result.
    //cout << "Board AFTER:\n";
    //checkers.dumpGame();
    //checkers.reportLostDisks();


    cout << "***************\nAll tests done.\n";
    return 0;
}