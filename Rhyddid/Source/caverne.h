#ifndef CAVERNE_H
#define CAVERNE_H

/* caverne.c/caverne.h : permet de gerer les cavernes */

/* ----- A inclure ----- */

#include "ennemi.h"

/* ----- Define ----- */

#define LONGUEUR_CAVERNE 5
#define LARGUEUR_CAVERNE 9

#define NB_COFFRE_MAX_CAVERNE 5
#define NB_ENNEMI_MAX_CAVERNE 12

#define NON_CAVERNE 0
#define CAVERNE 1

#define CHANCE_MAX_CAVERNE_PIEGE 10

/* ----- Structure + Enumeration ----- */

typedef struct Caverne Caverne;
struct Caverne
{
	unsigned int directionEntree;

	unsigned int ligDebut;
	unsigned int colDebut;

	char mapSalle[40][80];
	Ennemi ennemi[NB_ENNEMI_MAX_CAVERNE];
	unsigned int nbEnnemi;
};

/* ----- Prototype ----- */

/* Place une caverne sur le nouveau niveau */
void placerCaverneNouveauNiveau(void);


/* Teste le placement d'une caverne sur le nouveau niveau, retourne 1 si on peut placer la 
caverne a l'emplacement indique par ligne et colonne et 0 sinon */
unsigned int testerPlacementCaverneNouveauNiveau(
	const unsigned int indexSalle, const unsigned int ligneCaverne, 
	const unsigned int colonneCaverne);
/* Permet de determiner une position de caverne dans la salle indexSalle au hasard */
void determinerPositionCaverne(const unsigned int indexSalle);
/* Place une caverne sur la salle indexSalle */
void placerCaverne(const unsigned int indexSalle);
/* Permet de bloquer l'ajout de murs ou autre devant l'entree */
void bloquerAccesIndispensableEntreeCaverne(const unsigned int indexSalle);
/* Permet de generer la salle d'une caverne (interieur de la caverne) */
void genererSalleCaverne(const unsigned int indexSalle);
/* Permet de generer le contenu de la caverne (coffre, ennemi) */
void genererContenuCaverne(const unsigned int indexSalle);
/* Permet de generer une caverne dans la salle indexSalle */
void genererCaverne(const unsigned int indexSalle);


/* Permet d'entrer dans une caverne */
void entrerCaverne(void);


/* Permet de rechercher l'entree d'une caverne et de placer le resultat dans ligneEntreeCaverne 
et colonneEntreeCaverne */
void rechercherEntreeCaverne(unsigned int *ligneEntreeCaverne, 
	unsigned int *colonneEntreeCaverne);
/* Retourne la position de sortie d'une caverne en fonction de la direction et de la dimension */
int positionSortieCaverne(const unsigned int direction, const unsigned int dimension);
/* Permet de sortir de la caverne */
void sortirCaverne(void);

/* ----- Declaration ----- */

#endif
