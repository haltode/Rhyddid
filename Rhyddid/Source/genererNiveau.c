#include <stdio.h>

#include "genererNiveau.h"
#include "niveau.h"
#include "personnage.h"
#include "deplacement.h"
#include "coffre.h"
#include "ennemi.h"
#include "caverne.h"

/* Permet de bloquer les acces indispensables commencant de indexLig indexCol et s'etendant de
longueurMax blocs (ligne) */
void bloquerAccesIndispensableLigneNouveauNiveau(const unsigned int indexSalle, 
	unsigned int indexLig, const unsigned int indexCol, const unsigned int longueurMax)
{
	compteur indexLongueur;

	/* Tant que on pas parcourut toute la longueur longueurMax */
	for(indexLongueur = 0; indexLongueur < longueurMax; ++indexLongueur)
	{
		/* On place un 'N' pour indiquer que l'on bloque l'acces ici */
		niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = 'N';

		/* On incremente la ligne de 1 */
		++indexLig;
	}
}

/* Permet de bloquer les acces indispensables commencant de indexLig indexCol et s'etendant de
longueurMax blocs (colonne) */
void bloquerAccesIndispensableColonneNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, unsigned int indexCol, const unsigned int longueurMax)
{
	compteur indexLongueur;

	/* Tant que on pas parcourut toute la longueur longueurMax */
	for(indexLongueur = 0; indexLongueur < longueurMax; ++indexLongueur)
	{
		/* On place un 'N' pour indiquer que l'on bloque l'acces ici */
		niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = 'N';

		/* On incremente la colonne de 1 */
		++indexCol;
	}
}

/* Permet de bloquer les acces indispensables au passage du joueur */
void bloquerAccesIndispensableNouveauNiveau(const unsigned int indexSalle)
{
	/* On bloque tous les acces (ligne et colonne devant les portes) */

	bloquerAccesIndispensableLigneNouveauNiveau(indexSalle, 1, 38, 11);
	bloquerAccesIndispensableLigneNouveauNiveau(indexSalle, 27, 38, 12);

	bloquerAccesIndispensableColonneNouveauNiveau(indexSalle, 19, 1, 26);
	bloquerAccesIndispensableColonneNouveauNiveau(indexSalle, 19, 50, 29);
}

/* Remplit la salle aleatoirement (forme et bloque les acces indispensables) */
void remplirSalleNouveauNiveau(void)
{
	compteur indexSalle;

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		FILE *salle;
		unsigned int formeSalleAleatoire;
		char chemin[TAILLE_MAX];
		compteur indexLig;

		/* On tire au hasard une forme de salle */
		formeSalleAleatoire = hasard(1, NB_FORME_SALLE);

		/* On cree le chemin vers la forme de la salle choisit aleatoirement */
		sprintf(chemin, "Modele_Salle/Salle_%d/forme_%d.txt", indexSalle + 1, formeSalleAleatoire);

		/* On ouvre le dit fichier */
		salle = ouvrirFichier(chemin, "r",
		"fichier \"salle\", fonction \"remplirSalleNouveauNiveau\"");

		/* Pour chaque ligne du fichier */
		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			/* On la copie dans le niveau */
			lire(salle, niveauActuel.salle[indexSalle].mapSalle[indexLig]);

		/* On ferme le dit fichier */
		fermerFichier(salle,
		"fichier \"salle\", fonction \"remplirSalleNouveauNiveau\"");

		/* On bloque les acces indispensables de la salle */
		bloquerAccesIndispensableNouveauNiveau(indexSalle);
	}
}

/* Tire des coordonnes aleatoirement dans la salle indexSalle du niveau et place le resultat
dans ligne et colonne */
void tirerCoordonneeAleatoireNiveau(const unsigned int indexSalle, unsigned int *ligne,
	unsigned int *colonne, const unsigned int estCaverne)
{
	char caractere;

	/* Faire */
	do
	{
		/* On tire des coordonnes aleatoirement */

		*ligne = hasard(0, LARGUEUR_SALLE - 1);
		*colonne = hasard(0, LONGUEUR_SALLE - 1);

		/* On recupere le caractere a cet endroit */
		if(estCaverne)
			caractere = niveauActuel.salle[indexSalle].caverne.mapSalle[*ligne][*colonne];
		else
			caractere = niveauActuel.salle[indexSalle].mapSalle[*ligne][*colonne];
	
	/* Tant que le caractere est different du sol OU que la colonne est impaire */
	} while(caractere != ' ' || (*colonne & 1) == 1);
}

/* Tire au hasard un nombre de coffre et d'ennemi pour les salles du nouveau niveau */
void tirerNombreCoffreEtEnnemiNouveauNiveau(void)
{
	compteur indexSalle;

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* On tire un nombre de coffre et d'ennemi aleatoirement */

		niveauActuel.salle[indexSalle].nbCoffre = hasard(NB_COFFRE_MIN, NB_COFFRE_MAX);
		niveauActuel.salle[indexSalle].nbEnnemi = hasard(NB_ENNEMI_MIN, NB_ENNEMI_MAX);
	}
}



/* Place les coffres et les ennemis des salles du niveau */
void placerCoffreEtEnnemiNouveauNiveau(void)
{
	compteur indexSalle;

	/* On determine le nombre de coffre et d'ennemi du niveau */
	tirerNombreCoffreEtEnnemiNouveauNiveau();

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* On place les coffres */	
		placerCoffreAleatoireNouveauNiveau(indexSalle, niveauActuel.salle[indexSalle].nbCoffre, NON_CAVERNE);
		/* On place les ennemis */
		placerEnnemiAleatoireNouveauNiveau(indexSalle, niveauActuel.salle[indexSalle].nbEnnemi, NON_CAVERNE);
	}
}

/* Renvoie 1 si l'obstacle a indexLig indexCol de direction directionObstacle et de longueur 
longueurObstacle est bien place et 0 sinon */
unsigned int testerPlacementObstacleNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle, unsigned int indexLig, unsigned int indexCol,
	const unsigned int directionObstacle)
{
	compteur indexLongueur;

	/* Pour chaque bloc de l'obstacle */
	for(indexLongueur = 0; indexLongueur < longueurObstacle; ++indexLongueur)
	{
		/* Si le bloc est different du sol (vide) */
		if(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] != ' ')
			/* On retourne 0 */
			return 0;

		/* On continue d'avancer dans la direction de l'obstacle */

		indexLig += recupererDirectionCasNormal(directionObstacle, LIG);
		indexCol += recupererDirectionCasNormal(directionObstacle, COL);
	}

	/* Sinon l'obstacle peut etre place la, on retourne 1 */
	return 1;
}

/* Place un obstacle a indexLig indexCol de direction directionObstacle */
void placerObstacleEmplacementNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, const unsigned int indexCol,
	const unsigned int directionObstacle)
{
	/* Contient les differents obstacles possibles pour chaque direction */
	static const char caractereObstacle[NB_DIRECTION] =
	{
		'|',
		'|',
		'-',
		'-'
	};

	/* On sauvegarde le caractere de l'obstacle a indexLig indexCol depuis une base de donnees
	caractereObstacle */
	niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = caractereObstacle[directionObstacle];
}

/* Place un obstacle de longueur longueurObstacle sur le nouveau niveau */
void placerObstacleIndividuelNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle)
{
	unsigned int indexLig, indexCol, direction;
	compteur indexLongueur;

	/* Faire */
	do
	{	
		/* Faire */
		do
		{
			/* On tire des coordonnes au hasard */

			indexLig = hasard(0, LARGUEUR_SALLE - 1);
			indexCol = hasard(0, LONGUEUR_SALLE - 1);

		/* Tant que le caractere indexLig indexCol n'est pas libre (sol) */
		} while(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] != ' ');
		
		/* On tire une direction au hasard */
		direction = hasard(HAUT, DROITE);

	/* Tant que l'obstacle n'est sur un emplacement libre */
	} while(testerPlacementObstacleNouveauNiveau(indexSalle, longueurObstacle, indexLig, indexCol, direction) != 1);

	/* Pour chaque bloc de l'obstacle */
	for(indexLongueur = 0; indexLongueur < longueurObstacle; ++indexLongueur)
	{
		/* On place l'obstacle */
		placerObstacleEmplacementNouveauNiveau(indexSalle, indexLig, indexCol, direction);

		/* On continue dans la direction de l'obstacle */

		indexLig += recupererDirectionCasNormal(direction, LIG);
		indexCol += recupererDirectionCasNormal(direction, COL);
	}
}

/* Place les obstacles sur un nouveau niveau */
void placerObstacleNouveauNiveau(void)
{
	compteur indexSalle;

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		unsigned int nbObstacle;
		compteur indexObstacle;

		/* On determine le nombre d'obstacle de la salle */
		nbObstacle = hasard(NB_OBSTACLE_MIN, NB_OBSTACLE_MAX);

		/* Pour chaque obstacle */
		for(indexObstacle = 0; indexObstacle < nbObstacle; ++indexObstacle)
		{
			unsigned int longueurObstacle;

			/* On tire une longueur d'obstacle aleatoirement */
			longueurObstacle = hasard(NB_LONGUEUR_OBSTACLE_MIN, NB_LONGUEUR_OBSTACLE_MAX);

			/* On place l'obstacle de taille longueurObstacle */
			placerObstacleIndividuelNouveauNiveau(indexSalle, longueurObstacle);
		}
	}
}

/* Genere un nouveau niveau */
void genererNiveau(void)
{
	/* On initialise la position du joueur sur le nouveau niveau */
	initialiserPositionJoueurNouveauNiveau();
	/* On remplit le nouveau niveau (forme des salles) */
	remplirSalleNouveauNiveau();
	/* On place la caverne sur le nouveau niveau */
	placerCaverneNouveauNiveau();
	/* On place les obstacles sur le nouveau niveau */
	placerObstacleNouveauNiveau();
	/* On place les coffres et les ennemis sur le nouveau niveau */
	placerCoffreEtEnnemiNouveauNiveau();

	/* On initialise l'emplacement de la cle de fin de niveau */
	initialiserEmplacementCleEnnemi();
}
