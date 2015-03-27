#include <stdio.h>

#include "caverne.h"
#include "fonctionsUtiles.h"
#include "niveau.h"
#include "deplacement.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"
#include "coffre.h"

void placerCaverneNouveauNiveau(void)
{
	/* On determine si le joueur a 1 chance sur CHANCE_MAX_CAVERNE de faire generer une caverne
	sur le niveau */

	if(tirerChance(1, CHANCE_MAX_CAVERNE))
	{
		unsigned int indexSalleCaverne;

		indexSalleCaverne = hasard(0, NB_SALLE_NIVEAU - 1);
		niveauActuel.salleCaverne = indexSalleCaverne;

		genererCaverne(indexSalleCaverne);
	}
	else
		niveauActuel.salleCaverne = -1;
}

unsigned int testerPlacementCaverneNouveauNiveau(
	const unsigned int indexSalle, const unsigned int ligneCaverne, 
	const unsigned int colonneCaverne)
{
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LONGUEUR_CAVERNE; ++indexLig)
		for(indexCol = 0; indexCol < LARGUEUR_CAVERNE; ++indexCol)
			if(niveauActuel.salle[indexSalle].mapSalle[ligneCaverne + indexLig][colonneCaverne + indexCol] != ' ')
				return 0;

	return 1;
}

void determinerPositionCaverne(const unsigned int indexSalle)
{
	unsigned int ligCaverne, colCaverne;

	do
	{
		do
		{
			ligCaverne = hasard(0, LARGUEUR_SALLE - 1);
			colCaverne = hasard(0, LONGUEUR_SALLE - 1);

		} while(niveauActuel.salle[indexSalle].mapSalle[ligCaverne][colCaverne] != ' ' ||
			(colCaverne & 1) != 0);

	} while(testerPlacementCaverneNouveauNiveau(indexSalle, ligCaverne, colCaverne) != 1);

	niveauActuel.salle[indexSalle].caverne.directionEntree = hasard(HAUT, DROITE);

	niveauActuel.salle[indexSalle].caverne.ligDebut = ligCaverne;
	niveauActuel.salle[indexSalle].caverne.colDebut = colCaverne;
}

void placerCaverne(const unsigned int indexSalle)
{
	/* Tous les differents modeles de cavernes (4 entrees possible : Haut, Bas, Gauche, Droite) 
	Le E represente l'entree principale et les C represente l'interieur de la caverne. Tout le
	reste represente les murs (|, /, \, `, ,, ., _, -, ') */

	static const char *modeleCaverneEntreeHaut[LONGUEUR_CAVERNE] =
	{
		"  _|E|_  ",
		"`/CCCCC\\'",
		" |CCCCC| ",
		" |CCCCC| ",
		",\\_____/. "
	};
	static const char *modeleCaverneEntreeBas[LONGUEUR_CAVERNE] =
	{
		"  _____  ",
		"`/CCCCC\\'",
		" |CCCCC| ",
		" |CCCCC| ",
		",\\-|E|-/."
	};
	static const char *modeleCaverneEntreeGauche[LONGUEUR_CAVERNE] =
	{
		" `/----\\'",
		"---CCCCC| ",
		"ECCCCCCC| ",
		"---CCCCC| ",
		" ,\\____/."
	};
	static const char *modeleCaverneEntreeDroite[LONGUEUR_CAVERNE] =
	{
		"'/----\\` ",
		"|CCCCC---",
		"|CCCCCCCE",
		"|CCCCC---",
		",\\____/. "
	};
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LONGUEUR_CAVERNE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LARGUEUR_CAVERNE; ++indexCol)
		{
			unsigned int ligneCaverne, colonneCaverne;
			char caractereModeleCaverne;

			ligneCaverne = niveauActuel.salle[indexSalle].caverne.ligDebut;
			colonneCaverne = niveauActuel.salle[indexSalle].caverne.colDebut;

			switch(niveauActuel.salle[indexSalle].caverne.directionEntree)
			{
				case HAUT:
					caractereModeleCaverne = modeleCaverneEntreeHaut[indexLig][indexCol];
				break;

				case BAS:
					caractereModeleCaverne = modeleCaverneEntreeBas[indexLig][indexCol];
				break;

				case GAUCHE:
					caractereModeleCaverne = modeleCaverneEntreeGauche[indexLig][indexCol];
				break;

				case DROITE:
					caractereModeleCaverne = modeleCaverneEntreeDroite[indexLig][indexCol];
				break;
			}

			niveauActuel.salle[indexSalle].mapSalle[ligneCaverne + indexLig][colonneCaverne + indexCol] = caractereModeleCaverne;
		}
	}
}

void bloquerAccesIndispensableEntreeCaverne(const unsigned int indexSalle)
{
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			if(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] == 'E')
			{
				unsigned int ligEntree, colEntree;

				ligEntree = indexLig + positionSortieCaverne(niveauActuel.salle[indexSalle].caverne.directionEntree, LIG);
				colEntree = indexCol + positionSortieCaverne(niveauActuel.salle[indexSalle].caverne.directionEntree, COL);

				niveauActuel.salle[indexSalle].mapSalle[ligEntree][colEntree] = 'N';
			}
		}
	}
}

void genererSalleCaverne(const unsigned int indexSalle)
{
	static const char *nomFichierSalleCaverne[NB_DIRECTION] =
	{
		"Caverne/Modele_Caverne_Entree_Haut.txt",
		"Caverne/Modele_Caverne_Entree_Bas.txt",
		"Caverne/Modele_Caverne_Entree_Gauche.txt",
		"Caverne/Modele_Caverne_Entree_Droite.txt"
	};
	FILE *fichierSalleCaverne;
	unsigned int directionCaverne;
	compteur indexLig;

	directionCaverne = niveauActuel.salle[indexSalle].caverne.directionEntree;

	fichierSalleCaverne = ouvrirFichier(nomFichierSalleCaverne[directionCaverne], "r",
	"fichier \"modele_caverne.txt\", fonction \"genererSalleCaverne\"");

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
		lire(fichierSalleCaverne, niveauActuel.salle[indexSalle].caverne.mapSalle[indexLig]);

	fermerFichier(fichierSalleCaverne,
	"fichier \"modele_caverne.txt\", fonction \"genererSalleCaverne\"");

	bloquerAccesIndispensableEntreeCaverne(indexSalle);
}

void genererContenuCaverne(const unsigned int indexSalle)
{
	genererSalleCaverne(indexSalle);

	if(tirerChance(1, CHANCE_MAX_CAVERNE_PIEGE))
	{
		placerEnnemiAleatoireNouveauNiveau(indexSalle, NB_ENNEMI_MAX_CAVERNE, CAVERNE);
		niveauActuel.salle[indexSalle].caverne.nbEnnemi = NB_ENNEMI_MAX_CAVERNE;
	}
	else
	{
		placerCoffreAleatoireNouveauNiveau(indexSalle, NB_COFFRE_MAX_CAVERNE, CAVERNE);
		niveauActuel.salle[indexSalle].caverne.nbEnnemi = 0;
	}
}

void genererCaverne(const unsigned int indexSalle)
{
	determinerPositionCaverne(indexSalle);
	placerCaverne(indexSalle);
	genererContenuCaverne(indexSalle);
}

void entrerCaverne(void)
{
	/* Contient les positions de l'entree par rapport au joueur */
	static const int positionEntreeCaverne[NB_DIRECTION][2] = 
	{
		{-1, 0},
		{1, 0},
		{0, -2},
		{0, 2}
	};
	/* Contient l'emplacement de l'entree de la salle de la caverne en fonction de la
	direction de l'entree de la caverne */
	static const unsigned int entreeCaverneDirection[NB_DIRECTION][2] =
	{
		{0, 38},
		{39, 38},
		{19, 0},
		{19, 79}
	};
	unsigned int choixJoueur;
	unsigned int directionCaverne;

	effacer();
	titre("Caverne", VERT);

	choixJoueur = demanderConfirmation("Etes-vous sur de vouloir rentrer dans cette caverne ? (0/1)", PAS_SEPARATION);
	directionCaverne = niveauActuel.salle[niveauActuel.salleActuelle].caverne.directionEntree;

	if(choixJoueur == NON)
	{
		personnage.positionJoueur[LIG] += positionEntreeCaverne[directionCaverne][LIG];
		personnage.positionJoueur[COL] += positionEntreeCaverne[directionCaverne][COL];

		return ;
	}

	niveauActuel.estDansCaverne = 1;

	personnage.positionJoueur[LIG] = entreeCaverneDirection[directionCaverne][LIG];
	personnage.positionJoueur[COL] = entreeCaverneDirection[directionCaverne][COL];
}

void rechercherEntreeCaverne(unsigned int *ligneEntreeCaverne, 
	unsigned int *colonneEntreeCaverne)
{
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			if(niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[indexLig][indexCol] == 'E')
			{
				*ligneEntreeCaverne = indexLig;
				*colonneEntreeCaverne = indexCol;

				return ;
			}
		}
	}
}

int positionSortieCaverne(const unsigned int direction, const unsigned int dimension)
{
	/* Contient les positions de sortie par rapport au joueur */
	static const int basePositionSortieCaverne[NB_DIRECTION][2] = 
	{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	return basePositionSortieCaverne[direction][dimension];
}

void sortirCaverne(void)
{
	unsigned int directionCaverne;

	directionCaverne = niveauActuel.salle[niveauActuel.salleActuelle].caverne.directionEntree;

	effacer();
	titre("Caverne", VERT);

	appuyezEntree("Appuyez sur ENTREE pour sortir de la caverne...");

	niveauActuel.estDansCaverne = 0;

	rechercherEntreeCaverne(&personnage.positionJoueur[LIG], &personnage.positionJoueur[COL]);

	personnage.positionJoueur[LIG] += positionSortieCaverne(directionCaverne, LIG);
	personnage.positionJoueur[COL] += positionSortieCaverne(directionCaverne, COL);
}
