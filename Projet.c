    // TODO
    // Mise a jour de l'arbre binaire apres que le client finit l'achat d'un produit !!
    // Parcours Infixe plus organisé
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
    void switchf(int choix,ClientArbre* ar)
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
            break;
        case 2:
        printf("Entrer le nom du client que vous chercher : ");
        fgets(c.nom,sizeof(c.nom),stdin);
        TranslationNull(c.nom);
        Client* buffer = rechercherClient(c,ar->racine);
        if(buffer == NULL) printf("Client non trouvé \n");
        else printf("\n\nAffichage des informations du client %d :\n Nom : %s\t Total Depensé : %.2f \n\n",buffer->id,buffer->nom,buffer->totalDepense);
        break;
        case 3:
        Infixe(ar->racine);
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

        break;
        case 5:
        sauvegarderRecursive(ar->racine);
        break;
        case 6:
        ar = chargerArbre(ar);
        break;
        case 7:
        Menu();
        break;
        default:
            break;
        }
    }
    //affichage menu des options
    void menuClients(void){ //inplement a better asthetic later 
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
            switchf(choix,ar);
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
    #include<windows.h>
    int main(){
        SetConsoleOutputCP(65001); //pour windows lecture des accents en terminal VsCode
        printf("Bienvenu dans l'éspace du supermarché\n"
        "1. Espace Clients\n"
         "2. Espace Produits\n");
        printf("Choisir à quel espace vous voulez acceder :");
        int choice;
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            menuClients();
            break;
        case 2:
             Gestion_Produit();
             break;
        default:
            break;
        }
        
        
    }