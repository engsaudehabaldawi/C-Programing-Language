#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"
const char director_user[20] = "saass";
const char director_password[20] = "saass1234";
int director_sign_system(void)
{
    int choice_1;
    char sign_name[50];
    char sign_password[50];

    printf("\n===== Sign In =====\n");

    while (1)
    {
        printf("1. Sign In \n2. Log Out\nChoose A Number: ");
        if (scanf("%d", &choice_1) != 1)
        {
            printf("\nInvalid Input! Numbers Only\n");
            printf("\n----------------------------\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }
        else
        {
            break;
        }
    }

    if (choice_1 == 1)
    {
        int i = 3;
        while (1)
        {
            printf("--------------Press 0 To Return--------------");
            printf("\nEnter User Name: ");
            scanf("%9s", sign_name);
            if (strcmp(sign_name, "0") == 0)
            {
                printf("\nReturning to Main Menu...\n");
                return 0;
            }
            printf("Enter Password:  ");
            scanf("%9s", sign_password);
            if (strcmp(sign_password, "0") == 0)
            {
                printf("\nReturning to Main Menu...\n");
                return 0;
            }

            if (strcmp(director_user, sign_name) == 0 && strcmp(director_password, sign_password) == 0)
            {
                printf("\n------ Successfully Logged In ------\n");
                return 1;
            }
            else if (i <= 0)
            {
                printf("------ Too Many Tries, Logging Out ------ ");
                return 0;
            }
            else
            {
                printf("\n------ Wrong Input! %d Tries Left ------\n", i);
                i = (i - 1);
            }
        }
    }
    else
    {
        printf("------ Going To Main Menu ------");
        return 0;
    }

    return 0;
}

void directorMen(void)
{

    if (director_sign_system() == 0)
    {
        return;
    }

    int choice;

    do
    {
        printf("\n=====================================\n");
        printf("            Director Menu            \n");
        printf("=====================================\n");
        printf("1. Manage Administrator\n");
        printf("2. Staff Report\n");
        printf("3. Appointment Trend Report\n");
        printf("4. Logout\n");
        printf("=====================================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            manageAdmin();
        }
        else if (choice == 2)
        {
            staffReport();
        }
        else if (choice == 3)
        {
            appointmentTrendReport();
        }
        else if (choice == 4)
        {
            printf("Logging Out...\n");
        }
        else
        {
            printf("Invalid Choice. Please Try Again.\n");
        }

    } while (choice != 4);
}

void manageAdmin()
{
    int choice;

    do
    {
        printf("\n=====================================\n");
        printf("        Manage Administrator         \n");
        printf("=====================================\n");
        printf("1. Add New Administrator\n");
        printf("2. Search Administrator\n");
        printf("3. View All Administrators\n");
        printf("4. Remove Admin\n");
        printf("5. Back\n");
        printf("=====================================\n");
        printf("Enter Your Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Invalid Input. Numbers Only.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (choice == 1)
        {
            addAdmin();
        }
        else if (choice == 2)
        {
            searchAdmin();
        }
        else if (choice == 3)
        {
            viewAllAdmins();
        }
        else if (choice == 4)
        {

            remove_admin();
        }
        else if (choice == 5)
        {
            printf("Going Back...\n");
        }
        else
        {
            printf("Invalid Choice. Please Try Again.\n");
        }

    } while (choice != 5);
}

void addAdmin()
{
    char id[20];
    char username[50];
    char password[50];
    char name[100];
    char least_pass = 8;
    FILE *file;
    char line[300];
    char existingID[20];
    int alreadyExists = 0;
    int max_num = 99999;
    printf("\n--- Add New Administrator ---\n");

    printf("Enter Admin ID (Example: A003): ");
    scanf("%s", id);

    if (strlen(id) > 6)
    {
        printf("Error: ID must be 'A' followed by no more than 5 digits (e.g., A12345).\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%s", username);
    while (1)
    {
        printf("Enter Password: ");
        scanf("%s", password);
        if (strlen(password) < least_pass)
        {
            printf("The Password Must Be At Leat 8 Leters\n");
            continue;
        }
        else
        {
            printf("your password is %s", password);
            break;
        }
    }

    getchar();
    printf("Enter Full Name: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = 0;

    file = fopen("users.txt", "r");

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%[^|]", existingID);
            if (strcmp(existingID, id) == 0)
            {
                alreadyExists = 1;
            }
        }
        fclose(file);
    }

    if (alreadyExists == 1)
    {
        printf("Error: That ID Already Exists. Please Use A Different ID.\n");
        return;
    }

    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("Error: Could Not Open Users.txt\n");
        return;
    }

    fprintf(file, "%s|%s|%s|Administrator|%s\n", id, username, password, name);
    fclose(file);

    printf("New Administrator Added Successfully!\n");
}

void remove_admin()
{
    char search_target[100];
    char line[300];
    char id[20], user[50], pass[50], role[30], name[100];
    int found = 0;
    int choice;

    printf("\n|======================================================|\n");
    printf("|                Current Administrators                |\n");
    printf("|======================================================|\n");

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("[ERROR] Could Not Open Users.txt Database.\n");
        return;
    }

    printf("%-10s | %-20s | %-20s\n", "ID", "Username", "Full Name");
    printf("--------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", id, user, pass, role, name) == 5)
        {
            if (strcmp(role, "Administrator") == 0)
            {
                printf("%-10s | %-20s | %-20s\n", id, user, name);
                found = 1;
            }
        }
    }
    fclose(file);

    if (!found)
    {
        printf("No Administrators Found In The System.\n");
        return;
    }

    printf("\n--------------------------------------------------------\n");
    printf("Enter Admin ID Or Full Name To Remove: ");
    getchar();
    fgets(search_target, 100, stdin);
    search_target[strcspn(search_target, "\n")] = 0;

    FILE *fOriginal = fopen("users.txt", "r");
    FILE *fTemp = fopen("temp_users.txt", "w");

    if (fOriginal == NULL || fTemp == NULL)
    {
        printf("[ERROR] File Error During Deletion Process.\n");
        if (fOriginal)
            fclose(fOriginal);
        return;
    }

    int deleted = 0;
    while (fgets(line, sizeof(line), fOriginal))
    {

        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", id, user, pass, role, name) == 5)
        {

            if (strcmp(role, "Administrator") == 0 &&
                (strcasecmp(id, search_target) == 0 || strcasecmp(name, search_target) == 0))
            {
                printf("\n[SUCCESS] Administrator %s (ID: %s) Has Been Removed.\n", name, id);
                deleted = 1;
                continue;
            }
        }

        fprintf(fTemp, "%s", line);
    }

    fclose(fOriginal);
    fclose(fTemp);

    if (deleted)
    {
        remove("users.txt");
        rename("temp_users.txt", "users.txt");
    }
    else
    {
        remove("temp_users.txt");
        printf("\n[ERROR] Target '%s' Not Found Or Is Not An Administrator.\n", search_target);
    }
}

void searchAdmin()
{
    char keyword[100];
    char line[300];
    char id[20], username[50], password[50], role[30], name[100];
    int found = 0;
    FILE *file;

    printf("\n--- Search Administrator ---\n");
    printf("Enter ID Or Name To Search: ");
    getchar();
    fgets(keyword, 100, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could Not Open Users.txt\n");
        return;
    }

    printf("\n%-10s %-20s %-20s\n", "ID", "Username", "Full Name");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               id, username, password, role, name);

        if (strcmp(role, "Administrator") != 0)
        {
            continue;
        }

        if (strstr(id, keyword) != NULL || strstr(name, keyword) != NULL)
        {
            printf("%-10s %-20s %-20s\n", id, username, name);
            found++;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("No Administrator Found.\n");
    }
    else
    {
        printf("--------------------------------------------------\n");
        printf("Found: %d Result(s)\n", found);
    }
}

void viewAllAdmins()
{
    char line[300];
    char id[20], username[50], password[50], role[30], name[100];
    int count = 0;
    FILE *file;

    printf("\n--- All Administrators ---\n");

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could Not Open Users.txt\n");
        return;
    }

    printf("\n%-10s %-20s %-20s\n", "ID", "Username", "Full Name");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               id, username, password, role, name);

        if (strcmp(role, "Administrator") == 0)
        {
            printf("%-10s %-20s %-20s\n", id, username, name);
            count++;
        }
    }

    fclose(file);
    printf("--------------------------------------------------\n");
    printf("Total: %d Administrator(s)\n", count);
}

void staffReport()
{
    char line[300];
    char id[20], username[50], password[50], role[30], name[100];
    char filter[100];
    int choice;
    int count = 0;
    FILE *file;

    printf("\n--- Staff Report ---\n");
    printf("1. Show All Staff\n");
    printf("2. Filter By Role\n");
    printf("3. Filter By Name\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    if (choice == 2 || choice == 3)
    {
        printf("Enter Keyword (Note: This is Case-Sensitive!): ");
        getchar();
        fgets(filter, 100, stdin);
        filter[strcspn(filter, "\n")] = 0;
    }

    printf("\n%-10s %-20s %-20s %-20s\n", "ID", "Username", "Role", "Full Name");
    printf("-----------------------------------------------------------------------\n");

    // ==========================================================
    //                       users.txt
    // ==========================================================
    FILE *fUsr = fopen("users.txt", "r");
    if (fUsr == NULL)
    {
        printf("[INFO] Users File Not Found\n");
    }
    else
    {
        char line[300], id[20], username[50], password[50], role[30], name[100];
        while (fgets(line, sizeof(line), fUsr))
        {
            if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", id, username, password, role, name) == 5)
            {
                if (strcmp(role, "Patient") == 0 || strcmp(role, "Director") == 0)
                    continue;

                if (choice == 1)
                {
                    printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                    count++;
                }
                else if (choice == 2 && strstr(role, filter) != NULL)
                {
                    printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                    count++;
                }
                else if (choice == 3 && strstr(name, filter) != NULL)
                {
                    printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                    count++;
                }
            }
        }
        fclose(fUsr);
    }

    // ==========================================================
    //                    doctors.txt
    // ==========================================================
    FILE *fDoc = fopen("doctors.txt", "r");
    if (fDoc == NULL)
    {
        printf("[INFO] Doctors File Not Found\n");
    }
    else
    {
        struct doctors d;
        while (fscanf(fDoc, "%19s %49s %d %49s", d.doctor_id, d.doctor_name, &d.doctor_age, d.doctor_speciallization) == 4)
        {
            char id[20];
            strcpy(id, d.doctor_id);
            char name[100];
            strcpy(name, d.doctor_name);
            char role[30] = "Doctor";
            char username[50] = "N/A";

            if (choice == 1)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
            else if (choice == 2 && strstr(role, filter) != NULL)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
            else if (choice == 3 && strstr(name, filter) != NULL)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
        }
        fclose(fDoc);
    }

    // ==========================================================
    //                       nurse.txt
    // ==========================================================
    FILE *fNur = fopen("nurse.txt", "r");
    if (fNur == NULL)
    {
        printf("[INFO] Nurses File Not Found\n");
    }
    else
    {
        struct nurse n;
        while (fscanf(fNur, "%19s %49s %d %49s", n.nurse_id, n.nurse_name, &n.nurse_age, n.nurse_assigned_ward) == 4)
        {
            char id[20];
            strcpy(id, n.nurse_id);
            char name[100];
            strcpy(name, n.nurse_name);
            char role[30] = "Nurse";
            char username[50] = "N/A";

            if (choice == 1)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
            else if (choice == 2 && strstr(role, filter) != NULL)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
            else if (choice == 3 && strstr(name, filter) != NULL)
            {
                printf("%-10s %-20s %-20s %-20s\n", id, username, role, name);
                count++;
            }
        }
        fclose(fNur);
    }

    printf("-----------------------------------------------------------------------\n");
    printf("Total Shown: %d\n", count);
}

void appointmentTrendReport()
{
    char line[300];
    char apptID[20], patID[20], docID[20];
    char date[20], month[20], status[20];
    char filterMonth[20];
    char currentMonth[20];
    int choice;
    int scheduled, rescheduled, cancelled, total;
    FILE *file;

    strcpy(currentMonth, "");
    scheduled = 0;
    rescheduled = 0;
    cancelled = 0;
    total = 0;

    printf("\n--- Appointment Trend Report ---\n");
    printf("1. View All Months\n");
    printf("2. Filter By Month\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    if (choice == 2)
    {
        printf("Enter Month (Example: March): ");
        getchar();
        fgets(filterMonth, 20, stdin);
        filterMonth[strcspn(filterMonth, "\n")] = 0;
    }

    file = fopen("appointments.txt", "r");

    if (file == NULL)
    {
        printf("Appointments.txt Not Found Yet.\n");
        printf("This File Will Be Created By The Patient Module.\n");
        return;
    }

    printf("\n%-12s %-12s %-14s %-12s %-8s\n",
           "Month", "Scheduled", "Rescheduled", "Cancelled", "Total");
    printf("-------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               apptID, patID, docID, date, month, status);

        if (choice == 2 && strcmp(month, filterMonth) != 0)
        {
            continue;
        }

        if (strcmp(currentMonth, month) != 0)
        {
            if (strlen(currentMonth) > 0)
            {
                printf("%-12s %-12d %-14d %-12d %-8d\n",
                       currentMonth, scheduled, rescheduled, cancelled,
                       scheduled + rescheduled + cancelled);
            }
            strcpy(currentMonth, month);
            scheduled = 0;
            rescheduled = 0;
            cancelled = 0;
        }

        if (strcmp(status, "scheduled") == 0)
        {
            scheduled++;
        }
        else if (strcmp(status, "rescheduled") == 0)
        {
            rescheduled++;
        }
        else if (strcmp(status, "cancelled") == 0)
        {
            cancelled++;
        }

        total++;
    }

    if (strlen(currentMonth) > 0)
    {
        printf("%-12s %-12d %-14d %-12d %-8d\n",
               currentMonth, scheduled, rescheduled, cancelled,
               scheduled + rescheduled + cancelled);
    }

    fclose(file);
    printf("-------------------------------------------------------------\n");
    printf("Grand Total: %d Appointment(s)\n", total);
}
