#ifndef RACE_H
#define RACE_H

/* race.c/race.h : permet de gerer les races */

/* ----- A inclure ----- */

#include "menu.h"

/* ----- Define ----- */

#define NB_RACE 6
#define NB_CARACTERISTIQUE_RACE 3

#define NB_ANGLE_DE_VUE 4

/* ----- Structure + Enumeration ----- */

enum race
{
	HUMAIN = 0,
	ALIEN = 1,
	NAIN = 2,
	SORCIER = 3,
	GUERRIER = 4,
	OGRE = 5,
	ERREUR_RACE = 6
};

enum angleDeVue
{
	DEVANT = 0,
	DERRIERE = 1,
	GAUCHE = 2,
	DROITE = 3
};

enum caracteristique
{
	SANTE_RACE = 0,
	PROTECTION_RACE = 1,
	DEGAT_RACE = 2
};

/* ----- Prototype ----- */

/* Renvoie le nom de la race correspondant a l'index indexRace */
const char *recupererNomRace(const unsigned int indexRace);
/* Renvoie l'index correspondant au nom de la race donne en parametre */
unsigned int recupererIndexRace(const char *nomRace);


/* Cree un menu contenant chaque race */
void creerMenuRace(Menu *menu);


/* Affiche la race donnee en parametre */
void afficherRace(const char *nomRace);


/* Permet de visualiser les differentes races */
void visualiserRaceNouveauPersonnage(void);
/* Permet de choisir une race */
void choisirRaceNouveauPersonnage(void);
/* Permet de choisir entre soit visualiser soit choisir une race */
void choisirEtVisualiserRaceNouveauPersonnage(void);
/* Demande la race du nouveau personnage */
void demanderRaceNouveauPersonnage(void);


/* Affecte les caracteristiques d'une race donnee en parametre au joueur */
void affecterCaracteristiqueRace(void);

/* ----- Declaration ----- */

#endif
