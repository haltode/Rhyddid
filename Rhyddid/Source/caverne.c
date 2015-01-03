#include <stdio.h>

#include "caverne.h"
#include "fonctionsUtiles.h"
#include "niveau.h"
#include "deplacement.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"
#include "coffre.h"

/* Place une caverne sur le nouveau niveau */
void placerCaverneNouveauNiveau(void)
{
	/* On determine si le joueur a 1 chance sur CHANCE_MAX_CAVERNE de faire generer une caverne
	sur le niveau */

	/* Si il a la chance */
	if(tirerChance(1, CHANCE_MAX_CAVERNE))
	{
		unsigned int indexSalleCaverne;

		/* On choisit l'index de la salle contenant la caverne */
		indexSalleCaverne = hasard(0, NB_SALLE_NIVEAU - 1);

		/* On initialise la variable salleCaverne avec l'index de la caverne choisit */
		niveauActuel.salleCaverne = indexSalleCaverne;

		/* On genere la caverne dans la salle indexSalleCaverne */
		genererCaverne(indexSalleCaverne);
	}
	/* Sinon */
	else
		/* On initialise la variable salleCaverne a -1 pour indiquer qu'il n'y a pas de caverne
		sur le niveau */
		niveauActuel.salleCaverne = -1;
}

/* Teste le placement d'une caverne sur le nouveau niveau, retourne 1 si on peut placer la 
caverne a l'emplacement indique par ligne et colonne et 0 sinon */
unsigned int testerPlacementCaverneNouveauNiveau(
	const unsigned int indexSalle, const unsigned int ligneCaverne, 
	const unsigned int colonneCaverne)
{
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la caverne */
	for(indexLig = 0; indexLig < LONGUEUR_CAVERNE; ++indexLig)
	{
		/* Pour chaque colonne de la caverne */
		for(indexCol = 0; indexCol < LARGUEUR_CAVERNE; ++indexCol)
		{
			/* Si le caractere actuel est different de ' ', alors on ne peut pas placer la 
			caverne, on retoure donc 0 */
			if(niveauActuel.salle[indexSalle].mapSalle[ligneCaverne + indexLig][colonneCaverne + indexCol] != ' ')
				return 0;
		}
	}

	/* On retourne 1 puisque l'emplacement est libre pour la caverne */
	return 1;
}

/* Permet de determiner une position de caverne dans la salle indexSalle au hasard */
void determinerPositionCaverne(const unsigned int indexSalle)
{
	unsigned int ligCaverne, colCaverne;

	/* Faire ... */
	do
	{
		/* Faire ... */
		do
		{
			/* Tirer coordonnes (ligne et colonne) au hasard pour la caverne */
			ligCaverne = hasard(0, LARGUEUR_SALLE - 1);
			colCaverne = hasard(0, LONGUEUR_SALLE - 1);

		/* Tant que le caractere a l'emplacement ligCaverne colCaverne est different de ' ' 
		ou que la colonne est impaire (permet au joueur de pouvoir toujours entrer dans la 
		caverne, puisqu'il est toujours sur une colonne paire sauf cas exceptionnel) */
		} while(niveauActuel.salle[indexSalle].mapSalle[ligCaverne][colCaverne] != ' ' ||
			(colCaverne & 1) != 0);
		/* L'expression colCaverne & 1 != 0 est vraie lorsque colCaverne est impaire */

	/* Tant que l'emplacement choisis aleatoirement de la caverne n'est pas libre */
	} while(testerPlacementCaverneNouveauNiveau(indexSalle, ligCaverne, colCaverne) != 1);

	/* On choisit la direction de l'entree de la caverne (Haut, Bas, Gauche, Droite) au 
	hasard */
	niveauActuel.salle[indexSalle].caverne.directionEntree = hasard(HAUT, DROITE);

	/* On sauvegarde l'emplacement de la ligne et de la colonne de la caverne */
	niveauActuel.salle[indexSalle].caverne.ligDebut = ligCaverne;
	niveauActuel.salle[indexSalle].caverne.colDebut = colCaverne;
}

/* Place une caverne sur la salle indexSalle */
void placerCaverne(const unsigned int indexSalle)
{
	/* Tous les differents modeles de cavernes (4 entrees possible : Haut, Bas, Gauche, Droite) 
	Le E represente l'entree principale et les C reprensente l'interieur de la caverne. Tout le
	reste represente les murs (|, /, \, `, ,, ., _, -, ') */

	/* Modele de caverne avec entree en Haut */
	static const char *modeleCaverneEntreeHaut[LONGUEUR_CAVERNE] =
	{
		"  _|E|_  ",
		"`/CCCCC\\'",
		" |CCCCC| ",
		" |CCCCC| ",
		",\\_____/. "
	};
	/* Modele de caverne avec entree en Bas */
	static const char *modeleCaverneEntreeBas[LONGUEUR_CAVERNE] =
	{
		"  _____  ",
		"`/CCCCC\\'",
		" |CCCCC| ",
		" |CCCCC| ",
		",\\-|E|-/."
	};
	/* Modele de caverne avec entree en Gauche */
	static const char *modeleCaverneEntreeGauche[LONGUEUR_CAVERNE] =
	{
		" `/----\\'",
		"---CCCCC| ",
		"ECCCCCCC| ",
		"---CCCCC| ",
		" ,\\____/."
	};
	/* Modele de caverne avec entree en Droite */
	static const char *modeleCaverneEntreeDroite[LONGUEUR_CAVERNE] =
	{
		"'/----\\` ",
		"|CCCCC---",
		"|CCCCCCCE",
		"|CCCCC---",
		",\\____/. "
	};
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la caverne */
	for(indexLig = 0; indexLig < LONGUEUR_CAVERNE; ++indexLig)
	{
		/* Pour chaque colonne de la caverne */
		for(indexCol = 0; indexCol < LARGUEUR_CAVERNE; ++indexCol)
		{
			unsigned int ligneCaverne, colonneCaverne;
			char caractereModeleCaverne;

			/* On recupere les coordonnes de l'entree de la caverne (ligne et colonne) */
			ligneCaverne = niveauActuel.salle[indexSalle].caverne.ligDebut;
			colonneCaverne = niveauActuel.salle[indexSalle].caverne.colDebut;

			/* Pour chaque direction possible de la caverne, on recupere le caractere modele
			de la caverne */
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

			/* On copie ce caractere modele */
			niveauActuel.salle[indexSalle].mapSalle[ligneCaverne + indexLig][colonneCaverne + indexCol] = caractereModeleCaverne;
		}
	}
}

/* Permet de bloquer l'ajout de murs ou autre devant l'entree */
void bloquerAccesIndispensableEntreeCaverne(const unsigned int indexSalle)
{
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la salle */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		/* Pour chaque colonne de la salle */
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* Si le caractere actuel est l'entree d'une caverne */
			if(niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] == 'E')
			{
				/* On bloque l'ajout de murs ou autre en placant un N devant l'entree */
				unsigned int ligEntree, colEntree;

				ligEntree = indexLig + positionSortieCaverne(niveauActuel.salle[indexSalle].caverne.directionEntree, LIG);
				colEntree = indexCol + positionSortieCaverne(niveauActuel.salle[indexSalle].caverne.directionEntree, COL);

				niveauActuel.salle[indexSalle].mapSalle[ligEntree][colEntree] = 'N';
			}
		}
	}
}

/* Permet de generer la salle d'une caverne (interieur de la caverne) */
void genererSalleCaverne(const unsigned int indexSalle)
{
	/* Base contenant le nom des fichiers pour la salle de la caverne */
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

	/* On recupere la direction de l'entree de la caverne */
	directionCaverne = niveauActuel.salle[indexSalle].caverne.directionEntree;

	/* On ouvre le fichier correspondant a la direction de l'entree */
	fichierSalleCaverne = ouvrirFichier(nomFichierSalleCaverne[directionCaverne], "r",
	"fichier \"modele_caverne.txt\", fonction \"genererSalleCaverne\"");

	/* On lit chaque ligne du fichier pour creer la salle de la caverne */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
		lire(fichierSalleCaverne, niveauActuel.salle[indexSalle].caverne.mapSalle[indexLig]);

	/* On ferme le fichier correspondant a la direction de l'entree */
	fermerFichier(fichierSalleCaverne,
	"fichier \"modele_caverne.txt\", fonction \"genererSalleCaverne\"");

	/* On bloque les ajouts de murs ou autres devant la caverne pour permettre au joueur de 
	toujours avec un acces a la caverne */
	bloquerAccesIndispensableEntreeCaverne(indexSalle);
}

/* Permet de generer le contenu de la caverne (coffre, ennemi) */
void genererContenuCaverne(const unsigned int indexSalle)
{
	/* On cree l'interieur de la caverne (la salle) */
	genererSalleCaverne(indexSalle);

	/* On choisit si la caverne va contenir des ennemis ou des cofffres*/

	/* Si c'est des ennemis */
	if(tirerChance(1, CHANCE_MAX_CAVERNE_PIEGE))
	{
		/* On place les ennemis dans la salle de la caverne */
		placerEnnemiAleatoireNouveauNiveau(indexSalle, NB_ENNEMI_MAX_CAVERNE, CAVERNE);
		/* On indique le nombre d'ennemis dans la salle de la caverne */
		niveauActuel.salle[indexSalle].caverne.nbEnnemi = NB_ENNEMI_MAX_CAVERNE;
	}
	/* Sinon c'est des coffres*/
	else
	{
		/* On place les coffres dans la salle de la caverne */
		placerCoffreAleatoireNouveauNiveau(indexSalle, NB_COFFRE_MAX_CAVERNE, CAVERNE);
		/* On indique que la salle ne contient pas d'ennemis */
		niveauActuel.salle[indexSalle].caverne.nbEnnemi = 0;
	}
}

/* Permet de generer une caverne dans la salle indexSalle */
void genererCaverne(const unsigned int indexSalle)
{
	/* On determine la position de la caverne */
	determinerPositionCaverne(indexSalle);
	/* On place la caverne */
	placerCaverne(indexSalle);
	/* On remplit la caverne */
	genererContenuCaverne(indexSalle);
}

/* Permet d'entrer dans une caverne */
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
	/* Base contenant l'emplacement de l'entree de la salle de la caverne en fonction de la
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

	/* On demande si le joueur veut rentrer dans la caverne */
	choixJoueur = demanderConfirmation("Etes-vous sur de vouloir rentrer dans cette caverne ? (0/1)", PAS_SEPARATION);
	/* On recupere la direction de l'entree de la caverne */
	directionCaverne = niveauActuel.salle[niveauActuel.salleActuelle].caverne.directionEntree;

	/* Si le joueur ne veut pas rentrer dans la caverne */
	if(choixJoueur == NON)
	{
		/* On place le joueur sur l'entree de la caverne */
		personnage.positionJoueur[LIG] += positionEntreeCaverne[directionCaverne][LIG];
		personnage.positionJoueur[COL] += positionEntreeCaverne[directionCaverne][COL];

		/* On quitte la fonction */
		return ;
	}

	/* Sinon le joueur veut entrer dans la caverne */

	/* On indique que le joueur est dans la caverne */
	niveauActuel.estDansCaverne = 1;

	/* On place le joueur a l'entree de la salle de la caverne */
	personnage.positionJoueur[LIG] = entreeCaverneDirection[directionCaverne][LIG];
	personnage.positionJoueur[COL] = entreeCaverneDirection[directionCaverne][COL];
}

/* Permet de rechercher l'entree d'une caverne et de placer le resultat dans ligneEntreeCaverne 
et colonneEntreeCaverne */
void rechercherEntreeCaverne(unsigned int *ligneEntreeCaverne, 
	unsigned int *colonneEntreeCaverne)
{
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la salle */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		/* Pour chaque colonne de la salle */
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* Si le caractere actuel est l'entree d'une caverne */
			if(niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[indexLig][indexCol] == 'E')
			{
				/* On sauvegarde les coordonnes de l'entree de la caverne */
				*ligneEntreeCaverne = indexLig;
				*colonneEntreeCaverne = indexCol;

				/* On quitte la fonction */
				return ;
			}
		}
	}
}

/* Retourne la position de sortie d'une caverne en fonction de la direction et de la dimension */
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

	/* On retourne la position correspondante */
	return basePositionSortieCaverne[direction][dimension];
}

/* Permet de sortir de la caverne */
void sortirCaverne(void)
{
	unsigned int directionCaverne;

	directionCaverne = niveauActuel.salle[niveauActuel.salleActuelle].caverne.directionEntree;

	effacer();
	titre("Caverne", VERT);

	appuyezEntree("Appuyez sur ENTREE pour sortir de la caverne...");

	/* On indique que le joueur n'est plus dans une caverne */
	niveauActuel.estDansCaverne = 0;

	/* On recherche l'entree de la caverne */
	rechercherEntreeCaverne(&personnage.positionJoueur[LIG], &personnage.positionJoueur[COL]);

	/* Puis on place le joueur a l'emplacement de l'entree de la caverne */
	personnage.positionJoueur[LIG] += positionSortieCaverne(directionCaverne, LIG);
	personnage.positionJoueur[COL] += positionSortieCaverne(directionCaverne, COL);
}
