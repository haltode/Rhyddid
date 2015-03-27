#include <stdio.h>
#include <stdlib.h>

#include "quitter.h"
#include "fonctionsUtiles.h"

void quitter(void)
{
	separationTexte();
	printf("Au revoir ! :)\n\n");

	exit(EXIT_SUCCESS);
}
