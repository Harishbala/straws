// Code reused for learning purpose - https://github.com/nlohmann/json#projects-using-json-for-modern-c
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>

using nlohmann::json;

int main()
{
    std::ifstream i("file.json");
    json j;

    i >> j;
    std::ofstream o("pretty.json");
    o << std::setw(4) << j << std::endl;
}
