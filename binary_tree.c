#include "binary_tree.h"

t_Position *creer_position(int nbligne, int ordre, int nbphrase)
{
    t_Position *p = (t_Position *)malloc(sizeof(t_Position));
    p->numero_ligne = nbligne;
    p->ordre = ordre;
    p->numero_phrase = nbphrase;
    p->suivant = NULL;
    return p;
}

t_ListePosition *creer_liste_positions()
{
    t_ListePosition *p = (t_ListePosition *)malloc(sizeof(t_ListePosition));
    p->debut = NULL;
    p->nb_elements = 0;
    return p;
}

int behide_position(t_Position *pos, int ligne, int ordre, int num_phrase)
{
    if (pos == NULL)
        return 0;
    if (pos->numero_ligne < ligne)
    {
        return (pos->numero_phrase <= num_phrase);
    }
    else
    {
        return (pos->numero_ligne == ligne && pos->ordre < ordre && pos->numero_phrase <= num_phrase);
    }
}

int before_position(t_Position *pos, int ligne, int ordre, int num_phrase)
{
    if (pos == NULL)
        return 0;
    if (pos->numero_ligne > ligne)
    {
        return (pos->numero_phrase >= num_phrase);
    }
    else
    {
        return (pos->numero_ligne == ligne && pos->ordre > ordre && pos->numero_phrase >= num_phrase);
    }
}

int ajouter_position(t_ListePosition *listeP, int ligne, int ordre, int num_phrase)
{
    t_Position *p = listeP->debut, *suivp = NULL;
    if (p == NULL)
    {
        listeP->debut = creer_position(ligne, ordre, num_phrase);
        listeP->nb_elements += 1;
        return 1;
    }
    else
    {
        if (p->suivant == NULL)
        {
            if (behide_position(p, ligne, ordre, num_phrase))
            {
                p->suivant = creer_position(ligne, ordre, num_phrase);
                listeP->nb_elements += 1;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            suivp = p->suivant;
            while (suivp != NULL && (!behide_position(p, ligne, ordre, num_phrase) || !before_position(suivp, ligne, ordre, num_phrase)))
            {
                p = p->suivant;
                suivp = suivp->suivant;
            }
            if (suivp == NULL)
            {
                if (behide_position(p, ligne, ordre, num_phrase))
                {
                    p->suivant = creer_position(ligne, ordre, num_phrase);
                    listeP->nb_elements += 1;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                t_Position *p1 = creer_position(ligne, ordre, num_phrase);
                p->suivant = p1;
                p1->suivant = suivp;
                listeP->nb_elements += 1;
                return 1;
            }
        }
    }
}

t_Noeud *creer_noeud(char *mot, int num_occurences, t_ListePosition *listeP, t_Noeud *gauche, t_Noeud *droit)
{
    t_Noeud *p = (t_Noeud *)malloc(sizeof(t_Noeud));
    p->mot = (char *)malloc(sizeof(char) * strlen(mot));
    strcpy(p->mot, mot);
    p->nb_occurences = num_occurences;
    t_ListePosition *pPos = creer_liste_positions();
    p->positions = pPos;
    t_Position *pSrc = listeP->debut;
    while (pSrc != NULL)
    {
        ajouter_position(pPos, pSrc->numero_ligne, pSrc->ordre, pSrc->numero_phrase);
        pSrc = pSrc->suivant;
    }
    // pPos->debut = creer_position(listeP->debut->numero_ligne, listeP->debut->ordre, listeP->debut->numero_phrase);
    // pPos->nb_elements = listeP->nb_elements;
    // t_Position *pSrc = listeP->debut, *pDes = p->positions->debut;
    // for (int i = 1; i < listeP->nb_elements; i++)
    // {
    //     pDes->suivant = creer_position(pSrc->numero_ligne, pSrc->ordre, pSrc->numero_phrase);
    //     pDes = pDes->suivant;
    //     pSrc = pSrc->suivant;
    // }
    p->filsGauche = gauche;
    p->filsDroit = droit;
    return p;
}

t_Index *creer_index()
{
    t_Index *p = (t_Index *)malloc(sizeof(t_Index));
    p->racine = NULL;
    p->nb_mots_differents = 0;
    p->nb_mots_total = 0;
    return p;
}

char *strlower(char *s1)
{
    char *s2 = (char *)malloc(sizeof(char) * strlen(s1) + 1);
    for (int i = 0; i < strlen(s1); i++)
    {
        if ((s1[i] >= 'A') && (s1[i] <= 'Z'))
        {
            s2[i] = s1[i] - 'A' + 'a';
        }
        else
        {
            s2[i] = s1[i];
        }
    }
    s2[strlen(s1)] = '\0';
    return s2;
}

t_Noeud *rechercher_mot(t_Index *index, char *mot)
{
    if (index == NULL)
        return NULL;
    if (index->racine == NULL)
        return NULL;
    t_Noeud *p = index->racine;
    char *key = malloc(sizeof(char) * strlen(mot)), *word;
    strcpy(key, strlower(mot));
    word = malloc(sizeof(char) * strlen(p->mot));
    strcpy(word, strlower(p->mot));
    if (strcmp(word, mot) == 0)
    {
        return p;
    }
    else
    {
        while (p != NULL)
        {
            word = malloc(sizeof(char) * strlen(p->mot));
            strcpy(word, strlower(p->mot));
            if (strcmp(key, word) == 0)
                return p;
            if (strcmp(key, word) > 0)
            {
                p = p->filsDroit;
            }
            else
            {
                p = p->filsGauche;
            }
        }
        return NULL;
    }
}

int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{
    if (noeud == NULL || index == NULL)
        return 0;
    if (index->racine == NULL)
    {
        index->racine = noeud;
        index->nb_mots_total += noeud->nb_occurences;
        index->nb_mots_differents += 1;
        return 1;
    }
    else
    {
        t_Noeud *p = index->racine, *prep = NULL;
        while (1)
        {
            prep = p;
            if (strcmp(strlower(noeud->mot), strlower(p->mot)) > 0)
            {
                p = p->filsDroit;
                if (p == NULL)
                {
                    prep->filsDroit = noeud;
                    index->nb_mots_total += noeud->nb_occurences;
                    index->nb_mots_differents += 1;
                    return 1;
                }
            }
            else if (strcmp(strlower(noeud->mot), strlower(p->mot)) < 0)
            {
                p = p->filsGauche;
                if (p == NULL)
                {
                    prep->filsGauche = noeud;
                    index->nb_mots_total += noeud->nb_occurences;
                    index->nb_mots_differents += 1;
                    return 1;
                }
            }
            else
            {
                p->nb_occurences += noeud->nb_occurences;
                index->nb_mots_total += noeud->nb_occurences;
                return 1;
            }
        }
    }
    return 0;
}

void printListepositions(t_ListePosition *listeP)
{
    if (listeP == NULL)
        return;
    t_Position *p = listeP->debut;
    while (p != NULL)
    {
        printf("|---- (l:%d, o:%d, p:%d)\n", p->numero_ligne, p->ordre, p->numero_phrase);
        p = p->suivant;
    }
}

void printNoeud(t_Noeud *noeud, char *title)
{
    if (noeud != NULL)
    {
        printNoeud(noeud->filsGauche, title);
        if (strlower(noeud->mot)[0] > *title)
        {
            *title = strlower(noeud->mot)[0];
            printf("%c\n", *title);
        }
        printf("|-- |%s|   Occurences = %d\n", strlower(noeud->mot), noeud->nb_occurences);
        printListepositions(noeud->positions);
        printNoeud(noeud->filsDroit, title);
    }
}

void afficher_index(t_Index *index)
{
    if (index == NULL)
    {
        printf("Votre Index est Null\n");
        return;
    }
    if (index->racine == NULL)
    {
        printf("L'index est null\n");
        return;
    }
    char title = ' ';
    printNoeud(index->racine, &title);
    printf("Fin de Afichage d'Index\n");
}

void printPhrase(t_Phrase *listePhrase, int k)
{
    if (listePhrase == NULL || k < 0)
        return;
    t_Phrase *p = listePhrase;
    int i = 1;
    while (p != NULL && i != k)
    {
        p = p->suivant;
        i++;
    }
    if (p == NULL)
    {
        printf("On n'a pas ce phrase\n");
    }
    else
    {
        printf("%s\n", p->listeMots);
    }
    return;
}

void afficher_occurences_mot(t_Index *index, char *mot)
{
    t_Noeud *p = rechercher_mot(index, mot);
    if (p == NULL)
    {
        printf("On n'a pas ce mot dans l'index\n");
    }
    else
    {
        printf("Mot = %s\n", mot);
        printf("Occurences = %d\n", p->nb_occurences);
        t_Position *positions = p->positions->debut;
        while (positions != NULL)
        {
            printf("| Ligne %d, position %d : ", positions->numero_ligne, positions->ordre);
            printPhrase(index->start, positions->numero_phrase);
            positions = positions->suivant;
        }
    }
    printf("Fin de Affichage Occurences\n");
    return;
}

char *make_word(char *word, char c, int size)
{
    word = realloc(word, sizeof(char) * size);
    word[size - 2] = c;
    word[size - 1] = '\0';
    return word;
}

int check_char(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
    {
        return 1;
    }
    if (c == ' ')
    {
        return 2;
    }
    if (c == '.' || c == -1)
    {
        return 3;
    }
    if (c == '\n')
    {
        return 4;
    }
}

t_Phrase *creerPhrase(int serial, char *sentence)
{
    t_Phrase *p = (t_Phrase *)malloc(sizeof(t_Phrase));
    p->listeMots = (char *)malloc(sizeof(char) * strlen(sentence));
    strcpy(p->listeMots, sentence);
    p->suivant = NULL;
    return p;
}

char *prolong_sentence(char *sentence, char *word)
{
    char *temp = malloc(sizeof(char) * (strlen(sentence) + strlen(word) + 2));
    char *m = malloc(sizeof(char) * 2);
    m[0] = ' ';
    m[1] = '\0';
    strcpy(temp, sentence);
    strcpy(temp + strlen(sentence), m);
    strcpy(temp + strlen(sentence) + 1, word);
    return temp;
}

int indexer_fichier(t_Index *index, char *filename)
{
    FILE *fptr;
    int nbwords = 0, nbline = 1, nbphrase = 1, pos = 1, nbmotdiff = 0, size = 0;
    t_Noeud *pNoeud = NULL, *temp = NULL;
    t_ListePosition *pListePos = NULL;
    t_Phrase *pPhrase = NULL, *headPhrase = NULL;
    char *sentence = malloc(sizeof(char));
    sentence[0] = '\0';
    char *word = malloc(sizeof(char)), c;

    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("Error! Opening file");
    }
    else
    {
        while (!feof(fptr))
        {
            if (size == 0)
            {
                size++;
                word = malloc(sizeof(char));
                word[0] = '\0';
            }
            c = fgetc(fptr);
            if (c == -1)
                break;
            if (check_char(c) == 1)
            {
                size++;
                word = make_word(word, c, size);
            }
            else
            {
                if (size > 1)
                {
                    pNoeud = rechercher_mot(index, word);
                    if (pNoeud == NULL)
                    {
                        pListePos = creer_liste_positions();
                        pListePos->debut = creer_position(nbline, pos, nbphrase);
                        pListePos->nb_elements = 1;
                        temp = creer_noeud(word, 1, pListePos, NULL, NULL);
                        ajouter_noeud(index, temp);
                        nbmotdiff++;
                    }
                    else
                    {
                        ajouter_position(pNoeud->positions, nbline, pos, nbphrase);
                        pNoeud->nb_occurences += 1;
                    }
                }
                if (check_char(c) == 2)
                {
                    if (size == 1)
                    {
                        continue;
                    }
                    sentence = prolong_sentence(sentence, word);
                    free(word);
                    nbwords++;
                    word = NULL;
                    size = 0;
                    pos++;
                }
                else if (check_char(c) == 3)
                {
                    if (size == 1)
                    {
                        continue;
                    }
                    sentence = prolong_sentence(sentence, word);
                    if (pPhrase == NULL)
                    {
                        pPhrase = creerPhrase(nbphrase, sentence);
                        headPhrase = pPhrase;
                    }
                    else
                    {
                        pPhrase->suivant = creerPhrase(nbphrase, sentence);
                        pPhrase = pPhrase->suivant;
                    }
                    free(sentence);
                    sentence = malloc(sizeof(char));
                    sentence[0] = '\0';
                    nbwords++;
                    free(word);
                    word = NULL;
                    size = 0;
                    pos++;
                    nbphrase++;
                }
                else
                {
                    if (sentence != NULL)
                    {
                        if (size > 1)
                        {
                            pNoeud = rechercher_mot(index, word);
                            if (pNoeud == NULL)
                            {
                                pListePos = creer_liste_positions();
                                pListePos->debut = creer_position(nbline, pos, nbphrase);
                                pListePos->nb_elements = 1;
                                temp = creer_noeud(word, 1, pListePos, NULL, NULL);
                                ajouter_noeud(index, temp);
                                nbmotdiff++;
                            }
                            else
                            {
                                ajouter_position(pNoeud->positions, nbline, pos, nbphrase);
                            }
                        }
                        sentence = prolong_sentence(sentence, word);
                        free(word);
                        word = NULL;
                        nbwords++;
                        size = 0;
                        pos = 1;
                        nbline++;
                    }
                    else
                    {
                        nbline++;
                        pos = 1;
                    }
                }
            }
        }
        index->start = headPhrase;
        index->nb_mots_total = nbwords;
        index->nb_mots_differents = nbmotdiff;
        fclose(fptr);
    }
    printf("Fin de Indexer \n");
    printf("Dans notre Fichier, on a %d mots \n", nbwords);
    printf("Et il y a %d mots differents \n", nbmotdiff);
    return nbwords;
}

void printTree(t_Noeud *Noeud, int space)
{
    if (Noeud == NULL)
    {
        return;
    }
    for (int i = 0; i < space; i++)
    {
        printf("-");
    }
    printf("level %d %s\n", level_Noeud(Noeud), strlower(Noeud->mot));
    printTree(Noeud->filsGauche, space + 2);
    printTree(Noeud->filsDroit, space + 2);
}

int level_Noeud(t_Noeud *Noeud)
{
    if (Noeud == NULL)
    {
        return 0;
    }
    int g, d;
    if (Noeud->filsGauche == NULL)
    {
        g = 0;
    }
    if (Noeud->filsDroit == NULL)
    {
        d = 0;
    }
    if (Noeud->filsGauche)
    {
        g = 1 + level_Noeud(Noeud->filsGauche);
    }
    if (Noeud->filsDroit)
    {
        d = 1 + level_Noeud(Noeud->filsDroit);
    }

    if (Noeud->filsGauche == NULL && Noeud->filsDroit == NULL)
    {
        return 1;
    }
    if (d > g)
    {
        return d;
    }
    return g;
}

int check_Noeud(t_Noeud *Noeud)
{
    if (Noeud == NULL)
        return 1;
    int k = level_Noeud(Noeud->filsDroit) - level_Noeud(Noeud->filsGauche);
    if (abs(k) > 1)
        return 0;
    return check_Noeud(Noeud->filsDroit) && check_Noeud(Noeud->filsGauche);
}

t_Noeud *Left_Rotation(t_Noeud *Noeud)
{
    t_Noeud *res = Noeud->filsDroit;
    res->filsGauche = creer_noeud(Noeud->mot, Noeud->nb_occurences, Noeud->positions, NULL, NULL);
    res->filsDroit->filsDroit = NULL;
    Noeud->filsDroit = NULL;
    cleanNoeud(Noeud);
    return res;
}

t_Noeud *Maximale(t_Noeud *Noeud)
{
    if (Noeud == NULL)
        return Noeud;
    t_Noeud *temp = Noeud;
    while (temp->filsDroit != NULL)
    {
        temp = temp->filsDroit;
    }
    return temp;
}

t_Noeud *Minimale(t_Noeud *Noeud)
{
    if (Noeud == NULL)
        return Noeud;
    t_Noeud *temp = Noeud;
    while (temp->filsGauche != NULL)
    {
        temp = temp->filsGauche;
    }
    return temp;
}

t_Noeud *Parent_Noeud(t_Index *index, t_Noeud *Noeud)
{
    if (index == NULL || Noeud == NULL)
        return NULL;
    if (index->racine == NULL)
        return NULL;
    t_Noeud *p = index->racine, *prep = NULL;
    if (p == Noeud)
        return NULL;
    char *key = malloc(sizeof(char) * strlen(Noeud->mot));
    key = strcpy(key, Noeud->mot);
    if (rechercher_mot(index, key) != NULL)
    {
        while (p != NULL)
        {
            if (strcmp(strlower(key), strlower(p->mot)) == 0)
            {
                break;
            }
            prep = p;
            if (strcmp(strlower(key), strlower(p->mot)) > 0)
            {
                p = p->filsDroit;
            }
            else if (strcmp(strlower(key), strlower(p->mot)) < 0)
            {
                p = p->filsGauche;
            }
        }
        return prep;
    }
    else
    {
        return NULL;
    }
}

t_Noeud *Successeur_Noeud(t_Index *index, t_Noeud *Noeud)
{
    if (Noeud == NULL || index->racine == NULL)
    {
        return NULL;
    }
    t_Noeud *max = Maximale(index->racine);
    if (strcmp(strlower(Noeud->mot), strlower(max->mot)) == 0)
    {
        return NULL;
    }

    if (Noeud->filsDroit != NULL)
    {
        return Minimale(Noeud->filsDroit);
    }
    t_Noeud *p = Parent_Noeud(index, Noeud), *temp = Noeud;
    while ((p != NULL) && (p->filsDroit != NULL))
    {
        if (strcmp(strlower(temp->mot), strlower(p->filsDroit->mot)) == 0)
        {
            temp = rechercher_mot(index, p->mot);
            p = Parent_Noeud(index, temp);
        }
        else
        {
            break;
        }
    }
    return p;
}

t_Noeud *Classer_Noeud(t_Index *index)
{
    if (index == NULL || index->racine == NULL)
        return NULL;
    t_Noeud *p = index->racine;
    t_Noeud *min = Minimale(p);
    t_Noeud *final = creer_noeud(min->mot, min->nb_occurences, min->positions, NULL, NULL);
    t_Noeud *temp = Successeur_Noeud(index, final);
    t_Noeud *y = final;
    while (temp != NULL)
    {
        y->filsDroit = creer_noeud(temp->mot, temp->nb_occurences, temp->positions, NULL, NULL);
        y = y->filsDroit;
        temp = Successeur_Noeud(index, temp);
    }
    //char title = ' ';
    //printNoeud(final, &title);
    return final;
}
t_Noeud *equilibrer_Noeud(t_Noeud *Noeud, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    if (start == end)
    {
        Noeud->filsDroit = NULL;
        return Noeud;
    }
    if (end - start == 1)
    {
        Noeud->filsDroit->filsDroit = NULL;
        return Noeud;
    }
    else
    {
        if (end - start == 2)
        {
            return Left_Rotation(Noeud);
        }
        t_Noeud *res = Noeud;
        int mid = (start + end) / 2;
        for (int i = start; i < mid; i++)
        {
            res = res->filsDroit;
        }
        t_Noeud *Next = res->filsDroit;
        t_Noeud *gauche = (t_Noeud *)malloc(sizeof(t_Noeud)), *droit = (t_Noeud *)malloc(sizeof(t_Noeud));
        gauche = equilibrer_Noeud(Noeud, start, mid - 1);
        res->filsGauche = gauche;
        droit = equilibrer_Noeud(Next, mid + 1, end);
        res->filsDroit = droit;
        return res;
    }
}

t_Index *equilibrer_index(t_Index *index)
{
    if (check_Noeud(index->racine))
    {
        printf("L'index est eauilibre\n");
        return index;
    }
    else
    {
        printf("L'index n'est pas equilibre, Start Equilibration\n");
        t_Index *sol = creer_index();
        sol->start = index->start;
        sol->nb_mots_differents = index->nb_mots_differents;
        sol->nb_mots_total = index->nb_mots_total;
        t_Noeud *solution = Classer_Noeud(index);
        solution = equilibrer_Noeud(solution, 0, level_Noeud(solution) - 1);
        sol->racine = solution;
        printf("Fin de Equibration\n");
        return sol;
    }
}

void cleanPosition(t_Position *p)
{
    if (p == NULL)
        return;
    if (p->suivant)
    {
        cleanPosition(p->suivant);
    }
    free(p);
    p = NULL;
}

void cleanListePosition(t_ListePosition *p)
{
    if (p == NULL || p->debut == NULL)
    {
        return;
    }
    cleanPosition(p->debut);
    free(p);
    p = NULL;
}

void cleanNoeud(t_Noeud *p)
{
    if (p == NULL)
        return;
    if (p->filsDroit)
    {
        cleanNoeud(p->filsDroit);
    }
    if (p->filsGauche)
    {
        cleanNoeud(p->filsGauche);
    }
    cleanListePosition(p->positions);
    free(p->mot);
    free(p);
    p = NULL;
}

void cleanPhrase(t_Phrase *p)
{
    if (p == NULL)
        return;
    if (p->suivant)
    {
        cleanPhrase(p->suivant);
    }
    free(p->listeMots);
    free(p);
    p = NULL;
}

void cleanIndex(t_Index *p)
{
    if (p == NULL)
        return;
    cleanNoeud(p->racine);
    cleanPhrase(p->start);
    free(p);
    p = NULL;
}

void menu()
{
    int choix;
    t_Index *index = creer_index(), *index2 = creer_index();
    t_Noeud *pNoeud = NULL;
    char filename[50], fileExportname[50], mot[50];
    printf("Bonjour\n");
    do
    {
        printf("==========\n");
        printf("\t\t MENU \n");
        printf("1. Charger un  fichier\n");
        printf("2. Caracteristiques de l'index\n");
        printf("3. Afficher index\n");
        printf("4. Rechercher un mot\n");
        printf("5. Afficher les occurrences d’un mot\n");
        printf("6. Equilibrer l’index\n");
        printf("7. Quitter\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("Quel est le nom de le fichier? \n");
            scanf("%s", filename);
            indexer_fichier(index, filename);
            break;

        case 2:
            if (index == NULL)
            {
                printf("L'index est NULL\n");
            }
            else if (check_Noeud(index->racine))
            {
                printf("L'index est equilibre\n");
            }
            else
            {
                printf("L'index n'est pas equilibre\n");
            }
            //printTree(index->racine,0);
            break;

        case 3:
            afficher_index(index);
            break;

        case 4:
            printf("Quel mot voulez-vous rechercher?\n");
            scanf("%s", mot);
            pNoeud = rechercher_mot(index, mot);
            if (pNoeud == NULL)
            {
                printf("On n'a pas ce mot dans l'index\n");
            }
            else
            {
                printListepositions(pNoeud->positions);
            }
            printf("Fin de Rechercher\n");
            break;

        case 5:
            printf("Quel mot voulez-vous rechercher?\n");
            scanf("%s", mot);
            afficher_occurences_mot(index, mot);
            break;

        case 6:
            if (index == NULL)
            {
                printf("L'index est NULL\n");
            }
            else if (check_Noeud(index->racine))
            {
                printf("L'index est equilibre\n");
            }
            else
            {
                index2 = equilibrer_index(index);
                index = index2;
            }
            break;

        case 7:
            printf("Au revoir !\n");
            break;

        default:
            printf("Au revoir !\n");
            break;
        }
    } while (choix != 7);
    cleanIndex(index);
}

