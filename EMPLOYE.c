#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"

// Verification login/mot de passe
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

// Affichage d'un cadre simple
void afficherCadre(const char* message, const char* couleur) {
    int lignes = 4, colonnes = 100, i, j;
    for (i = 0; i < lignes; i++) {
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

// Affichage d�un cadre multi-lignes
void afficherCadreMulti(const char* lignes[], int nbLignes, const char* couleur) {
    int largeur = 100, i, j;
    for (j = 0; j < largeur; j++) printf("%s*%s", couleur, RESET);
    printf("\n");

    for (i = 0; i < nbLignes; i++) {
        int espaces = (largeur - 2 - strlen(lignes[i])) / 2;
        printf("%s*%s", couleur, RESET);
        for (j = 0; j < espaces; j++) printf(" ");
        printf("%s%s%s", couleur, lignes[i], RESET);
        for (j = 0; j < largeur - 2 - espaces - strlen(lignes[i]); j++) printf(" ");
        printf("%s*%s\n", couleur, RESET);
    }

    for (j = 0; j < largeur; j++) printf("%s*%s", couleur, RESET);
    printf("\n");
}

// Affichage fiche employ�
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
    sprintf(buffer[2], "Pr�nom    : %s", prenom);
    sprintf(buffer[3], "Mot de passe : %s", mdp);
    sprintf(buffer[4], "T�che     : %s", tache);
    for (i = 0; i < 5; i++) lignes[i] = buffer[i];
    afficherCadreMulti(lignes, 5, BLUE);
}

// Ajouter un employ�
#include <stdbool.h> // pour utiliser bool

int ajouterEmploye(int id, const char* nom, const char* prenom, const char* mdp, const char* tache) {
    FILE *fE = fopen("EMPLOYE.txt", "a");
    if (!fE) {
        afficherCadre("Erreur d ouverture du fichier", RED);
        return false; // échec
    }

    // Écriture dans le fichier
    if (fprintf(fE, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache) < 0) {
        fclose(fE);
        afficherCadre("Erreur lors de l ecriture", RED);
        return false; // échec
    }

    fclose(fE);

    // Confirmation visuelle
    afficherCadre("Employe ajoute avec succes !", GREEN);
    afficherFicheEmploye(id, nom, prenom, mdp, tache);

    return true; // succès
}

// Supprimer un employ�
void supprimerEmploye(int idASupprimer) {
    FILE *fE = fopen("EMPLOYE.txt", "r");
    FILE *temp = fopen("TEMP.txt", "w");
    if (!fE || !temp) {
        afficherCadre("Erreur d ouverture du fichier", RED);
        exit(1);
    }

    int id; char nom[30], prenom[30], mdp[30], tache[30];
    int trouve = 0;

    while (fscanf(fE, "%d %s %s %s %s", &id, nom, prenom, mdp, tache) == 5) {
        if (id != idASupprimer) {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache);
        } else {
            trouve = 1;
            afficherCadre("Employe supprimee avec succes !", RED);
            afficherFicheEmploye(id, nom, prenom, mdp, tache);
        }
    }

    fclose(fE);
    fclose(temp);
    remove("EMPLOYE.txt");
    rename("TEMP.txt", "EMPLOYE.txt");

    if (!trouve) afficherCadre("Aucun employee trouve avec cet ID.", YELLOW);
}

// Modifier la t�che d�un employ�
void changerTacheEmploye(int idAModifier, const char* nouvelleTache) {
    FILE *fE = fopen("EMPLOYE.txt", "r");
    FILE *temp = fopen("TEMP.txt", "w");
    if (!fE || !temp) {
        afficherCadre("Erreur d ouverture du fichier", RED);
        exit(1);
    }

    int id; char nom[30], prenom[30], mdp[30], tache[30];
    int trouve = 0;

    while (fscanf(fE, "%d %s %s %s %s", &id, nom, prenom, mdp, tache) == 5) {
        if (id == idAModifier) {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, nouvelleTache);
            trouve = 1;
            afficherCadre("Tache modifie avec succees !", CYAN);
            afficherFicheEmploye(id, nom, prenom, mdp, nouvelleTache);
        } else {
            fprintf(temp, "%d %s %s %s %s\n", id, nom, prenom, mdp, tache);
        }
    }

    fclose(fE);
    fclose(temp);
    remove("EMPLOYE.txt");
    rename("TEMP.txt", "EMPLOYE.txt");

    if (!trouve) afficherCadre("Aucun employ� trouv� avec cet ID.", YELLOW);
}
#include <time.h>



void prouverPresence(int idEmploye) {
    FILE *f = fopen("presence.txt", "a");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier presence.txt\n");
        return;
    }

    // Récupérer la date actuelle
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Format AAAA-MM-JJ
    fprintf(stdout, RED "%04d-%02d-%02d Employe %d present\n" RESET,
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, idEmploye);

    fclose(f);
    printf(RED"Prsence enregistre pour l employe %d a la date du jour.\n",RESET, idEmploye);
}


#include <string.h>

void voirPresenceParDate(const char* dateRecherche) {
    FILE *f = fopen("presence.txt", "r"); // ouvrir en lecture
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier presence.txt\n");
        return;
    }

    char ligne[256];
    int trouve = 0;

    printf(YELLOW"Presences pour la date %s :\n",RESET, dateRecherche);

    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), f)) {
        // Vérifie si la ligne contient la date recherchée
        if (strstr(ligne, dateRecherche) != NULL) {
            printf("%s", ligne); // afficher la ligne trouvée
            trouve = 1;
        }
    }

    if (!trouve) {
        printf(RED"Aucune presence trouvee pour cette date.\n"RESET);
    }

    fclose(f);
}
