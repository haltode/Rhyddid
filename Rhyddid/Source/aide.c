#include <stdio.h>

#include "aide.h"
#include "effacer.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "menuPrincipal.h"

void afficherElementLegendeAide(const char caractere, 
	const unsigned int couleurCaractere, const char *message)
{
	printf("\t");
	colorationCaractere(caractere, couleurCaractere);
	printf(" : %s\n", message);
}

void afficherLegendeAide(void)
{
	printf("Legende : \n\n");

	afficherElementLegendeAide('@', VERT, "Joueur");
	afficherElementLegendeAide('X', ROUGE, "Ennemi");

	afficherElementLegendeAide('#', BLEU, "Mur de la salle");
	afficherElementLegendeAide('.', BLANC, "Endroit inacessible");
	afficherElementLegendeAide(' ', BLANC, "Sol");
	afficherElementLegendeAide('C', JAUNE, "Coffre");
	afficherElementLegendeAide('|', VIOLET, "Obstacle");
	afficherElementLegendeAide('-', VIOLET, "Obstacle");

	afficherElementLegendeAide('P', CYAN, "Porte");
	afficherElementLegendeAide('E', CYAN, "Entree du niveau");
	afficherElementLegendeAide('S', CYAN, "Sortie du niveau");

}

void afficherAide(void)
{
	afficherLegendeAide();

	printf("Aide : \n\n");
	lireEtAfficher("Aide/Texte_Aide_Rhyddid.txt");
}

void aide(void)
{
	effacer();
	titre("Aide", VERT);

	afficherAide();

	appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal...");

	menuPrincipal();
}
