#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"
#include "voiture.h"

int main() {
    char login[30], motdepasse[30];
    int result, choix, id;
    char nom[30], prenom[30], mdp[30], tache[30];
    char date[20]; // ✅ Déclaration ajoutée pour le menu admin (case 4)

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
            // ===== MENU EMPLOYE : Gestion des voitures + présence =====
            afficherCadre("Connexion réussie en tant qu'EMPLOYE !", GREEN);

            do {
                printf(CYAN "\n=== Menu Gestion des Voitures ===\n" RESET);
                printf(YELLOW "1. PROUVER LA PRESENCE\n" RESET);
                printf(YELLOW "2. Afficher toutes les voitures\n" RESET);
                printf(YELLOW "3. Supprimer une voiture\n" RESET);
                printf(YELLOW "4. Modifier une voiture\n" RESET);
                printf(YELLOW "5. Ajouter une voiture\n" RESET);
                printf(YELLOW "0. Quitter\n" RESET);
                printf("Votre choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 1:
                        printf("Entrer votre ID employé : ");
                        scanf("%d", &id);
                        prouverPresence(id);
                        break; // ✅ Ajout du break pour éviter le “fall-through”

                    case 2:
                        printf(GREEN "\n--- Liste des voitures ---\n" RESET);
                        afficherToutesVoitures();
                        break;

                    case 3:
                        printf("Entrez l'ID de la voiture à supprimer : ");
                        scanf("%d", &id);
                        printf(RED "\n--- Suppression ---\n" RESET);
                        supprimerVoiture(id);
                        break;

                    case 4:
                        printf("Entrez l'ID de la voiture à modifier : ");
                        scanf("%d", &id);
                        printf(BLUE "\n--- Modification ---\n" RESET);
                        modifierVoiture(id);
                        break;

                    case 5:
                        ajouterVoiture();
                    
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
                "4. Voir présences par date",
                "5. QUITTER"
            };

            do {
                afficherCadreMulti(menu, 5, CYAN); // ✅ Passer 5 lignes (et non 4)
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
                        if (ajouterEmploye(id, nom, prenom, mdp, tache)) {
                            printf(GREEN "✔ Employé ajouté et confirmé.\n" RESET);
                        } else {
                            printf(RED "✖ Échec de l’ajout.\n" RESET);
                        }
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
                        printf("Entrer la date (AAAA-MM-JJ) : ");
                        scanf("%s", date); // ✅ Utilisation de la date déclarée
                        voirPresenceParDate(date);
                        break;

                    case 5:
                        afficherCadre("Retour au menu principal", CYAN);
                        break;

                    default:
                        afficherCadre("CHOIX INVALIDE", RED);
                        break;
                }
            } while (choix != 5); // ✅ Correction: sortir sur 5 (QUITTER)

        } else {
            afficherCadre("ID ou mot de passe incorrect.", RED);
        }

    } while (!result);

    return 0;
}