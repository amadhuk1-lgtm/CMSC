"""
File:    tactego.py
Author:  Akanksha Madhu Kiran
Date:    11/27/2023
Section: 45
E-mail:  amadhuk1@umbc.edu
Description: To play the game Tactego
"""
import random


def file_input(file_name):
    """
    file_input is a helper function for the tactego function.
    This function takes in the contents of the file and makes a list of the pieces on the board
    :param file: to open file inputed by user
    :param my_list: to create a list out of the content in the file
    :param final_list: to get the final_list of pieces
    :param seperate list: the list of strength of pieces and the number of pieces
    """
    file = open(file_name,'r')
    my_list = file.readlines()#as multiple lines in file
    final_list = []
    for i in range(len(my_list)):
        new_list = my_list[i].strip() # removes spaces in the end
        seperate_list = new_list.split(' ') # splits to two so that number of pieces of that particular strngth and the strength are two different elements

        for j in range(int(seperate_list[1])): # to get the number of pieces of that strength
            final_list.append(seperate_list[0])

    return final_list


def size_of_board(final_list,width,length):
    """
    This function shuffles the final list into two seperate shuffled lists for the red and blue teams and put the pieces into the board
    :param red_team: to get the pieces of the red team
    :param blue_team: to get the pieces of the blue team
    :param my_2d_list: to create the inner arrangement of the board with the pieces of both teams by making a 2d list.
    """
    R = list(final_list)
    B = list(final_list)
    random.shuffle(R)
    random.shuffle(B)
    blue_team = []
    red_team = []
    for element in range(len(B)): # to add the letter B before each piece of the blue team
        blue_team.append('B' + B[element])
        
    for element in range(len(R)):# to add letter R before each piece of the red team
        red_team.append('R' + R[element])

    my_2d_list = []
    index = 0
    for i in range(length):# making a 2d list by appended spaces into the sublist
        my_list = []
        for j in range(width):
            my_list.append(' ')
        my_2d_list.append(my_list)



    #to place pieces on the board
    count = 0
    for i in range(length):
        for j in range(width):
            if count < len(red_team):
                my_2d_list[i][j] = red_team[count % len(red_team)] # to get pieces on the next row when the number of columns have ended
                count += 1

    index = 0
    for i in range(length - 1,-1,-1):
        for j in range(width):
            if index < len(blue_team):
                my_2d_list[i][j] = blue_team[index % len(blue_team)] # to get pieces on the next row when the number of columns have ended
                index += 1


    
    return my_2d_list


def print_board(my_2d_list,width,length):
    """
    print_board is a helper function for the tactego function.
    This function prints the rows and columns along with the 2d list within the board
    :param length: the number of rows in the board
    :param width: the number of columns in the board
    :param my_2d_list: to print the updated 2d list within the rows and columns
    """
    print(' ', end='  ')
    for col in range(width):#to print the column numbers 
        print(col, end='  ')
    print()

    for row in range(length): # to print the row numbers
        print(row, end=' ')
        for col in range(width):
            if my_2d_list[row][col] == ' ':
                print(my_2d_list[row][col], end = '  ') # to print my_2d_list within the rows and columns
            else:
                print(my_2d_list[row][col], end = ' ')
        print()


def move_pieces(my_2d_list,turn,x):
    """
    move_pieces function moves the piece chosen by the user to the new position mentioned by the user
    :param initial_choice: to store the inputed choice
    :param piece: to store the piece present in the location of choice
    :param team: to check which team piece belongs to red or blue
    :param final_choice: the final position the user wants to move the piece
    """

    initial_choice = input('Select Piece to Move by Position: ')
    initial_choice = initial_choice.split() #to get the coordinates seperately

    first_choice = int(initial_choice[0])# to get row number
    second_choice = int(initial_choice[1])# to get column number
    piece = my_2d_list[first_choice][second_choice] # to check what piece is in that loaction
   

    team = piece[0]


    if len(piece) == 2: # to check if choice is valid
        if piece[1] == 'F':
            print('You must select a starting position with one of your pieces, not a flag.')
            return -1 # so that a turn is not lost if an invalid move is made
        if piece[1] == 'M':
            print('Invalid choice as mine is a non-movable piece')
            return -1
        
        elif piece[1] != 'F' and piece[1] != 'M':

            if turn % 2 == 0 and team == 'R': # to alternate turns between red team and blue team
                final_choice = input('Select Position to move Piece: ')
                final_choice = final_choice.split()
                first_final = int(final_choice[0]) # to get row of choice
                second_final = int(final_choice[1])# to get column of choice
                if validate_move_red(first_final,length,second_final,width,piece,first_choice,second_choice,my_2d_list) == False:
                    return False
              
    



            elif turn % 2 == 1 and team == 'B':# to alternate turns between red team and blue team
                final_choice = input('Select Position to move Piece: ')
                final_choice = final_choice.split()
                first_final = int(final_choice[0])
                second_final = int(final_choice[1])
                if validate_move_blue(first_final,length,second_final,width,piece,first_choice,second_choice,my_2d_list) == False:
                    return False
             

            else:
                print('Invalid choice')
                return -1 # so that a turn is not lost if an invalid move is made
    else:
        print('You must select a valid piece')
        return -1
    


def validate_move_red(first_final,length,second_final,width,piece,first_choice,second_choice,my_2d_list):
    """
    validate_move_red function checks if the move of the piece chosen by the red team to the new position mentioned by the user is valid
    :param initial_choice: to store the inputed choice
    :param piece: to store the piece present in the location of choice
    :param final_choice: the last position where the user wants piece to move
    :param my_2d_list: 2d list updated with the change of pieces position
    :param width: number of columns
    :param length: number of rows
    """
    check_move = my_2d_list[first_final][second_final]
    if check_move[0] == 'R':
        print('Invalid choice') #so that the piece of the same team is not undergoing combat
        return -1
    if first_final > length - 1 or second_final > width - 1: # to check if choice of position is within the range of columns and rows
            print('Invalid choice as out of range')
            return -1
    if piece[1] == 'A':#checking for assassins condition
        if first_final > length - 1 or second_final > width - 1 or first_final - first_choice > 1 or second_final - second_choice > 1:
            print('Invalid choice as out of range')
            return -1
        else:
            check_move = my_2d_list[first_final][second_final]
            if combat(check_move,first_final,second_final,first_choice,second_choice,piece,'R',my_2d_list) == 1000: # to check if flag is captured
                return False
            else:
                return True

    elif piece[1] == 'S':#checking for sapper condition
        check_move = my_2d_list[first_final][second_final]
        if first_final > length - 1 or second_final > width - 1 or first_final - first_choice > 1 or second_final - second_choice > 1:
            print('Invalid choice as out of range')
            return -1
        if check_move == ' ' or check_move == False: # if the final move has no pieces then replace it with chosen piece
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            return True
        
        if check_move[1] == 'M': # when sapper attacks mine it defeats mine
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            return True

        elif check_move[1] == 'S': # condition where all pieces defeat sappers
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '

        else:
            my_2d_list[first_final][second_final] = check_move
            my_2d_list[first_choice][second_choice] = '  '          

    else:
        check_move = my_2d_list[first_final][second_final]

        if check_move or check_move[1] == 'F':
            if check_move[0] == 'R':
                print('Invalid choice') #so that the piece of the same team is not combated
                return -1

            elif check_move[0] == 'B':
                if check_move[1] == 'M':#checking for mine condition
                    if my_2d_list[first_final][second_final] == 'F':
                        return False
                    if piece[1] == 'A':
                         my_2d_list[first_final][second_final] = '  '
                         my_2d_list[first_choice][second_choice] = '  '                       
                    else:
                        my_2d_list[first_final][second_final] = '  '
                        my_2d_list[first_choice][second_choice] = '  '
                        return True
                if combat(check_move,first_final,second_final,first_choice,second_choice,piece,'R',my_2d_list) == 1000:#to check if flag is destroyed or not
                    return False
                elif combat(check_move,first_final,second_final,first_choice,second_choice,piece,'R',my_2d_list) == 12:# to check if assassin is defeated or not
                    my_2d_list[first_final][second_final] = piece
                    my_2d_list[first_choice][second_choice] = '  '
                    return True
                else: 
                    return True
            
            elif first_final - first_choice > 1 or second_final - second_choice > 1:
                print('Invalid choice')
                return -1
            

            else:
                my_2d_list[first_choice][second_choice] = ' '
                my_2d_list[first_final][second_final] = piece # moves the piece if no piece occupies final position
                return True

        elif not check_move:
            my_2d_list[first_choice][second_choice] = ' '
            my_2d_list[first_final][second_final] = piece
            return True
            
        else:
            print('Invalid choice')
            return -1
        


def validate_move_blue(first_final,length,second_final,width,piece,first_choice,second_choice,my_2d_list):
    """
    validate_move_blue function checks if the move of the piece chosen by the blue team to the new position mentioned by the user is valid
    :param initial_choice: to store the inputed choice
    :param piece: to store the piece present in the location of choice
    :param final_choice: the last position where the user wants piece to move
    :param my_2d_list: 2d list updated with the change of pieces position
    :param width: number of columns
    :param length: number of rows
    """
    check_move = my_2d_list[first_final][second_final]
    if check_move[0] == 'B':
        print('Invalid choice') #so that the piece of the same team is not undergoing combat
        return -1
    if first_final > length or second_final > width:
        print('Invalid choice') # to check if choice of position is within the range of columns and rows
        return -1
    if piece[1] == 'A': # checking for assassins condition
        if first_final > length - 1 or second_final > width - 1 or first_final - first_choice > 1 or second_final - second_choice > 1:
            print('Invalid choice')
            return -1
        else:
            check_move = my_2d_list[first_final][second_final]
            if combat(check_move,first_final,second_final,first_choice,second_choice,piece,'B',my_2d_list) == 1000: # to check if flag is captured or not
                return False
            else:
                return True
            
    elif piece[1] == 'S':#checking for sapper condition
        check_move = my_2d_list[first_final][second_final]
        if first_final > length - 1 or second_final > width - 1 or first_final - first_choice > 1 or second_final - second_choice > 1:
            print('Invalid choice x')
            return -1
        if check_move == ' ' or check_move == False:# if the final move has no pieces then replace it with chosen piece
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            return True
        if check_move[1] == 'M': # when sapper attacks mine it defeats mine
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            return True

        elif check_move[1] == 'S': # condition where all pieces defeat sappers
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
        else:
            my_2d_list[first_final][second_final] = check_move
            my_2d_list[first_choice][second_choice] = '  '          

            
    
    else:
        check_move = my_2d_list[first_final][second_final]

        if check_move or check_move[1] == 'F':
            if check_move[0] == 'B': #so that the piece of the same team is not combated
                print('Invalid choice')
                return -1
            elif check_move[0] == 'R':
                if check_move[1] == 'M':#checking for mine condition
                    if my_2d_list[first_final][second_final] == 'F':
                        return False
                    if piece[1] == 'A':
                         my_2d_list[first_final][second_final] = '  '
                         my_2d_list[first_choice][second_choice] = '  '
                    else:
                        my_2d_list[first_final][second_final] = '  '
                        my_2d_list[first_choice][second_choice] = '  '
                        return True

                if combat(check_move,first_final,second_final,first_choice,second_choice,piece,'B',my_2d_list) == 1000: #to check if flag is captured or not

                    return False
                elif combat(check_move,first_final,second_final,first_choice,second_choice,piece,'B',my_2d_list) == 12: # to check if assassin is defeated or not
                    my_2d_list[first_final][second_final] = piece
                    my_2d_list[first_choice][second_choice] = '  '

                    return True

                else:
                    return True
                
            elif first_final - first_choice > 1 or second_final - second_choice > 1:
                print('Invalid choice')
                return -1
                
            elif first_final > length or second_final > width:
                print('Invalid choice')
                return -1
            

            else: # moves the piece if no piece occupies final position
                my_2d_list[first_choice][second_choice] = '  '
                my_2d_list[first_final][second_final] = piece

                return True

        elif not check_move:
            my_2d_list[first_choice][second_choice] = '  '
            my_2d_list[first_final][second_final] = piece

            return True
        else:
            print('Invalid choice')
            return -1



def combat(check_move,first_final,second_final,first_choice,second_choice,piece,team,my_2d_list):
    """
    the combat function is the helper function for the validate move functions for both red and blue
    the combat function is used to make the pieces combat with each other
    :param check_move: move the user inputed for the piece to go to
    :param piece: the piece chosen to move
    """
    if check_move != ' ':

        if check_move[1] == 'F': #checks if flag is captured or not
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            print(team + ' has won the game')       
            return 1000

        if check_move[1] == 'A': # checks assassins is defeatd by any piece
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
            return 12
        
        if piece[1]=='A': # makes assasin defeat any piece
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '     
            return   

        if piece[1] != 'S' and check_move[1] == 'M': 
            my_2d_list[first_final][second_final] = '  '
            my_2d_list[first_choice][second_choice] = '  '
            return
        


        elif int(check_move[1]) > int(piece[1]):
            my_2d_list[first_final][second_final] = check_move
            my_2d_list[first_choice][second_choice] = '  '

            return 1
        
        elif int(check_move[1]) < int(piece[1]):
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '

            return 1
        
        elif int(check_move[1]) == int(piece[1]):
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '

            return 1
    else:
            my_2d_list[first_final][second_final] = piece
            my_2d_list[first_choice][second_choice] = '  '
    



def tactego(file_name,width,length):
    """
    tactego function runs the entire game and prints the board as the move is made
    :param final_list: calls file_input and stores the list with the pieces
    :param my_2d_list: calls size_of_board function to get the board
    :param turn: to keep count on whose turn it is
    :param result: to call move_pieces function so that the pieces move according to the inputed position
    :param winner_found: it is a boolean flag which is used to run the game until winner is found
    """
    final_list = file_input(file_name)
    my_2d_list = size_of_board(final_list,width,length)
    print_board(my_2d_list,width,length)
    turn = 0
    x = True
    winner_found = False 
    while x and not winner_found: # to run until winner is found
            result = move_pieces(my_2d_list, turn, x)

            if result == False:
                print("Game Over: Winner found!")
                winner_found = True  # Set the flag to True to stop the game loop

            if result != -1:
                print_board(my_2d_list,width,length)
            
                turn += 1 # to keep count on whose turn it is
                
                x = True

            else:
                turn = turn # so that players invalid moves can be given another chance to make a valid move
                x = True



       


if __name__=='__main__':
    random.seed(input('What is seed? '))
    file_name = input('What is the filename for the pieces? ')
    length = int(input('What is the length? '))
    width = int(input('What is the width? '))
    tactego(file_name,width,length)

