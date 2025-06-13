// #ifndef STUDENT_OPS_H
// #define STUDENT_OPS_H

// #include "person.h"

// // Function to create and write a student record to file
// void createStudentRecord(int age, char grade, char *name);

// // Print a number of student records from file (line-by-line character output)
// void ReadStudentRecords(int upto);

// // Read one record at a specific position (e.g., 3rd student)
// void RetrieveData(int position);

// // Read all records and store them into a linked list on the heap
// void storeInHeap(int upto);

// #endif // STUDENT_OPS_H


// student_ops.h
#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

void createStudentRecord(int age, char grade, char *name);
void ReadStudentRecords(int upto);
void RetrieveData(int position);
void storeInHeap(int upto);

#endif
