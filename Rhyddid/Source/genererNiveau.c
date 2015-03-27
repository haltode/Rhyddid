#include <stdio.h>

#include "genererNiveau.h"
#include "niveau.h"
#include "personnage.h"
#include "deplacement.h"
#include "coffre.h"
#include "ennemi.h"
#include "caverne.h"

void bloquerAccesIndispensableLigneNouveauNiveau(const unsigned int indexSalle, 
	unsigned int indexLig, const unsigned int indexCol, const unsigned int longueurMax)
{
	compteur indexLongueur;

	for(indexLongueur = 0; indexLongueur < longueurMax; ++indexLongueur)
	{
		niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = 'N';
		++indexLig;
	}
}

void bloquerAccesIndispensableColonneNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, unsigned int indexCol, const unsigned int longueurMax)
{
	compteur indexLongueur;

	for(indexLongueur = 0; indexLongueur < longueurMax; ++indexLongueur)
	{
		niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = 'N';
		++indexCol;
	}
}

void bloquerAccesIndispensableNouveauNiveau(const unsigned int indexSalle)
{
	bloquerAccesIndispensableLigneNouveauNiveau(indexSalle, 1, 38, 11);
	bloquerAccesIndispensableLigneNouveauNiveau(indexSalle, 27, 38, 12);

	bloquerAccesIndispensableColonneNouveauNiveau(indexSalle, 19, 1, 26);
	bloquerAccesIndispensableColonneNouveauNiveau(indexSalle, 19, 50, 29);
}

void remplirSalleNouveauNiveau(void)
{
	compteur indexSalle;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		FILE *salle;
		unsigned int formeSalleAleatoire;
		char chemin[TAILLE_MAX];
		compteur indexLig;

		formeSalleAleatoire = hasard(1, NB_FORME_SALLE);

		sprintf(chemin, "Modele_Salle/Salle_%d/forme_%d.txt", indexSalle + 1, formeSalleAleatoire);

		salle = ouvrirFichier(chemin, "r",
		"fichier \"salle\", fonction \"remplirSalleNouveauNiveau\"");

		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			lire(salle, niveauActuel.salle[indexSalle].mapSalle[indexLig]);

		fermerFichier(salle,
		"fichier \"salle\", fonction \"remplirSalleNouveauNiveau\"");

		bloquerAccesIndispensableNouveauNiveau(indexSalle);
	}
}

void tirerCoordonneeAleatoireNiveau(const unsigned int indexSalle, unsigned int *ligne,
	unsigned int *colonne, const unsigned int estCaverne)
{
	char caractere;

	do
	{
		*ligne = hasard(0, LARGUEUR_SALLE - 1);
		*colonne = hasard(0, LONGUEUR_SALLE - 1);

		if(estCaverne)
			caractere = niveauActuel.salle[indexSalle].caverne.mapSalle[*ligne][*colonne];
		else
			caractere = niveauActuel.salle[indexSalle].mapSalle[*ligne][*colonne];
	
	} while(caractere != ' ' || (*colonne & 1) == 1);
}

void tirerNombreCoffreEtEnnemiNouveauNiveau(void)
{
	compteur indexSalle;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		niveauActuel.salle[indexSalle].nbCoffre = hasard(NB_COFFRE_MIN, NB_COFFRE_MAX);
		niveauActuel.salle[indexSalle].nbEnnemi = hasard(NB_ENNEMI_MIN, NB_ENNEMI_MAX);
	}
}

void placerCoffreEtEnnemiNouveauNiveau(void)
{
	compteur indexSalle;

	tirerNombreCoffreEtEnnemiNouveauNiveau();

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		placerCoffreAleatoireNouveauNiveau(indexSalle, niveauActuel.salle[indexSalle].nbCoffre, NON_CAVERNE);
		placerEnnemiAleatoireNouveauNiveau(indexSalle, niveauActuel.salle[indexSalle].nbEnnemi, NON_CAVERNE);
	}
}

unsigned int testerPlacementObstacleNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle, unsigned int indexLig, unsigned int indexCol,
	const unsigned int directionObstacle)
{
	compteur indexLongueur;

	for(indexLongueur = 0; indexLongueur < longueurObstacle; ++indexLongueur)
	{
		if(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] != ' ')
			return 0;

		indexLig += recupererDirectionCasNormal(directionObstacle, LIG);
		indexCol += recupererDirectionCasNormal(directionObstacle, COL);
	}

	return 1;
}

void placerObstacleEmplacementNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, const unsigned int indexCol,
	const unsigned int directionObstacle)
{
	static const char caractereObstacle[NB_DIRECTION] =
	{
		'|',
		'|',
		'-',
		'-'
	};

	niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = caractereObstacle[directionObstacle];
}

void placerObstacleIndividuelNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle)
{
	unsigned int indexLig, indexCol, direction;
	compteur indexLongueur;

	do
	{	
		do
		{
			indexLig = hasard(0, LARGUEUR_SALLE - 1);
			indexCol = hasard(0, LONGUEUR_SALLE - 1);

		} while(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] != ' ');
		
		direction = hasard(HAUT, DROITE);

	} while(testerPlacementObstacleNouveauNiveau(indexSalle, longueurObstacle, indexLig, indexCol, direction) != 1);

	for(indexLongueur = 0; indexLongueur < longueurObstacle; ++indexLongueur)
	{
		placerObstacleEmplacementNouveauNiveau(indexSalle, indexLig, indexCol, direction);

		indexLig += recupererDirectionCasNormal(direction, LIG);
		indexCol += recupererDirectionCasNormal(direction, COL);
	}
}

void placerObstacleNouveauNiveau(void)
{
	compteur indexSalle;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		unsigned int nbObstacle;
		compteur indexObstacle;

		nbObstacle = hasard(NB_OBSTACLE_MIN, NB_OBSTACLE_MAX);

		for(indexObstacle = 0; indexObstacle < nbObstacle; ++indexObstacle)
		{
			unsigned int longueurObstacle;

			longueurObstacle = hasard(NB_LONGUEUR_OBSTACLE_MIN, NB_LONGUEUR_OBSTACLE_MAX);
			placerObstacleIndividuelNouveauNiveau(indexSalle, longueurObstacle);
		}
	}
}

void genererNiveau(void)
{
	initialiserPositionJoueurNouveauNiveau();
	remplirSalleNouveauNiveau();
	placerCaverneNouveauNiveau();
	placerObstacleNouveauNiveau();
	placerCoffreEtEnnemiNouveauNiveau();
	initialiserEmplacementCleEnnemi();
}
