#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utilities.h"

#define MAX_DEPARTMENTS 100
#define DEPARTMENT_NAME_LEN 100

/* Matching indexes represent the same department. */
static char departments[MAX_DEPARTMENTS][DEPARTMENT_NAME_LEN];
static double allocatedBudget[MAX_DEPARTMENTS];
static double expenditures[MAX_DEPARTMENTS];
static int departmentCount = 0;

static int findDepartment(const char *name)
{
    int i;

    for (i = 0; i < departmentCount; i++) {
        if (strcmp(departments[i], name) == 0) {
            return i;
        }
    }

    return -1;
}

void addBudget(void)
{
    char name[DEPARTMENT_NAME_LEN];
    double amount;

    if (departmentCount >= MAX_DEPARTMENTS) {
        printf("The department list is full.\n");
        return;
    }

    if (!readText("Department name: ", name, sizeof(name))) return;

    if (findDepartment(name) >= 0) {
        printf("A budget for that department already exists.\n");
        return;
    }

    if (!readDouble("Allocated budget (N$): ", &amount)) return;

    strcpy(departments[departmentCount], name);
    allocatedBudget[departmentCount] = amount;
    expenditures[departmentCount] = 0.0;
    departmentCount++;

    printf("Department budget added successfully.\n");
}

void enterExpenditure(void)
{
    char name[DEPARTMENT_NAME_LEN];
    double amount;
    int index;

    if (departmentCount == 0) {
        printf("Add a department budget before entering expenditure.\n");
        return;
    }

    if (!readText("Department name: ", name, sizeof(name))) return;

    index = findDepartment(name);

    if (index < 0) {
        printf("Department not found. Check the name and try again.\n");
        return;
    }

    if (!readDouble("Expenditure amount (N$): ", &amount)) return;

    expenditures[index] += amount;
    printf("Expenditure recorded successfully.\n");
}

void displayBudgets(void)
{
    int i;

    if (departmentCount == 0) {
        printf("No departmental budgets have been added.\n");
        return;
    }

    printf("\n--- Department Budgets ---\n");

    for (i = 0; i < departmentCount; i++) {
        printf("\nDepartment: %s\n", departments[i]);
        printf("Allocated: N$%.2f\n", allocatedBudget[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining: N$%.2f\n",
               allocatedBudget[i] - expenditures[i]);

        if (expenditures[i] > allocatedBudget[i]) {
            printf("Status: OVER BUDGET\n");
        } else {
            printf("Status: Within budget\n");
        }
    }
}

void generateReport(void)
{
    double totalAllocated = 0.0;
    double totalSpent = 0.0;
    int i;

    printf("\n--- Budget Report ---\n");

    if (departmentCount == 0) {
        printf("No departmental budgets are available.\n");
        return;
    }

    for (i = 0; i < departmentCount; i++) {
        totalAllocated += allocatedBudget[i];
        totalSpent += expenditures[i];
    }

    printf("Number of departments: %d\n", departmentCount);
    printf("Total allocated: N$%.2f\n", totalAllocated);
    printf("Total expenditure: N$%.2f\n", totalSpent);
    printf("Overall balance: N$%.2f\n", totalAllocated - totalSpent);
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add departmental budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budgets\n");
        printf("4. Generate budget report\n");
        printf("5. Back to main menu\n");

        if (!readInt("Choose an option: ", &choice)) return;

        switch (choice) {
            case 1:
                addBudget();
                break;
            case 2:
                enterExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please select 1 to 5.\n");
        }
    } while (choice != 5);
}
