#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main()
{
    menu();
    return 0;
}
/*
    t_Position *p;
    t_Index *index = creer_index(), *index2 = creer_index();
    t_ListePosition *listeP;
    t_Noeud *noeud;
    int i = 1;
    listeP = creer_liste_positions();
    if (listeP != NULL)
        printf("ok\n ");
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 1, 1, 1));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 1, 2, 1));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 1, 4, 1));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 1, 3, 2));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 2, 1, 1));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 2, 1, 2));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 2, 1, 2));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 2, 1, 3));
    printf("ajouter %d : %d \n", i++, ajouter_position(listeP, 2, 4, 3));

    p = listeP->debut;
    while (p != NULL)
    {
        printf("%d %d %d\n", p->numero_ligne, p->ordre, p->numero_phrase);
        p = p->suivant;
    }
    noeud = creer_noeud("hello", 1, listeP, NULL, NULL);

    ajouter_noeud(index, creer_noeud("0", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("1", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("2", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("3", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("4", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("5", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("6", 2, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("7", 1, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("8", 5, NULL, NULL, NULL));
    ajouter_noeud(index, creer_noeud("9", 3, NULL, NULL, NULL));
    // ajouter_noeud(index, creer_noeud("10", 2, NULL, NULL, NULL));

    // afficher_index(index);
    // int level = level_Noeud(index->racine);
    // printf("level of index = %d \n", level);
    // printf("check equilibre = %d \n", check_Noeud(index->racine));

    t_Noeud *fin = index->racine;
    // fin = Classer_Noeud(index);
    // printf("fin de classer\n");
    if (fin == NULL)
    {
        printf("NULL\n");
    }
    while (fin != NULL)
    {
        printf("%s \n", fin->mot);
        fin = fin->filsDroit;
    }
    t_Noeud *fin2 = NULL, *fin3=NULL;
    fin2 = Classer_Noeud(index);
    // while (fin2 != NULL)
    // {
    //     printf("main %s \n", fin2->mot);
    //     fin2 = fin2->filsDroit;
    // }
    // printf("%s\n",fin2->mot);
    printf("Level = %d\n",level_Noeud(fin2));
    printf("Check = %d\n",check_Noeud(fin2));
    fin2 = equilibrer_Noeud(fin2,0,level_Noeud(fin2)-1);
    printf("Check after = %d\n",check_Noeud(fin2));
    // t_Noeud *p1,*p2,*p3,*min,*max;
    // p1= rechercher_mot(index,"i");
    // printf("rechercher mot: %s \n",p1->mot);
    // min = Minimale(index->racine);
    // printf("Min: %s \n",min->mot);
    // max = Maximale(index->racine);
    // printf("Max: %s \n",max->mot);
    // // p2=Parent_Noeud(index,p1);
    // // printf("parrent: %s \n",p2->mot);
    // p3 = Successeur_Noeud(index,p1);
    // if(p3!=NULL){
    // printf("succeseur: %s \n",p3->mot);
    // }
    // else
    // {
    //     printf("ffffffffff\n");
    // }

    // char *word = malloc(sizeof(char)), c;
    // c = 'a';
    // printf("%d \n", strlen(word));
    // word = make_word(word, c, 1);
    // printf("%s \n", word);
    // printf("%d \n", check_char('a'));
    // free(word);
    // word = NULL;
    return 0;
}
*/