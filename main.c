#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "reports.h"
#include "utilities.h"

int main(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Employee management\n");
        printf("2. Budget management\n");
        printf("3. Employee report\n");
        printf("4. Budget report\n");
        printf("5. Exit\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("\nEnd of input. Closing program.\n");
            break;
        }

        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                employeeReport();
                break;
            case 4:
                budgetReport();
                break;
            case 5:
                printf("Thank you for using MFMS. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select 1 to 5.\n");
        }
    } while (choice != 5);

    return 0;
}
