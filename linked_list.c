#include "linked_list.h"

T_Soigneur* createSoigneur(Index_Soigneur idSoi, char* nom, char* prenom){
    T_Soigneur* temp = (T_Soigneur*) malloc(sizeof(T_Soigneur));
    temp->id_soi = idSoi;
    temp->nom = nom;
    temp->prenom = prenom;
    temp->suivant = NULL;
    return temp;
}

T_Intervalle* createIntervalle(Time debut, Time fin){
    T_Intervalle* temp = (T_Intervalle*) malloc(sizeof(T_Intervalle));
    temp->debut = debut;
    temp->fin = fin;
    temp->suivant = NULL;
    return temp;
}

T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){
    T_Soigneur* temp;

    // On ajoute le soigneur en tête de liste
    if(listeSoigneurs == NULL){
        temp = createSoigneur(idSoi, nom, prenom);
        temp->listeIntervalle = createIntervalle(0, inf);
        listeSoigneurs = temp;
    }
    else{
        T_Soigneur* p = listeSoigneurs;
        if (p->id_soi == idSoi){
            // Verification de l'unicité des identifiants
            printf("L'dentifiant %d des Soigneurs existe déjà\n", p->id_soi);
            exit(1);
        }
        while(p->suivant != NULL){
            p = p->suivant;
            if (p->id_soi == idSoi){
                printf("L'dentifiant %d des Soigneurs existe déjà\n", p->id_soi);
                exit(1);
            }
        }
        temp = createSoigneur(idSoi, nom, prenom);
        temp->listeIntervalle = createIntervalle(0,inf);
        p->suivant = temp;
    }
    return listeSoigneurs;
}

T_Patient* createPatient(Index_Patient idPat, char* nom, char* prenom){
    T_Patient* temp = (T_Patient*) malloc(sizeof(struct Patient));
    temp->id_pat = idPat;
    temp->nom = nom;
    temp->prenom = prenom;
    temp->suivant = NULL;
    temp->listeRendezVous = NULL;
    return temp;
}

T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom){
    T_Patient* temp;

    // On ajoute le patient en tête de liste
    if(listePatients == NULL){
        temp = createPatient(idPat, nom, prenom);
        listePatients = temp;
    }
    else{
        T_Patient* p = listePatients;
        if (p->id_pat == idPat){
            // Verification de l'unicité des identifiants
            printf("L'dentifiant %d des Patients existe déjà\n", p->id_pat);
            exit(1);
        }
        while(p->suivant != NULL){
            p = p->suivant;
            if (p->id_pat == idPat){
                // Verification de l'unicité des identifiants
                printf("L'dentifiant %d des Patients existe déjà\n", p->id_pat);
                exit(1);
            }
        }
        temp = createPatient(idPat, nom, prenom);
        p->suivant = temp;
    }
    return listePatients;
}

T_RendezVous* createRendezVous(Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    T_RendezVous* temp = (T_RendezVous*) malloc(sizeof(struct RendezVous));
    temp->id_soi = idSoi;
    temp->debut_souhaitee = dateDebutSouhaitee;
    temp->fin_souhaitee = dateFinSouhaitee;
    temp->temps_deplacement = tempsDeplacement;
    temp->suivant = NULL;
    temp->desc = desc;
    return temp;
 }

T_RendezVous* ajouterRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    T_RendezVous* temp = createRendezVous(idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
    if (listeRdV == NULL){
        listeRdV = temp;
    }
    else{
        T_RendezVous* p = listeRdV;
        while(p->suivant != NULL){
            p = p->suivant;
        }
        p->suivant = temp;
    }
    return listeRdV;
}

void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    if(listeRdV == NULL){
        printf("Votre liste de rendez-vous est NULL\n");
        exit(1);
    }

    T_RendezVous* p = listeRdV;
    int k = 0;

    if (p->id_soi == idSoi){
        p->debut_souhaitee = dateDebutSouhaitee;
        p->fin_souhaitee = dateFinSouhaitee;
        p->temps_deplacement = tempsDeplacement;
        p->desc = desc;
        k = 1;
    }

    while (p->suivant != NULL){
        p = p->suivant;
        if (p->id_soi == idSoi){
            p->debut_souhaitee = dateDebutSouhaitee;
            p->fin_souhaitee = dateFinSouhaitee;
            p->temps_deplacement = tempsDeplacement;
            p->desc = desc;
            k = 1;
        }
   }
   if (k == 0) printf("Cette idSoi n'existe pas\n");
}

T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi){
    if(listeRdV == NULL){
        printf("Votre liste de rendez-vous est NULL\n");
        return listeRdV;
    }

    T_RendezVous* temp = listeRdV, *prev;
    int k = 0;

    if(temp->id_soi == idSoi){
        prev = temp->suivant;
        free(temp);
        return prev;
    }

    while(temp->suivant != NULL){
        prev = temp;
        temp = temp->suivant;
        if(temp->id_soi == idSoi){
            int a, b;
            a = temp->temps_deplacement;
            b = temp->suivant->temps_deplacement;
            prev->suivant = temp->suivant;
            prev->suivant->temps_deplacement = sqrt(a*a + b*b);
            free(temp);
            return listeRdV;
        }
    }

    if (k == 0) printf("Cette idSoi n'existe pas\n");
    return listeRdV;
}

T_Ordonnancement* creerInstance(char* filename){
    FILE *fptr;
    T_Ordonnancement* p=(T_Ordonnancement*) malloc(sizeof(T_Ordonnancement));
    T_Patient* y=NULL;
    T_RendezVous* listeRdv=NULL;
    int nbsoi,nbpat,nbrdv;
    Index_Patient idpat;
    Index_Soigneur idsoi;
    Time debutSou,finSou,deplace;
    char nompat[50],prenompat[50],nomsoi[50],prenomsoi[50],desc[50];

    if ((fptr=fopen(filename,"r")) == NULL){
        printf("Error! Opening file");
    }
    else{
        fscanf(fptr,"%d %d",&nbpat,&nbsoi);
        for(int i=0;i<nbpat;i++){
            fscanf(fptr,"%d %d %s %s",&idpat,&nbrdv,nompat,prenompat);
            for(int j=0;j<nbrdv;j++){
                fscanf(fptr,"%d %d %d %d %s",&idsoi,&debutSou,&finSou,&deplace,desc);
                listeRdv=ajouterRendezVous(listeRdv,idsoi,debutSou,finSou,deplace,desc);
            }
            p->listePatients=ajouterPatient(p->listePatients,idpat,nompat,prenompat);
            y=p->listePatients;
            while(y && y->id_pat!=idpat){
                y=y->suivant;
            }
            y->listeRendezVous=listeRdv;
            listeRdv=NULL;
        }
       for(int k=0;k<nbsoi;k++){
          fscanf(fptr,"%d %s %s",&idsoi,nomsoi,prenomsoi);
          p->listeSoigneurs=ajouterSoigneur(p->listeSoigneurs,idsoi,nomsoi,prenomsoi);
       }
    }
    fclose(fptr);
    return p;
}

void printIntervalle(T_Soigneur *soigneur) {
    T_Intervalle *p = soigneur->listeIntervalle;
    printf("Intervalle de soigneur [%d]\n", soigneur->id_soi);
    while (p){
        printf("(%d %d) ", p->debut, p->fin);
        p=p->suivant;
    }
    printf("\n");
}

int max(int a, int b) {
    return a>b?a:b;
}

void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
    int k=0;
    Time DureeRdv,Dureep,DebutBon,FinBon;
    T_Intervalle *p=soigneur->listeIntervalle, *prep=NULL, *p1,*p2;
    printf("Affecting: souhaitee (%d %d) => %d\n", rdv->debut_souhaitee, rdv->fin_souhaitee, soigneur->id_soi);
    printIntervalle(soigneur);
    while(p!=NULL && k!=1){
        DureeRdv=rdv->fin_souhaitee-rdv->debut_souhaitee;
        Dureep=p->fin-p->debut;
        if (max(p->debut, rdv->debut_souhaitee) + DureeRdv <= p->fin){
            k=1;
        }
        else{
            prep=p;
            p=p->suivant;
        }
    }
    if (p==NULL){
        printf("On ne peut pas affecter ce rdv a ce soigneur \n");
    }
    else{
        if(p->debut > rdv->debut_souhaitee){
            DebutBon=p->debut;
        }
        else{
            DebutBon=rdv->debut_souhaitee;
        }
        FinBon=DebutBon+DureeRdv;
        printf("\t=> Trouvee (%d %d)\n", DebutBon, FinBon);
        rdv->id_soi=soigneur->id_soi;
        rdv->debut_affectee=DebutBon;
        rdv->fin_affectee=FinBon;

        p1=createIntervalle(p->debut,DebutBon);
        p2=createIntervalle(FinBon,p->fin);

        if (prep) {
            prep->suivant=p1;
        } else {
            soigneur->listeIntervalle=p1;
        }
        p1->suivant=p2;
        p2->suivant=p->suivant;
        free(p);
        p=NULL;


    }

    printIntervalle(soigneur);

}


void ordonnancer(T_Ordonnancement* solution){
    T_Patient* pPat;
    T_Soigneur* pSoi;
    T_RendezVous* rdv;
    provided_MergeSort(&(solution->listePatients));
    pPat = solution->listePatients;
    pSoi = solution->listeSoigneurs;
    while(pPat!=NULL){
        printf("Patient [%d]\n", pPat->id_pat);
        rdv=pPat->listeRendezVous;
        while(rdv!=NULL){
            pSoi=solution->listeSoigneurs;
            while(pSoi!=NULL){
                if (pSoi->id_soi == rdv->id_soi)
                {
                    affecterRdV(rdv,pSoi);
                    break;
                }
                pSoi=pSoi->suivant;
            }
            rdv=rdv->suivant;
        }
        pPat=pPat->suivant;
    }
}

void exportSolution(T_Ordonnancement* solution, char* filename){
    FILE *fptr;
    T_Patient *pPat=solution->listePatients;
    T_Soigneur *pSoi=solution->listeSoigneurs;
    T_RendezVous *rdv;

    int nbSoi,nbPat;

    if ((fptr=fopen(filename,"w")) == NULL){
        printf("Error! Opening file");
    }
    else{
        nbPat=provided_compter_nb_patients(solution->listePatients);
        nbSoi=provided_compter_nb_soigneurs(solution->listeSoigneurs);
        fprintf(fptr,"%d %d\n",nbPat,nbSoi);
        while(pPat!=NULL){
            rdv=pPat->listeRendezVous;
            fprintf(fptr,"%d %d\n",pPat->id_pat,provided_compter_nb_Rdv_par_patient(pPat->id_pat,pPat));
            while(rdv!=NULL){
                fprintf(fptr,"%d %d %d %d\n",rdv->id_soi,rdv->debut_affectee,rdv->fin_affectee,rdv->temps_deplacement);
                rdv=rdv->suivant;
            }
            pPat=pPat->suivant;
        }
        fclose(fptr);
    }
}

void menu(){
    int choix = 0;
    do{
        printf("==========\n");
        printf("\t\t MENU \n");
        printf("1. Creer une instance à partir d’un fichier\n");
        printf("2. Afficher tous les patients et leurs rendez-vous\n");
        printf("3. Afficher tous les soigneurs et leurs intervalles de temps disponibles\n");
        printf("4. Afficher un rendez-vous\n");
        printf("5. Modifier un rendez-vous\n");
        printf("6. Supprimer un rendez-vous\n");
        printf("7. Ordonnancer\n");
        printf("8. Exporter la solution d’un ordonnancement\n");
        printf("9. Quitter\n");

        scanf("%d", &choix);
        switch (choix){
        case 1:
            /* code */
            break;

        case 2:
            /* code */
            break;

        case 3:
            /* code */
            break;

        case 4:
            /* code */
            break;

        case 5:
            /* code */
            break;

        case 6:
            /* code */
            break;

        case 7:
            /* code */
            break;

        case 8:
            /* code */
            break;

        case 9: printf("Au revoir !\n"); break;

        default: printf("Au revoir !\n"); break;
        }
    } while (choix != 9);

}
