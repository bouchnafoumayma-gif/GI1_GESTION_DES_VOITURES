#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "interface.h"
#include "client.h"


void inscriptionClient() {
    Client c;
    FILE *f = fopen("clients.txt", "a+");
    if (!f) {
        centrerTexte(RED "Erreur : impossible d’ouvrir le fichier clients.txt" RESET);
        return;
    }

    afficherLogo();
    afficherCadreCentre("INSCRIPTION CLIENT");

    centrerTexte("Nom : "); scanf("%s", c.nom);
    centrerTexte("Prénom : "); scanf("%s", c.prenom);
    centrerTexte("Email : "); scanf("%s", c.email);
    centrerTexte("Téléphone : "); scanf("%s", c.telephone);
    centrerTexte("CIN : "); scanf("%s", c.cin);
    centrerTexte("Mot de passe : "); saisirMotDePasse(c.motDePasse);

    int id = 1; Client tmp;
    FILE *fr = fopen("clients.txt", "r");
    if (fr) {
        while (fscanf(fr, "%d %s %s %s %s %s %s\n",
                      &tmp.id, tmp.nom, tmp.prenom, tmp.email,
                      tmp.motDePasse, tmp.telephone, tmp.cin) == 7)
            id++;
        fclose(fr);
    }
    c.id = id;

    fprintf(f, "%d %s %s %s %s %s %s\n",
            c.id, c.nom, c.prenom, c.email,
            c.motDePasse, c.telephone, c.cin);
    fclose(f);

    effacerConsole();
    afficherLogo();
    afficherCadreCentre(GREEN "? Inscription réussie !" RESET);
    _getch();
}

int connexionClient() {
    FILE *f = fopen("clients.txt", "r");
    if (!f) {
        centrerTexte(YELLOW "?? Aucun client enregistré pour le moment." RESET);
        _getch();
        return -1;
    }

    char email[50], motDePasse[30];
    Client c;

    afficherLogo();
    afficherCadreCentre("CONNEXION CLIENT");
    centrerTexte("Email : "); scanf("%s", email);
    centrerTexte("Mot de passe : "); saisirMotDePasse(motDePasse);

    while (fscanf(f, "%d %s %s %s %s %s %s\n",
                  &c.id, c.nom, c.prenom, c.email,
                  c.motDePasse, c.telephone, c.cin) == 7) {
        if (strcmp(email, c.email) == 0 && strcmp(motDePasse, c.motDePasse) == 0) {
            fclose(f);
            effacerConsole();
            afficherLogo();
            afficherCadreCentre(GREEN "Connexion réussie !" RESET);
            _getch();
            return c.id;
        }
    }

    fclose(f);
    effacerConsole();
    afficherLogo();
    afficherCadreCentre(RED "? Identifiants incorrects." RESET);
    _getch();
    return -1;
}

void voirProfilClient(int idClient) {
    FILE *f = fopen("clients.txt", "r");
    if (!f) return;

    Client c;
    while (fscanf(f, "%d %s %s %s %s %s %s\n",
                  &c.id, c.nom, c.prenom, c.email,
                  c.motDePasse, c.telephone, c.cin) == 7) {
        if (c.id == idClient) {
            effacerConsole();
            afficherLogo();
            afficherCadreCentre("MON PROFIL");
            printf("\n\n");
            centrerTexte(c.nom);
            centrerTexte(c.prenom);
            centrerTexte(c.email);
            centrerTexte(c.telephone);
            centrerTexte(c.cin);
            _getch();
            break;
        }
    }
    fclose(f);
}

void modifierProfilClient(int idClient) {
    FILE *f = fopen("clients.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    if (!f || !tmp) return;

    Client c;
    while (fscanf(f, "%d %s %s %s %s %s %s\n",
                  &c.id, c.nom, c.prenom, c.email,
                  c.motDePasse, c.telephone, c.cin) == 7) {
        if (c.id == idClient) {
            effacerConsole();
            afficherLogo();
            afficherCadreCentre("MODIFICATION DU PROFIL");
            centrerTexte("Nouveau téléphone : "); scanf("%s", c.telephone);
            centrerTexte("Nouveau mot de passe : "); saisirMotDePasse(c.motDePasse);
        }
        fprintf(tmp, "%d %s %s %s %s %s %s\n",
                c.id, c.nom, c.prenom, c.email,
                c.motDePasse, c.telephone, c.cin);
    }
    fclose(f);
    fclose(tmp);
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    afficherCadreCentre(GREEN "Profil modifié avec succès." RESET);
    _getch();
}

