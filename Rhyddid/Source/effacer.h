#ifndef EFFACER_H
#define EFFACER_H

/* effacer.c/effacer.h : permet de gerer l'effacement de la console */

/* ----- A inclure ----- */

#include <stdlib.h>

#ifdef __WIN32__
	#include "effacer_windows.h"
#elif __APPLE__
	#include "effacer_mac.h"
#elif __linux__ || __FreeBSD__
	#include "effacer_linux.h"
#else
	#error "OS non compatible"
#endif

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */


/* ----- Declaration ----- */

#endif
