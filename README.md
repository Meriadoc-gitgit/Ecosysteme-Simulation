> Réalisé par Vu Hoang Thuy Duong <br>
Numéro d'étudiant : 21110221 <br>
Groupe : 7 <br>

# Ecosystème
## Prologue
Ce projet vise à réaliser une <strong>simulation simple de l'écosystème</strong>, qui consiste principalement à nous faire comprendre mieux les structures et les listes chainées en C. <br>
La simulation aura lieu sur un terrain de dimension 20x50, dont les agents proviennent de 2 types : prédateurs et proies. <br>
* Au cas où il n'y a qu'un proie dans la case, l'affichage sera '*'
* S'il n'y a qu'un prédateur dans la case, l'affichage deviendra 'O' 
* Et si tous lé 2 sont dans la même case, l'affichage sera '@'
<p>Ce projet est réalisé dans le cadre d'un projet de la 2ème et 3ème semaine, contribuant 25% de la note totale de l'UE 2IN018 - C avancé que propose Sorbonne Université durant le premier semestre en L2 Informatique. <br>

## struct Animal 
### Définition de structure
```
typedef struct _animal {
  int x;
  int y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
} Animal;
```
### D'autres variables 
```
#define SIZE_X 20
#define SIZE_Y 50

#define p_ch_dir 0.01
#define p_reproduce_proie 0.4
#define p_reproduce_predateur 0.5
#define temps_repousse_herbe -15 
```
### Méthodes
Pour créer un animal 
```
Animal *creer_animal(int x, int y, float energie);
```
Pour ajouter un animal en tête de la liste chainée
```
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);
```
Pour compter le nombre d'animaux dans la liste
* de facon récursive :
```
unsigned int compte_animal_rec(Animal *la);
```
* de facon itérative : 
```
unsigned int compte_animal_it(Animal *la);
```
Pour ajouter dynamiquement un animal dans la liste
```
void ajouter_animal(int x, int y, float energie, Animal **liste_animal);
```
Pour enlever un animal de la liste

```
void enlever_animal(Animal **liste, Animal *animal);
```
Pour libérer toute une liste 
```
Animal* liberer_liste_animaux(Animal *liste);
```
Faire afficher l'écosystème 
```
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur);
```
Faire bouger les animaux dans une liste 
```
void bouger_animaux(Animal *la);
```
Faire reproduire la liste d'animaux
```
void reproduce(Animal **liste_animal, float p_reproduce);
```
Vérifier s'il y a un animal à la position [x,y] et le retourner comme résultat de fonction
```
Animal *animal_en_XY(Animal *l, int x, int y);
```
Rafraichissement des animaux<br>
3 étapes principales : <br>
* faire bouger les animaux
* baisser l'énergie des animaux (sauf s'il y a des algues au même coordonnée qu'animal, son énergie cumule une même quantité que celle des algues, et on initialise la quantité des algues à temp_repousse_algue)
* faire reprodure les animaux
1. Pour les proies : 
```
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]);
```
2. Pour les prédateurs : 
```
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);
```
3. Pour les herbes : 
```
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);
```
#### Pour la gestion des fichiers
Écriture des fichiers : 
```
void ecrire_ecosys(const char *nom_fichier, Animal *liste_pred, Animal *liste_proie); 
```
Lire les fichiers : 
```
void lire_ecosys(const char *nom_fichier, Animal **liste_pred, Animal **liste_proie); 
```
## Remerciement
Je tiens à exprimer mes sincères remerciements à mes professeurs, notamment les chargés du groupe 7 Informatique pour des lecons de C avancé qui m'intéressent vraiment et qui m'ont donné une telle motivation depuis le début des cours. <br>
Et merci beaucoup à vous tous à avoir jeté un coup d'oeil sur ce projet simple de simulation d'écosystème :) <br>
Tout est réalisé dans le cadre d'un projet de la 2ème et 3ème semaine, contribuant 25% de la note totale de l'UE 2IN018 - C avancé que propose Sorbonne Université durant le premier semestre en L2 Informatique. <br>
<p align="center"><img src="IMG_4988.JPG"></p>