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

/* Fait mourrir le joueur */
void mourrir(void)
{
	Menu menu;

	/* On cree un menu contenant ce que peut faire le joueur apres sa mort */

	menuNouveau(&menu);

	menuAjouter(&menu, highscore, "Highscore");
	menuAjouter(&menu, menuPrincipal, "Menu principal");
	menuAjouter(&menu, quitter, "Quitter");

	effacer();
	titre("Rhyddid", VERT);

	/* On affiche un ASCII Art representant la mort */

	couleur(ROUGE);
	lireEtAfficher("ASCII_Art/ASCII_Art_Mourrir.txt");
	couleur(BLANC);

	/* On affiche un texte et le nombre de niveau passe par le joueur */

	printf("Vous venez de mourrir... apres avoir passe %d niveau !\n\n", personnage.niveauActuel);

	printf("Lorsque vous mourrez, vous ne pouvez plus revenir dans le jeu !\n");
	printf("Votre score est cependant conserve dans le Highscore.\n\n");

	/* On ajoute au highscore la performance du joueur */
	ajouterHighscore();

	/* On supprime la partie */
	supprimerSauvegardePartie(personnage.nom);

	attendre(1);

	appuyezEntree("Appuyez sur ENTREE pour continuer ...");

	/* On demande au joueur ce qu'il veut faire a partir du menu */
	menuChoisirSansOperationPossible(&menu, "Que souhaitez-vous faire ?");
}
