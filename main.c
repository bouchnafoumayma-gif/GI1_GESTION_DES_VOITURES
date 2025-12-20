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
    char date[20]; // ✅ Déclaration ajoutée pour le menu admin (case 4)
    int A;
    /// LOGO

    printf(BLUE);
    printf("    _      _       _        _       _                   _                     \n");
    printf("   / \\    | |     | |      | |     | |                 | |                    \n");
    printf("  / _ \\   | |     | |      | |     | |     __ _ _ __ __| | ___ _ __ ___ ___   \n");
    printf(" / ___ \\  | |___  | |___   | |___  | |__  / _` | '__/ _` |/ _ \\ '__/ __/ _ \\  \n");
    printf("/_/   \\_\\ |_____| |_____|  |_____| |____|\\__,_|_|  \\__,_|\\___/|  |\\___\\___/  \n");
    printf("                                                            | |              \n");
    printf("                                                            |_|              \n");
    printf(RESET);

    printf(BLUE "\nBienvenue dans ALLOCATION_HOUSE !\n\n" RESET);
    getchar();
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux / Mac
#endif
    ///PAGE1
    printf(BLUE"*******************************************BONJOUR!******************************\n"RESET);
    printf(BLUE"*********POUR UNE CONNEXION EN TANT QUE EMPLOYE CLIQUE SUR 1 EN TANT QUE CLIENT CLIQUE SUR 2**********\n"RESET);
    scanf("%d",&A);
    #ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux / Mac
#endif
    //////////////
    switch(A){
        case 1:{
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
                        break; // ✅ Ajout du break pour éviter le “fall-through”

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
                        printf("Entrez l ID de la voiture a modifier : ");
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
                        printf(CYAN "\nAu revoir 👋\n" RESET);
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
                "3. CHANGER LA TaCHE D'UN EMPLOYE",
                "4. Voir presences par date",
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
                        afficherCadre("AJOUT D UN EMPLOYE", GREEN);
                        printf("ID : "); scanf("%d", &id);
                        printf("Nom : "); scanf("%s", nom);
                        printf("Prenom : "); scanf("%s", prenom);
                        printf("Mot de passe : "); scanf("%s", mdp);
                        printf("Tache : "); scanf("%s", tache);
                        if (ajouterEmploye(id, nom, prenom, mdp, tache)) {
                            printf(GREEN "✔ Employe ajoute et confirme.\n" RESET);
                        } else {
                            printf(RED "✖ Echec de l ajout.\n" RESET);
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
                        afficherCadre("MODIFICATION DE LA TÂCHE", YELLOW);
                        printf("Entrer l ID de l employe a modifier : ");
                        scanf("%d", &id);
                        printf("Nouvelle tache : ");
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
break;
 case 2:
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
                        "Faire une réservation",
                        "Voir mes réservations",
                        "Annuler une réservation",
                        "Déconnexion"
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
                afficherCadreCentre(YELLOW "Merci d’avoir utilisé notre application !" RESET);
                _getch();
          
    }
}
  break;
}
}

    return 0;
}