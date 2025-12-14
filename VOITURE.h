#ifndef VOITURE_H
#define VOITURE_H

typedef struct {
    int id;
    char matricule[20];
    char marque[30];
    char modele[30];
    int annee;
    char carburant[15];
    char transmission[15];
    int places;
    char couleur[20];
    float kilometrage;
    float prixJour;
    float prixSemaine;
    float caution;
    char options[100];
    int disponible;
} Voiture;

// 🎨 Couleurs ANSI pour affichage
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

// Prototypes des fonctions liées aux voitures
void afficherToutesVoitures(void);
void supprimerVoiture(int idSupp);
void modifierVoiture(int idModif);

#endif