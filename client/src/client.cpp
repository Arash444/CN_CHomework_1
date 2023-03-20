#include "../include/client.hpp"
#include "../include/jsonReader.hpp"
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

Client::Client() {}

int connectServer(int port, const std::string& hostName)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(hostName.c_str());
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if (connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout<<"Error in connecting to server\n";
        return -1;
    }
    return fd;
}

void Client::run() {
    std::ifstream f("../json_files/config.json");
    json j_config;
    f >> j_config;
    int fd_to_server = connectServer(j_config["commandChannelPort"], j_config["hostName"]);
    
    std::string command;
    char read_buffer[1024];
    memset(read_buffer, 0, sizeof(read_buffer));
    while(std::getline(std::cin, command)) {
        send(fd_to_server, command.c_str(), command.size(), 0);
        recv(fd_to_server, read_buffer, sizeof(read_buffer), 0);
        std::cout << read_buffer << std::endl;
    }
}