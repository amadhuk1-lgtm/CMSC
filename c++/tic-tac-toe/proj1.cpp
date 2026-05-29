//*****************************************************************************************
//File: proj1.cpp
//Project: 1
//Author: Akanksha Madhu Kiran
//Date: 02/24/2025
//Section: 40/42
//E-mail: amadhuk1@umbc.edu
//This file helps the user to play tic-tac-toe and display statistics
//This is the extra credit verion
//*****************************************************************************************

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;
const int ROWS = 3;
const int COLS = 3;
const int SIZE = 4;
const char SYMBOL_X = 'X';
const char SYMBOL_O = 'O';
const char EMPTY = '_';


int playGame(char gameArray[ROWS][COLS]);
// Name: playGame
//PreCondition: loads the gameArray to save the current board
//PostCondition: Does not return anything
//Manages the main gameplay loop. Displays the board then alternates turns for what location the user would like to place their respective symbol. Keeps alternating until checkWin indicates the game has completed.

void saveGame(char gameArray[ROWS][COLS]);
// Name: saveGame
//PreCondition: loads the gameArray to save the current board into the file
//PostCondition: Does not return anything
//Saves the board whose move is made into text file

void displayBoard(char gameArray[ROWS][COLS]);
// Name: displayBoard
//PreCondition: loads the gameArray to display any valid move made
//PostCondition: Does not return anything
//Displays the game board to the console.

void clearBoard(char gameArray[ROWS][COLS]);
// Name: clearBoard
// PreCondition: loads the gameArray to clear and restart the board.
// PostCondition: Does not return anything
// Resets the board after the game ends in anticipation of playing again

char chooseSymbol();
// Name: chooseSymbol
// PreCondition: loads no parameters
// PostCondition: returns the symbol choice made by the user.
// Allows the user to choose a symbol (either symbol1 or symbol2). These should start as constants (X and O).

void makeMove(char player,char gameArray[ROWS][COLS]);
// Name: makeMove
//PreCondition: loads the gameArray and player to make a move and check if its valid.
//PostCondition: Does not return anything
//Attempts to place a player's symbol on the board. Makes sure it is a valid play

bool checkWin(char player,char gameArray[ROWS][COLS]);
// Name: checkWin
//PreCondition: loads the gameArray and player to check which player wins
//PostCondition: checks if someone wins or is a draw and returns a boolean variable.
//Checks if there is a winner or if the game is a draw. Checks vertical, horizontal, and diagonal for three of the same symbols in a row.
//void calcStats(int &totalGames, int &xWins, int &oWins, int &draws, int result);

void displayStats(int totalGames, int xWins, int oWins, int draws);
// Name: displayStats
// PreCondition: loads the total number of games, wins of each player, counting draws and result(which is the value returned from checkWin)
// PostCondition: prints the statistics when the option is chosen.
// prints whenever the option display stats is chosen


void calcStats(int winArray[SIZE],int result);
// Name: calcStats
// PreCondition: Loads an array and increments the number of wins,draws and total games using the value given by playgame
// PostCondition: updates the array every time someone wins,draws and total games
// does not return anything


int main() {
    int choice;
    char symbol;
    bool flag = true;
    int totalGames = 0;
    int xWins = 0;
    int oWins = 0;
    int draws = 0;


    cout << "Welcome to Tic-Tac-Toe "<< endl;
    do{ //to keep asking until chosen to quit
        cout << "What would you like to do? "<< endl;
        cout << "1. Play New Game" << endl;
        cout << "2. Display Stats" << endl;
        cout << "3. Quit \n";
        cin >> choice; //store the choice being made
        int winArray[SIZE] = {}; //empty array to store total games played,wins and draws
        switch(choice) {
            case 1:{
                char gameArray[ROWS][COLS] = { {'_','_','_'}, {'_','_','_'}, {'_','_','_'}};//to initialize an empty array
                
                int result = playGame(gameArray);//run the entire game
                if (result == 1) {//if returns 1 PLAYER_X wins
                    calcStats(winArray, result);//increments after each win
                    xWins = winArray[1];
                }else if (result == 2) { //if returns 2, PLAYER_O wins and increments after each win
                    calcStats(winArray, result);
                    xWins = winArray[2];//stores it in the array
                }else{
                    //draws = incrementWins(draws);//if returns 0, draws and increments after each draw
                    calcStats( winArray, result);//increments after each draw
                    xWins = winArray[3];
                }
                flag = true; //to keep the game continue playing
                
                break;
            }
            case 2:{
                totalGames = winArray[0];
                displayStats(totalGames, xWins, oWins, draws);//to display the statistics
                flag = true;
                break;
            }
            case 3:{
                cout << "Thank you for playing Tic-Tac-Toe" << endl;
                flag = false;/// to not run the do while loop again
            }
            default:{
                cout << "Invalid choice. Please enter 1 or 2." << endl;
                flag = true;//to ask the user their choice again by going through the while loop
            }
        }
    }while(flag);
    return 0;
}



// Name: saveGame
//PreCondition: loads the gameArray to save the current board into the file
//PostCondition: Does not return anything
//Saves the board whose move is made into text file
void saveGame(char gameArray[ROWS][COLS]) { 
      ofstream file("proj1_data.txt"); //to open the file and write the board in it after each move
        if (file.is_open()) { 
            file << "Current board:" << endl; 
            for(int i=0; i < ROWS; i++){  //to go through each row
                for(int j=0; j < COLS; j++){   //to go though each column
                    file << " " << gameArray[i][j] ;  //to print the board(updates whenever move is made)
                }
                file << endl;//to print each row to next line
            }
        file.close();//closing the file
        }      
}


// Name: displayBoard
// PreCondition: loads the gameArray to display any valid move made
// PostCondition: Does not return anything
// Displays the game board to the console.
void displayBoard(char gameArray[ROWS][COLS]) {  
    cout << "Current board:" << endl; 
    for(int i=0; i < ROWS; i++){  //to go through each row
        for(int j=0; j < COLS; j++){   //to go though each column
            cout << " " << gameArray[i][j] ;  //to print the board(updates whenever move is made)
        }
       cout << endl; 
    }
}

// Name: clearBoard
// PreCondition: loads the gameArray to clear and restart the board.
// PostCondition: Does not return anything
// Resets the board after the game ends in anticipation of playing again
void clearBoard(char gameArray[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++)
            gameArray[i][j] = EMPTY; //clears board and replaces each location of the array with an "_"
    }
}

// Name: chooseSymbol
// PreCondition: loads no parameters
// PostCondition: returns the symbol choice made by the user.
// Allows the user to choose a symbol (either symbol1 or symbol2). These should start as constants (X and O).
char chooseSymbol() {
    char symbol;
    while (true) {
            cout << "What symbol would you like to be? ("<< SYMBOL_X << " or " << SYMBOL_O << ")"<< endl;
            cin >> symbol;
            
            if (symbol == SYMBOL_X) { //to check if it is symbol_x and return it to alternate
                return SYMBOL_X;
            } else if (symbol == SYMBOL_O) { //to check if it is symbol_o and return it to alternate
                return SYMBOL_O;
            }
        }
}


// Name: playGame
// PreCondition: loads the gameArray to save the current board
// PostCondition: Does not return anything
// Manages the main gameplay loop. Displays the board then alternates turns for what location the user would like to place their respective symbol. Keeps alternating until checkWin indicates the game has completed.
int playGame(char gameArray[ROWS][COLS]) {
    char player1;
    char player2;
    bool endGame = false; // Initialize endGame to false
    int turns = 0;
    player1 = chooseSymbol(); //to save the symbol chosen by user as player1

    // Assign symbol to player2
    if (player1 == SYMBOL_X){ //to give the other player a name
            player2 = SYMBOL_O;
    } 
    if (player1 == SYMBOL_O){ 
        player2 = SYMBOL_X;
    }

    displayBoard(gameArray); //to display the initial empty board

    while(turns < 9 && !endGame) {  //to keep continuing the game until somebody wins

        //Player 1's turn
        makeMove(player1, gameArray); // calls makeMove to input the symbol in chosen location
        saveGame(gameArray); // save the board game so that the move is tracked
        displayBoard(gameArray);// Display the board after the move
        endGame = checkWin(player1, gameArray); //after each move to check if player1 won

        if (endGame) {
            return (player1 == SYMBOL_X) ? 1 : 2; // 1 for X win, 2 for O win
        } else {
            turns++;
        }

        // Check for Draw
        if (turns >= 9) {
            cout << "The game is a draw!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe" << endl;
            return 0;
        }

        //Player 2's turn
        makeMove(player2, gameArray); //for player2 to make a move
        saveGame(gameArray);
        displayBoard(gameArray);
        // Display the board after the move
        endGame = checkWin(player2, gameArray); //to check if player2 won

        if (endGame) {
            return (player2 == SYMBOL_O) ? 2 : 1; // 1 for X win, 2 for O win
        } else {
            turns++;
        }

        // Check for Draw again after Player 2's move
        if (turns >= 9) {
            cout << "The game is a draw!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe" << endl;
            return 0;
        }
    }
    return 0;
}

// Name: makeMove
// PreCondition: loads the gameArray and player to make a move and check if its valid.
// PostCondition: Does not return anything
// Attempts to place a player's symbol on the board. Makes sure it is a valid play
void makeMove(char player, char gameArray[ROWS][COLS]){
    int row, col;
    bool validOption = true;


    while (validOption) {
        cout << "Player " << player << ", enter row and column (0-2): ";

        if (!(cin >> row >> col)) {  // Check for valid integer input
            cout << "Invalid input. Try again." << endl;
            cin.clear();  // Clear error flags(clears anything extra)
            cout << "Current board:" << endl;
            displayBoard(gameArray);//to display the board with the last valid move made so that even if invalid choice board is displayed
            validOption = true;
        }

        // Validate row and column range
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) { //to check if move made is withing the 2D array
            cout << "Invalid move. Try again." << endl;
            cout << "Current board:" << endl;
            displayBoard(gameArray);//to diplay board even if invalid move with previous saved move
        }
        else if (gameArray[row][col] != '_') { // Check if cell is occupied previously
            cout << "Invalid move. Try again." << endl;
            cout << "Current board:" << endl;
            displayBoard(gameArray);
        }
        else {
            gameArray[row][col] = player; // Place the player's symbol
            validOption = false; // Exit loop only after valid move is entered.

        }
    }
}

// Name: checkWin
//PreCondition: loads the gameArray and player to check which player wins
//PostCondition: checks if someone wins or is a draw and returns a boolean variable.
//Checks if there is a winner or if the game is a draw. Checks vertical, horizontal, and diagonal for three of the same symbols in a row.
bool checkWin(char player,char gameArray[ROWS][COLS]) {
    bool win = false; // to stop continuing the game when someone wins or a draw
    //the following are possible conditions for a player to win
        if(gameArray[0][0] == player && gameArray[1][1] == player && gameArray[2][2] == player){
            //to check if player gets all his symbols in the diagonal
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }if(gameArray[0][0] == player && gameArray[0][1] == player && gameArray[0][2] == player){
            //to check if player gets all his symbols in the first row
            cout << "Player "<< player << " Wins!" << endl;//
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[1][0] == player && gameArray[1][1] == player && gameArray[1][2] == player){
            //to check if player gets all his symbols in the second row
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[2][0] == player && gameArray[2][1] == player && gameArray[2][2] == player){
            //to check if player gets all his symbols in the third row
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[0][0] == player && gameArray[1][0] == player && gameArray[2][0] == player){
            //to check if player gets all his symbols in the first column
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[0][1] == player && gameArray[1][1] == player && gameArray[2][1] == player){
            //to check if player gets all his symbols in the second column
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[0][2] == player && gameArray[1][2] == player && gameArray[2][2] == player){
            //to check if player gets all his symbols in the third column
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else if(gameArray[0][2] == player && gameArray[1][1] == player && gameArray[2][0] == player){
            //to check if player gets all his symbols in the opposite diagonal
            cout << "Player "<< player << " Wins!" << endl;
            cout << "Thank you for playing Tic-Tac-Toe"<< endl;
            win = true;
        }else{
            //checking for a draw
            bool isDraw = true;
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    if (gameArray[i][j] == EMPTY) {
                        isDraw = false; // If any empty space, game is still ongoing
                    }
                }
            }

            if (isDraw) {
                win = false;
                return win;
            }
        }
        return win; // Game is still ongoing
    }










// Name: calcStats
// PreCondition: loads the total number of games, wins of each player, counting draws and result(which is the value returned from checkWin)
// PostCondition: Since they are pointers no need to return automatically saved in memory
// counts and increments whenever someone wins or draws.


// Name: displayStats
// PreCondition: loads the total number of games, wins of each player, counting draws and result(which is the value returned from checkWin)
// PostCondition: prints the statistics when the option is chosen.
// prints whenever the option display stats is chosen
void displayStats(int totalGames, int xWins, int oWins, int draws) {
    //printing the format of display
    cout << "********************" << endl;
    cout << "Total games: " << totalGames << endl;
    cout << "Draws: " << draws << endl;
    cout << SYMBOL_X << " wins: " << xWins << endl;
    cout << SYMBOL_O << " wins: " << oWins << endl;
    cout << "********************" << endl;
}

// Name: calcStats
// PreCondition: Loads an array and increments the number of wins,draws and total games using the value given by playgame
// PostCondition: updates the array every time someone wins,draws and total games
// does not return anything
void calcStats(int winArray[SIZE],int result){
    winArray[0]++; //total games is kept on track
    if (result == 1) {
        winArray[1]++; // X wins incremented
    } else if (result == 2) {
        winArray[2]++; // O wins incremented
    } else {
        winArray[3]++; // Draws incremented
    }
}



