#include <stdio.h>

#include "coffre.h"
#include "fonctionsUtiles.h"
#include "effacer.h"
#include "couleur.h"
#include "niveau.h"
#include "deplacement.h"
#include "personnage.h"
#include "jeu.h"
#include "genererNiveau.h"

void placerCoffreAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbCoffre, const unsigned int estCaverne)
{
	unsigned int indexLig, indexCol;

	while(nbCoffre > 0)	
	{
		tirerCoordonneeAleatoireNiveau(indexSalle, &indexLig, &indexCol, estCaverne);

		if(estCaverne)
			niveauActuel.salle[indexSalle].caverne.mapSalle[indexLig][indexCol] = '?';
		else
			niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = '?';

		--nbCoffre;	
	}
}

void initialiserContenuCoffre(Coffre *coffre)
{
	coffre->tek = NON;
	coffre->armure = NON;
	coffre->arme = NON;
	coffre->tresor = NON;
	coffre->potion = NON;	
}

void deciderContenuCoffre(Coffre *coffre)
{
	if(tirerChance(1, CHANCE_MAX_TEK))
		coffre->tek = OUI;
	if(tirerChance(1, CHANCE_MAX_ARMURE))
		coffre->armure = OUI;
	if(tirerChance(1, CHANCE_MAX_ARME))
		coffre->arme = OUI;
	if(tirerChance(1, CHANCE_MAX_TRESOR))
		coffre->tresor = OUI;
	if(tirerChance(1, CHANCE_MAX_POTION))
		coffre->potion = OUI;
}

void remplirContenuCoffre(Coffre *coffre)
{
	if(coffre->tek == OUI)
		genererTekCoffre(&(coffre->inventaire.tek));
	if(coffre->armure == OUI)
		genererArmureCoffre(&(coffre->inventaire.armure));
	if(coffre->arme == OUI)
		genererArmeCoffre(&(coffre->inventaire.arme));
	if(coffre->tresor == OUI)
		genererTresorCoffre(&(coffre->inventaire.tresor[0]));
	if(coffre->potion == OUI)
		genererPotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

void genererContenuCoffre(Coffre *coffre)
{
	deciderContenuCoffre(coffre);
	remplirContenuCoffre(coffre);
}

void afficherContenuCoffre(const Coffre *coffre)
{
	effacer();
	titre("Coffre", VERT);

	separationTexte();

	printf("Equipement : \n\n");

	afficherArmureInventaire();
	afficherArmeInventaire();

	separationTexte();

	printf("Voici le contenu du coffre :\n\n");

	if(coffre->tek == OUI && coffre->inventaire.tek.nbTek != 0)
		afficherTekCoffre(coffre);
	if(coffre->armure == OUI)
		afficherArmureCoffre(coffre);
	if(coffre->arme == OUI)
		afficherArmeCoffre(coffre);
	if(coffre->tresor == OUI)
		afficherTresorCoffre(coffre);
	if(coffre->potion == OUI)
		afficherPotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

void prendreContenuCoffre(const Coffre *coffre)
{
	if(coffre->tek == OUI)
		prendreTekCoffre(&(coffre->inventaire.tek));
	if(coffre->armure == OUI)
		prendreArmureCoffre(&(coffre->inventaire.armure));
	if(coffre->arme == OUI)
		prendreArmeCoffre(&(coffre->inventaire.arme));
	if(coffre->tresor == OUI)
		prendreTresorCoffre(&(coffre->inventaire.tresor[0]));
	if(coffre->potion == OUI)
		prendrePotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

unsigned int estCoffreVide(const Coffre *coffre)
{
	if(coffre->tek == OUI && coffre->inventaire.tek.nbTek != 0)
		return 0;
	if(coffre->armure == OUI)
		return 0;
	if(coffre->arme == OUI)
		return 0;
	if(coffre->tresor == OUI)
		return 0;
	if(coffre->potion == OUI)
		return 0;

	return 1;
}

void coffrePiege(void)
{
	unsigned int indexEnnemi;

	if(niveauActuel.estDansCaverne)
		indexEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else	
		indexEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;
	
	if(niveauActuel.estDansCaverne)
	{
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG] = personnage.positionJoueur[LIG];
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL] = personnage.positionJoueur[COL];
	}
	else
	{
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG] = personnage.positionJoueur[LIG];
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL] = personnage.positionJoueur[COL];
	}

	if(niveauActuel.estDansCaverne)
		tirerCompetenceEnnemieAleatoireNouveauNiveau(niveauActuel.salleActuelle, indexEnnemi, CAVERNE);
	else
		tirerCompetenceEnnemieAleatoireNouveauNiveau(niveauActuel.salleActuelle, indexEnnemi, NON_CAVERNE);

	if(niveauActuel.estDansCaverne)
		++(niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi);
	else
		++(niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi);
}

void supprimerCoffre(void)
{
	if(niveauActuel.estDansCaverne)
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[personnage.positionJoueur[LIG]][personnage.positionJoueur[COL]] = ' ';
	else
		niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[personnage.positionJoueur[LIG]][personnage.positionJoueur[COL]] = ' ';
}

void ouvrirCoffre(void)
{
	Coffre coffre;

	if(tirerChance(1, CHANCE_MAX_COFFRE_PIEGE))
	{
		ajouterMessageZoneInformation("C'est un coffre piege ! Un ennemi est apparu !", ROUGE);
		coffrePiege();
	}
	else
	{
		unsigned int estVide;

		initialiserContenuCoffre(&coffre);
		genererContenuCoffre(&coffre);

		estVide = estCoffreVide(&coffre);

		if(estVide)
			ajouterMessageZoneInformation("C'est un coffre vide ! :(", ROUGE);
		else
		{
			afficherContenuCoffre(&coffre);
			separationTexte();
			prendreContenuCoffre(&coffre);
			appuyezEntree("Appuyez sur ENTREE pour prendre le contenu du coffre et revenir en jeu...");
		}
	}

	supprimerCoffre();
}
