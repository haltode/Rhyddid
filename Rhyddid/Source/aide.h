#ifndef AIDE_H
#define AIDE_H

/* aide.c/aide.h : permet d'affiche l'aide de Rhyddid */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Affiche un element de la legende de l'aide */
void afficherElementLegendeAide(const char caractere, 
	const unsigned int couleurCaractere, const char *message);
/* Affiche la legende de l'aide */
void afficherLegendeAide(void);


/* Affiche l'aide de Rhyddid */
void afficherAide(void);
/* Menu Aide */
void aide(void);

/* ----- Declaration ----- */

#endif
