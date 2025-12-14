#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"
#include "voiture.h"

int main() {
    char login[30], motdepasse[30];
    int result, choix, id;
    char nom[30], prenom[30], mdp[30], tache[30];

    do {
        // Connexion
        afficherCadre("DONNER VOTRE IDENTIFIANT!", CYAN);
        scanf("%s", login);

        afficherCadre("DONNER VOTRE MOT DE PASSE", CYAN);
        scanf("%s", motdepasse);

        result = oumayma(login, motdepasse);

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if (result == 1) {
            // ===== MENU EMPLOYE : Gestion des voitures =====
            afficherCadre("Connexion réussie en tant qu'EMPLOYE !", GREEN);

            do {
                printf(CYAN "\n=== Menu Gestion des Voitures ===\n" RESET);
                printf(YELLOW "1. Afficher toutes les voitures\n" RESET);
                printf(YELLOW "2. Supprimer une voiture\n" RESET);
                printf(YELLOW "3. Modifier une voiture\n" RESET);
                printf(YELLOW "0. Quitter\n" RESET);
                printf("Votre choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 1:
                        printf(GREEN "\n--- Liste des voitures ---\n" RESET);
                        afficherToutesVoitures();
                        break;

                    case 2:
                        printf("Entrez l'ID de la voiture à supprimer : ");
                        scanf("%d", &id);
                        printf(RED "\n--- Suppression ---\n" RESET);
                        supprimerVoiture(id);
                        break;

                    case 3:
                        printf("Entrez l'ID de la voiture à modifier : ");
                        scanf("%d", &id);
                        printf(BLUE "\n--- Modification ---\n" RESET);
                        modifierVoiture(id);
                        break;

                    case 0:
                        printf(CYAN "\nAu revoir 👋\n" RESET);
                        break;

                    default:
                        printf(RED "Choix invalide, réessayez.\n" RESET);
                }

            } while (choix != 0);

        } else if (result == 2) {
            // ===== MENU ADMIN =====
            afficherCadre("Connexion réussie en tant qu'ADMIN !", YELLOW);

            const char* menu[] = {
                "1. AJOUTER UN EMPLOYE",
                "2. SUPPRIMER UN EMPLOYE",
                "3. CHANGER LA TÂCHE D'UN EMPLOYE",
                "4. QUITTER"
            };

            do {
                afficherCadreMulti(menu, 4, CYAN);
                printf("Votre choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 1:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif
                        afficherCadre("AJOUT D'UN EMPLOYE", GREEN);
                        printf("ID : "); scanf("%d", &id);
                        printf("Nom : "); scanf("%s", nom);
                        printf("Prénom : "); scanf("%s", prenom);
                        printf("Mot de passe : "); scanf("%s", mdp);
                        printf("Tâche : "); scanf("%s", tache);
                        ajouterEmploye(id, nom, prenom, mdp, tache);
                        break;

                    case 2:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif
                        afficherCadre("SUPPRESSION D'UN EMPLOYE", RED);
                        printf("Entrer l'ID de l'employé à supprimer : ");
                        scanf("%d", &id);
                        supprimerEmploye(id);
                        break;

                    case 3:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif
                        afficherCadre("MODIFICATION DE LA TÂCHE", YELLOW);
                        printf("Entrer l'ID de l'employé à modifier : ");
                        scanf("%d", &id);
                        printf("Nouvelle tâche : ");
                        scanf("%s", tache);
                        changerTacheEmploye(id, tache);
                        break;

                    case 4:
                        afficherCadre("Retour au menu principal", CYAN);
                        break;

                    default:
                        afficherCadre("CHOIX INVALIDE", RED);
                        break;
                }
            } while (choix != 4);

        } else {
            afficherCadre("ID ou mot de passe incorrect.", RED);
        }

    } while (!result);

    return 0;
}