// Coding exercise for learning purpose - https://docs.websocketpp.org/md_tutorials_utility_client_utility_client.html
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;

int main()
{
    bool done = false;
    std::string input;

    while (!done) {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        }
        else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n";
        }
        else {
            std::cout << "Unrecognized Command\n";
        }
    }
    return 0;
}

