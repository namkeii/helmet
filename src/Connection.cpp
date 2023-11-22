#include "../include/Connection.h"

Connection::Connection(int family, int port, char* address){
    family_ = family;
    port_ = port;
    address_ = address;
}

void Connection::init(){
    int opt = 1;

    //create the socket
    socketId_ = socket(family_, SOCK_STREAM, 0);
    if (socketId_ < 0 && DEBUG) { std::cout << "socket not created" << std::endl; }

    bzero((char *) &addr_, sizeof(addr_));
    struct hostent *server;
    //server = gethostbyname("192.168.169.167");
    server = gethostbyname(address_);
    bcopy((char *)server->h_addr, (char *)&addr_.sin_addr.s_addr,server->h_length);

    addr_.sin_family = family_;
    //addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port_);

    //binding
    int bindStatus = bind(socketId_, (struct sockaddr*)&addr_, sizeof(addr_));
    if (bindStatus < 0 && DEBUG){ std::cout << "Bind unsuccessfull" << std::endl; }

    //listing to atmost 1 request (since the client is fixed)
    int lstatus = listen(socketId_, 5);
    if (lstatus < 0 && DEBUG){ std::cout << "listening error" << std::endl; }
}

std::string Connection::recv(){
    char buffer[256];
    std::string connectionData = "";
    int nSocket_ = accept(socketId_, (struct sockaddr*)&caddr_, &caddrlen_);
    std::string temp;
        if (nSocket_ < 0 && DEBUG){ std::cout << "Client not accepted" << std::endl; }
        bzero(buffer,256);

        int n = read(nSocket_, buffer, 256);
        //if (buffer[0] == '\0') return connectionData;
        if (n < 0 && DEBUG){ std::cout << "Reading error" << std::endl; }

        std::cout << "Raw Data Received from sensor: ";
        for(auto ii : buffer){
            //if (ii == '\0') { break; }
            temp += ii;
            //std::cout << "in: " << temp << std::endl;
            std::cout << ii << " ";
        }
        std::cout<<std::endl;

    int count = 0;
    for(auto ii : buffer){
        if (ii == ' ') count++;
        if (count == 4) break;
        connectionData += ii;
    }
    return connectionData;
}

std::string Connection::crecv(){
    char buffer[256];
    std::string connectionData = "";
    int nSocket_ = accept(socketId_, (struct sockaddr*)&caddr_, &caddrlen_);
    std::string temp;
        if (nSocket_ < 0 && DEBUG){ std::cout << "Client not accepted" << std::endl; }
        bzero(buffer,256);

        int n = read(nSocket_, buffer, 256);
        //if (buffer[0] == '\0') return connectionData;
        if (n < 0 && DEBUG){ std::cout << "Reading error" << std::endl; }

    for(auto ii : buffer){
        connectionData += ii;
    }
    return connectionData;
}
