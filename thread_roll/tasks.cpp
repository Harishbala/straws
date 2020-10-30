// Practical experiments based on Scott Meyers Effective Modern C++ book.

#include <iostream>
#include <future>
#include <chrono>

using namespace std::literals;

int task() {
    return 0;
}

int main() {
    auto future_var = std::async(task);

    auto fut2 = std::async(std::launch::async |
                            std::launch::deferred, task);

    std::cout << "Task returned:" << future_var.get() << std::endl;

    std::cout << "Task2 returned:" << fut2.get() << std::endl;

    while (fut2.wait_for(100ms) !=  std::future_status::ready)
    {
    }
}
