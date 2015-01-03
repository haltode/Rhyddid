#include <stdio.h>

#include "sortie.h"
#include "effacer.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "inventaire.h"
#include "personnage.h"
#include "boutique.h"
#include "supprimerSauvegarde.h"
#include "jeu.h"

/* Affiche un texte lorsque le joueur se trouve sur la porte de la sortie */
void afficherTextePorteSortie(void)
{
	effacer();
	titre("Porte de sortie", VERT);

	/* Si le joueur possede la cle de fin de niveau */
	if(inventaire.possedeCleFinNiveau)
	{
		unsigned int choixJoueur;

		/* On affiche un texte indiquant le passage du prochain niveau */
		lireEtAfficher("Sortie/Texte_Porte_Sortie_Cle.txt");

		/* On demande si le joueur veut faire un tour a la boutique avant de passer au prochain
		niveau */
		choixJoueur = demanderConfirmation("Voulez-vous aller dans la boutique ? (0/1)", SEPARATION);

		/* S'il veut */
		if(choixJoueur == OUI)
			/* On appelle la fonction boutique */
			boutique();

		appuyezEntree("\nAppuyez sur ENTREE pour acceder au prochain niveau");

		/* On enleve la cle de fin de niveau de l'inventaire du joueur */
		inventaire.possedeCleFinNiveau = 0;
		/* On incremente de 1 la variable niveauActuel du joueur pour indiquer le passage au 
		prochain niveau */
		++(personnage.niveauActuel);

		/* On sauvegarde l'inventaire pour que le joueur conserve l'inventaire entre le passage
		de niveau */
		sauvegarderInventaire();

		/* On vide le dossier de sauvegarde sur le niveau (car on va changer de niveau) */
		viderDossierNiveauSauvegarde(personnage.nom);

		/* On relance le jeu */
		jeu();
	}
	/* Sinon */
	else
	{
		/* On affiche un texte indiquant qu'il faut une cle au joueur pour passer la porte */
		lireEtAfficher("Sortie/Texte_Porte_Sortie.txt");
		
		appuyezEntree("\nAppuyez sur ENTREE pour continuer");
	}
}
