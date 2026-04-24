//Name:Yasmin Mohamed Al shawawrh
//ID:1220848
//Section number:1
//Project #2
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*------------------------------------------------------------*/
//stack
typedef struct Stack
{
    struct Stack*StackNext;
    char*addedStr;
    int index;
    char* status;//we can change it to string insert or remove
} Stack;
/*------------------------------------------------------------*/
// queue
typedef struct Queue
{
    struct Queue*QueueNext;
    char*str;
} Queue;
struct Queue*front=NULL;
struct Queue*rear=NULL;
/*------------------------------------------------------------*/
//functions
void displayMenu();
/*case 1*/char* loadTheInputFile();
/*case 2*/void printTheLoadedText(char*array);
/*case 3*/Stack*insert(char*string,int index,char*array);
void enqueue(char*word,Queue*q);
void dequeue();
Stack*push(char*word,Stack*s);
void insertAtIndex(char*array, int index,char*word);
/*case 4*/Stack* removeFromTheText(char*strin,char* array, Stack* undo) ;
void shiftLeft(char*array, int index, int length);
void undoOperation(Stack*undo,Stack*redo,char*array);
void redoOperation(Stack*undo,Stack*redo,char*array);
void storeToTheOutputFile(char*array);
int IsEmpty(Stack*s);
void MakeEmpty(Stack*s);
void Pop(Stack*s);
void DisposeStack(Stack*s);
/*------------------------------------------------------------*/
int main()
{
    char*array;//original array
    Stack*undo=NULL;
    Stack*redo=NULL;
    displayMenu();
    int op;
    scanf("%d",&op);
    int counter = 0;
    while(op!=9)
    {
        switch(op)
        {
        case 1:
            if(counter<1)
            {
                array=loadTheInputFile();
                counter++;
                break;
            }
            else
                printf("You already loaded the file!!\n");
            break;
        case 2:
            if (array==NULL)
            {
                printf("There is no file loaded to print\n");
                break;
            }
            printf("The loaded information:\n");
            printTheLoadedText(array);
            printf("\n");
            break;
        case 3:
            if (array==NULL)
            {
                printf("There is no file loaded to add string for it\n");
                break;
            }
            printf("Please enter the string you want to add\n");
            char string[1000];
            int c;
            while ((c = getchar()) != '\n');
            fgets(string, sizeof(string), stdin);
            int index;
            printf("and the index where you want to add (-1 to insert at the end):\n");
            scanf("%d",&index);
            undo=insert(string,index,array);
            break;
        case 4:
            if (array==NULL)
            {
                printf("There is no file loaded remove add string for it\n");
                break;
            }
            printf("Please enter the word you want to remove (just one word):\n");
            char* strin = (char*)malloc(100 * sizeof(char));
            if (strin == NULL)
            {
                printf("Memory allocation failed\n");
                return undo;
            }
            scanf("%s", strin);
            undo=removeFromTheText(strin,array,undo);
            break;
        case 5:
            if(undo==NULL)
            {
                printf("Undo stack is empty\n");
                break;
            }
            if(strcmp(undo->status,"Insert")==0)
            {
                printf("Final operation is insert\n");
                undo=removeFromTheText(undo->addedStr,array,undo);
                Pop(&undo);
                //redo=push(undo->addedStr,&redo);
                Pop(&undo);
                break;
            }
            if(strcmp(undo->status,"remove")==0)
            {
                printf("Final operation is remove\n");
                undo=insert(undo->addedStr,undo->index,array);
                redo=push(undo->addedStr,&redo);
                Pop(&undo);
                break;
            }
            Pop(&undo);
            break;
        case 6:
            if(redo==NULL)
            {
                printf("Redo stack is empty\n");
                break;
            }
            if(strcmp(redo->status,"Insert")==0)
            {
                //insert undo->addstr from the array
            }
            if(strcmp(redo->status,"remove")==0)
            {
                //remove undo->addstr to the array
            }
//            push(redo->addedStr,&undo);
//            Pop(&redo);
            break;
        case 7:
            printf("Undo stack:\n\n");
            if(undo==NULL)
            {
                printf("Empty stack\n");
            }
            else
            {
                printf("Token\t\toperation\tindex\n");
                Stack* temp = undo;
                while(temp->StackNext!=NULL)
                {
                    printf("%s\t\t%s\t\t%d\n",temp->addedStr,temp->status,temp->index);
                    Pop(&temp);
                }
            }
            printf("Redo stack:\n\n");
            if(redo==NULL)
            {
                printf("Empty stack\n");
            }
            else
            {
                printf("Token\t\toperation\t\tindex\n");
                Stack* temp2 = redo;
                while(temp2->StackNext!=NULL)
                {
                    printf("%s\t\t%s\t\t%d\n",temp2->addedStr,temp2->status,temp2->index);
                    Pop(&temp2);
                }
            }
            break;
        case 8:
            storeToTheOutputFile(array);
            while(undo!=NULL)
                Pop(&undo);
            while(redo!=NULL)
                Pop(&redo);
            break;
        default:
            printf("No such operation! please try again.\n");
        }
        printf("--------------------------------------------------------------\n");
        displayMenu();
        scanf("%d",&op);
    }
    if(op==9)
        printf("Thank you for using my program, goodbye.\n");
    return 0;
}
/*------------------------------------------------------------*/
void displayMenu()
{
    printf("Select which operation you want to do :\n\n");
    printf("1. Load the input file which contains the initial text.\n");
    printf("2. Print the loaded text.\n");
    printf("3. Insert strings to the text. \n");
    printf("4. Remove strings from the text.\n");
    printf("5. Perform Undo operation.\n");
    printf("6. Perform Redo operation.\n");
    printf("7. Print the Undo Stack and the Redo stack.\n");
    printf("8. Save the updated text to the output file.\n");
    printf("9. Exit.\n\n");
    printf("number of operation :\n");
}
/*------------------------------------------------------------*/
//case 1
char* loadTheInputFile()
{
    char*array=NULL;
    FILE *input = fopen("inputFile.txt", "r");
    if (input == NULL)
    {
        printf("Unable to open the file!\n");
        return NULL;
    }
    char text[1000];
    if (fgets(text, sizeof(text), input) == NULL)
    {
        printf("The file is empty!\n");
        fclose(input);
        return NULL;
    }

    int size = 0;
    while (text[size] != '\0')//for the empty index
    {
        size++;
    }

    array = (char*)malloc((size + 1) * sizeof(char));
    if (array == NULL)
    {
        printf("Allocate memory failed!\n");
        fclose(input);
        return NULL;
    }

    for (int k = 0; k < size; k++)
    {
        array[k] = text[k];
    }
    array[size] = '\0';
    printf("The file is successfully loaded!\n");
    fclose(input);
    return array;
}
/*------------------------------------------------------------*/
//case 2
void printTheLoadedText(char*array)
{
    int i = 0;
    while(array[i]!='\0')
    {
        printf("%c",array[i]);
        i++;
    }
}
/*------------------------------------------------------------*/
//case 3
Stack*insert(char*string,int index,char*array)
{
    Queue*q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    char*token=strtok(string," .");//add string to the queue
    while(token!=NULL)
    {
        enqueue(token,q);
        token=strtok(NULL," .");
    }
    Stack*undo=malloc(sizeof(Stack));
    if(undo==NULL)
        printf("Out of space");
    undo->addedStr=NULL;
    undo->index=0;
    undo->StackNext=NULL;
    undo->status=NULL;
    while(front!=NULL)
    {
        undo=push(front->str,undo);
        undo->index=index;
        undo->status="Insert";
        if (index==-1)
        {
            strcat(array," ");
            strcat(array,front->str);
            printf("The updated string is: %s\n", array);
        }
        else
        {
            index--;
            insertAtIndex(array,index,front->str);
            index+=strlen(front->str);
        }
        dequeue();
    }
    return undo;
}
void enqueue(char*word,Queue*q)//add to end
{
    Queue*temp=(Queue*)malloc(sizeof(Queue));
    temp->str=word;
    temp->QueueNext=NULL;
    if(front==NULL&&rear==NULL)
    {
        front=rear=temp;
        return ;
    }
    rear->QueueNext=temp;
    rear=temp;
    q=temp;
}
void dequeue()//delete from fisrt
{
    Queue* q = front;
    if(front==NULL)
    {
        printf("queue is empty\n");
        return;
    }
    if(front==rear)
        front=rear=NULL;
    else
    {
        front=front->QueueNext;
    }
    free(q);
}
Stack*push(char*word,Stack*s)
{
    int len = strlen(word);
    if (len > 0 && word[len - 1] == '\n')
    {
        word[len - 1] = '\0';
    }
    Stack*temp=(Stack*)malloc(sizeof(Stack));
    if(temp==NULL)
    {
        printf("Allocate memory failed\n");
        return NULL;
    }
    temp->addedStr = (char*)malloc(strlen(word) + 1);
    if (temp->addedStr == NULL)
    {
        printf("Allocate memory failed\n");
        return NULL;
    }
    strcpy(temp->addedStr, word);
    temp->StackNext=s;
    s=temp;
    return s;
}
void insertAtIndex(char* array, int index, char* word)
{
    int length = strlen(array);
    int wordLength = strlen(word);
    if (index < 0 || index > length)
    {
        printf("Invalid index\n");
        return;
    }
    if(index == length)
    {
        strcat(array, " ");
        strcat(array,front->str);
        return;
    }
    int newLength = length + wordLength + 2;//for the spaces
    char* newArray = (char*)malloc(newLength * sizeof(char));// Allocate a new array with the updated size
    if (newArray == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(newArray, array, index);// Copy the elements before the index
    newArray[index] = ' ';
    strcpy(newArray + index + 1, word);// Add the spaces and the new word
    newArray[index + 1 + wordLength] = ' ';
    strcpy(newArray + index + 1 + wordLength + 1, array + index);// Copy the elements after the index
    newArray[newLength - 1] = '\0';
    free(array);
    array = newArray;
    printf("The updated string is: %s\n", array);
}
/*------------------------------------------------------------*/
//case 4
Stack* removeFromTheText(char*strin,char* array, Stack* undo)
{
    int found = 0;
    int index = 0;
    char*arr=(char *)malloc((lstrlen(array) + 1) * sizeof(char));
    strncpy(arr,array,strlen(array));
    arr[strlen(array)] = '\0';
    char* token = strtok(arr, " .");
    while (token != NULL)
    {
        if (strcmp(strin, token) == 0)  //first occurrence
        {
            found = 1;
            Stack* new_undo = (Stack*)malloc(sizeof(Stack));
            if (new_undo == NULL)
            {
                printf("Memory allocation failed\n");
                free(strin);
                return undo;
            }
            new_undo->addedStr = strin;
            new_undo->index = index;
            new_undo->StackNext = undo;
            new_undo->status = "remove";
            undo = new_undo;
            break;
        }
        index += strlen(token) + 1;
        token = strtok(NULL, " .");
    }

    if (found)
    {
        shiftLeft(array, index, strlen(strin) + 1);
        printf("The updated string is: %s\n", array);
    }
    else
    {
        printf("The word is not found\n");
    }

    return undo;
}
void shiftLeft(char*array, int index, int length)
{
    while (array[index] != '\0')
    {
        array[index] = array[index + length];
        index++;
    }
}
/*------------------------------------------------------------*/
//case 8
void storeToTheOutputFile(char*array)
{
    if(array==NULL)
    {
        printf("There is no text to store in file!\n");
        return;
    }
    FILE*output=fopen("outputFile.txt","w");
    if (output == NULL)
    {
        printf("Unable to open the file!\n");
        return;
    }
    int i = 0;
    while(array[i]!='\0')
    {
        fprintf(output,"%c",array[i]);
        i++;
    }
    printf("THE OUTPUT IS SAVED IN FILE (^_^)...\n");
    fclose(output);
}
/*------------------------------------------------------------*/
int IsEmpty(Stack*s)
{
    return s->StackNext==NULL;
}
void MakeEmpty(Stack*s)
{
    if (s==NULL)
        printf("OUT OF SPACE!");
    else
        while(!IsEmpty(s))
            Pop(s);
}
void Pop(Stack*s)
{
    Stack* first;
    if(IsEmpty(s))
        printf("Empty Stack");
    else
    {
        first=s->StackNext;
        s->StackNext=s->StackNext->StackNext;
        free(first);
    }
}
void DisposeStack(Stack*s)
{
    MakeEmpty(s);
    free(s);
}
