#include <iostream>

int binary_search(std::string& str, char c)
{
    int left = 0;
    int right = str.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (str[mid] < c)
            left = mid + 1;
        else if(str[mid] > c)
            right = mid - 1;
        else
            return mid;
    }

    return -1;
}

int main()
{
    std::string str{"Helloworld"};

    sort(begin(str), end(str));

    for(auto c : str) {
        std::cout <<binary_search(str, c) <<'\n';
    }
    std::cout << str << '\n';
}
