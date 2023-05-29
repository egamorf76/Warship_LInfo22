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

const int port = 8000;

int main(int argc, char **argv)
{
    struct sockaddr_in sock_host;
    int sock, val_read;
    char buffer[1024] = {0};
    char message[1024];

    /* ouverture d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* on cre l'adresse de la machine distante */
    memset(&sock_host, '\0', sizeof(sock_host));
    sock_host.sin_family = AF_INET;
    sock_host.sin_port = htons(port);
    inet_aton("127.0.0.1", &sock_host.sin_addr);

    /* on demande un connection sur l'adresse distante */
    connect(sock, (struct sockaddr *)&sock_host, sizeof(sock_host));

     // Boucle principale du chat
    while (1) {
        // Lire le message entrant
        val_read = read(sock, buffer, 1024);
        printf("Client : %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));

        // Demander un message à envoyer
        printf("Entrez un message : ");
        fgets(message, 1024, stdin);

        // Envoyer le message au serveur distant
        send(sock, message, strlen(message), 0);

        // Effacer le message pour la prochaine itération
        memset(message, 0, sizeof(message));
    }

    return 0;
}