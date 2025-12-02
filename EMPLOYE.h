#ifndef EMPLOYE_H
#define EMPLOYE_H

// ? Structure de base pour un employé
typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char motDePasse[30];
    char tache[30];
} Employe;

// ? Couleurs ANSI pour affichage
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

// ? Fonctions de vérification
int oumayma(const char* login, const char* motDePasse);

// ? Fonctions d'affichage
void afficherCadre(const char* message, const char* couleur);
void afficherCadreMulti(const char* lignes[], int nbLignes, const char* couleur);
void afficherFicheEmploye(int id, const char* nom, const char* prenom, const char* mdp, const char* tache);

// ? Fonctions de gestion des employés
void ajouterEmploye(int id, const char* nom, const char* prenom, const char* mdp, const char* tache);
void supprimerEmploye(int idASupprimer);
void changerTacheEmploye(int idAModifier, const char* nouvelleTache);

#endif
