#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char email[50];
    char motDePasse[30];
    char telephone[20];
    char cin[15];
} Client;

void inscriptionClient();
int connexionClient();
void voirProfilClient(int idClient);
void modifierProfilClient(int idClient);

#endif

