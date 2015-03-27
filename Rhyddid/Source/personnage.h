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

void initialiserPositionJoueurNouveauNiveau(void);


void initialiserNouveauPersonnage(void);
void sauvegarderPersonnage(void);


void infligerDegatJoueur(const unsigned int degat);


void ajouterEffetPotionSantePersonnage(const unsigned int nbSanteBonus);
void ajouterEffetPotionForcePersonnage(const unsigned int nbForceBonus);
void ajouterEffetPotionResistancePersonnage(const unsigned int nbResistanceBonus);


void afficherBonusNouveauLvlPersonnage(void);
unsigned int choisirBonusNouveauLvlPersonnage(void);
void ajouterBonusNouveauLvlPersonnage(const unsigned int choixJoueurNouveauLvl);
void bonusNouveauLvlPersonnage(void);
void ajouterLvlPersonnage(void);


void verifierSiNouveauLvlPersonnage(void);


void recupererEXPEnnemiMortPersonnage(void);

/* ----- Declaration ----- */

Personnage personnage;

#endif
