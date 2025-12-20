#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "interface.h"

#define LARGEUR_CONSOLE 80

void effacerConsole() {
    system("cls");
}

void centrerTexte(const char *texte) {
    int len = strlen(texte);
    int spaces = (LARGEUR_CONSOLE - len) / 2;
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s\n", texte);
}

void afficherCadreCentre(const char *titre) {
    int len = strlen(titre);
    int total = LARGEUR_CONSOLE;
    int spaces = (total - len - 4) / 2;

    printf(CYAN);
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("+");
    for (int i = 0; i < len + 2; i++) printf("-");
    printf("+\n");

    for (int i = 0; i < spaces; i++) printf(" ");
    printf("¦ %s ¦\n", titre);

    for (int i = 0; i < spaces; i++) printf(" ");
    printf("+");
    for (int i = 0; i < len + 2; i++) printf("-");
    printf("+\n");
    printf(RESET);
}

void afficherLogo() {
    effacerConsole();
    centrerTexte(CYAN "+----------------------------------------------------------------------+" RESET);
    centrerTexte(CYAN "¦          SYSTEME DE LOCATION DE VOITURES - CLIENT                   ¦" RESET);
    centrerTexte(CYAN "+----------------------------------------------------------------------+" RESET);
}

void saisirMotDePasse(char *motDePasse) {
    char c; int i = 0;
    printf("Mot de passe : ");
    while ((c = _getch()) != 13) {
        if (c == 8 && i > 0) { printf("\b \b"); i--; }
        else if (c != 8) { motDePasse[i++] = c; printf("*"); }
    }
    motDePasse[i] = '\0';
    printf("\n");
}

int afficherMenuCentre(const char *titre, const char *options[], int n) {
    int choix = 0;
    int touche;

    while (1) {
        afficherLogo();
        afficherCadreCentre(titre);

        printf("\n");
        for (int i = 0; i < n; i++) {
            int len = strlen(options[i]) + 6;
            int spaces = (LARGEUR_CONSOLE - len) / 2;
            for (int j = 0; j < spaces; j++) printf(" ");
            if (i == choix)
                printf(GREEN ">  %s\n" RESET, options[i]);
            else
                printf("   %s\n", options[i]);
        }

        printf("\n");
        centrerTexte(YELLOW "Utilisez ? ? pour naviguer et Entrée pour valider." RESET);

        touche = _getch();
        if (touche == 72 && choix > 0)
            choix--;
        else if (touche == 80 && choix < n - 1)
            choix++;
        else if (touche == 13)
            break;
    }
    return choix;
}

