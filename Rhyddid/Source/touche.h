#ifndef TOUCHE_H
#define TOUCHE_H

/* touche.c/touche.h : permet de gerer les touches entrees par le joueur */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define ECHAP 27

#define NB_TOUCHE 4

/* ----- Structure + Enumeration ----- */

typedef struct Touche Touche;
struct Touche
{
	char touche;
	void (*pointeurFonction)(void);
};

/* ----- Prototype ----- */

unsigned int estDirection(const char touche);
unsigned int estMenuPause(const unsigned int touche);


unsigned int testerTouche(const char touche, const char actionTouche);


void effectuerActionToucheEntree(const char toucheEntree);

/* ----- Declaration ----- */


#endif
