#ifndef LIRE_SANS_ENTREE_LINUX_H
#define LIRE_SANS_ENTREE_LINUX_H

/* ----- A inclure ----- */

#include <termios.h>
#include <unistd.h>

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

	struct termios term, tmp;
		
	if(tcgetattr(STDIN_FILENO, &term) < 0)
		return EOF;
			
	tmp = term;
	tmp.c_lflag &= ~ICANON;
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;	
		
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &tmp) < 0)
		return EOF;
	
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

	return c;
}

#endif
