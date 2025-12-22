#ifndef RESERVATION_H
#define RESERVATION_H

typedef struct {
    int id;
    int idClient;
    char voiture[50];
    char dateDebut[20];
    char dateFin[20];
    char statut[20];
} Reservation;

void faireReservation(int idClient);
void afficherReservationsClient(int idClient);
void annulerReservation(int idClient);

#endif

