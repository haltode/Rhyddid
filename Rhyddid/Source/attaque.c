#include <stdio.h>

#include "attaque.h"
#include "niveau.h"
#include "inventaire.h"
#include "deplacement.h"
#include "personnage.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "jeu.h"

void infligerDegatEnnemi(const unsigned int indexEnnemi, const unsigned int degat)
{
	int *nbVieEnnemi;

	if(niveauActuel.estDansCaverne)
	{
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie -= degat;
		nbVieEnnemi = &(niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie);
	}
	else
	{
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie -= degat;
		nbVieEnnemi = &(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie);
	}

	if(*nbVieEnnemi <= 0)
	{
		*nbVieEnnemi = 0;

		if(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].possedeCle)
		{
			ajouterMessageZoneInformation("Vous avez trouve une cle !", VERT);
			ajouterCleInventaire();
		}

		recupererEXPEnnemiMortPersonnage();
	}
}

unsigned int joueurPeutAttaquerEnnemi(const unsigned int indexEnnemi)
{ 
	int distanceLig, distanceCol;

	if(niveauActuel.estDansCaverne)
	{
		distanceLig = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG] - personnage.positionJoueur[LIG];
		distanceCol = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL] - personnage.positionJoueur[COL];
	}
	else
	{
		distanceLig = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG] - personnage.positionJoueur[LIG];
		distanceCol = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL] - personnage.positionJoueur[COL];
	}

	return estAportee(distanceLig, distanceCol, inventaire.arme.portee);
}

void attaquerEnnemi(void)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;
	int degat;

	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		if(joueurPeutAttaquerEnnemi(indexEnnemi) && !estMortEnnemi(indexEnnemi))
		{
			char message[TAILLE_MAX];

			degat = personnage.degatParTour + inventaire.arme.degat;

			if(niveauActuel.estDansCaverne)
				degat -= niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].protection;
			else
				degat -= niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].protection;

			if(degat < 0)
				degat = 0;

			sprintf(message, "Vous avez inflige %d degat a l'ennemi !", degat);
			ajouterMessageZoneInformation(message, VERT);

			infligerDegatEnnemi(indexEnnemi, degat);

			personnage.attaque.aAttaqueEnnemi = 1;
			personnage.attaque.indexEnnemiAttaque = indexEnnemi;

			return ;
		}
	}
}
