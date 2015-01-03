#include <stdio.h>

#include "creerDossier.h"
#include "dossier.h"

/* Cree un nouveau dossier du nom donne en parametre */
void creerNouveauDossier(const char *nom)
{
	/* Si le joueur est sous windows il suffit juste de creer le dossier avec mkdir sinon il
	faut le creer et donner les droits au joueur */

	#ifdef __WIN32__
		mkdir(nom);
	#elif __APPLE__
		mkdir(nom, 0);
		chmod(nom, S_IRWXU);
	#elif __linux__ || __FreeBSD__
		mkdir(nom, 0);
		chmod(nom, S_IRWXU);
	#else
		#error "OS non compatible"
	#endif
}
