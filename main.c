#include "saass.h"
#include <stdio.h>
void print_ascii_art(){
    printf("\n");
    printf("  #####    #####   #####   #####   #####\n");
    printf("  #        #   #   #   #   #       #\n");
    printf("  #####    #####   #####   #####   #####\n");
    printf("      #    #   #   #   #       #       #\n");
    printf("  #####    #   #   #   #   #####   #####\n");
    printf("\n");
}

int main(void)
{
    int choice;

    while (1)
    {
        print_ascii_art();
        printf("\nWelcome To SAASS Hospital Management System\n");
        printf("1. Register New Patient\n");
        printf("2. Login\n");
        printf("3. Director Login\n");
        printf("4. Report A Problem\n");
        printf("5. Hospital Information & Hours\n");
        printf("6. Exit System\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Invalid Input. Numbers Only.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        switch (choice)
        {
        case 1:
            Register_Patient();
            break;
        case 2:
            unified_login();
            break;
        case 3:
            directorMen();
            break;
        case 4:
            submit_system_report();
            break;
        case 5:
            display_hospital_info();
            break;
        case 6:
            printf("\nThank You For Using The SAASS Hospital System. Goodbye!\n\n");
            return 0;
        case 0:
            return 0;

        default:
            printf("\n[ERROR] Invalid Choice! Please Select 1-5.\n");
        }
    }
    return 0;
}