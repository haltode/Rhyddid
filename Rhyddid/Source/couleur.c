#include <stdio.h>

#include "couleur.h"
#include "fonctionsUtiles.h"

/* Initialisaiton la couleur de la sortie a typeCouleur */
void couleur(const unsigned int typeCouleur)
{
	#ifdef __WIN32__
		HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
   		SetConsoleTextAttribute(H, typeCouleur);
	#elif __APPLE__ || __linux__ || __FreeBSD__
		printf("\033[%dm", typeCouleur);
	#else
		#error "OS non compatible"
	#endif
	
}

/* Fonction qui affiche le texte donne en parametre en couleur donne en parametre */
void coloration(const char *texte, const unsigned int typeCouleur)
{
	couleur(typeCouleur);
	printf("%s", texte);
	couleur(BLANC);
}

/* Fonction qui affiche le caractere donne en parametre en couleur donne en parametre */
void colorationCaractere(const char caractere, const unsigned int typeCouleur)
{
	couleur(typeCouleur);
	putchar(caractere);
	couleur(BLANC);
}
