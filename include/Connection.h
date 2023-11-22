#pragma once
#include <poll.h>
#include <netdb.h> 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#define DEBUG 1
//Connection established using socket
class Connection
{
    public:
        //assigning the port and family address
        Connection(int family, int port, char* address);
        //intialisizng the socket
        void init();
        //accepting and socket and updating the values
        std::string recv();
        std::string crecv();
    private:
        //for socket internals
        int family_, port_;
        char* address_;
        struct sockaddr_in addr_, caddr_;
        socklen_t caddrlen_ = sizeof(addr_);
        socklen_t addrlen_ = sizeof(addr_);

        int socketId_; //initial connection
        int nSocket_; // accepted connection
};
