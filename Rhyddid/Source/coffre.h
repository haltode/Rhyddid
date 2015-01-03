#ifndef COFFRE_H
#define COFFRE_H

/* coffre.c/coffre.h : permet de gerer les coffres et coffres pieges */

/* ----- A inclure ----- */

#include "inventaire.h"

/* ----- Define ----- */

#define CHANCE_MAX_TEK 2
#define CHANCE_MAX_ARMURE 12
#define CHANCE_MAX_ARME 12
#define CHANCE_MAX_TRESOR 10
#define CHANCE_MAX_POTION 7

#define NB_OBJET_COFFRE_MAX 5

#define CHANCE_MAX_COFFRE_PIEGE 15

/* ----- Structure + Enumeration ----- */

typedef struct ObjetCoffre ObjetCoffre;
struct ObjetCoffre
{
	unsigned int estDansCoffre;
	void (*pointeur)(void);
};

typedef struct Coffre Coffre;
struct Coffre
{
	Inventaire inventaire;

	unsigned int tek;
	unsigned int armure;
	unsigned int arme;
	unsigned int tresor;
	unsigned int potion;

	unsigned int typePotion;
	unsigned int niveauPotion;
};


/* ----- Prototype ----- */

/* Place aleatoirement les coffres dans la salle indexSalle du niveau */
void placerCoffreAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbCoffre, const unsigned int estCaverne);
	

/* Initialise le contenu du coffre donne en parametre */
void initialiserContenuCoffre(Coffre *coffre);
/* Decide du contenu du coffre donne en parametre */
void deciderContenuCoffre(Coffre *coffre);
/* Remplit le contenu du coffre donne en parametre */
void remplirContenuCoffre(Coffre *coffre);
/* Genenere le contenu du coffre donne en parametre */
void genererContenuCoffre(Coffre *coffre);
/* Affiche le contenu du coffre donne en parametre */
void afficherContenuCoffre(const Coffre *coffre);
/* Prend le contenu du coffre donne en parametre */
void prendreContenuCoffre(const Coffre *coffre);


/* Retourne 1 si le coffre donne en parametre est vide et 0 sinon */
unsigned int estCoffreVide(const Coffre *coffre);


/* Genere un coffre piege */
void coffrePiege(void);


/* Supprime un coffre */
void supprimerCoffre(void);


/* Ouvre un coffre */
void ouvrirCoffre(void);

/* ----- Declaration ----- */

#endif
