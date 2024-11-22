#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a node in the BST and doubly linked list
struct Nodo{
    struct Nodo* left;               // Left child in BST
    struct Nodo* right;              // Right child in BST
    struct Nodo* listainternasucc;   // Next node in internal list
    struct Nodo* listainternaprec;   // Previous node in internal list
    char* string;                    // Word stored in the node
};

// Definition of the BST
struct bst{
    struct Nodo* root;               // Root of the BST
};

// Converts an integer to a character based on a custom mapping
char frominttochar(int g){
    if(g >= 0 && g <= 9)
        return g + 48;               // 0-9
    else if(g <= 35)
        return g + 55;               // A-Z
    else if(g <= 61)
        return g + 61;               // a-z
    else if(g == 62)
        return '-';                  // Hyphen
    else
        return '_';                  // Underscore
}

// Converts a character to an integer based on a custom mapping
int fromchartoint(char g){
    if (g >= 48 && g <= 57)
        return g - 48;               // 0-9
    else if (g >= 65 && g <= 90)
        return g - 55;               // A-Z
    else if (g >= 97 && g <= 122)
        return g - 61;               // a-z
    else if (g == 45)
        return 62;                   // Hyphen
    else
        return 63;                   // Underscore
}
// There are only 64 allowable characters. These two functions convert characters into integer indices and vice versa, simplifying various checks.

// Compares two strings lexicographically
int precordinelex(char* stringa1, char* stringa2, int k){
    int i = 0;
    while(i < k){
        if(stringa1[i] < stringa2[i])
            return 1;                // stringa1 precedes stringa2
        if(stringa1[i] > stringa2[i])
            return 0;                // stringa1 does not precede stringa2
        else
            i++;
    }
    return 0;
}

// Checks if two strings are identical
int stessastringa(char* stringa1, char* stringa2, int k){
    int i = 0;
    while(i < k){
        if(stringa1[i] != stringa2[i])
            return 0;                // Strings are not equal
        i++;
    }
    return 1;                        // Strings are equal
}

// Searches for a string in the BST
int searchstringa(struct bst T, char* stringa, int k){
    struct Nodo* punt = T.root;
    while(punt != NULL) {
        if (stessastringa(punt->string, stringa, k))
            return 1;                // String found
        if(precordinelex(stringa, punt->string, k))
            punt = punt->left;       // Search left subtree
        else
            punt = punt->right;      // Search right subtree
    }
    return 0;                        // String not found
}

// Adds a node to the front of the internal list
void aggiungifil(struct Nodo** reftesta, struct Nodo* nodoconstringa) {
    struct Nodo* punt = nodoconstringa;
    if((*reftesta) == NULL)
        (*reftesta) = punt;          // First node in the list
    else{
        (*reftesta)->listainternaprec = punt;
        punt->listainternasucc = (*reftesta);
        (*reftesta) = punt;
    }
}
// O(1), adds a given node with an already contained string to the top of the internal list

// Compares the input word with the reference word and updates clues
void confronta(int k, char* parolariferimento, char* parolainserita, char* filtro, char* gratina, char memoria[k][64], char* temprifpermem, unsigned short* beccate, char* mem2) {
    char character, ch, arraysupp[64] = {0}, arraysup2[64] = {0};
    int i = 0, ind, ind2;
    
    // First pass: check for correct letters in correct positions
    while(i < k){
        ch = parolariferimento[i];
        character = parolainserita[i];
        if(ch == character){
            if(gratina[i] == '<'){
                gratina[i] = character;           // Update known letters
                ind = fromchartoint(character);
                arraysup2[ind]++;
                if(arraysup2[ind] > temprifpermem[ind]){
                    temprifpermem[ind] = arraysup2[ind];
                    (*beccate)++;                 // Increase the count of correctly guessed letters
                }
            }
            filtro[i] = '+';                      // Correct letter and position
        }
        else{
            ind = fromchartoint(ch);
            arraysupp[ind]++;                     // Count of letters in reference word
            ind2 = fromchartoint(character);
            filtro[i] = '/';                      // Incorrect letter or position
            if(memoria[i][ind2] == '<')
                memoria[i][ind2] = 'z';           // Mark letter as not in this position
        }
        i++;
    }
    i = 0;
    // Second pass: check for correct letters in wrong positions
    while(i < k){
        while(i < k && filtro[i] == '+')
            i++;
        if(i == k)
            break;
        character = parolainserita[i];
        ind2 = fromchartoint(character);
        if(arraysupp[ind2] != 0){
            if((*beccate) < k){
                arraysup2[ind2]++;
                if(arraysup2[ind2] > temprifpermem[ind2]){
                    temprifpermem[ind2] = arraysup2[ind2];
                    memoria[i][ind2] = '|';       // Letter is in the word but wrong position
                    (*beccate)++;
                }
            }
            filtro[i] = '|';
            arraysupp[ind2]--;
        }
        else
            mem2[ind2] = 1;                       // Letter not in the word
        i++;
    }
}
// O(2k), function called for each guessed word. Updates the clues based on the comparison with the reference word.

// Simplified version of 'confronta' when the player knows all the letters
void confronta2(int k, char* parolariferimento, char* parolainserita, char* filtro, char* gratina, char memoria[k][64]){
    char character, ch, arraysupp[64] = {0};
    int i = 0, ind, ind2;
    
    // First pass: check for correct letters in correct positions
    while(i < k){
        ch = parolariferimento[i];
        character = parolainserita[i];
        if(ch == character){
            if(gratina[i] == '<')
                gratina[i] = character;
            filtro[i] = '+';
        }
        else{
            ind = fromchartoint(ch);
            arraysupp[ind]++;
            filtro[i] = '/';
            ind2 = fromchartoint(character);
            if(memoria[i][ind2] == '<')
                memoria[i][ind2] = 'z';
        }
        i++;
    }
    i = 0;
    // Second pass: check for correct letters in wrong positions
    while(i < k){
        while(i < k && filtro[i] == '+')
            i++;
        if(i == k)
            break;
        character = parolainserita[i];
        ind2 = fromchartoint(character);
        if(arraysupp[ind2] != 0){
            filtro[i] = '|';
            arraysupp[ind2]--;
        }
        i++;
    }
}
// O(2k), simplified version of the previous function when the player already knows which letters appear and how many times in the reference word.

// Creates a new node for the BST
struct Nodo* creanodo(struct bst T, char* stringaa, int k){
    struct Nodo *q;
    q = (struct Nodo*)malloc(sizeof(struct Nodo));
    q->right = NULL;
    q->left = NULL;
    q->string = stringaa;
    q->listainternasucc = NULL;
    q->listainternaprec = NULL;
    return q;
}

// Adds a node to the internal list in the correct alphabetical position
void aggiungifilordinatamente(struct Nodo** reftesta, struct Nodo* punt, int k){
    struct Nodo *temp = (*reftesta), *prec = NULL;
    if((*reftesta) == NULL)
        (*reftesta) = punt;          // First node in the list
    else{
        while(temp != NULL && precordinelex(temp->string, punt->string, k)){
            prec = temp;
            temp = temp->listainternasucc;
        }
        if(prec == NULL){
            (*reftesta)->listainternaprec = punt;
            punt->listainternasucc = (*reftesta);
            (*reftesta) = punt;
        }
        else{
            if(temp != NULL)
                temp->listainternaprec = punt;
            punt->listainternasucc = temp;
            prec->listainternasucc = punt;
            punt->listainternaprec = prec;
        }
    }
}

// Adds a node to the BST in alphabetical order
void aggiungialvocab(struct Nodo** refroot, struct Nodo* z, int k) {
    struct Nodo *x = (*refroot), *y = NULL;
    while (x != NULL) {
        y = x;
        if (precordinelex(z->string, x->string, k))
            x = x->left;             // Insert in left subtree
        else
            x = x->right;            // Insert in right subtree
    }
    if(y == NULL)
        (*refroot) = z;              // Tree was empty
    else if (precordinelex(z->string, y->string, k))
        y->left = z;
    else
        y->right = z;
    z->left = NULL;
    z->right = NULL;
}

// Prints the internal list in order
void stampainordinedalista(struct Nodo* testa){
    struct Nodo* curr = testa;
    while(curr != NULL){
        printf("%s\n", curr->string);
        curr = curr->listainternasucc;
    }
}

// Optimized function to add a node to the BST and internal list
void aggiungialvocab2(struct Nodo** refroot, struct Nodo** reftesta, struct Nodo* z, int k) {
    struct Nodo *x = (*refroot), *y = NULL, *temp = NULL, *temp2 = NULL;
    char control = 0;
    // Traverse the BST to find the insertion point
    while (x != NULL) {
        y = x;
        if (precordinelex(z->string, x->string, k)){
            x = x->left;
            if(x != NULL && (x->listainternasucc != NULL || x->listainternaprec != NULL)){
                temp = x;            // Save reference to node in internal list
            }
        }
        else{
            x = x->right;
            if(x != NULL && (x->listainternasucc != NULL || x->listainternaprec != NULL)){
                temp = x;            // Save reference to node in internal list
            }
        }
    }
    // Determine where to insert in the internal list
    if(temp != NULL){
        if(precordinelex(temp->string, z->string, k))
            control = 1;             // Insert after temp
        else
            control = 2;             // Insert before temp
    }
    if(temp == NULL){
        aggiungifilordinatamente(reftesta, z, k); // Insert in order
    }
    else if(control == 1){
        // Insert after temp
        while(temp->listainternasucc != NULL && precordinelex(temp->listainternasucc->string, z->string, k))
            temp = temp->listainternasucc;
        temp2 = temp->listainternasucc;
        temp->listainternasucc = z;
        z->listainternaprec = temp;
        z->listainternasucc = temp2;
        if(temp2 != NULL)
            temp2->listainternaprec = z;
    }
    else if(control == 2){
        // Insert before temp
        while(temp->listainternaprec != NULL && precordinelex(z->string, temp->listainternaprec->string, k))
            temp = temp->listainternaprec;
        temp2 = temp->listainternaprec;
        temp->listainternaprec = z;
        z->listainternasucc = temp;
        z->listainternaprec = temp2;
        if(temp2 != NULL)
            temp2->listainternasucc = z;
        else
            (*reftesta) = z;         // Update head of internal list
    }
    // Insert the node into the BST
    if(y == NULL)
        (*refroot) = z;              // Tree was empty
    else if (precordinelex(z->string, y->string, k))
        y->left = z;
    else
        y->right = z;
}

// Prints the BST in-order
void stampainordineint(struct bst T, struct Nodo* n){
    if(n != NULL){
        stampainordineint(T, n->left);
        printf("%s\n", n->string);
        stampainordineint(T, n->right);
    }
}

void stampainordine(struct bst T){
    struct Nodo* x = T.root;
    stampainordineint(T, x);
}

// Checks if a string satisfies the current filter (clues)
int confrontafiltro(char *parolainserita, char *filtro, char *stringa, int k){
    int i = 0, ind, ind2;
    char chins, chstr, arraysupp[64] = {0}, arraysup2[64] = {0};
    // Compare each character based on the filter clues
    while(i < k){
        chins = parolainserita[i];   // Character in the guessed word
        chstr = stringa[i];          // Character in the candidate word
        if(filtro[i] == '+'){
            if(chins != chstr)
                return 0;            // Must match exactly
        }
        else {
            ind = fromchartoint(chins);
            ind2 = fromchartoint(chstr);
            if (chins == chstr)
                return 0;            // Should not match at this position
            if (filtro[i] == '|'){
                arraysupp[ind2]--;
                if(arraysupp[ind2] < 0 && arraysup2[ind2] == 1)
                    return 0;
                arraysupp[ind]++;
            }
            else{
                if(arraysupp[ind] < 0)
                    return 0;
                arraysupp[ind2]--;
                if(arraysupp[ind2] < 0 && arraysup2[ind2] == 1)
                    return 0;
                arraysup2[ind] = 1;
            }
        }
        i++;
    }
    i = 0;
    while(i < k){
        ind = fromchartoint(parolainserita[i]);
        if(arraysupp[ind] > 0)
            return 0;
        i++;
    }
    return 1;                        // Candidate word matches the filter
}

// Removes words from the internal list that do not match the current filter
struct Nodo *cancelladallalista(struct Nodo* testa, char* parolains, char* filtro, int k, int* p){
    struct Nodo* curr = testa, *prec = NULL, *temp = NULL, *next_node = NULL;
    while(curr != NULL){
        if(!confrontafiltro(parolains, filtro, curr->string, k)){
            temp = curr;
            next_node = curr->listainternasucc;
            temp->listainternasucc = NULL;
            temp->listainternaprec = NULL;
            (*p)--;                  // Decrement the count of possible words
            // Remove consecutive non-matching nodes
            while(next_node != NULL && !confrontafiltro(parolains, filtro, next_node->string, k)){
                temp = next_node;
                next_node = next_node->listainternasucc;
                temp->listainternasucc = NULL;
                temp->listainternaprec = NULL;
                (*p)--;
            }
            if(prec == NULL){
                testa = next_node;   // Update head of the list
                if(next_node != NULL)
                    next_node->listainternaprec = NULL;
            }
            else{
                prec->listainternasucc = next_node;
                if(next_node != NULL)
                    next_node->listainternaprec = prec;
            }
            curr = next_node;
        }
        else{
            prec = curr;
            curr = curr->listainternasucc;
        }
    }
    return testa;                    // Return updated head of the list
}

// Recursively frees memory allocated for the BST nodes
void cancellaint(struct bst T, struct Nodo* root){
    if(root != NULL){
        cancellaint(T, root->left);
        cancellaint(T, root->right);
        free(root->string);
        free(root);
    }
}

void cancella(struct bst T){
    struct Nodo *x = T.root;
    cancellaint(T, x);
}

// Cleans up the internal list by resetting pointers
void pulisci2(struct Nodo* testa){
    struct Nodo* temp = testa, *temp2 = NULL;
    while(temp != NULL){
        temp2 = temp->listainternasucc;
        temp->listainternasucc = NULL;
        temp->listainternaprec = NULL;
        temp = temp2;
    }
}

// Checks if a new word can be added to the internal list based on the current clues
int confrontinoperinserisci(char* stringa, char* gratina, int k, char memoria[k][64], char* temprifpermem, char* mem2, char* parolariferimento) {
    int i = 0, ind;
    char mem1[64] = {0};
    // Initialize the memory for letters in the reference word
    for(int g = 0; g < k; g++){
        ind = fromchartoint(parolariferimento[g]);
        mem1[ind] = temprifpermem[ind];
    }
    // Check each character against the clues
    while(i < k){
        ind = fromchartoint(stringa[i]);
        if(gratina[i] != '<'){
            if(gratina[i] != stringa[i]){
                return 0;            // Must match the known letter
            }
            mem1[ind]--;
        }
        else {
            if (memoria[i][ind] != '<'){
                return 0;            // Letter cannot be in this position
            }
            mem1[ind]--;
            if(mem1[ind] < 0 && mem2[ind] == 1){
                return 0;            // Letter not present in the reference word
            }
        }
        i++;
    }
    // Check if any letters are unaccounted for
    for(int b = 0; b < 64; b++)
        if(mem1[b] > 0){
            return 0;
        }
    return 1;                        // Word can be added to the internal list
}

// Adds possible words from the BST to the internal list based on the current clues
void aggiungiallalistadallalbero(struct Nodo* root, char* parolains, struct Nodo** reftesta, char* filtro, int k, int* p){
    if(root != NULL){
        aggiungiallalistadallalbero(root->right, parolains, reftesta, filtro, k, p);
        if(confrontafiltro(parolains, filtro, root->string, k)){
            aggiungifil(reftesta, root);     // Add to internal list
        }
        else
            (*p)--;                          // Word does not match, decrement count
        aggiungiallalistadallalbero(root->left, parolains, reftesta, filtro, k, p);
    }
}

// Main function
int main() {
    int *p, nparvoc = 0, m = 0;
    short h;
    unsigned short k, ind, ntentativi, l = 0, *beccate;
    if(scanf("%hd", &k)){}                   // Read the length of the words
    char ch, ch1 = 'z', esito = -2, modalita[30], parolariferimento[k], temprifpermem[64] = {0}, filtro[k+1], gratina[k], *stringa, stringhina[k], memoria[k][64], mem2[64] = {0};
    filtro[k] = '\0';                        // Null-terminate the filter string
    p = &m;
    beccate = &l;
    struct bst T;
    struct Nodo* testina = NULL, *temp = NULL;
    T.root = NULL;
    h = k - 1;
    // Initialize gratina and memoria arrays
    do{
        gratina[h] = '<';
        for(int f = 0; f < 64; f++)
            memoria[h][f] = '<';
        h--;
    }while(h + 1);
    // Read the initial vocabulary
    while(1){
        ch1 = getchar_unlocked();            // First character
        while((ch1 == (char) 13) || (ch1 == (char) 10))
            ch1 = getchar_unlocked();
        if(ch1 == '+' || ch1 == EOF)
            break;
        stringa = (char*) malloc((k + 1));
        stringa[0] = ch1;
        stringa[k] = '\0';
        for(int i = 1; i < k; i++)
            stringa[i] = getchar_unlocked();
        temp = creanodo(T, stringa, k);
        aggiungialvocab(&T.root, temp, k);   // Add to BST
        nparvoc++;                           // Increment vocabulary count
    }
    m = nparvoc;                             // Total number of words
    // Main game loop
    while(1) {
        ind = 0;
        ch = getchar_unlocked();
        while((ch == (char) 13) || (ch == (char) 10) || ch == '+')
            ch = getchar_unlocked();
        if(ch == EOF)
            break;
        // Read command (e.g., 'nuova_partita', 'stampa_filtrate', 'inserisci_inizio')
        do{
            if(ind == 0 || ind == 10)
                modalita[ind] = ch;
            ch = getchar_unlocked();
            ind++;
        }while(ch != (char) 13 && ch != '\n');
        // If the game hasn't started yet and 'inserisci_fine' command is received
        if(esito == -2 && modalita[10] == 'f'){
            // Read and add words to the vocabulary
            while(1){
                ch1 = getchar_unlocked();    // First character
                while((ch1 == (char) 13) || (ch1 == (char) 10))
                    ch1 = getchar_unlocked();
                if(ch1 == '+' || ch1 == EOF)
                    break;
                stringa = (char*) malloc((k + 1));
                stringa[0] = ch1;
                stringa[k] = '\0';
                for(int i = 1; i < k; i++)
                    stringa[i] = getchar_unlocked();
                temp = creanodo(T, stringa, k);
                aggiungialvocab(&T.root, temp, k);
                nparvoc++;
            }
            m = nparvoc;
            continue;
        }
        // Handle different commands
        if (modalita[0] == 'n' || modalita[10] == 'f' || modalita[0] == 's') {
            if (modalita[0] == 's'){
                // 'stampa_filtrate' command
                if(testina == NULL)
                    stampainordine(T);       // Print all words
                else
                    stampainordinedalista(testina); // Print filtered words
            }
            else if(modalita[0] == 'n') {
                // 'nuova_partita' command
                if (esito != -2) {
                    // Reset game state
                    pulisci2(testina);
                    testina = NULL;
                    (*p) = nparvoc;
                    h = k - 1;
                    for(int o = 0; o < 64; o++)
                        mem2[o] = 0;
                    do{
                        gratina[h] = '<';
                        ind = fromchartoint(parolariferimento[h]);
                        temprifpermem[ind] = 0;
                        for(int f = 0; f < 64; f++)
                            memoria[h][f] = '<';
                        h--;
                    }while(h + 1);
                    l = 0;
                }
                esito = 1;
                // Read the reference word and number of attempts
                while ((ch == (char) 13) || (ch == (char) 10))
                    ch = getchar_unlocked();
                parolariferimento[0] = ch;
                for (int i = 1; i < k; i++)
                    parolariferimento[i] = getchar_unlocked();
                if (scanf("%hd", &ntentativi) == 1){}
            }
            // Start guessing loop
            while (1) {
                do{
                    ch1 = getchar_unlocked();
                }while((ch1 == (char) 13) || (ch1 == (char) 10));
                if (ch1 == '+')
                    break;
                if(ch1 == EOF){
                    esito = -1;
                    break;
                }
                // Read the guessed word
                stringhina[0] = ch1;
                for (int w = 1; w < k; w++)
                    stringhina[w] = getchar_unlocked();
                if (!searchstringa(T, stringhina, k)) {
                    printf("not_exists\n");
                    continue;
                }
                if (stessastringa(stringhina, parolariferimento, k)) {
                    printf("ok\n");
                    esito = 1;               // Player guessed the word
                    break;
                }
                if(l < k)
                    confronta(k, parolariferimento, stringhina, filtro, gratina, memoria, temprifpermem, beccate, mem2);
                else
                    confronta2(k, parolariferimento, stringhina, filtro, gratina, memoria);
                if(testina == NULL)
                    aggiungiallalistadallalbero(T.root, stringhina, &testina, filtro, k, p);
                else
                    testina = cancelladallalista(testina, stringhina, filtro, k, p);
                printf("%s\n%d\n", filtro, *p); // Print clues and remaining possible words
                ntentativi--;
                if (ntentativi == 0) {
                    printf("ko\n");
                    break;
                }
            }
            if(esito == -1)
                break;
            continue;
        }
        else {
            // 'inserisci_inizio' command
            while(1){
                ch1 = getchar_unlocked();    // First character
                while((ch1 == (char) 13) || (ch1 == (char) 10))
                    ch1 = getchar_unlocked();
                if(ch1 == '+'){
                    break;
                }
                if(ch1 == EOF){
                    break;
                }
                stringa = (char*) malloc((k + 1));
                stringa[0] = ch1;
                stringa[k] = '\0';
                for(int i = 1; i < k; i++){
                    stringa[i] = getchar_unlocked();
                }
                temp = creanodo(T, stringa, k);
                if(testina == NULL){
                    aggiungialvocab(&T.root, temp, k);
                    (*p)++;
                }
                else if(confrontinoperinserisci(stringa, gratina, k, memoria, temprifpermem, mem2, parolariferimento)){
                    aggiungialvocab2(&T.root, &testina, temp, k);
                    (*p)++;
                }
                else
                    aggiungialvocab(&T.root, temp, k);
                nparvoc++;
            }
            if(esito == -1)
                break;
            continue;
        }
    }
    return 0;
}
