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

/* Initialise les potions de l'inventaire dans le fichier Inventaire/potion.txt */
void initialiserPotionInventaire(void);
/* Charge les potions de l'inventaire grace au fichier Inventaire/potion.txt */
void chargerPotionInventaire(void);
/* Sauvegarde oles potions de l'inventaire dans le fichier Inventaire/potion.txt */
void sauvegarderPotionInventaire(void);
/* Affiche la partie potion de l'inventaire */
void afficherPotionInventaire(void);


/* Affiche une potion individuellement de l'inventaire */
void afficherPotionIndividuelleInventaire(const char *nomPotion, 
	const unsigned int nbPotionNiveau1, const unsigned int nbPotionNiveau2);
/* Ajoute quantitePotion de potion de type nomPotion de niveau niveauPotion dans l'inventaire
du joueur */
void ajouterPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion);
	/* Enleve quantitePotion potion de type typePotion de niveau niveauPotion de l'inventaire du
joueur */
void enleverPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion);


/* Renvoie 1 si le joueur peut utiliser la potion typePotion de niveau niveauPotion et une 
erreur sinon */
unsigned int peutUtiliserPotion(const unsigned int typePotion, const unsigned int niveauPotion);
/* Affiche la raison de l'erreur typeErreurPotion */
void afficherErreurPotion(const unsigned int typeErreurPotion);
/* Utilise une potion */
void utiliserPotion(const char toucheEntree, const unsigned int typePotion, 
	void (*pointeurFonctionEffetPotion)(const unsigned int effetPotion), 
	const unsigned int effetNiveau1, const unsigned int effetNiveau2);
	/* Utilise une potion de sante */
void utiliserPotionSante(const char toucheEntree);
/* Utilise une potion de force */
void utiliserPotionForce(const char toucheEntree);
/* Utilise une potion de resistance */
void utiliserPotionResistance(const char toucheEntree);


/* Initialise le nombre de tour durant lesquels la potion typePotion de niveau niveauPotion est
active */
void initialiserNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion);
/* Renvoie le nombre de tour durant lesquels la potion typePotion de niveau niveauPotion est
active */
unsigned int recupererNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion);
/* Decremente le nombre de tour ou les potions sont actives */
void decrementezNbTourPotionActive(void);


/* Genere une potion dans un coffre et place le resultat dans typePotion et niveauPotion */
void genererPotionCoffre(unsigned int *typePotion, unsigned int *niveauPotion);
/* Affiche la potion dans un coffre */
void afficherPotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion);
/* Prend la potion d'un coffre */
void prendrePotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion);


/* Formate le nom d'une potion de maniere correcte (SaNtE -> sante) */
void formaterNomPotion(char *typePotion);


/* Retourne le type de la potion grace a son nom donne en parametre */
unsigned int recupererTypePotion(const char *nomPotion);

/* ----- Declaration ----- */

#endif
