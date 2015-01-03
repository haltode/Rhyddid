#ifndef TEK_H
#define TEK_H

/* tek.c/tek.h : permet de gerer l'argent du jeu (tek) */

/* ----- A inclure ----- */

/* ----- Define ----- */

#define CHANCE_MAX_NB_TEK_NIVEAU_1 2
#define CHANCE_MAX_NB_TEK_NIVEAU_2 4
#define CHANCE_MAX_NB_TEK_NIVEAU_3 6
#define CHANCE_MAX_NB_TEK_NIVEAU_4 10

#define NB_TEK_NIVEAU_1 20
#define NB_TEK_NIVEAU_2 50
#define NB_TEK_NIVEAU_3 70
#define NB_TEK_NIVEAU_4 120

/* ----- Structure + Enumeration ----- */

typedef struct Coffre Coffre;

typedef struct Tek Tek;
struct Tek
{
	unsigned int nbTek;
};

/* ----- Prototype ----- */

/* Initialise les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void initialiserTekInventaire(void);
/* Charge les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void chargerTekInventaire(void);
/* Sauvegarde les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void sauvegarderTekInventaire(void);
/* Affiche la section Tek de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherTekInventaire(void);


/* Ajoute nbTek a l'inventaire du joueur */
void ajouterTekInventaire(const unsigned int nbTek);
/* Enleve nbTek a l'inventaire du joueur */
void enleverTekInventaire(const unsigned int nbTek);

/* Genere des teks au hasard situes dans un coffre */
void genererTekCoffre(Tek *tek);
/* Affiche la section Tek d'un coffre lorsqu'on l'ouvre */
void afficherTekCoffre(const Coffre *coffre);
/* Prend les teks situes dans le coffre que le joueur vient d'ouvrir (donne en parametre) */
void prendreTekCoffre(const Tek *tek);

/* ----- Declaration ----- */

#endif
