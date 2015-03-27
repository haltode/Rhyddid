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

void lireInformationHighscore(FILE *fichierHighscore, Highscore baseHighscore[NB_HIGHSCORE]);
void ecrireInformationHighscore(FILE *fichier, const Highscore baseHighscore[NB_HIGHSCORE]);


void afficherHighscoreIndividuel(const Highscore *baseHighscore);
void afficherHighscore(void);


void ajouterHighscore(void);


void highscore(void);

/* ----- Declaration ----- */


#endif
