#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

//#define PORT 8888
//#define SIZE 4096
namespace zzy {
namespace car {
}
}
    //enum hack to replace #Macro
    enum var {
        PORT = 8888,
        SIZE = 4096
    };
    int main(int argc, const char* argv[]) {
        // create socket: IPv4, TCP, IP
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (0 == fd) {
            std::cerr << "Fail to create Server sokcet" << std::endl;
            return -1; 
        }

        // bind port 
        int opt = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); // reuse address
        struct sockaddr_in my_addr;
        my_addr.sin_family = AF_INET;
        my_addr.sin_addr.s_addr = INADDR_ANY;
        my_addr.sin_port = htons(PORT);
        if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
            std::cerr << "Fail to bind PORT " << PORT << std::endl;
            return -1;
        }

        // listen to channel with message buffer queue size
        int queue_size = 10;
        if (listen(fd, queue_size) < 0) {
            std::cerr << "Fail to listen PORT " << PORT << std::endl;
            return -1;
        } else {
            std::cerr << "SUCC to listen to PORT " << PORT << std::endl;
        } 

        // accept & read message
        int addr_len = sizeof(my_addr);
        int client_fd = accept(fd, (sockaddr *)&my_addr, (socklen_t *)&addr_len);
        if (client_fd < 0) {
            std::cerr << "Fail to accept message " << std::endl;
            return -1; 
        } else {
            std::printf("Server [%d] accept client[%d]'s connection]\n", fd, client_fd);
        }
        char buffer[1024] = {0};
        // send message
        char* hello = "Hello from Server!";
        int nums = send(client_fd, hello, strlen(hello), 0);
        printf("Send %d Bytes to client\n", nums);
        nums = read(client_fd, buffer, 1024);
        std::cout << "[GET] " << nums << "B Message: " << buffer << std::endl;
        return 0;
    }


