#include "library.h"

#include <iostream>
#include <iostream>
#ifdef _WIN32
#include <direct.h> // Windows
#define MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h> // POSIX
#include <sys/types.h>
#define MKDIR(p) mkdir(p, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif
void hello() {
    std::cout << "Hello, World!" << std::endl;
}




// 跨平台创建目录的函数
bool create_directory(const char* path) {
    if (MKDIR(path) == 0) {
        std::cout << "Directory " << path << " created successfully.\n";
        return true;
    } else {
        std::cerr << "Failed to create directory " << path << ".\n";
        return false;
    }
}

