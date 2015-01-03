#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "ecranTitre.h"
#include "menuPrincipal.h"
#include "niveau.h"

int main(void)
{
	srand(time(NULL));
	
	/* On cree la table de donnee contenant les caracteres du niveau */
	creerTableCaractereNiveau();

	/* On affiche l'ecran titre */
	afficherEcranTitre();
	/* On lance le menu principal du jeu */
	menuPrincipal();

	return EXIT_SUCCESS;
}
