#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utilities.h"

#define MAX_EMPLOYEES 100
#define EMPLOYEE_ID_LEN 20
#define EMPLOYEE_NAME_LEN 100

/* Employee records are stored in matching array positions. */
static char employeeIds[MAX_EMPLOYEES][EMPLOYEE_ID_LEN];
static char employeeNames[MAX_EMPLOYEES][EMPLOYEE_NAME_LEN];
static double employeeSalaries[MAX_EMPLOYEES];
static int employeeCount = 0;

static int findEmployee(const char *id)
{
    int i;

    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employeeIds[i], id) == 0) {
            return i;
        }
    }

    return -1;
}

void addEmployee(void)
{
    char id[EMPLOYEE_ID_LEN];
    double salary;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("The employee list is full.\n");
        return;
    }

    if (!readText("Employee ID: ", id, sizeof(id))) return;

    if (findEmployee(id) >= 0) {
        printf("That employee ID already exists.\n");
        return;
    }

    if (!readText("Employee name: ",
                  employeeNames[employeeCount],
                  EMPLOYEE_NAME_LEN)) return;

    if (!readDouble("Monthly salary (N$): ", &salary)) return;

    strcpy(employeeIds[employeeCount], id);
    employeeSalaries[employeeCount] = salary;
    employeeCount++;

    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("No employees have been added.\n");
        return;
    }

    printf("\n--- Employee List ---\n");

    for (i = 0; i < employeeCount; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %s\n", employeeIds[i]);
        printf("Name: %s\n", employeeNames[i]);
        printf("Salary: N$%.2f\n", employeeSalaries[i]);
    }
}

int getEmployeeCount(void)
{
    return employeeCount;
}

double getAverageSalary(void)
{
    double total = 0.0;
    int i;

    if (employeeCount == 0) return 0.0;

    for (i = 0; i < employeeCount; i++) {
        total += employeeSalaries[i];
    }

    return total / employeeCount;
}

double getHighestSalary(void)
{
    double highest;
    int i;

    if (employeeCount == 0) return 0.0;

    highest = employeeSalaries[0];

    for (i = 1; i < employeeCount; i++) {
        if (employeeSalaries[i] > highest) {
            highest = employeeSalaries[i];
        }
    }

    return highest;
}

double getLowestSalary(void)
{
    double lowest;
    int i;

    if (employeeCount == 0) return 0.0;

    lowest = employeeSalaries[0];

    for (i = 1; i < employeeCount; i++) {
        if (employeeSalaries[i] < lowest) {
            lowest = employeeSalaries[i];
        }
    }

    return lowest;
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Back to main menu\n");

        if (!readInt("Choose an option: ", &choice)) return;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please select 1, 2 or 3.\n");
        }
    } while (choice != 3);
}
