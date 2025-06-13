// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "person.h"
// #include "student_ops.h"

// #define SERIALIZED_DATA "(%d, %c, %s )\n" // how data is saved to file

// // These are shared with `main.c`
// extern Person *P1; // Temporary heap object for writing
// extern Person P2;  // Temporary stack object for reading

// // Linked list node to store each Person
// typedef struct Person_list {
//     Person person;
//     struct Person_list *next;
// } Person_list;

// // Writes a new Person struct to file after taking its details
// void createStudentRecord(int age, char grade, char *name)
// {
//     P1 = malloc(sizeof(Person)); // heap allocation

//     // Fill data into the struct
//     P1->age = age;
//     P1->grade = grade;
//     strcpy(P1->name, name);

//     // Open file in append mode
//     FILE *file = fopen("students.dat", "a");
//     if (!file) {
//         perror("Failed to open file");
//         exit(1);
//     }

//     // Write record in defined format
//     fprintf(file, SERIALIZED_DATA, P1->age, P1->grade, P1->name);

//     fclose(file);
// }

// // Reads characters from the file and prints them up to `upto` records
// void ReadStudentRecords(int upto)
// {
//     if (upto == -1) upto = 1000; // read up to 1000 lines by default

//     FILE *file = fopen("students.dat", "r");
//     if (!file) {
//         perror("Failed to open file");
//         return;
//     }

//     int i = 0;
//     char c = fgetc(file); // get first character

//     while (c != EOF && i < upto) {
//         putchar(c);         // display char
//         if (c == '\n') i++; // count lines
//         c = fgetc(file);    // move to next character
//     }

//     fclose(file);
// }

// // Retrieves a record from a specific line number (1-indexed)
// void RetrieveData(int position)
// {
//     FILE *file = fopen("students.dat", "r");
//     if (!file) {
//         perror("Failed to open file");
//         return;
//     }

//     int i = 1;
//     int found = 0;

//     // Read line-by-line using fscanf
//     while (!feof(file)) {
//         fscanf(file, SERIALIZED_DATA, &P2.age, &P2.grade, P2.name);
//         if (i == position) {
//             found = 1;
//             break; 
//         }
//         i++;
//     }

//     if (found)
//         printf("Retrieved: %s %d %c\n", P2.name, P2.age, P2.grade);
//     else
//         printf("No record found at position %d\n", position);

//     fclose(file);
// }

// // Reads all records and stores them as linked list nodes in the heap
// void storeInHeap(int upto)
// {
//     FILE *file = fopen("students.dat", "r");
//     if (!file) {
//         perror("Failed to open file");
//         return;
//     }

//     // Count total number of records by counting newlines
//     int safety_check = 0;
//     char c;
//     while ((c = fgetc(file)) != EOF)
//         if (c == '\n') safety_check++;

//     rewind(file); // go back to start

//     Person_list *headPtr = NULL;
//     Person *t = malloc(sizeof(Person)); // buffer struct
//     int i = 1;

//     // Read each line and add to linked list
//     while (i <= safety_check && i <= upto) {
//         fscanf(file, SERIALIZED_DATA, &t->age, &t->grade, t->name);

//         // Copy data into a new person
//         Person *temp = malloc(sizeof(Person));
//         *temp = *t;

//         // Create a new linked list node
//         Person_list *l = malloc(sizeof(Person_list));
//         l->person = *temp;
//         l->next = headPtr; // insert at head (reverse order)
//         headPtr = l;

//         i++;
//     }

//     fclose(file);
//     free(t);

//     // Print all data from the linked list
//     Person_list *temp = headPtr;
//     while (temp) {
//         printf("age -->  %d, grade --> %c, name --> %s\n", temp->person.age, temp->person.grade, temp->person.name);
//         temp = temp->next;
//     }

//     // Free all memory in the list
//     while (headPtr) {
//         Person_list *next = headPtr->next;
//         free(headPtr);
//         headPtr = next;
//     }
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "person.h"
#include "student_ops.h"

// #ifdef _WIN32
//     mkdir("records"); // Windows doesn't accept mode
// #else
//     mkdir("records", 0777); // Unix/Linux version
// #endif

// #ifdef _WIN32
//     mkdir(folder);
// #else
//     mkdir(folder, 0777);
// #endif

#define SERIALIZED_DATA "(%d, %c, %s )\n"

Person *P1;
Person P2;

char *getTodayFilePath()
{
    static char path[200];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(path, "records/%04d-%02d-%02d/students.dat",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    return path;
}
/*
void ensureRecordFolderExists()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char folder[100];
    sprintf(folder, "records/%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    struct stat st = {0};

    mkdir("records", 0777); // for parent folder
    if (stat(folder, &st) == -1)
        mkdir(folder, 0777);
}
 */

void ensureRecordFolderExists()
{
    // Create records directory
#ifdef _WIN32
    mkdir("records");
#else
    mkdir("records", 0777);
#endif

    // Create today's date folder inside records
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char folder[100];
    strftime(folder, sizeof(folder), "records/%Y-%m-%d", tm_info);

#ifdef _WIN32
    mkdir(folder);
#else
    mkdir(folder, 0777);
#endif
}

void createStudentRecord(int age, char grade, char *name)
{
    ensureRecordFolderExists();

    P1 = malloc(sizeof(Person));
    P1->age = age;
    P1->grade = grade;
    strcpy(P1->name, name);

    FILE *file = fopen(getTodayFilePath(), "a");

    if (!file)
    {
        perror("Error opening student record file");
        return;
    }

    fprintf(file, SERIALIZED_DATA, P1->age, P1->grade, P1->name);
    fclose(file);
    free(P1);
}

void ReadStudentRecords(int upto)
{
    if (upto == -1)
        upto = 1000;

    FILE *file = fopen(getTodayFilePath(), "r");
    if (!file)
    {
        printf("No student records found for today.\n");
        return;
    }

    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF && i < upto)
    {
        putchar(c);
        if (c == '\n')
            i++;
    }

    fclose(file);
}

void RetrieveData(int position)
{
    FILE *file = fopen(getTodayFilePath(), "r");
    if (!file)
    {
        printf("No student records found.\n");
        return;
    }

    int i = 1;
    int found = 0;

    while (fscanf(file, SERIALIZED_DATA, &P2.age, &P2.grade, P2.name) == 3)
    {
        if (i == position)
        {
            printf("Found: %s %d %c\n", P2.name, P2.age, P2.grade);
            found = 1;
            break;
        }
        i++;
    }

    if (!found)
    {
        printf("No record at position %d.\n", position);
    }

    fclose(file);
}

typedef struct Person_list
{
    Person person;
    struct Person_list *next;
} Person_list;

void storeInHeap(int upto)
{
    FILE *file = fopen(getTodayFilePath(), "r");
    if (!file)
    {
        printf("No student records found.\n");
        return;
    }

    Person_list *head = NULL;
    Person temp;
    int i = 0;

    while (fscanf(file, SERIALIZED_DATA, &temp.age, &temp.grade, temp.name) == 3 && i < upto)
    {
        Person_list *node = malloc(sizeof(Person_list));
        node->person = temp;
        node->next = head;
        head = node;
        i++;
    }

    fclose(file);

    Person_list *curr = head;
    while (curr)
    {
        printf("age: %d | grade: %c | name: %s\n", curr->person.age, curr->person.grade, curr->person.name);
        curr = curr->next;
    }

    // Free memory
    while (head)
    {
        Person_list *next = head->next;
        free(head);
        head = next;
    }
}
