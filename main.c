#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERIALIZED_DATA "(%d, %c, %s )\n"

typedef struct Person
{
    char name[20];
    int age;
    char grade;
} Person;

typedef struct Person_list
{
    Person person;
    struct Person_list *next;
} Person_list;
// Person p1 = {.name = "shivang", .age = 19, .grade = 'B'}; // if we initialize and assign at the same time then it works for string without strcpy fn
Person *P1;
Person P2;

void createStudentRecord(int age, char grade, char *name);

void ReadStudentRecords(int upto);

void RetrieveData(int position);

void storeInHeap(int upto);

int main()
{

        createStudentRecord(22, 'C', "raj");
        createStudentRecord(19, 'B', "shivang");
        createStudentRecord(19, 'B', "shivang");
        createStudentRecord(19, 'A', "shivang");

    ReadStudentRecords(-1);
    RetrieveData(3);
    storeInHeap(1000);
    return 0;
}

void createStudentRecord(int age, char grade, char *name)
{
    P1 = malloc(sizeof(Person));

    P1->age = age;
    P1->grade = grade;
    strcpy(P1->name, name);

    FILE *file;

    file = fopen("students.dat", "a");

    fprintf(file, SERIALIZED_DATA, P1->age, P1->grade, P1->name);

    fclose(file);
}

void ReadStudentRecords(int upto)
{
    if (upto == -1)
        upto = 1000;

    FILE *file;

    file = fopen("students.dat", "r");

    // char i = 0;
    int i = 0;
    char c = fgetc(file);

    putchar(c);

    while (c != EOF && /* (int)  */ i < upto)
    // while ((c = fgetc(file)) != EOF && i < upto)
    {
        // so the reason why while((c= fgetc(file) ) !=EOF) was used because it first initialized the value then compared but i did it wrong it can be fixed by pointed the first char manually outside the loop body
        // this will also fix the i not being integer

        c = fgetc(file); // read the byte value and increment by 1 to read the next content in the file
        putchar(c);
        // display char one by one

        if (c == '\n')
            i += 1;
    }

    fclose(file);
    // char nominal[1024];

    /*   while (c != EOF)
      {
          c = fgetc(file);
          fgets(nominal, 1024, file);
      }
      printf("%s ", nominal); */
}

void RetrieveData(int position)
{
    char buffer[2048];

    int max_read = 1024;

    int keep_reading = 1;

    FILE *file;

    file = fopen("students.dat", "r");

    // char c;

    char i = 1;

    // char grade;

    // int age;

    do
    {
        // fgets(buffer, max_read, file);
        fscanf(file, SERIALIZED_DATA, &P2.age, &P2.grade, P2.name);

        if (i == max_read)
        {
            keep_reading = 0;
            printf("no record available \n");
        }

        else if (i == position && feof(file) != 0)
        {

            // fseek(file, , SEEK_SET);
            // printf("%s\n", buffer);

            keep_reading = 0;
        }

        // if (i == position - 1)

        i++;
    } while (keep_reading);

    printf("%s %d %c ", P2.name, P2.age, P2.grade);

    fclose(file);

    return;
}

void storeInHeap(int upto)
{

    FILE *file;

    file = fopen("students.dat", "r");

    int keep_inserting = 1; // true

    Person_list *headPtr = NULL;

    Person *t = (Person *)malloc(sizeof(Person));

    int i = 1;
    char c;
    int safety_check = 0;
    while ((c = fgetc(file)) != EOF)

        if (c == '\n')
            safety_check++;

    fseek(file, SEEK_SET, 0);

    do
    {
        fscanf(file, SERIALIZED_DATA, &t->age, &t->grade, t->name);

        Person *temp = (Person *)malloc(sizeof(Person));

        if (1)
        {
            strcpy(temp->name, t->name);
            temp->age = t->age;
            temp->grade = t->grade;
        }

        if (headPtr == NULL)
        {
            Person_list *l = malloc(sizeof(Person_list));

            headPtr = l;

            l->person = *temp;
            l->next = NULL;
        }
        else
        {
            Person_list *l = malloc(sizeof(Person_list));

            l->person = *temp;

            l->next = headPtr;

            headPtr = l;
        }

        if (i == upto || i >= safety_check + 1)
            keep_inserting = 0;

        i++;
    } while (keep_inserting);

    fclose(file);

    Person_list *temp = headPtr;

    while (temp != NULL)
    {
        printf("age -->  %d, grade --> %c, name --> %s\n\n", temp->person.age, temp->person.grade, temp->person.name);
        temp = temp->next;
    }
    // free that memory
    temp = headPtr;
    while (temp)
    {
        // Person_list nTemp = *temp->next;
        free(temp);
        temp = temp->next;
        
    }
}
// char c;

// fclose(file);

// file = fopen("students.dat", "r");