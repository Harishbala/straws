#include <iostream>
#include <future>

int task() {
    return 0;
}
int main() {
    auto future_var = std::async(task);
    std::cout << "Task returned:" << future_var.get() << std::endl;
}
