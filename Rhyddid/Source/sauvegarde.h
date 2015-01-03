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

/* Recupere le nom des sauvegardes */
void recupererNomSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX]);


/* Recupere les informations du personnage nomPersonnage */
void recupererInformationPersonnage(const char *nomPersonnage);
/* Affiche les informations sur le personnage */
void afficherInformationPersonnageSauvegarde(void);


/* Affiche le menu sauvegarde */
void afficherMenuSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX]);


/* Permet de faire une action (charger ou supprimer) sur la sauvegarde indexSauvegarde */
void actionSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX],
	const unsigned int indexSauvegarde);


/* Menu sauvegarde */
void sauvegarde(void);

/* ----- Declaration ----- */

#endif
