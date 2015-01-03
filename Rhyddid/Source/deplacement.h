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

/* Renvoie la direction correspondante a la touche donne en parametre */
unsigned int recupererDirectionTouche(const char touche);


/* Renvoie le deplacement correspondant a direction dimension dans le cas normal */
int recupererDirectionCasNormal(const unsigned int direction,
	const unsigned int dimension);
/* Renvoie le deplacement correspondant a direction dimension dans le cas normal pour le joueur */
int recupererDirectionJoueurCasNormal(const unsigned int direction, 
	const unsigned int dimension);
/* Renvoie le deplacement correspondant a direction dans le cas special pour le joueur */
int recupererDirectionJoueurCasSpecial(const unsigned int direction);


/* Renvoie 1 si les coordonnes donnees sont en dehors de la map et 0 sinon */
unsigned int estDehorsMap(const int coordonnee, const unsigned int longueurMax);
/* Renvoie 1 si la case lig col est un mur et 0 sinon */
unsigned int estMur(const unsigned int lig, const unsigned int col);
/* Retourne 1 si la case lig col est un ennemi */
unsigned int estEnnemi(const unsigned int lig, const unsigned int col);
/* Renvoie 1 si la case lig col est un joueur */
unsigned int estJoueur(const unsigned int lig, const unsigned int col);
/* Renvoie 1 si la case lig col est un endroit impossible a acceder et 0 sinon */
unsigned int estEndroitImpossible(const unsigned int lig, const unsigned int col);


/* Retourne 1 si le joueur se trouvant a la case lig col est une case valide et 0 sinon */
unsigned int testerDeplacementJoueur(const unsigned int lig, const unsigned int col);
/* Deplace le joueur et renvoie 1 si la case ou se trouve le joueur apres le deplacement est 
valide et 0 sinon */
unsigned int estPossibleDeplacementJoueur(const unsigned int direction, 
	const unsigned int position[2], const unsigned int nbColonneCote);
/* Deplace le joueur dans la direction donnee en parametre apres avoir tester si c'est 
possible */
void deplacerJoueurDirection(const unsigned int direction, unsigned int position[2]);

/* ----- Declaration ----- */

#endif
