#ifndef LIRE_SANS_ENTREE_WINDOWS_H
#define LIRE_SANS_ENTREE_WINDOWS_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

char lireSansEntree(void);

/* ----- Declaration ----- */

char lireSansEntree(void)
{
	char c;

	c = getch();

	return c;
}

#endif
