#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "menu.c"
#include "gameengine.c"

const int port = 8000;

int startserver()
{
    // instanciation des variables
    struct sockaddr_in my_adr;
    struct sockaddr_in serveur_adr;
    socklen_t sz_sock_serveur;
    int sock, sock_distante, val_read;
    int addrlen = sizeof(my_adr);
    char buffer[1024] = {0};
    char message[1024];

    /* Place les bateaux */
    BOAT boats[number_boats];
    int field[SIZE][SIZE];

    buildarrays(field, EMPTY);

    placeboats(field, boats);

    /* ouverture d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* cration d'une adresse locale */
    memset(&my_adr, '\0', sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_port = htons(port);
    my_adr.sin_addr.s_addr = INADDR_ANY;

    /* association de l'adresse locale a la socket */
    bind(sock, (struct sockaddr *)&my_adr, sizeof(struct sockaddr_in));

    /* attente des clients */
    listen(sock, 1);

    printf("Attend la connection d'un autre joueur");
    
    // Attendre la connexion entrante
    if ((sock_distante = accept(sock, (struct sockaddr *)&serveur_adr, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    

    // Boucle principale du chat
    while (1) {
        // Demander un message à envoyer
        

        // Envoyer le message au client distant
        send(sock_distante, message, strlen(message), 0);

        // Effacer le message pour la prochaine itération
        memset(message, 0, sizeof(message));

        // Lire le message entrant
        val_read = read(sock_distante, buffer, 1024);
        printf("Client : %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}