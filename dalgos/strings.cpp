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

int binary_search(std::string& str, char c, int left, int right)
{
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

int search_rotated(std::string str, char target) {
    int left = 0;
    int right = str.size() - 1;
    int mid = 0;

    while(left <= right) {
        mid = (left + right) / 2;

        if(str[0] < str[mid]) {
            left = mid + 1;
        }
        else if(str[0] > str[mid]) {
            if (str.size() > 2) {
                if (str[mid-1] > str[mid]) {
                    break;
                }
                else {
                    right = mid - 1;
                }
            }
            else {
                mid += 1;
                break;
            }
        }
        else {
            mid += 1;
            break;
        }
    }
    int index = -1;
    
    if(target < str[0])
        index = binary_search(str, target, mid, str.size()-1);
    else
        index = binary_search(str, target, 0, mid-1);
    
    return index;
}

int main()
{
    std::string str{"Helloworld"};

    sort(begin(str), end(str));
    
    std::cout <<str<<'\n';
    std::cout <<binary_search(str, 'o') <<'\n';

    std::rotate(begin(str), begin(str) + 3, end(str));
    
    std::cout << str << '\n';
    std::cout <<search_rotated(str, 'o') <<'\n';
}
