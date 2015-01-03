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

/* Initialise les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void initialiserTresorInventaire(void);
/* Charge les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void chargerTresorInventaire(void);
/* Sauvegarde les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void sauvegarderTresorInventaire(void);
/* Affiche une partie individuelle de la section Tresor de l'inventaire lorsqu'on ouvre 
l'inventaire */
void afficherTresorIndividuelInventaire(const unsigned int indexTresor);
/* Affiche la section Tresor de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherTresorInventaire(void);


/* Genere un tresor au hasard situe dans un coffre */
void genererTresorCoffre(Tresor *tresor);
/* Affiche la section Tresor d'un coffre lorsqu'on l'ouvre */
void afficherTresorCoffre(const Coffre *coffre);
/* Prend le tresor situe dans le coffre que le joueur vient d'ouvrir (donne en parametre) */
void prendreTresorCoffre(const Tresor *tresor);


/* Renvoie 1 si le joueur possede au moins 1 tresor et 0 sinon */
unsigned int joueurPossedeTresor(void);


/* Vend le tresor indexTresor */
void vendreTresor(const unsigned int indexTresor);

/* ----- Declaration ----- */

#endif
