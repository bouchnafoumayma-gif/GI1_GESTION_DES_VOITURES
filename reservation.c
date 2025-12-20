#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "interface.h"
#include "reservation.h"


void faireReservation(int idClient) {
    Reservation r;
    FILE *f = fopen("reservations.txt", "a+");
    if (!f) return;

    afficherLogo();
    afficherCadreCentre("FAIRE UNE RÉSERVATION");
    centrerTexte("Voiture : "); scanf("%s", r.voiture);
    centrerTexte("Date de début (JJ/MM/AAAA) : "); scanf("%s", r.dateDebut);
    centrerTexte("Date de fin (JJ/MM/AAAA) : "); scanf("%s", r.dateFin);
    strcpy(r.statut, "Confirmée");
    r.id = rand() % 10000;
    r.idClient = idClient;

    fprintf(f, "%d %d %s %s %s %s\n",
            r.id, r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut);
    fclose(f);

    afficherCadreCentre(GREEN "Réservation enregistrée avec succès !" RESET);
    _getch();
}

void afficherReservationsClient(int idClient) {
    FILE *f = fopen("reservations.txt", "r");
    if (!f) {
        afficherCadreCentre(YELLOW "Aucune réservation trouvée." RESET);
        _getch();
        return;
    }

    Reservation r;
    int trouve = 0;
    afficherLogo();
    afficherCadreCentre("MES RÉSERVATIONS");
    printf("\n");
    while (fscanf(f, "%d %d %s %s %s %s\n",
                  &r.id, &r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut) == 6) {
        if (r.idClient == idClient) {
            char buffer[150];
            sprintf(buffer, "Réservation #%d : %s du %s au %s (%s)",
                    r.id, r.voiture, r.dateDebut, r.dateFin, r.statut);
            centrerTexte(buffer);
            trouve = 1;
        }
    }
    if (!trouve) centrerTexte(YELLOW "Aucune réservation trouvée." RESET);
    fclose(f);
    _getch();
}

void annulerReservation(int idClient) {
    FILE *f = fopen("reservations.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    if (!f || !tmp) return;

    int idAnnul;
    Reservation r;
    afficherLogo();
    afficherCadreCentre("ANNULER UNE RÉSERVATION");
    centrerTexte("Entrez l’ID de la réservation : ");
    scanf("%d", &idAnnul);

    while (fscanf(f, "%d %d %s %s %s %s\n",
                  &r.id, &r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut) == 6) {
        if (r.id == idAnnul && r.idClient == idClient)
            strcpy(r.statut, "Annulée");
        fprintf(tmp, "%d %d %s %s %s %s\n",
                r.id, r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut);
    }

    fclose(f);
    fclose(tmp);
    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    afficherCadreCentre(GREEN "Réservation annulée." RESET);
    _getch();
}

