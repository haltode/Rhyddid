#ifndef ACTION_H
#define ACTION_H

/* action.c/action.h : permet de detecter des actions (soit sur la case, soit par une touche
entree par le joueur) */


/* ----- A inclure ----- */

#include "jeu.h"

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Execute l'interaction sur la case ou se trouve le joueur */
void actionCase(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);

/* Lis la touche du clavier pressee par le joueur et deduis l'action qu'il faut faire */
void actionJoueur(void);

/* ----- Declaration ----- */


#endif
