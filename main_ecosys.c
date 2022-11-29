#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


int main(void) {

  srand(time(NULL));

  /* Initialisation de liste proies et liste prédateurs */
    unsigned i=0, j=0; 
    int monde[SIZE_X][SIZE_Y];

    Animal *liste_proie = creer_animal(4, 5, 20);
    Animal *liste_pred = creer_animal(4, 5, 20);
    Animal *a0 = creer_animal(4, 5, 20);

    /* Créer 20 proies aléatoirement */
    while (liste_proie && i<19) {
        ajouter_animal(rand()%20, rand()%50, rand()%100-50, &liste_proie);
        ++i;
    }
    

    /* Créer 20 prédateurs aléatoirement */
    while (liste_pred && j<19) {
        ajouter_animal(rand()%20, rand()%50, rand()%100, &liste_pred);
        ++j;
    }

 
    
    /* Quelques animaux */
    Animal *a1 = creer_animal(4, 5, 30);
    Animal *a2 = creer_animal(12, 23, 50);

    /* Ecrire fichier */
    ecrire_ecosys("ppPreprocess.txt", liste_pred, liste_proie);
    lire_ecosys("ppPreprocess.txt", &liste_pred, &liste_proie);

    /* Affichage */
    afficher_ecosys(liste_proie, liste_pred);

    /* Suppression de quelques animaux */
    enlever_animal(&liste_proie, a0);  

    /* Rafraichissement */
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_pred, &liste_proie);
    rafraichir_monde(monde);

    /* Bouger */
    bouger_animaux(liste_proie);
    bouger_animaux(liste_pred);

    /* Ecrire fichier */
    ecrire_ecosys("ppAlterprocess.txt", liste_pred, liste_proie);

    afficher_ecosys(liste_proie, liste_pred);


    // afficher_ecosys(liste_pred, liste_proie);

    /* Reproduce */
    reproduce(&liste_proie, p_reproduce_proie);
    reproduce(&liste_pred, p_reproduce_predateur);



    afficher_ecosys(liste_proie, liste_pred);

    /* Ecrire fichier */
    ecrire_ecosys("ppRes.txt", liste_pred, liste_proie);


    /* Liberer toute la memoire allouee */
    liste_pred = liberer_liste_animaux(liste_pred);
    liste_proie = liberer_liste_animaux(liste_proie);
    assert(liste_pred==NULL);
    
    /* Ecrire fichier */
    ecrire_ecosys("ppFinal.txt", liste_pred, liste_proie);


  return 0;
}

