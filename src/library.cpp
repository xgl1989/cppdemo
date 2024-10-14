#include "library.h"

#include <iostream>
#include <iostream>
#ifdef _WIN32
#include <direct.h>  // Windows
#include <io.h>      // Windows, for _access
#define MKDIR(p) _mkdir(p)
#define ACCESS(p, m) _access(p, m)
#else
#include <sys/stat.h>  // POSIX
#include <sys/types.h>
#include <unistd.h>    // POSIX, for access
#define MKDIR(p, m) mkdir(p, m)
#define ACCESS(p, m) access(p, m)
#endif

void hello() {
    std::cout << "Hello, World!" << std::endl;
}


/**
 * @brief 创建目录
 *
 * @param path 要创建的目录路径
 * @return true 如果目录创建成功或已经存在
 * @return false 如果目录创建失败
 */
bool create_directory(const char* path) {
#ifdef _WIN32
    if (ACCESS(path, 0) != 0) { // 如果目录不存在 (Windows: 使用 0 作为 F_OK)
        if (MKDIR(path) == 0) { // 尝试创建目录 (Windows: _mkdir 不接受模式参数)
            std::cout << "Directory " << path << " created successfully.\n";
            return true;
        }
        else {
            std::cerr << "Failed to create directory " << path << ".\n";
            return false;
        }
    }
    else {
        std::cout << "Directory " << path << " already exists.\n";
        return true; // 如果目录已存在，返回true，因为不需要创建
    }
#else
    if (ACCESS(path, F_OK) != 0) { // 如果目录不存在 (POSIX)
        if (MKDIR(path, 0777) == 0) { // 尝试创建目录 (POSIX: mkdir 接受模式参数)
            std::cout << "Directory " << path << " created successfully.\n";
            return true;
        }
        else {
            std::cerr << "Failed to create directory " << path << ".\n";
            return false;
        }
    }
    else {
        std::cout << "Directory " << path << " already exists.\n";
        return true; // 如果目录已存在，返回true，因为不需要创建
    }
#endif
}

/**
 * @brief 检查目录是否存在，如果不存在则创建
 *
 * @param path 要检查的目录路径
 * @return true 如果目录存在或创建成功
 * @return false 如果目录创建失败
 */
bool check_and_create_directory(const char* path) {
    return create_directory(path); // 直接调用 create_directory 函数
}
