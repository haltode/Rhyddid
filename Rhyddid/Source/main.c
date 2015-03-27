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
	
	creerTableCaractereNiveau();

	afficherEcranTitre();
	menuPrincipal();

	return EXIT_SUCCESS;
}
