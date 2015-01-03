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

/* Calcule le prix de l'achat pour x potion du type y et du niveau z indique en parametre */
unsigned int calculerPrixPotionAcheterBoutique(
	const unsigned int quantite, const char *typePotion, unsigned int niveauPotion)
{
	/* Tableau contenant les prix de chaque potion pour chaque niveau */
	static const unsigned int prix[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{PRIX_POTION_SANTE_1, 		PRIX_POTION_SANTE_2}, 
		{PRIX_POTION_FORCE_1, 		PRIX_POTION_FORCE_2}, 
		{PRIX_POTION_RESISTANCE_1, 	PRIX_POTION_RESISTANCE_2}
	};
	
	/* On retourne le prix, que l'on calcule en multipliant le prix de la potion typePotion
	de niveau niveauPotion par la quantite */
	return quantite * prix[recupererTypePotion(typePotion)][--niveauPotion];
}

/* Retourne 1 si le joueur peut acheter une commande de prix prixCommande et 0 sinon */
unsigned int peutAcheterCommande(const unsigned int prixCommande)
{
	/* Si on a pas assez d'argent */
	if(inventaire.tek.nbTek < prixCommande)
	{
		/* On affiche un message d'erreur */
		printf("\nVous n'avez pas assez d'argent !\n");
		printf("Vous n'avez que %d tek !\n", inventaire.tek.nbTek);

		appuyezEntree("\nAppuyez sur ENTREE pour continuer vos achats");

		/* On retourne 0 */
		return 0;
	}
	/* Sinon */
	else
	{
		/* On affiche un message indiquant la depense */

		printf("Vous avez depense %d tek.\n", prixCommande);
		printf("Il vous reste %d tek !\n", inventaire.tek.nbTek);

		appuyezEntree("\nAppuyez sur ENTREE pour continuer vos achats");

		/* On retourne 1 */
		return 1;
	}
}

/* Execute une commande indiquee en parametre lors d'un achat dans la boutique */
void executerCommandeAcheterBoutique(const char *commande)
{
	char typePotion[TAILLE_MAX];
	unsigned int quantitePotion, niveauPotion;
	unsigned int prixCommande;
	unsigned int choixJoueur;

	/* Si la commande est -1 (le joueur veut revenir a la boutique) on retourne a la boutique */
	if(strcmp(commande, "-1") == 0)
		boutique();
	/* Sinon si on peut lire la quantite, le type de la potion et son niveau (commande correcte) */
	else if(sscanf(commande, "%d %s %d", &quantitePotion, typePotion, &niveauPotion) == 3)
	{
		/* On formate le nom de la potion entree pour que le joueur puisse entrer de n'importe
		quelle forme le nom de la potion (Sante, sante, SaNtE etc.) */
		formaterNomPotion(typePotion);

		/* On affiche la commande */
		printf("Vous souhaitez donc acheter %d potion(s) de %s de niveau %d.\n", quantitePotion, 
		typePotion, niveauPotion);

		/* On calcule le prix de la commande */
		prixCommande = calculerPrixPotionAcheterBoutique(quantitePotion, typePotion, 
		niveauPotion);

		/* On affiche le prix */
		printf("Ca vous fera %d tek.\n", prixCommande);
		/* On demande si le joueur est sur de faire l'achat */
		choixJoueur = demanderConfirmation("Etes vous sur de vouloir faire cet achat ? (0/1)", 
		SEPARATION);

		/* Si le joueur veut effectuer l'achat */
		if(choixJoueur == OUI)
		{
			/* On lui enleve le prix de la commande, si le joueur a assez d'argent on lui ajoute
			sa commande dans son inventaire */
			if(peutAcheterCommande(prixCommande))
			{
				enleverTekInventaire(prixCommande);
				ajouterPotionInventaire(quantitePotion, recupererTypePotion(typePotion), niveauPotion);
			}
		}
		/* Si le joueur ne veut pas effectuer l'achat, on le redirige juste vers la categorie
		achat de la boutique */

		/* On retourne dans la categorie achat de la boutique */
		acheterBoutique();
	}
	/* Sinon c'est une commande incorrecte */
	else
	{
		/* On affiche un message d'erreur, on attend un certain temps et on retourne dans la 
		categorie achat de la boutique */
		printf("Veuillez entrer une commande correcte !\n");
		attendre(1.2);
		acheterBoutique();
	}
}

/* Affiche les prix des potions de la categorie achat de la boutique */
void afficherPrixPotionBoutique(void)
{
	/* On affiche les prix des potions */
	printf("Voici mes prix !\n\n");
	printf("\t- 1 potion de sante I = %d tek\n", PRIX_POTION_SANTE_1);
	printf("\t- 1 potion de force I = %d tek\n", PRIX_POTION_FORCE_1);
	printf("\t- 1 potion de resistance I = %d tek\n\n", PRIX_POTION_RESISTANCE_1);

	printf("\t- 1 potion de sante II = %d tek\n", PRIX_POTION_SANTE_2);
	printf("\t- 1 potion de force II = %d tek\n", PRIX_POTION_FORCE_2);
	printf("\t- 1 potion de resistance II = %d tek\n\n", PRIX_POTION_RESISTANCE_2);
}

/* Categorie achat de la boutique */
void acheterBoutique(void)
{
	char commande[TAILLE_MAX];

	effacer();
	titre("Boutique", VERT);

	/* On affiche les explications pour la categorie achat de la boutique */
	lireEtAfficher("Boutique/Texte_Explication_Potion.txt");

	/* On affiche les prix */
	afficherPrixPotionBoutique();

	/* On lit la commande du joueur */
	printf("Que souhaitez-vous faire ? (-1 pour revenir dans la boutique)\n\n");
	printf("> ");
	lire(stdin, commande);

	/* On execute la commande du joueur */
	executerCommandeAcheterBoutique(commande);
}

/* Demande et renvoie l'index du tresor que le joueur souhaite vendre */
int demanderObjetAvendre(void)
{
	compteur indexTresor;
	int choixJoueur;

	/* On demande ce que le joueur veut vendre et on affiche tous ses tresors */

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

	/* On lit le choix du joueur */

	choixJoueur = choisirMenu(inventaire.tresorActuel + 1);

	/* Si il veut revenir en arriere ou quitter, on le redirige vers la boutique et on 
	retourne -1 */
	if(choixJoueur == REVENIR_ARRIERE || choixJoueur == QUITTER)
	{
		boutique();
		return -1;
	}
	/* Sinon on retourne l'index du tresor qu'il veut vendre (choixJoueur - 1) */
	else
		return choixJoueur - 1;
}

/* Categorie vente de la boutique */
void vendreBoutique(void)
{
	unsigned int choixJoueur;
	int indexTresor;

	effacer();
	titre("Boutique", VERT);

	/* Si le joueur a des tresors a vendre */
	if(joueurPossedeTresor())
	{
		/* On recupere l'index du tresor que le joueur souhaite vendre */
		indexTresor = demanderObjetAvendre();

		if(indexTresor != -1)
		{
			/* On demande la confirmation de la vente */
			choixJoueur = demanderConfirmation("Etes vous sur de vouloir vendre cet objet ? (0/1)", 
			SEPARATION);

			/* Si le joueur veut */
			if(choixJoueur == OUI)
			{
				/* On vend le tresor */
				vendreTresor(indexTresor);
				appuyezEntree("Appuyez sur ENTREE pour continuer vos ventes");
			}
			/* Si le joueur ne veut pas vendre, on le redirige simplement dans la categorie vente
			de la boutique*/


			/* On revient a la categorie vente de la boutique */
			vendreBoutique();
		}
	}
	/* Sinon le joueur n'a aucun tresor */
	else
	{
		/* On affiche qu'il n'a rien a vendre et on le redirige vers la boutique */

		printf("Vous n'avez rien a vendre ! :'(\n");
		appuyezEntree("Appuyez sur ENTREE pour revenir a la boutique");

		boutique();
	}
}

/* Sort de la boutique */
void sortirBoutique(void)
{
	/* On affiche au revoir et on quitte la boutique */

	separationTexte();
	printf("Au revoir ! :)\n");
	appuyezEntree("Appuyez sur ENTREE pour sortir de la boutique");
}

/* Boutique */
void boutique(void)
{
	Menu menu;

	effacer();
	titre("Boutique", VERT);

	/* On affiche l'ASCII Art du marchand de la boutique */
	lireEtAfficher("ASCII_Art/ASCII_Art_Marchand_Boutique.txt");
	
	printf("\n\n");

	/* On affiche le texte de presentation du marchant de la boutique */
	lireEtAfficher("Boutique/Texte_Presentation_Marchand.txt");

	/* On affiche le nombre de tek du joueur */
	printf("Vous avez %d tek ;)\n", inventaire.tek.nbTek);

	/* 
	On cree un menu : 
		- Acheter des potions
		- Vendre des tresors
		- Sortir de la boutique

	Puis on demande ce que le joueur veut faire */
		
	menuNouveau(&menu);

	menuAjouter(&menu, acheterBoutique, "Acheter des potions");
	menuAjouter(&menu, vendreBoutique, "Vendre des tresors");
	menuAjouter(&menu, sortirBoutique, "Sortir de la boutique");

	menuChoisirSansOperationPossible(&menu, "Que souhaitez-vous faire ?");
}
