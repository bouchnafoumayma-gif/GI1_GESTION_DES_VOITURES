#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>


#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define WHITE   "\x1b[1;37m"

void effacerConsole();
void centrerTexte(const char *texte);
void afficherCadreCentre(const char *titre);
void afficherLogo();
void saisirMotDePasse(char *motDePasse);
int afficherMenuCentre(const char *titre, const char *options[], int n);

#endif

