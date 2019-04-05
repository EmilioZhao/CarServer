#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h> 
#include <iostream>


enum Consts{
    PORT = 8888,
    SIZE = 4096
};
int main() {
    // new socket
    std::cout << "STARTING TO creat client socket" << std::endl;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        std::cerr << "Fail to create sokcet: ret " << fd << std::endl;
        return -1; 
    }
    struct sockaddr_in my_addr, server_addr;
    memset(&server_addr, '0', sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }

    // connect to server
    if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Fail to create sokcet" << fd << std::endl;
        return -1; 
    }else {
        std::printf("Succeed to connect the Server[%d]", fd);
    }

    // send message
    char *hello = "Hello from client"; 
    ssize_t n_send = send(fd, hello, strlen(hello), 0);
    printf("Hello message sent %d Bytes\n", (int)n_send); 
    char buffer[1024] = {0};
    int nums = read(fd, buffer, 1024); 
    printf("Read %d Bytes: %s\n", nums, buffer); 
    return 0;

}
