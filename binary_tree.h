#ifndef binary_tree_H
#define binary_tree_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct Position{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct Position* suivant;
}t_Position;

typedef struct listePosition{
    t_Position* debut;
    int nb_elements;
}t_ListePosition;

typedef struct Noeud{
    char* mot;
    int nb_occurences;
    t_ListePosition* positions;
    struct Noeud* filsGauche;
    struct Noeud* filsDroit;
}t_Noeud;

typedef struct Phrase{ // new struct
    int serial;
    char* listeMots;
    struct Phrase* suivant;
}t_Phrase;

typedef struct Index{
    t_Noeud* racine;
    t_Phrase* start; // just want to test
    int nb_mots_differents;
    int nb_mots_total;
}t_Index;


//fonctions supplementaires
t_Position* creer_position(int nbligne, int ordre, int nbphrase);

int behide_position(t_Position *pos, int ligne, int ordre, int num_phrase);
int before_position(t_Position *pos, int ligne, int ordre, int num_phrase);

t_Noeud* creer_noeud(char* mot, int num_occurences, t_ListePosition* listeP, t_Noeud* gauche, t_Noeud* droit);

char* strlower(char *s1);

void printListepositions(t_ListePosition *listeP);
void printNoeud(t_Noeud *noeud, char *title);
void printPhrase(t_Phrase *listePhrase, int k);

char *make_word(char *word, char c, int size);
int check_char(char c);
t_Phrase *creerPhrase(int serial, char *sentence);
char *prolong_sentence(char *sentence, char *word);

int level_Noeud(t_Noeud *Noeud);
int check_Noeud(t_Noeud *Noeud);

t_Noeud *Maximale(t_Noeud *Noeud);
t_Noeud *Minimale(t_Noeud *Noeud);
t_Noeud *Parent_Noeud(t_Index *index, t_Noeud *Noeud);
t_Noeud *Successeur_Noeud(t_Index *index, t_Noeud *Noeud);
t_Noeud *Classer_Noeud(t_Index *index);

t_Noeud *Left_Rotation(t_Noeud *Noeud);
t_Noeud *equilibrer_Noeud(t_Noeud *Noeud, int start, int end);


//fonctions de base
t_ListePosition* creer_liste_positions();
int ajouter_position(t_ListePosition* listeP, int ligne, int ordre, int num_phrase);
t_Index*creer_index();
t_Noeud* rechercher_mot(t_Index* index, char* mot);
int ajouter_noeud(t_Index* index, t_Noeud* noeud);
int indexer_fichier(t_Index*index, char *filename);
void afficher_index(t_Index *index);
void afficher_occurences_mot(t_Index *index, char *mot);
t_Index* equilibrer_index(t_Index *index);

void printTree(t_Noeud *Noeud, int space);
void menu();

//fonctions clean
void cleanPosition(t_Position *p);
void cleanListePosition(t_ListePosition *p);
void cleanNoeud(t_Noeud *p);
void cleanPhrase(t_Phrase *p);
void cleanIndex(t_Index *p);

#endif //TP4_TP4_H