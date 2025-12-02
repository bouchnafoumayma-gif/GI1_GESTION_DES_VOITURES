#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employe.h"

int main() {
    char login[30], motdepasse[30];
    int result, choix, id;
    char nom[30], prenom[30], mdp[30], tache[30];
do{

    // ? Connexion
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
        afficherCadre("? Connexion reussie en tant qu'EMPLOYE !", GREEN);
    } else if (result == 2) {
        afficherCadre("? Connexion reussie en tant qu'ADMIN !", YELLOW);
        // ? Menu ADMIN encadr�
        const char* menu[] = {
            "1. AJOUTER UN EMPLOYE",
            "2. SUPPRIMER UN EMPLOYE",
            "3. CHANGER LA TACHE D'UN EMPLOYE"
        };
   do{
        
        afficherCadreMulti(menu, 3, CYAN);

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
                printf("Pr�nom : "); scanf("%s", prenom);
                printf("Mot de passe : "); scanf("%s", mdp);
                printf("T�che : "); scanf("%s", tache);
                ajouterEmploye(id, nom, prenom, mdp, tache);
                break;

            case 2:
            		#ifdef _WIN32
                  system("cls");
                #else
                  system("clear");
                 #endif
                afficherCadre("SUPPRESSION D'UN EMPLOYE", RED);
                printf("Entrer l'ID de l'employ� � supprimer : ");
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
                printf("Entrer l'ID de l'employ� � modifier : ");
                scanf("%d", &id);
                printf("Nouvelle t�che : ");
                scanf("%s", tache);
                changerTacheEmploye(id, tache);
                break;
            case 4:
            	#ifdef _WIN32
                  system("cls");
                #else
                  system("clear");
                 #endif
                 afficherCadreMulti(menu, 3, CYAN);
            default:
            		#ifdef _WIN32
                  system("cls");
                #else
                  system("clear");
                 #endif
                afficherCadre("CHOIX INVALIDE", RED);
				}}while(choix =! 1 || choix != 2 || choix != 3);}
    else {
        	#ifdef _WIN32
                  system("cls");
                #else
                  system("clear");
                 #endif
          afficherCadre("? ID ou mot de passe incorrect.", RED);   
		      
		    
    }

}while(!result);


    return 0;
}
