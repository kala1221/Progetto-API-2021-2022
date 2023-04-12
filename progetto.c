#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Nodo{;
    struct Nodo* left, *right ,*listainternasucc, *listainternaprec;
    char* string;
};
struct bst{
    struct Nodo* root;
};
char frominttochar(int g){
    if(g>=0 && g<=9)
        return g+48;
    else if(g<=35)
        return g+55;
    else if(g<= 61)
        return g+61;
    else if(g==62)
        return '-';
    else
        return '_';

}
int fromchartoint(char g){
    if (g >= 48 && g <= 57)
        return g - 48;
    else if (g >= 65 && g <= 90)
        return g - 55;
    else if (g >= 97 && g <= 122)
        return g - 61;
    else if (g == 45)
        return 62;
    else
        return 63;
}// ci sono solo 64 caratteri ammissibili, queste due funzione convertono le lettere di tipo char 0-9(codificati in base alla tabella dei char con 48-57), a-z(codificati con 48-57), A-z(codificati con 65-90), "-" e "_" in indici interi che sono uno di seguito all'altro, e viceversa,  per semplificare i diversi controlli (es ciclo for)
int precordinelex(char*stringa1, char*stringa2, int k){
    int i=0;
    while(i<k){
        if(stringa1[i]<stringa2[i])
            return 1;
        if(stringa1[i]>stringa2[i])
            return 0;
        else
            i++;
    }
    return 0;
}//date due stringhe stabilisce se la prima stringa precede la seconda (return 1) o meno(return 0)
int stessastringa(char* stringa1, char* stringa2, int k){
    int i=0;
    while(i<k){
        if(stringa1[i]!=stringa2[i])
            return 0;
        i++;
    }
    return 1;
}//stabilisce se due stringhe sono uguali
int searchstringa(struct bst T, char* stringa, int k){
    struct Nodo* punt;
    punt = T.root;
    while(punt!=NULL) {
        if (stessastringa(punt->string, stringa, k))
            return 1;
        if(precordinelex(stringa, punt->string, k))
            punt=punt->left;
        else
            punt=punt->right;
    }
    return 0;
} // O(h), data una stringa in input stabilisce se questa si trova nell'albero
void aggiungifil(struct Nodo** reftesta, struct Nodo* nodoconstringa) {
    struct Nodo* punt=nodoconstringa;
    if((*reftesta)==NULL)
        (*reftesta)=punt;
    else{
        (*reftesta)->listainternaprec=punt;
        punt->listainternasucc=(*reftesta);
        (*reftesta)=punt;
    }
}
// O(1), aggiunge in cima alla lista interna un dato nodo con una stringa già contenuta
void confronta(int k, char* parolariferimento, char* parolainserita, char* filtro, char*gratina, char memoria[k][64], char* temprifpermem, unsigned short* beccate, char* mem2) {
    char character, ch, arraysupp[64]={0}, arraysup2[64]={0};
    int i = 0, ind, ind2;
    while(i<k){
        ch=parolariferimento[i];
        character=parolainserita[i];
        if(ch==character){
            if(gratina[i]=='<'){
                gratina[i] = character;
                ind= fromchartoint(character);
                arraysup2[ind]++;
                if(arraysup2[ind]>temprifpermem[ind]){
                    temprifpermem[ind]=arraysup2[ind];
                    (*beccate)++;
                }

            }
            filtro[i]='+';
        }
        else{
            ind = fromchartoint(ch);
            arraysupp[ind]++;
            ind2=fromchartoint(character);
            filtro[i]='/';
            if(memoria[i][ind2]=='<')
                memoria[i][ind2]='z';
        }
        i++;
    }
    i=0;
    while(i<k){
        while(i<k && filtro[i]=='+')
            i++;
        if(i==k)
            break;
        character=parolainserita[i];
        ind2=fromchartoint(character);
        if(arraysupp[ind2]!=0){
            if((*beccate)<k){
                arraysup2[ind2]++;
                if(arraysup2[ind2]>temprifpermem[ind2]){
                    temprifpermem[ind2]=arraysup2[ind2];
                    memoria[i][ind2]='|';
                    (*beccate)++;
                }
            }
            filtro[i]='|';
            arraysupp[ind2]--;
        }
        else
            mem2[ind2]=1;
        i++;
    }

}
// O(2k), funzione chiamata per ogni parola "giocata": parolariferimento è la parola da indovinare, parolainserita è la parola inserita dal giocatore, filtro è la stringa di +,/ e | da stampare, gratina è un array di supporto inizializzato con '<' che tiene traccia delle lettere "beccate" dal giocatore
void confronta2(int k, char* parolariferimento, char* parolainserita, char* filtro, char*gratina, char memoria[k][64]){
    char character, ch, arraysupp[64]={0};
    int i = 0, ind, ind2;
    while(i<k){
        ch=parolariferimento[i];
        character=parolainserita[i];
        if(ch==character){
            if(gratina[i]=='<')
                gratina[i] = character;
            filtro[i]='+';
        }
        else{
            ind = fromchartoint(ch);
            arraysupp[ind]++;
            filtro[i]='/';
            ind2=fromchartoint(character);
            if(memoria[i][ind2]=='<')
                memoria[i][ind2]='z';

        }
        i++;
    }
    i=0;
    while(i<k){
        while(i<k && filtro[i]=='+')
            i++;
        if(i==k)
            break;
        character=parolainserita[i];
        ind2=fromchartoint(character);
        if(arraysupp[ind2]!=0){
            filtro[i]='|';
            arraysupp[ind2]--;
        }
        i++;
    }
}
// O(2k), versione semplificata della funzione precedente nel caso in cui il giocatore sappia ormai quali e quante volte appaiono le lettere nella parola da indovinare.
struct Nodo* creanodo(struct bst T,char* stringaa, int k){
    struct Nodo *q;
    q=(struct Nodo*)malloc(sizeof(struct Nodo));
    (*q).right=NULL;
    (*q).left=NULL;
    (*q).string=stringaa;
    (*q).listainternasucc=NULL;
    (*q).listainternaprec=NULL;
    return q;
}
void aggiungifilordinatamente(struct Nodo** reftesta, struct Nodo* punt, int k){
    struct Nodo *temp=(*reftesta), *prec=NULL;
    if((*reftesta)==NULL)
        (*reftesta)=punt;
    else{
        while(temp!=NULL && precordinelex(temp->string, punt->string, k)){
            prec=temp;
            temp=temp->listainternasucc;
        }
        if(prec==NULL){
            (*reftesta)->listainternaprec=punt;
            punt->listainternasucc=(*reftesta);
            (*reftesta)=punt;
        }
        else{
            if(temp!=NULL)
                temp->listainternaprec=punt;
            punt->listainternasucc=temp;
            prec->listainternasucc=punt;
            punt->listainternaprec=prec;
        }
    }
}//aggiunge nella corretta posizione alfabetica una stringa nella lista interna all'albero
void aggiungialvocab(struct Nodo** refroot, struct Nodo* z, int k) {
    struct Nodo *x, *y;
    x = (*refroot);
    y=NULL;
    while (x != NULL) {
        y=x;
        if (precordinelex(z->string, x->string, k))
            x = x->left;
        else
            x = x->right;
    }
    if(y==NULL)
        (*refroot)=z;
    else if (precordinelex(z->string, y->string, k))
        y->left = z;
    else
        y->right = z;
    z->left=NULL;
    z->right=NULL;
}//aggiunge una parola nell'albero, in ordine alfabetico
void stampainordinedalista(struct Nodo* testa){
    struct Nodo* curr;
    curr=testa;
    while(curr!=NULL){
        printf("%s\n", curr->string);
        curr=curr->listainternasucc;
    }
}
void aggiungialvocab2(struct Nodo** refroot,struct Nodo** reftesta, struct Nodo* z, int k) {
    struct Nodo *x= (*refroot), *y, *temp=NULL, *temp2=NULL;
    char control=0;
    y=NULL;
    while (x != NULL) {
        y=x;
        if (precordinelex(z->string, x->string, k)){
            x = x->left;
            if(x !=NULL && (x->listainternasucc!=NULL|| x->listainternaprec!=NULL)){
                temp=x;
            }
        }
        else{
            x = x->right;
            if(x !=NULL && (x->listainternasucc!=NULL|| x->listainternaprec!=NULL)){
                temp=x;
            }
        }
    }
    if(temp!=NULL){
        if(precordinelex(temp->string, z->string, k))
            control=1;
        else
            control=2;
    }
    if(temp==NULL){
        aggiungifilordinatamente(reftesta, z, k);
    }
    else if(control==1){
        while(temp->listainternasucc!=NULL && precordinelex(temp->listainternasucc->string, z->string, k))
            temp=temp->listainternasucc;
        temp2=temp->listainternasucc;
        temp->listainternasucc=z;
        z->listainternaprec=temp;
        z->listainternasucc=temp2;
        if(temp2!=NULL)
            temp2->listainternaprec=z;
    }
    else if(control==2){
        while(temp->listainternaprec!=NULL && precordinelex(z->string, temp->listainternaprec->string, k))
            temp=temp->listainternaprec;
        temp2=temp->listainternaprec;
        temp->listainternaprec=z;
        z->listainternasucc=temp;
        z->listainternaprec=temp2;
        if(temp2!=NULL)
            temp2->listainternasucc=z;
        else
            (*reftesta)=z;
    }
    if(y==NULL)
        (*refroot)=z;
    else if (precordinelex(z->string, y->string, k))
        y->left = z;
    else
        y->right = z;
}//O(h), funzione che mi ha permesso di velocizzare di molto l'algoritmo: mentre aggiungo una stringa nell'albero, controllo se scorrendo riesco a beccare una stringa che è anche contenuta nella lista interna, se sì mi salvo il riferimento al nodo, così da poter aggiungere più velocemente la stringa appena inserita. Se mentre scendo ne becco un'altra, allora salvo il riferimento a quella. Alla fine avrò salvato una stringa che è molto "vicina" alfabeticamente alla stringa che sto inserendo, permettendo così di inserire più velocemente la nuova stringa nella lista interna.
void stampainordineint(struct bst T,struct Nodo* n){
    if(n!=NULL){
        stampainordineint(T, (*n).left);
        printf("%s\n", (*n).string);
        stampainordineint(T, (*n).right);
    }
}
void stampainordine(struct bst T){
    struct Nodo* x=T.root;
    stampainordineint(T,x);
}
int confrontafiltro(char *parolainserita, char *filtro, char *stringa, int k){
    int i=0, ind, ind2;
    char chins, chstr, arraysupp[64]={0}, arraysup2[64]={0};
    while(i<k){
        chins=parolainserita[i];
        chstr=stringa[i];
        if(filtro[i]=='+'){
            if(chins != chstr)
                return 0;
        }
        else {
            ind=fromchartoint(chins);
            ind2=fromchartoint(chstr);
            if (chins == chstr)
                return 0;
            if (filtro[i] == '|'){
                arraysupp[ind2]--;
                if(arraysupp[ind2]<0 && arraysup2[ind2]==1)
                    return 0;
                arraysupp[ind]++;
            }
            else{
                if(arraysupp[ind]<0)
                    return 0;
                arraysupp[ind2]--;
                if(arraysupp[ind2]<0 && arraysup2[ind2]==1)
                    return 0;
                arraysup2[ind]=1;
            }
        }
        i++;
    }
    i=0;
    while(i<k){
        ind=fromchartoint(parolainserita[i]);
        if(arraysupp[ind]>0)
            return 0;
        i++;
    }
    return 1;
}
//O(2k) (strcpy e while)
struct Nodo *cancelladallalista(struct Nodo* testa,char* parolains, char*filtro, int k, int*p){
    struct Nodo* curr=testa, *prec=NULL, *temp=NULL, *miao=NULL;
    while(curr!=NULL){
        if(!confrontafiltro(parolains, filtro, curr->string, k)){
            temp=curr;
            miao=curr->listainternasucc;
            temp->listainternasucc=NULL;
            temp->listainternaprec=NULL;
            (*p)--;
            while(miao!=NULL && !confrontafiltro(parolains, filtro, miao->string, k)){
                temp=miao;
                miao=miao->listainternasucc;
                temp->listainternasucc=NULL;
                temp->listainternaprec=NULL;
                (*p)--;
            }
            if(prec==NULL){
                testa=miao;
                miao->listainternaprec=NULL;
            }
            else{
                prec->listainternasucc=miao;
                if(miao!=NULL)
                    miao->listainternaprec=prec;
            }
            curr=miao;
        }
        else{
            prec=curr;
            curr=curr->listainternasucc;}
    }
    return testa;
}
//O(n)
void cancellaint(struct bst T, struct Nodo* root){
    if(root!=NULL){
        cancellaint(T,(*root).left);
        cancellaint(T,(*root).right);
        free(root->string);
        free(root);
    }
}
void cancella(struct bst T){
    struct Nodo *x=T.root;
    cancellaint(T, x);
}
void pulisci2(struct Nodo* testa){
    struct Nodo* temp, *temp2;
    temp=testa;
    testa= NULL;
    temp2=temp;
    while(temp2!=NULL){
        temp2=temp2->listainternasucc;
        temp->listainternasucc=NULL;
        temp->listainternaprec=NULL;
        temp=temp2;
    }
}
int confrontinoperinserisci(char* stringa, char* gratina, int k, char memoria[k][64], char* temprifpermem, char * mem2, char* parolariferimento) {
    int i = 0, ind;
    char mem1[64]={0};
    for(int g=0; g<k; g++){
        ind=fromchartoint(parolariferimento[g]);
        mem1[ind]=temprifpermem[ind];
    }
    while(i<k){
        ind=fromchartoint(stringa[i]);
        if(gratina[i]!='<'){
            if(gratina[i]!=stringa[i]){
                return 0;}
            mem1[ind]--;
        }
        else {
            if (memoria[i][ind]!='<'){
                return 0;}
            mem1[ind]--;
            if(mem1[ind]<0 && mem2[ind]==1){
                return 0;}
        }
        i++;
    }
    for(int b=0; b<64 ; b++)
        if(mem1[b]>0){
            return 0;}
    return 1;
}
//O(64 + k + 64)
void aggiungiallalistadallalbero(struct Nodo* root,char* parolains, struct Nodo** reftesta,char* filtro, int k, int*p){
    if(root!=NULL){
        aggiungiallalistadallalbero(root->right,parolains, reftesta, filtro, k, p );
        if(confrontafiltro(parolains, filtro, root->string,k)){
            aggiungifil(reftesta,root);}
        else
            (*p)--;
        aggiungiallalistadallalbero(root->left,parolains, reftesta, filtro, k, p );
    }
}
//O(n*(2k+h))


int main() {
    int *p, nparvoc=0, m=0;
    short h;
    unsigned short k,ind, ntentativi,l=0, *beccate;
    if(scanf("%hd", &k)){}
    char ch, ch1='z',esito=-2, modalita[30], parolariferimento[k],temprifpermem[64]={0}, filtro[k+1], gratina[k], *stringa, stringhina[k], memoria[k][64], mem2[64]={0};
    filtro[k]='\0';
    p=&m;
    beccate=&l;
    struct bst T;
    struct Nodo* testina=NULL, *temp=NULL;
    T.root=NULL;
    h=k-1;
    do{
        gratina[h] = '<';
        for(int f=0; f<64; f++)
            memoria[h][f]='<';
        h--;
    }while(h+1);
    while(1){
        ch1=getchar_unlocked();// primo carattere
        while((ch1== (char) 13) || (ch1== (char) 10))
            ch1=getchar_unlocked();
        if(ch1 == '+'||ch1==EOF)
            break;
        stringa=(char*) malloc((k+1));
        stringa[0]=ch1;
        stringa[k]='\0';
        for(int i=1; i<k; i++)
            stringa[i]=getchar_unlocked();
        temp=creanodo(T,stringa, k);
        aggiungialvocab(&T.root, temp, k);
        nparvoc++;
    } // inserimento delle parole da aggiungere al vocabolario prima dell'inizio della partita
    m=nparvoc;
    while(1) {
        ind=0;
        ch=getchar_unlocked();
        while((ch== (char) 13) || (ch== (char) 10) || ch=='+')
            ch=getchar_unlocked();
        if(ch == EOF)
            break;
        do{
            if(ind==0 || ind==10)
                modalita[ind]=ch;
            ch=getchar_unlocked();
            ind++;
        }while(ch!=(char) 13 && ch!='\n');
        if(esito==-2 && modalita[10]=='f'){
            while(1){
                ch1=getchar_unlocked();// primo carattere
                while((ch1== (char) 13) || (ch1== (char) 10))
                    ch1=getchar_unlocked();
                if(ch1 == '+'||ch1==EOF)
                    break;
                stringa=(char*) malloc((k+1));
                stringa[0]=ch1;
                stringa[k]='\0';
                for(int i=1; i<k; i++)
                    stringa[i]=getchar_unlocked();
                temp=creanodo(T,stringa, k);
                aggiungialvocab(&T.root, temp, k);
                nparvoc++;
            }
            m=nparvoc;
            continue;
        }
        if (modalita[0] == 'n' || modalita[10] == 'f' || modalita[0] == 's') {
            if (modalita[0] == 's'){
                if(testina==NULL)
                    stampainordine(T);
                else
                    stampainordinedalista(testina);
            }
            else if(modalita[0]=='n') {
                if (esito != -2) {
                    pulisci2(testina);
                    testina=NULL;
                    (*p) = nparvoc;
                    h=k-1;
                    for(int o=0; o<64; o++)
                        mem2[o]=0;
                    do{
                        gratina[h] = '<';
                        ind=fromchartoint(parolariferimento[h]);
                        temprifpermem[ind]=0;
                        for(int f=0; f<64; f++)
                            memoria[h][f]='<';
                        h--;
                    }while(h+1);
                    l=0;
                }
                esito = 1;
                while ((ch == (char) 13) || (ch == (char) 10))
                    ch = getchar_unlocked();
                parolariferimento[0] = ch;
                for (int i = 1; i < k; i++)
                    parolariferimento[i] = getchar_unlocked();
                if (scanf("%hd", &ntentativi) == 1){}
            }
            while (1) {
                do{
                    ch1=getchar_unlocked();
                }while((ch1== (char) 13) || (ch1== (char) 10));
                if (ch1 == '+')
                    break;
                if(ch1==EOF){
                    esito=-1;
                    break;
                }
                stringhina[0] = ch1;
                for (int w = 1; w < k; w++)
                    stringhina[w] =getchar_unlocked();
                if (!searchstringa(T, stringhina,k)) {
                    printf("not_exists\n");
                    continue;
                }
                if (stessastringa(stringhina, parolariferimento,k)) {
                    printf("ok\n");
                    esito=1;
                    break;
                }
                if(l<k)
                    confronta(k, parolariferimento, stringhina, filtro, gratina,memoria,temprifpermem, beccate, mem2);
                else
                    confronta2(k, parolariferimento, stringhina, filtro, gratina,memoria);
                if(testina==NULL)
                    aggiungiallalistadallalbero(T.root, stringhina, &testina, filtro, k, p);
                else
                    testina = cancelladallalista(testina, stringhina, filtro, k, p);
                printf("%s\n%d\n", filtro, *p);
                ntentativi--;
                if (ntentativi == 0) {
                    printf("ko\n");
                    break;
                }

            }//da nuova partita fino a +, puntatore getchar_unlocked a carattere successivo al +, esito 0 se nuova modalita, 1 se vinto, 2 se fine tentativi
            if(esito==-1)
                break;
            continue;
        }
        else {
            while(1){
                ch1=getchar_unlocked();// primo carattere
                while((ch1== (char) 13) || (ch1== (char) 10))
                    ch1=getchar_unlocked();
                if(ch1 == '+'){
                    break;}
                if(ch1==EOF){
                    break;
                }
                stringa=(char*) malloc((k+1));
                stringa[0]=ch1;
                stringa[k]='\0';
                for(int i=1; i<k; i++){
                    stringa[i]=getchar_unlocked();
                }
                temp=creanodo(T, stringa, k);
                if(testina==NULL){
                    aggiungialvocab(&T.root, temp,  k);
                    (*p)++;
                }
                else if(confrontinoperinserisci(stringa, gratina, k, memoria,temprifpermem, mem2, parolariferimento)){
                    aggiungialvocab2(&T.root, &testina, temp, k);
                    (*p)++;
                }
                else
                    aggiungialvocab(&T.root, temp,  k);
                nparvoc++;
            }
            if(esito==-1)
                break;
            continue;}

    }// partita intera
    return 0;
}
