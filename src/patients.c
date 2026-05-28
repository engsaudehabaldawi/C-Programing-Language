#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"
int main_patient_mnue(void)
{
    struct Patient p;
    char userID[20];
    int choise_p;

    while (1)
    {
        int found = 0;

        printf("\n====================================\n");
        printf("   Hospital Management System\n");
        printf("====================================\n");
        printf("1. Sign In By ID\n2. Log Out\nChoice: ");

        if (scanf("%d", &choise_p) != 1)
        {
            printf("\n[ERROR] Invalid Input! Numbers Only.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (choise_p == 1)
        {
            printf("Enter Your Patient ID: ");
            scanf("%19s", userID);

            FILE *file = fopen("data/patients.txt", "r");

            if (file == NULL)
            {
                printf("\nError! Database File Not Found.\n");
                return 0;
            }

            while (fscanf(file, " %19s %49s %d %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease) == 4)
            {
                if (strcmp(userID, p.patient_id) == 0)
                {
                    found = 1;
                    break;
                }
            }

            fclose(file);

            if (found == 1)
            {
                printf("\n--- Log In Successful! Welcome %s ---\n", p.patient_name);
                patientMenu(userID);
            }
            else
            {
                printf("\n[ERROR] User [ID]: %s Not Found!\n", userID);
            }
        }
        else if (choise_p == 2)
        {
            printf("\nLogging Out...\n");
            return 0;
        }
        else
        {
            printf("\n[ERROR] Invalid Choice. Please Select 1 Or 2.\n");
        }
    }
    return 0;
}

void patientMenu(char userID[])
{
    int choice;

    while (1)
    {
        printf("\n==============================");
        printf("\n   PATIENT MODULE - %s", userID);
        printf("\n==============================");
        printf("\n1. Book Appointment");
        printf("\n2. View My Appointments");
        printf("\n3. Reschedule Appointment");
        printf("\n4. Cancel Appointment");
        printf("\n5. View Medical Records & Billing");
        printf("\n6. Logout");
        printf("\nChoose An Option: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
            {
            }
            printf("\n[ERROR] Invalid Input! Numbers Only.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            bookAppointment(userID);
            break;
        case 2:
            viewAppointments(userID);
            break;
        case 3:
            updateAppointment(userID, 1);
            break;
        case 4:
            updateAppointment(userID, 2);
            break;
        case 5:
            viewMedicalInfo(userID);
            break;
        case 6:
            printf("\nLogging Out...\n");
            return;
        default:
            printf("\n[ERROR] Invalid Choice!\n");
        }
    }
}

void bookAppointment(char userID[])
{
    struct Appointment newApp;
    int i;
    char dummy_id[20];

    strcpy(newApp.patientID, userID);

    printf("\n|======================================================|\n");
    printf("|                  AVAILABLE DOCTORS                   |\n");
    printf("|======================================================|\n");

    FILE *fDoc = fopen("data/doctors.txt", "r");

    if (fDoc != NULL)
    {
        char d_name[50], d_spec[50] , d_pass[50];
        int d_age;

        printf(" | %-20s | %-20s\n", "Name", "Specialization");
        printf("------------------------------------------------------\n");

        // We MUST read 4 items (ID, Name, Age, Spec) even if we only print 2
        while (fscanf(fDoc, "%19s %49s %d %49s %49s", dummy_id, d_name, &d_age, d_spec , d_pass)  == 5)
        {
            printf(" | %-20s | %-20s\n", d_name, d_spec);
        }

        fclose(fDoc);
        printf("------------------------------------------------------\n");
    }
    else
    {
        printf("No Doctors Currently In The Database.\n");
        return;
    }

    int valid_doctor = 0;

    while (valid_doctor == 0)
    {
        printf("\nEnter Doctor Name (Use_Underscores) Or '0' To Cancel: ");
        scanf(" %49s", newApp.doctorName);

        if (strcmp(newApp.doctorName, "0") == 0)
        {
            printf("\nCanceling Appointment Booking...\n");
            return;
        }

        FILE *fCheck = fopen("data/doctors.txt", "r");

        if (fCheck != NULL)
        {
            char c_id[20], c_name[50], c_spec[50] , c_pass[50];
            int c_age;

            while (fscanf(fCheck, "%19s %49s %d %49s %49s", c_id, c_name, &c_age, c_spec , c_pass ) == 5)
            {
                if (strcmp(c_name, newApp.doctorName) == 0)
                {
                    valid_doctor = 1;
                    break;
                }
            }

            fclose(fCheck);
        }

        if (valid_doctor == 0)
        {
            printf("\n[ERROR] Doctor '%s' Not Found! Please Check The Spelling From The List Above.\n", newApp.doctorName);
        }
    }

    printf("\n|======================================================|\n");
    printf("|                  SELECT A DATE                       |\n");
    printf("|======================================================|\n");

    time_t t = time(NULL);
    struct tm *tm_info;
    char dateOptions[10][15];
    int dateChoice;

    for (i = 0; i < 10; i++)
    {
        tm_info = localtime(&t);
        strftime(dateOptions[i], 15, "%d/%m/%Y", tm_info);
        printf("%2d. %s\n", i + 1, dateOptions[i]);
        t += (24 * 60 * 60);
    }

    printf("11. Enter Date Manually\n");

    while (1)
    {
        printf("Choice: ");

        if (scanf("%d", &dateChoice) != 1)
        {
            printf("\n[ERROR] Invalid Input. Numbers Only.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (dateChoice >= 1 && dateChoice <= 10)
        {
            strcpy(newApp.date, dateOptions[dateChoice - 1]);
            break;
        }
        else if (dateChoice == 11)
        {
            int test_d, test_m, test_y;
            printf("Enter Date (DD/MM/YYYY): ");
            scanf(" %14s", newApp.date);

            if (sscanf(newApp.date, "%d/%d/%d", &test_d, &test_m, &test_y) != 3)
            {
                printf("\n[ERROR] Invalid Format! You Must Use DD/MM/YYYY (E.g., 25/04/2026).\n");
                continue;
            }
            break;
        }
        else
        {
            printf("\n[ERROR] Please Select A Number Between 1 And 11.\n");
        }
    }

    char ch;
    printf("\nIs This An Emergency? (Y/N): ");
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y')
    {
        strcpy(newApp.priority, "Emergency");
        strcpy(newApp.time, "08:00");
        printf("\n!!! Emergency Case !!! Auto-assigned Time: 08:00\n");
    }
    else
    {
        strcpy(newApp.priority, "Normal");
        int timeChoice;

        printf("\n|======================================================|\n");
        printf("|                  AVAILABLE TIME SLOTS                |\n");
        printf("|======================================================|\n");
        printf("1. 09:00 AM\n2. 10:00 AM\n3. 11:00 AM\n4. 01:00 PM (13:00)\n5. 02:00 PM (14:00)\n6. 03:00 PM (15:00)\n");

        while (1)
        {
            printf("Choice: ");

            if (scanf("%d", &timeChoice) != 1)
            {
                printf("\n[ERROR] Invalid Input. Numbers Only.\n");
                while (getchar() != '\n')
                {
                }
                continue;
            }

            if (timeChoice == 1)
            {
                strcpy(newApp.time, "09:00");
                break;
            }
            else if (timeChoice == 2)
            {
                strcpy(newApp.time, "10:00");
                break;
            }
            else if (timeChoice == 3)
            {
                strcpy(newApp.time, "11:00");
                break;
            }
            else if (timeChoice == 4)
            {
                strcpy(newApp.time, "13:00");
                break;
            }
            else if (timeChoice == 5)
            {
                strcpy(newApp.time, "14:00");
                break;
            }
            else if (timeChoice == 6)
            {
                strcpy(newApp.time, "15:00");
                break;
            }
            else
            {
                printf("\n[ERROR] Please Select A Time Slot Between 1 And 6.\n");
            }
        }
    }

    strcpy(newApp.status, "Booked");

    FILE *fp = fopen("data/appointments.txt", "a");

    if (!fp)
    {
        printf("\n[ERROR] Could Not Open Appointments.txt File.\n");
        return;
    }

    fprintf(fp, "%s|%s|%s|%s|%s|%s\n",
            newApp.patientID,
            newApp.doctorName,
            newApp.date,
            newApp.time,
            newApp.status,
            newApp.priority);

    fclose(fp);

    printf("\n<<< Appointment Booked Successfully For %s At %s >>>\n", newApp.date, newApp.time);
}

void viewAppointments(char userID[])
{
    struct Appointment list[100], app;
    int count = 0;

    FILE *fp = fopen("data/appointments.txt", "r");

    if (!fp)
    {
        printf("\n[INFO] No Records Found. You Have No Appointments.\n");
        return;
    }

    while (fscanf(fp, " %19[^|]|%49[^|]|%19[^|]|%9[^|]|%19[^|]|%19[^\n]\n",
                  app.patientID, app.doctorName, app.date,
                  app.time, app.status, app.priority) != EOF)
    {
        if (strcmp(app.patientID, userID) == 0)
        {
            list[count++] = app;
        }
    }

    fclose(fp);

    if (count == 0)
    {
        printf("\n[INFO] You Currently Have No Appointments Booked.\n");
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int d1 = 0, m1 = 0, y1 = 0;
            int d2 = 0, m2 = 0, y2 = 0;

            int valid1 = sscanf(list[i].date, "%d/%d/%d", &d1, &m1, &y1);
            int valid2 = sscanf(list[j].date, "%d/%d/%d", &d2, &m2, &y2);

            int should_swap = 0;

            if (valid1 == 3 && valid2 == 3)
            {
                if (y1 > y2)
                {
                    should_swap = 1;
                }
                else if (y1 == y2 && m1 > m2)
                {
                    should_swap = 1;
                }
                else if (y1 == y2 && m1 == m2 && d1 > d2)
                {
                    should_swap = 1;
                }
            }

            if (should_swap == 1)
            {
                struct Appointment temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    printf("\n|==============================================================================|");
    printf("\n|                               MY APPOINTMENTS                                |");
    printf("\n|==============================================================================|");
    printf("\n%-15s %-20s %-12s %-8s %-12s %-10s",
           "Patient ID", "Doctor", "Date", "Time", "Status", "Priority");
    printf("\n--------------------------------------------------------------------------------");

    for (int i = 0; i < count; i++)
    {
        printf("\n%-15s %-20s %-12s %-8s %-12s %-10s",
               list[i].patientID,
               list[i].doctorName,
               list[i].date,
               list[i].time,
               list[i].status,
               list[i].priority);
    }
    printf("\n--------------------------------------------------------------------------------\n");
}

void updateAppointment(char userID[], int mode)
{
    struct Appointment list[100], app;
    int count = 0;

    FILE *fp = fopen("data/appointments.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (!fp || !temp)
    {
        printf("\n[ERROR] File Error!\n");
        return;
    }

    while (fscanf(fp, " %19[^|]|%49[^|]|%19[^|]|%9[^|]|%19[^|]|%19[^\n]\n",
                  app.patientID, app.doctorName, app.date,
                  app.time, app.status, app.priority) != EOF)
    {
        list[count++] = app;
    }
    fclose(fp);

    int indices[100], idx_count = 0;

    printf("\n|======================================================|\n");
    printf("|                  YOUR APPOINTMENTS                   |\n");
    printf("|======================================================|\n");

    for (int i = 0; i < count; i++)
    {
        if (strcmp(list[i].patientID, userID) == 0)
        {
            idx_count++;
            indices[idx_count - 1] = i;
            printf("%d. %-15s | Date: %-10s | Time: %-5s | Status: [%s]\n",
                   idx_count, list[i].doctorName, list[i].date, list[i].time, list[i].status);
        }
    }

    if (idx_count == 0)
    {
        printf("\n[INFO] No Appointments Found.\n");
        fclose(temp);
        remove("data/temp.txt");
        return;
    }

    int choice;
    printf("\nSelect Appointment Number To %s (Or 0 To Exit): ", (mode == 1 ? "Reschedule" : "Cancel"));

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
        {
        }
        printf("\n[ERROR] Invalid Input.\n");
        fclose(temp);
        remove("data/temp.txt");
        return;
    }

    if (choice == 0)
    {
        printf("\nAction Cancelled.\n");
        fclose(temp);
        remove("data/temp.txt");
        return;
    }

    if (choice < 1 || choice > idx_count)
    {
        printf("\n[ERROR] Invalid Selection.\n");
        fclose(temp);
        remove("data/temp.txt");
        return;
    }

    int sel = indices[choice - 1];

    if (mode == 1)
    {
        int i, dateChoice, timeChoice;
        time_t t = time(NULL);
        struct tm *tm_info;
        char dateOptions[10][15];

        printf("\n|======================================================|\n");
        printf("|               SELECT A NEW DATE                      |\n");
        printf("|======================================================|\n");

        for (i = 0; i < 10; i++)
        {
            tm_info = localtime(&t);
            strftime(dateOptions[i], 15, "%d/%m/%Y", tm_info);
            printf("%2d. %s\n", i + 1, dateOptions[i]);
            t += (24 * 60 * 60);
        }

        printf("11. Enter Date Manually\n");

        while (1)
        {
            printf("Choice: ");

            if (scanf("%d", &dateChoice) != 1)
            {
                printf("\n[ERROR] Invalid Input. Numbers Only.\n");
                while (getchar() != '\n')
                {
                }
                continue;
            }

            if (dateChoice >= 1 && dateChoice <= 10)
            {
                strcpy(list[sel].date, dateOptions[dateChoice - 1]);
                break;
            }
            else if (dateChoice == 11)
            {
                int test_d, test_m, test_y;
                printf("Enter Date (DD/MM/YYYY): ");
                scanf(" %14s", list[sel].date);

                if (sscanf(list[sel].date, "%d/%d/%d", &test_d, &test_m, &test_y) != 3)
                {
                    printf("\n[ERROR] Invalid Format! You Must Use DD/MM/YYYY.\n");
                    continue;
                }
                break;
            }
            else
            {
                printf("\n[ERROR] Please Select A Number Between 1 And 11.\n");
            }
        }

        printf("\n|======================================================|\n");
        printf("|               AVAILABLE NEW TIME SLOTS               |\n");
        printf("|======================================================|\n");
        printf("1. 09:00 AM\n2. 10:00 AM\n3. 11:00 AM\n4. 01:00 PM (13:00)\n5. 02:00 PM (14:00)\n6. 03:00 PM (15:00)\n");

        while (1)
        {
            printf("Choice: ");

            if (scanf("%d", &timeChoice) != 1)
            {
                printf("\n[ERROR] Invalid Input. Numbers Only.\n");
                while (getchar() != '\n')
                {
                }
                continue;
            }

            if (timeChoice == 1)
            {
                strcpy(list[sel].time, "09:00");
                break;
            }
            else if (timeChoice == 2)
            {
                strcpy(list[sel].time, "10:00");
                break;
            }
            else if (timeChoice == 3)
            {
                strcpy(list[sel].time, "11:00");
                break;
            }
            else if (timeChoice == 4)
            {
                strcpy(list[sel].time, "13:00");
                break;
            }
            else if (timeChoice == 5)
            {
                strcpy(list[sel].time, "14:00");
                break;
            }
            else if (timeChoice == 6)
            {
                strcpy(list[sel].time, "15:00");
                break;
            }
            else
            {
                printf("\n[ERROR] Please Select A Time Slot Between 1 And 6.\n");
            }
        }

        strcpy(list[sel].status, "Rescheduled");
    }
    else
    {
        strcpy(list[sel].status, "Cancelled");
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(temp, "%s|%s|%s|%s|%s|%s\n",
                list[i].patientID,
                list[i].doctorName,
                list[i].date,
                list[i].time,
                list[i].status,
                list[i].priority);
    }

    fclose(temp);
    remove("data/appointments.txt");
    rename("data/temp.txt", "data/appointments.txt");

    printf("\n<<< Appointment %s Successfully! >>>\n", (mode == 1 ? "Rescheduled" : "Cancelled"));
}

void viewMedicalInfo(char userID[])
{
    char line[300];
    char p_id[20], d_id[20], diag[50], med_name[50], extra[50], inv_med[50];
    int inv_stock;
    float inv_price;
    float total_medicine_cost = 0.0;
    float consultation_fee = 50.00;

    userID[strcspn(userID, "\r\n")] = 0;

    printf("\n|======================================================|\n");
    printf("|             MEDICAL RECORD & BILLING: %-14s |\n", userID);
    printf("|======================================================|\n\n");

    FILE *fPres = fopen("data/PatientsPrescription.txt", "r");
    if (fPres == NULL)
        fPres = fopen("data/PatientsPrescription", "r");

    if (fPres == NULL)
    {
        printf("[INFO] No medical history or prescriptions found.\n");
        return;
    }

    printf("--- Prescribed Medicines ---\n");
    int items_found = 0;

    while (fgets(line, sizeof(line), fPres))
    {

        if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^|] | %[^\n]", p_id, d_id, diag, med_name, extra) >= 4)
        {
            p_id[strcspn(p_id, "\r\n")] = 0;
            med_name[strcspn(med_name, "\r\n")] = 0;

            if (strcasecmp(p_id, userID) == 0)
            {
                items_found = 1;
                float item_price = 0.0;
                int qty = 1;

                FILE *fInv = fopen("data/supplies.txt", "r");
                if (fInv == NULL)
                    fInv = fopen("data/supplies", "r");

                if (fInv != NULL)
                {
                    char inv_line[150];
                    while (fgets(inv_line, sizeof(inv_line), fInv))
                    {
                        // Added spaces around these pipes too!
                        if (sscanf(inv_line, " %[^|] | %d | %f", inv_med, &inv_stock, &inv_price) >= 3)
                        {
                            inv_med[strcspn(inv_med, "\r\n")] = 0;

                            if (strcasecmp(inv_med, med_name) == 0)
                            {
                                item_price = inv_price;
                                break;
                            }
                        }
                    }
                    fclose(fInv);
                }
                else
                {

                    printf("[WARNING] Could not open 'supplies.txt'! Prices will show as 0.00.\n");
                }

                float line_total = item_price * qty;
                total_medicine_cost += line_total;

                printf("- %s (x%d) : %.2f MYR\n", med_name, qty, line_total);
            }
        }
    }
    fclose(fPres);

    if (items_found == 0)
    {
        printf("No medications prescribed.\n");
    }

    printf("\n--- BILLING SUMMARY ---\n");
    printf("Consultation Fee : %.2f MYR\n", consultation_fee);
    printf("Pharmacy Total   : %.2f MYR\n", total_medicine_cost);
    printf("-------------------------------\n");
    printf("TOTAL AMOUNT DUE : %.2f MYR\n", consultation_fee + total_medicine_cost);
}


