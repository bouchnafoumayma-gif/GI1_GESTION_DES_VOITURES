#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voiture.h"

// 📂 Nom du fichier des voitures
#define FICHIER_VOITURES "voiture.txt"

// ======================= AFFICHER =======================
void afficherToutesVoitures(void) {
    FILE *f = fopen(FICHIER_VOITURES, "r");
    if (!f) {
        printf(RED "Erreur : impossible d’ouvrir le fichier %s\n" RESET, FICHIER_VOITURES);
        return;
    }

    Voiture v;
    while (fscanf(f, "%d %s %s %s %d %s %s %d %s %f %f %f %f %s %d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {
        printf(GREEN "ID:%d | %s %s %s (%d) | %s | %s | %d places | %s | %.0f km | %.2f€/jour | %.2f€/semaine | Caution: %.2f | Options:%s | Disponible:%d\n" RESET,
               v.id, v.matricule, v.marque, v.modele, v.annee,
               v.carburant, v.transmission, v.places, v.couleur,
               v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
               v.options, v.disponible);
    }

    fclose(f);
}

// ======================= SUPPRIMER =======================
void supprimerVoiture(int idSupp) {
    FILE *f = fopen(FICHIER_VOITURES, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        printf(RED "Erreur ouverture fichier.\n" RESET);
        return;
    }

    Voiture v;
    int trouve = 0;
    while (fscanf(f, "%d %s %s %s %d %s %s %d %s %f %f %f %f %s %d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {
        if (v.id != idSupp) {
            fprintf(temp, "%d %s %s %s %d %s %s %d %s %.0f %.2f %.2f %.2f %s %d\n",
                    v.id, v.matricule, v.marque, v.modele, v.annee,
                    v.carburant, v.transmission, v.places, v.couleur,
                    v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
                    v.options, v.disponible);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER_VOITURES);
    rename("temp.txt", FICHIER_VOITURES);

    if (trouve)
        printf(GREEN "Voiture supprimée avec succès.\n" RESET);
    else
        printf(RED "Voiture avec ID %d introuvable.\n" RESET, idSupp);
}

// ======================= MODIFIER =======================
void modifierVoiture(int idModif) {
    FILE *f = fopen(FICHIER_VOITURES, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        printf(RED "Erreur ouverture fichier.\n" RESET);
        return;
    }

    Voiture v;
    int trouve = 0;
    while (fscanf(f, "%d %s %s %s %d %s %s %d %s %f %f %f %f %s %d",
                  &v.id, v.matricule, v.marque, v.modele, &v.annee,
                  v.carburant, v.transmission, &v.places, v.couleur,
                  &v.kilometrage, &v.prixJour, &v.prixSemaine, &v.caution,
                  v.options, &v.disponible) == 15) {
        if (v.id == idModif) {
            trouve = 1;
            printf(YELLOW "Modification de la voiture ID %d\n" RESET, idModif);
            printf("Nouveau prix par jour : "); scanf("%f", &v.prixJour);
            printf("Nouveau prix par semaine : "); scanf("%f", &v.prixSemaine);
            printf("Nouvelle disponibilité (0/1) : "); scanf("%d", &v.disponible);
        }
        fprintf(temp, "%d %s %s %s %d %s %s %d %s %.0f %.2f %.2f %.2f %s %d\n",
                v.id, v.matricule, v.marque, v.modele, v.annee,
                v.carburant, v.transmission, v.places, v.couleur,
                v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
                v.options, v.disponible);
    }
    fclose(f);
    fclose(temp);

    remove(FICHIER_VOITURES);
    rename("temp.txt", FICHIER_VOITURES);

    if (trouve)
        printf(GREEN "Voiture modifiée avec succès.\n" RESET);
    else
        printf(RED "Voiture avec ID %d introuvable.\n" RESET, idModif);
}

// ======================= AJOUTER =======================
void ajouterVoiture() {
    FILE *f = fopen("voiture.txt", "a"); // 🔒 Mode append pour ne pas écraser
    if (!f) {
        printf(RED "Erreur : impossible d’ouvrir le fichier voiture.txt\n" RESET);
        return;
    }

    int n;
    printf(YELLOW "Combien de voitures voulez-vous ajouter ? " RESET);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Voiture v;
        printf(CYAN "\n--- Voiture %d ---\n" RESET, i + 1);

        printf("ID : "); scanf("%d", &v.id);
        printf("Matricule : "); scanf("%s", v.matricule);
        printf("Marque : "); scanf("%s", v.marque);
        printf("Modèle : "); scanf("%s", v.modele);
        printf("Année : "); scanf("%d", &v.annee);
        printf("Carburant : "); scanf("%s", v.carburant);
        printf("Transmission : "); scanf("%s", v.transmission);
        printf("Nombre de places : "); scanf("%d", &v.places);
        printf("Couleur : "); scanf("%s", v.couleur);
        printf("Kilométrage : "); scanf("%f", &v.kilometrage);
        printf("Prix par jour : "); scanf("%f", &v.prixJour);
        printf("Prix par semaine : "); scanf("%f", &v.prixSemaine);
        printf("Caution : "); scanf("%f", &v.caution);
        printf("Options : "); scanf("%s", v.options);
        printf("Disponible (1=oui, 0=non) : "); scanf("%d", &v.disponible);

        fprintf(f, "%d %s %s %s %d %s %s %d %s %.0f %.2f %.2f %.2f %s %d\n",
                v.id, v.matricule, v.marque, v.modele, v.annee,
                v.carburant, v.transmission, v.places, v.couleur,
                v.kilometrage, v.prixJour, v.prixSemaine, v.caution,
                v.options, v.disponible);
    }

    fclose(f);
    printf(GREEN "\n✅ Voiture(s) ajoutée(s) avec succès !\n" RESET);
}