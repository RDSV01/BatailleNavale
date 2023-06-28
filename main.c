#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "definitions.h"

//Message de bienvenu
void bienvenu() {
    printf("Bienvenu sur le jeu de la Bataile Navale\n");
}

//Plateau bataille navale
Plateau initialisationJeu() {
    Plateau p;
    int i, j;

    // Initialiser les valeurs des bateaux
    p.contreTorpilleur = B_CONTRE_TORPILLEUR;
    p.croiseur = B_CROISEUR;
    p.porteAvion = B_PORTE_AVION;
    p.sousMarin = B_SOUS_MARIN;
    p.torpilleur = B_TORPILLEUR;
    p.points = 0;

    // Initialiser les grilles
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            p.grille[i][j] = C_RATE;  // Remplir la grille du joueur avec des cases "raté"
            p.grilleEnnemie[i][j] = C_RATE;  // Remplir la grille ennemie avec des cases "raté"
        }
    }
    return p;  // Retourner le plateau initialisé
}


//Affiche la grille de jeu
void afficherGrille(int g[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;

    // Afficher l'en-tête des colonnes
    puts("\n   1   2   3   4   5   6   7   8   9   10");
    puts(line);  // Afficher la ligne de séparation

    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", i + 'A');  // Afficher la lettre de la rangée

        for (j = 0; j < BOARD_SIZE; j++) {
            if ((int) g[i][j] == C_RATE) {  // Case d'eau non touchée
                printf("%s", EAU);
            } else if (g[i][j] == C_RATE_T) {  // Case d'eau touchée
                printf("%s", EAU_TOUCHE);
            } else if (g[i][j] == C_PORTE_AVION || g[i][j] == C_CROISEUR || g[i][j] == C_CONTRE_TORPILLEUR || g[i][j] == C_SOUS_MARIN || g[i][j] == C_TORPILLEUR) {
                // Case contenant un bateau non touché
                printf("%s", BAT);
            } else {
                // Case contenant un bateau touché
                printf("%s", BAT_TOUCHE);
            }
        }

        printf("\n");
        puts(line);  // Afficher la ligne de séparation
    }
}

Coordonnees Coordo(char string[], int hasDirection) {
    Coordonnees c;  // Structure pour stocker les coordonnées
    char strX[2 + 1];  // Chaîne pour stocker la composante X
    int i;

    if (hasDirection > 0) {
        hasDirection = 1;
        c.d = string[strlen(string) - 1];  // Stocker la direction
    } else {
        hasDirection = 0;
    }

    // Convertir la composante Y en entier
    c.y = string[0] - 'a';

    // Extraire la composante X
    for (i = 0; i < strlen(string) - (1 + hasDirection); i++) {
        strX[i] = string[i + 1];
    }

    strX[i] = '\0';  // Terminer la chaîne avec un caractère nul

    // Convertir la composante X en entier
    c.x = strtol(strX, NULL, 10) - 1;

    return c;  // Retourner les coordonnées
}


int calcAlive(Plateau p) {
    return p.contreTorpilleur + p.croiseur + p.porteAvion + p.sousMarin + p.torpilleur;
}
Plateau placerBateau(Plateau p, char nom[], int size, int val) {
    int done, error, i;
    Coordonnees c;
    char pos[4 + 1],  // Coordonnées
    orientation[10 + 1];

    afficherGrille(p.grille);

    //Pour placer un bateau il faut choisir une coordonnée verticale, puis horizontal et pour finir, l'orientation,
    //Exemple : a1h
    printf(">>> Veuillez placer le %s (%i cases)\n\n", nom, size);
    do {
        // Réinitialiser les variables
        error = 0;
        done = 0;
        strcpy(orientation, "horizontal");

        // Demander la coordonnée verticale
        printf(">>> Coordonnée verticale (a-j) : ");
        scanf("%s", pos);
        c.y = pos[0] - 'a';

        if (c.y < 0 || c.y >= BOARD_SIZE) {
            puts(" >>> Coordonnée verticale incorrecte.");
            error = 1;
        }

        // Demander la coordonnée horizontale
        if (error == 0) {
            printf(">>> Coordonnée horizontale (1-10) : ");
            scanf("%s", pos);
            c.x = atoi(pos) - 1;

            if (c.x < 0 || c.x >= BOARD_SIZE) {
                puts(" >>> Coordonnée horizontale incorrecte.");
                error = 1;
            }
        }

        // Demander l'orientation
        if (error == 0) {
            printf(">>> Orientation (h/v) : ");
            scanf(" %c", &pos[0]);
            if (pos[0] == 'v' || pos[0] == 'V') {
                strcpy(orientation, "vertical");
            } else if (pos[0] != 'h' && pos[0] != 'H') {
                puts(" >>> Orientation incorrecte. Veuillez choisir 'h' pour horizontal ou 'v' pour vertical.");
                error = 1;
            }
        }

        // Vérification du placement des bateaux
        if (error == 0) {
            if (strcmp(orientation, "vertical") == 0) {
                // Sortie de la carte
                if (c.y + size > BOARD_SIZE) {
                    printf(" >>> Impossible de placer le bateau ici. Il sort du cadre. (y=%i)\n", c.y);
                    error = 1;
                } else {
                    // Chevauchements
                    for (i = c.y; i < c.y + size; i++) {
                        if (p.grille[i][c.x] != C_RATE) {
                            puts(" >>> Un bateau est déjà ici.");
                            error = 1;
                            break;
                        }
                    }
                }
            } else {  // Orientation horizontale
                if (c.x + size > BOARD_SIZE) {
                    printf(" >>> Impossible de placer le bateau ici. Il sort du cadre. (x=%i)\n", c.x);
                    error = 1;
                } else {
                    // Chevauchements
                    for (i = c.x; i < c.x + size; i++) {
                        if (p.grille[c.y][i] != C_RATE) {
                            puts(" >>> Un bateau est déjà ici.");
                            error = 1;
                            break;
                        }
                    }
                }
            }
        }

        if (error == 0) {
            done = 1;
        }
    } while (done == 0);


    // Placer le bateau sur la grille
    if (strcmp(orientation, "vertical") == 0) {
        for (i = c.y; i < c.y + size; i++) {
            p.grille[i][c.x] = val;
        }
    } else {
        for (i = c.x; i < c.x + size; i++) {
            p.grille[c.y][i] = val;
        }
    }
    return p;
}





//Fermeture des sockets
void fermerApp(InfosServer is, int code, char message[50]) {
    // Fermer les sockets
    close(is.socket_desc);
    close(is.client_sock);

    // Message
    printf("\n%s\n", message);

    //Fermeture
    exit(code);
}

//Initialisation du serveur
InfosServer initialisationServeur(int port) {
    InfosServer is;

    // Creation du socket
    is.socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (is.socket_desc == -1) {
        fermerApp(is, 1, ">>> Creation socket impossible.");
    }

    // Création de l'écoute
    is.server.sin_family = AF_INET;
    is.server.sin_addr.s_addr = INADDR_ANY;
    is.server.sin_port = htons(port); // définition du port d'écoute du socket

    // Mise en place de l'écoute
    if (bind(is.socket_desc, (struct sockaddr *) &is.server, sizeof (is.server)) < 0) {
        fermerApp(is, 1, ">>> Erreur écoute");
    }

    listen(is.socket_desc, 3);

    printf(">>> Serveur en place (port %i). Attente du client...\n", port);
    is.c = sizeof (struct sockaddr_in);

    return is;
}

//Reception client, 0 pour le succes et 1 pour erreur
int receptionMessageClient(InfosServer is, Plateau *p) {
    int content, status = 0, pv = -1;
    Coordonnees coup;

    // Acceptation de la connexion client
    is.client_sock = accept(is.socket_desc, (struct sockaddr *)&is.client, (socklen_t *)&is.c);
    if (is.client_sock < 0) {
        perror(">>> Connexion refusée");
        return 1;
    }

    printf(">>> En attente du tir de l'adversaire.\n");

    // Définition de la taille maximale des messages
#define MAX_MESSAGE_SIZE 100
    char server_response[MAX_MESSAGE_SIZE + 1]; // +1 pour le caractère nul de fin de chaîne

    while ((is.read_size = recv(is.client_sock, is.client_message, 100, 0)) > 0) {
        // À l'intérieur de la boucle while
        size_t message_length = strlen(is.client_message);
        size_t copy_length = message_length < MAX_MESSAGE_SIZE ? message_length : MAX_MESSAGE_SIZE;
        strncpy(server_response, is.client_message, copy_length);
        server_response[copy_length] = '\0'; // S'assurer que la chaîne est terminée correctement

        printf(  " > %s\n\n"  , is.client_message);

        coup = Coordo(is.client_message, 0);
        content = (*p).grille[coup.y][coup.x];

        if (content == C_RATE || content == C_RATE_T) {
            sprintf(server_response, "%d", S_RATE);
            (*p).grille[coup.y][coup.x] = C_RATE_T;
            status = S_RATE;
        } else {
            status = S_TOUCHE;
            sprintf(server_response, "%d", S_TOUCHE);
            switch (content) {
                case C_CONTRE_TORPILLEUR:
                    (*p).grille[coup.y][coup.x] = C_CONTRE_TORPILLEUR_T;
                    (*p).contreTorpilleur--;
                    pv = (*p).contreTorpilleur;
                    break;
                case C_CROISEUR:
                    (*p).grille[coup.y][coup.x] = C_CROISEUR_T;
                    (*p).croiseur--;
                    pv = (*p).croiseur;
                    break;
                case C_PORTE_AVION:
                    (*p).grille[coup.y][coup.x] = C_PORTE_AVION_T;
                    (*p).porteAvion--;
                    pv = (*p).porteAvion;
                    break;
                case C_SOUS_MARIN:
                    (*p).grille[coup.y][coup.x] = C_SOUS_MARIN_T;
                    (*p).sousMarin--;
                    pv = (*p).sousMarin;
                    break;
                case C_TORPILLEUR:
                    (*p).grille[coup.y][coup.x] = C_TORPILLEUR_T;
                    (*p).torpilleur--;
                    pv = (*p).torpilleur;
                    break;
                default:
                    sprintf(server_response, "%d", S_TOUCHE_BIS);
                    status = S_RATE;
            }
        }

        if (pv == 0) {
            status = S_TOUCHE;
            sprintf(server_response, "%d", S_COULE);
        }

        printf(">>> Résultat :\n");
        afficherGrille((*p).grille);
        printf(  "\n>>> Il vous reste %i points.\n"  , calcAlive(*p));
        if (calcAlive(*p) == 0) {
            printf(  ">>> Plus de bateaux. Perdu.\n"  );
            sprintf(server_response, "%d", S_PERDU);
        }

        write(is.client_sock, server_response, sizeof(char) * strlen(server_response));

        if (calcAlive(*p) == 0) {
            return S_PERDU;
        }

        break;
    }

    if (is.read_size == 0) {
        puts(">>> Déconnexion client");
        fflush(stdout);
    } else if (is.read_size == -1) {
        perror(">>> Erreur réception");
    }

    return status;
}

//Connexion Serveur
int connexionServeur(int server_port, int wait) {
    struct sockaddr_in server;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf(">>> Erreur création socket");
    }

    // Connexion au serveur
    server.sin_addr.s_addr = inet_addr(CLIENT_ADDR); //définition de l'adresse IP du serveur
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port); //définition du port d'écoute du serveur

    if (wait == 0) {
        if (connect(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
            puts(">>> Serveur inacessible");
            return -1;
        }
    } else {
        while (connect(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
            // Nothing. Infinite loop. Great.
        }
    }
    return sock;
}

//Permet d'envoyer un message au serveur et d'afficher la réponse
int strike(int other_port, Plateau *p) {
    char message[3 + 1], server_reply[100];
    int sock, srvR;
    Coordonnees c;

    // Creation du socket
    sock = connexionServeur(other_port, 0);

    // Interface
    printf("\n >>> Grille de l'adversaire :\n");
    afficherGrille((*p).grilleEnnemie);
    printf("\n >>> A votre tour !\n");
    printf(">>> Entrez les coordonnées pour tirer (ex: a1) : ");
    scanf("%3s", message); // Limiter la lecture à 3 caractères

    c = Coordo(message, 0);

    // Envoi de la chaine saisie par l'utilisateur
    if (send(sock, message, strlen(message), 0) < 0) {
        puts("erreur envoi");
        return -1;
    }

    // Réception du message de retour du serveur
    if (recv(sock, server_reply, sizeof(server_reply) - 1, 0) < 0) {
        puts(">>> Erreur reception reponse serveur");
        return -1;
    } else {
        server_reply[3] = '\0'; // Ajouter le caractère de fin de chaîne
        srvR = strtol(server_reply, NULL, 10);
        printf(">>> Résultat :\n");

        switch (srvR) {
            case S_RATE:
                printf(  " >>> Raté.\n"  );
                (*p).grilleEnnemie[c.y][c.x] = C_RATE_T;
                break;
            case S_TOUCHE:
                printf(  " >>> Touché.\n"  );
                (*p).grilleEnnemie[c.y][c.x] = C_BAT_T;
                break;
            case S_COULE:
                printf(  " >>> Coulé !\n"  );
                (*p).grilleEnnemie[c.y][c.x] = C_BAT_T;
                break;
            case S_TOUCHE_BIS:
                printf(  ">>> Vous avez déjà touché ici.\n"  );
                break;
            case S_PERDU:
                printf(">>> Vous avez gagné ! Bravo !\n");
                break;
            default:
                printf(  ">>> Réponse incorrecte. (%i)\n"  , srvR);
                return -1; // Retourner une erreur si la réponse est incompréhensible
        }

        return srvR;
    }
}

//Test d'un handshake
void handshake(int port) {
    int sock, msgSize = (sizeof(char) * 3);
    char message[2 + 1], server_reply[2 + 1];
    int srvV;

    // Conversion du code de poignée de main en chaîne de caractères
    sprintf(message, "%d", S_HANDSHAKE);

    printf(">>> En attente du deuxième joueur.\n");

    // Établissement de la connexion avec le serveur
    sock = connexionServeur(port, 1);

    // Envoi du code de poignée de main
    if (send(sock, message, msgSize, 0) < 0) {
        puts(">>> Erreur de poignée de main");
    }

    // Réception du message de retour du serveur
    if (recv(sock, server_reply, msgSize, 0) < 0) {
        puts(">>> Erreur de réception de la réponse du serveur");
    } else {
        srvV = strtol(server_reply, NULL, 10);
        if (srvV != S_HANDSHAKE) {
            printf(">>> Réponse du serveur (%i)\n", srvV);
        } else {
            printf(">>> Connecté au deuxième joueur\n");
        }
    }

    // Fermeture de la connexion avec le serveur
    close(sock);
}


//Permet d'attendre la connexion du client
int attente_handshake(InfosServer is) {
    int content;
    char resp[2 + 1];
    sprintf(resp, "%d", S_HANDSHAKE);

    printf(">>> En attente du deuxième joueur.\n");
    // Acceptation de la connexion d'un client
    is.client_sock = accept(is.socket_desc, (struct sockaddr *) &is.client, (socklen_t*) & is.c);
    if (is.client_sock < 0) {
        perror(">>> Connexion refusee");
        return 1;
    }

    while ((is.read_size = recv(is.client_sock, is.client_message, 100, 0)) > 0) {
        // Traitement du retours
        content = strtol(is.client_message, NULL, 10);
        if (content == S_HANDSHAKE) {
            write(is.client_sock, resp, sizeof (int));
            printf(">>> Connecté au deuxieme joueur.\n");
        }
    }
}

//Fonction main
//Lance les différentes fonctions pour le jeu
int main() {
    int t, self_port, other_port, status, perdu;

    bienvenu();

    /*
     * Saisie du type d'instance.
     */
    printf(">>> Selectionner votre joueur, joueur 1 ou 2 ? [1/2] > ");
    scanf("%i", &t);

    if (t == 1) {
        self_port = SRV_PORT;
        other_port = CLT_PORT;
    } else {
        self_port = CLT_PORT;
        other_port = SRV_PORT;
    }

    //Initialisation du serveur
    InfosServer srv = initialisationServeur(self_port);

    // Génération de la grille
    Plateau plateau = initialisationJeu();

    printf(">>> Placement de vos bateaux\n");

    // Placement des bateaux
    plateau = placerBateau(plateau, "porte avions", B_PORTE_AVION, C_PORTE_AVION);
    plateau = placerBateau(plateau, "croiseur", B_CROISEUR, C_CROISEUR);
    plateau = placerBateau(plateau, "contre-torpilleur", B_CONTRE_TORPILLEUR, C_CONTRE_TORPILLEUR);
    plateau = placerBateau(plateau, "sous-marin", B_SOUS_MARIN, C_SOUS_MARIN);
    plateau = placerBateau(plateau, "torpilleur", B_TORPILLEUR, C_TORPILLEUR);

    printf(" C'est parti !\n");

    status = S_TOUCHE;
    // Décalage entre joueur 1 et 2
    if (t == 1) {
        // Mode "écoute"
        attente_handshake(srv);
        afficherGrille(plateau.grille);
        while (status != S_PERDU) {
            // Tant que l'autre touche
            do {
                status = receptionMessageClient(srv, &plateau);
            } while (status == S_TOUCHE || status == S_COULE);
            if (status != S_PERDU) {
                do {
                    status = strike(other_port, &plateau);
                } while (status == S_TOUCHE || status == S_COULE);
            }
        }
    } else {
        // Mode "envoi"
        handshake(other_port);
        while (status != S_PERDU) {
            do {
                status = strike(other_port, &plateau);
            } while (status == S_TOUCHE || status == S_COULE);

            if (status != S_PERDU) {
                do {
                    status = receptionMessageClient(srv, &plateau);
                } while (status == S_TOUCHE || status == S_COULE);
            }
        }
    }

    fermerApp(srv, 0, "A bientot");

    return (EXIT_SUCCESS);
}