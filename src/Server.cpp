#include "Server.hpp"


Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}


Server::Server(std::string port, std::string pw) : _port(port), _pw(pw)
{
	std::cout << "Server constructor called" << std::endl;
}

void	Server::launch()
{}
void	Server::generate_socket()
{
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int sockfd; // Le descripteur de la socket
    struct sockaddr_in server_addr; // Structure pour les informations du serveur

    // Créer la socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Initialiser les informations du serveur
    server_addr.sin_family = AF_INET; // Famille d'adresses Internet
    server_addr.sin_port = htons(8080); // Port (8080 dans cet exemple)
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accepter les connexions de n'importe quelle adresse IP

    // Lier la socket au port et à l'adresse
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la liaison de la socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Écouter les connexions entrantes
    if (listen(sockfd, 5) == -1) { // Vous pouvez ajuster le nombre maximal de connexions en attente (ici, 5)
        perror("Erreur lors de l'écoute de la socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexions...\n");

    // Plus de code pour accepter et gérer les connexions ici...

    // Fermer la socket lorsque vous avez terminé
    close(sockfd);

    return 0;
}*/
}
