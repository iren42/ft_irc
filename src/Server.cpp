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
{
	//checker le port
	generate_socket();
}

void	Server::generate_socket(int port, )
{
/*#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 6667 // Port IRC standard

int main() {
    int server_socket;
    sockaddr_in server_addr;

    // Créez la socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Initialisez la structure sockaddr_in
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Écoutez sur toutes les interfaces réseau
    server_addr.sin_port = htons(PORT);

    // Liez la socket à l'adresse et au port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la liaison de la socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Mettez la socket en mode écoute
    if (listen(server_socket, 5) == -1) {
        perror("Erreur lors de la mise en mode écoute de la socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Serveur IRC en attente de connexions sur le port " << PORT << "..." << std::endl;

    // Vous pouvez maintenant accepter les connexions entrantes, gérer les clients IRC, etc.

    // Fermez la socket du serveur lorsque vous avez terminé
    close(server_socket);

    return 0;
}*/

	struct sockaddr_in sock_serv;
	/*
	struct sockaddr_in {
    short sin_family;           // Famille d'adresses (AF_INET pour IPv4)
    unsigned short sin_port;    // Numéro de port en ordre octet réseau (big-endian)
    struct in_addr sin_addr;    // Adresse IP en format binaire
    char sin_zero[8];           // Remplissage pour alignement}; */

	//creation de la socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET -> on utilise IPv4, SOCK_STREAM -> socket de type flux (TCP), 0 pour mettre le protocole par defaut (IPv4)
	if (sock_fd == -1) {
		throw std::runtime_error("Error while generating a socket");}
	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0) { //fcntl fonction modifiant les attribut socket, F_SETFL pour set un mode, O_NONBLOCK pour definir le mode a set (non bloquant)
		throw std::runtime_error("Error while setting spcket to non-blocking mode")

	//initialisation de la structure sockaddr_in pour definir les parametre de l'adresse du Serveur
	sock_serv.sin_family = AF_INET; //sock utilise IPv4
	sock_serv.sin_addr = INADDR_ANY; //le serveur ecoutera sur toutes les interfaces reseauc disponibles
	sock_serv.sin_port = htons
}
