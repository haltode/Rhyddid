#ifndef MENU_H
#define MENU_H

/* menu.c/menu.h : permet de gerer les menus */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define TAILLE_MAX_COMPOSANTS 100
#define TAILLE_MAX_CARACTERE 300

/* ----- Structure + Enumeration ----- */

typedef void(*callback)(void);

typedef struct Menu Menu;
struct Menu
{
	/* Tableau contenant tous les pointeurs sur fonction des composants du menu */
	callback nomFonction[TAILLE_MAX_COMPOSANTS];
	/* Tableau contenant tous les noms des composants du menu */
	char nomComposant[TAILLE_MAX_COMPOSANTS][TAILLE_MAX_CARACTERE];
	/* Variable qui contient le nombre de composant du menu */
	unsigned int nbComposant;
};

/* ----- Prototype ----- */

/* Initialise le menu donne en parametre */
void menuNouveau(Menu *menu);
/* Affiche le menu donne en paramtre */
void menuAfficher(const Menu *menu);
/* Ajoute un element donne en parametre au menu donne en parametre */
void menuAjouter(Menu *menu, const callback pointeurFonction, const char *nom);
/* Enleve un element donne en parametre au menu donne en parametre */
void menuEnlever(Menu *menu, const char *nom);
/* Execute une action du menu donne en parametre */
void menuAction(const Menu *menu, const unsigned int choixAction);
/* Permet de choisir un element du menu donne en parametre */
int menuChoisir(const Menu *menu, const char *messageAvantMenu);
/* Permet de choisir un element du menu donne en parametre sans pouvoir retourner en 
arriere ou de quitter le jeu et execute le choix du joueur */
void menuChoisirSansOperationPossible(const Menu *menu, const char *messageAvantMenu);

/* ----- Declaration ----- */

#endif
