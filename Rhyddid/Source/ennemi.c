#include <stdio.h>

#include "ennemi.h"
#include "personnage.h"
#include "genererNiveau.h"
#include "deplacement.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "inventaire.h"
#include "niveau.h"

void tirerCompetenceEnnemieAleatoireNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexEnnemi, const unsigned int estCaverne)
{
	unsigned int niveauIA;

	niveauIA = determinerNiveauIAEnnemi(personnage.niveauActuel);

	if(estCaverne)
	{
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].nbVie = tirerVieAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].degatAttaque = tirerDegatAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].protection = tirerProtectionAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].porteeAttaque = tirerPorteeAleatoireNouveauEnnemi(niveauIA);

		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].estModeFocus = 0;
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].nbTourFocus = -1;
		niveauActuel.salle[indexSalle].caverne.ennemi[indexEnnemi].nbTourAttendreFocus = 0;
	}
	else
	{
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbVie = tirerVieAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].degatAttaque = tirerDegatAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].protection = tirerProtectionAleatoireNouveauEnnemi(niveauIA);
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].porteeAttaque = tirerPorteeAleatoireNouveauEnnemi(niveauIA);

		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].estModeFocus = 0;
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourFocus = -1;
		niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourAttendreFocus = 0;
	}
}

void placerEnnemiAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbEnnemi, const unsigned int estCaverne)
{
	while(nbEnnemi > 0)
	{
		unsigned int indexLig, indexCol;

		tirerCoordonneeAleatoireNiveau(indexSalle, &indexLig, &indexCol, estCaverne);

		if(estCaverne)
		{
			niveauActuel.salle[indexSalle].caverne.ennemi[nbEnnemi].position[LIG] = indexLig;
			niveauActuel.salle[indexSalle].caverne.ennemi[nbEnnemi].position[COL] = indexCol;
		}
		else
		{
			niveauActuel.salle[indexSalle].ennemi[nbEnnemi].position[LIG] = indexLig;
			niveauActuel.salle[indexSalle].ennemi[nbEnnemi].position[COL] = indexCol;
		}

		tirerCompetenceEnnemieAleatoireNouveauNiveau(indexSalle, nbEnnemi, estCaverne);

		--nbEnnemi;
	}
}

unsigned int determinerNiveauIAEnnemi(const unsigned int niveau)
{
	if(niveau >= 1 && niveau <= 5)
		return NIVEAU_IA_1;
	else if(niveau >= 5 && niveau <= 10)
		return NIVEAU_IA_2;
	else
		return NIVEAU_IA_3;
}

unsigned int determinerNbTourFocusEnnemi(const unsigned int niveauIA)
{
	static const unsigned int baseNbTourFocus[NB_NIVEAU_IA] =
	{
		10,
		25,
		50
	};

	return baseNbTourFocus[niveauIA];
}

unsigned int determinerNbTourAttendreFocusEnnemi(const unsigned int niveauIA)
{
	static const unsigned int baseNbTourAttendreFocus[NB_NIVEAU_IA] =
	{
		20,
		15,
		5
	};

	return baseNbTourAttendreFocus[niveauIA];
}

unsigned int tirerVieAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	static const unsigned int baseVieEnnemi[NB_NIVEAU_IA][2] =
	{
		{7, 12},
		{12, 21},
		{21, 35}
	};

	return hasard(baseVieEnnemi[niveauIA][MIN], baseVieEnnemi[niveauIA][MAX]);
}

unsigned int tirerDegatAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	static const unsigned int baseDegatEnnemi[NB_NIVEAU_IA][2] =
	{
		{3, 8},
		{8, 15},
		{15, 22}
	};

	return hasard(baseDegatEnnemi[niveauIA][MIN], baseDegatEnnemi[niveauIA][MAX]);
}

unsigned int tirerProtectionAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	static const unsigned int baseProtectionEnnemi[NB_NIVEAU_IA][2] =
	{
		{2, 6},
		{6, 14},
		{14, 24}
	};

	return hasard(baseProtectionEnnemi[niveauIA][MIN], baseProtectionEnnemi[niveauIA][MAX]);
}

unsigned int tirerPorteeAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	static const unsigned int basePorteeEnnemi[NB_NIVEAU_IA][2] =
	{
		{1, 1},
		{2, 5},
		{5, 7}
	};

	return hasard(basePorteeEnnemi[niveauIA][MIN], basePorteeEnnemi[niveauIA][MAX]);
}

unsigned int peutAttaquerJoueur(const unsigned int indexEnnemi)
{
	int distanceLig, distanceCol;
	unsigned int porteeAttaque;

	if(niveauActuel.estDansCaverne)
	{
		distanceLig = personnage.positionJoueur[LIG] - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG];
		distanceCol = personnage.positionJoueur[COL] - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL];
	}
	else
	{
		distanceLig = personnage.positionJoueur[LIG] - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG];
		distanceCol = personnage.positionJoueur[COL] - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL];
	}

	if(niveauActuel.estDansCaverne)
		porteeAttaque = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].porteeAttaque;
	else
		porteeAttaque = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].porteeAttaque;

	return estAportee(distanceLig, distanceCol, porteeAttaque);
}

void attaquerJoueur(const unsigned int indexEnnemi)
{
	unsigned int protectionJoueur;
	int difference;

	protectionJoueur = personnage.protection + inventaire.armure.protection;

	if(niveauActuel.estDansCaverne)
		difference = protectionJoueur - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].degatAttaque;
	else
		difference = protectionJoueur - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].degatAttaque;

	if(difference < 0)
		infligerDegatJoueur(-difference);
}

void deplacerEnnemi(const unsigned int indexEnnemi, const unsigned int direction)
{
	if(niveauActuel.estDansCaverne)
		deplacerJoueurDirection(direction, niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position);
	else
		deplacerJoueurDirection(direction, niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position);
}

void deplacerEnnemiAleatoire(const unsigned int indexEnnemi)
{
	deplacerEnnemi(indexEnnemi, hasard(HAUT, DROITE));
}

void deplacerEnnemiFocus(const unsigned int indexEnnemi, int *nbTourFocus)
{
	unsigned int ligEnnemi, colEnnemi;
	unsigned int estChoisisDirectionDeplacement;
	unsigned int directionAleatoire;

	estChoisisDirectionDeplacement = 0;

	if(niveauActuel.estDansCaverne)
	{
		ligEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG];
		colEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL];
	}
	else
	{
		ligEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG];
		colEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL];
	}

	do
	{
		directionAleatoire = hasard(HAUT, DROITE);

		if(directionAleatoire == HAUT && ligEnnemi > personnage.positionJoueur[LIG])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == BAS && ligEnnemi < personnage.positionJoueur[LIG])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == GAUCHE && colEnnemi > personnage.positionJoueur[COL])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == DROITE && colEnnemi < personnage.positionJoueur[COL])
			estChoisisDirectionDeplacement = 1;

	} while(!estChoisisDirectionDeplacement);

	deplacerEnnemi(indexEnnemi, directionAleatoire);
	--(*nbTourFocus);
}

unsigned int peutFocusJoueur(const unsigned int indexEnnemi, const unsigned int niveauIA)
{
	static const unsigned int basePorteeFocus[NB_NIVEAU_IA] =
	{
		5,
		15,
		30
	};
	int distanceLig, distanceCol;

	if(niveauActuel.estDansCaverne)
	{
		distanceLig = personnage.positionJoueur[LIG] - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG];
		distanceCol = personnage.positionJoueur[COL] - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL];
	}
	else
	{
		distanceLig = personnage.positionJoueur[LIG] - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG];
		distanceCol = personnage.positionJoueur[COL] - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL];
	}

	return estAportee(distanceLig, distanceCol, basePorteeFocus[niveauIA]);
}

void defocusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA)
{
	*modeFocus = 0;
	*nbTourFocus = -1;
	*nbTourAttendreFocus = determinerNbTourAttendreFocusEnnemi(niveauIA);
}

void focusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA)
{
	*modeFocus = 1;
	*nbTourFocus = determinerNbTourFocusEnnemi(niveauIA);
	*nbTourAttendreFocus = -1;
}

void IAennemi(void)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;
	unsigned int niveauIA;

	niveauIA = determinerNiveauIAEnnemi(personnage.niveauActuel);

	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		unsigned int *modeFocus;
		int *nbTourFocus, *nbTourAttendreFocus;

		if(niveauActuel.estDansCaverne)
		{
			modeFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].estModeFocus);
			nbTourFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbTourFocus);
			nbTourAttendreFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbTourAttendreFocus);
		}
		else
		{
			modeFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].estModeFocus);
			nbTourFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbTourFocus);
			nbTourAttendreFocus = &(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbTourAttendreFocus);
		}

		if(!estMortEnnemi(indexEnnemi))
		{
			if(peutAttaquerJoueur(indexEnnemi))
				attaquerJoueur(indexEnnemi);
			else if(*nbTourFocus == 0)
				defocusJoueurIAEnnemi(modeFocus, nbTourFocus, nbTourAttendreFocus, niveauIA);
			else if(peutFocusJoueur(indexEnnemi, niveauIA) && *nbTourAttendreFocus == 0)
			{
				focusJoueurIAEnnemi(modeFocus, nbTourFocus, nbTourAttendreFocus, niveauIA);
				deplacerEnnemiFocus(indexEnnemi, nbTourFocus);
			}
			else if(*modeFocus)
				deplacerEnnemiFocus(indexEnnemi, nbTourFocus);
			else
				deplacerEnnemiAleatoire(indexEnnemi);

			if(*nbTourAttendreFocus > 0)
				--(*nbTourAttendreFocus);
		}
	}
}

int trouverIndexEnnemi(const unsigned int ligne, const unsigned int colonne)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;

	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		unsigned int ligEnnemi, colEnnemi;

		if(niveauActuel.estDansCaverne)
		{
			ligEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG];
			colEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL];
		}
		else
		{
			ligEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG];
			colEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL];
		}

		if(ligEnnemi == ligne &&
		   colEnnemi == colonne)
			return indexEnnemi;
	}

	return -1;
}

unsigned int estMortEnnemi(const unsigned int indexEnnemi)
{
	int nbVieEnnemi;

	if(niveauActuel.estDansCaverne)
		nbVieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie;
	else
		nbVieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie;

	return nbVieEnnemi <= 0;
}

unsigned int nombreEnnemiNiveau(void)
{
	compteur indexSalle;
	unsigned int compteurEnnemi;

	compteurEnnemi = 0;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
		compteurEnnemi += niveauActuel.salle[indexSalle].nbEnnemi;

	return compteurEnnemi;
}

void placerCleEnnemi(const unsigned int indexCle)
{
	compteur indexSalle, indexEnnemi;
	unsigned int compteurEnnemi;

	compteurEnnemi = 0;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
		{
			if(indexCle == compteurEnnemi)
				niveauActuel.salle[indexSalle].ennemi[indexEnnemi].possedeCle = 1;
			else
				niveauActuel.salle[indexSalle].ennemi[indexEnnemi].possedeCle = 0;

			++compteurEnnemi;
		}
	}
}

void initialiserEmplacementCleEnnemi(void)
{
	placerCleEnnemi(hasard(0, nombreEnnemiNiveau()));
}

void afficherCaracteristiqueEnnemi(const unsigned int indexEnnemi)
{
	unsigned int nbVie;
	unsigned int nbDegat;
	unsigned int nbProtection;

	if(niveauActuel.estDansCaverne)
	{
		nbVie = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie;
		nbDegat = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].degatAttaque;
		nbProtection = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].protection;
	}
	else
	{
		nbVie = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie;
		nbDegat = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].degatAttaque;
		nbProtection = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].protection;
	}

	printf("Vie : ");

	couleur(BLEU);
	printf("%d", nbVie);
	couleur(BLANC);

	printf(" Degat : ");

	couleur(BLEU);
	printf("%d", nbDegat);
	couleur(BLANC);

	putchar('\n');

	printf("Protection : ");

	couleur(BLEU);
	printf("%d", nbProtection);
	couleur(BLANC);

	putchar('\n');
}
