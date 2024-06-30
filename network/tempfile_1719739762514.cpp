#include <cstdint>
#include <vector>

// 初始化CRC32表，这是一个常用的优化手段，避免每次计算时重复进行位运算
static const uint32_t crc32_table[256] = [](){
    uint32_t table[256];
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t entry = i;
        for (int j = 0; j < 8; ++j) {
            if (entry & 1) {
                entry = (entry >> 1) ^ 0x4C11DB7;
            } else {
                entry >>= 1;
            }
        }
        table[i] = entry;
    }
    return table;
}();

// CRC32校验函数
uint32_t crc32(const std::vector<uint8_t>& data) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint8_t byte : data) {
        crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ byte];
    }
    return ~crc;
}

int main() {
    std::vector<uint8_t> testData = {0x01, 0x02, 0x03, 0x04, 0x05}; // 示例数据
    uint32_t crcResult = crc32(testData);
    std::cout << "CRC32 of the data: " << std::hex << crcResult << std::endl;
    return 0;
}
