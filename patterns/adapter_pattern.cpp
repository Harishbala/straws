#include <string>
#include <iostream>
#include <vector>

#include "boost/algorithm/string.hpp"
#include <sstream>

class String {
 public:
     String(const std::string s) :
         s{s}
     {}

     String to_lower_copy() const {
         return {boost::to_lower_copy(s)};
     }

     std::vector<String> split(const std::string& delimiter = " ") const {
         std::vector<std::string> parts;
         boost::split(parts, s, boost::is_any_of(" "), boost::token_compress_on);
         return std::vector<String>(parts.begin(), parts.end());
     }

     auto get_length() const {
         return s.length();
     }
private:
     std::string s;
};
int main()
{
    String s{"Hello  world"};

    for (const auto& p : s.to_lower_copy().split())
        std::cout<<p.get_length()<<'\n';

    return 0;
}
