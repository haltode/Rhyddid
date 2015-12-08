# Rhyddid

*Date du projet : Octobre 2013 à Janvier 2014*

Rhyddid est un rogue-like, dans lequel vous incarnez un personnage dont vous choisissez les caractéristiques grâce aux différentes races et multiples métiers. Vous traversez les niveaux, en combattant et en découvrant des objets (armes, armures et trésors). Chaque niveau possède une clé pour accéder au niveau suivant, cette clé se trouve aléatoirement sur le niveau bien gardée par l’un des ennemis. Chaque niveau est composé de neuf salles, toutes différentes et contenant des coffres, des ennemis et même une caverne si vous êtes chanceux...

Lorsque vous passez un niveau, vous pouvez accéder à la boutique pour vendre vos trésors, gagner de l'argent et aussi acheter des potions.

Le jeu contient 6 races, 15 métiers, 35 armes, 30 armures, 3 types de potions de deux niveaux différents, et 50 trésors.

## Se déplacer dans les menus

Pour vous déplacer dans les menus il faut utiliser les chiffres, pour revenir en arrière tapez -1, pour quitter le jeu tapez 0.

### Menu principal

Le menu principal est composé de quatre sous-menus :

- **Sauvegarde** : permet de gérer vos sauvegardes (créer, charger, supprimer).
- **Highscore** : affiche le top 10 de vos performances.
- **Aide**
- **Quitter**

## Nouvelle partie

Pour créer une nouvelle partie, sélectionnez un espace de sauvegarde vide, entrez un nom de personnage, choisissez la race de votre nouveau personnage (vous pouvez aussi visualiser les races, ce qui vous permet de voir ses caractéristiques ainsi qu'un ASCII Art), puis choisissez un métier (chaque métier vous apporte des compétences supplémentaires à votre personnage). Un texte vous expliquant l'histoire de Rhyddid apparaît.

## Jeu

Après avoir chargé ou créé une partie, vous verrez le jeu. En haut à gauche se situe la carte du niveau (le *E* indique l’entrée, le *S* indique la sortie, le *X* indique votre position), la carte est composée de neuf carrés représentant chacun une salle. A droite de la carte se trouve le résumé de votre personnage indiquant le niveau actuel où vous vous trouvez, son Lvl, son EXP, sa santé, ses dégâts, sa protection.

## Touches

Voici les différentes touches de Rhyddid :

| Touche           | Action                  |
| ------           | ------                  |
| <kbd>z</kbd>     | haut                    |
| <kbd>s</kbd>     | bas                     |
| <kbd>q</kbd>     | gauche                  |
| <kbd>d</kbd>     | droite                  |
| <kbd>n</kbd>     | sauvegarder et quitter  |
| <kbd>m</kbd>     | sauvegarder             |
| <kbd>echap</kbd> | pause                   |
| <kbd>e</kbd>     | inventaire              |
| <kbd>t</kbd>     | attaque l'ennemi        |
| <kbd>h</kbd>     | potion de santé I       |
| <kbd>j</kbd>     | potion de force I       |
| <kbd>k</kbd>     | potion de résistance I  |
| <kbd>H</kbd>     | potion de santé II      |
| <kbd>J</kbd>     | potion de force II      |
| <kbd>K</kbd>     | potion de résistance II |

## Boutique

Une boutique est mise à votre disposition, vous pouvez y accéder après avoir passé la porte de sortie du niveau. La boutique vous permet d'acheter des potions et de vendre des trésors contre des teks (la monnaie de Rhyddid).

Voici les prix des potions :

| Potion                  | Prix    |
| ------                  | ----    |
| potion de santé I       | 30 teks |
| potion de force I       | 20 teks |
| potion de résistance I  | 20 teks |
| potion de santé II      | 70 teks |
| potion de force II      | 60 teks |
| potion de résistance II | 60 teks |

## Caverne

Il se peut que vous trouviez une caverne dans un niveau, celle-ci contient soit des coffres, soit beaucoup d'ennemis...

Voici a quoi elle pourrait ressembler :

```
   _| |_  
 `/     \'
  |     | 
  |     | 
 ,\_____/.
```

## Ennemi

Les ennemis ont une IA qui évolue (en fonction du niveau dans lequel vous vous trouvez). Chaque ennemi a des caractéristiques différents (santé, dégât, protection), à partir d'un certain rayon de distance l'ennemi vous "focus", et vous suit de manière à vous tuer pendant un certain nombre de tour, puis il arrête de vous suivre. Un ennemi choisi aléatoirement dans tout le niveau porte la clé de fin de niveau, vous devez le tuer pour avoir la clé.

## Combat

Pour attaquer un ennemi utilisez la touche <kbd>t</kbd>. Lorsque vous attaquez un ennemi la carte en haut à gauche se transforme en ASCII Art de l'ennemi et vous indique ses caractéristiques (santé, dégât, protection).

## Arme

Il existe 35 armes dans le jeu. Une arme se compose d'un nom, d'un nombre de dégât, et de sa portée d'attaque.

## Armure

Il existe 30 armures dans le jeu. Une armure se compose d'un nom, et de sa protection.

## Potions

Il existe 3 types de potions : potion de santé, de force, et de résistance. Chacune affecte respectivement les caractéristiques du joueur : santé, dégât, protection. Il y a deux niveaux de potions : le niveau I et le niveau II. Voici les effets des potions :

**santé I** -> 4 points de vie  
**santé II** -> 10 points de vie  

**force I** -> 4 points de dégât pendant 5 tours  
**force II** -> 8 points de dégât pendant 10 tours  

**résistance I** -> 3 point de résistance pendant 5 tours  
**résistance II** -> 7 point de résistance pendant 10 tours  

Vous pouvez utiliser une potion uniquement si vous n'êtes pas sous l'effet d'une potion du même type. Cependant, la potion de santé I nécessite d'attendre 3 tours avant de réutiliser une potion de santé, et la potion de santé II nécessite d'attendre 8 tours.

## Trésor

Il existe 50 trésors dans le jeu. Un trésor se compose d'un nom, d'un nombre de tek correspondant au prix du trésor. Vous pouvez vendre vos trésors dans la boutique et ainsi obtenir des teks.

## EXP

L'EXP est donné par un ennemi lorsque vous le tuez, au bout de 100 EXP vous augmentez de Lvl ce qui vous permet d’améliorer une de vos caractéristiques (santé, dégât, protection).

## Coffre

Les coffres sont placés aléatoirement dans les salles, ils peuvent contenir des armes, des armures, des teks, des trésors, des potions. Ils peuvent être vides, ou même piégés et dans ce cas un ennemi apparaîtra.

## Inventaire

Votre inventaire est composé d'une arme, d'une armure, de potions, de tek, et de 5 trésors au maximum.

## Mort

Lorsque vous mourrez, vos statistiques sont conservées dans le highscore, mais votre partie est supprimée définitivement.
