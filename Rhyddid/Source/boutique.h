#ifndef BOUTIQUE_H
#define BOUTIQUE_H

/* boutique.c/boutique.h : permet de gerer la boutique (achat, vente) */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define PRIX_POTION_SANTE_1 30
#define PRIX_POTION_FORCE_1 20
#define PRIX_POTION_RESISTANCE_1 20

#define PRIX_POTION_SANTE_2 70
#define PRIX_POTION_FORCE_2 60
#define PRIX_POTION_RESISTANCE_2 60

/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

unsigned int calculerPrixPotionAcheterBoutique(
	const unsigned int quantite, const char *typePotion, unsigned int niveauPotion);
unsigned int peutAcheterCommande(const unsigned int prixCommande);
void executerCommandeAcheterBoutique(const char *commande);
void afficherPrixPotionBoutique(void);
void acheterBoutique(void);


int demanderObjetAvendre(void);
void vendreBoutique(void);


void sortirBoutique(void);


void boutique(void);

/* ----- Declaration ----- */


#endif
