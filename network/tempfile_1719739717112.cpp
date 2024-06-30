#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// crc32函数定义省略，假设已定义

bool receiveAndProcessWithProtocol(int new_socket) {
    char start_byte, end_byte;
    uint32_t length, received_crc;
    std::vector<uint8_t> data;

    // 接收起始符
    if (recv(new_socket, &start_byte, sizeof(start_byte), 0) != sizeof(start_byte) || start_byte != 0x02) {
        std::cerr << "Invalid start byte." << std::endl;
        return false;
    }

    // 接收消息长度
    if (recv(new_socket, &length, sizeof(length), 0) != sizeof(length)) {
        perror("Error receiving length");
        return false;
    }
    length = ntohl(length);

    // 接收数据体
    data.resize(length);
    if (recv(new_socket, data.data(), length, 0) != static_cast<ssize_t>(length)) {
        perror("Error receiving data");
        return false;
    }

    // 接收CRC32校验值
    if (recv(new_socket, &received_crc, sizeof(received_crc), 0) != sizeof(received_crc)) {
        perror("Error receiving CRC");
        return false;
    }
    received_crc = ntohl(received_crc);

    // 接收结束符
    if (recv(new_socket, &end_byte, sizeof(end_byte), 0) != sizeof(end_byte) || end_byte != 0x03) {
        std::cerr << "Invalid end byte." << std::endl;
        return false;
    }

    // 计算收到数据的CRC32
    uint32_t computed_crc = crc32(data);

    // 验证CRC
    if (computed_crc == received_crc) {
        std::cout << "Received message: " << std::string(data.begin(), data.end()) << std::endl;
        std::cout << "CRC check passed." << std::endl;
    } else {
        std::cerr << "CRC check failed!" << std::endl;
        return false;
    }

    return true;
}

int main() {
    // 监听和接受连接的代码省略，与之前示例相同
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置套接字选项，允许端口复用
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    // 绑定
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        std::thread t([](int new_socket) {
            while (true) {
                if (receiveAndProcessWithProtocol(new_socket)) {
                    close(new_socket);
                }
            }

        }, new_socket);
    }


    return 0;
}
