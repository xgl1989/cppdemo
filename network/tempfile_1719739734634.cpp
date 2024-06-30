#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// crc32函数定义省略，假设已定义

void sendMessageWithProtocol(int socket_fd, const std::string& message) {
    const char START_BYTE = 0x02; // 假定起始符为STX字符
    const char END_BYTE = 0x03;   // 假定结束符为ETX字符

    std::vector<uint8_t> data(message.begin(), message.end());

    // 消息长度（假设为4字节整型）
    uint32_t length = htonl(static_cast<uint32_t>(data.size()));

    // 计算CRC32
    uint32_t crc = crc32(data);
    crc = htonl(crc);

    // 发送数据包
    send(socket_fd, &START_BYTE, sizeof(START_BYTE), 0);
    send(socket_fd, &length, sizeof(length), 0);
    send(socket_fd, data.data(), data.size(), 0);
    send(socket_fd, &crc, sizeof(crc), 0);
    send(socket_fd, &END_BYTE, sizeof(END_BYTE), 0);
}

int main() {
    // 连接到服务器的代码省略，与之前示例相同

    std::string message = "Hello, Server!";
    sendMessageWithProtocol(sockfd, message);
    std::cout << "Message sent with protocol." << std::endl;

    close(sockfd);
    return 0;
}
