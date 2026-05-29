"""
File:    project_mancala.py
Author:  Akanksha Madhu Kiran
Date:    11/02/2023
Section: 45
email:  amadhuk1@umbc.edu
Description: To play the mancala game
"""
BLOCK_WIDTH = 6
BLOCK_HEIGHT = 5
BLOCK_SEP = "*"
SPACE = ' '
NUM_CUPS = 6


def draw_board(top_cups, bottom_cups, mancala_a, mancala_b):
    """
    draw_board is the function that you should call in order to draw the board.
        top_cups and bottom_cups are 2d lists of strings.  Each string should be length BLOCK_WIDTH and each list should be of length BLOCK_HEIGHT.
        mancala_a and mancala_b should be 2d lists of strings.  Each string should be BLOCK_WIDTH in length, and each list should be 2 * BLOCK_HEIGHT + 1

    :param top_cups: This should be a list of strings that represents cups 1 to 6 (Each list should be at least BLOCK_HEIGHT in length, since each string in the list is a line.)
    :param bottom_cups: This should be a list of strings that represents cups 8 to 13 (Each list should be at least BLOCK_HEIGHT in length, since each string in the list is a line.)
    :param mancala_a: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 7.
    :param mancala_b: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 0.
    """
    board = [[SPACE for _ in range((BLOCK_WIDTH + 1) * (len(top_cups) + 2) + 1)] for _ in range(BLOCK_HEIGHT * 2 + 3)]
    for p in range(len(board)):
        board[p][0] = BLOCK_SEP
        board[p][len(board[0]) - 1] = BLOCK_SEP

    for q in range(len(board[0])):
        board[0][q] = BLOCK_SEP
        board[len(board) - 1][q] = BLOCK_SEP

    # draw midline
    for p in range(BLOCK_WIDTH + 1, (BLOCK_WIDTH + 1) * (len(top_cups) + 1) + 1):
        board[BLOCK_HEIGHT + 1][p] = BLOCK_SEP

    for i in range(len(top_cups)):
        for p in range(len(board)):
            board[p][(1 + i) * (1 + BLOCK_WIDTH)] = BLOCK_SEP

    for p in range(len(board)):
        board[p][1 + BLOCK_WIDTH] = BLOCK_SEP
        board[p][len(board[0]) - BLOCK_WIDTH - 2] = BLOCK_SEP

    for i in range(len(top_cups)):
        draw_block(board, i, 0, top_cups[i])
        draw_block(board, i, 1, bottom_cups[i])

    draw_mancala(0, mancala_a, board)
    draw_mancala(1, mancala_b, board)

    print('\n'.join([''.join(board[i]) for i in range(len(board))]))


def draw_mancala(fore_or_aft, mancala_data, the_board):
    """
        Draw_mancala is a helper function for the draw_board function.
    :param fore_or_aft: front or back (0, or 1)
    :param mancala_data: a list of strings of length 2 * BLOCK_HEIGHT + 1 each string of length BLOCK_WIDTH
    :param the_board: a 2d-list of characters which we are creating to print the board.
    """
    if fore_or_aft == 0:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][1 + j] = data[j]
    else:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][len(the_board[0]) - BLOCK_WIDTH - 1 + j] = data[j]


def draw_block(the_board, pos_x, pos_y, block_data):
    """
        Draw block is a helper function for the draw_board function.
    :param the_board: the board is the 2d grid of characters we're filling in
    :param pos_x: which cup it is
    :param pos_y: upper or lower
    :param block_data: the list of strings to put into the block.
    """
    for i in range(BLOCK_HEIGHT):
        data = block_data[i][0:BLOCK_WIDTH].rjust(BLOCK_WIDTH)
        for j in range(BLOCK_WIDTH):
            the_board[1 + pos_y * (BLOCK_HEIGHT + 1) + i][1 + (pos_x + 1) * (BLOCK_WIDTH + 1) + j] = data[j]

def get_player():
    """
    get_player is the helper function for run_game()
    Asks the player's names and returns the names of each player. 
    But this function needs to be called twice to return two names player_1 and player_2
    :param player:to store the name of player inputed
    """
    player = input('Enter name of player : ')
    return player


def take_turn(player, my_pons,z,player_1,player_2):
    """
    Helper function for run_game()
    Asks the move that the player wishes to make. This function checks if the move made by the user is valid or not.
    It also makes he number of stones in the cup chosen to be zero.
    :param move: is the cup chosen to move by player
    :param my_pons: is a list which stores the number of stones in each cup(in order of my_pons index)
    :param choice: to store boolean value
    :param number_of_pons: shows the number of stones in the chosen cup
    returns a boolean expression
    """
    choice = True
    while choice != False:
        move = int(input('What cup does '+ player +' want to move? '))
        if move % 14 == 7 or move % 14 == 0 or my_pons[move]==0: #to check if move is valid or not....here modulus is used to keep updating the number of stones in clockwise direction
            print('Invalid choice')
            choice = True 
        elif move in range(1,7) or range(8,14) and my_pons[move] != 0:
            number_of_pons = my_pons[move]
            my_pons[move] = 0    #to check if the number of stones in the chosen cup is 0 or not
            choice = add_pons(move,number_of_pons,my_pons,choice,player_1,player_2)

    return choice


def add_pons(move, number_of_pons, my_pons,choice,player_1,player_2):
    """
    Helper function for take_turn
    This function adds stones to the cups following the chosen cup
    :param move: move made by player
    :param my_pons: is a list which stores the number of stones in each cup(in order of my_pons index which is nothing but i)
    :param number_of_pons: shows the number of stones in the cup
    """
    for i in range(move + 1 , move + 1 + number_of_pons ):
        i = i % 14 
        my_pons[i] = my_pons[i] + 1 #to increase the number of stones each cup following the chosen cup 
    choice = check_mancala(move, number_of_pons, choice,my_pons,player_1,player_2)
    return choice


def check_mancala(move, number_of_pons, choice,my_pons,player_1,player_2):
    """
    helper function for add_pons
    This function checks if the last stone is dropped in the mancala or not
    returns a boolean expression
    :param my_pons: is a list which stores the number of stones in each cup
    :param number_of_pons: shows the number of stones in the chosen cup
    :param move: move made by player
    :param choice: to store boolean value
    :param player_1: player inputed first
    :param player_2: player inputed second
    """
    if (move + number_of_pons) % 14 == 7 or (move + number_of_pons) % 14 == 0: #to check if last stone landed in mancala
        print('Your last stone landed in a mancala.\n Go again please...')
        make_board(my_pons,player_1,player_2)
        choice = True
    else:
        make_board(my_pons,player_1,player_2) #to draw the board
        choice = False
    return choice


def check_winner(x,my_pons,player,a,b):
    """
    This is a helper function for run_game()
    This function checks when the player wins and when the game must end
    returns the player if the player wins else it returns a number
    :param win_flag: to store boolean value
    :param my_pons: is a list which stores the number of stones in each cup(in order of my_pons index which is nothing but i)
    :param x:just to store the output required
    :param a:to update the range of top cups and bottom cups to make it easier to code
    :param b:to update the range of top cups and bottom cups to make it easier to code
    """
    win_flag = True
    for i in range(a,b):
        if my_pons[i] != 0: #to check if any row is empty or not
            win_flag = False
    if win_flag == True:
        if my_pons[0] > my_pons[7]: #to check which mancala has the highest number of stones
            x = player
        elif my_pons[7] > my_pons[0]:
            x = player
    if win_flag == False:
        x = 1
    return x

def make_board(my_pons,player_1,player_2):
    """
    This function is a helper function for run game
    This function creates the board and returns the mancala board
    :param all_cells: It is a list to store the top row and the bottom row cups
    :param current_cell: list to append content required to create board
    :param top_rows: to show the first row
    :param bottom_rows: to show the second row
    :param first_mancala: list to append content to that particular column and row
    :param second_mancala: list to append content to that particular column and row
    """
    all_cells = []
    for i in range(7):
        current_cell = []
        current_cell.append(f'Cup * \n{i}*')
        current_cell.append(str(i))
        current_cell.append(f"Stones*")
        current_cell.append(str(my_pons[i]))
        for i in range(BLOCK_HEIGHT - 1):
            current_cell.append(" " * BLOCK_WIDTH)
        all_cells.append(current_cell)

    top_rows = all_cells[1:7]

    
    for j in range(8,14):
        current_cell = []
        current_cell.append(f'Cup * \n{i}*')
        current_cell.append(str(j))
        current_cell.append(f"Stones*")
        current_cell.append(str(my_pons[j])) #to add the number of stones in the row....keeps updating as functions are run
        for i in range(BLOCK_HEIGHT - 1):
            current_cell.append(" " * BLOCK_WIDTH)
        all_cells.append(current_cell)

        bottom_rows = all_cells[7:]
        bottom_rows = all_cells[::-1] #to reverse the bottom row so the number can be in clockwise order

        first_mancala = []
        second_mancala = []
    for i in range(BLOCK_HEIGHT * 2 + 1):
        if i == 3:
            first_mancala.append(player_2) #so that player names are shown in the two sides
            second_mancala.append(player_1)
        elif i == 6:
            first_mancala.append('Stones')
            second_mancala.append('Stones')
        elif i == 7:
            first_mancala.append(str(my_pons[0]).rjust(BLOCK_WIDTH)) #to show number of stones in mancala
            second_mancala.append(str(my_pons[7]).rjust(BLOCK_WIDTH))
        else:
            first_mancala.append(" " * BLOCK_WIDTH)
            second_mancala.append(" " * BLOCK_WIDTH)
    draw_board(top_rows, bottom_rows, first_mancala, second_mancala)



def run_game():
    """
    This function makes the game work and prints the board so it keeps updating as the player chooses the cups to be moved
    :param player_1:to call and store first player's name
    :param player_2:to call and store second player's name
    :param count:to keep track of the turns taken alternatively between player_1 and player_2
    :param move:boolean value to keep running the game until some player wins

    """
    my_pons = [0,4,4,4,4,4,4,0,4,4,4,4,4,4]
    player_1 = get_player() #calling get_player() and storing player's name
    player_2 = get_player()
    count = 0 #to keep track of the player's turn
    move = True
    make_board(my_pons,player_1,player_2)
    move = True
    while move == True:
        count += 1
        if count%2==0:#if even player_2 turn
            player = player_2
            selection = take_turn(player,my_pons,0,player_1,player_2)
            if selection == True:
                count -= 1
            if check_winner(move,my_pons,player_2,8,14) == player:
                print(player_2,' is the winner')
                move = False
            else:
                move = True
        if count%2==1:#if odd player_1 turn
            player = player_1
            selection = take_turn(player,my_pons,0,player_1,player_2)
            if selection == True:#if one player's turn is over to alternate turn nee to make it even again that is why count = count-1
                count -= 1
            if check_winner(move,my_pons,player_1,1,7) == player:
                    print(player_1,' is the winner')
                    move = False
        else:
            move = True



if __name__ == "__main__":
    run_game()
