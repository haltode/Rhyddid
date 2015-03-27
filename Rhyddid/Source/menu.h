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
	callback nomFonction[TAILLE_MAX_COMPOSANTS];
	char nomComposant[TAILLE_MAX_COMPOSANTS][TAILLE_MAX_CARACTERE];
	unsigned int nbComposant;
};

/* ----- Prototype ----- */

void menuNouveau(Menu *menu);
void menuAfficher(const Menu *menu);
void menuAjouter(Menu *menu, const callback pointeurFonction, const char *nom);
void menuEnlever(Menu *menu, const char *nom);
void menuAction(const Menu *menu, const unsigned int choixAction);
int menuChoisir(const Menu *menu, const char *messageAvantMenu);
void menuChoisirSansOperationPossible(const Menu *menu, const char *messageAvantMenu);

/* ----- Declaration ----- */

#endif
