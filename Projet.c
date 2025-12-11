#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define Taille_Table 13
typedef struct Produit{ 
int id;     
float prix;          
char nom[30];         
int quantite;         
struct Produit *suivant;
} stProduit;

typedef struct Client{
    int id;
    char nom[30];
    float totalDepense;
    struct Client* gauche;
    struct Client* droite;
}Client;
int hachage(int id) { 
    return id % Taille_Table; 
} 
typedef struct stHach{
    stProduit *Table[Taille_Table];
}stHach;
void Menu(){
    printf("******************Chere gerant(e) :-)****************\n");
    printf("1)Ajouter Produit .\n");
    printf("2)Modifier Produit .\n");
    printf("3)Supprimer Produit .\n");
    printf("4)Rechercher un produit .\n");
    printf("5)Afficher la liste des produit .\n");
    printf("6)Sauvegarder la liste des produits.\n");
    printf("**************************************************\n");
}
int Lire_Choix(char *message,int from, int to){
    int Choix=0;
    do{
        printf("%s", message);
        scanf(" %d",&Choix);
    }while(Choix>to || Choix<from);
    return Choix;
}
int Lire_Id(char *message){
    int Choix=0;
    do{
        printf("%s", message);
        scanf(" %d",&Choix);
    }while(Choix<0);
    return Choix;
}
char Continuer(){
    char choix=' ';
    printf(" Est ce que vous voulez changer quelque chose d'autre dans ce produit : (Y/y) ou bien (N/n) \n");
    scanf(" %c",&choix);
    return choix;
}
void Lire_Info(stProduit *Produit){
    printf("Entrez l'identite de Produit : \n ");
    scanf(" %d",&(Produit->id));
    printf("Entrez le nom de Produit : \n ");
    scanf(" %s",(Produit->nom));
    printf("Entrez le prix de produit : \n");
    scanf(" %f",&Produit->prix);
    printf("Entrez la quantite de Produit : \n ");
    scanf(" %d", &Produit->quantite);
}
void Print_Info(stProduit *ptr){
    printf("Id : %d Nom : %s , Prix : %.2f, quantite : %d \n",ptr->id,ptr->nom,ptr->prix,ptr->quantite);
}
stProduit *Creer_Produit(){
    stProduit *Produit=(stProduit *)malloc(sizeof(stProduit));
    if(Produit==NULL){
        perror("Erreur, Allocation dynamique du produit \n");
        exit(0);
    }
    Produit->suivant=NULL;
    return Produit;
}
void Ajouter_Produit(stProduit *Table[Taille_Table],int indexe, stProduit *Produit ){
    if(Table[indexe]==NULL){
        Table[indexe]=Produit;
        return ;
    }
    stProduit *ptr=Table[indexe];
    Produit->suivant=Table[indexe];
    Table[indexe]=Produit;
}
int Menu_Changement(){
    int choix=0;
    do{
        printf("Les types de changement : \n");
        printf("1)Changer l'ID \n");
        printf("2)Changer le nom \n");
        printf("3)Changer le Prix : \n");
        printf("4)Changer la quantite \n");
        choix=Lire_Choix("Entrez votre choix (Entre 1 et 4)",1,4);
    }while(choix>4 && choix<0);
    return choix;
}
void Copier_Info(stProduit *P1,stProduit *P2){
    P1->id=P2->id;
    strcpy(P1->nom,P2->nom);
    P1->prix=P2->prix;
    P1->quantite=P2->quantite;
}
void supprimer(stProduit * Table[Taille_Table], int indexe, int id_supprimer);
void modifier(stProduit *Table[Taille_Table],int indexe, int id_modifie){
    char choix;
    if(Table[indexe]==NULL){
        printf("\tPas d'element à modifier :-( .\t\n");
        return ;
    }
    stProduit *ptr=Table[indexe];
    while(ptr!=NULL && ptr->id!=id_modifie  ) ptr=ptr->suivant;
    do{
        int choix_changement=Menu_Changement();
        switch(choix_changement){
            case 1:
            printf("Entrez le nouveau ID : \n");
            stProduit *Nvl_Case=Creer_Produit();
            scanf(" %d",&Nvl_Case->id);
            strcpy(Nvl_Case->nom,ptr->nom);
            Nvl_Case->quantite=ptr->quantite;
            Ajouter_Produit(Table,hachage(Nvl_Case->id),Nvl_Case);
            supprimer(Table,indexe,id_modifie);
            break;
            case 2:
            printf("Entrez le nouveau nom : \n");
            scanf(" %s", ptr->nom);
            break;
            case 3: 
            printf("Entrez le nouveau prix : \n");
            scanf(" %f",&ptr->prix);
            break;
            case 4:
            printf("Entrez la nouvelle quantite : \n");
            scanf(" %d",&ptr->quantite);
            break;
        }
        printf("-->Changement fait avec succes :-) \t\n\n");
        choix=Continuer();
    }while(choix=='Y' || choix=='y');
}

void supprimer(stProduit * Table[Taille_Table], int indexe, int id_supprimer){
    stProduit *ptr=*(Table+indexe);
    if(ptr==NULL){
        printf("Pas d'element à supprimer .\n");
        return ;
    }
    if(ptr->id==id_supprimer){
        Table[indexe]=ptr->suivant;
        free(ptr);
        return;
    }
    stProduit *ptr1=ptr->suivant;
    while( ptr1 != NULL && ptr1->id!=id_supprimer ){
        ptr=ptr1;
        ptr1=ptr1->suivant;
    } 
    ptr->suivant=ptr1->suivant;
    free(ptr1);
    printf(" \t\t Suppression avec succes :-)  \t\n");
}
void Menu_Recherche(){
    printf("*********Type de recherche********** \n");
    printf("1)Recherche par id.\n");
    printf("2)Recherche par nom .\n");
}
void Rechercher_Par_Id(stProduit * Table[Taille_Table], int indexe, int id_Recherche){
    if(Table[indexe]==NULL){
        printf("Element Non trouve .\n");
        return ;
    }
    stProduit *ptr=Table[indexe];
    while(ptr!= NULL && ptr->id != id_Recherche ){
        ptr=ptr->suivant;
    }
    if(ptr==NULL){
        printf("Element Non trouve .\n");
        return ;
    }
    Print_Info(ptr);
}
void Rechercher_Par_nom(stProduit * Table[Taille_Table], char nom_modifie[]){
    stProduit *ptr;
    for(int index=0;index<Taille_Table;index++){
        ptr=Table[index];
        while((ptr!= NULL) && strcmp(ptr->nom,nom_modifie)!=0)
        {
           ptr=ptr->suivant;
        }
    if(ptr!=NULL){
        Print_Info(ptr);
        return ;
    }
    }
    printf("Element non trouvé !");
}
void Afficher_NonTrie(stProduit * Table[Taille_Table]){
    stProduit *ptr;
    for(int i=0;i<Taille_Table;i++){
        ptr=Table[i];
        while(ptr!=NULL)
        {
        Print_Info(ptr);
        printf("\n");
        ptr=ptr->suivant;
    }
    
    }
}
//afficher trie
void fusionner(stProduit tableau[], int debut, int
 milieu, int fin) {
 // taille de la première moitié
 int n1 = milieu - debut + 1; 
// taille de la deuxième moitié
 int n2 = fin - milieu; 
// Tableaux temporaires
 stProduit *G = (stProduit*) malloc(n1 * sizeof(stProduit));
 stProduit *D = (stProduit*) malloc(n2 * sizeof(stProduit));
 // Copier les éléments dans G et D
 for (int i = 0; i < n1; i++)
 G[i] = tableau[debut + i];
 for (int j = 0; j < n2; j++)
 D[j] = tableau[milieu + 1 + j];
 int i = 0, j = 0, k = debut;
 while (i < n1 && j < n2) {
 if (G[i].id <= D[j].id) {
 Copier_Info(&tableau[k],&G[i]);
 i++;
 } else {
 Copier_Info(&tableau[k],&D[j]);
 j++;
 }
 k++;
 }
 while (i < n1) {
  Copier_Info(&tableau[k],&G[i]);
 i++;
 k++;
 }
 while (j < n2) {
 Copier_Info(&tableau[k],&D[j]);
 j++;
 k++;
 }
 free(G);
 free(D);
 }
void triFusion(stProduit tableau[], int debut, int fin) {
 if (debut < fin) {
 int milieu = (debut + fin) / 2;
 triFusion(tableau, debut, milieu);
 triFusion(tableau, milieu + 1, fin);
 fusionner(tableau, debut, milieu, fin);
 }
 }
void Afficher_Trie(stProduit *tab[Taille_Table]){
    int count=0,j=0;
    stProduit *ptr;
    for(int i=0;i<Taille_Table;i++){
        ptr=tab[i];
        while(ptr!=NULL)
        {
            count++;
            ptr=ptr->suivant;
        }
    }
    stProduit *NTab=(stProduit *)malloc(count*sizeof(stProduit));
    for(int i=0;i<Taille_Table;i++){
        if(tab[i]==NULL)continue;
        ptr=tab[i];
        while(ptr!=NULL) {
           Copier_Info(&NTab[j], ptr);
            ptr=ptr->suivant;
            j++;
        }
    }
    triFusion(NTab,0,count-1);
    for(int i=0;i<count;i++){
        Print_Info(&NTab[i]);
    }
    free(NTab);
}
void Sauvegarder(stProduit *Tab[Taille_Table]){
    stProduit *ptr;
    FILE *pf=fopen("produit.txt","w");
    if(pf==NULL){
        perror("erreur !\n");
        exit(0);
    }

    for(int i=0;i<13;i++){
    ptr=Tab[i];
    while(ptr!=NULL){
        fprintf(pf," %d|%s|%.2f|%d\n",ptr->id,ptr->nom,ptr->prix,ptr->quantite);
        ptr=ptr->suivant;
    }
   }
    fclose(pf);
}
void initialiser_Table(stProduit * table[Taille_Table]){
    for(int i=0;i<Taille_Table;i++){
        table[i]=NULL;
    }
}
void Menu_affichage(){
    printf("\t****Quels type d'\affichage voulez vous Monsieur ?****\t\n");
    printf("1)Trie\n");
    printf("2)Non Trie\n");
}
void charger(stProduit *Table[Taille_Table]){
    FILE *pf=fopen("produit.txt","r");
    if(pf==NULL){
        perror("erreur !\n");
        exit(0);
    }
    while(1){
        stProduit *ptr=Creer_Produit();
        if(fscanf(pf,"%d|%[^|]|%f|%d",&ptr->id,ptr->nom,&ptr->prix,&ptr->quantite)==4){
            Ajouter_Produit(Table,hachage(ptr->id),ptr);
        }
        else{
            break;
        }
    }
    fclose(pf);
}
void Gestion_Produit(){
    char nom[20];
    stHach HashTable;
    initialiser_Table(HashTable.Table);
    charger(HashTable.Table);
   int nbre,indexe,id,choix_affichage,choix_Re;
   char choix;
   stProduit *Produit;
   do{
    Menu();
    choix=Lire_Choix("Entrez votre choix : ",0,7);
    switch(choix){
    case 1:
    Produit=Creer_Produit();
    Lire_Info(Produit);
    indexe=hachage(Produit->id);
    Ajouter_Produit(HashTable.Table,indexe,Produit);
    break;
    case 2:
    id=Lire_Id("Entrez l'ID du produit que vous voulez modifier \n");
    indexe=hachage(id);
    modifier(HashTable.Table,indexe,id);
    break;
    case 3:
    id=Lire_Id("Entrez l'ID du produit que vous voulez supprimer \n");
    indexe=hachage(id);
    supprimer(HashTable.Table,indexe,id);
    break;
    case 4:
    Menu_Recherche();
    choix_Re=Lire_Choix("Entrez votre choix : ",1,2);
    switch(choix_Re){
    case 1:
    id=Lire_Id("Entrez l'ID du produit que vous voulez rechercher : \n");
    indexe=hachage(id);
    Rechercher_Par_Id(HashTable.Table,indexe,id);
    break;
    case 2 :
    printf("Entrez Le nom du produit  : \n");
    scanf(" %s", nom);
    Rechercher_Par_nom(HashTable.Table,nom);
    break;
    }
    break;
    case 5:
    Menu_affichage();
    choix_affichage=Lire_Choix("Entrez votre choix : \n ",1,2);
    switch (choix_affichage)
    {
    case 1:
        Afficher_Trie(HashTable.Table);
        break;
    case 2:
        Afficher_NonTrie(HashTable.Table);
        break;
    }
    break;
    case 6:
    Sauvegarder(HashTable.Table);
    break;
    }
   }while(choix!=0);
}
int main(){
    Gestion_Produit();
}