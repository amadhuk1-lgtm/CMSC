"""
File:    network.py
Author:  Akanksha Madhu Kiran
Date:    12/11/2023
Section: 45
E-mail:  amadhuk1@umbc.edu
Description: To make a connection servers for all of the phones signed up with company.
"""

"""
Note: I have done the extra credit only to a certain point. I have not implemented it completely by disconnected the connection when end call is run.
You could input the maximum number of lines in a trunk line to be 1000 or a million to not consider it.
"""
HYPHEN = "-"
QUIT = 'quit'
SWITCH_CONNECT = 'switch-connect'
SWITCH_ADD = 'switch-add'
PHONE_ADD = 'phone-add'
NETWORK_SAVE = 'network-save'
NETWORK_LOAD = 'network-load'
START_CALL = 'start-call'
END_CALL = 'end-call'
DISPLAY = 'display'


def connect_switchboards(switchboards, area_1, area_2,number_connection):
    """
    connect_switchboards is a function which connects the switchboards across a trunk line and also keeps count of the connection in each line and stores it in a dictionary
    :param my_list: to make the value of the dictionary a 2d list and appending the area code and the number of connections in that line
    :param new_list: to make the value of the dictionary a 2d list and appending the area code and the number of connections in that line so that connection goes two ways
    :param area_1: is area code of 1st switchboard that needs to be connected
    :param area_2: is the area code of 2nd switchboard that needs to be connected
    """

    if area_1 in switchboards: # key of the dictionary switchboards is the area code
        my_list = [] # to make a 2d_list
        my_list.append(area_2)
        my_list.append(number_connection)
        switchboards[area_1].append(my_list) # making the value of the dictionary a 2d list
        
        new_list= []
        new_list.append(area_1)
        new_list.append(number_connection)
        switchboards[area_2].append(new_list)

    return switchboards


def add_switchboard(switchboards, area_code):
    """
    This function adds the area codes as the keys of the dictionary switchboards
    :param area_code: area code of the switchboard that needs to be added as a key to dictionary
    :param my_list: is an empty list that is the value of the dictionary which later is appended in connect_switchboards function
    """
    my_list = [] # make it an empty list to later append the connected switchboards
    if area_code in switchboards: #if the area code already exists pass
        pass

    else:
        switchboards[area_code] = my_list # if it does not then add it to the dictionary as a key

    return switchboards


def add_phone(phone_switchboard, area_code, phone_number):
    """
        This function adds phone numbers to the dictionaries named phone_switchboard
        ;param area_code: area code of the switchboard which has phone numbers. Area code is the key of the dictionary.
        :param phone_number: is the number inputed after the area code
    """
    if area_code in phone_switchboard:
        phone_switchboard[area_code].append(phone_number) #to add the phone number in the list(value of dictionary)

    else:
        phone_switchboard[area_code] = [] # make it into a list so that multiple numbers can be connected to the same area code
        if phone_number in phone_switchboard[area_code]:
            pass
        else:
            phone_switchboard[area_code].append(phone_number) # if phone number has not been added yet need to be appended to the list(value)


    return phone_switchboard

def save_network(switchboards,phone_switchboard, file_name):
    """
    This function saves the network made
    :param file: to open the file name mentioned by user
    :param switchboards: dictionary with area codes and connected area codes along with the number of connections
    :param value_list: to store the 2d list in a variable
    :param value_pair: to store the inner list(sub list) into a variable
    :param j: to store only the connected switchboards 
    :param phone: to store the value of the phone_switchboard dictionary
    """
    file = open(file_name,'w') 
    for i in switchboards:
        file.write(str(i)+ ';') # to seperate area codes and connected area codes by ;
        value_list = switchboards[i]
        for value_pair in value_list:#to seperate the connected area code and the number of connections
            j = value_pair[0]
            file.write(str(j))
            file.write(' ')

        file.write(';')
        for k in phone_switchboard:
            phone = phone_switchboard[k] # to get the list(value of dictionary) to loop through and print each number side by side
            for l in phone:
                if k == i: #to make sure the area code of that particular numbers match with what is written into the file
                    file.write(str(l)+ ' ') 
        file.write('\n') #to print in newline

    file.close()


def load_network(file_name):
    """
    This function helps to load back the switchboards, connections and the phone numbers
    :param file_name: the name of the file to load.
    :param switchboards: a dictionary to store area codes and the other connected area codes
    :param phone_switchboard: A dictionary to store area codes and their specific phone numbers
    :param lines: to store ecah line in the file
    :param data: is a list containing area codes, connected area codes and phone numbers
    :param phone: phone numbers connected to each area codes
    :param my_list: to make the two dictionaries in one list so it can be returned and then splitted into the two dictionaries again
    """
    switchboards = {}
    phone_switchboard = {}
    file = open(file_name,'r')
    lines = file.readlines()
    my_list = []
    for line in lines: #to go through each lines

        data = line.split(';') #to seperate area codes, connected area codes and phone numbers

        area_code = int(data[0]) #area code

        new_list = []

        connect_area = data[1].split() # connected area codes
        for i in range(len(connect_area)):
            inner_list = []
            inner_list.append(int(connect_area[i])) # to make a 2d list
            inner_list.append(0) # to make all connections 0 as all calls have been disconnected when reloaded
            new_list.append(inner_list)

        switchboards[area_code] = new_list #making area code as key and value as 2d list containing connected area code and the connections in that line

        phone = data[2] # phone numbers
        phone = phone.strip()
        if phone!= '': # if no phone numbers are connected
            phone = int(phone)
        if area_code in phone_switchboard and phone != '':
            phone_switchboard[area_code].append(phone) # to make phone numbers includedin a list and the value of the dictionary

        else:
            phone_switchboard[area_code] = []
            if phone != '':
                phone_switchboard[area_code].append(phone)
        my_list.append(switchboards)
        my_list.append(phone_switchboard)

    return my_list


def start_call(switchboards, start_area, start_number, end_area, end_number,connection,phone_switchboard,number_connection,max_connection):
    """
    :param switchboards: Dictionary containing switchboard connections.
    :param start_area: Area code of the starting switchboard.
    :param start_number: Phone number of the caller.
    :param end_area: Area code of the destination switchboard.
    :param end_number: Phone number of the called number.
    :param connection: Dictionary containing active phone connections.
    :param phone_switchboard: Dictionary containing phone numbers for each switchboard.
    :param number_connection: Number of connections on the trunk line.
    :param max_connection: Maximum number of connections in each line
    """
    visited = {}
    for key in switchboards:
        visited[key] = False #to keep it empty first
    if start_area == end_area:#to connect if in same switchboard
                print(str(start_area) + '-' + str(start_number) + ' and ' + str(end_area) + '-' + str(end_number) + ' are now connected.')
                if start_number in connection:# to add in another dictionary to keep track of the numbers on call
                    connection[start_number].append(end_number)
                elif end_number in connection:
                    connection[end_number].append(start_number)
                else:
                    connection[start_number] = end_number
                    connection[end_number] = start_number
                return connection
    else:
        pass

    my_list = network_make(switchboards, start_area, start_number, end_area, end_number, visited,max_connection) # to store path taken
    if len(my_list) >= 2 :
        if my_list[0] == start_area and my_list[len(my_list) - 1] == end_area: # to check if it starts and ends at the right switchboard
            
            if phone_switchboard[start_area] and phone_switchboard[end_area]:
                print(str(start_area) + '-' + str(start_number) + ' and ' + str(end_area) + '-' + str(end_number) + ' are now connected.')


                for i in range(len(my_list)):
                    for value_pair in switchboards[my_list[i]]:
               
                        if i != len(my_list)-1:
                            
                            if my_list[i] == [value_pair][0]:#to add one as number of connections in a trunk line
                                value_pair[1] += 1
                                if value_pair[1] > max_connection: #to check if it exceeds the limit
                                    print('Failed to connect as exceeding limit')
                                    return connection
                            elif my_list[i+1] == [value_pair][0]:

                                value_pair[1] += 1
                                if value_pair[1] > max_connection:
                                    print('Failed to connect as exceeding limit')
                                    return connection
                            elif my_list[i-1] == [value_pair][0]:
                                
                                value_pair[1] += 1
                                if value_pair[1] > max_connection:
                                    print('Failed to connect as exceeding limit')
                                    return connection
                            else:
                              
                                value_pair[1] += 1
                                if value_pair[1] > max_connection:
                                    print('Failed to connect as exceeding limit')
                                    return connection
                        elif i == len(my_list)-1:
                            value_pair[1] += 1
                            if value_pair[1] > max_connection:
                                    print('Failed to connect as exceeding limit')
                                    return connection
                        else:
                            value_pair[1] += 0 # to not add if no connections are made
                            
                            

                if start_number in connection:
                    connection[start_number].append(end_number)
                elif end_number in connection:
                    connection[end_number].append(start_number)
                else:
                    connection[start_number] = end_number
                    connection[end_number] = start_number
            else:
                print(str(start_area) + '-' + str(start_number) + ' and ' + str(end_area) + '-' + str(end_number) + ' are not connected.')



        else:
            print(str(start_area) + str(start_number) + ' and ' + str(end_area) + str(end_number) + ' were not connected.')
                

        
    return connection


def network_make(switchboards, start_area, start_number, end_area, end_number, visited,max_connection):
    """
    Build a network path from the starting switchboard to the destination switchboard.
    
    :param switchboards: Dictionary containing switchboard connections.
    :param start_area: Area code of the starting switchboard.
    :param start_number: Phone number of the caller.
    :param end_area: Area code of the destination switchboard.
    :param end_number: Phone number of the called number.
    :param visited: Dictionary to keep track of visited switchboards.
    :param max_connection: Maximum number of connections on the trunk line.
    :return: List representing the network path.
    """
    path = []  # set the path to empty at first, this will contain the path from the current place that we start to the end.

    if start_area == end_area:  # if we've reached the end, then begin constructing the path from the back.
        
        return [end_area]
    # setting the visited to true so we don't loop back.

    visited[start_area] = True
    for value_pair in switchboards[start_area]:
        for next_place in value_pair:
            if not visited[next_place]:
                pass
                 
                if value_pair[1] <= max_connection:
                    path = network_make(switchboards, next_place ,start_number, end_area, end_number, visited,max_connection)
                else:
                    print('Exceeding the connection limit')

                if path:

                    return [start_area] + path

    visited[start_area] = False
    # essentially this will return if no path is found, i.e. we still have  path = []
    return path


def end_call( switchboards,start_area, start_number, phone_switchboard,connection):
    """
    This function ends an active phone call.
    
    :param switchboards: Dictionary containing switchboard connections.
    :param start_area: Area code of the starting switchboard.
    :param start_number: Phone number of the caller.
    :param phone_switchboard: Dictionary containing phone numbers for each switchboard.
    :param connection: Dictionary containing active phone connections.
    """
 
    found = False
    saved_key = 0
    for i in connection:
        if start_number == connection[i]:
            found = True
            saved_key = i

    if start_number in connection: #to check what is inputed and remove from dictionary and to print
        value = connection[start_number]
        del connection[start_number]
        del connection[value]
        print('Hanging up...')
        print('Connection Terminated.')

    elif found:

        del connection[saved_key] #to make sure it prints 'Hanging up....' if the call is cut by either caller. 
        del connection[start_number]
        print('Hanging up...')
        print('Connection Terminated.')

    else:
        print('Unable to disconnect')
    


    
 
def display(switchboards,phone_switchboard,connection):
    """
    This function displays information about the switchboards, connections, and phone numbers.
    
    :param switchboards: Dictionary containing switchboard connections.
    :param phone_switchboard: Dictionary containing phone numbers for each switchboard.
    :param connection: Dictionary containing active phone connections.
    """
    for area_code, value in switchboards.items():
        print('Switchboard with area code: ', area_code)
        print('\t' + 'Trunk lines are: ')
       
        value = switchboards[area_code]
   

        if switchboards[area_code] != []:
            for i in range(len(switchboards[area_code])):
                connection_area = switchboards[area_code][i] 
                connect_area = connection_area[0]
                print('\t' + '\t' + 'Truck line connection to:',connect_area)

        print('\t'+'Local phone numbers are: ')

        if (area_code in phone_switchboard):
            phone = phone_switchboard[area_code]
            if phone_switchboard[area_code] != []:
                if connection:
                    for i in phone:
                        if connection.get(i,'0') or i in connection.get(i,"0"):
                            print('\t' + '\t' + 'Phone with number: '+str(i)+ ' is connected to '+str(connection[i]))
                            
                        else:
                            for j in i:
                                print('\t' + '\t' + 'Phone with number: '+ str(j) + ' is not in use' )
                            
                else:
                    for i in phone:

                        print('\t' + '\t' + 'Phone with number: '+ str(i) + ' is not in use' )


        
if __name__ == '__main__':
    switchboards = {} 
    phone_switchboard = {}
    connection = {}
    number_connection = 0
    my_list = []
    max_connection = int(input('Input the maximum number of phone calls that can be put on a single trunk line at any time: '))
    s = input('Enter command: ')
    while s.strip().lower() != QUIT:
        split_command = s.split()
        if len(split_command) == 3 and split_command[0].lower() == SWITCH_CONNECT:
            area_1 = int(split_command[1])
            area_2 = int(split_command[2])
            switchboards = connect_switchboards(switchboards, area_1, area_2,number_connection)
        elif len(split_command) == 2 and split_command[0].lower() == SWITCH_ADD:
            switchboards = add_switchboard(switchboards, int(split_command[1]))
        elif len(split_command) == 2 and split_command[0].lower() == PHONE_ADD:
            number_parts = split_command[1].split('-')
            area_code = int(number_parts[0])
            phone_number = int(''.join(number_parts[1:]))
            phone_switchboard = add_phone(phone_switchboard, area_code, phone_number)
        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_SAVE:
            save_network(switchboards,phone_switchboard, split_command[1])
            print('Network saved to {}.'.format(split_command[1]))
        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_LOAD:
            #switchboards = load_network(split_command[1])
            my_list = load_network(split_command[1])
            switchboards = my_list[0]
            phone_switchboard = my_list[1]
            print('Network loaded from {}.'.format(split_command[1]))
        elif len(split_command) == 3 and split_command[0].lower() == START_CALL:
            src_number_parts = split_command[1].split(HYPHEN)
            src_area_code = int(src_number_parts[0])
            src_number = int(''.join(src_number_parts[1:]))

            dest_number_parts = split_command[2].split(HYPHEN)
            dest_area_code = int(dest_number_parts[0])
            dest_number = int(''.join(dest_number_parts[1:]))
            connection = start_call(switchboards, src_area_code, src_number, dest_area_code, dest_number,connection,phone_switchboard,number_connection,max_connection)

        elif len(split_command) == 2 and split_command[0].lower() == END_CALL:
            number_parts = split_command[1].split(HYPHEN)
            area_code = int(number_parts[0])
            number = int(''.join(number_parts[1:]))
            end_call(switchboards, area_code, number,phone_switchboard,connection)

        elif len(split_command) >= 1 and split_command[0].lower() == DISPLAY:
            display(switchboards,phone_switchboard,connection)

        s = input('Enter command: ')
