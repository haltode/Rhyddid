#include <stdio.h>
#include <string.h>

#include "boutique.h"
#include "effacer.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "menu.h"
#include "potion.h"
#include "tresor.h"
#include "inventaire.h"

unsigned int calculerPrixPotionAcheterBoutique(
	const unsigned int quantite, const char *typePotion, unsigned int niveauPotion)
{
	static const unsigned int prix[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{PRIX_POTION_SANTE_1, 		PRIX_POTION_SANTE_2}, 
		{PRIX_POTION_FORCE_1, 		PRIX_POTION_FORCE_2}, 
		{PRIX_POTION_RESISTANCE_1, 	PRIX_POTION_RESISTANCE_2}
	};
	
	return quantite * prix[recupererTypePotion(typePotion)][--niveauPotion];
}

unsigned int peutAcheterCommande(const unsigned int prixCommande)
{
	if(inventaire.tek.nbTek < prixCommande)
	{
		printf("\nVous n'avez pas assez d'argent !\n");
		printf("Vous n'avez que %d tek !\n", inventaire.tek.nbTek);

		appuyezEntree("\nAppuyez sur ENTREE pour continuer vos achats");

		return 0;
	}
	else
	{
		printf("Vous avez depense %d tek.\n", prixCommande);
		printf("Il vous reste %d tek !\n", inventaire.tek.nbTek);

		appuyezEntree("\nAppuyez sur ENTREE pour continuer vos achats");

		return 1;
	}
}

void executerCommandeAcheterBoutique(const char *commande)
{
	char typePotion[TAILLE_MAX];
	unsigned int quantitePotion, niveauPotion;
	unsigned int prixCommande;
	unsigned int choixJoueur;

	if(strcmp(commande, "-1") == 0)
		boutique();
	else if(sscanf(commande, "%d %s %d", &quantitePotion, typePotion, &niveauPotion) == 3)
	{
		formaterNomPotion(typePotion);

		printf("Vous souhaitez donc acheter %d potion(s) de %s de niveau %d.\n", quantitePotion, 
		typePotion, niveauPotion);

		prixCommande = calculerPrixPotionAcheterBoutique(quantitePotion, typePotion, 
		niveauPotion);

		printf("Ca vous fera %d tek.\n", prixCommande);
		choixJoueur = demanderConfirmation("Etes vous sur de vouloir faire cet achat ? (0/1)", 
		SEPARATION);

		if(choixJoueur == OUI)
		{
			if(peutAcheterCommande(prixCommande))
			{
				enleverTekInventaire(prixCommande);
				ajouterPotionInventaire(quantitePotion, recupererTypePotion(typePotion), niveauPotion);
			}
		}

		acheterBoutique();
	}
	else
	{
		printf("Veuillez entrer une commande correcte !\n");
		attendre(1.2);
		acheterBoutique();
	}
}

void afficherPrixPotionBoutique(void)
{
	printf("Voici mes prix !\n\n");
	printf("\t- 1 potion de sante I = %d tek\n", PRIX_POTION_SANTE_1);
	printf("\t- 1 potion de force I = %d tek\n", PRIX_POTION_FORCE_1);
	printf("\t- 1 potion de resistance I = %d tek\n\n", PRIX_POTION_RESISTANCE_1);

	printf("\t- 1 potion de sante II = %d tek\n", PRIX_POTION_SANTE_2);
	printf("\t- 1 potion de force II = %d tek\n", PRIX_POTION_FORCE_2);
	printf("\t- 1 potion de resistance II = %d tek\n\n", PRIX_POTION_RESISTANCE_2);
}

void acheterBoutique(void)
{
	char commande[TAILLE_MAX];

	effacer();
	titre("Boutique", VERT);

	lireEtAfficher("Boutique/Texte_Explication_Potion.txt");

	afficherPrixPotionBoutique();

	printf("Que souhaitez-vous faire ? (-1 pour revenir dans la boutique)\n\n");
	printf("> ");
	lire(stdin, commande);

	executerCommandeAcheterBoutique(commande);
}

int demanderObjetAvendre(void)
{
	compteur indexTresor;
	int choixJoueur;

	printf("Que souhaitez-vous vendre ?\n\n");

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{	
		if(strcmp(inventaire.tresor[indexTresor].nom, "Rien") != 0)
		{
			printf("\t%d - ", indexTresor + 1);
			afficherTresorIndividuelInventaire(indexTresor);
			putchar('\n');
		}
	}

	putchar('\n');

	choixJoueur = choisirMenu(inventaire.tresorActuel + 1);

	if(choixJoueur == REVENIR_ARRIERE || choixJoueur == QUITTER)
	{
		boutique();
		return -1;
	}
	else
		return choixJoueur - 1;
}

void vendreBoutique(void)
{
	unsigned int choixJoueur;
	int indexTresor;

	effacer();
	titre("Boutique", VERT);

	if(joueurPossedeTresor())
	{
		indexTresor = demanderObjetAvendre();

		if(indexTresor != -1)
		{
			choixJoueur = demanderConfirmation("Etes vous sur de vouloir vendre cet objet ? (0/1)", 
			SEPARATION);

			if(choixJoueur == OUI)
			{
				vendreTresor(indexTresor);
				appuyezEntree("Appuyez sur ENTREE pour continuer vos ventes");
			}

			vendreBoutique();
		}
	}
	else
	{
		printf("Vous n'avez rien a vendre ! :'(\n");
		appuyezEntree("Appuyez sur ENTREE pour revenir a la boutique");

		boutique();
	}
}

void sortirBoutique(void)
{
	separationTexte();
	printf("Au revoir ! :)\n");
	appuyezEntree("Appuyez sur ENTREE pour sortir de la boutique");
}

void boutique(void)
{
	Menu menu;

	effacer();
	titre("Boutique", VERT);

	lireEtAfficher("ASCII_Art/ASCII_Art_Marchand_Boutique.txt");
	
	printf("\n\n");

	lireEtAfficher("Boutique/Texte_Presentation_Marchand.txt");

	printf("Vous avez %d tek ;)\n", inventaire.tek.nbTek);

	menuNouveau(&menu);

	menuAjouter(&menu, acheterBoutique, "Acheter des potions");
	menuAjouter(&menu, vendreBoutique, "Vendre des tresors");
	menuAjouter(&menu, sortirBoutique, "Sortir de la boutique");

	menuChoisirSansOperationPossible(&menu, "Que souhaitez-vous faire ?");
}
