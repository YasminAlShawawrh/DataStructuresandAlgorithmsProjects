//Name:Yasmin Mohamed Al shawawrh
//ID:1220848
//Section number:1
//Project #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*-------------------------------------------------------------------------------------------*/
/*struct to create lists of towns*/
typedef struct town
{
    struct town* previous;//pointer
    char town_name[20];//char of array contain the town name
    int town_population;//the population of the town
    struct town* next;//pointer
} town;
/*-------------------------------------------------------------------------------------------*/
/*struct to create lists of districts*/
typedef struct district
{
    struct district* previous;//pointer
    char district_name[20];//char of array contain the district name
    int district_population;//the total population in the district equal the sum of population in every town in this district
    struct town* district_town;//pointer to town
    struct district* next;//pointer
} district;

/*-------------------------------------------------------------------------------------------*/
//functions I used:

void displayMenu();
/*case:1*/void loadTheInputFile(district*head);
int isEmpty(district* head);
district* searchDistrict(district *head,char *name);
/*case:2*/void printLoadedIformationPeforeSorting(district*head);
/*case:3*/int getMaxLength(char* arr[], int n);
void countingSort(char* arr[], int n, int d);
void radixSort(char* arr[], int n);
district* districtSortedList(district* head);
/*case:4*/void*sortTownsUsingBubbleSort(district*head);
/*case:6*/district* addNewDistrict(district*sort,char*nameNewDistrict);
/*case:7*/district* addNewTown(district*head);
town* searchTown(town*headTown,char*name);
/*case:8*/district* deleteTown(district*head);
/*case:9*/district* deleteCompleteDistrict(district*head, char*name);
void deleteAllTowns(district*isExistDistrict);
/*case:10*/void calculateThePopulation(district*head);
/*case:11*/void printDistrictsWithoutTowns(district*head);
/*case:13*/void saveToOutputFile(district* head);
/*-------------------------------------------------------------------------------------------*/
int main()
{
    district* head=(district*)malloc(sizeof(district));//allocate memory
    if(head==NULL)//fail to allocate memory
    {
        printf("Out of space");
    }
    head->next=NULL;
    head->previous=NULL;
    head->district_town=NULL;
    district*sorted=NULL;
    displayMenu();
    int op;
    scanf("%d",&op);
    int counter=0;
    while(op!=14)
    {
        switch(op)
        {
        case 1:
            if(counter<1)
            {
                loadTheInputFile(head);
                printf("The file is successfully loaded!\n");
                counter++;
                break;
            }
            else
                printf("You already loaded the file!!\n");
            break;
        case 2:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty we can not print the loaded information...\n");
                break;
            }
            printf("The loaded information before sorting:\n");
            printLoadedIformationPeforeSorting(head);
            break;
        case 3:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            sorted=districtSortedList(head);
            printf("Districts sorted successfully!\n");
            break;
        case 4:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            sortTownsUsingBubbleSort(head);
            printf("Towns sorted successfully!\n");
            break;
        case 5:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            printf("The sorted information:\n");
            sorted=districtSortedList(sorted);
            printLoadedIformationPeforeSorting(sorted);
            break;
        case 6:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            printf("please enter the name of district you want to add:");
            //printf("(note:if the name of district is more than word put - instead of the space)\n");
            char name[20];
            scanf("%s",name);//if the name is from to word we should use another thing // when i use gets there is a jump
            sorted=addNewDistrict(sorted,name);
            break;
        case 7:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            sorted=addNewTown(sorted);
            break;
        case 8:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            sorted=deleteTown(sorted);
            break;
        case 9:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            printf("please enter the name of district you want to delete:(from the sorted list)\n");
            char name_dist[20];
            scanf("%s",name_dist);
            sorted=deleteCompleteDistrict(sorted,name_dist);
            break;
        case 10:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            calculateThePopulation(sorted);//for sorted list
            break;
        case 11:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            printDistrictsWithoutTowns(sorted);//for sorted list
            break;
        case 12:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            if(sorted==NULL||sorted->next==NULL)
            {
                printf("The Sorted List is Empty...\n");
                break;
            }
            printf("Enter the district name that contain the town you want to change the population for it:\n");
            char*name_district[20];
            scanf("%s",name_district);
            district*change=searchDistrict(sorted,name_district);
            if(change!=NULL)
            {
                printf("Enter the town name:\n");
                char*name_town[20];
                scanf("%s",name_town);
                town*changPop=change->district_town;
                changPop=searchTown(changPop,name_town);
                if(changPop!=NULL)
                {
                    printf("Enter the population of the town:\n");
                    int po;
                    scanf("%d",&po);
                    change->district_population-=changPop->town_population;
                    changPop->town_population=po;
                    change->district_population+=po;
                    printf("The change is done.\n");
                }
                else
                    printf("The town does not exist.\n");
            }
            else
                printf("The District does not found.\n");
            break;
        case 13:
            if(head==NULL||head->next==NULL)
            {
                printf("The List is Empty...\n");
                break;
            }
            saveToOutputFile(sorted);
            break;
        default:
            printf("No such operation! please try again.\n");
        }
        printf("--------------------------------------------------------------\n");
        displayMenu();
        scanf("%d",&op);
    }
    if(op==14)
        printf("Thank you for using my program, goodbye.\n");
    return 0;
}/*-------------------------------------------------------------------------------------------*/
void displayMenu()
{
    printf("Select which option you want to do :\n\n");
    printf("1. Load the input file (Palestinian districts and their town with population).\n");
    printf("2. Print the loaded information before sorting (as in the input file format).\n");
    printf("3. Sort the districts alphabetically using Radix sort.\n");
    printf("4. Sort the towns for each district based on population in ascending order.\n");
    printf("5. Print the sorted information.\n");
    printf("6. Add a new district to the list of sorted districts (and sort the list).\n");
    printf("7. Add a new town to a certain district.\n");
    printf("8. Delete a town from a specific district.\n");
    printf("9. Delete a complete district.\n");
    printf("10. Calculate the population of Palestine, the max and min town population.\n");
    printf("11. Print the districts and their total population (without towns details).\n");
    printf("12. Change the population of a town.\n");
    printf("13. Save to output file.\n");
    printf("14. Exit.\n\n");
    printf("number of option :\n");
}
/*-------------------------------------------------------------------------------------------*/
/*case:1*/
void loadTheInputFile(district* head)
{
    FILE* input = fopen("districts.txt", "r");//open the file
    if (input == NULL)
    {
        printf("Unable to open file!\n");//there is no output of the file
        return;
    }
    char line[50];//Assume the maximum length of the input string is 50 characters (from the project)
    while (fgets(line, sizeof(line), input) != NULL)//fgets(where you want to store the string , maximum number of character , from where)
    {
        char* districtName = strtok(line, "|");//split the string according to |
        char* townName = strtok(NULL, "|");
        char* populationStr = strtok(NULL, "|");
        int population = atoi(populationStr);//converts the string argument populationStr to an integer (type int). since strtok return string


        district* currentDistrict = searchDistrict(head, districtName);//define a new district if the district does not exist
        if (currentDistrict == NULL)
        {
            currentDistrict = (district*)malloc(sizeof(district));//allocate memory to the district if it does not exist
            if (currentDistrict == NULL)//the memory is full
            {
                printf("Out of space!");
                return;
            }
            strcpy(currentDistrict->district_name, districtName);//strcpy function that copies the string
            currentDistrict->next = NULL;//creation to the doubly linked list
            currentDistrict->district_town = NULL;
            currentDistrict->previous = NULL;
            currentDistrict->district_population = 0;

            district* lastDistrict = head;//to connect the nodes with each other
            while (lastDistrict->next != NULL)
            {
                lastDistrict = lastDistrict->next;//after reach the last node , add the new node
            }
            lastDistrict->next = currentDistrict;
            currentDistrict->previous = lastDistrict;
        }
        town* newTown = (town*)malloc(sizeof(town));//allocate memory to the town
        if ( newTown == NULL)//the memory is full
        {
            printf("Out of space!");
            return;
        }
        strcpy(newTown->town_name, townName);//strcpy function that copies the string
        newTown->town_population = population;//creation to the doubly linked list
        newTown->next = NULL;
        newTown->previous=NULL;

        currentDistrict->district_population += population;

        town* currentTown = currentDistrict->district_town;//pointer from the district
        if (currentTown == NULL)//that mean the district does not have any town
        {
            currentDistrict->district_town = newTown;//that mean the newTown is the first town in the district
        }
        else
        {
            while (currentTown->next != NULL)//to reach the last town
            {
                currentTown = currentTown->next;
            }
            currentTown->next = newTown;//add to the last town
        }
    }
    fclose(input);
}
int isEmpty(district* head)
{
    return head==NULL;
}
district* searchDistrict(district* head,char *name)
{
    char*arr=strlwr(name);
    if(isEmpty(head))
    {
        printf("The list is empty!\n");
        return NULL;
    }
    district* l=head;
    while(l->next!=NULL)//when we reach the last node we does not enter the loop
    {
        int temp=strcmp(arr,strlwr(l->district_name));//compares two strings character by character. If the strings are equal, the function returns 0.
        if (temp==0)//the strings are equal
            return l;
        l=l->next;
    }
    int temp=strcmp(name,l->district_name);//for the last element
    if(l->next==NULL&&temp==0)
        return l;

    return NULL;
}
/*-------------------------------------------------------------------------------------------*/
/*case:2*/
void printLoadedIformationPeforeSorting(district*head)
{
    district* ptr = head->next;
    town* ptr2;
    while (ptr!= NULL)
    {
        printf("%s District, Population=%d\n", ptr->district_name, ptr->district_population);
        ptr2 = ptr->district_town;
        while (ptr2 != NULL)
        {
            printf("%s, %d\n", ptr2->town_name, ptr2->town_population);
            ptr2 = ptr2->next;
        }
        ptr = ptr->next;
    }
}
/*-------------------------------------------------------------------------------------------*/
/*case:3*/
int getMaxLength(char* arr[], int n) // Function to get the maximum length of strings in the array
{
    int maxLen = 0;
    for (int i = 0; i < n; i++)//n the size of the array
    {
        if (strlen(arr[i]) > maxLen)
        {
            maxLen = strlen(arr[i]);
        }
    }
    return maxLen;
}
void countingSort(char* arr[], int n, int d)//(the input of array to be sorted , the size of array , the current digit position sorted)
{
    char* output[n];//that store the sorted string and n is the size of input array
    int count[256] = {0}; // array of size 256 for all ASCII characters and initializes all element to zero
    for (int i = 0; i < n; i++)//for all elements in the array
    {
        if (arr[i][d] != '\0')//at the first loop we do this for the last digit
        {
            //If the character at the current digit position is not the null character '\0'
            int index = arr[i][d] - '0';// subtracting the ASCII value of '0' (which is 48) from the ASCII value of the current digit character
            count[index]++;//increments the count at that index in the count array
        }
        else//If the character at the current digit position is the null character '\0'
        {
            count[0]++;//it increments the count at index 0 in the count array
        }
    }
    for (int i = 1; i < 256; i++)
    {
        count[i] += count[i - 1];//count[i] now contains the total number of digits less than or equal to i
    }
    for (int i = n - 1; i >= 0; i--)// Build the output array
    {
        if (arr[i][d] != '\0')//If the character at the current digit position is not the null character '\0'
        {
            int index = arr[i][d] - '0';
            output[count[index] - 1] = arr[i];
            count[index]--;
        }
        else
        {
            int index = 0;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }
    }
    for (int i = 0; i < n; i++)
    {
        //since arr is pointer then the element change by referance
        arr[i] = output[i];// Placing output array elements back to arr[]
    }
}
void radixSort(char* arr[], int n)
{
    int maxLen = getMaxLength(arr, n);//if the length is 3 then the last digit with index 2 so we start from 3-1
    for (int d = maxLen - 1; d >= 0; d--)
    {
        countingSort(arr, n, d);
    }
}
district* districtSortedList(district* head)
{
    district* sort=(district*)malloc(sizeof(district));//allocate memory
    if(sort==NULL)//fail to allocate memory
    {
        printf("Out of space");
    }
    sort->next=NULL;
    sort->previous=NULL;
    sort->district_town=NULL;
    district* ptr = head->next; // Start from the first node
    int numberOfDistricts = 0;
    while (ptr != NULL)
    {
        numberOfDistricts++;// Count the number of districts
        ptr = ptr->next;
    }
    char* arr[numberOfDistricts];// Allocate memory for the arr
    for (int i = 0; i < numberOfDistricts; i++)
    {
        arr[i] = (char*)malloc(20 * sizeof(char)); // Assuming max length of 20 characters
    }
    ptr = head->next;
    for (int i = 0; i < numberOfDistricts; i++)
    {
        strcpy(arr[i], ptr->district_name);
        ptr = ptr->next;
    }
    radixSort(arr, numberOfDistricts);// Sort the arr array using radixSort
    // Create the sorted linked list
    for (int i = 0; i < numberOfDistricts; i++)
    {
        district* temp = searchDistrict(head, arr[i]);
        district* founded = (district*)malloc(sizeof(district));
        strcpy(founded->district_name, temp->district_name);
        founded->district_population = temp->district_population;
        founded->district_town = temp->district_town;
        founded->next = NULL;
        founded->previous = NULL;
        // Insert the new node into the sorted linked list
        if (sort == NULL)
        {
            sort = founded;
        }
        else
        {
            district* lastDistrict = sort;
            while (lastDistrict->next != NULL)
            {
                lastDistrict = lastDistrict->next;
            }
            lastDistrict->next = founded;
            founded->previous = lastDistrict;
        }
    }
    return sort;
}
/*-------------------------------------------------------------------------------------------*/
/*case:4*/
void*sortTownsUsingBubbleSort(district*head)//ascending order
{
    district*ptr=head->next;
    while(ptr!=NULL)
    {
        if(ptr->district_town==NULL)//the case when the district does not have towns
        {
            ptr=ptr->next;
            continue;
        }
        town*tempTown=ptr->district_town;
        for(tempTown; tempTown!=NULL; tempTown=tempTown->next)
        {
            town*currentTown;
            for(currentTown=tempTown->next; currentTown!=NULL; currentTown=currentTown->next)
            {
                if(tempTown->town_population > currentTown->town_population)
                {
                    int temp=currentTown->town_population;
                    currentTown->town_population=tempTown->town_population;
                    tempTown->town_population=temp;
                    char tempName[20];
                    strcpy(tempName,currentTown->town_name);
                    strcpy(currentTown->town_name,tempTown->town_name);
                    strcpy(tempTown->town_name,tempName);
                }
            }
        }
        ptr=ptr->next;
    }
    return head;
}
/*-------------------------------------------------------------------------------------------*/
/*case:6*/
district* addNewDistrict(district*sort,char*nameNewDistrict)
{
    if(searchDistrict(sort,nameNewDistrict)!=NULL)
    {
        printf("The district is already add...\n");
        return sort;
    }
    district*ptr=sort;
    district* newDistrict=(district*)malloc(sizeof(district));
    newDistrict->previous=NULL;
    newDistrict->next=NULL;
    newDistrict->district_town=NULL;
    while(ptr->next!=NULL)//find the last district
    {
        ptr=ptr->next;
    }
    ptr->next=newDistrict;
    newDistrict->previous=ptr;
    strcpy(newDistrict->district_name,nameNewDistrict);
    newDistrict->district_population=0;
    printf("The district is added...\n");
    return sort;
}
/*-------------------------------------------------------------------------------------------*/
/*case:7*/
district* addNewTown(district*head)
{
    if(head==NULL||head->next==NULL)
    {
        printf("The sorted list is empty\n");
        return head;
    }
    printf("Please enter the name of district you want to add town for it(we will add to the sorted list) :\n");
    //printf("(note:if the name of district is more than word put - instead of the space)\n");
    char name_diss[20];
    scanf("%s",name_diss);
    district*existDistrict=searchDistrict(head,name_diss);
    if(existDistrict!=NULL)
    {
        town*nextTown=existDistrict->district_town;
        printf("please enter the name of town you want to add:\n");
        //printf("(note:if the name of town is more than word put - instead of the space)\n");
        char name_town[20];
        scanf("%s",name_town);
        town*tempTown=searchTown(nextTown,name_town);
        if(tempTown==NULL)
        {
            printf("the town does not exist and we will add it...\n");
            town*temp=(town*)malloc(sizeof(town));
            temp->next=NULL;
            temp->previous=NULL;
            while(nextTown->next!=NULL)
            {
                nextTown=nextTown->next;
            }
            nextTown->next=temp;
            temp->previous=nextTown;
            strcpy(temp->town_name,name_town);
            printf("enter the population of this town:\n");
            int  pop;
            scanf("%d",&pop);
            temp->town_population=pop;
            existDistrict->district_population+=pop;
            printf("The town is added...\n");
            return head;
        }
        else
        {
            printf("The town is already exist.\n");
            return head;
        }
    }
    else
    {
        printf("The district does not exist, add district first\n");
        return head;
    }
}
town* searchTown(town* headTown, char* name)
{
    char *arr=strlwr(name);
    if (headTown == NULL)
    {
        return NULL;
    }

    town* tempTown = headTown;
    while (tempTown != NULL)
    {
        int temp = strcmp(arr, strlwr(tempTown->town_name));
        if (temp == 0)
        {
            return tempTown;
        }
        tempTown = tempTown->next;
    }

    return NULL;
}
/*-------------------------------------------------------------------------------------------*/
/*case:8*/
district* deleteTown(district*head)//the last element
{
    printf("please enter the name of district you want to delete a town from it(in sorted list):\n");
    char name_dis[20];
    scanf("%s",name_dis);
    district*townDeleted=searchDistrict(head,name_dis);//find district
    if(townDeleted!=NULL)
    {
        char name_town[20];
        printf("Please enter the name of town you want to delete:\n");
        scanf("%s",name_town);
        town*currentTown=townDeleted->district_town;
        town *ptr=NULL;
        while (currentTown!=NULL&&strcmp(currentTown->town_name,name_town)!=0)//to find the town to be deleted
        {
            ptr=currentTown;
            currentTown=currentTown->next;
        }
        if (currentTown!=NULL)
        {
            if(ptr==NULL)//the first town
            {
                townDeleted->district_town=currentTown->next;
                townDeleted->district_population-=currentTown->town_population;
            }
            else
            {
                ptr->next=currentTown->next;
                townDeleted->district_population-=currentTown->town_population;
            }
            free(currentTown);
            printf("The town is deleted.\n");
        }
        else//if the town does not exist
        {
            printf("The town does not exist.\n");
            return head;
        }
    }
    else
    {
        printf("The district does not exist.\n");
        return head;
    }
    return head;
}
/*-------------------------------------------------------------------------------------------*/
/*case:9*/
district* deleteCompleteDistrict(district*head, char*name)//we need delete from first and delete from final
{
    district*isExistDistrict=searchDistrict(head,name);
    if(isExistDistrict==NULL)//case when the district does not exist
    {
        printf("The district does not exist.\n");
        return head;
    }
    else if(isExistDistrict->next!=NULL)//case when find the district
    {
        deleteAllTowns(isExistDistrict);
        district*temp1=isExistDistrict->previous;
        district*temp2=isExistDistrict->next;
        free(isExistDistrict);
        temp1->next=temp2;
        temp2->previous=temp1;
        printf("The district is deleted ...\n");
    }
    else if(isExistDistrict->next==NULL) //the last element (delete from last)
    {
        deleteAllTowns(isExistDistrict);
        district*temp=isExistDistrict->previous;
        temp->next=NULL;
        free(isExistDistrict);
        printf("The district is deleted ...\n");
    }
    else //the first element (delete from first)
    {
        deleteAllTowns(isExistDistrict);
        district*temp=isExistDistrict->next;
        temp->previous=NULL;
        free(isExistDistrict);
        printf("The district is deleted ...\n");
    }
    return head;
}
void deleteAllTowns(district*isExistDistrict)
{
    town*t=isExistDistrict->district_town;
    town*ptr=t;
    while(t!=NULL)
    {
        t=t->next;
        free(ptr);
        ptr=t;
    }
}
/*-------------------------------------------------------------------------------------------*/
/*case:10*/
void calculateThePopulation(district*head)
{
    district*calculate=head;
    if(head==NULL||head->next==NULL)
    {
        printf("The Sorted List is Empty...\n");
        return;
    }
    int totalPopulation=0,min=100000000/*very large number*/,max=0;
    while(calculate!=NULL)
    {
        town*tempTown=calculate->district_town;
        while(tempTown!=NULL)
        {
            totalPopulation+=tempTown->town_population;
            if(tempTown->town_population>max)
                max=tempTown->town_population;
            if(tempTown->town_population<min)
                min=tempTown->town_population;
            tempTown=tempTown->next;
        }
        calculate=calculate->next;
    }
    printf("The population in Palestine is :%d\n",totalPopulation);
    printf("The min town population in Palestine is :%d\n",min);
    printf("The max town population in Palestine is :%d\n",max);
}
/*-------------------------------------------------------------------------------------------*/
/*case:11*/
void printDistrictsWithoutTowns(district*head)
{
    if(head==NULL||head->next==NULL)
    {
        printf("The Sorted List is Empty...\n");
        return;
    }
    district* ptr = head->next;
    while (ptr!= NULL)
    {
        printf("%s District, Population=%d\n", ptr->district_name, ptr->district_population);
        ptr = ptr->next;
    }
}
/*-------------------------------------------------------------------------------------------*/
/*case:13*/
void saveToOutputFile(district* head)
{
    if(head==NULL||head->next==NULL)
    {
        printf("The Sorted List is Empty...\n");
        return;
    }
    FILE*output=fopen("sorted_districts.txt","w");
    sortTownsUsingBubbleSort(head);
    district* ptr = head->next;
    town* ptr2;
    while (ptr!= NULL)
    {
        fprintf(output,"%s District, Population=%d\n", ptr->district_name, ptr->district_population);
        ptr2 = ptr->district_town;
        while (ptr2 != NULL)
        {
            fprintf(output,"%s, %d\n", ptr2->town_name, ptr2->town_population);
            ptr2 = ptr2->next;
        }
        ptr = ptr->next;
    }
    printf("THE OUTPUT IS SAVED IN FILE (^_^)...\n");
    fclose(output);
}
/*-------------------------------------------------------------------------------------------*/

