#ifndef HIGHSCORE_H
#define HIGHSCORE_H

/* highscore.c/highscore.h : permet de gerer le highscore */

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_HIGHSCORE 10

/* ----- Structure + Enumeration ----- */

typedef struct Highscore Highscore;
struct Highscore
{
	char nom[TAILLE_MAX];
	char race[TAILLE_MAX];
	char metier[TAILLE_MAX];
	unsigned int lvl;
	unsigned int niveau;
};

/* ----- Prototype ----- */

/* Lit le fichier "Highscore.txt" et le charge dans la structure Highscore */
void lireInformationHighscore(FILE *fichierHighscore, Highscore baseHighscore[NB_HIGHSCORE]);
/* Ecrit dans le fichier "Highscore.txt" la structure Highscore */
void ecrireInformationHighscore(FILE *fichier, const Highscore baseHighscore[NB_HIGHSCORE]);


/* Affiche individuellement un highscore */
void afficherHighscoreIndividuel(const Highscore *baseHighscore);
/* Affiche le highscore en entier */
void afficherHighscore(void);


/* Ajoute une sauvegarde au highscore */
void ajouterHighscore(void);


/* Affiche le highscore et retourne au menu principal */
void highscore(void);

/* ----- Declaration ----- */


#endif
