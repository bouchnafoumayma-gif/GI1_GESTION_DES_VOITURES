#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"
#include "voiture.h"
#include "interface.h"
#include "reservation.h"
#include <conio.h>
#include "client.h"

int main() {
    char login[30], motdepasse[30];
    int result, choix, id;
    char nom[30], prenom[30], mdp[30], tache[30];
    char date[20];
    int A;

    /// LOGO
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Couleur du cadre et du grand logo
    printf(BLUE);
    printf("=============================================================================================\n");
    printf("||                                                                                         ||\n");
    printf("||    _      _       _        _       _                   _                                ||\n");
    printf("||   / \\    | |     | |      | |     | |                 | |                               ||\n");
    printf("||  / _ \\   | |     | |      | |     | |     __ _ _ __ __| | ___ _ __ ___ ___              ||\n");
    printf("|| / ___ \\  | |___  | |___   | |___  | |__  / _` | '__/ _` |/ _ \\ '__/ __/ _ \\             ||\n");
    printf("||/_/     \\ |_____| |_____|  |_____| |____| \\__,_|_|  \\__,|\\___/|  |\\___\\___/              ||\n");
    printf("||                                                                                         ||\n");

    // Texte blanc à l'intérieur du cadre
    printf(WHITE);
    printf("||                                 ALLOCATION_HOUSE                                        ||\n");
    printf(BLUE "||-----------------------------------------------------------------------------------------||\n" WHITE);
    printf("||       * Bienvenue dans votre application de location de voitures ! *                    ||\n");
    printf("||      Gestion complete : Employes | Clients | Reservations | Voitures                    ||\n");
    printf(BLUE "||-----------------------------------------------------------------------------------------||\n" WHITE);
    printf("||          2025 | Projet developpe en C | By Meriem & Oumayma                             ||\n");
    printf(BLUE "=============================================================================================\n" RESET);

    printf("\n");
    printf(WHITE "Appuyez sur une touche pour continuer...\n" RESET);
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    /// PAGE 1
   /* printf(BLUE"*******************************************BONJOUR!******************************\n"RESET);
    printf(BLUE"*********POUR UNE CONNEXION EN TANT QUE EMPLOYE CLIQUE SUR 1 EN TANT QUE CLIENT CLIQUE SUR 2**********\n"RESET);
    scanf("%d", &A);*/
  // PAGE 1 : Menu principal stylé avec curseur
int choixMenu = 0; // 0 = Employe, 1 = Client, 2 = Quitter
char touche;

do {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf(BLUE);
    printf("=============================================================================================\n");
    printf("||                                                                                         ||\n");
    printf("||                               *  MENU PRINCIPAL  *                                      ||\n");
    printf("||-----------------------------------------------------------------------------------------||\n");
    printf(WHITE);

    printf("||   %s EMPLOYE                                                                            ||\n", (choixMenu == 0) ? "??" : "   ");
    printf("||   %s CLIENT                                                                             ||\n", (choixMenu == 1) ? "??" : "   ");
    printf("||   %s QUITTER                                                                            ||\n", (choixMenu == 2) ? "??" : "   ");

    printf(BLUE);
    printf("||-----------------------------------------------------------------------------------------||\n");
    printf("||      Utilisez les flèches pour naviguer et Entrée pour valider votre choix.             ||\n");
    printf("=============================================================================================\n");
    printf(RESET);

    touche = _getch();
    if (touche == 72) { // flèche haut
        if (choixMenu > 0) choixMenu--;
    } else if (touche == 80) { // flèche bas
        if (choixMenu < 2) choixMenu++;
    }

} while (touche != 13); // 13 = Entrée

A = choixMenu + 1; // 1 = Employé, 2 = Client, 3 = Quitter
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
  

/*#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif*/

    switch (A) {
        case 1: {
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
                    // ===== MENU EMPLOYE =====
                    afficherCadre("Connexion reussie en tant qu EMPLOYE !", GREEN);

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
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                printf(YELLOW"Entrer votre ID employe : "RESET);
                                scanf("%d", &id);
                                prouverPresence(id);
                                break;

                            case 2:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                printf(GREEN "\n--- Liste des voitures ---\n" RESET);
                                afficherToutesVoitures();
                                break;

                            case 3:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                printf("Entrez l ID de la voiture à supprimer : ");
                                scanf("%d", &id);
                                printf(RED "\n--- Suppression ---\n" RESET);
                                supprimerVoiture(id);
                                break;

                            case 4:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                printf("Entrez l ID de la voiture à modifier : ");
                                scanf("%d", &id);
                                printf(BLUE "\n--- Modification ---\n" RESET);
                                modifierVoiture(id);
                                break;

                            case 5:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                ajouterVoiture();
                                break;

                            case 0:
                                printf(CYAN "\nAu revoir ??\n" RESET);
                                break;

                            default:
                                printf(RED "Choix invalide, reessayez.\n" RESET);
                        }
                    } while (choix != 0);

                } else if (result == 2) {
                    // ===== MENU ADMIN =====
                    afficherCadre("Connexion reussie en tant qu ADMIN !", YELLOW);

                    const char* menu[] = {
                        "1. AJOUTER UN EMPLOYE",
                        "2. SUPPRIMER UN EMPLOYE",
                        "3. CHANGER LA TACHE D'UN EMPLOYE",
                        "4. Voir presences par date",
                        "5. QUITTER"
                    };

                    do {
                        afficherCadreMulti(menu, 5, CYAN);
                        printf("Votre choix : ");
                        scanf("%d", &choix);

                        switch (choix) {
                            case 1:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                afficherCadre("AJOUT D UN EMPLOYE", GREEN);
                                printf("ID : "); scanf("%d", &id);
                                printf("Nom : "); scanf("%s", nom);
                                printf("Prenom : "); scanf("%s", prenom);
                                printf("Mot de passe : "); scanf("%s", mdp);
                                printf("Tache : "); scanf("%s", tache);
                                if (ajouterEmploye(id, nom, prenom, mdp, tache)) {
                                    printf(GREEN "? Employe ajoute et confirme.\n" RESET);
                                } else {
                                    printf(RED "? Echec de l ajout.\n" RESET);
                                }
                                break;

                            case 2:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                afficherCadre("SUPPRESSION D UN EMPLOYE", RED);
                                printf("Entrer l ID de l employe a supprimer : ");
                                scanf("%d", &id);
                                supprimerEmploye(id);
                                break;

                            case 3:
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                                afficherCadre("MODIFICATION DE LA TACHE", YELLOW);
                                printf("Entrer l ID de l employe a modifier : ");
                                scanf("%d", &id);
                                printf("Nouvelle tache : ");
                                scanf("%s", tache);
                                changerTacheEmploye(id, tache);
                                break;

                            case 4:
                                printf("Entrer la date (AAAA-MM-JJ) : ");
                                scanf("%s", date);
                                voirPresenceParDate(date);
                                break;

                            case 5:
                                afficherCadre("Retour au menu principal", CYAN);
                                break;

                            default:
                                afficherCadre("CHOIX INVALIDE", RED);
                                break;
                        }
                    } while (choix != 5);

                } else {
                    afficherCadre("ID ou mot de passe incorrect.", RED);
                }

            } while (!result);
            break;
        }

        case 2: {
            const char *menuPrincipal[] = {"Inscription", "Connexion", "Quitter"};
            int chois;

            while (1) {
                chois = afficherMenuCentre("MENU PRINCIPAL", menuPrincipal, 3);
                switch (chois) {
                    case 0:
                        inscriptionClient();
                        break;
                    case 1: {
                        int id = connexionClient();
                        if (id != -1) {
                            const char *menuClient[] = {
                                "Voir mon profil",
                                "Modifier mes informations",
                                "Faire une reservation",
                                "Voir mes reservations",
                                "Annuler une reservation",
                                "Deconnexion"
                            };
                            int choixClient;
                            do {
                                choixClient = afficherMenuCentre("ESPACE CLIENT", menuClient, 6);
                                switch (choixClient) {
                                    case 0: voirProfilClient(id); break;
                                    case 1: modifierProfilClient(id); break;
                                    case 2: faireReservation(id); break;
                                    case 3: afficherReservationsClient(id); break;
                                    case 4: annulerReservation(id); break;
                                }
                            } while (choixClient != 5);
                        }
                        break;
                    }
                    case 2:
                        afficherCadreCentre(YELLOW "Merci d’avoir utiliser notre application !" RESET);
#ifdef _WIN32
                        _getch();
#else
                        getchar();
#endif
                        return 0;
                }
            }
            break;
        }
    }

    return 0;
}

