#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voiture.h"
#include "employe.h"

void afficherToutesVoitures() {
    FILE *f = fopen("voitures.txt", "r");
    if (!f) {
        printf(RED "Erreur : impossible d'ouvrir le fichier voitures.txt\n" RESET);
        return;
    }

    Voiture v;
    int ligne = 0;

    // Lecture avec ESPACES comme séparateurs
    while (fscanf(f, "%d %19s %29s %29s %d %14s %14s %d %19s %f %f %f %f %99s %d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {

        ligne++;
        printf(RED "=====================================\n" RESET);
        printf("ID           : %d\n", v.id);
        printf("Matricule    : %s\n", v.matricule);
        printf("Marque       : %s\n", v.marque);
        printf("Modèle       : %s\n", v.modele);
        printf("Année        : %d\n", v.annee);
        printf("Carburant    : %s\n", v.carburant);
        printf("Transmission : %s\n", v.transmission);
        printf("Places       : %d\n", v.places);
        printf("Couleur      : %s\n", v.couleur);
        printf("Kilométrage  : %.0f km\n", v.kilometrage);
        printf("Prix/Jour    : %.2f MAD\n", v.prixJour);
        printf("Prix/Semaine : %.2f MAD\n", v.prixSemaine);
        printf("Caution      : %.2f MAD\n", v.caution);
        printf("Options      : %s\n", v.options);
        printf("Disponibilité: %s\n", v.disponible ? GREEN "Disponible" RESET : RED "Louée" RESET);
        printf(RED "=====================================\n\n" RESET);
    }

    fclose(f);

    if (ligne == 0) {
        printf(YELLOW "Aucune voiture trouvée dans le fichier.\n" RESET);
    }
}
void supprimerVoiture(int idSupp) {
    FILE *f = fopen("voitures.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf(RED "Erreur : impossible d'ouvrir le fichier.\n" RESET);
        return;
    }

    Voiture v;
    int trouve = 0;

    while (fscanf(f, "%d;%19[^;];%29[^;];%29[^;];%d;%14[^;];%14[^;];%d;%19[^;];%f;%f;%f;%f;%99[^;];%d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {

        if (v.id == idSupp) {
            trouve = 1;
        } else {
            fprintf(temp, "%d;%s;%s;%s;%d;%s;%s;%d;%s;%.0f;%.2f;%.2f;%.2f;%s;%d\n",
                    v.id, v.matricule, v.marque, v.modele, v.annee,
                    v.carburant, v.transmission, v.places, v.couleur,
                    v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
                    v.options, v.disponible);
        }
    }

    fclose(f);
    fclose(temp);

    remove("voitures.txt");
    rename("temp.txt", "voitures.txt");

    if (trouve)
        printf(GREEN "Voiture avec ID %d supprimée avec succès.\n" RESET, idSupp);
    else
        printf(RED "Voiture avec ID %d introuvable.\n" RESET, idSupp);
}

void modifierVoiture(int idModif) {
    FILE *f = fopen("voitures.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf(RED "Erreur : impossible d'ouvrir le fichier.\n" RESET);
        return;
    }

    Voiture v;
    int trouve = 0;

    while (fscanf(f, "%d;%19[^;];%29[^;];%29[^;];%d;%14[^;];%14[^;];%d;%19[^;];%f;%f;%f;%f;%99[^;];%d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {

        if (v.id == idModif) {
            trouve = 1;
            printf(YELLOW "=== Modification de la voiture ID %d ===\n" RESET, idModif);

            char choix;

            printf("Matricule actuel : %s\nModifier ? (o/n) : ", v.matricule);
            scanf(" %c", &choix);
            if (choix == 'o' || choix == 'O') {
                printf("Nouveau matricule : ");
                scanf("%19s", v.matricule);
            }

            printf("Marque actuelle : %s\nModifier ? (o/n) : ", v.marque);
            scanf(" %c", &choix);
            if (choix == 'o' || choix == 'O') {
                printf("Nouvelle marque : ");
                scanf("%29s", v.marque);
            }

            printf("Modele actuel : %s\nModifier ? (o/n) : ", v.modele);
            scanf(" %c", &choix);
            if (choix == 'o' || choix == 'O') {
                printf("Nouveau modele : ");
                scanf("%29s", v.modele);
            }

            printf("Annee actuelle : %d\nModifier ? (o/n) : ", v.annee);
            scanf(" %c", &choix);
            if (choix == 'o' || choix == 'O') {
                printf("Nouvelle annee : ");
                scanf("%d", &v.annee);
            }

            // 👉 À compléter pour carburant, transmission, places, couleur, etc.
        }

        fprintf(temp, "%d;%s;%s;%s;%d;%s;%s;%d;%s;%.0f;%.2f;%.2f;%.2f;%s;%d\n",
                v.id, v.matricule, v.marque, v.modele, v.annee,
                v.carburant, v.transmission, v.places, v.couleur,
                v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
                v.options, v.disponible);
    }

    fclose(f);
    fclose(temp);

    remove("voitures.txt");
    rename("temp.txt", "voitures.txt");

    if (trouve)
        printf(GREEN "Voiture avec ID %d modifiée avec succès.\n" RESET, idModif);
    else
        printf(RED "Voiture avec ID %d introuvable.\n" RESET, idModif);
}