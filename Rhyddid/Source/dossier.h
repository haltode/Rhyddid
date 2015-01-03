#ifndef DOSSIER_H
#define DOSSIER_H

/* dossier.h : permet d'inclure toutes les librairires necessaires pour la creation de dossier */

/* ----- A inclure ----- */

#ifdef __WIN32__
	#include "dossier_windows.h"
#elif __APPLE__
	#include "dossier_mac.h"
#elif __linux__ || __FreeBSD__
	#include "dossier_linux.h"
#else
	#error "OS non compatible"
#endif

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */


/* ----- Declaration ----- */

#endif
