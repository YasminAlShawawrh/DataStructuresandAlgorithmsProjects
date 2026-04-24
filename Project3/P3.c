//Name:Yasmin Mohamed Al shawawrh
//ID:1220848
//Section number:1
//Project #3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 997
/*------------------------------------------------------------*/
typedef struct AVL
{
    char*data;//the word
    int frequency;//the number of repeated word
    struct AVL*right;//pointer to the right of the tree
    struct AVL*left;//pointer to the left of the tree
    int height;//to keep the balance of AVL tree
} AVL;
//we need to implement array of hash nodes
typedef struct HashNode
{
    char* data;//the word
    int frequency;//the number of repeated word
} HashNode;
HashNode* hashTable[HASH_TABLE_SIZE] = {0};//array of hash nodes
/*------------------------------------------------------------*/
//functions
void displayMenu();
//functions to AVL tree
AVL*loadTheInputFile();
int isalphabetical(int c);
AVL*insertAVL(AVL*t,char*word);
AVL*createAVLNode(char*word);
int height(AVL*node);
int max(int a,int b);
AVL* singleRotateWithLeft(AVL*n2);
AVL* doubleRotateWithLeft(AVL*n3);
AVL* singleRotateWithRight(AVL*n2);
AVL* doubleRotateWithRight(AVL*n3);
AVL* deleteAVL(AVL*t,char*word);
AVL* findMin(AVL*t);
void printInOrder(AVL*t);
AVL* searchAVL(AVL* t, char* word);
int NumberOfElementsOnTheAVLTree(AVL*t);
//functions to hash table
int nextPrime(int num);
int prePrime(int num);
HashNode* createHashTable(int size);
void buildHashTable(AVL*copyToHashTabl,HashNode*hashTable, int size);
void insertToTheHashTable(HashNode hashTable[], int size, char*word, int frequency);
unsigned int hash1(char* data, int size);
unsigned int hash2(char* data, int size);
void printHashTable(HashNode hashTable[], int size);
void deleteFromHashTable(HashNode hashTable[], int size, char*word);
void searchHashTable(HashNode hashTable[], int size, char*word);
void printTheStatistics(HashNode hashTable[],int size, int num);
int NumberOfElementsOnTheHashTable(HashNode hashTable[],int size);
double loadFactor(HashNode hashTable[],int size);
HashNode* buildRehashingHashTable(HashNode hashTable[],int size);
/*------------------------------------------------------------*/
int main()
{
    displayMenu();
    int op;
    scanf("%d",&op);
    int counter1 = 0;
    int counter2 = 0;
    AVL*root=NULL;
    AVL*copyToHashTable=NULL;
    HashNode* hashTable = NULL;
    HashNode* rehashTable = NULL;
    while(op!=12)
    {
        switch(op)
        {
        case 1:
            if(counter1<1)
            {
                root =loadTheInputFile();
                copyToHashTable=loadTheInputFile();
                printf("The file is successfully loaded!\n");
                counter1++;
                break;
            }
            else
                printf("You already loaded the file!!\n");
            break;
        case 2:
            if(counter2<1)
            {
                if(root!=NULL)
                {
                    printf("AVL tree created.\n");
                    counter2++;
                }
                else
                    printf("Load the file at first.\n");
            }
            else
                printf("You already create the AVL tree!!\n");
            break;
        case 3:
            if(root==NULL)
            {
                printf("The the AVL tree is Empty.\n");
                break;
            }
            printf("please enter the word you want to add:\n");
            char str[20];
            scanf("%s",str);
            if(searchAVL(root,str))
            {
                printf("The word is already exist so we increase the frequency.\n");
                root=insertAVL(root,str);
                break;
            }
            root=insertAVL(root,str);
            printf("The word is added.\n");
            break;
        case 4:
            if(root==NULL)
            {
                printf("The the AVL tree is Empty.\n");
                break;
            }
            printf("please enter the word you want to delete:\n");
            char strr[20];
            scanf("%s",strr);
            AVL*find=searchAVL(root,strr);
            if(find)
            {
                if(find->frequency>1)
                    printf("The word is already exist so we decrease the frequency.\n");
                else
                    printf("The word is deleted .\n");
                root=deleteAVL(root,strr);
                break;
            }
            else
                printf("%s not found in the AVL tree.\n", strr);
            break;
        case 5:
            if(root==NULL)
            {
                printf("There is no data to print.\n");
                break;
            }
            printInOrder(root);
            break;
        case 6:
            if(root==NULL)
            {
                printf("There is no data to create the hash table.\n");
                break;
            }
            int numberOfElements = NumberOfElementsOnTheAVLTree(copyToHashTable);
            int hashSize = nextPrime(numberOfElements * 2); // table size = first prime number > 2 * number of elements
            hashTable = createHashTable(hashSize);
            buildHashTable(copyToHashTable, hashTable, hashSize);
            printf("The hash table is created.\n");
            printHashTable(hashTable,hashSize);
            break;
        case 7:
            if(root==NULL)
            {
                printf("There is no hash table to insert an element.\n");
                break;
            }
            if(hashTable==NULL)
            {
                printf("create the hash table at first.\n");
                break;
            }
            printf("please enter the word you want to add:\n");
            char word[20];
            scanf("%s",word);
            insertToTheHashTable(hashTable,hashSize,word,1);
            printf("The word is added.\n");
            printHashTable(hashTable,hashSize);
            break;
        case 8:
            if(root==NULL)
            {
                printf("There is no hash table to delete an element.\n");
                break;
            }
            if(hashTable==NULL)
            {
                printf("create the hash table at first.\n");
                break;
            }
            printf("please enter the word you want to delete:\n");
            char s[20];
            scanf("%s",s);
            deleteFromHashTable(hashTable,hashSize,s);
            printHashTable(hashTable,hashSize);
            break;
        case 9:
            if(root==NULL)
            {
                printf("There is no hash table to search an element.\n");
                break;
            }
            if(hashTable==NULL)
            {
                printf("create the hash table at first.\n");
                break;
            }
            printf("please enter the word you want to search:\n");
            char r[20];
            scanf("%s",r);
            searchHashTable(hashTable,hashSize,r);
            break;
        case 10:
            if(root==NULL)
            {
                printf("There is no hash table.\n");
                break;
            }
            if(hashTable==NULL)
            {
                printf("create the hash table at first.\n");
                break;
            }
            printf("please enter a number:\n");
            int num;
            scanf("%d",&num);
            printTheStatistics(hashTable,hashSize,num);
            break;
        case 11:
            if(root==NULL)
            {
                printf("There is no hash table.\n");
                break;
            }
            if(hashTable==NULL)
            {
                printf("create the hash table at first.\n");
                break;
            }
            double l = loadFactor(hashTable,hashSize);
            printf("The load Factor is :%lf\n",l);
            rehashTable=buildRehashingHashTable(hashTable,hashSize);
            if(rehashTable!=NULL)
            {
                int newSize=nextPrime(hashSize*2);
                if(rehashTable!=NULL)
                    printHashTable(rehashTable,newSize);
                hashSize=newSize;
                hashTable=rehashTable;
            }
            break;
        default:
            printf("No such operation! please try again.\n");
        }
        printf("--------------------------------------------------------------\n");
        displayMenu();
        scanf("%d",&op);
    }
    if(op==12)
        printf("Thank you for using my program, goodbye.\n");
    return 0;
}
/*------------------------------------------------------------*/
void displayMenu()
{
    printf("Select which option you want to do :\n\n");
    printf("1. Load data from the file.\n");
    printf("2. Create the AVL tree.\n");
    printf("3. Insert a word to the AVL tree.\n");
    printf("4. Delete a word from the AVL tree.\n");
    printf("5. Print the words as sorted in the AVL tree.\n");
    printf("6. Create the Hash Table.\n");
    printf("7. Insert a word to the Hash table.\n");
    printf("8. Delete a word from the hash table.\n");
    printf("9. Search for a word in the hash table and print its frequency.\n");
    printf("10. Print words statistics.\n");
    printf("11. Rehashing .\n");
    printf("12. Exit the application.\n\n");
    printf("number of option :\n");
}
/*------------------------------------------------------------*/
//case 1
AVL* loadTheInputFile()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Unable to open the file.\n");
        return NULL;
    }

    AVL* root = NULL;
    char line[100];
    while (fgets(line, sizeof(line), input) != NULL)  //split each line
    {
        char* word = strtok(line, " \n");//split the words if there is a space or new line
        while (word != NULL)
        {
            char apWord[50];
            int j = 0;
            for (int i = 0; word[i] != '\0'; i++)//while word i does not equal null terminal
            {
                if (isalphabetical(tolower(word[i])))//ignoring all input except the alphabetical characters
                {
                    apWord[j++] =tolower(word[i]);
                }
            }
            apWord[j] = '\0';
            root = insertAVL(root,apWord);//insert the word into the AVL tree
            word = strtok(NULL," \n");//get the next word by split the words if there is a space or new line
        }
    }
    fclose(input);
    return root;
}
/*------------------------------------------------------------*/
//case 1
int isalphabetical(int c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}
/*------------------------------------------------------------*/
//case 1 & 2
AVL* insertAVL(AVL* t, char* word)
{
    char lowerWrd[50];
    strcpy(lowerWrd,word);
    for(int i = 0 ; lowerWrd[i]; i++)
    {
        lowerWrd[i]=tolower(lowerWrd[i]);
    }
    if (t == NULL)//for the root
    {
        t = createAVLNode(lowerWrd);
    }
    else if (strcmp(lowerWrd, t->data) > 0)//insert to the right
    {
        t->right = insertAVL(t->right, lowerWrd);
        if (height(t->right) - height(t->left) == 2)//check the balance
        {
            if (strcmp(lowerWrd, t->right->data) > 0)
            {
                t = singleRotateWithRight(t);
            }
            else
            {
                t = doubleRotateWithRight(t);
            }
        }
    }
    else if (strcmp(lowerWrd, t->data) < 0)//insert to the left
    {
        t->left = insertAVL(t->left, lowerWrd);
        if (height(t->left) - height(t->right) == 2)//check the balance
        {
            if (strcmp(lowerWrd, t->left->data) < 0)
            {
                t = singleRotateWithLeft(t);
            }
            else
            {
                t = doubleRotateWithLeft(t);
            }
        }
    }
    else//if the word already exists, increment its frequency when the strcmp = 0
    {
        t->frequency++;
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}
/*------------------------------------------------------------*/
//case 1 & 2
AVL*createAVLNode(char*word)
{
    AVL* newNode = (AVL*)malloc(sizeof(AVL));
    if(newNode==NULL)
    {
        printf("Out of memory.\n");
        return NULL;
    }
    newNode->data = (char*)malloc(strlen(word) + 1);//+1 for null terminal
    if(newNode->data==NULL)
    {
        printf("Out of memory.\n");
        return NULL;
    }
    strcpy(newNode->data, word);
    newNode->frequency = 1;//one word
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;//first word
    return newNode;
}
/*------------------------------------------------------------*/
int height(AVL* node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}
/*------------------------------------------------------------*/
int max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}
/*------------------------------------------------------------*/
//functions to the rotate
AVL* singleRotateWithLeft(AVL* n2)
{
    AVL* n1 = n2->left;
    n2->left = n1->right;
    n1->right = n2;

    n2->height = max(height(n2->left), height(n2->right)) + 1;
    n1->height = max(height(n1->left), n2->height) + 1;

    return n1;
}
AVL* doubleRotateWithLeft(AVL* n3)
{
    n3->left = singleRotateWithRight(n3->left);
    return singleRotateWithLeft(n3);
}
AVL* singleRotateWithRight(AVL* n2)
{
    AVL* n1 = n2->right;
    n2->right = n1->left;
    n1->left = n2;

    n2->height = max(height(n2->left), height(n2->right)) + 1;
    n1->height = max(n2->height, height(n1->right)) + 1;

    return n1;
}
AVL* doubleRotateWithRight(AVL* n3)
{
    n3->right = singleRotateWithLeft(n3->right);
    return singleRotateWithRight(n3);
}
/*------------------------------------------------------------*/
//case 4
AVL* deleteAVL(AVL* t, char* word)
{
    char lowerWrd[50];
    strcpy(lowerWrd,word);
    for(int i = 0 ; lowerWrd[i]; i++)
    {
        lowerWrd[i]=tolower(lowerWrd[i]);
    }
    if (t == NULL)
    {
        return NULL;//the word does not found
    }
    if (strcmp(lowerWrd, t->data) < 0)
    {
        t->left = deleteAVL(t->left, lowerWrd);
    }
    else if (strcmp(lowerWrd, t->data) > 0)
    {
        t->right = deleteAVL(t->right, lowerWrd);
    }
    else//we find the word
    {
        if (t->frequency > 1)
        {
            t->frequency--; // Decrement the frequency
            return t;
        }
        if (t->left == NULL)// Node with only one child or no child
        {
            AVL* temp = t->right;
            free(t);
            return temp;
        }
        else if (t->right == NULL)
        {
            AVL* temp = t->left;
            free(t);
            return temp;
        }
        AVL* temp = findMin(t->right);//delete with two children
        strcpy(t->data, temp->data);
        t->frequency = temp->frequency;
        t->right = deleteAVL(t->right, temp->data);
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    if (height(t->left) - height(t->right) == 2)//check the balance
    {
        if (height(t->left->left) - height(t->left->right) == 1)
        {
            t = singleRotateWithLeft(t);
        }
        else
        {
            t = doubleRotateWithLeft(t);
        }
    }
    else if (height(t->right) - height(t->left) == 2)//check the balance
    {
        if (height(t->right->right) - height(t->right->left) == 1)
        {
            t = singleRotateWithRight(t);
        }
        else
        {
            t = doubleRotateWithRight(t);
        }
    }
    return t;
}
/*------------------------------------------------------------*/
//case 4
AVL* findMin(AVL* t)
{
    if (t == NULL)
    {
        return NULL;
    }
    while (t->left != NULL)
    {
        t = t->left;//the most left
    }
    return t;
}
/*------------------------------------------------------------*/
//case 5
void printInOrder(AVL* t)//left root right
{
    if (t == NULL)
    {
        return;
    }
    printInOrder(t->left);
    printf("word : %s -> frequency : %d\n", t->data, t->frequency);
    printInOrder(t->right);
}
/*------------------------------------------------------------*/
AVL* searchAVL(AVL* t, char* word)
{
    char lowerWrd[50];
    strcpy(lowerWrd,word);
    for(int i = 0 ; lowerWrd[i]; i++)
    {
        lowerWrd[i]=tolower(lowerWrd[i]);
    }
    if (t == NULL)
    {
        return NULL;// If the tree is empty the word does not exist
    }
    if (strcmp(lowerWrd, t->data) < 0)
    {
        return searchAVL(t->left, lowerWrd);
    }
    else if (strcmp(lowerWrd, t->data) > 0)
    {
        return searchAVL(t->right, lowerWrd);
    }
    else
    {
        return t;//we find the word
    }
}
/*------------------------------------------------------------*/
//case 6
int NumberOfElementsOnTheAVLTree(AVL*t)
{
    if (t == NULL)
    {
        return 0;
    }
    return t->frequency + NumberOfElementsOnTheAVLTree(t->left) + NumberOfElementsOnTheAVLTree(t->right);
}
/*------------------------------------------------------------*/
//case 6
int nextPrime(int num)
{
    if (num <= 1)
    {
        return 2;
    }
    if (num % 2 == 0)//find the next odd number
    {
        num++;
    }
    else
    {
        num += 2;
    }
    while (1)
    {
        int isPrime = 1;
        for (int i = 3; i * i <= num; i += 2)
        {
            if (num % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
        {
            return num;
        }
        num += 2;
    }
    return num;
}
/*------------------------------------------------------------*/
int prePrime(int num)
{
    if (num <= 2)
    {
        return -1; // No previous prime number exists
    }

    if (num % 2 == 0)
    {
        //find the last odd number
        num--;
    }
    else
    {
        num -= 2;
    }
    while (num > 1)
    {
        int isPrime = 1;
        for (int i = 3; i * i <= num; i += 2)
        {
            if (num % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
        {
            return num;
        }
        num -= 2;
    }
    return -1; // No previous prime number exists
}
/*------------------------------------------------------------*/
//case 6
HashNode*createHashTable(int size)
{
    HashNode* hashTable = (HashNode*)malloc(size * sizeof(HashNode));//array of hash nodes
    if (hashTable == NULL)
    {
        printf("Out of space.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        hashTable[i].data = NULL;
        hashTable[i].frequency = 0;
    }
    return hashTable;
}
/*------------------------------------------------------------*/
//case 6
void buildHashTable(AVL*copyToHashTabl,HashNode*hashTable, int size)//build hash table from AVL tree
{
    if (copyToHashTabl == NULL)
        return;
    insertToTheHashTable(hashTable, size, copyToHashTabl->data, copyToHashTabl->frequency);
    buildHashTable(copyToHashTabl->left, hashTable, size);
    buildHashTable(copyToHashTabl->right, hashTable, size);
}
/*------------------------------------------------------------*/
//case 6 & 7
void insertToTheHashTable(HashNode hashTable[], int size, char* word, int frequency)
{
    char lowerWrd[50];
    strcpy(lowerWrd, word);
    for (int i = 0; lowerWrd[i]; i++)
    {
        lowerWrd[i] = tolower(lowerWrd[i]);
    }
    double loadfactor = loadFactor(hashTable, size);
    if (loadfactor > 0.7)
    {
        printf("The load factor is %lf and greater than 0.7 , prefer to do rehashing\n",loadfactor);
        return;
    }
    unsigned int h1 = hash1(lowerWrd, size);
    unsigned int h2 = hash2(lowerWrd, size);
    int index = h1;
    int i = 1;
    while (hashTable[index].data != NULL && strcmp(hashTable[index].data, lowerWrd) != 0)// Check if the word already exists in the hash table
    {
        index = (h1 + i*h2) % size;
        i++;
    }
    if (hashTable[index].data == NULL)// If the word doesn't exist, create a new node and insert it
    {
        int length = strlen(lowerWrd);
        hashTable[index].data = (char*)malloc((length + 1) * sizeof(char)); // +1 for null terminator
        if (hashTable[index].data == NULL)
        {
            printf("Out of space.\n");
            return;
        }
        strcpy(hashTable[index].data, lowerWrd);
        hashTable[index].frequency = frequency;
    }
    else
    {
        hashTable[index].frequency++;// If the word already exists, update the frequency
    }
}
/*------------------------------------------------------------*/
//case 6 & 7
//double hashing
//(hash1+*hash2)%size
//hash1=hash%size
//hash2=prevprime-(hash%prevprime)
unsigned int hash1(char* data, int size)
{
    unsigned int hash = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        hash = (hash << 5) + hash + tolower(data[i]);
    }
    return hash % size;
}
unsigned int hash2(char* data, int size)
{
    unsigned int prevPrime = prePrime(size);
    if (prevPrime == -1)
    {
        unsigned int hash = 1;// No previous prime number found
        for (int i = 0; data[i] != '\0'; i++)
        {
            hash = (hash * 33) + tolower(data[i]);
        }
        return hash % size;
    }
    unsigned int hash = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        hash = (hash * 33) + tolower(data[i]);
    }
    return prevPrime - (hash % prevPrime);
}
/*------------------------------------------------------------*/
void printHashTable(HashNode hashTable[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (hashTable[i].data != NULL)
        {
            printf("index %d: %s->%d\n", i, hashTable[i].data, hashTable[i].frequency);
        }
    }
}
/*------------------------------------------------------------*/
//case 8
void deleteFromHashTable(HashNode hashTable[], int size, char*word)
{
    char lowerWrd[50];
    strcpy(lowerWrd, word);
    for (int i = 0; lowerWrd[i]; i++)
    {
        lowerWrd[i] = tolower(lowerWrd[i]);
    }
    unsigned int h1 = hash1(lowerWrd, size);
    unsigned int h2 = hash2(lowerWrd, size);
    int index = h1;
    int i = 1;
    while (hashTable[index].data != NULL && strcmp(hashTable[index].data, lowerWrd) != 0)// Check if the word already exists in the hash table
    {
        index = (h1 + i * h2) % size;
        i++;
    }
    if (hashTable[index].data == NULL)
    {
        printf("Word '%s' not found in the hash table.\n", word);
        return;
    }
    if (hashTable[index].frequency > 1)
    {
        hashTable[index].frequency--;
    }
    else
    {
        free(hashTable[index].data);
        hashTable[index].data = NULL;
        hashTable[index].frequency = 0;
    }
    printf("The word is deleted.\n");
}
/*------------------------------------------------------------*/
//case 9
void searchHashTable(HashNode hashTable[], int size, char*word)
{
    char lowerWrd[50];
    strcpy(lowerWrd, word);
    for (int i = 0; lowerWrd[i]; i++)
    {
        lowerWrd[i] = tolower(lowerWrd[i]);
    }
    unsigned int h1 = hash1(lowerWrd, size);
    unsigned int h2 = hash2(lowerWrd, size);
    int currentIndex = h1;
    int i = 1;
    while (hashTable[currentIndex].data != NULL && strcmp(hashTable[currentIndex].data, lowerWrd) != 0)
    {
        currentIndex = (h1 + i * h2) % size;
        i++;
    }
    if (hashTable[currentIndex].data == NULL)
    {
        printf("the word not found in the hash table.\n");
        return;
    }

    printf("%s found at index %d in the hash table with frequency %d.\n", word, currentIndex,hashTable[currentIndex].frequency);
}
/*------------------------------------------------------------*/
//case 10
void printTheStatistics(HashNode hashTable[],int size, int num)
{
    int totalNumberOfUniqeWord=0;
    printf("The unique words :\n");
    for (int i = 0 ; i < size ; i ++)
    {
        if(hashTable[i].frequency==1)
        {
            totalNumberOfUniqeWord++;
            printf("%s -> %d \n",hashTable[i].data,hashTable[i].frequency);
        }
    }
    printf("The number of unique words is :%d\n",totalNumberOfUniqeWord);
    int mostFrequent=hashTable[0].frequency;
    for (int i = 1 ; i < size ; i ++)
    {
        if(mostFrequent<hashTable[i].frequency)
        {
            mostFrequent=hashTable[i].frequency;
        }
    }
    printf("The words with most frequent %d are :\n",mostFrequent);
    for(int i = 0 ; i < size ; i++)
    {
        if(hashTable[i].frequency==mostFrequent)
        {
            printf("%s\n",hashTable[i].data);
        }
    }
    printf("The words repeated more than the specific threshold in the hash table :\n");
    for(int i = 0 ; i < size ; i ++)
    {
        if(hashTable[i].frequency>num)
        {
            printf("%s \n",hashTable[i].data);
        }
    }
}
/*------------------------------------------------------------*/
//case 11
int NumberOfElementsOnTheHashTable(HashNode hashTable[],int size)
{
    int num =0;
    for(int i = 0 ; i < size ; i++)
    {
        if(hashTable[i].data!=NULL)
            num++;
    }
    return num;
}
/*------------------------------------------------------------*/
//case 11
double loadFactor(HashNode hashTable[],int size)
{
    double numberOfElements=NumberOfElementsOnTheHashTable(hashTable,size);
    double lmda=numberOfElements/size;
    return lmda;
}
/*------------------------------------------------------------*/
//case 11
HashNode* buildRehashingHashTable(HashNode hashTable[],int size)//build hash table from AVL tree
{
    double l =loadFactor(hashTable,size);
    HashNode*rehashingTable=NULL;
    if(l>0.7)
    {
        int sizeOfRehashing=nextPrime(size*2);
        rehashingTable=createHashTable(sizeOfRehashing);
        for(int i = 0 ; i < size ; i ++)
        {
            if(hashTable[i].data!=NULL)
                insertToTheHashTable(rehashingTable,sizeOfRehashing,hashTable[i].data,hashTable[i].frequency);
        }
    }
    else
    {
        printf("Don't need to Rehashing \n");
        return NULL;
    }
    return rehashingTable;
}
