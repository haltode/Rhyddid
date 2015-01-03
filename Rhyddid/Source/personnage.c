#include <stdio.h>

#include "personnage.h"
#include "couleur.h"
#include "potion.h"
#include "inventaire.h"
#include "effacer.h"
#include "niveau.h"
#include "deplacement.h"
#include "jeu.h"

/* Initiliase la position du joueur sur le nouveau niveau */
void initialiserPositionJoueurNouveauNiveau(void)
{
	/* On initialise la position du joueur (ligne et colonne) */

	personnage.positionJoueur[LIG] = LIG_INITIALE_JOUEUR;
	personnage.positionJoueur[COL] = COL_INITIALE_JOUEUR;

	/* On initialise la salle actuelle a 0 */
	niveauActuel.salleActuelle = 0;
}

/* Initialise un nouveau personnage */
void initialiserNouveauPersonnage(void)
{
	/* On initialise toutes les variables du nouveau personnage */

	personnage.niveauEXPActuel = 1;
	personnage.niveauActuel = 1;
	personnage.lvl = 1;
	personnage.santeActuelle = personnage.sante;

	personnage.attaque.aAttaqueEnnemi = 0;
	personnage.attaque.indexEnnemiAttaque = 0;
}

/* Sauvegarde le personnage */
void sauvegarderPersonnage(void)
{
	FILE *detailPersonnage;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", personnage.nom);

	/* On ouvre le fichier contenant les informations du personnage */
	detailPersonnage = ouvrirFichier(chemin, "w+",
	"fichier \"detail_personnage.txt\", fonction \"sauvegarderPersonnage\"");

	/* On ecrit toutes les informations du personnage (nom, race, EXP, lvl, metier etc.) */

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

	/* On ferme le fichier contenant les informations du personnage */
	fermerFichier(detailPersonnage,
	"fichier \"detail_personnage.txt\", fonction \"sauvegarderPersonnage\"");
}

/* Infflige des degats donnes en parametre au joueur */
void inffligerDegatJoueur(const unsigned int degat)
{
	char message[TAILLE_MAX];

	/* On enleve de la vie au joueur*/
	personnage.santeActuelle -= degat;

	/* Si sa vie est inferieure a 0 */
	if(personnage.santeActuelle < 0)
		/* On la remet a 0 pour ne pas avoir de nombre negatif */
		personnage.santeActuelle = 0;

	/* On affiche un message indiquant la perte de vie */

	sprintf(message, "Vous avez perdu %d point(s) de vie !", degat);
	ajouterMessageZoneInformation(message, ROUGE);
}	

/* Ajout l'effet d'une potion de sante sur le personnage (effet indique en parametre) */
void ajouterEffetPotionSantePersonnage(const unsigned int nbSanteBonus)
{
	/* On ajoute nbSanteBonus de vie au joueur */

	/* Si l'ajout de vie est toujours inferieur a la sante maximum du joueur */
	if(personnage.santeActuelle + nbSanteBonus <= personnage.sante)
		/* On ajoute simplement la vie */
		personnage.santeActuelle += nbSanteBonus;
	/* Sinon */
	else
		/* On initialise la vie a la vie maximum du joueur (pour ne pas depasser la vie maximum
		lorsque le joueur prend la potion de sante) */
		personnage.santeActuelle = personnage.sante;

	/* On enregistre le bonus de sante */
	inventaire.sante.nbBonus = nbSanteBonus;

	/* On affiche un message indiquant l'utilisation de la potion */
	ajouterMessageZoneInformation("Vous avez utilise une potion de Sante !", VERT);
}

/* Ajout l'effet d'une potion de force sur le personnage (effet indique en parametre) */
void ajouterEffetPotionForcePersonnage(const unsigned int nbForceBonus)
{
	/* On ajoute nbForceBonus au degat du joueur */
	personnage.degatParTour += nbForceBonus;

	/* On enregistre le bonus de force */
	inventaire.force.nbBonus = nbForceBonus;

	/* On affiche un message indiquant l'utilisation de la potion */
	ajouterMessageZoneInformation("Vous avez utilise une potion de Force !", VERT);
}

/* Ajout l'effet d'une potion de resistance sur le personnage (effet indique en parametre) */
void ajouterEffetPotionResistancePersonnage(const unsigned int nbResistanceBonus)
{
	/* On ajoute nbResistanceBonus a la resistance du joueur */
	personnage.protection += nbResistanceBonus;

	/* On enregistre le bonus de resistance */
	inventaire.resistance.nbBonus = nbResistanceBonus;

	/* On affiche un message indiquant l'utilisation de la potion */
	ajouterMessageZoneInformation("Vous avez utilise une potion de Resistance !", VERT);
}

/* Affiche les bonus disponibles lors d'un nouveau lvl de la part du joueur */
void afficherBonusNouveauLvlPersonnage(void)
{
	printf("Choisissez la categorie que vous voulez ameliorer :\n\n");

	printf("\t1 - Sante (+1)\n");
	printf("\t2 - Degat (+1)\n");
	printf("\t3 - Protection (+1)\n\n");
}

/* Permet de choisir le bonus du au fait du nouveau lvl du joueur */
unsigned int choisirBonusNouveauLvlPersonnage(void)
{
	unsigned int choixJoueur;

	/* On demande le choix du joueur */
	choixJoueur = choisirMenuSansOperationPossible(NB_CATEGORIE_AMELIORABLE_NOUVEAU_LVL);

	/* On retourne son choix */
	return choixJoueur;
}

/* Ajoute le bonus du nouveau lvl au joueur */
void ajouterBonusNouveauLvlPersonnage(const unsigned int choixJoueurNouveauLvl)
{
	/* Contient un pointeur vers chaque categorie ameliorable grace au nouveau lvl */
	static unsigned int *categorieAmeliorable[NB_CATEGORIE_AMELIORABLE_NOUVEAU_LVL] = 
	{
		&(personnage.sante),
		&(personnage.degatParTour),
		&(personnage.protection)
	};

	/* On incremente de 1 la categorie choisit par le joueur */
	*(categorieAmeliorable[choixJoueurNouveauLvl - 1]) += 1;
}

/* Ajoute le bonus du fait du nouveau lvl du joueur */
void bonusNouveauLvlPersonnage(void)
{
	/* On affiche les bonus disponibles lors d'un nouveau lvl */
	afficherBonusNouveauLvlPersonnage();
	/* On ajoute au joueur son bonus qu'il a choisit */
	ajouterBonusNouveauLvlPersonnage(choisirBonusNouveauLvlPersonnage());
}

/* Ajoute un lvl au joueur */
void ajouterLvlPersonnage(void)
{
	effacer();
	titre("Nouveau lvl !", VERT);

	/* On incremente de 1 le lvl du personnage */
	++(personnage.lvl);
	/* On affiche un message indiquant le passage d'un nouveau lvl */
	ajouterMessageZoneInformation("Vous avez augmente de lvl !", VERT);

	/* On ajoute le bonus du au fait du nouveau lvl du joueur */
	bonusNouveauLvlPersonnage();
}

/* Verifie si le joueur a passe un nouveau lvl, si c'est le cas il fait passer un lvl au 
joueur */
void verifierSiNouveauLvlPersonnage(void)
{
	/* Si le joueur a assez d'EXP pour passer un niveau */
	if(personnage.niveauEXPActuel >= NB_EXP_NIVEAU_MAX)
	{
		/* On fait passer au joueur 1 lvl */
		ajouterLvlPersonnage();

		/* On initialise son EXP a 1 */
		personnage.niveauEXPActuel = 1;
	}
}

/* Recupere l'EXP donne par un ennemi mort */
void recupererEXPEnnemiMortPersonnage(void)
{
	unsigned int nbEXP;
	char message[TAILLE_MAX];

	/* Le joueur a 1 chance sur CHANCE_MAX_EXP_MAX d'avoir NB_EXP_MAX d'EXP et sinon il a
	NB_EXP_MIN d'EXP */

	/* On determine l'EXP que le joueur va recevoir */

	if(tirerChance(1, CHANCE_MAX_EXP_MAX))
		nbEXP = NB_EXP_MAX;
	else
		nbEXP = NB_EXP_MIN;

	/* On ajoute l'EXP au joueur */
	personnage.niveauEXPActuel += nbEXP;

	/* On affiche un message indiquant que le joueur a gagne de l'EXP */
	sprintf(message, "Vous avez tue un ennemi et gagne %d EXP !", nbEXP);
	ajouterMessageZoneInformation(message, VERT);

	/* On verifie si le joueur a gagne un lvl */
	verifierSiNouveauLvlPersonnage();
}
