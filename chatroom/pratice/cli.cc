#include <cstdio>
#include <string>
#include <iostream>
#include <thread>

int main() {
    constexpr size_t buffer_size = 2024 * 2024;  // 设置缓冲区大小为 1 MB
    char buffer[buffer_size];

    // 设置 stdout 的缓冲区为自定义缓冲区
    std::setvbuf(stdout, buffer, _IOFBF, buffer_size);

    // 之后的输出将使用设置的缓冲区大小
    std::string a;
    std::getline(std::cin,a);
    std::cout << a << std::endl;

    return 0;
}