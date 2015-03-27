#include <stdio.h>

#include "mourrir.h"
#include "fonctionsUtiles.h"
#include "effacer.h"
#include "couleur.h"
#include "highscore.h"
#include "personnage.h"
#include "supprimerSauvegarde.h"
#include "menuPrincipal.h"
#include "quitter.h"
#include "menu.h"

void mourrir(void)
{
	Menu menu;

	menuNouveau(&menu);

	menuAjouter(&menu, highscore, "Highscore");
	menuAjouter(&menu, menuPrincipal, "Menu principal");
	menuAjouter(&menu, quitter, "Quitter");

	effacer();
	titre("Rhyddid", VERT);

	couleur(ROUGE);
	lireEtAfficher("ASCII_Art/ASCII_Art_Mourrir.txt");
	couleur(BLANC);

	printf("Vous venez de mourrir... apres avoir passe %d niveau !\n\n", personnage.niveauActuel);

	printf("Lorsque vous mourrez, vous ne pouvez plus revenir dans le jeu !\n");
	printf("Votre score est cependant conserve dans le Highscore.\n\n");

	ajouterHighscore();

	supprimerSauvegardePartie(personnage.nom);

	attendre(1);

	appuyezEntree("Appuyez sur ENTREE pour continuer ...");

	menuChoisirSansOperationPossible(&menu, "Que souhaitez-vous faire ?");
}
