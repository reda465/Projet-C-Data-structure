    // TODO
    // Mise a jour de l'arbre binaire apres que le client finit l'achat d'un produit !!
    // Parcours Infixe plus organisé
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
    struct Produit *suivant;
    } stProduit;
    // définition de type client qui sera un element de l'arbre.
    typedef struct Client{
        int id;
        char nom[30];
        float totalDepense;
        struct Client* gauche;
        struct Client* droite;
    }Client;
    void Menu(); //should me updated to the real menu (not implemented yet)
    // définition de type arbre qui sera l'arbre définit par sa racine.
    typedef struct ClientArbre{
        Client* racine;
    }ClientArbre;
    //checkAllocation()
    char* TranslationNull(char* string)
    {
        if(string == NULL) return NULL;
        else 
        {
            int length = strlen(string);
            for(int i =0; i<length;i++)
            {
                if (string[i] == '\n') {
                string[i] = '\0'; break;}
            }
        }
        return string;
    }
    void checkAllocationArbre(ClientArbre* Arbre)
    {
        if(Arbre == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }
    // Initialisation et reservation de l'éspace mémoire.
    ClientArbre* InitArbre(ClientArbre* Arbre){
        Arbre = (ClientArbre*) malloc(sizeof(ClientArbre));
        checkAllocationArbre(Arbre);
        Arbre->racine = NULL;
        return Arbre;
    }
    void Infixe(Client* noeud) //pour ordre alphabétique
    {
        if(noeud != NULL){
        Infixe(noeud->gauche);
        printf("\nInformations sur le client %d:\n\nNom du client : %s\t Total depensé : %.2f\n\n", noeud->id, noeud->nom, noeud->totalDepense);
        Infixe(noeud->droite);
    }
    return;
    }


    Client* creeNoeud(Client client, Client* droite, Client* gauche)
    {
        Client* cli = malloc(sizeof(Client));
        cli->id = client.id;
        strcpy(cli->nom,client.nom);
        cli->totalDepense = client.totalDepense;
        cli->droite = droite;
        cli->gauche = gauche;
        return cli;

    }
    //fct ajouterclient()
    Client* ajouterClient(Client* noeud,Client client)
    {
    if(noeud==NULL) {
    return creeNoeud(client,NULL,NULL);
    }
    else{
        if(strcmp(client.nom , noeud->nom) > 0)
        noeud->droite = ajouterClient(noeud->droite,client);
        else if (strcmp(client.nom , noeud->nom) < 0)
        noeud->gauche = ajouterClient(noeud->gauche,client);
        return noeud;
    }

    }
    Client* rechercherClient(Client cli, Client* noeud)
    {
        if(noeud == NULL) 
        return NULL;
        else if( strcmp(noeud->nom,cli.nom) == 0) return noeud;
        else if( strcmp(cli.nom , noeud->nom) > 0) return rechercherClient(cli,noeud->droite);
        else return rechercherClient(cli,noeud->gauche);
    }
    //fonction min
    Client* min(Client* noeud){
        if(noeud == NULL) return NULL;
        while(noeud->gauche != NULL) noeud = noeud->gauche;
        return noeud;
    }
    Client* supprimerClient(Client* noeud,Client cli)
    {
        if(noeud == NULL)
        return noeud;
        if ( strcmp(noeud->nom,cli.nom) > 0 )
        noeud->gauche = supprimerClient(noeud->gauche,cli);
        else if ( strcmp(noeud->nom,cli.nom) < 0 )
        noeud->droite = supprimerClient(noeud->droite,cli);
        else //trouvee debut de decalage
        {
    //cas d'un arabre sans enfants
        if (noeud->droite == NULL && noeud->gauche == NULL){
        free(noeud);
        return NULL;}
        else if(noeud->droite == NULL){ // pas de fils droit
        Client* tmp = noeud->gauche;
        free(noeud);
        return tmp;
    }
    else if(noeud->gauche == NULL){
        Client* tmp = noeud->droite;
        free(noeud);
        return tmp;
        }
        else {
            //pour conserver l'ordre
            Client* successeur = min(noeud->droite);
            strcpy(noeud->nom, successeur->nom);
            Client buffer;
            strcpy(buffer.nom, successeur->nom);
            noeud->droite = supprimerClient(noeud->droite,buffer);
        }
        return noeud; 
    }

    }
    int forcerLireEntier(void)
    {
        int choix;
        while(1)
        {
        printf("Effectuer un choix : ");

        if(scanf("%d",&choix) == 1)
        {
            if( choix>7 || choix<0 ) 
            {printf("choix Invalide\n");
            continue ;}
            else break;
        } 
        else {while(getchar() != '\n');
        printf("choix Invalide\n");}
        }
        return choix; 
    }

    void sauvegarderArbre(Client* client)
    {
        FILE* file = fopen("clients.txt","a+");
        fprintf(file,"%d|%s|%f\n",client->id,client->nom,client->totalDepense);
        fclose(file);
    }
    void sauvegarderRecursive(Client* client){
    if(client!=NULL){
        sauvegarderRecursive(client->droite);
        sauvegarderArbre(client);
        sauvegarderRecursive(client->gauche);
    }
}

    ClientArbre* chargerArbre(ClientArbre* Arb)
    {
        FILE* file = fopen("clients.txt","r");
        Client buffer;
        if(Arb == NULL)
        {
            Arb = InitArbre(Arb);
        }
        while (fscanf(file,"%d|%[^|]|%f\n",&buffer.id,buffer.nom,&buffer.totalDepense) == 3){
        Arb->racine = ajouterClient(Arb->racine,buffer);
    }
        fclose(file);
        return Arb;
    }
    int switchf(int choix,ClientArbre* ar)
    {
        switch (choix)
        {
        case 1:
            printf("Insertion des clients : \n");
            Client c;
            printf("Entrer l'id :");
            scanf("%d",&c.id);
            while (getchar() != '\n');
            printf("Entrer le nom :");
            fgets(c.nom,sizeof(c.nom),stdin);
            TranslationNull(c.nom);
            c.totalDepense = 0;
            ar->racine = ajouterClient(ar->racine,c);
            return 1;
            break;
        case 2:
        printf("Entrer le nom du client que vous chercher : ");
        fgets(c.nom,sizeof(c.nom),stdin);
        TranslationNull(c.nom);
        Client* buffer = rechercherClient(c,ar->racine);
        if(buffer == NULL) printf("Client non trouvé \n");
        else printf("\n\nAffichage des informations du client %d :\n Nom : %s\t Total Depensé : %.2f \n\n",buffer->id,buffer->nom,buffer->totalDepense);
        break;
        return 1;
        case 3:
        Infixe(ar->racine);
        return 1;
        break;
        case 4:
        printf("Entrer le nom du client que vous voulez supprimer : ");
        fgets(c.nom,sizeof(c.nom),stdin);
        TranslationNull(c.nom);
        buffer = rechercherClient(c,ar->racine);
        if(buffer == NULL)
        {
            printf("Client non trouvé \n");
        }
        else{
        ar->racine = supprimerClient(ar->racine,c);
        printf("Client supprimé avec succés\n");}
        return 1;
        break;
        case 5:
        sauvegarderRecursive(ar->racine);
        return 1;
        break;
        case 6:
        ar = chargerArbre(ar);
        return 1;
        break;
        case 7:
        return 0;
        break;
        default:
            break;
        }
    }
    //affichage menu des options
    int menuClients(void){ //inplement a better asthetic later 
        ClientArbre* ar;
        ar = InitArbre(ar);
        start:
        printf("\n=================ESPACE CLIENTS=====================\n"
            "1. Inserer un client \n"
            "2. Rechercher un client \n" 
            "3. Afficher les client en ordre alphabétique \n" 
            "4. Supprimer un client \n"
            "5. Sauvegarder dans \"clients.txt\"\n" 
            "6. Charger depuis \"clients.txt\"\n"
            "7. Retour Au Menu Principale\n");
            int choix = forcerLireEntier();
            while(getchar() != '\n');
            int k;
            k = switchf(choix,ar);
            if(k == 0) return 0;
            goto start;
    }



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
        printf("7)Retour Au menu principale\n");
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
    int Gestion_Produit(){
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
        return 1;
        break;
        case 2:
        id=Lire_Id("Entrez l'ID du produit que vous voulez modifier \n");
        indexe=hachage(id);
        modifier(HashTable.Table,indexe,id);
        return 1;
        break;
        case 3:
        id=Lire_Id("Entrez l'ID du produit que vous voulez supprimer \n");
        indexe=hachage(id);
        supprimer(HashTable.Table,indexe,id);
        return 1;
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
        return 1;
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
        return 1;
        break;
        case 6:
        Sauvegarder(HashTable.Table);
        return 1;
        break;
        case 7:
        printf("Retour Au Menu Principale ...");
        return 0;
        }

    }while(choix!=0);
    }
    //                               partie passage_en_caisse                        //
    typedef struct ClientFile {
    int idClient;
    struct ClientFile *suivant;
} ClientFile;

typedef struct {
    ClientFile *debut;
    ClientFile *fin;
} FileAttente;//========================================partie historique========================================


//structure de la transaction
 // Chaque transaction correspond à un passage en caisse validé
typedef struct Transaction {
    int id;
    int idClient;
    char nomClient[30];
    float total;
    char dateHeure[20];
    struct Transaction *suivant;
} Transaction;

//structure de la Pile historique LIFO

typedef struct {
    Transaction *tete;
    int nef;
} historique;
historique *historiqueGlobal=NULL;

//Initialisation de la pile
historique* initHistorique() {
    historique *h =(historique*)malloc(sizeof(historique));
    if (!h){
        printf("erreur d'allocation memoire");
        return NULL;
    }
    h->tete = NULL; 
    h->nef = 0;
    return h;
}

 // Crée une transaction à partir des informations de la caisse
Transaction* creerTransaction(int id,int IdClient,char *nomclient,float total){
Transaction *t= (Transaction*)malloc(sizeof(Transaction));
if(!t){
    printf("Erreur allocation Memoire");
    return NULL;
}
t->id=id;
t->idClient=IdClient;
strcpy(t->nomClient,nomclient);
t->total=total;
time_t now = time(NULL);
struct tm *tm_info=localtime(&now);
strftime(t->dateHeure,20,"%Y-%m-%d %H:%M",tm_info);
t->suivant=NULL;
return t ;
}
//Empile une transaction dans l'historique
void pushTransaction( historique *h ,Transaction *t){
   if ( h==NULL || t==NULL)
   return;
   t->suivant= h->tete;
   h->tete = t;
   h->nef++;
}
// Depiler une transaction dans l'historique
Transaction *popTransaction(historique *h){
      if (h->nef==0){
        printf("Historique vide");
        return NULL;
      }
      Transaction *ptr=h->tete;
      h->tete=ptr->suivant;
      ptr->suivant=NULL;
      h->nef--;
      return ptr;
}
//Sauvegarde l'historique dans historique.txt
void sauvegarderHistorique(historique *h) {
    if (!h) 
    return;

    FILE *f=fopen("historique.txt","w");
    if (!f) {
        perror("Erreur ouverture historique.txt");
        return;
    }
    // Parcours de la pile et écriture dans le fichier
    Transaction *ptr=h->tete;
    while (ptr) {
        fprintf(f,"%d|%d|%s|%.2f|%s\n",ptr->id,ptr->idClient,ptr->nomClient,ptr->total,ptr->dateHeure);
        ptr=ptr->suivant;
    }

    fclose(f);
}
// Charge l'historique depuis le fichier historique.txt
historique* chargerHistorique() {
    FILE *f=fopen("historique.txt","r");
    historique *h=initHistorique();
    if (!f)
     return h;
    
    while (1) {
        Transaction *t=malloc(sizeof(*t));
        if (!t) 
        break;

        if (fscanf(f,"%d|%d|%[^|]|%f|%[^\n]\n",&t->id,&t->idClient,t->nomClient,&t->total,t->dateHeure)==5) {
            t->suivant=h->tete;
            h->tete=t;
            h->nef++;
        } else {
            free(t);
            break;
        }
    }
    fclose(f);
    return h;
}

// Affiche toutes les transactions de l'historique
void afficherHistorique(historique *h){
    if (h->nef==0){
    printf("Historique vide");
    return;
}
printf("=================HISTORIQUE DES TRANSACTIONS(%d)=================",h->nef);
Transaction *ptr=h->tete;
while (ptr!=NULL){
    printf("ID:%d | Client:%s(%d) | Total:%.2f DH | Date:%s\n",ptr->id,ptr->nomClient,ptr->idClient,ptr->total,ptr->dateHeure);
    ptr=ptr->suivant;
}
}

  //Menu historique de gestion de l'historique
int menuHistorique(historique *h) {
    int choix;

    do {
        printf("\n========== MENU HISTORIQUE ==========\n");
        printf("1. Afficher l'historique des transactions\n");
        printf("2. Annuler la derniere transaction\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                afficherHistorique(h);
                return 1;
                break;

            case 2: {
                Transaction *t = popTransaction(h);
                if (t != NULL) {
                    printf("Transaction %d annulée (Client %s,%.2f DH)\n",
                           t->id,t->nomClient,t->total);
                    free(t);
                    sauvegarderHistorique(h);
                }
                return 1;
                break;
            }

            case 0:
                printf("Retour au menu précédent...\n");
                return 0;
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);
}
// menu qui s'affiche a l'utilisateur
int menuHistoriqueGlobal() {
    if (historiqueGlobal == NULL) {
        printf("Historique non initialisé.\n");
        return 1;
    }
    int p;
    p = menuHistorique(historiqueGlobal);
    return p;

}


typedef struct CaisseSystem {
    ClientArbre *arbreClients;
    FileAttente *fileAttente;
    stHach *stockProduits;
    historique *historique;
    int dernierIDTransaction;
} CaisseSystem;
// Fonction pour initialiser une file d'attente
FileAttente* initFileAttente() {
    FileAttente *file = (FileAttente*)malloc(sizeof(FileAttente));
    file->debut = NULL;
    file->fin = NULL;
    return file;
}

// Fonction pour ajouter un client à la file d'attente
void ajouterClientFile(FileAttente *file, int idClient) {
    ClientFile *nouveau = (ClientFile*)malloc(sizeof(ClientFile));
    nouveau->idClient = idClient;
    nouveau->suivant = NULL;
    
    if (file->fin == NULL) {  // File vide
        file->debut = file->fin = nouveau;
    } else {
        file->fin->suivant = nouveau;
        file->fin = nouveau;
    }
    printf("Client ID %d ajouté à la file d'attente\n", idClient);
}
void defilerClientFile(FileAttente *file) {
    if (file->debut == NULL) {
        printf("La file d'attente est vide.\n");
        return;
    }
    
    ClientFile *temp = file->debut;
    file->debut = file->debut->suivant;
    
    if (file->debut == NULL) {
        file->fin = NULL;  // La file est maintenant vide
    }
    
    free(temp);
}
// 6. Fonction pour afficher la file d'attente
void afficherFileAttente(FileAttente *file) {
    if (file->debut == NULL) {
        printf("File d'attente vide.\n");
        return;
    }
    printf("\n=== File d'attente ===\n");
    ClientFile *current = file->debut;
    int position = 1;
    
    while (current != NULL) {
        printf("%d. Client ID: %d\n", position++, current->idClient);
        current = current->suivant;
    }
    printf("=====================\n");
}

// Fonction pour chercher un client par ID dans l'arbre (récursif)
Client* chercherClientParID(Client* noeud, int id) {
    if (noeud == NULL) return NULL;
    
    if (noeud->id == id) return noeud;
    
    Client* gauche = chercherClientParID(noeud->gauche, id);
    if (gauche != NULL) return gauche;
    
    return chercherClientParID(noeud->droite, id);
}
// Ajouter panier manuellement
void ajouterPanierManuellement(CaisseSystem *caisse) {
    int idClient;
    char nomClient[30];
    float total;
    printf("\n=== Ajout manuel d'une transaction ===\n");
    printf("ID du client: ");
    scanf("%d", &idClient);
    while(getchar() != '\n');
    
    printf("Nom du client: ");
    fgets(nomClient, sizeof(nomClient), stdin);
    nomClient[strcspn(nomClient, "\n")] = 0;
    
    printf("Total de la transaction: ");
    scanf("%f", &total);
    
    // Vérifier si le client existe
    Client *client = chercherClientParID(caisse->arbreClients->racine, idClient);
    if (client != NULL) {
        client->totalDepense += total;
        printf("Client %s mis a jour: +%.2f DH\n", client->nom, total);
    } 
}
float calculerTotalPanier(stHach *stock, int *produitsAchetes, int *quantites, int nbProduits) {
    float total = 0.0;
    for (int i = 0; i < nbProduits; i++) {
        int idProduit = produitsAchetes[i];
        int quantite = quantites[i];
        int index = hachage(idProduit);
        // Recherche du produit
        stProduit *produit = stock->Table[index];
        while (produit != NULL && produit->id != idProduit) {
            produit = produit->suivant;
        }
        if (produit != NULL) {
            total += produit->prix * quantite;
        }
    }
    return total;
}
int verifierStock(stHach *stock, int idProduit, int quantiteDemandee) {
    int index = hachage(idProduit);
    stProduit *produit = stock->Table[index];
    // Recherche du produit dans la liste chaînée
    while (produit != NULL && produit->id != idProduit) {
        produit = produit->suivant;
    }
    // Cas 1: Produit non trouvé
    if (produit == NULL) {
        printf(" Produit ID %d non trouvé dans le stock.\n", idProduit);
        return -1; // Code d'erreur: produit non existant
    }
    // Cas 2: Stock insuffisant
    if (produit->quantite < quantiteDemandee) {
        printf("  Stock insuffisant pour '%s' (ID: %d)\n", produit->nom, idProduit);
        printf("   Quantité demandée: %d | Disponible: %d\n", quantiteDemandee, produit->quantite);
        return 0; // Code d'erreur: stock insuffisant
    }
    // Cas 3: Stock suffisant
    printf(" Stock disponible pour '%s'\n", produit->nom);
    printf("   Prix unitaire: %.2f DH | Quantité disponible: %d\n", produit->prix, produit->quantite);
    
    // Calcul et affichage du sous-total
    float sousTotal = produit->prix * quantiteDemandee;
    printf("   Sous-total pour %d unité(s): %.2f DH\n", quantiteDemandee, sousTotal);
    return 1; // Code de succès: stock OK
}
// Fonction unique pour générer et sauvegarder le ticket
void genererEtSauvegarderTicket(Client *client, int *produitsAchetes, int *quantites, 
                                stHach *stock, int nbProduits, float total) {
    // 1. Création nom fichier
    char nomFichier[50];
    sprintf(nomFichier, "ticket_%d.txt", client->id);
    // 2. Ouverture fichier
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf(" Erreur: Impossible de créer le fichier ticket.\n");
        return;
    }
    // 3. Préparation date/heure
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char dateHeure[30];
    strftime(dateHeure, 30, "%Y-%m-%d %H:%M:%S", tm_info);
    // 4. ÉCRITURE DANS LE FICHIER (format optimisé)
    fprintf(fichier, "==========================================\n");
    fprintf(fichier, "           SUPERMARCHé XYZ               \n");
    fprintf(fichier, "           TICKET DE CAISSE              \n");
    fprintf(fichier, "==========================================\n");
    fprintf(fichier, "Client    : %s\n", client->nom);
    fprintf(fichier, "ID Client : %d\n", client->id);
    fprintf(fichier, "Date/Heure: %s\n", dateHeure);
    fprintf(fichier, "------------------------------------------\n");
    fprintf(fichier, "ARTICLES ACHETES:\n");
    fprintf(fichier, "------------------------------------------\n");
    // 5. Liste des articles (optimisé)
    for (int i = 0; i < nbProduits; i++) {
        int idProduit = produitsAchetes[i];
        int quantite = quantites[i];
        int index = hachage(idProduit);
        // Recherche produit
        stProduit *produit = stock->Table[index];
        while (produit != NULL && produit->id != idProduit) {
            produit = produit->suivant;
        }
        if (produit != NULL) {
            float prixUnitaire = produit->prix;
            float sousTotal = prixUnitaire * quantite;
            
            fprintf(fichier, "• %-20s x%-3d @ %.2f DH = %6.2f DH\n",
                    produit->nom, quantite, prixUnitaire, sousTotal);
        }
    }
    // 6. Total et informations
    fprintf(fichier, "------------------------------------------\n");
    fprintf(fichier, "TOTAL A PAYER  : %26.2f DH\n", total);
    fprintf(fichier, "------------------------------------------\n");
    fprintf(fichier, "Nombre d'articles : %d\n", nbProduits);
    fprintf(fichier, "Ticket ID         : %d\n", client->id);
    fprintf(fichier, "Fichier           : %s\n", nomFichier);
    fprintf(fichier, "==========================================\n");
    fprintf(fichier, "        MERCI POUR VOTRE ACHAT !         \n");
    fprintf(fichier, "==========================================\n");
    // 7. Fermeture fichier
    fclose(fichier);
    // 8. AFFICHAGE À L'ÉCRAN simple
    printf("\n");
    printf("==========================================\n");
    printf("           TICKET DE CAISSE              \n");
    printf("==========================================\n");
    printf("Client    : %s\n", client->nom);
    printf("Date/Heure: %s\n", dateHeure);
    printf("------------------------------------------\n");
    // Affichage articles (résumé)
    for (int i = 0; i < nbProduits; i++) {
        int idProduit = produitsAchetes[i];
        int quantite = quantites[i];
        int index = hachage(idProduit);
        
        stProduit *produit = stock->Table[index];
        while (produit != NULL && produit->id != idProduit) {
            produit = produit->suivant;
        }
        
        if (produit != NULL) {
            printf("• %s x%d = %.2f DH\n", 
                   produit->nom, quantite, produit->prix * quantite);
        }
    }
    printf("------------------------------------------\n");
    printf("TOTAL     : %.2f DH\n", total);
    printf("==========================================\n");
    printf(" Ticket sauvegardé dans: %s\n", nomFichier);
}
// Fonction pour servir le prochain client
void servirProchainClient(CaisseSystem *caisse) {
    // ÉTAPE 1: Vérifier si la file n'est pas vide
    if (caisse->fileAttente == NULL || caisse->fileAttente->debut == NULL) {
        printf("\n Aucun client en attente!\n");
        afficherFileAttente(caisse->fileAttente);
        return;
    }
    // ÉTAPE 2: Récupérer le premier client de la file (FIFO)
    ClientFile *clientEnTete = caisse->fileAttente->debut;
    int idClient = clientEnTete->idClient;
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("               SERVICE DU CLIENT ID: %d                   \n", idClient);
    printf("═══════════════════════════════════════════════════════════\n");
    // ÉTAPE 3: Chercher le client dans l'arbre
    Client *client = chercherClientParID(caisse->arbreClients->racine, idClient);
    if (client == NULL) {
        printf(" ERREUR: Client ID %d non trouvé dans la base de données!\n", idClient);
        // Retirer quand même de la file
        defilerClientFile(caisse->fileAttente);
        return;
    }
    // ÉTAPE 4: Afficher les informations du client
    printf(" CLIENT: %s (ID: %d)\n", client->nom, client->id);
    printf(" Total déjà dépensé: %.2f DH\n", client->totalDepense);
    printf("-----------------------------------------------------------\n");
    // ÉTAPE 5: Saisie du panier
    int produitsAchetes[100];
    int quantites[100];
    int nbProduits = 0;
    float totalAchat = 0.0;
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║        SAISIE DU PANIER               ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Entrez les produits (ID=-1 pour terminer):\n\n");
    while (nbProduits < 100) {
        int idProduit, quantite;
        printf("→ ID Produit (-1 pour terminer): ");
        scanf("%d", &idProduit);
        if (idProduit == -1) {
            break;
        }
        printf("→ Quantité désirée: ");
        scanf("%d", &quantite);
        // Vérifier le stock
        int resultatStock = verifierStock(caisse->stockProduits, idProduit, quantite);
        if (resultatStock == 1) { // Stock disponible
            // Ajouter au panier
            produitsAchetes[nbProduits] = idProduit;
            quantites[nbProduits] = quantite;
            nbProduits++;
            // Mettre à jour le stock immédiatement
            int index = hachage(idProduit);
            stProduit *produit = caisse->stockProduits->Table[index];
            while (produit != NULL && produit->id != idProduit) {
                produit = produit->suivant;
            }
            if (produit != NULL) {
                produit->quantite -= quantite;
                float sousTotal = produit->prix * quantite;
                totalAchat += sousTotal;
                printf("Ajouté: %s ×%d = %.2f DH\n", 
                       produit->nom, quantite, sousTotal);
            }
        } else if (resultatStock == 0) {
            printf(" Article non ajouté au panier (stock insuffisant)\n");
        } else {
            printf(" Article non ajouté au panier (produit non trouvé)\n");
        }
        printf(" Sous-total courant: %.2f DH | Articles: %d\n\n", totalAchat, nbProduits);
    }
    // ÉTAPE 6: Vérifier si le panier n'est pas vide
    if (nbProduits == 0) {
        printf("\n Panier vide - Transaction annulée\n");
        return;
    }
    // ÉTAPE 7: Calculer le total final (vérification)
    float totalVerifie = calculerTotalPanier(caisse->stockProduits, produitsAchetes, quantites, nbProduits);
    // ÉTAPE 8: Confirmation
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("RÉCAPITULATIF FINAL:\n");
    printf("• Client: %s\n", client->nom);
    printf("• Nombre d'articles: %d\n", nbProduits);
    printf("• Montant total: %.2f DH\n", totalVerifie);
    printf("═══════════════════════════════════════════════════════════\n");
    printf("\nConfirmer la transaction? (o/n): ");
    char confirmation;
    scanf(" %c", &confirmation);
    if (confirmation != 'o' && confirmation != 'O') {
        printf("\n Transaction annulée\n");
        // Rembourser le stock (annuler les modifications)
        for (int i = 0; i < nbProduits; i++) {
            int idProduit = produitsAchetes[i];
            int quantite = quantites[i];
            int index = hachage(idProduit);
            stProduit *produit = caisse->stockProduits->Table[index];
            while (produit != NULL && produit->id != idProduit) {
                produit = produit->suivant;
            }
            if (produit != NULL) {
                produit->quantite += quantite;
            }
        }
        
        return;
    }
    // ÉTAPE 9: Mettre à jour le client
    float ancienTotal = client->totalDepense;
    client->totalDepense += totalVerifie;
    
    printf("\n Mise à jour des informations client:\n");
    printf("  %s: %.2f DH → %.2f DH (+%.2f DH)\n", 
           client->nom, ancienTotal, client->totalDepense, totalVerifie);
//creation d'une transaction pour l'empiler dans l'historique (Aymen)
    Transaction *t=creerTransaction(caisse->dernierIDTransaction++,client->id,client->nom,totalVerifie);
    if (caisse->historique != NULL) {
    pushTransaction(caisse->historique,t);
    sauvegarderHistorique(caisse->historique);
}
    // ÉTAPE 10: Générer le ticket
    genererEtSauvegarderTicket(client, produitsAchetes, quantites, caisse->stockProduits, nbProduits, totalVerifie);
    
    // ÉTAPE 11: Retirer le client de la file d'attente
    caisse->fileAttente->debut = clientEnTete->suivant;
    if (caisse->fileAttente->debut == NULL) {
        caisse->fileAttente->fin = NULL;
    }
    free(clientEnTete);
    
    // ÉTAPE 12: Sauvegarder les modifications
    printf("\n Sauvegarde des données...\n");
    sauvegarderRecursive(caisse->arbreClients->racine);
    Sauvegarder(caisse->stockProduits->Table);
    printf(" Données sauvegardées avec succès!\n");
    
    // ÉTAPE 13: Message final
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf(" TRANSACTION TERMINÉE AVEC SUCCÈS!\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Client %s servi et retiré de la file d'attente.\n", client->nom);
    printf("Montant total: %.2f DH\n", totalVerifie);
    printf("═══════════════════════════════════════════════════════════\n");
}


int menuCaisse() {
    int choix;
    
    // INITIALISATION 
    CaisseSystem caisse;  
    

    caisse.arbreClients = InitArbre(NULL);
    caisse.arbreClients = chargerArbre(caisse.arbreClients);
    
    caisse.stockProduits = (stHach*)malloc(sizeof(stHach));
    initialiser_Table(caisse.stockProduits->Table);
    charger(caisse.stockProduits->Table);  // Pas de &
    
    caisse.fileAttente = initFileAttente();
    caisse.historique = historiqueGlobal;
;
    caisse.dernierIDTransaction = 1;
        // BOUCLE DU MENU
    
    do {
        printf("\n=== MENU CAISSE ===\n");
        printf("1. Ajouter un client a la file d'attente\n");
        printf("2. Servir le prochain client\n");
        printf("3. Afficher la file d'attente\n");
        printf("4. Ajouter une transaction manuellement\n");
        printf("0. Retour au menu principal\n");
        printf("Choix: ");
        scanf("%d", &choix);
        
        while(getchar() != '\n');  // Nettoyer buffer
        
        switch (choix) {
            case 1: {
                int idClient;
                printf("Entrez l'ID du client a ajouter: ");
                scanf("%d", &idClient);
                ajouterClientFile(caisse.fileAttente, idClient);  // . car variable
                return 1;
                break;
            }
            case 2:
                servirProchainClient(&caisse);  // & pour passer l'adresse
                return 1;
                break;
            case 3:
                afficherFileAttente(caisse.fileAttente);  // . car variable
                return 1;
                break;
            case 4:
                ajouterPanierManuellement(&caisse);  // & pour passer l'adresse
                return 1;
                break;
            case 0:
                printf("\nRetour au menu principal...\n");
                return 0;
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
}











//                               partie main                        //
#include <windows.h>

int main() {
    start:
    SetConsoleOutputCP(65001);
    historiqueGlobal = chargerHistorique(); 
    printf("\n\nBienvenu dans l'espace du supermarche\n"
           "1. Espace Clients\n"
           "2. Espace Produits\n"
           "3. Passage en caisse\n"
           "4. Menu Historique\n"
           "Choisir a quel espace vous voulez acceder: ");
    
    int choice;
    scanf("%d",&choice);
    
    switch (choice) {
        case 1:
        int p;
            p = menuClients();
            if (p==0)
            goto start;
            break;
        case 2:
        int l;
            l = Gestion_Produit();
            if (l==0)
            goto start;

            break;
        case 3:
        int b;
           b =  menuCaisse(); 
           if (b==0) 
           goto start;
            break;
        case 4:
        int h;
            h = menuHistoriqueGlobal();
            if (h==0)
            goto start;
            break;
        default:
            printf("Choix invalide!\n");
            break;
    }
    
    return 0;
}