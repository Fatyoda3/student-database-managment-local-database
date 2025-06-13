// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "person.h"
#include "student_ops.h"

// ANSI Colors
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

// Show main menu
void showMenu() {
    printf(CYAN "\n========= Student Record Manager =========\n" RESET);
    printf(YELLOW "1. " RESET " Create new student record\n");
    printf(YELLOW "2. " RESET " Show today's records\n");
    printf(YELLOW "3. " RESET " Retrieve record by position\n");
    printf(YELLOW "4. " RESET " Load records into memory (heap)\n");
    printf(YELLOW "0. " RESET " Exit\n");
}

// Fancy loading animation
void loading(const char *msg) {
    const char spinner[] = "|/-\\";
    printf(BLUE "%s " RESET, msg);
    fflush(stdout);
    for (int i = 0; i < 10; ++i) {
        printf(BLUE "%c" RESET, spinner[i % 4]);
        fflush(stdout);
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000);
#endif
        printf("\b");
    }
    printf(GREEN "✔️ Done!\n" RESET);
}

// Terminal beep
void beep() {
    printf("\a");
    fflush(stdout);
}

int main() {
    int choice, age, upto, position;
    char grade;
    char name[100];

    do {
        showMenu();
        printf(MAGENTA "\nEnter your choice: " RESET);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear input buffer
            beep();
            printf(RED " Invalid input. Please enter a number.\n" RESET);
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf(MAGENTA "Enter name: " RESET);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf(MAGENTA "Enter age: " RESET);
                if (scanf("%d", &age) != 1) {
                    while (getchar() != '\n');
                    beep();
                    printf(RED " Invalid age input.\n" RESET);
                    break;
                }

                printf(MAGENTA "Enter grade: " RESET);
                getchar(); // remove newline
                grade = getchar();

                loading("Creating record...");
                createStudentRecord(age, grade, name);
                beep();
                printf(GREEN " Record added for %s!\n" RESET, name);
                break;

            case 2:
                printf(MAGENTA "Enter how many records to read (-1 for all): " RESET);
                if (scanf("%d", &upto) != 1) {
                    while (getchar() != '\n');
                    beep();
                    printf(RED " Invalid input.\n" RESET);
                    break;
                }
                loading("Reading records...");
                ReadStudentRecords(upto);
                beep();
                break;

            case 3:
                printf(MAGENTA "Enter record position to retrieve: " RESET);
                if (scanf("%d", &position) != 1) {
                    while (getchar() != '\n');
                    beep();
                    printf(RED " Invalid position.\n" RESET);
                    break;
                }
                loading("Retrieving record...");
                RetrieveData(position);
                beep();
                break;

            case 4:
                printf(MAGENTA "Enter how many records to load: " RESET);
                if (scanf("%d", &upto) != 1) {
                    while (getchar() != '\n');
                    beep();
                    printf(RED " Invalid input.\n" RESET);
                    break;
                }
                loading("Loading records into memory...");
                storeInHeap(upto);
                beep();
                break;

            case 0:
                loading("Exiting system...");
                printf(RED " Goodbye, see you soon!\n" RESET);
                beep();
                break;

            default:
                beep();
                printf(RED " Invalid option. Try again.\n" RESET);
        }

    } while (choice != 0);

    return 0;
}
