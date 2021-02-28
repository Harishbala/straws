#include <iostream>
#include "directory.hpp"

int main() {
    Directory dir("/Users/harish");
    std::cout << "------------------- Directories ------------------------\n";
    std::vector<std::string> entries;
    dir.get_directory_entries(entries);
    for(const auto& entry : entries) {
        if (entry != "." && entry != "..") {
            std::cout << entry << '\n';
        }
    }

    std::cout << "------------------- Files ------------------------\n";
    std::vector<std::string> file_entries;
    dir.get_file_entries(file_entries);
    for(const auto& entry : file_entries) {
        std::cout << entry << '\n';
    }
}
