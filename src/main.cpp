#include "Server.hpp"

int main(int ac, char **av) {

    try {
        if (ac != 3) {
            throw std::invalid_argument("Erreur : Nombre invalide d'arguments.\nFormat: ./ircserver <port> <mdp>");
        }
        if (!av[2][0]) { throw std::invalid_argument("Erreur: mot de passe invalide. \nIl ne doit pas être vide."); }
        Server server(atoi(av[1]), av[2]);
        server.launch();
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n" << std::endl;
        return 1;
    }
    return (0);
}
