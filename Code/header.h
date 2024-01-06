/******************************************************************************************
*Assignment Name:    Employee Database Implementation
*Course:             C Language CST8234
*Source Files:       main.c header.h
******************************************************************************************/

#ifndef header_h
#define header_h

/* needed libraries */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 100
#define MAX_JOB_LENGTH 100

/* Employee structure*/
struct Employee
{
    char name[MAX_NAME_LENGTH];
    char gender[20];
    int age;
    char description[MAX_JOB_LENGTH];

    /* pointers to next employee structures in the linked list*/
    struct Employee *next;
};

/* function declarations */
void addEmployee(struct Employee *employee);
void printEmployees(struct Employee *employee);
int validateInt(char *input);
int printMenu();
void sortEmployees(struct Employee *head, struct Employee *employee, int empCount);
void verifyString(char *string);
int findEmployee(struct Employee *head, char *name, int age);
void editEmployee(struct Employee *employee);
int accessEmployee(struct Employee *head, struct Employee *employee, int empCount, int option);

#endif
