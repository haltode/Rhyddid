#include <stdio.h>

#include "creerDossier.h"
#include "dossier.h"

void creerNouveauDossier(const char *nom)
{
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
