// Code reused for learning purpose - https://github.com/nlohmann/json#projects-using-json-for-modern-c
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>

using nlohmann::json;

int main()
{
    std::ifstream i("file.json");
    json j;

    i >> j;
    std::ofstream o("pretty.json");
    o << std::setw(4) << j << std::endl;

    std::vector<uint8_t> v = {'t', 'r', 'u', 'e'};
    json serized = json::parse(v);
    std::cout << serized << '\n';

    for (auto it = j.begin(); it != j.end(); ++it) {
        std::cout << *it << '\n';
    }
}
