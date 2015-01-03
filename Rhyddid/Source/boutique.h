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

/* Calcule le prix de l'achat pour x potion du type y et du niveau z indique en parametre */
unsigned int calculerPrixPotionAcheterBoutique(
	const unsigned int quantite, const char *typePotion, unsigned int niveauPotion);
/* Retourne 1 si le joueur peut acheter une commande de prix prixCommande et 0 sinon */
unsigned int peutAcheterCommande(const unsigned int prixCommande);
/* Execute une commande indiquee en parametre lors d'un achat dans la boutique */
void executerCommandeAcheterBoutique(const char *commande);
/* Affiche les prix des potions de la categorie achat de la boutique */
void afficherPrixPotionBoutique(void);
/* Categorie achat de la boutique */
void acheterBoutique(void);


/* Demande et renvoie l'index du tresor que le joueur souhaite vendre */
int demanderObjetAvendre(void);
/* Categorie vente de la boutique */
void vendreBoutique(void);


/* Sort de la boutique */
void sortirBoutique(void);


/* Boutique */
void boutique(void);

/* ----- Declaration ----- */


#endif
