#ifndef COULEUR_H
#define COULEUR_H

/* couleur.c/couleur.h : permet de gerer les couleurs */

/* ----- A inclure ----- */

#ifdef __WIN32__
	#include "couleur_windows.h"
#elif __APPLE__
	#include "couleur_mac.h"
#elif __linux__ || __FreeBSD__
	#include "couleur_linux.h"
#else
	#error "OS non compatible"
#endif

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

void couleur(const unsigned int typeCouleur);
void coloration(const char *texte, const unsigned int typeCouleur);
void colorationCaractere(const char caractere, const unsigned int typeCouleur);

/* ----- Declaration ----- */

#endif
