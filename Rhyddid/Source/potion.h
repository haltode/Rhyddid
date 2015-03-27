#ifndef POTION_H
#define POTION_H

/* potion.c/potion.h : permet de gerer les potions */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define NB_NIVEAU_POTION 2
#define NB_POTION 3

#define NB_VIE_POTION_SANTE_NIVEAU_1 4
#define NB_VIE_POTION_SANTE_NIVEAU_2 10

#define NB_FORCE_POTION_FORCE_NIVEAU_1 4
#define NB_FORCE_POTION_FORCE_NIVEAU_2 8

#define NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_1 3
#define NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_2 7

#define CHANCE_MAX_POTION_NIVEAU_2 4

#define CHANCE_MAX_POTION_SANTE 3
#define CHANCE_MAX_POTION_FORCE 2

/* ----- Structure + Enumeration ----- */

enum niveauPotion
{
	NIVEAU_1 = 0, 
	NIVEAU_2 = 1
};

enum typePotion
{
	SANTE = 0, 
	FORCE = 1,
	RESISTANCE = 2,
	ERREUR_POTION = 3
};

enum erreurPotion
{
	/* 1 correspond a aucune erreur */
	AUCUNE_POTION = 2, 
	NON_UTILISABLE = 3, 
	VIE_MAXIMUM = 4
};

typedef struct Potion Potion;
struct Potion
{
	unsigned int nbPotionForce1;
	unsigned int nbPotionForce2;

	int nbTourPotionActive;
	unsigned int nbBonus;
};

/* ----- Prototype ----- */

void initialiserPotionInventaire(void);
void chargerPotionInventaire(void);
void sauvegarderPotionInventaire(void);
void afficherPotionInventaire(void);


void afficherPotionIndividuelleInventaire(const char *nomPotion, 
	const unsigned int nbPotionNiveau1, const unsigned int nbPotionNiveau2);
void ajouterPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion);
void enleverPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion);


unsigned int peutUtiliserPotion(const unsigned int typePotion, const unsigned int niveauPotion);
void afficherErreurPotion(const unsigned int typeErreurPotion);
void utiliserPotion(const char toucheEntree, const unsigned int typePotion, 
	void (*pointeurFonctionEffetPotion)(const unsigned int effetPotion), 
	const unsigned int effetNiveau1, const unsigned int effetNiveau2);
void utiliserPotionSante(const char toucheEntree);
void utiliserPotionForce(const char toucheEntree);
void utiliserPotionResistance(const char toucheEntree);


void initialiserNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion);
unsigned int recupererNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion);
void decrementezNbTourPotionActive(void);


void genererPotionCoffre(unsigned int *typePotion, unsigned int *niveauPotion);
void afficherPotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion);
void prendrePotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion);


void formaterNomPotion(char *typePotion);


unsigned int recupererTypePotion(const char *nomPotion);

/* ----- Declaration ----- */

#endif
