#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"

void employeeReport(void)
{
    printf("\n--- Employee Report ---\n");
    printf("Number of employees: %d\n", getEmployeeCount());

    if (getEmployeeCount() == 0) {
        printf("No salary statistics are available yet.\n");
        return;
    }

    printf("Average salary: N$%.2f\n", getAverageSalary());
    printf("Highest salary: N$%.2f\n", getHighestSalary());
    printf("Lowest salary: N$%.2f\n", getLowestSalary());
}

void budgetReport(void)
{
    generateReport();
}
