#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;
void pulse(int count)
{
    for (int i  = 0; i < count; ++i) {
        std::this_thread::sleep_for(seconds{1});
        std::cout << "Pulse: " <<  i+1 << '\n';
    }
}

int main()
{
    std::thread pulse_thread {pulse, 5};
    pulse_thread.join();
}

