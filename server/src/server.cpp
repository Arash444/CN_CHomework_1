#include "server.hpp"
#include "cmdHandler.hpp"
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

Server::Server(
const std::string& config_path, 
const std::string& rooms_path,
const std::string& user_info_path) 
:jsonReader(JsonReader(config_path, rooms_path, user_info_path))
{
    hostName = jsonReader.getHostName();
    commandChannelPort = jsonReader.getCommandChannelPort();
    allUsers = jsonReader.getUsers();
    allRooms = jsonReader.getRooms();
}

struct sockaddr_in initialSocket(const int port,const std::string& hostName) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(hostName.c_str());
    address.sin_port = htons(port);
    return address;
}

int setupServer(int port,const std::string& hostName) {
    struct sockaddr_in address = initialSocket(port, hostName);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 8);
    return server_fd;
}

void* handleConnection(int i) {
    
}

int Server::checkUser(std::string )
{

}

void Server::setServerDate(void)
{
    std::string In_date;
    while (true)
    {
        std::cout << "setTime ";
        std::cin >> In_date;
        if (CurrentDate.setDate(In_date))
        {
            break;
        }
        elseS
        {
            std::cout << termcolor::red << "Error 401: Invalid value!" << termcolor::reset << std::endl;
        }
    }
}


void Server::run() {
    int fd_socket = setupServer(commandChannelPort, hostName);

    fd_set master_set, working_set;
    FD_ZERO(&master_set);
    FD_ZERO(&working_set);
    FD_SET(fd_socket, &master_set);
    int max_fd = fd_socket;
    int return_select;
    
    

    setServerDate();

    while(true) {
        working_set = master_set;       
        return_select = select(max_fd + 1, &working_set, NULL, NULL, NULL);
        if (return_select < 0) {
            std::cerr << "Error in select" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i <= max_fd; i++) {

            ///check this next time 
            if (FD_ISSET(i, &working_set)) {
                if (i == fd_socket) {
                    int new_socket = accept(fd_socket, NULL, NULL);
                    FD_SET(new_socket, &master_set);
                    if (new_socket > max_fd) {
                        max_fd = new_socket;
                    }
                }
                else {
                    //using cmdHandler check connection between client & server
                    char read_buffer[1024];
                    memset(read_buffer, 0, sizeof(read_buffer));

                    char write_buffer[1024];
                    memset(write_buffer, 0, sizeof(write_buffer));

                    CmdHandler* commandHandler = new CmdHandler();
                    int logged_in = 0;
                    User* logged_in_user;
                    while (true) {
                        if (logged_in == 1)
                        {
                            memset(read_buffer, 0, sizeof(read_buffer));
                            std::string message = "1. View user information\n2. View all users\n3. View rooms information\n4. Booking\n5. Canceling\n6. pass day\n7. Edit information\n8. Leaving room\n9. Rooms\n0. Logout";
                            strcpy(write_buffer, message.c_str());
                            send(i, write_buffer, sizeof(write_buffer), 0);
                            memset(write_buffer, 0, sizeof(write_buffer));
                            recv(i, read_buffer, sizeof(read_buffer), 0);
                            //commands
                            if(strcmp(read_buffer, "0") == 0)//logout
                            {
                                logged_in = 0;
                                std::cout << "Client " << i << " disconnected" << std::endl;
                                close(i);
                                FD_CLR(i, &master_set);
                                break;
                            }
                            else if(strcmp(read_buffer, "1") == 0)//View user information
                                std::string message = logged_in_user->viewUser();

                            else if(strcmp(read_buffer, "2") == 0)//View all users
                            {
                                if(logged_in_user->getAdmin())
                                {
                                    for(int j=0;j<this->allUsers.size();j++)
                                    {
                                        std::string message = this->allUsers[j]->viewUserForAdmin();
                                        strcpy(write_buffer, message.c_str());
                                        send(i, write_buffer, sizeof(write_buffer), 0);
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                    }
                                    std::string message = "Error 110: Successfully done!";
                                }
                                else
                                    std::string message = "Error 403: Access denied!";
                            }
                            else if(strcmp(read_buffer, "3") == 0)//View rooms information
                            {
                                if(logged_in_user->getAdmin())
                                {
                                    for(int j=0;j<this->allRooms.size();j++)
                                    {
                                        std::string message = this->allRooms[j]->viewRoomForAdmin()
                                        strcpy(write_buffer, message.c_str());
                                        send(i, write_buffer, sizeof(write_buffer), 0);
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                    }
                                }
                                else
                                {
                                    for(int j=0;j<this->allRooms.size();j++)
                                    {
                                        std::string message = this->allRooms[j]->viewRoom()
                                        strcpy(write_buffer, message.c_str());
                                        send(i, write_buffer, sizeof(write_buffer), 0);
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                    }
                                }
                                std::string message = "Error 110: Successfully done!";
                            }

                            else if(strcmp(read_buffer, "4") == 0)//Booking
                            {
                                //getting command
                                memset(read_buffer, 0, sizeof(read_buffer));
                                recv(i, read_buffer, sizeof(read_buffer), 0);

                                std::stringstream ss(read_buffer);
                                std::vector<std::string> command;
                                while (getline(ss, s, ' ')) // store token string in the vector
                                    command.push_back(s);

                                if(command.size() == 5 && !strcmp(command[0], "book"))
                                {
                                    int roomPrice = -1;
                                    bool is_available = true;
                                    Room curr_room;
                                    for(int j=0;j<this.allRooms.size();j++)
                                    {
                                        if(this.allRooms[j]->getNumber() == stoi(command[1]))
                                        {
                                            roomPrice = this.allRooms[j].getPrice();
                                            is_available = this.allRooms[j].isRoomAvailabe(command[2], 
                                            this->CurrentDate.getCurrentDay());
                                            curr_room = allRooms[j];
                                            break;
                                        }
                                    }
                                    if(roomPrice == -1)
                                        std::string message = "Error 101: The desired room was not found.";
                                    else if (!is_available)
                                        std::string message = "Error 109: The room capacity is full!";
                                    else
                                    {
                                        if(logged_in_user->getPurse() >= roomPrice * stoi(command[2]))
                                        {
                                            logged_in_user->setPurse(roomPrice * stoi(command[2]));
                                            logged_in_user->Reserve(stoi(command[2]), stoi(command[3]), command[4], command[5]);
                                            curr_room->addUser(logged_in_user);
                                            std::string message = "Error 110: Successfully done!";
                                        }
                                        else
                                            std::string message = "Error 108: Your account balance is not enough!";
                                    } 
                                }
                                else
                                    std::string message = "Error 503: bad sequence of commands.";
                                }
                            else if(strcmp(read_buffer, "5") == 0)//Canceling
                            {
                                std::string message = logged_in_user->showAllReservations();
                                strcpy(write_buffer, message.c_str());
                                send(i, write_buffer, sizeof(write_buffer), 0);
                                memset(write_buffer, 0, sizeof(write_buffer));

                                memset(read_buffer, 0, sizeof(read_buffer));
                                recv(i, read_buffer, sizeof(read_buffer), 0);

                                std::stringstream ss(read_buffer);
                                std::vector<std::string> command;
                                 while (getline(ss, s, ' ')) // store token string in the vector
                                    command.push_back(s);

                                if(command.size() == 3 && !strcmp(command[0], "cancel"))
                                {
                                    int roomPrice = -1;
                                    for(int j=0;j<this.allRooms.size();j++)
                                    {
                                        if(this.allRooms[j]->getNumber() == stoi(command[1]))
                                        {
                                            roomPrice = this.allRooms[j].getPrice();
                                            break;
                                        }
                                    }
                                    if(roomPrice == -1)
                                        std::string message = "Error 101: The desired room was not found.";

                                    else if (!(logged_in_user->canCancel(stoi(command[1]), stoi(command[2]),
                                        this->CurrentDate.getCurrentDay())))
                                        std::string message = "Error 102: Your reservation was not found.";
                                    else
                                    { 
                                        logged_in_user->setPurse(-(roomPrice/2) * stoi(command[2]));
                                        logged_in_user->Cancel(stoi(command[1]), stoi(command[2]), 
                                        this->CurrentDate.getCurrentDay());
                                        std::string message = "Error 110: Successfully done!";
                                    }
                                }
                                else
                                    std::string message = "Error 503: bad sequence of commands.";
                            }
                            else if(strcmp(read_buffer, "6") == 0)//pass days
                            {
                                if(logged_in_user->getAdmin())
                                {
                                    memset(read_buffer, 0, sizeof(read_buffer));
                                    recv(i, read_buffer, sizeof(read_buffer), 0);

                                    std::stringstream ss(read_buffer);
                                    std::vector<std::string> command;
                                    while (getline(ss, s, ' ')) // store token string in the vector
                                        command.push_back(s);
                                    if(command.size() == 2 && command[0] == "passDay")
                                    {
                                        this->CurrentDate.passDay(command[1]);
                                        for(int i = 0; i < this->allRooms.size(); i++)
                                            this->allRooms[i].passDay(this->CurrentDate.getCurrentDay())
                                        std::string message = "Error 110: Successfully done!";
                                    }
                                    else
                                        std::string message = "Error 503: bad sequence of commands.";
                                }
                                else
                                    std::string message = "Error 403: Access denied!";
                            }
                            else if(strcmp(read_buffer, "7") == 0) //edit information
                            {
                                if(logged_in_user->getAdmin())
                                {
                                    memset(read_buffer, 0, sizeof(read_buffer));
                                    recv(i, read_buffer, sizeof(read_buffer), 0);

                                    std::stringstream ss(read_buffer);
                                    std::vector<std::string> command;
                                    while (getline(ss, s, ' ')) // store token string in the vector
                                        command.push_back(s);
                                    if(command.size() == 2)
                                    {
                                        logged_in_user->updatePassword(command[1]);
                                        std::string message = "Error 110: Successfully done!";
                                    }
                                    else
                                        std::string message = "Error 503: bad sequence of commands.";
                                }
                                else
                                {
                                    //password
                                    string new_phone_number, new_password;
                                    memset(read_buffer, 0, sizeof(read_buffer));
                                    recv(i, read_buffer, sizeof(read_buffer), 0);
                                    std::stringstream ss(read_buffer);
                                    std::vector<std::string> command;
                                    while (getline(ss, s, ' ')) // store token string in the vector
                                        command.push_back(s);
                                    if(command.size() == 2)
                                    {
                                        new_password = command[1];
                                        //phone number
                                        memset(read_buffer, 0, sizeof(read_buffer));
                                        recv(i, read_buffer, sizeof(read_buffer), 0);
                                        std::stringstream ss(read_buffer);
                                        std::vector<std::string> command1;
                                        while (getline(ss, s, ' ')) // store token string in the vector
                                            command1.push_back(s);
                                        if(command1.size() == 2)
                                        {
                                            new_phone_number = command1[1];
                                            //address
                                            memset(read_buffer, 0, sizeof(read_buffer));
                                            recv(i, read_buffer, sizeof(read_buffer), 0);
                                            stringstream ss(read_buffer);
                                            vector<string> command2;
                                            while (getline(ss, s, ' ')) // store token string in the vector
                                                command2.push_back(s);
                                            if(command2.size() == 2)
                                            {
                                                logged_in_user->updatePassword(new_password);
                                                logged_in_user->updatePhoneNumber(new_phone_number);
                                                logged_in_user->updateAdress(command2[1]);
                                                std::string message = "Error 110: Successfully done!";
                                            }
                                            else
                                                std::string message = "Error 503: bad sequence of commands.";
                                        }
                                        else
                                            std::string message = "Error 503: bad sequence of commands.";
                                    }
                                    else
                                        std::string message = "Error 503: bad sequence of commands.";
                                }
                            }
                            else if(strcmp(read_buffer, "8") == 0)//Leaving
                            {
                                memset(read_buffer, 0, sizeof(read_buffer));
                                recv(i, read_buffer, sizeof(read_buffer), 0);

                                std::stringstream ss(read_buffer);
                                std::vector<std::string> command;
                                 while (getline(ss, s, ' ')) // store token string in the vector
                                    command.push_back(s);

                                if(command.size() == 3 && !strcmp(command[0], "room"))
                                {
                                    bool hasBookedRoom = false, has_checked_in = false;
                                    for(int j=0;j<this.allRooms.size();j++)
                                    {
                                        if(this.allRooms[j]->getNumber() == stoi(command[1]))
                                        {
                                            hasBookedRoom = true;
                                            if(logged_in_user->hasCheckedIn(this->CurrentDate.getCurrentDay(), i))
                                                has_checked_in = true;
                                            break;
                                        }
                                    }
                                    if(!hasBookedRoom)
                                        std::string message = "Error 503: bad sequence of commands.";

                                    else if (!has_checked_in)
                                        std::string message = "Error 102: Your reservation was not found.";
                                    else
                                    { 
                                        logged_in_user->Leave(stoi(command[1]), this->CurrentDate.getCurrentDay());
                                        std::string message = "Error 413: Successfully leaving!";
                                    }
                                }
                                else
                                    std::string message = "Error 503: bad sequence of commands.";
                            }
                            else if(strcmp(read_buffer, "9") == 0) //rooms
                            {
                                if(logged_in_user->getAdmin())
                                {
                                    for(int j=0;j<this->allUsers.size();j++)
                                    {
                                        memset(read_buffer, 0, sizeof(read_buffer));
                                        recv(i, read_buffer, sizeof(read_buffer), 0);
                                        std::stringstream ss(read_buffer);
                                        std::vector<std::string> command1;
                                        while (getline(ss, s, ' ')) // store token string in the vector
                                            command1.push_back(s);
                                        if(command1.size() == 5 && command[1] == "add")
                                        {
                                            bool does_room_num_exist = false;
                                            for(int i = 0; i < allRooms.size(); i++)
                                            {
                                                if(allRooms[j].getNumber() == command[2])
                                                {
                                                    does_room_num_exist = true;
                                                    break;
                                                }
                                            }
                                            if(does_room_num_exist)
                                                std::string message = "Error 111: This room already exists!";
                                            else
                                            {
                                                std::vector<User*> allUsersNew;
                                                allRooms.push_back(new Room(command[2], false, command[3], command[4], 0, allUsersNew))
                                                std::string message = "Error 104: Successfully added!";
                                            }
                                        }
                                        else if(command1.size() == 5 && command[1] == "modify") 
                                        {
                                            bool found_room_num = false;
                                            for (int i = 0; i < allRooms.size(); i++)
                                            {
                                                if(allRooms[i] == room_num)
                                                {
                                                    found_room_num = true;
                                                    if(allRooms[i].isRoomOccupied(command[2]))
                                                        std::string message = "Error 109: The room capacity is full!";
                                                    else
                                                    {
                                                        allRooms[i].modifyRoom(command[2], command[3]);
                                                        std::string message = "Error 105: Successfully modified!";
                                                    }
                                                    break;
                                                }
                                            }   
                                            if (!found_room_num)
                                                std::string message = "Error 101: Desired room was not found!";
                                        }
                                        else if(command1.size() == 3 && command[1] == "remove") 
                                        {
                                            bool found_room_num = false;
                                            for (int i = 0; i < allRooms.size(); i++)
                                            {
                                                if(allRooms[i] == room_num)
                                                {
                                                    found_room_num = true;
                                                    if(allRooms[i].isRoomOccupied(0))
                                                        std::string message = "Error 109: The room capacity is full!";
                                                    else
                                                    {
                                                        allRooms.erase(allRooms.begin() + i);
                                                        std::string message = "Error 110: Successfully deleted!";
                                                    }
                                                    break;
                                                }
                                            }   
                                            if (!found_room_num)
                                                std::string message = "Error 101: Desired room was not found!";

                                        }
                                        else 
                                            std::string message = "Error 503: bad sequence of commands.";
                                    }
                                }
                                else
                                    std::string message = "Error 403: Access denied!";
                            }
                        }
                        //get commands from channels and call commandHandler->runCommand()
                        int EOF_recv = recv(i, read_buffer, sizeof(read_buffer), 0);
                        if (EOF_recv == 0) { // client disconnected
                            std::cout << "Client " << i << " disconnected" << std::endl;
                            close(i);
                            FD_CLR(i, &master_set);
                            break;
                        }
                        else 
                        {
                            if (logged_in == 0)
                            {
                                // print client i sent message
                                 std::cout << "Client " << i << " sent message: ";
                                std::cout << read_buffer << std::endl; 
                                //memset(read_buffer, 0, sizeof(read_buffer));
                                // send message to client i
                                //std::string message = commandHandler->runCommand(string(read_buffer), this->allUsers);

                                //splitting command
                                std::stringstream ss(read_buffer);
                                std::vector<std::string> command;
                                while (getline(ss, s, ' ')) // store token string in the vector
                                        command.push_back(s);

                                if (!strcmp(command[0], "signin"))
                                {
                                    User* signed_in_user;
                                    if (command.size() != 3 )
                                        std::string message = "Error 430: Invalid username or password.";
                                    else
                                    {
                                        for(int j=0;j<this->allUsers.size(), j++)
                                        {
                                            signed_in_user = this->allUsers[j]->checkInfo(command[1], command[2])
                                            if(signed_in_user != NULL)
                                                break;
                                        }

                                        if(signed_in_user != NULL)//succ signedin
                                        {
                                            std::string message = "Error 230: User logged in.";
                                            logged_in = 1;
                                            logged_in_user = signed_in_user;
                                        }
                                        else//fail signin
                                            std::string message ="Error 430: Invalid username or password.";
                                    }
                                }
                                else if(!strcmp(command[0], "signup"))
                                {
                                    int userExist;
                                    if(command.size() != 2)
                                        std::string message = "Error 503: bad sequence of commands.";
                                    else
                                    {
                                        for(int j = 0; j<this->allUsers.size();j++)
                                        {
                                            if(this->allUsers[i]->checkUser(command[1]) == 1)
                                            {
                                                userExist = 1;
                                                break;
                                            }
                                        }
                                        if(userExist)
                                            std::string message = "Error 451: User already exist!";
                                        else
                                        {
                                            //sending that username is fine
                                            std::string message = "Error 311: User signed up. Enter your password, purse, phone and address.";
                                            strcpy(write_buffer, message.c_str());
                                            send(i, write_buffer, sizeof(write_buffer), 0);
                                            memset(write_buffer, 0, sizeof(write_buffer));

                                            std::string password, purse, phone, address;
                                            memset(read_buffer, 0, sizeof(read_buffer));
                                            recv(i, read_buffer, sizeof(read_buffer), 0);
                                            password = string(read_buffer);

                                            memset(read_buffer, 0, sizeof(read_buffer));
                                            recv(i, read_buffer, sizeof(read_buffer), 0);
                                            purse = string(read_buffer);

                                            memset(read_buffer, 0, sizeof(read_buffer));
                                            recv(i, read_buffer, sizeof(read_buffer), 0);
                                            phone = string(read_buffer);

                                            memset(read_buffer, 0, sizeof(read_buffer));
                                            recv(i, read_buffer, sizeof(read_buffer), 0);
                                            address = string(read_buffer);
                                            User* new_user = new User(this->allUsers.size(), command[1], password, false, purse, phone, address, 0, NULL, NULL, 0);

                                            this->allUsers.push_back(new_user);// adding new user
                                            logged_in = 1;
                                            logged_in_user = new_user;
                                            std::string message = "Error 231: User successfully singed up.";
                                        }  
                                    }
                                }
                            }
                            //sending result to client
                            strcpy(write_buffer, message.c_str());
                            send(i, write_buffer, sizeof(write_buffer), 0);
                            memset(write_buffer, 0, sizeof(write_buffer));
                        }
                    }
                }
            }
            ///check this next time 
        }
    }
}