#ifndef LIRE_SANS_ENTREE_WINDOWS_H
#define LIRE_SANS_ENTREE_WINDOWS_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Lit une lettre sans appuyer sur ENTREE */
char lireSansEntree(void);

/* ----- Declaration ----- */

/* Lit une lettre sans appuyer sur ENTREE */
char lireSansEntree(void)
{
	char c;

	c = getch();

	return c;
}

#endif
