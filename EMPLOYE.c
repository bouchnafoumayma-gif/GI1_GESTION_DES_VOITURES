#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"

// ? Vérification login/mot de passe
void afficherCadre(const char* message, const char* couleur);
int oumayma(const char* login_saisie, const char* motDePasse) {
    int id;
    char nom[30], prenom[30], mdp[30], tache[30];
    FILE *fE = fopen("EMPLOYE.txt", "r");
    if (!fE) {
        afficherCadre("Erreur d'ouverture du fichier", RED);
        exit(1);
    }

    while (fscanf(fE, "%d %s %s %s %s", &id, nom, prenom, mdp, tache) == 5) {
        if (atoi(login_saisie) == id && strcmp(mdp, motDePasse) == 0) {
            fclose(fE);
            return (strcmp(tache, "ADMIN") == 0) ? 2 : 1;
        }
    }

    fclose(fE);
    return 0;
}

// ? Affichage d’un cadre simple
void afficherCadre(const char* message, const char* couleur) {
    int lignes = 4, colonnes = 100,i,j;
    for ( i = 0; i < lignes; i++) {
        for (j = 0; j < colonnes; j++) {
            if (i == 0 || i == lignes - 1 || j == 0 || j == colonnes - 1) {
                printf("%s*%s", couleur, RESET);
            } else if (i == lignes / 2 && j == (colonnes - strlen(message)) / 2) {
                printf("%s%s%s", couleur, message, RESET);
                j += strlen(message) - 1;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// ? Affichage d’un cadre multi-lignes
void afficherCadreMulti(const char* lignes[], int nbLignes, const char* couleur) {
    int largeur = 100,i,j;
    for (j = 0; j < largeur; j++) printf("%s*%s", couleur, RESET);
    printf("\n");

    for (i = 0; i < nbLignes; i++) {
        int espaces = (largeur - 2 - strlen(lignes[i])) / 2;
        printf("%s*%s", couleur, RESET);
        for (j = 0; j < espaces; j++) printf(" ");
        printf("%s%s%s", couleur, lignes[i], RESET);
        for ( j = 0; j < largeur - 2 - espaces - strlen(lignes[i]); j++) printf(" ");
        printf("%s*%s\n", couleur, RESET);
    }

    for ( j = 0; j < largeur; j++) printf("%s*%s", couleur, RESET);
    printf("\n");
}

// ? Affichage fiche employé
void afficherFicheEmploye(int id, const char* nom, const char* prenom, const char* mdp, const char* tache) {
	#ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    const char* lignes[5];
    char buffer[5][100];
    int i;
    sprintf(buffer[0], "ID        : %d", id);
    sprintf(buffer[1], "Nom       : %s", nom);
    sprintf(buffer[2], "Prénom    : %s", prenom);
    sprintf(buffer[3], "Mot de passe : %s", mdp);
    sprintf(buffer[4], "Tâche     : %s", tache);
    for ( i = 0; i < 5; i++) lignes[i] = buffer[i];
    afficherCadreMulti(lignes, 5, BLUE);
}

// ? Ajouter un employé
void ajouterEmploye(int id, const char* nom, const char* prenom, const char* mdp, const char* tache) {
	#ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    FILE *fE = fopen("EMPLOYE.txt", "a");
    if (!fE) {
        afficherCadre("Erreur d'ouverture du fichier", RED);
        exit(1);
    }
    fprintf(fE, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache);
    fclose(fE);
    afficherCadre("Employé ajouté avec succès !", GREEN);
    afficherFicheEmploye(id, nom, prenom, mdp, tache);
}

// ? Supprimer un employé
void supprimerEmploye(int idASupprimer) {
    FILE *fE = fopen("EMPLOYE.txt", "r");
    FILE *temp = fopen("TEMP.txt", "w");
    if (!fE || !temp) {
        afficherCadre("Erreur d'ouverture du fichier", RED);
        exit(1);
    }

    int id; char nom[30], prenom[30], mdp[30], tache[30];
    int trouve = 0;

    while (fscanf(fE, "%d %s %s %s %s", &id, nom, prenom, mdp, tache) == 5) {
        if (id != idASupprimer) {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache);
        } else {
            trouve = 1;
            afficherCadre("Employé supprimé avec succès !", RED);
            afficherFicheEmploye(id, nom, prenom, mdp, tache);
        }
    }

    fclose(fE); fclose(temp);
    remove("EMPLOYE.txt"); rename("TEMP.txt", "EMPLOYE.txt");

    if (!trouve) afficherCadre("Aucun employé trouvé avec cet ID.", YELLOW);
}

// ? Modifier la tâche d’un employé
void changerTacheEmploye(int idAModifier, const char* nouvelleTache) {
    FILE *fE = fopen("EMPLOYE.txt", "r");
    FILE *temp = fopen("TEMP.txt", "w");
    if (!fE || !temp) {
        afficherCadre("Erreur d'ouverture du fichier", RED);
        exit(1);
    }

    int id; char nom[30], prenom[30], mdp[30], tache[30];
    int trouve = 0;

    while (fscanf(fE, "%d %s %s %s %s", &id, nom, prenom, mdp, tache) == 5) {
        if (id == idAModifier) {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, nouvelleTache);
            trouve = 1;
            afficherCadre("Tâche modifiée avec succès !", CYAN);
            afficherFicheEmploye(id, nom, prenom, mdp, nouvelleTache);
        } else {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache);
        }
    }

    fclose(fE); fclose(temp);
    remove("EMPLOYE.txt"); rename("TEMP.txt", "EMPLOYE.txt");

    if (!trouve) afficherCadre("Aucun employé trouvé avec cet ID.", YELLOW);
}

