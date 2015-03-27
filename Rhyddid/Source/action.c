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

void actionCase(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	unsigned int lig, col;
	char caractereActuel;

	lig = personnage.positionJoueur[LIG];
	col = personnage.positionJoueur[COL];

	if(niveauActuel.estDansCaverne)
		caractereActuel = niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[lig][col];
	else
		caractereActuel = niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[lig][col];

	if(niveauActuel.estDansCaverne)
	{
		/* Case de sortie de caverne */
		if(caractereActuel == '0')
			sortirCaverne();
	}
	else
	{
		/* Case d'entrée du niveau */
		if(caractereActuel == '0' && niveauActuel.salleActuelle == 0)
			afficherTextePorteEntree();
        /* Case de sortie du niveau */
		else if(caractereActuel == '0' && niveauActuel.salleActuelle == 8)
			afficherTextePorteSortie();
	}

	/* Coffre */
	if(caractereActuel == '?')
		ouvrirCoffre();
	/* Porte */
	else if(caractereActuel >= '1' && caractereActuel <= '9')
	{
		changerSalleNiveau(niveauActuel.salleActuelle, caractereActuel - '1'); 
		mettreAjourCarteNiveau(carteNiveau);
	}
	/* Entrée caverne */
	else if(caractereActuel == 'C' || caractereActuel == 'E')
		entrerCaverne();
}

void actionJoueur(void)
{
	char toucheEntree;
	
	toucheEntree = lireSansEntree();
	effectuerActionToucheEntree(toucheEntree);
}
