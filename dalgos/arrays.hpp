#include <iostream>
#include <vector>

int max_contiguous_sum(std::vector<int>& nums_one) {

    int max_sum = INT_MIN; 
    int current_big_sum = INT_MIN;
    for(int i = 0; i < nums_one.size(); ++i) {
        int temp = current_big_sum + nums_one[i];
        
        if(temp > current_big_sum) {
            current_big_sum = temp;

            if(current_big_sum > max_sum)
                max_sum = current_big_sum;
        }
    }
    return max_sum;
}
