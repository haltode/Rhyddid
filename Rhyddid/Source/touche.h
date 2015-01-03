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

/* Retourne 1 si la touche donnee en parametre indique une direction a prendre et 0 sinon */
unsigned int estDirection(const char touche);
/* Renvoie 1 si la touche est ECHAP et 0 sinon */
unsigned int estMenuPause(const unsigned int touche);


/* Renvoie 1 si la touche donnee en parametre est la meme que actionTouche et 0 sinon */
unsigned int testerTouche(const char touche, const char actionTouche);


/* Effectue une action en fonction de la touche entree */
void effectuerActionToucheEntree(const char toucheEntree);

/* ----- Declaration ----- */


#endif
