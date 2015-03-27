#ifndef TRESOR_H
#define TRESOR_H

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_TRESOR_MAX 5

#define NB_TRESOR 50

/* ----- Structure + Enumeration ----- */

typedef struct Coffre Coffre;

typedef struct Tresor Tresor;
struct Tresor
{
	char nom[TAILLE_MAX];
	unsigned int cout;
};

/* ----- Prototype ----- */

void initialiserTresorInventaire(void);
void chargerTresorInventaire(void);
void sauvegarderTresorInventaire(void);
void afficherTresorIndividuelInventaire(const unsigned int indexTresor);
void afficherTresorInventaire(void);


void genererTresorCoffre(Tresor *tresor);
void afficherTresorCoffre(const Coffre *coffre);
void prendreTresorCoffre(const Tresor *tresor);


unsigned int joueurPossedeTresor(void);


void vendreTresor(const unsigned int indexTresor);

/* ----- Declaration ----- */

#endif
