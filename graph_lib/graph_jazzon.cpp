#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>

using nlohmann::json;
int main()
{
    json j;

    j["dummy"] = {1, 0, 2, 0};
    std::ofstream o("graph.json");
    o << std::setw(4) << j << std::endl;
}
