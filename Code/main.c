/******************************************************************************************
*Filename:           main.c
*Version:            1
*Course:             C Language CST8234
*Assignment Name:    Employee Database Implementation
*Purpose:            Implement an employee database using linkedlist of structures
******************************************************************************************/

#include "header.h"

/******************************************************************************************
*Function name:              main
*Purpose:                    Main function for the employee database program calls other functions and loops through menu
*Function In parameters:     None
*Function Out parameters:    An integer for function success
*Version:                    1
******************************************************************************************/
int main()
{
    struct Employee *head;
    struct Employee *employee;
    int menuChoice = -1;
    int empCount = 0;

    /* print welcome */
    printf("\nWelcome to the Employee Database\n--------------------------------\n");

    /* allocate memory */
    head = (struct Employee *)malloc(sizeof(struct Employee));
    head->next = NULL;

    employee = (struct Employee *)malloc(sizeof(struct Employee));

    /* loop through menu */
    while (menuChoice != 5)
    {
        menuChoice = printMenu();
        switch (menuChoice)
        {
        case 1:
            /* add an employee if we do not have 150 */
            if (empCount < 150)
            {
                employee->next = NULL;

                /* ask for details */
                printf("\nEnter information for employee %d\n\n", empCount + 1);
                addEmployee(employee);

                /* first check if the name & age exist already */
                if (empCount > 0 && findEmployee(head, employee->name, employee->age) == 0)
                {
                    /* if they were found, print error */
                    printf("\nEmployee with name \"%s\" and age \"%d\" already exists. Employee was not added.\n", employee->name, employee->age);
                }
                else
                {
                    /* otherwise place them in sorted */
                    sortEmployees(head, employee, empCount);
                    empCount++;
                }
            }
            else
            {
                printf("Database is full.\n");
            }
            break;
        case 2:
            /* delete an employee */
            if (empCount > 0)
            {
                if (accessEmployee(head, employee, empCount, 1) == 1)
                {
                    empCount--;
                }
            }
            else
            {
                printf("There are no employees, use menu option 1 to add.\n");
            }
            break;
        case 3:
            /* edit an employee */
            if (empCount > 0)
            {
                accessEmployee(head, employee, empCount, 2);
            }
            else
            {
                printf("There are no employees, use menu option 1 to add.\n");
            }
            break;
        case 4:
            /* print all employees */
            if (empCount > 0)
            {
                printEmployees(head);
            }
            else
            {
                printf("There are no employees, use menu option 1 to add.\n");
            }
            break;
        case 5:
            /* exit program */
            printf("\nGood Bye.\n");
            break;
        default:
            return EXIT_FAILURE;
        }
    }

    free(employee->next);
    free(employee);
    /* free every node */
    while (head != NULL)
    {
        /* start from the head, free then move on */
        employee = head;
        head = head->next;
        free(employee);
    }

    return EXIT_SUCCESS;
}

/******************************************************************************************
*Function name:              menu
*Purpose:                    Prints the menu for the database functions and validates input
*Function In parameters:     None
*Function Out parameters:    The validated input for the menu
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
int printMenu()
{
    char input[3];
    int menuChoice = -1;

    while (menuChoice == -1)
    {
        printf("\nPlease choose one of the following actions:\n1- Add an employee\n2- Delete an employee\n3- Edit an employee\n4- Print all employees\n5- Quit\nPlease your menu choice: ");

        /* read input */
        fgets(input, 5, stdin);
        input[strcspn(input, "\n")] = 0;

        /* check if it is an int, then range */
        menuChoice = atoi(input);
        if (menuChoice == 0)
        {
            if (menuChoice == 0 && input[0] == '0' && input[1] == '\0')
            {
                /* input was 0 */
                printf("Option %d is not a valid choice. Options range from 1 to 5. Try again.\n", menuChoice);
                menuChoice = -1;
            }
            else
            {
                /* input wasnt an int */
                printf("Enter a valid whole number from 1 to 5. Try again.\n");
                menuChoice = -1;
            }
        }
        else if (menuChoice < 0 || menuChoice > 5)
        {
            /* if out of range */
            printf("Option %d is not a valid choice. Options range from 1 to 5. Try again.\n", menuChoice);
            menuChoice = -1;
        }
    }
    return menuChoice;
}

/******************************************************************************************
*Function name:              addEmployee
*Purpose:                    Reads input and adds the information to a struct of an Employee
*Function In parameters:     The employee to add information to
*Function Out parameters:    None
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
void addEmployee(struct Employee *employee)
{
    char input[MAX_NAME_LENGTH];
    int age = -1;
    char tempChar;

    input[0] = '\0';

    /* ask for details and verify */
    while (input[0] == '\0')
    {
        printf("Enter Employee Name: ");
        /* store in temp variable, remove newline */
        fgets(input, MAX_NAME_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;
        /* validate */
        verifyString(input);
    }
    /* set first letter to capital if its a lower case letter */
    tempChar = input[0];
    if ((tempChar >= 97 && tempChar <= 122))
    {
        tempChar = tempChar - 32;
        input[0] = tempChar;
    }
    /* copy into struct */
    strcpy(employee->name, input);

    input[0] = '\0';
    /* ask for details and verify */
    while (input[0] == '\0')
    {
        printf("Enter Employee Gender: ");
        /* store and remove new line */
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = 0;
        /* validate */
        verifyString(input);
    }
    /* set first letter to capital if its a lower case letter */
    tempChar = input[0];
    if ((tempChar >= 97 && tempChar <= 122))
    {
        tempChar = (tempChar - 32);
        input[0] = tempChar;
    }
    /* copy into struct */
    strcpy(employee->gender, input);

    /* validate and save age */
    while (age == -1)
    {
        printf("Enter Employee Age: ");
        /* read input */
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = 0;
        age = validateInt(input);
    }
    employee->age = age;

    input[0] = '\0';
    /* ask for details and verify */
    while (input[0] == '\0')
    {
        /* store and remove new line */
        printf("Enter Employee Description: ");
        fgets(input, MAX_JOB_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0;
        /* validate */
        verifyString(input);
    }
    /* set first letter to capital if its a lower case letter */
    tempChar = input[0];
    if ((tempChar >= 97 && tempChar <= 122))
    {
        tempChar = tempChar - 32;
        input[0] = tempChar;
    }
    /* copy into struct */
    strcpy(employee->description, input);
}

/******************************************************************************************
*Function name:              validateInt
*Purpose:                    Reads input and validates an integer to ensure it is 0 or greater
*Function In parameters:     The string input to validate if it was a integer
*Function Out parameters:    The validated integer value
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
int validateInt(char *input)
{
    int number;

    /* check if it is an int, then range */
    number = atoi(input);
    if (number == 0)
    {
        if (number == 0 && input[0] == '0' && input[1] == '\0')
        {
            /* input was 0 */
            printf("Cannot be 0. Try again.\n");
            number = -1;
        }
        else
        {
            /* input wasnt an int */
            printf("Input whole numbers only. try again.\n");
            number = -1;
        }
    }
    else if (number < 0)
    {
        /* if it is negative */
        printf("Must be a positive number. Try again.\n");
        number = -1;
    }
    else if (number > 150)
    {
        /* if it is too large */
        printf("Input is too large. Try again.\n");
        number = -1;
    }

    return number;
}

/******************************************************************************************
*Function name:              verifyString
*Purpose:                    Takes a string and verifies it has no disallowed characters
*Function In parameters:     The string to compare
*Function Out parameters:    None
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
void verifyString(char *string)
{
    char tempChar = string[0];
    int i = 0;

    /* confirm it does not begin with dash, apostrophe or space */
    if (tempChar == 96 || tempChar == 45 || tempChar == 39 || tempChar == 32)
    {
        printf("Can not begin with \"%c\", try again.\n", tempChar);
        i = strlen(string);
        string[0] = '\0';
    }
    /* verify there are no invalid characters in the whole string */
    while (i < strlen(string))
    {
        if (tempChar != 32 && tempChar != 39 && tempChar != 45 && tempChar != 96 && !(tempChar >= 65 && tempChar <= 90) && !(tempChar >= 97 && tempChar <= 122))
        {
            printf("Invalid character \"%c\" entered, try again.\n", tempChar);
            string[0] = '\0';
            i = strlen(string);
        }
        i++;
        tempChar = string[i];
        /* capitalise a letter if its preceeded by a space */
        if (string[i - 1] == 32 && (tempChar >= 97 && tempChar <= 122))
        {
            tempChar = tempChar - 32;
            string[i] = tempChar;
        }
    }
}

/******************************************************************************************
*Function name:              sortEmployees
*Purpose:                    Finds where to place the employee based on alphabetic order
*Function In parameters:     Head/first employee, employee being added and how many employees there are
*Function Out parameters:    None
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
void sortEmployees(struct Employee *head, struct Employee *employee, int empCount)
{

    int i;

    /* if it's the first one, add it to head otherwise make it current */
    if (empCount == 0)
    {
        /* set as head */
        *head = *employee;
    }
    else if (employee->name[0] < head->name[0])
    {
        /* if should be ordered before head, set head as the next data, and the employee as head */
        if (employee->next == NULL)
        {
            employee->next = (struct Employee *)malloc(sizeof(struct Employee));
        }
        *employee->next = *head;
        *head = *employee;
    }
    else
    {
        /* loop to check where it should enter */
        for (i = 0; i < empCount; i++)
        {
            /* set head next if we are adding to the end */
            if (head->next == NULL)
            {
                head->next = (struct Employee *)malloc(sizeof(struct Employee));
                /* add to the end of list */
                employee->next = NULL;
                *head->next = *employee;
            }
            /* if its between two employees add in the middle */
            else if (employee->name[0] < head->next->name[0])
            {
                /* add in sorted position */
                if (employee->next == NULL)
                {
                    employee->next = (struct Employee *)malloc(sizeof(struct Employee));
                }
                *employee->next = *head->next;
                *head->next = *employee;

                i = empCount;
            }
            head = head->next;
        }
    }
}

/******************************************************************************************
*Function name:              findEmployee
*Purpose:                    Finds a provided employee based on name and age in provided list
*Function In parameters:     The first employee in linked list, the employee name, the employee age
*Function Out parameters:    Whether they were found or not
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
int findEmployee(struct Employee *head, char *name, int age)
{
    int i = 1;

    /* first check if it is the head */
    if (strcmp(name, head->name) == 0 && head->age == age)
    {
        /* if it is return true for found */
        return 0;
    }
    else
    {
        /* otherwise loop through until they're found */
        while (head->next != NULL)
        {
            /* if its a match return success */
            if (strcmp(name, head->next->name) == 0 && head->next->age == age)
            {
                return 0;
            }
            i++;
            head = head->next;
        }
    }

    /* if they were not found return false */
    return 1;
}

/******************************************************************************************
*Function name:              printEmployees
*Purpose:                    Prints all employees and their information
*Function In parameters:     The first employee in linked list to print
*Function Out parameters:    None
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
void printEmployees(struct Employee *employee)
{
    int count = 1;

    printf("\n-------------------------\n--- Employee Database ---\n-------------------------\n\n");
    /* loop through until the struct is null */
    while (employee != NULL)
    {
        /* print information */
        printf("Employee %d\n------------\nName: %s \nGender: %s \nAge: %d \nJob Description: %s\n\n", count, employee->name, employee->gender, employee->age, employee->description);
        /* increment count, set struct to next one */
        count++;
        employee = employee->next;
    }
}

/******************************************************************************************
*Function name:              accessEmployee
*Purpose:                    Accesses an selected employee to edit or delete them
*Function In parameters:     The head of the linked list, a temporary employee, the number of employees and option for deleting or editing 
*Function Out parameters:    Integer how many were deleted
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
int accessEmployee(struct Employee *head, struct Employee *employee, int empCount, int option)
{
    int success;
    int i = 1;
    char input[5];
    int number = -1;
    char *message;
    int found = 0;
    char name[MAX_NAME_LENGTH];
    int age;
    struct Employee *temp;

    /* set a variable for deleting or editing */
    if (option == 1)
    {
        message = "Delete";
    }
    else
    {
        message = "Edit";
    }

    printEmployees(head);

    /* ask which one to delete */
    while (number == -1)
    {
        printf("Enter employee number to select: ");
        /* read input */
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = 0;
        number = validateInt(input);

        if (number > empCount)
        {
            printf("Employee %d is the last employee, %d is too large. Try again.\n", empCount, number);
            number = -1;
        }
    }

    /* Loop until employee */
    if (number > 2)
    {
        for (i = 1; i < number - 1; i++)
        {
            head = head->next;
        }
    }

    /* confirm */
    input[0] = '\0';
    while (input[0] == '\0')
    {
        if (number == 1)
        {
            printf("%s employee %d: %s, age: %d ? (\"y\" for yes, \"n\" for no): ", message, number, head->name, head->age);
        }
        else
        {
            printf("%s employee %d: %s, age: %d ? (\"y\" for yes, \"n\" for no): ", message, number, head->next->name, head->next->age);
        }
        fgets(input, 20, stdin);
        input[strcspn(input, "\n")] = 0;
        /* lower case the letter */
        if (input[0] >= 65 && input[0] <= 90)
        {
            input[0] = input[0] + 32;
        }
        /* check if valid */
        if (input[1] != '\0' || (input[0] != 'y' && input[0] != 'n'))
        {
            printf("Invalid input \"%s\", try again.\n", input);
            input[0] = '\0';
        }
    }

    /* if they cancel set success as 0, else success is employee position */
    if (input[0] != 'n')
    {
        success = number;
    }
    else
    {
        success = 0;
    }

    /* if employee found, delete and edit - function prints by default */
    if (success != 0)
    {
        /* if we are deleting or editing the head */
        if (success == 1)
        {
            /* copy if editing and delete the head */
            if (option == 2)
            {
                *employee = *head;
                employee->next = NULL;
            }
            if (head->next != NULL)
            {
                temp = head->next;
                *head = *head->next;
                free(temp);
            } else {
                head = NULL;
            }
            /* if we are deleting, print so otherwise enter new employee details */
            if (option == 1)
            {
                printf("Employee was deleted.\n");
                return 1;
            }
            else
            {
                /* edit the copied employee then re sort */
                /* copy original name and age in case of duplicate */
                strcpy(name, employee->name);
                age = employee->age;

                /* edit the employee */
                editEmployee(employee);

                /* first check if the name & age exist already */
                found = findEmployee(head, employee->name, employee->age);
                if (found == 0)
                {
                    /* if they were found, print error */
                    printf("\nEmployee with name \"%s\" and age \"%d\" already exists. Changes were not made.\n", employee->name, employee->age);

                    /* copy original values back */
                    employee->age = age;
                    strcpy(employee->name, name);
                }

                /* insert employee */
                sortEmployees(head, employee, empCount - 1);
            }
        }
        /* if we are editing or deleting other than the head */
        else
        {
            /* copy if editing then remove the one after head */
            if (option == 2)
            {
                *employee = *head->next;
                employee->next = NULL;
            }
            temp = head->next;
            head->next = head->next->next;
            free(temp);
            /* if we are deleting, print so otherwise enter new employee details */
            if (option == 1)
            {
                printf("Employee was deleted.\n");
                return 1;
            }
            else
            {
                /* edit the copied employee then re sort */
                /* copy original name and age in case of duplicate */
                strcpy(name, employee->name);
                age = employee->age;

                /* edit the employee */
                editEmployee(employee);

                /* first check if the name & age exist already */
                found = findEmployee(head, employee->name, employee->age);
                if (found == 0)
                {
                    /* if they were found, print error */
                    printf("\nEmployee with name \"%s\" and age \"%d\" already exists. Changes were not made.\n", employee->name, employee->age);

                    /* copy original values back */
                    employee->age = age;
                    strcpy(employee->name, name);
                }

                /* insert employee */
                sortEmployees(head, employee, empCount - 1);
            }
        }
    }
    return 0;
}

/******************************************************************************************
*Function name:              editEmployee
*Purpose:                    Asks what to edit of a provided employee
*Function In parameters:     The employee to edit
*Function Out parameters:    None
*Version:                    1
*Authors:                    Mostapha Abdelaziz
******************************************************************************************/
void editEmployee(struct Employee *employee)
{
    char menuOption[10];
    char string[MAX_NAME_LENGTH];
    int age = -1;
    int success;

    /* loop for validation */
    success = 1;
    while (success == 1)
    {
        /* ask for what to change */
        printf("Enter the corresponding option\n 1. Name\n 2. Gender\n 3. Age\n 4. Description\n > ");
        fgets(menuOption, 10, stdin);
        menuOption[strcspn(menuOption, "\n")] = 0;

        /* if invalid print so */
        if (menuOption[1] != '\0' || (menuOption[0] != '1' && menuOption[0] != '2' && menuOption[0] != '3' && menuOption[0] != '4'))
        {
            printf("Invalid menu choice \"%s\", try again.\n", menuOption);
            success = 1;
        }
        else
        {
            /* otherwise implement choice */
            success = 0;
            string[0] = '\0';
            switch (menuOption[0])
            {
            case '1':
                /* ask for name */
                while (string[0] == '\0')
                {
                    printf("Enter new Employee Name: ");
                    /* store in temp variable, remove newline */
                    fgets(string, MAX_NAME_LENGTH, stdin);
                    string[strcspn(string, "\n")] = 0;
                    /* validate */
                    verifyString(string);
                }
                /* set first letter to capital if its a lower case letter */
                if ((string[0] >= 97 && string[0] <= 122))
                {
                    string[0] = string[0] - 32;
                }

                /* change employee name */
                strcpy(employee->name, string);
                break;
            case '2':
                /* ask for gender */
                while (string[0] == '\0')
                {
                    printf("Enter new Employee gender: ");
                    /* store in temp variable, remove newline */
                    fgets(string, MAX_NAME_LENGTH, stdin);
                    string[strcspn(string, "\n")] = 0;
                    /* validate */
                    verifyString(string);
                }
                /* set first letter to capital if its a lower case letter */
                if ((string[0] >= 97 && string[0] <= 122))
                {
                    string[0] = string[0] - 32;
                }

                /* change employee gender */
                strcpy(employee->gender, string);
                break;
            case '3':
                /* ask for employee age */
                while (age == -1)
                {
                    printf("Enter Employee Age: ");
                    /* read input */
                    fgets(string, 5, stdin);
                    string[strcspn(string, "\n")] = 0;
                    age = validateInt(string);
                }
                /* change employee age */
                employee->age = age;
                break;
            case '4':
                /* ask for description */
                while (string[0] == '\0')
                {
                    printf("Enter new Employee description: ");
                    /* store in temp variable, remove newline */
                    fgets(string, MAX_NAME_LENGTH, stdin);
                    string[strcspn(string, "\n")] = 0;
                    /* validate */
                    verifyString(string);
                }
                /* set first letter to capital if its a lower case letter */
                if ((string[0] >= 97 && string[0] <= 122))
                {
                    string[0] = string[0] - 32;
                }

                /* change employee description */
                strcpy(employee->description, string);
                break;
            default:
                printf("No changes were made.\n");
                break;
            }
        }
    }
}
