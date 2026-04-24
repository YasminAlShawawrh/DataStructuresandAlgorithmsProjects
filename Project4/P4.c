//Name:Yasmin Mohamed Al shawawrh
//ID:1220848
//Section number:1
//Project #4
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <limits.h>//for infinite(MAX_INT)
#define BUILDING_ARRAY_SIZE 100
#define COURSES_ARRAY_SIZE 100
/*------------------------------------------------------------*/
//contingency list to represent the graph and store it
typedef struct building
{
    char*buildingName;
    int distance;
    struct building*nextBuilding;
} building;
building*arrBuilding[BUILDING_ARRAY_SIZE];
int numOfBuilding=0;
/*------------------------------------------------------------*/
typedef struct MinHeapNode
{
    building* building;
    int distance;
} MinHeapNode;

typedef struct MinHeap
{
    int size;
    int capacity;
    MinHeapNode* array;
} MinHeap;
/*------------------------------------------------------------*/
//contingency list to represent the graph and store it
typedef struct course
{
    char*courseName;
    struct course*nextCourse;
} course;
course*arrCourse[COURSES_ARRAY_SIZE];
int numOfCourses = 0;
/*------------------------------------------------------------*/
//functions

void displayMenu();
//case 1
void readBuildingsFromFile();
building*createBuilding(char*buildingName,int distance);
void printBuildings();
void readCoursesFromFile();
course*createCourse(char*courseName);
void printCourses();
//case 2
void addEdge(building*source,building*second,int weight);
MinHeapNode*createMinHeapNode(building*building,int distance);
MinHeap*createMinHeap(int capacity);
void insertNode(MinHeap*heap, MinHeapNode*newNode);
MinHeapNode extractMin(MinHeap* heap);
int isEmpty(MinHeap* heap);
void decreaseKey(MinHeap* heap, int index, int newDistance);
int findBuildingIndexByName(char*name);
void dijkstra(char* firstBuildingName, char* secondBuildingName);
void followPath(char* firstBuildingName, char* secondBuildingName);
//case 3
//case 4
course* topsort();
int findCourseIndex(char* course);
//case 5
void printTopologicalSortCourses(course* sortedCourses);
/*------------------------------------------------------------*/
int main()
{
    displayMenu();
    int op;
    scanf("%d",&op);
    int counter = 0;
    course* sortedCourses = NULL;
    while(op!=6)
    {
        switch(op)
        {
        case 1:
            if(counter<1)
            {
                readBuildingsFromFile();//load the first file(input_buildings.txt)
                printf("the first file:\n");
                printBuildings();
                printf("\n");
                readCoursesFromFile();//load the second file(input_courses.txt)
                printf("the second file:\n");
                printCourses();
                printf("\n");
                printf("The file is successfully loaded!\n");
                counter++;
                break;
            }
            else
                printf("You already loaded the file!!\n");
            break;
        case 2:
            if(arrBuilding[0]==0)
            {
                printf("Load the file at first!\n");
                break;
            }
            printf("please enter the name of the first building:\n");
            char firstBuildingName[20];
            scanf("%s",firstBuildingName);
            printf("please enter the name of the second building:\n");
            char secondBuildingName[20];
            scanf("%s",secondBuildingName);
            dijkstra(firstBuildingName,secondBuildingName);
            break;
        case 3:
            if(arrBuilding[0]==0)
            {
                printf("Load the file at first!\n");
                break;
            }
            printf("please enter the name of the first building:\n");
            char firstBuilding[20];
            scanf("%s",firstBuilding);
            printf("please enter the name of the second building:\n");
            char secondBuilding[20];
            scanf("%s",secondBuilding);
            followPath(firstBuilding,secondBuilding);
            break;
        case 4:
            if(arrCourse[0]==0)
            {
                printf("Load the file at first!\n");
                break;
            }
            sortedCourses = topsort();
            printf("The courses are sorted\n");
            break;
        case 5:
            if(arrCourse[0]==0)
            {
                printf("Load the file at first!\n");
                break;
            }
            printTopologicalSortCourses(sortedCourses);
            break;
        default:
            printf("No such operation! please try again.\n");
        }
        printf("--------------------------------------------------------------\n");
        displayMenu();
        scanf("%d",&op);
    }
    if(op==6)
        printf("Thank you for using my program, goodbye.\n");
    return 0;
}
/*------------------------------------------------------------*/
void displayMenu()
{
    printf("Select which operation you want to do :\n\n");
    printf("1. Load the two files.\n");
    printf("2. Calculate the shortest distance between two buildings.\n");
    printf("3. Print the shortest route between two buildings and the total distance.\n");
    printf("4. Sort the courses using the topological sort.\n");
    printf("5. Print the sorted courses.\n");
    printf("6. Exit the application.\n");
    printf("number of operation :\n");
}
/*------------------------------------------------------------*/
//case 1
//for the first file
void readBuildingsFromFile()
{
    FILE* input = fopen("input_buildings.txt", "r");
    if (input == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), input))
    {
        char* firstBuildingName = strtok(line, "#");
        char* secondBuildingName = strtok(NULL, "#");
        int distance = atoi(strtok(NULL, "\n"));
        int foundFirst = 0;
        int foundSecond = 0;
        for (int i = 0; i < numOfBuilding; i++)// Search for first building
        {
            if (strcmp(arrBuilding[i]->buildingName, firstBuildingName) == 0)
            {
                foundFirst = 1;
                building* current = arrBuilding[i];
                while (current->nextBuilding != NULL)
                {
                    current = current->nextBuilding;
                }
                building* secondBuildingNode = createBuilding(secondBuildingName, distance);
                if (secondBuildingNode == NULL)
                {
                    printf("Failed to allocate memory.\n");
                    fclose(input);
                    return;
                }
                current->nextBuilding = secondBuildingNode;
                break;
            }
        }
        if (!foundFirst)// If first building not found, create and add it
        {
            if (numOfBuilding >= BUILDING_ARRAY_SIZE)
            {
                printf("Building array is full.\n");
                fclose(input);
                return;
            }
            arrBuilding[numOfBuilding] = createBuilding(firstBuildingName, 0);
            if (arrBuilding[numOfBuilding] == NULL)
            {
                printf("Failed to allocate memory.\n");
                fclose(input);
                return;
            }
            building* secondBuildingNode = createBuilding(secondBuildingName, distance);
            if (secondBuildingNode == NULL)
            {
                printf("Failed to allocate memory.\n");
                fclose(input);
                return;
            }
            arrBuilding[numOfBuilding]->nextBuilding = secondBuildingNode;
            numOfBuilding++;
        }
        for (int i = 0; i < numOfBuilding; i++)// Search for second building
        {
            if (strcmp(arrBuilding[i]->buildingName, secondBuildingName) == 0)
            {
                foundSecond = 1;
                break;
            }
        }
        if (!foundSecond)// If second building not found, create and add it
        {
            if (numOfBuilding >= BUILDING_ARRAY_SIZE)
            {
                printf("Building array is full.\n");
                fclose(input);
                return;
            }
            arrBuilding[numOfBuilding] = createBuilding(secondBuildingName, 0);
            if (arrBuilding[numOfBuilding] == NULL)
            {
                printf("Failed to allocate memory.\n");
                fclose(input);
                return;
            }
            numOfBuilding++;
        }
    }
    fclose(input);
}
/*------------------------------------------------------------*/
//case 1
//for the first file
building*createBuilding(char*buildingName,int distance)
{
    building*newBuilding =(building*)malloc(sizeof(building));
    if(newBuilding==NULL)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    newBuilding->buildingName=(char*)malloc(strlen(buildingName)+1);
    if (newBuilding->buildingName==NULL)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    strcpy(newBuilding->buildingName, buildingName);
    newBuilding->distance = distance;
    newBuilding->nextBuilding = NULL;
    return newBuilding;
}
/*------------------------------------------------------------*/
//case 1
//for the first file
void printBuildings()
{
    for (int i = 0; i < numOfBuilding; i++)
    {
        if (arrBuilding[i] != NULL)
        {
            building *current = arrBuilding[i];
            printf("%s: ", current->buildingName);
            current = current->nextBuilding;
            while (current != NULL)
            {
                printf("%s:%d ", current->buildingName, current->distance);
                current = current->nextBuilding;
            }
            printf("\n");
        }
    }
}
/*------------------------------------------------------------*/
//case 1
//for the second file
void readCoursesFromFile()
{
    FILE* input = fopen("input_courses.txt", "r");
    if (input == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), input))
    {
        char* secondCourseName = strtok(line, "#\n");
        char* prerequisite = strtok(NULL, "#\n");
        int prerequisiteIndex = -1; // Search for the prerequisite course in the array of courses
        for (int i = 0; i < numOfCourses; i++)
        {
            if (strcmp(arrCourse[i]->courseName, prerequisite) == 0)
            {
                prerequisiteIndex = i;
                break;
            }
        }
        if (prerequisiteIndex != -1)// If the prerequisite course is found, add the second course as its prerequisite
        {
            course *current = arrCourse[prerequisiteIndex];
            while (current->nextCourse != NULL)
            {
                current = current->nextCourse;
            }

            course* secondCourseNode = createCourse(secondCourseName);
            if (secondCourseNode == NULL)
            {
                printf("Allocate memory failed\n");
                return;
            }
            current->nextCourse = secondCourseNode;
        }
        else
        {
            if (numOfCourses < COURSES_ARRAY_SIZE)// If the prerequisite course is not found, create a new course for it
            {
                arrCourse[numOfCourses] = createCourse(prerequisite);
                if (arrCourse[numOfCourses] == NULL)
                {
                    printf("Allocate memory failed\n");
                    return;
                }
                course *current = arrCourse[numOfCourses];
                while (current->nextCourse != NULL)
                {
                    current = current->nextCourse;
                }

                course* secondCourseNode = createCourse(secondCourseName);
                if (secondCourseNode == NULL)
                {
                    printf("Allocate memory failed\n");
                    return;
                }
                if(strcmp("NULL",secondCourseName)!=0)
                {
                    current->nextCourse = secondCourseNode;
                }
                numOfCourses++;
            }
        }
    }
    fclose(input);
}
/*------------------------------------------------------------*/
//case 1
//for the second file
course*createCourse(char*courseName)
{
    course*newCourse=(course*)malloc(sizeof(course));
    if(newCourse==NULL)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    newCourse->courseName=(char*)malloc(strlen(courseName)+1);
    if (newCourse->courseName==NULL)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    strcpy(newCourse->courseName, courseName);
    newCourse->nextCourse = NULL;
    return newCourse;
}
/*------------------------------------------------------------*/
//case 1
//for the second file
void printCourses()
{
    for (int i = 0; i < numOfCourses; i++)
    {
        if (arrCourse[i] != NULL)
        {
            course *current = arrCourse[i];
            printf("%s", current->courseName);
            current = current->nextCourse;
            while (current != NULL)
            {
                printf(": %s ", current->courseName);
                current = current->nextCourse;
            }
            printf("\n");
        }
    }
}
/*------------------------------------------------------------*/
//case 2
void addEdge(building*source,building*second,int weight)
{
    building* newNode = createBuilding(second->buildingName, weight);
    if (newNode != NULL)
    {
        newNode->nextBuilding = source->nextBuilding;
        source->nextBuilding = newNode;
    }
}
/*------------------------------------------------------------*/
//case 2
MinHeapNode*createMinHeapNode(building*building,int distance)
{
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (newNode != NULL)
    {
        newNode->building = building;
        newNode->distance = distance;
    }
    if(newNode==NULL)
    {
        printf("allocate memory faield");
        return NULL;
    }
    return newNode;
}
/*------------------------------------------------------------*/
//case 2
MinHeap* createMinHeap(int capacity)
{
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap != NULL)
    {
        heap->capacity = capacity;
        heap->size = 0;
        heap->array = (MinHeapNode*)malloc(capacity*sizeof(MinHeapNode));
        if (heap->array == NULL)
        {
            free(heap);
            return NULL;
        }
    }
    return heap;
}
/*------------------------------------------------------------*/
//case 2
void insertNode(MinHeap*heap, MinHeapNode*newNode)
{
    if (heap == NULL || newNode == NULL || heap->size == heap->capacity)
        return;
    int i = heap->size++;
    heap->array[i] = *newNode;
    while (i != 0 && heap->array[(i - 1) / 2].distance > heap->array[i].distance)
    {
        MinHeapNode temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
/*------------------------------------------------------------*/
//case 2
MinHeapNode extractMin(MinHeap* heap)
{
    if (heap == NULL || heap->size == 0)
        return (MinHeapNode)
    {
        NULL, INT_MAX
    };
    if (heap->size == 1)
    {
        heap->size--;
        return heap->array[0];
    }
    MinHeapNode minNode = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    // Heapify down
    int i = 0;
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap->size && heap->array[left].distance < heap->array[smallest].distance)
            smallest = left;
        if (right < heap->size && heap->array[right].distance < heap->array[smallest].distance)
            smallest = right;
        if (smallest != i)
        {
            MinHeapNode temp = heap->array[i];
            heap->array[i] = heap->array[smallest];
            heap->array[smallest] = temp;
            i = smallest;
        }
        else
        {
            break;
        }
    }
    return minNode;
}
/*------------------------------------------------------------*/
//case 2
int isEmpty(MinHeap* heap)
{
    return (heap == NULL || heap->size == 0);
}
/*------------------------------------------------------------*/
//case 2
void decreaseKey(MinHeap* heap, int index, int newDistance)
{
    int i;
    for (i = 0; i < heap->size; i++)// Find the index of the building in the heap
    {
        if (heap->array[i].building == arrBuilding[index])
        {
            break;
        }
    }
    heap->array[i].distance = newDistance;// Update the distance of the building in the heap
    while (i != 0 && heap->array[(i - 1) / 2].distance > heap->array[i].distance)
    {
        MinHeapNode temp = heap->array[i];// Swap the node with its parent
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
/*------------------------------------------------------------*/
//case 2
int findBuildingIndexByName(char*name)
{
    for (int i = 0; i < numOfBuilding; i++)
    {
        if (strcmp(arrBuilding[i]->buildingName, name) == 0)
        {
            return i;
        }
    }
    return -1;// Building not found
}
/*------------------------------------------------------------*/
void dijkstra(char* firstBuildingName, char* secondBuildingName)
{
    // Find the source building index
    int sourceIndex = findBuildingIndexByName(firstBuildingName);
    if (sourceIndex == -1)
    {
        printf("The source building '%s' was not found.\n", firstBuildingName);
        return;
    }
    // Create a min heap to store distances
    MinHeap* heap = createMinHeap(numOfBuilding);
    if (heap == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    // Initialize distances to all buildings
    int* distances = (int*)malloc(numOfBuilding * sizeof(int));
    if (distances == NULL)
    {
        printf("Memory allocation failed.\n");
        free(heap);
        return;
    }
    for (int i = 0; i < numOfBuilding; i++)
    {
        if (i == sourceIndex)
            distances[i] = 0;
        else
            distances[i] = INT_MAX;
        insertNode(heap, createMinHeapNode(arrBuilding[i], distances[i]));
    }
    // Main loop of Dijkstra's algorithm
    while (!isEmpty(heap))
    {
        MinHeapNode minNode = extractMin(heap);
        building* u = minNode.building;
        int uIndex = findBuildingIndexByName(u->buildingName);
        // Traverse the adjacency list of vertex u and update distances
        building* neighbor = arrBuilding[uIndex]->nextBuilding;
        while (neighbor != NULL)
        {
            int vIndex = findBuildingIndexByName(neighbor->buildingName);
            // Update distance if a shorter path is found
            if (distances[uIndex] != INT_MAX && distances[uIndex] + neighbor->distance < distances[vIndex])
            {
                distances[vIndex] = distances[uIndex] + neighbor->distance;
                // Update priority of vertex v in the heap
                decreaseKey(heap, vIndex, distances[vIndex]);
            }
            neighbor = neighbor->nextBuilding; // Move to the next neighbor
        }
    }
    // Find the destination building index
    int destIndex = findBuildingIndexByName(secondBuildingName);
    if (destIndex == -1)
    {
        printf("The destination building '%s' was not found.\n", secondBuildingName);
        free(distances);
        free(heap->array);
        free(heap);
        return;
    }
    // Check if there is a path to the destination
    if (distances[destIndex] == INT_MAX)
    {
        printf("There is no path from '%s' to '%s'.\n", firstBuildingName, secondBuildingName);
    }
    else
    {
        // Print the shortest distance from the source building to the destination building
        printf("Shortest distance from '%s' to '%s' is: %d\n", firstBuildingName, secondBuildingName, distances[destIndex]);
    }
}
/*------------------------------------------------------------*/
//case 3
void followPath(char* firstBuildingName, char* secondBuildingName)
{
    // Find the source building index
    int sourceIndex = findBuildingIndexByName(firstBuildingName);
    if (sourceIndex == -1)
    {
        printf("The source building '%s' was not found.\n", firstBuildingName);
        return;
    }
    // Create a min heap to store distances
    MinHeap* heap = createMinHeap(numOfBuilding);
    if (heap == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    // Initialize distances and predecessors arrays
    int* distances = (int*)malloc(numOfBuilding * sizeof(int));
    int* predecessors = (int*)malloc(numOfBuilding * sizeof(int));
    if (distances == NULL || predecessors == NULL)
    {
        printf("Memory allocation failed.\n");
        free(heap);
        free(distances);
        free(predecessors);
        return;
    }
    for (int i = 0; i < numOfBuilding; i++)
    {
        if (i == sourceIndex)
        {
            distances[i] = 0;
            predecessors[i] = -1;  // Indicates no predecessor
        }
        else
        {
            distances[i] = INT_MAX;
            predecessors[i] = -1;
        }
        insertNode(heap, createMinHeapNode(arrBuilding[i], distances[i]));
    }
    // Main loop of Dijkstra's algorithm
    while (!isEmpty(heap))
    {
        MinHeapNode minNode = extractMin(heap);
        building* u = minNode.building;
        int uIndex = findBuildingIndexByName(u->buildingName);
        // Traverse the adjacency list of vertex u and update distances
        building* neighbor = arrBuilding[uIndex]->nextBuilding;
        while (neighbor != NULL)
        {
            int vIndex = findBuildingIndexByName(neighbor->buildingName);

            // Update distance if a shorter path is found
            if (distances[uIndex] != INT_MAX && distances[uIndex] + neighbor->distance < distances[vIndex])
            {
                distances[vIndex] = distances[uIndex] + neighbor->distance;
                predecessors[vIndex] = uIndex; // Update predecessor
                // Update priority of vertex v in the heap
                decreaseKey(heap, vIndex, distances[vIndex]);
            }
            neighbor = neighbor->nextBuilding; // Move to the next neighbor
        }
    }
    // Find the destination building index
    int destIndex = findBuildingIndexByName(secondBuildingName);
    if (destIndex == -1)
    {
        printf("The destination building '%s' was not found.\n", secondBuildingName);
        free(distances);
        free(predecessors);
        free(heap->array);
        free(heap);
        return;
    }
    // Check if there is a path to the destination
    if (distances[destIndex] == INT_MAX)
    {
        printf("There is no path from '%s' to '%s'.\n", firstBuildingName, secondBuildingName);
    }
    else
    {
        // Print the shortest distance from the source building to the destination building
        printf("Shortest distance from '%s' to '%s' is: %d\n", firstBuildingName, secondBuildingName, distances[destIndex]);

        // Print the path
        printf("Path: ");
        int current = destIndex;
        while (current != -1)
        {
            printf("%s", arrBuilding[current]->buildingName);
            current = predecessors[current];
            if (current != -1)
                printf(" -> ");
        }
        printf("\n");
    }
}
/*------------------------------------------------------------*/
//case 4
course*topsort()
{
    int*inDegree = (int*)malloc(numOfCourses*sizeof(int));
    if(inDegree == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for (int i = 0; i < numOfCourses; i++)
    {
        inDegree[i] = 0;// Initialize in-degrees to zero
    }
    for (int i = 0; i < numOfCourses; i++) // Calculate in-degrees for each course
    {
        course* current = arrCourse[i]->nextCourse;
        while (current != NULL)
        {
            int index = findCourseIndex(current->courseName);
            if (index != -1)
            {
                inDegree[index]++;
            }
            current = current->nextCourse;
        }
    }
    course* queue[numOfCourses];// Initialize a queue for topological sorting
    int front = 0;
    int rear = 0;
    for (int i = 0; i < numOfCourses; i++)// Enqueue courses with in-degree 0
    {
        if (inDegree[i] == 0)
        {
            queue[rear++] = arrCourse[i];
        }
    }
    int count = 0; // Initialize a counter to track the number of courses visited
    course*sorted = (course*)malloc(numOfCourses * sizeof(course));// Array to store the topological order
    if (sorted == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    while (front < rear)// Perform topological sorting
    {
        course* currentCourse = queue[front++];
        sorted[count++] = *currentCourse;
        course* current = currentCourse->nextCourse;// Reduce in-degree of adjacent courses
        while (current != NULL)
        {
            int index = findCourseIndex(current->courseName);
            if (index != -1 && --inDegree[index] == 0)
            {
                queue[rear++] = arrCourse[index];
            }
            current = current->nextCourse;
        }
    }
    if (count!= numOfCourses)
    {
        printf("Graph has a cycle!\n");
        return NULL;
    }
    free(inDegree);
    return sorted;
}
/*------------------------------------------------------------*/
//case 5
void printTopologicalSortCourses(course* sortedCourses)
{
    printf("Topological Order:\n");
    for (int i = 0; i < numOfCourses; i++)
    {
        printf("%s\n", sortedCourses[i].courseName);
    }
}
/*------------------------------------------------------------*/
//case 5
int findCourseIndex(char* course)
{
    for (int i = 0; i < numOfCourses; i++)
    {
        if (strcmp(arrCourse[i]->courseName, course) == 0)
        {
            return i;
        }
    }
    return -1;
}
