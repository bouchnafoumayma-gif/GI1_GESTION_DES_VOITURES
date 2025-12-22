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
    afficherCadreCentre("FAIRE UNE RESERVATION");
    centrerTexte("Voiture : "); scanf("%s", r.voiture);
    centrerTexte("Date de debut (JJ/MM/AAAA) : "); scanf("%s", r.dateDebut);
    centrerTexte("Date de fin (JJ/MM/AAAA) : "); scanf("%s", r.dateFin);
    strcpy(r.statut, "Confirmee");
    r.id = rand() % 10000;
    r.idClient = idClient;

    fprintf(f, "%d %d %s %s %s %s\n",
            r.id, r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut);
    fclose(f);

    afficherCadreCentre(GREEN "Reservation enregistree avec succes !" RESET);
    _getch();
}

void afficherReservationsClient(int idClient) {
    FILE *f = fopen("reservations.txt", "r");
    if (!f) {
        afficherCadreCentre(YELLOW "Aucune reservation trouvee." RESET);
        _getch();
        return;
    }

    Reservation r;
    int trouve = 0;
    afficherLogo();
    afficherCadreCentre("MES RESERVATIONS");
    printf("\n");
    while (fscanf(f, "%d %d %s %s %s %s\n",
                  &r.id, &r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut) == 6) {
        if (r.idClient == idClient) {
            char buffer[150];
            sprintf(buffer, "REservation #%d : %s du %s au %s (%s)",
                    r.id, r.voiture, r.dateDebut, r.dateFin, r.statut);
            centrerTexte(buffer);
            trouve = 1;
        }
    }
    if (!trouve) centrerTexte(YELLOW "Aucune reservation trouvee." RESET);
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
    afficherCadreCentre("ANNULER UNE RESERVATION");
    centrerTexte("Entrez l’ID de la réservation : ");
    scanf("%d", &idAnnul);

    while (fscanf(f, "%d %d %s %s %s %s\n",
                  &r.id, &r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut) == 6) {
        if (r.id == idAnnul && r.idClient == idClient)
            strcpy(r.statut, "Annulee");
        fprintf(tmp, "%d %d %s %s %s %s\n",
                r.id, r.idClient, r.voiture, r.dateDebut, r.dateFin, r.statut);
    }

    fclose(f);
    fclose(tmp);
    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    afficherCadreCentre(GREEN "Reservation annulee." RESET);
    _getch();
}

