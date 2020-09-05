#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>

using nlohmann::json;
int main()
{
    auto json_array = json::array();
    
    json j1;
    j1["label"] = "Plato";
    j1["neighbors"] = {"Socrates", "Aristotle", "Pythagoras"};
    j1["weights"] = {1,2,3};
    json_array.push_back(j1);

    json j2;
    j2["label"] = "Aristotle";
    j2["neighbors"] = {"Parmenides", "Plato", "Archimedes"};
    j2["weights"] = {4,5,6};
    json_array.push_back(j2);

    json j3;
    j3["label"] = "Descartes";
    j3["neighbors"] =  {"Leibniz", "Spinoza", "Hume"};
    j3["weights"] = {7,8,9};
    json_array.push_back(j3);

    json j4;
    j4["label"] = "Kant";
    j4["neighbors"] = {"Hegel", "Descartes", "Schopenhauer"};
    j4["weights"] = {10,11,12};
    json_array.push_back(j4);

    std::ofstream o("graph.json");
    o << std::setw(4) << json_array << std::endl;
}
