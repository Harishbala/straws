#include <iostream>

void add_pipes() {
    std::string str = "This is a sample sentence";
    int i = 0;

   str.insert(i, "|");
    for (const auto c : str) {
        if (c == ' ') {
           str.replace(i, 1, "|");
            auto temp = str.substr(0, i);

           std::cout << temp << '\n';
        }
    ++i;
    }
   str.insert(i, "|");
   std::cout << str << '\n';
}

void reverse_words() {
    std::string str = "This is a sample sentence";
    int i = 0;
    int last_index = 0;
    for(const auto& c : str) {
        if(c == ' ' && i > last_index)
        {
            std::reverse(str.begin() + last_index, str.begin() + i);
            last_index = i + 1;
        }
        ++i;
    }
    if(i > last_index)
        std::reverse(str.begin() + last_index, str.begin() + i);

    std::cout << str << '\n';
}

int main() {
    add_pipes();
    reverse_words();
}
