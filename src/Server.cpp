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

void	Server::generate_socket()
{
	struct sockaddr_in sock_serv;
	/*
	struct sockaddr_in {
    short sin_family;           // Famille d'adresses (AF_INET pour IPv4)
    unsigned short sin_port;    // Numéro de port en ordre octet réseau (big-endian)
    struct in_addr sin_addr;    // Adresse IP en format binaire
    char sin_zero[8];           // Remplissage pour alignement mémoire}; */

	//creation de la socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET -> on utilise IPv4, SOCK_STREAM -> socket de type flux (TCP), 0 pour mettre le protocole par defaut (IPv4)
	if (sock_fd == -1) {
		throw std::runtime_error("Error while generating a socket");}
	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0) { //fcntl fonction modifiant les attribut socket, F_SETFL pour set un mode, O_NONBLOCK pour definir le mode a set (non bloquant)
		throw std::runtime_error("Error while setting spcket to non-blocking mode");}

	//initialisation de la structure sockaddr_in pour definir les parametre de l'adresse du Serveur
	sock_serv.sin_family = AF_INET; //sock utilise IPv4
	sock_serv.sin_addr = INADDR_ANY; //le serveur ecoutera sur toutes les interfaces reseauc disponibles
	sock_serv.sin_port = htons(server._port); //on convertit le port en ordre octet réseau

	//liage de la socket à l'adresse et au port
	if (bind(sock_serv, (struct sockaddr*) &sock_fd, sizeof(sock_fd)) < 0){
		throw std::runtime_error("Error While binding socket");} //bind() lie la socket a l'adresse et au port spécifié, msg si Erreur

	if (listen(fd, address.sin_port) == < 0) {
		throw std::runtime_error("Error while putting the socket in listening mode");}

	std::cout << "Server socket has been generated\n";
}
