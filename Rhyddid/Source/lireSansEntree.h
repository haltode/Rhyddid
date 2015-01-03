#ifndef LIRE_SANS_ENTREE_H
#define LIRE_SANS_ENTREE_H

/* lireSansEntree.h : permet de lire sur l'entree sans que le joueur appuie sur ENTREE */

/* ----- A inclure ----- */

#ifdef __WIN32__
	#include "lireSansEntree_windows.h"
#elif __APPLE__
	#include "lireSansEntree_mac.h"
#elif __linux__ || __FreeBSD__
	#include "lireSansEntree_linux.h"
#else
	#error "OS non compatible"
#endif

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */


/* ----- Declaration ----- */

#endif
