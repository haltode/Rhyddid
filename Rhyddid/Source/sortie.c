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

void afficherTextePorteSortie(void)
{
	effacer();
	titre("Porte de sortie", VERT);

	if(inventaire.possedeCleFinNiveau)
	{
		unsigned int choixJoueur;

		lireEtAfficher("Sortie/Texte_Porte_Sortie_Cle.txt");
		choixJoueur = demanderConfirmation("Voulez-vous aller dans la boutique ? (0/1)", SEPARATION);

		if(choixJoueur == OUI)
			boutique();

		appuyezEntree("\nAppuyez sur ENTREE pour acceder au prochain niveau");

		inventaire.possedeCleFinNiveau = 0;
		++(personnage.niveauActuel);

		sauvegarderInventaire();
		viderDossierNiveauSauvegarde(personnage.nom);
		jeu();
	}
	else
	{
		lireEtAfficher("Sortie/Texte_Porte_Sortie.txt");
		appuyezEntree("\nAppuyez sur ENTREE pour continuer");
	}
}
