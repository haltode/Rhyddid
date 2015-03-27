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

const char *recupererNomRace(const unsigned int indexRace);
unsigned int recupererIndexRace(const char *nomRace);


void creerMenuRace(Menu *menu);


void afficherRace(const char *nomRace);


void visualiserRaceNouveauPersonnage(void);
void choisirRaceNouveauPersonnage(void);
void choisirEtVisualiserRaceNouveauPersonnage(void);
void demanderRaceNouveauPersonnage(void);


void affecterCaracteristiqueRace(void);

/* ----- Declaration ----- */

#endif
