#ifndef METIER_H
#define METIER_H

/* ----- A inclure ----- */


/* ----- Define ----- */

#define NB_METIER 15

/* ----- Structure + Enumeration ----- */

typedef struct Metier Metier;
struct Metier
{
	const char *nomMetier;
	const unsigned int sante;
	const unsigned int protection;
	const unsigned int degatParTour;
};

/* ----- Prototype ----- */

void demanderMetierNouveauPersonnage(void);


void afficherDifferentMetier(void);

/* ----- Declaration ----- */

#endif
