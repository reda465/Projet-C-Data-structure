#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#define Taille_Table 13
typedef struct Produit{ 
int id;     
float prix;          
char nom[30];         
int quantite;  
float prix;       
struct Produit *suivant;
} stProduit;
typedef struct Client { 
    int id; 
    char nom[30]; 
    float totalDepense; 
    struct Panier panier;
    struct Client *gauche; 
    struct Client *droite; 
} Client;
typedef struct ClientFile { 
    Client cl;
    struct ClientFile *suivant; 
} ClientFile;  
typedef struct { 
    ClientFile *debut; 
    ClientFile *fin; 
    int taille;
} FileAttente;
typedef struct ArticlePanier {
    int idProduit;
    int quantite;
    struct ArticlePanier *suivant;
} ArticlePanier;
typedef struct Panier {
    ArticlePanier *debut;
    ArticlePanier *fin;
    int nbArticles;
    float total;
} Panier;
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
void initialiserPanier(Panier *panier) {
    panier->debut = NULL;
    panier->fin = NULL;
    panier->nbArticles = 0;
    panier->total = 0;
}
void ajouterAuPanier(Panier *panier, int idProduit, int quantite) {
    ArticlePanier *nvn = (ArticlePanier*)malloc(sizeof(ArticlePanier));
    nvn->idProduit = idProduit;
    nvn->quantite = quantite;
    nvn->suivant = NULL;
    
    if (panier->fin == NULL) {
        panier->debut = nvn;
        panier->fin = nvn;
    } else {
        panier->fin->suivant = nvn;
        panier->fin = nvn;
    }
    
    panier->nbArticles++;
    printf("    Article %d %d ajouté au panier\n", idProduit, quantite);
}
int estPanierVide(Panier *panier) {
    return panier->debut == NULL;
}
void viderPanier(Panier *panier) {
    ArticlePanier *article = panier->debut;

    while (article != NULL) {
        ArticlePanier *tmp = article;
        article = article->suivant;
        free(tmp);
    }

    panier->debut = NULL;
    panier->fin = NULL;
    panier->nbArticles = 0;
    panier->total = 0.0;
}
typedef struct stHach{
    stProduit *Table[Taille_Table];
}stHach;
ClientFile* creerNoeudClientFile(Client cl) {
    ClientFile* ptr = (ClientFile*)malloc(sizeof(ClientFile));
    if(ptr == NULL) {
        printf("Erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    ptr->cl = cl;
    ptr->suivant = NULL;
    return ptr;
}
int estFileVide(FileAttente* fi) {
    return fi->taille == 0;
}
void enfilerEnfinFile(FileAttente* fi, Client cl) {
    ClientFile* nvn = creerNoeudClientFile(cl);
    if (fi->fin == NULL) {
        fi->debut = nvn;
        fi->fin = nvn;
    } else {
        fi->fin->suivant = nvn;
        fi->fin = nvn;
    }
    fi->taille++;
}
void defilerFile(FileAttente* fi) {
    if (estFileVide(fi)) {
        printf("La file est vide, impossible de defiler.\n");
        return;
    }
    ClientFile* temp = fi->debut;
    fi->debut = fi->debut->suivant;
    if (fi->debut == NULL) {
        fi->fin = NULL;
    }
    free(temp);
    fi->taille--;
}
void afficherFile(FileAttente* fi){
    if(estFileVide(fi)){
        printf("La file est vide.\n");
        return;
    }
    ClientFile* current = fi->debut;
    while(current != NULL){
        printf("ID Client: %d, Nom: %s, Total Depense: %.2f\n", current->cl.id, current->cl.nom, current->cl.totalDepense);
        current = current->suivant;
    }
    return;
}
int verifierPanier(Panier *panier, stHach *tableProduits) {
    if (panier->debut == NULL) {
        printf("Le panier est vide.\n");
        return 0;
    }
    
    ArticlePanier *article = panier->debut;
    int disponible = 1;  // 1 = tout disponible, 0 = probleme de stock
    printf("Vérification panier...\n");
    
    while (article != NULL) {
        // Recherche rapide par hachage
        int index = hachage(article->idProduit);
        stProduit *produit = tableProduits->Table[index];
        
        // Parcourir la liste chaînée à cet index
        int trouve = 0;
        while (produit != NULL) {
            if (produit->id == article->idProduit) {
                trouve = 1;
                
                if (produit->quantite < article->quantite) {
                    printf("  [ERREUR] %s: stock %d < demande %d\n", 
                           produit->nom, produit->quantite, article->quantite);
                    disponible = 0;
                }
                break;
            }
            produit = produit->suivant;
        }
        
        if (!trouve) {
            printf("  [ERREUR] Produit ID %d introuvable\n", article->idProduit);
            disponible = 0;
        }
        
        article = article->suivant;
    }
    
    return disponible;
}
float calculerTotalTVA(Panier *panier, stHach *table, float tauxTVA) {
    float totalHT = 0.0;
    ArticlePanier *article = panier->debut;
    
    printf("Articles :\n");
    
    while (article != NULL) {
        int index = hachage(article->idProduit);
        stProduit *produit = table->Table[index];
        
        while (produit != NULL && produit->id != article->idProduit) {
            produit = produit->suivant;
        }
        
        if (produit != NULL) {
            float st = produit->prix * article->quantite;
            totalHT += st;
            printf("- %s x%d : %.2f€\n", produit->nom, article->quantite, st);
        }
        
        article = article->suivant;
    }
    
    float tva = totalHT * tauxTVA;
    float totalTTC = totalHT + tva;
    
    panier->total = totalTTC;
    return totalTTC;
}
void mettreAJourStock(Panier *panier, stHach *tableHachage) {
    printf("\n IPDATE DU STOCK \n");
    
    ArticlePanier *article = panier->debut;
    int produitsMisesAJour = 0;
    int alertesStock = 0;
    
    while (article != NULL) {
        int index = hachage(article->idProduit);
        stProduit *produit = tableHachage->Table[index];
        
        // Recherche du produit dans la liste chaînée
        while (produit != NULL && produit->id != article->idProduit) {
            produit = produit->suivant;
        }
        
        if (produit != NULL) {
            // Sauvegarde de l'ancien stock
            int ancienStock = produit->quantite;
            
            // Mise à jour du stock
            produit->quantite -= article->quantite;
            
            // Vérification de validité
            if (produit->quantite < 0) {
                printf("ERREUR: Stock négatif pour %s! Réinitialisation à 0\n", 
                       produit->nom);
                produit->quantite = 0;
            }
            
            printf("  %-20s : %3d → %3d (-%d)\n",
                   produit->nom, ancienStock, 
                   produit->quantite, article->quantite);
            
            produitsMisesAJour++;
            
            // Alertes stock faible
            if (produit->quantite == 0) {
                printf("    RUPTURE DE STOCK pour %s!\n", produit->nom);
                alertesStock++;
            } else if (produit->quantite <= 3) {
                printf("    Stock critique pour %s (%d restant)\n", 
                       produit->nom, produit->quantite);
                alertesStock++;
            }
        } else {
            printf("   Produit ID %d non trouvé dans le catalogue\n", 
                   article->idProduit);
        }
        
        article = article->suivant;
    }
    
    printf("\nRésumé: %d produits mis à jour, %d alertes stock\n", 
           produitsMisesAJour, alertesStock);
}
void genererTicket(Panier *panier, stHach *tableHachage, Client *client) {
    printf("\n=== GÉNÉRATION DU TICKET ===\n");
    
    // Obtention de la date et heure actuelles
    time_t maintenant;
    time(&maintenant);
    struct tm *infoDate = localtime(&maintenant);
    
    // Calcul du total
    float totalHT = 0.0;
    ArticlePanier *article = panier->debut;
    
    // Entête du ticket
    printf("\n");
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║            SUPERMARCHÉ XYZ                  ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║ Date: %02d/%02d/%04d  Heure: %02d:%02d          ║\n",
           infoDate->tm_mday, infoDate->tm_mon + 1, 
           infoDate->tm_year + 1900, infoDate->tm_hour, 
           infoDate->tm_min);
    printf("║ Caisse: 01              Ticket: %06d     ║\n", rand() % 1000000);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║ Client: %-34s ║\n", client->nom);
    printf("║ ID Client: %-31d ║\n", client->id);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║                    ARTICLES                  ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    
    int numeroArticle = 1;
    
    while (article != NULL) {
        int index = hachage(article->idProduit);
        stProduit *produit = tableHachage->Table[index];
        
        // Recherche du produit
        while (produit != NULL && produit->id != article->idProduit) {
            produit = produit->suivant;
        }
        
        if (produit != NULL) {
            float sousTotal = produit->prix * article->quantite;
            totalHT += sousTotal;
            
            printf("║ %2d. %-18s x%2d @ %6.2f€ %9.2f€ ║\n",
                   numeroArticle,
                   produit->nom,
                   article->quantite,
                   produit->prix,
                   sousTotal);
        } else {
            printf("║ %2d. PRODUIT INCONNU ID:%d x%2d          ║\n",
                   numeroArticle,
                   article->idProduit,
                   article->quantite);
        }
        
        article = article->suivant;
        numeroArticle++;
    }
    
    // Calcul des taxes
    float tva = totalHT * 0.20;  // TVA à 20%
    float totalTTC = totalHT + tva;
    
    // Pied du ticket
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║ Sous-total                    %14.2f€ ║\n", totalHT);
    printf("║ TVA (20%%)                     %14.2f€ ║\n", tva);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║ TOTAL À PAYER                %14.2f€ ║\n", totalTTC);
    printf("╠══════════════════════════════════════════════╣\n");
    
    // Paiement
    printf("║ Mode paiement: ESPÈCES                      ║\n");
    printf("║ Montant reçu:  %21.2f€ ║\n", totalTTC);
    printf("║ Monnaie rendue: %20.2f€ ║\n", 0.0);
    printf("╠══════════════════════════════════════════════╣\n");
    
    // Informations client mises à jour
    client->totalDepense += totalTTC;
    printf("║ Dépense cumulée client:      %14.2f€ ║\n", client->totalDepense);
    printf("║ Articles achetés: %22d   ║\n", panier->nbArticles);
    printf("╚══════════════════════════════════════════════╝\n");
    
    // Message de remerciement
    printf("\nchoukran de votre visite, %s!\n", client->nom);
    printf("Nous espérons vous revoir bientôt.\n");
    
    // Sauvegarde du total dans le panier
    panier->total = totalTTC;
}
int passageEnCaisse(Panier *panier, stHach *tableHachage, Client *client) {

    printf("\n==================================================\n");
    printf("PASSAGE EN CAISSE - Client: %s (ID: %d)\n", client->nom, client->id);
    printf("==================================================\n");

    // Panier vide
    if (panier->debut == NULL) {
        printf(" Panier vide. Transaction annulée.\n");
        return 0;
    }

    // Calcul du total TTC (TVA 20%)
    float totalTTC = 0.0;
    ArticlePanier *article = panier->debut;

    while (article != NULL) {
        int index = hachage(article->idProduit);
        stProduit *prod = tableHachage->Table[index];

        // Recherche du produit dans la liste chaînée
        while (prod && prod->id != article->idProduit)
            prod = prod->suivant;

        if (prod)
            totalTTC += prod->prix * article->quantite * 1.20;

        article = article->suivant;
    }

    printf("Total estimé : %.2f €\n", totalTTC);

    // Confirmation
    printf("Confirmez-vous cet achat ? (O/N) : ");
    char c;
    scanf(" %c", &c);

    if (c != 'O' && c != 'o') {
        printf(" Transaction annulée.\n");
        return 0;
    }

    // Mise à jour du stock
    mettreAJourStock(panier, tableHachage);

    // Génération ticket
    genererTicket(panier, tableHachage, client);

    // Nettoyage panier
    viderPanier(panier);

    printf("\n Transaction terminée avec succès !\n");
    return 1;
}
int main(){
    Gestion_Produit();
}