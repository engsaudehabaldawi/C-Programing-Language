#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"
#define MAX 200
void doc_menu(char dr_id[], char dr_name[])
{

    int choice;
    int found = 0;

    while (1)
    {
        printf("\n|======================================================|\n");
        printf("|                DOCTOR MENU (Dr. %s )                 \n", dr_name);
        printf("|======================================================|\n");
        printf("1. View My Appointments (Schedule)\n");
        printf("2. View Patient File\n");
        printf("3. Update Patient Diagnosis\n");
        printf("4. Write Prescription\n");
        printf("5. View My Prescription History\n");
        printf("6. Logout\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Invalid Input.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (choice == 1)
        {
            show_schedule(dr_name);
        }
        else if (choice == 2)
        {
            find_patient();
        }
        else if (choice == 3)
        {
            change_status();
        }
        else if (choice == 4)
        {
            write_meds(dr_id);
        }
        else if (choice == 5)
        {
            show_history(dr_id);
        }
        else if (choice == 6)
        {
            printf("\nLogging Out...\n");
            break;
        }
        else
        {
            printf("\n[ERROR] Invalid Choice!\n");
        }
    }
}

void show_schedule(char dr_name[])
{
    struct Appointment app;
    int found = 0;

    FILE *f = fopen("data/appointments.txt", "r");

    if (f == NULL)
    {
        printf("\n[INFO] No Appointments Have Been Booked In The System Yet.\n");
        return;
    }

    printf("\n|======================================================================|\n");
    printf("|                        MY APPOINTMENT SCHEDULE                       |\n");
    printf("|======================================================================|\n");
    printf("%-15s | %-12s | %-8s | %-15s | %-10s\n", "Patient ID", "Date", "Time", "Status", "Priority");
    printf("------------------------------------------------------------------------\n");

    while (fscanf(f, " %19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^|]|%19[^\n]\n",
                  app.patientID, app.doctorName, app.date, app.time, app.status, app.priority) == 6)
    {
        if (strcmp(app.doctorName, dr_name) == 0)
        {
            printf("%-15s | %-12s | %-8s | %-15s | %-10s\n",
                   app.patientID, app.date, app.time, app.status, app.priority);
            found = 1;
        }
    }

    fclose(f);

    if (!found)
    {
        printf("You Currently Have No Appointments Booked.\n");
    }
    printf("------------------------------------------------------------------------\n");
}

void find_patient()
{
    struct Patient p;
    char target[20];
    int found = 0;

    printf("\nEnter Patient ID: ");
    scanf("%19s", target);

    FILE *f = fopen("data/patients.txt", "r");

    if (f == NULL)
    {
        printf("\n[INFO] Patient Database Is Currently Empty.\n");
        return;
    }

    printf("\n--- Patient Record ---\n");

    while (fscanf(f, "%19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease , p.ppasword) == 5)
    {
        if (strcmp(p.patient_id, target) == 0)
        {
            printf("ID: %s\nName: %s\nAge: %d\nDiagnosis/Disease: %s\n",
                   p.patient_id, p.patient_name, p.patient_age, p.patient_disease);
            found = 1;
            break;
        }
    }

    fclose(f);

    if (!found)
    {
        printf("\n[ERROR] Patient ID '%s' Not Found.\n", target);
    }
}

void change_status()
{
    struct Patient p;
    char target[20], new_disease[50];
    int found = 0;

    FILE *f = fopen("data/patients.txt", "r");
    FILE *temp = fopen("data/temp_pat.txt", "w");

    if (f == NULL || temp == NULL)
    {
        printf("\n[ERROR] Could Not Open Patient Database.\n");
        if (f)
            fclose(f);
        if (temp)
            fclose(temp);
        return;
    }

    printf("\nEnter Patient ID To Update: ");
    scanf("%19s", target);

    while (fscanf(f, "%19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease , p.ppasword) == 5)
    {
        if (strcmp(p.patient_id, target) == 0)
        {
            printf("Current Diagnosis: %s\n", p.patient_disease);
            printf("Enter New Diagnosis (Use_Underscores): ");
            scanf("%49s", new_disease);
            strcpy(p.patient_disease, new_disease);
            found = 1;
        }

        fprintf(temp, "%s %s %d %s %s\n", p.patient_id, p.patient_name, p.patient_age, p.patient_disease , p.ppasword);
    }

    fclose(f);
    fclose(temp);

    if (found)
    {
        remove("data/patients.txt");
        rename("data/temp_pat.txt", "data/patients.txt");
        printf("\n[SUCCESS] Patient Diagnosis Updated Successfully!\n");
    }
    else
    {
        remove("data/temp_pat.txt");
        printf("\n[ERROR] Patient ID '%s' Not Found.\n", target);
    }
}

void write_meds(char dr_id[])
{
    FILE *f = fopen("data/PatientsPrescription.txt", "a");

    if (f == NULL)
    {
        printf("\n[ERROR] Could Not Open Prescription File.\n");
        return;
    }

    char pid[20], illness[100], meds[100], note[100];

    printf("\nEnter Patient ID: ");
    scanf("%19s", pid);

    printf("Enter Disease/Illness (Use_Underscores): ");
    scanf("%99s", illness);

    printf("Enter Medicine (Use_Underscores): ");
    scanf("%99s", meds);

    printf("Enter Note (Use_Underscores): ");
    scanf("%99s", note);

    fprintf(f, "%s|%s|%s|%s|%s\n", pid, dr_id, illness, meds, note);
    fclose(f);

    printf("\n[SUCCESS] Prescription Saved Successfully!\n");
}

void show_history(char dr_id[])
{
    FILE *f = fopen("data/PatientsPrescription.txt", "r");

    if (f == NULL)
    {
        printf("\n[INFO] No Prescriptions Have Been Written Yet.\n");
        return;
    }

    char pid[20], did[20], illness[100], meds[100], note[100];
    int found = 0;

    printf("\n|======================================================================|\n");
    printf("|                        MY PRESCRIPTION HISTORY                       |\n");
    printf("|======================================================================|\n");
    printf("%-15s | %-20s | %-20s\n", "Patient ID", "Illness", "Medicine");
    printf("------------------------------------------------------------------------\n");

    while (fscanf(f, " %19[^|]|%19[^|]|%99[^|]|%99[^|]|%99[^\n]\n", pid, did, illness, meds, note) == 5)
    {
        if (strcmp(did, dr_id) == 0)
        {
            printf("%-15s | %-20s | %-20s\n", pid, illness, meds);
            found = 1;
        }
    }

    fclose(f);

    if (!found)
    {
        printf("You Have Not Written Any Prescriptions Yet.\n");
    }

    printf("------------------------------------------------------------------------\n");
}