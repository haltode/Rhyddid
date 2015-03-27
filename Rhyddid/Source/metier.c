#include <stdio.h>
#include <string.h>

#include "metier.h"
#include "menu.h"
#include "couleur.h"
#include "effacer.h"
#include "fonctionsUtiles.h"
#include "personnage.h"

void demanderMetierNouveauPersonnage(void)
{
	static const Metier baseTypeMetier[NB_METIER] = 
	{
		{"Paysan", 4, 0, 0},
		{"Assassin", 0, 4, 0},
		{"Forgeron", 0, 0, 4},
		{"Laboureur", 3, 1, 0},
		{"Charpentier", 3, 0, 1},
		{"Marchand", 1, 3, 0},
		{"Macon", 0, 3, 1},
		{"Bourreau", 1, 0, 3},
		{"Marechal", 0, 1, 3},
		{"Mineur", 2, 2, 0},
		{"Chevalier", 0, 2, 2},
		{"Alchimiste", 2, 0, 2},
		{"Meunier", 2, 1, 1},
		{"Boulanger", 1, 2, 1},
		{"Boucher", 1, 1, 2}
	};
	unsigned int choixJoueur;

	effacer();
	titre("Nouvelle Partie", VERT);

	printf("Quel metier voulez-vous choisir ?\n\n");
	afficherDifferentMetier();
	choixJoueur = choisirMenuSansOperationPossible(NB_METIER);

	strcpy(personnage.metier, baseTypeMetier[choixJoueur - 1].nomMetier);
	personnage.sante += baseTypeMetier[choixJoueur - 1].sante;
	personnage.protection += baseTypeMetier[choixJoueur - 1].protection;
	personnage.degatParTour += baseTypeMetier[choixJoueur - 1].degatParTour;
}

void afficherDifferentMetier(void)
{
	Menu metier;

	menuNouveau(&metier);

	menuAjouter(&metier, NULL, "Paysan (+4 de sante)");
	menuAjouter(&metier, NULL, "Assassin (+4 de protection)");
	menuAjouter(&metier, NULL, "Forgeron (+4 de degat par tour)");
	menuAjouter(&metier, NULL, "Laboureur (+3 de sante, +1 de protection)");
	menuAjouter(&metier, NULL, "Charpentier (+3 de sante, +1 de degat par tour)");
	menuAjouter(&metier, NULL, "Marchand (+1 de sante, +3 de protection)");
	menuAjouter(&metier, NULL, "Macon (+3 de protection, +1 de degat par tour)");
	menuAjouter(&metier, NULL, "Bourreau (+1 de sante, +3 de degat par tour)");
	menuAjouter(&metier, NULL, "Marechal (+1 de protection, +3 de degat par tour)");
	menuAjouter(&metier, NULL, "Mineur (+2 de sante, +2 de protection)");
	menuAjouter(&metier, NULL, "Chevalier (+2 de protection, +2 de degat par tour)");
	menuAjouter(&metier, NULL, "Alchimiste (+2 de sante, +2 de degat par tour)");
	menuAjouter(&metier, NULL, "Meunier (+2 de sante, +1 de protection, +1 de degat par tour)");
	menuAjouter(&metier, NULL, "Boulanger (+1 de sante, +2 de protection, +1 de degat par tour)");
	menuAjouter(&metier, NULL, "Boucher (+1 de sante, +1 de protection, +2 de degat par tour)");
	
	menuAfficher(&metier);
}
