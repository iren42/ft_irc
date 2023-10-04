#include "Server.hpp"
#include "Colors.hpp"

int main(int ac, char **av) {

    try {
        if (ac != 3) {
            throw std::invalid_argument("Error: Invalid number of arguments.\nShould be: ./ircserver <port> <pw>");
        }
        if (!av[2][0]) { throw std::invalid_argument("Error: Invalid Password. \n Should not be an empty string."); }
        Server server(atoi(av[1]), av[2]);
        server.launch();
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n" << std::endl;
        return 1;
    }
    return (0);
}
