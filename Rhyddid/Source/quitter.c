#include <stdio.h>
#include <stdlib.h>

#include "quitter.h"
#include "fonctionsUtiles.h"

/* Quitte le jeu */
void quitter(void)
{
	separationTexte();
	printf("Au revoir ! :)\n\n");

	exit(EXIT_SUCCESS);
}
