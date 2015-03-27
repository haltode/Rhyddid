#include <stdio.h>
#include <string.h>

#include "deplacement.h"
#include "niveau.h"
#include "ennemi.h"
#include "personnage.h"

unsigned int recupererDirectionTouche(const char touche)
{
	switch(touche)
	{
		case 'z': case 'Z':
			return HAUT;
		break;

		case 's': case 'S':
			return BAS;
		break;

		case 'q': case 'Q':
			return GAUCHE;
		break;
		
		case 'd': case 'D':
			return DROITE;
		break;
	}

	return ERREUR_DIRECTION;
}

int recupererDirectionCasNormal(const unsigned int direction,
	const unsigned int dimension)
{
	static const int baseDirection[NB_DIRECTION][2] =
	{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	return baseDirection[direction][dimension];
}

int recupererDirectionJoueurCasNormal(const unsigned int direction, 
	const unsigned int dimension)
{
	static const int baseDirectionJoueurCasNormal[NB_DIRECTION][2] =
	{
		{-1, 0},
		{1, 0},
		{0, -2},
		{0, 2}
	};

	return baseDirectionJoueurCasNormal[direction][dimension];
}

int recupererDirectionJoueurCasSpecial(const unsigned int direction)
{
	static const int baseDirectionJoueurCasSpecial[NB_DIRECTION] =
	{
		0,
		0,
		-1,
		1
	};

	return baseDirectionJoueurCasSpecial[direction];
}

unsigned int estDehorsMap(const int coordonnee, const unsigned int longueurMax)
{
	return coordonnee < 0 || coordonnee > longueurMax;
}

unsigned int estMur(const unsigned int lig, const unsigned int col)
{
	static const char baseCaractereMur[] = "#|-_\\/`,\'";
	char caractere;

	if(niveauActuel.estDansCaverne)
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	return strchr(baseCaractereMur, caractere) != NULL;
}

unsigned int estEnnemi(const unsigned int lig, const unsigned int col)
{
	return trouverIndexEnnemi(lig, col) != -1;
}

unsigned int estJoueur(const unsigned int lig, const unsigned int col)
{
	return lig == personnage.positionJoueur[LIG] && col == personnage.positionJoueur[COL];
}

unsigned int estEndroitImpossible(const unsigned int lig, const unsigned int col)
{
	char caractere;

	if(niveauActuel.estDansCaverne)
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	return caractere == '.' || (estEnnemi(lig, col) && !estMortEnnemi(trouverIndexEnnemi(lig, col))) ||
	  	estJoueur(lig, col);
}

unsigned int testerDeplacementJoueur(const unsigned int lig, const unsigned int col)
{
    return !(   estDehorsMap(lig, LARGUEUR_SALLE)   || 
                estDehorsMap(col, LONGUEUR_SALLE)   ||
                estMur(lig, col)                    ||
                estEndroitImpossible(lig, col));
}

unsigned int estPossibleDeplacementJoueur(const unsigned int direction, 
	const unsigned int position[2], const unsigned int nbColonneCote)
{
	unsigned int testLig, testCol;

	testLig = position[LIG] + recupererDirectionJoueurCasNormal(direction, LIG);

	if(nbColonneCote == CAS_NORMAL)
		testCol = position[COL] + recupererDirectionJoueurCasNormal(direction, COL);
	else
		testCol = position[COL] + recupererDirectionJoueurCasSpecial(direction);

	return testerDeplacementJoueur(testLig, testCol);
}

void deplacerJoueurDirection(const unsigned int direction, unsigned int position[2])
{
	/* Colonne impaire = sol (normal) 
	   Colonne paire = porte decalee ou mur decale (non normal) 
	*/

	/* Si la direction est soit HAUT soit BAS on teste si on peut se deplacer de 2 dans cette
	   direction. Si on peut on le fait. (normal)

	   Si la direction est soit GAUCHE soit DROITE : 
	   		- si c'est une colonne impaire on teste si on peut se deplacer de 2. Si on peut on
	   		 le fait. (normal)
	   		- si c'est une colonne impaire et qu'on ne peut pas de deplacer de 2, on teste si
	   		  on peut se deplacer de 1. Si on peut on le fait. (on va sur une porte decalee ou
	   		  sur un mur decale)
	   		- sinon on teste si on peut se deplacer de 1. Si on peut on le fait. (on revient 
	   	 	  sur le sol, normal)
	*/

	if((direction == HAUT || direction == BAS) &&
		estPossibleDeplacementJoueur(direction, position, CAS_NORMAL))
	{
		position[LIG] += recupererDirectionJoueurCasNormal(direction, LIG);
		position[COL] += recupererDirectionJoueurCasNormal(direction, COL);
	}
	else if (direction == GAUCHE || direction == DROITE)
	{
		if(((position[COL] & 1) == 0) &&
		   estPossibleDeplacementJoueur(direction, position, CAS_NORMAL) &&
		   estPossibleDeplacementJoueur(direction, position, CAS_SPECIAL))
		{
			position[LIG] += recupererDirectionJoueurCasNormal(direction, LIG);
			position[COL] += recupererDirectionJoueurCasNormal(direction, COL);
		}
		else if(estPossibleDeplacementJoueur(direction, position, CAS_SPECIAL))
		{
			position[LIG] += recupererDirectionJoueurCasNormal(direction, LIG);
			position[COL] += recupererDirectionJoueurCasSpecial(direction);
		}
	}
}
