#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

/* deplacement.c/deplacement.h : permet de gerer les deplacements */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define LIG 0
#define COL 1

#define NB_DIRECTION 4

#define CAS_NORMAL 2
#define CAS_SPECIAL 1

/* ----- Structure + Enumeration ----- */

enum Direction 
{
	HAUT = 0,
	BAS = 1,
	GAUCHE = 2,
	DROITE = 3,
	ERREUR_DIRECTION = 4
};

/* ----- Prototype ----- */

unsigned int recupererDirectionTouche(const char touche);


int recupererDirectionCasNormal(const unsigned int direction,
	const unsigned int dimension);
int recupererDirectionJoueurCasNormal(const unsigned int direction, 
	const unsigned int dimension);
int recupererDirectionJoueurCasSpecial(const unsigned int direction);


unsigned int estDehorsMap(const int coordonnee, const unsigned int longueurMax);
unsigned int estMur(const unsigned int lig, const unsigned int col);
unsigned int estEnnemi(const unsigned int lig, const unsigned int col);
unsigned int estJoueur(const unsigned int lig, const unsigned int col);
unsigned int estEndroitImpossible(const unsigned int lig, const unsigned int col);


unsigned int testerDeplacementJoueur(const unsigned int lig, const unsigned int col);
unsigned int estPossibleDeplacementJoueur(const unsigned int direction, 
	const unsigned int position[2], const unsigned int nbColonneCote);
void deplacerJoueurDirection(const unsigned int direction, unsigned int position[2]);

/* ----- Declaration ----- */

#endif
