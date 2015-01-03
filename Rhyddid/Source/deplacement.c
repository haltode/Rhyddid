#include <stdio.h>
#include <string.h>

#include "deplacement.h"
#include "niveau.h"
#include "ennemi.h"
#include "personnage.h"

/* Renvoie la direction correspondante a la touche donne en parametre */
unsigned int recupererDirectionTouche(const char touche)
{
	/* On teste chaque cas possible de touche et on retourne la direction correspondante */
	switch(touche)
	{
		/* Haut */
		case 'z': case 'Z':
			return HAUT;
		break;
		/* Bas */
		case 's': case 'S':
			return BAS;
		break;
		/* Gauche */
		case 'q': case 'Q':
			return GAUCHE;
		break;
		/* Droite */
		case 'd': case 'D':
			return DROITE;
		break;
	}

	return ERREUR_DIRECTION;
}

/* Renvoie le deplacement correspondant a direction dimension dans le cas normal */
int recupererDirectionCasNormal(const unsigned int direction,
	const unsigned int dimension)
{
	/* Tableau contenant pour chaque direction les deplacements necessaires sur la ligne et sur 
	la colonne */
	static const int baseDirection[NB_DIRECTION][2] =
	{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	/* On retourne le deplacement correspondant */
	return baseDirection[direction][dimension];
}

/* Renvoie le deplacement correspondant a direction dimension dans le cas normal pour le joueur */
int recupererDirectionJoueurCasNormal(const unsigned int direction, 
	const unsigned int dimension)
{
	/* Tableau contenant pour chaque direction les deplacements necessaires pour deplacer le joueur
	ici Gauche et Droite deplace de 2 le joueur car sur les cotes le joueur parcourt 2 cases sinon
	le niveau serait trop grand */
	static const int baseDirectionJoueurCasNormal[NB_DIRECTION][2] =
	{
		{-1, 0}, /* Coordonnees a ajouter sur lig et col respectivement pour aller en Haut */
		{1, 0}, /* Coordonnees a ajouter sur lig et col respectivement pour aller en Bas */
		{0, -2}, /* Coordonnees a ajouter sur lig et col respectivement pour aller a Gauche */
		{0, 2} /* Coordonnees a ajouter sur lig et col respectivement pour aller a Droite */
	};

	/* On retourne le deplacement correspondant */
	return baseDirectionJoueurCasNormal[direction][dimension];
}

/* Renvoie le deplacement correspondant a direction dans le cas special pour le joueur */
int recupererDirectionJoueurCasSpecial(const unsigned int direction)
{
	/* Tableau contenant pour chaque direction les deplacements necessaires pour deplacer le joueur
	ici Gauche et Droite deplace de 1 le joueur car dans certains cas special on deplace le joueur
	de 1 au lieu de 2 */
	static const int baseDirectionJoueurCasSpecial[NB_DIRECTION] =
	{
		0,
		0,
		-1,
		1
	};

	/* On retourne le deplacement correspondant */
	return baseDirectionJoueurCasSpecial[direction];
}

/* Renvoie 1 si les coordonnes donnees sont en dehors de la map et 0 sinon */
unsigned int estDehorsMap(const int coordonnee, const unsigned int longueurMax)
{
	/* On teste si la position est inferieur a 0 ou superieur a la longueurMax */

	/* On renvoie 1 si le joueur est en dehors de la map et 0 sinon */
	return coordonnee < 0 || coordonnee > longueurMax;
}

/* Renvoie 1 si la case lig col est un mur et 0 sinon */
unsigned int estMur(const unsigned int lig, const unsigned int col)
{
	static const char baseCaractereMur[] = "#|-_\\/`,\'";
	char caractere;

	/* On recupere le caractere a la case lig col */
	if(niveauActuel.estDansCaverne)
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	/* On renvoie 1 si le caractere est un mur et 0 sinon */
	return strchr(baseCaractereMur, caractere) != NULL;
}

/* Retourne 1 si la case lig col est un ennemi et 0 sinon */
unsigned int estEnnemi(const unsigned int lig, const unsigned int col)
{
	/* On regarde si il y a un ennemi a cette position */

	/* On renvoie 1 si la case lig col est un ennemi et 0 sinon */
	return trouverIndexEnnemi(lig, col) != -1;
}

/* Renvoie 1 si la case lig col est un joueur et 0 sinon */
unsigned int estJoueur(const unsigned int lig, const unsigned int col)
{
	/* On regarde si les coordonnes (lig, col) correspondent aux coordonnes du joueur */

	/* On renvoie 1 si la case lig col est le joueur et 0 sinon */
	return lig == personnage.positionJoueur[LIG] && col == personnage.positionJoueur[COL];
}

/* Renvoie 1 si la case lig col est un endroit impossible a acceder et 0 sinon */
unsigned int estEndroitImpossible(const unsigned int lig, const unsigned int col)
{
	char caractere;

	/* On recupere le caractere a la case lig col */
	if(niveauActuel.estDansCaverne)
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractere = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	/* On teste si le caractere est un endroit impossible a acceder (., ennemi, joueur) */

	/* On renvoie 1 si le caractere est un '.' OU que la case est un ennemi (non mort) OU que la case
	est un joueur et 0 sinon */
	return caractere == '.' || (estEnnemi(lig, col) && !estMortEnnemi(trouverIndexEnnemi(lig, col))) ||
	  	estJoueur(lig, col);
}

/* Retourne 1 si le joueur se trouvant a la case lig col est une case valide et 0 sinon */
unsigned int testerDeplacementJoueur(const unsigned int lig, const unsigned int col)
{
	/* On teste si le deplacement fait que le joueur est en dehors de la map (ligne et colonne) OU 
	que la case est un mur OU que la case est un endroit impossible a acceder */

	/* On renvoie 1 si le joueur n'est pas en dehors de la map (ligne) OU que le joueur n'est pas en
	dehors de la map (colonne) OU que la case n'est pas un mur OU que la case n'est pas un 
	endroit impossible et 0 sinon */
	return 	!(estDehorsMap(lig, LARGUEUR_SALLE) 	|| 
	   	estDehorsMap(col, LONGUEUR_SALLE) 	||
	 	estMur(lig, col) 				||
	   	estEndroitImpossible(lig, col));
}

/* Deplace le joueur et renvoie 1 si la case ou se trouve le joueur apres le deplacement est 
valide et 0 sinon */
unsigned int estPossibleDeplacementJoueur(const unsigned int direction, 
	const unsigned int position[2], const unsigned int nbColonneCote)
{
	unsigned int testLig, testCol;

	/* On deplace le joueur */
	testLig = position[LIG] + recupererDirectionJoueurCasNormal(direction, LIG);

	/* Si on deplace le joueur de 2 sur le cote (cas normal) */
	if(nbColonneCote == CAS_NORMAL)
		testCol = position[COL] + recupererDirectionJoueurCasNormal(direction, COL);
	/* Sinon on deplace le joueur de 1 sur le cote (cas special) */
	else
		testCol = position[COL] + recupererDirectionJoueurCasSpecial(direction);

	/* On renvoie 1 si la case est valide et 0 sinon */
	return testerDeplacementJoueur(testLig, testCol);
}

/* Deplace le joueur dans la direction donnee en parametre apres avoir tester si c'est 
possible */
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
