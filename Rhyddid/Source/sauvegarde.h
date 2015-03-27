#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

/* sauvegarde.c/sauvegarde.h : permet de gerer le menu sauvegarde */

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_SAUVEGARDE 3

#define NB_ACTION_SAUVEGARDE 2

/* ----- Structure + Enumeration ----- */

enum actionSauvegarde
{
	CHARGER = 1,
	SUPPRIMER = 2
};

/* ----- Prototype ----- */

void recupererNomSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX]);


void recupererInformationPersonnage(const char *nomPersonnage);
void afficherInformationPersonnageSauvegarde(void);


void afficherMenuSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX]);


void actionSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX],
	const unsigned int indexSauvegarde);


void sauvegarde(void);

/* ----- Declaration ----- */

#endif
