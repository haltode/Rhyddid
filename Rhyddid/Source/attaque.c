#include <stdio.h>

#include "attaque.h"
#include "niveau.h"
#include "inventaire.h"
#include "deplacement.h"
#include "personnage.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "jeu.h"

/* Inflige des degats indiques en paramtre a l'ennemi indique en parametre */
void inffligerDegatEnnemi(const unsigned int indexEnnemi, const unsigned int degat)
{
	int *nbVieEnnemi;

	/* On recupere la vie de l'ennemi */
	
	/* Si le joueur est dans une caverne */
	if(niveauActuel.estDansCaverne)
	{
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie -= degat;

		nbVieEnnemi = &(niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].nbVie);
	}
	/* Sinon le joueur est dans le niveau normal */
	else
	{
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie -= degat;

		nbVieEnnemi = &(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].nbVie);
	}

	/* Si l'ennemi est mort */
	if(*nbVieEnnemi <= 0)
	{
		/* On met sa vie a 0 pour eviter d'avoir des nombres negatifs */
		*nbVieEnnemi = 0;

		/* Si l'ennemi tue possede la cle de fin de niveau */
		if(niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].possedeCle)
		{
			/* On affiche un message d'information */
			ajouterMessageZoneInformation("Vous avez trouve une cle !", VERT);
			/* On ajoute la cle de fin de niveau a l'inventaire du joueur */
			ajouterCleInventaire();
		}

		/* Le joueur recupere de l'EXP grace a la mort de l'ennemi */
		recupererEXPEnnemiMortPersonnage();
	}
}

/* Renvoie un nombre different de 0 si le joueur peut attaque l'ennemi indique en parametre */
unsigned int joueurPeutAttaquerEnnemi(const unsigned int indexEnnemi)
{ 
	int distanceLig, distanceCol;

	/* On recupere la distance (ligne et colonne) entre le joueur et l'ennemi */

	/* Si le joueur est dans une caverne */
	if(niveauActuel.estDansCaverne)
	{
		distanceLig = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG] - personnage.positionJoueur[LIG];
		distanceCol = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL] - personnage.positionJoueur[COL];
	}
	/* Sinon le joueur est dans le niveau normal */
	else
	{
		distanceLig = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG] - personnage.positionJoueur[LIG];
		distanceCol = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL] - personnage.positionJoueur[COL];
	}

	/* On retourne le resultat de estAportee */
	return estAportee(distanceLig, distanceCol, inventaire.arme.portee);
}

/* Permet au joueur d'attaquer un ennemi */
void attaquerEnnemi(void)
{
	compteur indexEnnemi;
	unsigned int nbEnnemi;
	int degat;

	/* On recupere le nombre d'ennemi dans la salle ou dans la caverne */

	/* Si le joueur est dans une caverne */
	if(niveauActuel.estDansCaverne)
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	/* Sinon le joueur est dans le niveau normal */
	else
		nbEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;

	/* Pour chaque ennemi de la salle ou de la caverne */
	for(indexEnnemi = 0; indexEnnemi < nbEnnemi; ++indexEnnemi)
	{
		/* Si le joueur peut attaquer l'ennemi ET que l'ennemi n'est pas mort */
		if(joueurPeutAttaquerEnnemi(indexEnnemi) && !estMortEnnemi(indexEnnemi))
		{
			char message[TAILLE_MAX];

			/* On calcule les degats fait par le joueur */
			degat = personnage.degatParTour + inventaire.arme.degat;

			/* On calcule les degats en prenant en compte la protection de l'ennemi */
			if(niveauActuel.estDansCaverne)
				degat -= niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].protection;
			else
				degat -= niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].protection;

			/* Si les degats sont inferieurs a 0 */
			if(degat < 0)
				/* On met degat a 0, pour eviter d'avoir des nombres negatifs */
				degat = 0;

			/* On affiche le nombre de degat infflige a l'ennemi */
			sprintf(message, "Vous avez infflige %d degat a l'ennemi !", degat);
			ajouterMessageZoneInformation(message, VERT);

			/* On infflige les degats a l'ennemi (on appelle la fonction apres avoir afficher
			le nombre de degat au cas ou on trouve une cle pour afficher ca apres le nombre de
			degat infflige) */
			inffligerDegatEnnemi(indexEnnemi, degat);

			/* On initialise les variables aAttaqueEnnemi et indexEnnemiAttaque pour afficher
			au prochain tour les caracteristiques de l'ennemi a la place de la map en haut a 
			gauche */
			personnage.attaque.aAttaqueEnnemi = 1;
			personnage.attaque.indexEnnemiAttaque = indexEnnemi;

			/* On quitte la fonction car le joueur ne peut pas attaquer plus de 1 ennemi par
			tour */
			return ;
		}
	}
}
