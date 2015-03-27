#include <stdio.h>

#include "personnage.h"
#include "couleur.h"
#include "potion.h"
#include "inventaire.h"
#include "effacer.h"
#include "niveau.h"
#include "deplacement.h"
#include "jeu.h"

void initialiserPositionJoueurNouveauNiveau(void)
{
	personnage.positionJoueur[LIG] = LIG_INITIALE_JOUEUR;
	personnage.positionJoueur[COL] = COL_INITIALE_JOUEUR;

	niveauActuel.salleActuelle = 0;
}

void initialiserNouveauPersonnage(void)
{
	personnage.niveauEXPActuel = 1;
	personnage.niveauActuel = 1;
	personnage.lvl = 1;
	personnage.santeActuelle = personnage.sante;

	personnage.attaque.aAttaqueEnnemi = 0;
	personnage.attaque.indexEnnemiAttaque = 0;
}

void sauvegarderPersonnage(void)
{
	FILE *detailPersonnage;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", personnage.nom);

	detailPersonnage = ouvrirFichier(chemin, "w+",
	"fichier \"detail_personnage.txt\", fonction \"sauvegarderPersonnage\"");

	fprintf(detailPersonnage, "%s\n", personnage.nom);
	fprintf(detailPersonnage, "%s\n", personnage.race);
	fprintf(detailPersonnage, "%d\n", personnage.niveauEXPActuel);
	fprintf(detailPersonnage, "%d\n", personnage.niveauActuel);
	fprintf(detailPersonnage, "%d\n", personnage.lvl);
	fprintf(detailPersonnage, "%s\n", personnage.metier);
	fprintf(detailPersonnage, "%d\n", personnage.sante);
	fprintf(detailPersonnage, "%d\n", personnage.santeActuelle);
	fprintf(detailPersonnage, "%d\n", personnage.protection);
	fprintf(detailPersonnage, "%d\n", personnage.degatParTour);

	fprintf(detailPersonnage, "%d\n", personnage.attaque.aAttaqueEnnemi);
	fprintf(detailPersonnage, "%d\n", personnage.attaque.indexEnnemiAttaque);

	fermerFichier(detailPersonnage,
	"fichier \"detail_personnage.txt\", fonction \"sauvegarderPersonnage\"");
}

void infligerDegatJoueur(const unsigned int degat)
{
	char message[TAILLE_MAX];

	personnage.santeActuelle -= degat;

	if(personnage.santeActuelle < 0)
		personnage.santeActuelle = 0;

	sprintf(message, "Vous avez perdu %d point(s) de vie !", degat);
	ajouterMessageZoneInformation(message, ROUGE);
}	

void ajouterEffetPotionSantePersonnage(const unsigned int nbSanteBonus)
{
	if(personnage.santeActuelle + nbSanteBonus <= personnage.sante)
		personnage.santeActuelle += nbSanteBonus;
	else
		personnage.santeActuelle = personnage.sante;

	inventaire.sante.nbBonus = nbSanteBonus;

	ajouterMessageZoneInformation("Vous avez utilise une potion de Sante !", VERT);
}

void ajouterEffetPotionForcePersonnage(const unsigned int nbForceBonus)
{
	personnage.degatParTour += nbForceBonus;

	inventaire.force.nbBonus = nbForceBonus;

	ajouterMessageZoneInformation("Vous avez utilise une potion de Force !", VERT);
}

/* Ajout l'effet d'une potion de resistance sur le personnage (effet indique en parametre) */
void ajouterEffetPotionResistancePersonnage(const unsigned int nbResistanceBonus)
{
	personnage.protection += nbResistanceBonus;

	inventaire.resistance.nbBonus = nbResistanceBonus;

	ajouterMessageZoneInformation("Vous avez utilise une potion de Resistance !", VERT);
}

void afficherBonusNouveauLvlPersonnage(void)
{
	printf("Choisissez la categorie que vous voulez ameliorer :\n\n");

	printf("\t1 - Sante (+1)\n");
	printf("\t2 - Degat (+1)\n");
	printf("\t3 - Protection (+1)\n\n");
}

unsigned int choisirBonusNouveauLvlPersonnage(void)
{
	unsigned int choixJoueur;

	choixJoueur = choisirMenuSansOperationPossible(NB_CATEGORIE_AMELIORABLE_NOUVEAU_LVL);
	return choixJoueur;
}

void ajouterBonusNouveauLvlPersonnage(const unsigned int choixJoueurNouveauLvl)
{
	static unsigned int *categorieAmeliorable[NB_CATEGORIE_AMELIORABLE_NOUVEAU_LVL] = 
	{
		&(personnage.sante),
		&(personnage.degatParTour),
		&(personnage.protection)
	};

	*(categorieAmeliorable[choixJoueurNouveauLvl - 1]) += 1;
}

void bonusNouveauLvlPersonnage(void)
{
	afficherBonusNouveauLvlPersonnage();
	ajouterBonusNouveauLvlPersonnage(choisirBonusNouveauLvlPersonnage());
}

void ajouterLvlPersonnage(void)
{
	effacer();
	titre("Nouveau lvl !", VERT);

	++(personnage.lvl);
	ajouterMessageZoneInformation("Vous avez augmente de lvl !", VERT);

	bonusNouveauLvlPersonnage();
}

void verifierSiNouveauLvlPersonnage(void)
{
	if(personnage.niveauEXPActuel >= NB_EXP_NIVEAU_MAX)
	{
		ajouterLvlPersonnage();
		personnage.niveauEXPActuel = 1;
	}
}

void recupererEXPEnnemiMortPersonnage(void)
{
	unsigned int nbEXP;
	char message[TAILLE_MAX];

	if(tirerChance(1, CHANCE_MAX_EXP_MAX))
		nbEXP = NB_EXP_MAX;
	else
		nbEXP = NB_EXP_MIN;

	personnage.niveauEXPActuel += nbEXP;

	sprintf(message, "Vous avez tue un ennemi et gagne %d EXP !", nbEXP);
	ajouterMessageZoneInformation(message, VERT);

	verifierSiNouveauLvlPersonnage();
}
