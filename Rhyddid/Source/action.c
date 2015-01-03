#include <stdio.h>

#include "action.h"
#include "touche.h"
#include "deplacement.h"
#include "niveau.h"
#include "entree.h"
#include "sortie.h"
#include "coffre.h"
#include "caverne.h"
#include "lireSansEntree.h"
#include "personnage.h"

/* Execute l'interaction sur la case ou se trouve le joueur */
void actionCase(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	unsigned int lig, col;
	char caractereActuel;

	/* On recupere les coordonnes du joueur */
	lig = personnage.positionJoueur[LIG];
	col = personnage.positionJoueur[COL];

	/* On recupere le caractere de la case actuelle */
	if(niveauActuel.estDansCaverne)
		caractereActuel = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractereActuel = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	/* On teste le caractere */
	if(niveauActuel.estDansCaverne)
	{
		/* Si le joueur est dans une caverne et qu'il est sur la case '0' c'est qu'il est sur 
		la case pour sortir */
		if(caractereActuel == '0')
			sortirCaverne();
	}
	else
	{
		/* Sinon le joueur est dans le niveau normal, et s'il est sur la case '0' et que c'est 
		la salle 1, alors il est sur la case d'entree */
		if(caractereActuel == '0' && niveauActuel.salleActuelle == 0)
			afficherTextePorteEntree();
		/* Sinon le joueur est dans le niveau normal, et s'il est sur la case '0' et que c'est 
		la salle 9, alors il est sur la case de sortie */
		else if(caractereActuel == '0' && niveauActuel.salleActuelle == 8)
			afficherTextePorteSortie();
	}

	/* Si le joueur est sur un coffre */
	if(caractereActuel == '?')
		ouvrirCoffre();
	/* Si le joueur est sur une porte porte */
	else if(caractereActuel >= '1' && caractereActuel <= '9')
	{
		/* On change de salle */
		changerSalleNiveau(niveauActuel.salleActuelle, caractereActuel - '1'); 
		/* On met a jour la carte du niveau a cause du changement de salle */
		mettreAjourCarteNiveau(carteNiveau);
	}
	/* Si le joueur est dans une case pour entrer dans une caverne */
	else if(caractereActuel == 'C' || caractereActuel == 'E')
		entrerCaverne();
}

/* Lis la touche du clavier pressee par le joueur et deduis l'action qu'il faut faire */
void actionJoueur(void)
{
	char toucheEntree;
	
	/* On lit la touche */
	toucheEntree = lireSansEntree();
	/* On fait les tests pour savoir quelle est la touche appuyee */
	effectuerActionToucheEntree(toucheEntree);
}
