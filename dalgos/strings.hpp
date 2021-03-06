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

int drop_chars_to_palindrome(const std::string& str)
{
    vector<vector<int>> dyn_table;

    dyn_table.resize(str.length());
    for(int i = 0; i < str.length(); ++i) {
        dyn_table[i].resize(str.length());
    }

    for(int i = 1; i < 2; ++i) {
       for(int j = 0; j < str.length() - (i + 1); ++j) {
            if(str[j] == str[j + i])
            {
                dyn_table[i][j] = 0; 
            }
            else {
               dyn_table[i][j] = 1;
               dyn_table[i][j+1] = 1; 
            }
        }
    }
    for(int i = 0; i < str.length(); ++i) {
        for (int j = 0; j< str.length(); ++j) {
            std::cout<< dyn_table[i][j] <<' ';
        }
        std::cout << '\n';
    }

    for(int i = 1; i <= str.length(); ++i) {
        for(int j = 0; j < str.length() - i; ++j) {
            if(str[j] == str[j + i]) {
                dyn_table[i][j] = dyn_table[i-1][j+1];
            }
            else {
                int left_max = dyn_table[i-1][j];
                int right_max = dyn_table[i-1][j+1];
                dyn_table[i][j] = std::max(left_max, right_max);
            }
        }
    }
    return 0;
}


void filter_duplicated_from_sorted(std::string& str)
{
    auto current_unique = str.begin();
    for(auto it = str.begin() + 1; it != str.end(); ++it)
    {
        if(*current_unique != *it) {
            it = str.erase(current_unique + 1, it);
            current_unique = it;
        }
    }
}

