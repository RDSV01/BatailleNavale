//Définitions
#define CLIENT_ADDR "127.0.0.1" // Adresse client
#define SRV_PORT 8888 // Port du serveur
#define CLT_PORT 8889 //Port du client

#define BOARD_SIZE 10
#define S_PERDU -1 // Partie perdue
#define S_TOUCHE 1 // Bateau touché
#define S_RATE 2 // Bateau raté
#define S_TOUCHE_BIS 3 // Bateau touché
#define S_COULE 4 //Bateau coulé.
#define S_HANDSHAKE 10 // Code handshake
// Taille bateau
#define B_PORTE_AVION 5
#define B_CROISEUR 4
#define B_CONTRE_TORPILLEUR 3
#define B_SOUS_MARIN 3
#define B_TORPILLEUR 2
// Valeur des célules
#define C_RATE 0
#define C_RATE_T 1
#define C_BAT_T 2
#define C_PORTE_AVION 10
#define C_PORTE_AVION_T 11
#define C_CROISEUR 20
#define C_CROISEUR_T 11
#define C_CONTRE_TORPILLEUR 30
#define C_CONTRE_TORPILLEUR_T 31
#define C_SOUS_MARIN 40
#define C_SOUS_MARIN_T 41
#define C_TORPILLEUR 50
#define C_TORPILLEUR_T 51

// Définition des couleurs
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
