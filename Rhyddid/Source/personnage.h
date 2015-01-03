#ifndef PERSONNAGE_H
#define PERSONNAGE_H

/* personnage.c/personnage.h : permet de gerer un personnage */

/* ----- A inclure ----- */

#include "attaque.h"
#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_EXP_MAX 3
#define NB_EXP_MIN 2

#define NB_CATEGORIE_AMELIORABLE_NOUVEAU_LVL 3

#define NB_EXP_NIVEAU_MAX 100

#define CHANCE_MAX_EXP_MAX 2

#define LIG_INITIALE_JOUEUR 0
#define COL_INITIALE_JOUEUR 38

/* ----- Structure + Enumeration ----- */

typedef struct Personnage Personnage;
struct Personnage
{
	char nom[TAILLE_MAX];
	char race[TAILLE_MAX];
	unsigned int niveauEXPActuel;
	unsigned int niveauActuel;
	unsigned int lvl;
	char metier[TAILLE_MAX];
	unsigned int sante;
	int santeActuelle;
	unsigned int degatParTour;
	unsigned int protection;

	Attaque attaque;
	

	unsigned int positionJoueur[2];
};

/* ----- Prototype ----- */

/* Initiliase la position du joueur sur le nouveau niveau */
void initialiserPositionJoueurNouveauNiveau(void);


/* Initialise un nouveau personnage */
void initialiserNouveauPersonnage(void);
/* Sauvegarde le personnage */
void sauvegarderPersonnage(void);


/* Infflige des degats donnes en parametre au joueur */
void inffligerDegatJoueur(const unsigned int degat);


/* Ajout l'effet d'une potion de sante sur le personnage (effet indique en parametre) */
void ajouterEffetPotionSantePersonnage(const unsigned int nbSanteBonus);
/* Ajout l'effet d'une potion de force sur le personnage (effet indique en parametre) */
void ajouterEffetPotionForcePersonnage(const unsigned int nbForceBonus);
/* Ajout l'effet d'une potion de resistance sur le personnage (effet indique en parametre) */
void ajouterEffetPotionResistancePersonnage(const unsigned int nbResistanceBonus);


/* Affiche les bonus disponibles lors d'un nouveau lvl de la part du joueur */
void afficherBonusNouveauLvlPersonnage(void);
/* Permet de choisir le bonus du au fait du nouveau lvl du joueur */
unsigned int choisirBonusNouveauLvlPersonnage(void);
/* Ajoute le bonus du nouveau lvl au joueur */
void ajouterBonusNouveauLvlPersonnage(const unsigned int choixJoueurNouveauLvl);
/* Ajoute le bonus du fait du nouveau lvl du joueur */
void bonusNouveauLvlPersonnage(void);
/* Ajoute un lvl au joueur */
void ajouterLvlPersonnage(void);


/* Verifie si le joueur a passe un nouveau lvl, si c'est le cas il fait passer un lvl au 
joueur */
void verifierSiNouveauLvlPersonnage(void);


/* Recupere l'EXP donne par un ennemi mort */
void recupererEXPEnnemiMortPersonnage(void);

/* ----- Declaration ----- */

Personnage personnage;

#endif
