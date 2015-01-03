#include <stdio.h>

#include "ennemi.h"
#include "personnage.h"
#include "genererNiveau.h"
#include "deplacement.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "inventaire.h"
#include "niveau.h"

/* Tire des competences d'un ennemi aleatoirement */
void tirerCompetenceEnnemieAleatoireNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexEnnemi, const unsigned int estCaverne)
{
	unsigned int niveauIA;

	/* On determine le niveau de l'IA de l'ennemi */
	niveauIA = determinerNiveauIAEnnemi(personnage.niveauActuel);

	/* On tire au hasard ses competences (vie, degat, protection, portee) et initialise ses 
	variables importantes (estModeFocus, nbTourFocus, nbTourAttendreFocus) */

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

/* Place aleatoirement les ennemis dans la salle indexSalle du niveau */
void placerEnnemiAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbEnnemi, const unsigned int estCaverne)
{
	/* Pour chaque ennemi a generer */
	while(nbEnnemi > 0)
	{
		unsigned int indexLig, indexCol;

		/* On tire des coordonnes pour l'ennemi */
		tirerCoordonneeAleatoireNiveau(indexSalle, &indexLig, &indexCol, estCaverne);

		/* On enregistre les coordonnes de l'ennemi */

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

		/* On tire les competences de l'ennemi */
		tirerCompetenceEnnemieAleatoireNouveauNiveau(indexSalle, nbEnnemi, estCaverne);

		/* On decremente de 1 le nombre d'ennemi a generer */
		--nbEnnemi;
	}
}

/* Permet de terminer le niveau de l'IA de l'ennemi en fonction du niveau ou se trouve le joueur */
unsigned int determinerNiveauIAEnnemi(const unsigned int niveau)
{
	/* On teste tous les intervalles et on renvoie le niveau correspondant a l'intervalle */

	if(niveau >= 1 && niveau <= 5)
		return NIVEAU_IA_1;
	else if(niveau >= 5 && niveau <= 10)
		return NIVEAU_IA_2;
	else
		return NIVEAU_IA_3;
}

/* Determine le nombre de tour que l'ennemi doit focus le joueur en fonction du niveau de l'IA */
unsigned int determinerNbTourFocusEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA le nombre de tour de focus min et le nombre de tour
	de focus max possible pour un ennemi */
	static const unsigned int baseNbTourFocus[NB_NIVEAU_IA] =
	{
		10,
		25,
		50
	};

	/* On renvoie un nombre au  hasard entre le nombre de tour de focus min et le nombre de 
	tour de focus max possible pour le niveau de l'IA correspondant */
	return baseNbTourFocus[niveauIA];
}

/* Determine le nombre de tour que l'ennemi doit attendre avant de pouvoir re-focus le joueur 
en fonction du niveau de l'IA */
unsigned int determinerNbTourAttendreFocusEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA le nombre de tour a attendre avant de re-focus min 
	et le nombre de tour a attendre avant de re-focus max possible pour un ennemi */
	static const unsigned int baseNbTourAttendreFocus[NB_NIVEAU_IA] =
	{
		20,
		15,
		5
	};

	/* On renvoie un nombre au  hasard entre le nombre de tour a attendre avant de re-focus min
	et le nombre de tour a attendre avant de re-focus max possible pour le niveau de l'IA 
	correspondant */
	return baseNbTourAttendreFocus[niveauIA];
}

/* Tire la vie d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerVieAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA la vie min et la vie max possible pour un ennemi */
	static const unsigned int baseVieEnnemi[NB_NIVEAU_IA][2] =
	{
		{7, 12},
		{12, 21},
		{21, 35}
	};

	/* On renvoie un nombre au  hasard entre la vie min et la vie max possible pour le niveau
	de l'IA correspondant */
	return hasard(baseVieEnnemi[niveauIA][MIN], baseVieEnnemi[niveauIA][MAX]);
}

/* Tire les degats d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerDegatAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA les degats min et les degats max possible pour un 
	ennemi */
	static const unsigned int baseDegatEnnemi[NB_NIVEAU_IA][2] =
	{
		{3, 8},
		{8, 15},
		{15, 22}
	};

	/* On renvoie un nombre au  hasard entre les degats min et les degats max possible pour le
	niveau de l'IA correspondant */
	return hasard(baseDegatEnnemi[niveauIA][MIN], baseDegatEnnemi[niveauIA][MAX]);
}

/* Tire la protection d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerProtectionAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA la protection min et la protection max possible pour 
	un ennemi */
	static const unsigned int baseProtectionEnnemi[NB_NIVEAU_IA][2] =
	{
		{2, 6},
		{6, 14},
		{14, 24}
	};

	/* On renvoie un nombre au  hasard entre la protection min et la protection max possible 
	pour le niveau de l'IA correspondant */
	return hasard(baseProtectionEnnemi[niveauIA][MIN], baseProtectionEnnemi[niveauIA][MAX]);
}

/* Tire la portee d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerPorteeAleatoireNouveauEnnemi(const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA la portee min et la portee max possible pour un 
	ennemi */
	static const unsigned int basePorteeEnnemi[NB_NIVEAU_IA][2] =
	{
		{1, 1},
		{2, 5},
		{5, 7}
	};

	/* On renvoie un nombre au  hasard entre la portee min et la portee max possible pour le 
	niveau de l'IA correspondant */
	return hasard(basePorteeEnnemi[niveauIA][MIN], basePorteeEnnemi[niveauIA][MAX]);
}

/* Renvoie 1 si l'ennemi indexEnnemi peut attaque le joueur  et 0 sinon */
unsigned int peutAttaquerJoueur(const unsigned int indexEnnemi)
{
	int distanceLig, distanceCol;
	unsigned int porteeAttaque;

	/* On recupere la distance entre le joueur et l'ennemi */

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

	/* On recupere la portee de l'ennemi */

	if(niveauActuel.estDansCaverne)
		porteeAttaque = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].porteeAttaque;
	else
		porteeAttaque = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].porteeAttaque;

	/* On retourne le resultat de estAportee */
	return estAportee(distanceLig, distanceCol, porteeAttaque);
}

/* Attaque le joueur */
void attaquerJoueur(const unsigned int indexEnnemi)
{
	unsigned int protectionJoueur;
	int difference;

	/* On recupere la protection du joueur (protection + protection armure) */
	protectionJoueur = personnage.protection + inventaire.armure.protection;

	/* On recupere la difference entre la protection du joueur et les degats de l'ennemi 
	indexEnnemi*/
	if(niveauActuel.estDansCaverne)
		difference = protectionJoueur - niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].degatAttaque;
	else
		difference = protectionJoueur - niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].degatAttaque;

	/* Si la difference est inferieure a 0 */
	if(difference < 0)
		/* On inflige les degats au joueur */
		inffligerDegatJoueur(-difference);

	/* Sinon le joueur a trop de protection pour que cet ennemi lui inflige des degats donc on
	ne fait rien */
}

/* Deplace l'ennemi indexEnnemi dans la direction donnee en parametre */
void deplacerEnnemi(const unsigned int indexEnnemi, const unsigned int direction)
{
	/* On appelle la fonction deplacerJoueurDirection en lui donnant les coordonnes de l'ennemi */

	if(niveauActuel.estDansCaverne)
		deplacerJoueurDirection(direction, niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position);
	else
		deplacerJoueurDirection(direction, niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position);
}

/* Deplace l'ennemi indexEnnemi aleatoirement */
void deplacerEnnemiAleatoire(const unsigned int indexEnnemi)
{
	/* On appelle la fonction deplacerEnnemi en lui donnant indexEnnemi et une direction au 
	hasard tire entre Haut, Bas, Gauche, Droite) */
	deplacerEnnemi(indexEnnemi, hasard(HAUT, DROITE));
}

/* Deplace l'ennemi indexEnnemi de maniere intelligente car il focus le joueur */
void deplacerEnnemiFocus(const unsigned int indexEnnemi, int *nbTourFocus)
{
	unsigned int ligEnnemi, colEnnemi;
	unsigned int estChoisisDirectionDeplacement;
	unsigned int directionAleatoire;

	estChoisisDirectionDeplacement = 0;

	/* On recupere la position de l'ennemi indexEnnemi */

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

	/* Faire */
	do
	{
		/* On tire une direction aleatoirement */
		directionAleatoire = hasard(HAUT, DROITE);

		/* On teste pour les directions si le joueur est dans cette direction, si c'est le cas
		on arrete la boucle sinon on continue */

		if(directionAleatoire == HAUT && ligEnnemi > personnage.positionJoueur[LIG])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == BAS && ligEnnemi < personnage.positionJoueur[LIG])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == GAUCHE && colEnnemi > personnage.positionJoueur[COL])
			estChoisisDirectionDeplacement = 1;
		else if(directionAleatoire == DROITE && colEnnemi < personnage.positionJoueur[COL])
			estChoisisDirectionDeplacement = 1;

	/* Tant que on a pas choisit une direction pour le deplacement de l'ennemi */
	} while(!estChoisisDirectionDeplacement);

	/* On deplace l'ennemi indexEnnemi dans la direction directionAleatoire */
	deplacerEnnemi(indexEnnemi, directionAleatoire);

	/* On decremente le nombre de tour de focus de l'ennemi de 1 */
	--(*nbTourFocus);
}

/* Retourne 1 si l'ennemi indexEnnemi peut focus le joueur et 0 sinon */
unsigned int peutFocusJoueur(const unsigned int indexEnnemi, const unsigned int niveauIA)
{
	/* Contient pour chaque niveau de l'IA la portee du focus min et la portee du focus max 
	possible pour un ennemi */
	static const unsigned int basePorteeFocus[NB_NIVEAU_IA] =
	{
		5,
		15,
		30
	};
	int distanceLig, distanceCol;

	/* On recupere la distance entre le joueur et l'ennemi */

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

	/* On retourne le resultat de estAportee */
	return estAportee(distanceLig, distanceCol, basePorteeFocus[niveauIA]);
}

/* Defocus l'ennemi du joueur et met a jour les informations necessaires */
void defocusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA)
{
	/* On met la variable modeFocus de l'ennemi a 0 pour indiquer qu'il ne focus plus le 
	joueur */
	*modeFocus = 0;

	/* On met la variable nbTourFocus de l'ennemi a -1 pour indiquer que l'ennemi ne focus plus
	et qu'il doit attendre avant de re-focus le joueur */
	*nbTourFocus = -1;
	
	/* On determine la valeur de la variable nbTourAttendreFocus de l'ennemi pour indiquer a 
	l'ennemi le nombre de tour a attendre avant de pouvoir re-focus le joueur */
	*nbTourAttendreFocus = determinerNbTourAttendreFocusEnnemi(niveauIA);
}

/* Focus le joueur et met a jour les informations necessaires */
void focusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA)
{
	/* On met la variable modeFocus de l'ennemi a 1 pour indiquer que l'ennemi focus le joueur */ 
	*modeFocus = 1;

	/* On determine la valeur de la variable nbTourFocus de l'ennemi pour indiquer a l'ennemi 
	le nombre de tour ou il focus le joueur */
	*nbTourFocus = determinerNbTourFocusEnnemi(niveauIA);

	/* On met la variable nbTourAttendreFocus de l'ennemi a -1 pour indiquer que l'ennemi focus
	le joueur */
	*nbTourAttendreFocus = -1;
}

/* Gere l'IA de l'ennemi */
void IAennemi(void)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;
	unsigned int niveauIA;

	/* On recupere le niveau de l'IA de l'ennemi */
	niveauIA = determinerNiveauIAEnnemi(personnage.niveauActuel);

	/* On recupere le nombre d'ennemi dans la salle ou caverne */

	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	/* Pour chaque ennemi */
	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		unsigned int *modeFocus;
		int *nbTourFocus, *nbTourAttendreFocus;

		/* On pointe sur les informations (si l'ennemi est en train de focus, le nombre de tour 
		de focus de l'ennemi, le nombre de tour a attendre avant de re-focus) de l'ennemi */

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

		/* Si l'ennemi n'est pas mort */
		if(!estMortEnnemi(indexEnnemi))
		{
			/* Si l'ennemi peut attaquer le joueur */
			if(peutAttaquerJoueur(indexEnnemi))
				/* L'ennemi attaque le joueur */
				attaquerJoueur(indexEnnemi);
			/* Sinon si le nombre de tour de focus de l'ennemi atteint 0 */
			else if(*nbTourFocus == 0)
				/* On defocus le joueur */
				defocusJoueurIAEnnemi(modeFocus, nbTourFocus, nbTourAttendreFocus, niveauIA);
			/* Sinon si l'ennemi peut focus le joueur et qu'il peut focus */
			else if(peutFocusJoueur(indexEnnemi, niveauIA) && *nbTourAttendreFocus == 0)
			{
				/* On focus le joueur */
				focusJoueurIAEnnemi(modeFocus, nbTourFocus, nbTourAttendreFocus, niveauIA);

				/* On deplace l'ennemi de facon intelligente puisqu'il focus l'ennemi */
				deplacerEnnemiFocus(indexEnnemi, nbTourFocus);
			}
			/* Sinon si l'ennemi focus deja le joueur */
			else if(*modeFocus)
				/* On deplace l'ennemi de facon intelligente puisqu'il focus l'ennemi */
				deplacerEnnemiFocus(indexEnnemi, nbTourFocus);
			/* Sinon */
			else
				/* On deplace l'ennemi de maniere aleatoire */
				deplacerEnnemiAleatoire(indexEnnemi);

			/* Si nbTourAttendreFocus est superieur a 0 */
			if(*nbTourAttendreFocus > 0)
				/* On le decremente de 1 */
				--(*nbTourAttendreFocus);
		}
	}
}

/* Renvoie l'index de l'ennemi sur les coordonnes ligne colonne */
int trouverIndexEnnemi(const unsigned int ligne, const unsigned int colonne)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;

	/* On recupere le nombre d'ennemi dans la salle ou la caverne */

	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	/* Pour chaque ennemi */
	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		unsigned int ligEnnemi, colEnnemi;

		/* On recupere les coordonnes (ligne et colonne) de l'ennemi */

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

		/* Si les coordonnes donnees en parametre correspondent aux coordonnes de l'ennemi */
		if(ligEnnemi == ligne &&
		   colEnnemi == colonne)
			/* On retourne l'index de l'ennemi */
			return indexEnnemi;
	}

	/* Si on a pas trouve l'ennemi on renvoit -1 */
	return -1;
}

/* Renvoie 1 si l'ennemi indexEnnemi est mort et 0 sinon */
unsigned int estMortEnnemi(const unsigned int indexEnnemi)
{
	int nbVieEnnemi;

	/* On recupere la vie de l'ennemi */

	if(niveauActuel.estDansCaverne)
		nbVieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie;
	else
		nbVieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie;

	/* Retourne la condition nbVieEnnemi <= 0 */
	return nbVieEnnemi <= 0;
}

/* Renvoie le nombre d'ennemi dans le niveau */
unsigned int nombreEnnemiNiveau(void)
{
	compteur indexSalle;
	unsigned int compteurEnnemi;

	compteurEnnemi = 0;

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
		/* On ajoute au compteur le nombre d'ennemi de la salle */
		compteurEnnemi += niveauActuel.salle[indexSalle].nbEnnemi;

	/* On retourne le compteur */
	return compteurEnnemi;
}

/* Place la cle de fin de niveau sur l'ennemi numero indexCle du niveau */
void placerCleEnnemi(const unsigned int indexCle)
{
	compteur indexSalle, indexEnnemi;
	unsigned int compteurEnnemi;

	compteurEnnemi = 0;

	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* Pour chaque ennemi */
		for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
		{
			/* Si on a trouve l'ennemi numero indexCle du niveau */
			if(indexCle == compteurEnnemi)
				/* On met la variable possedeCle de l'ennemi a 1 */
				niveauActuel.salle[indexSalle].ennemi[indexEnnemi].possedeCle = 1;
			/* Sinon */
			else
				/* On met la variable possedeCle de l'ennemi a 0 */
				niveauActuel.salle[indexSalle].ennemi[indexEnnemi].possedeCle = 0;

			/* On incremente le compteur de 1 */
			++compteurEnnemi;
		}
	}
}

/* Choisit l'emplacement de la cle de fin de niveau et la place sur l'ennemi choisit */
void initialiserEmplacementCleEnnemi(void)
{
	/* On place la cle sur l'ennemi choisit au hasard par la fonction hasard entre 0 et le 
	nombre d'ennemi du niveau */
	placerCleEnnemi(hasard(0, nombreEnnemiNiveau()));
}

/* Affiche les caracteristiques de l'ennemi indexEnnemi */
void afficherCaracteristiqueEnnemi(const unsigned int indexEnnemi)
{
	unsigned int nbVie;
	unsigned int nbDegat;
	unsigned int nbProtection;

	/* On recupere les informations de l'ennemi (vie, degat, protection) */

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

	/* On affiche les informations de l'ennemi */

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
