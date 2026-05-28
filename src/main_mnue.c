#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"


void display_hospital_info()
{
    printf("\n|======================================================================|\n");
    printf("|                    SAASS HOSPITAL INFORMATION                        |\n");
    printf("|======================================================================|\n");
    printf("| Location: 123 Tech Avenue, Silicon District, Cyber City              |\n");
    printf("|                                                                      |\n");
    printf("| Working Hours:                                                       |\n");
    printf("|   - Emergency Room:       24/7 (Always Open)                         |\n");
    printf("|   - Outpatient Clinics:   Monday - Friday, 08:00 AM - 08:00 PM       |\n");
    printf("|   - Administration:       Monday - Friday, 09:00 AM - 05:00 PM       |\n");
    printf("|                                                                      |\n");
    printf("| Contact: +1-800-SAASS-CARE | Email: Contact@Saasshospital.com        |\n");
    printf("|======================================================================|\n");

    printf("\nPress Enter To Return To The Main Menu...");
    getchar();
    while (getchar() != '\n')
    {
    }
}

// ==============================================================================
//                              SMART UNIFIED LOGIN
// ==============================================================================

void unified_login()
{
    char login_id[50];
    char log_in_pass[50];

    // Clean the buffer from the main menu selection
    while (getchar() != '\n')
        ;

    printf("\n|======================================================|\n");
    printf("|                  UNIFIED LOGIN PORTAL                |\n");
    printf("|======================================================|\n");
    printf("Enter Your ID (Examples: P1, D12, N3, Admin) Or 0 to Return: ");
    fflush(stdout);
    scanf("%49s", login_id);

    // Clean the ID of any invisible characters immediately
    login_id[strcspn(login_id, "\r\n ")] = 0;

    // 1. EXIT CHECK
    if (strcmp(login_id, "0") == 0)
    {
        printf("\nReturning to Main Menu...\n");
        return;
    }

    // 2. THE ADMIN INTERCEPTOR
    // If they typed 'admin' or just 'A', skip the password and go straight to Admin
    if (strcasecmp(login_id, "admin") == 0 || login_id[0] == 'a' || login_id[0] == 'A')
    {
        printf("\n[INFO] Redirecting to Secure Administration Portal...\n");
        main_admistration_mnue();
        return; // Exits the Unified Portal entirely
    }

    // 3. IF NOT ADMIN, ASK FOR PASSWORD
    printf("Enter Your Password: ");
    fflush(stdout);
    scanf(" %49s", log_in_pass);

    // Clean the password of invisible characters
    log_in_pass[strcspn(log_in_pass, "\r\n ")] = 0;

    // Standardize the first letter to Uppercase for P, D, and N checks
    login_id[0] = (char)toupper(login_id[0]);

    // ==========================================
    // PATIENT LOGIN
    // ==========================================
    if (login_id[0] == 'P')
    {
        struct Patient p;
        int found = 0;
        FILE *f = fopen("data/patients.txt", "r");
        if (f == NULL)
        {
            printf("\n[ERROR] Patient database not found!\n");
            return;
        }

        while (fscanf(f, "%19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease, p.ppasword) == 5)
        {
            p.patient_id[strcspn(p.patient_id, "\r\n ")] = 0;
            p.ppasword[strcspn(p.ppasword, "\r\n ")] = 0;

            if (strcasecmp(login_id, p.patient_id) == 0 && strcmp(log_in_pass, p.ppasword) == 0)
            {
                found = 1;
                printf("\n--- Login Successful! Welcome %s ---\n", p.patient_name);
                fclose(f);
                patientMenu(login_id);
                return;
            }
        }
        fclose(f);
        if (!found)
        {
            printf("\n[ERROR] Patient ID '%s' Not Found! Or Wrong Password\n", login_id);
        }
    }

    // ==========================================
    // DOCTOR LOGIN
    // ==========================================
    else if (login_id[0] == 'D')
    {
        int found = 0;
        FILE *f = fopen("data/doctors.txt", "r");

        if (f != NULL)
        {
            char t_id[20], t_name[50], t_spec[50], t_pasword[50];
            int t_age;

            while (fscanf(f, "%19s %49s %d %49s %49s", t_id, t_name, &t_age, t_spec, t_pasword) == 5)
            {
                t_id[strcspn(t_id, "\r\n ")] = 0;
                t_pasword[strcspn(t_pasword, "\r\n ")] = 0;

                if (strcasecmp(login_id, t_id) == 0 && strcmp(log_in_pass, t_pasword) == 0)
                {
                    found = 1;
                    printf("\n--- Login Successful! Welcome Dr. %s ---\n", t_name);
                    fclose(f);
                    doc_menu(t_id, t_name);
                    return;
                }
            }
            fclose(f);
        }
        if (!found)
        {
            printf("\n[ERROR] Doctor ID '%s' Not Found! Or Wrong Password\n", login_id);
        }
    }

    // ==========================================
    // NURSE LOGIN
    // ==========================================
    else if (login_id[0] == 'N')
    {
        int found = 0;
        FILE *f = fopen("data/nurse.txt", "r");

        if (f != NULL)
        {
            char t_id[20], t_name[50], t_ward[50], t_pass[50];
            int t_age;

            while (fscanf(f, "%19s %49s %d %49s %49s", t_id, t_name, &t_age, t_ward, t_pass) == 5)
            {
                t_id[strcspn(t_id, "\r\n ")] = 0;
                t_pass[strcspn(t_pass, "\r\n ")] = 0;

                if (strcasecmp(login_id, t_id) == 0 && strcmp(log_in_pass, t_pass) == 0)
                {
                    found = 1;
                    printf("\n--- Login Successful! Welcome %s ---\n", t_name);
                    fclose(f);
                    nurse_menu(t_id, t_name);
                    return;
                }
            }
            fclose(f);
        }
        if (!found)
        {
            printf("\n[ERROR] Nurse ID '%s' Not Found! Or Wrong Password\n", login_id);
        }
    }

    // ==========================================
    // INVALID FORMAT
    // ==========================================
    else
    {
        printf("\n[ERROR] System Could Not Recognize ID Format.\n");
        printf("IDs Must Start With P (Patient), D (Doctor), N (Nurse), Or Admin.\n");
    }
}




void submit_system_report(void)
{

    char reporter_id[20], report_pass[50];
    int account_found = 0;
    char reporter_name[100] = "Unknown";

    printf("\n|======================================================|\n");
    printf("|                REPORT AN ISSUE                       |\n");
    printf("|======================================================|\n");

    printf("Enter your ID to verify your account Or Prss 0 ro Retun (e.g., P1, D12): \n");
    scanf("%19s", reporter_id);
    if (strcmp(reporter_id, "0") == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }

    printf("enetr your password Or Prss 0 ro Retun: ");
    scanf("%49s", report_pass);
    reporter_id[strcspn(reporter_id, "\r\n ")] = 0;
    report_pass[strcspn(report_pass, "\r\n ")] = 0;

    if (strcmp(report_pass, "0") == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }

    FILE *fUsr = fopen("data/users.txt", "r");
    if (fUsr != NULL)
    {
        char line[300], t_id[20], t_user[50], t_pass[50], t_role[30], t_name[100];
        while (fgets(line, sizeof(line), fUsr))
        {
            if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^|] | %[^\n]", t_id, t_user, t_pass, t_role, t_name) >= 4)
            {
                t_id[strcspn(t_id, "\r\n ")] = 0;
                t_name[strcspn(t_name, "\r\n")] = 0;

                if (strcasecmp(t_id, reporter_id) == 0)
                {
                    account_found = 1;
                    strcpy(reporter_name, t_name);
                    break;
                }
            }
        }
        fclose(fUsr);
    }

    if (!account_found)
    {
        FILE *fPat = fopen("data/patients.txt", "r");
        if (fPat != NULL)
        {
            char p_id[20], p_name[50], p_extra[50], p_pass[50];
            int p_age;

            while (fscanf(fPat, "%19s %49s %d %49s %49s", p_id, p_name, &p_age, p_extra, p_pass) == 5)
            {
                p_id[strcspn(p_id, "\r\n ")] = 0;
                p_pass[strcspn(p_pass, "\r\n ")] = 0;
                if (strcasecmp(p_id, reporter_id) == 0 && strcasecmp(p_pass, report_pass) == 0)
                {
                    account_found = 1;
                    strcpy(reporter_name, p_name);
                    strcpy(report_pass, p_pass);
                    break;
                }
            }
            fclose(fPat);
        }
    }

    if (!account_found)
    {
        FILE *fDoc = fopen("data/doctors.txt", "r");
        if (fDoc != NULL)
        {
            char d_id[20], d_name[50], d_spec[50], d_pass[50];
            int d_age;
            while (fscanf(fDoc, "%19s %49s %d %49s %49s", d_id, d_name, &d_age, d_spec, d_pass) == 5)
            {
                d_id[strcspn(d_id, "\r\n ")] = 0;
                if (strcasecmp(d_id, reporter_id) == 0 && strcasecmp(d_pass, report_pass) == 0)
                {
                    account_found = 1;
                    strcpy(reporter_name, d_name);
                    strcpy(report_pass, d_pass);
                    break;
                }
            }
            fclose(fDoc);
        }
    }

    if (!account_found)
    {
        FILE *fNur = fopen("data/nurse.txt", "r");
        if (fNur != NULL)
        {
            char n_id[20], n_name[50], n_ward[50], n_pass[50];
            int n_age;
            while (fscanf(fNur, "%19s %49s %d %49s %49s", n_id, n_name, &n_age, n_ward, n_pass) == 5)
            {
                n_id[strcspn(n_id, "\r\n ")] = 0;
                n_pass[strcasecmp(n_pass, "\r\n ")] = 0;
                if (strcasecmp(n_id, reporter_id) == 0 && strcasecmp(n_pass, report_pass) == 0)

                {
                    account_found = 1;
                    strcpy(reporter_name, n_name);
                    strcpy(report_pass, n_pass);
                    break;
                }
            }
            fclose(fNur);
        }
    }

    if (!account_found)
    {
        printf("\n[ERROR] Account not found. Only registered users can submit reports.\n");
        return;
    }

    // ==========================================================
    //                      MENU SELECTION
    // ==========================================================
    int choice;
    printf("\nWelcome, %s.\nWhat would you like to report?\n", reporter_name);
    printf("1. Report a Doctor\n");
    printf("2. Report a Nurse\n");
    printf("3. Report a Patient\n");
    printf("4. General Hospital Issue (Equipment, Facility, etc.)\n");
    printf("5. Log Out");
    printf("Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
        {
        }
        printf("\n[ERROR] Invalid input.\n");
        return;
    }

    char target_name[100] = "General_Issue";
    char category[30] = "General";

    if (choice >= 1 && choice <= 3)
    {
        char list_names[100][100];
        int count = 1;

        if (choice == 1)
        {
            strcpy(category, "Doctor");
            printf("\n--- List of Doctors ---\n");
            FILE *fDoc = fopen("data/doctors.txt", "r");
            if (fDoc)
            {
                char d_id[20], d_name[50], d_spec[50];
                int d_age;
                while (fscanf(fDoc, "%19s %49s %d %49s", d_id, d_name, &d_age, d_spec) == 4)
                {
                    printf("%d. Dr. %-15s | Work: %s\n", count, d_name, d_spec);
                    strcpy(list_names[count], d_name);
                    count++;
                }
                fclose(fDoc);
            }
        }
        else if (choice == 2)
        {
            strcpy(category, "Nurse");
            printf("\n--- List of Nurses ---\n");
            FILE *fNur = fopen("data/nurse.txt", "r");
            if (fNur)
            {
                char n_id[20], n_name[50], n_ward[50];
                int n_age;
                while (fscanf(fNur, "%19s %49s %d %49s", n_id, n_name, &n_age, n_ward) == 4)
                {
                    printf("%d. Nurse %-13s | Work: %s\n", count, n_name, n_ward);
                    strcpy(list_names[count], n_name);
                    count++;
                }
                fclose(fNur);
            }
        }
        else if (choice == 3)
        {
            strcpy(category, "Patient");
            printf("\n--- List of Patients ---\n");

            FILE *fPat = fopen("data/patients.txt", "r");
            if (fPat)
            {
                char p_id[20], p_name[50], p_extra[50];
                int p_age;
                while (fscanf(fPat, "%19s %49s %d %49s", p_id, p_name, &p_age, p_extra) == 4)
                {
                    printf("%d. Patient %-13s | Info: %s\n", count, p_name, p_extra);
                    strcpy(list_names[count], p_name);
                    count++;
                }
                fclose(fPat);
            }
        }

        if (count == 1)
        {
            printf("[INFO] No records found to report.\n");
            return;
        }

        int target_choice;
        printf("\nEnter the NUMBER of the person you want to report Or Press 0 To Return: ");
        if (scanf("%d", &target_choice) != 1)
        {
            while (getchar() != '\n')
            {
            }
            printf("\n[ERROR] Invalid input. Please enter a number.\n");
            return;
        }

        if (target_choice == 0)
        {
            printf("\nReturning to previous menu...\n");
            return;
        }

        if (target_choice < 1 || target_choice >= count)
        {
            printf("\n[ERROR] Invalid selection. Please pick a number from the list.\n");
            return;
        }

        strcpy(target_name, list_names[target_choice]);
    }
    else if (choice != 4)
    {
        printf("\n[ERROR] Invalid choice.\n");
        return;
    }
    int min_length = 10;
    char message[500];
    printf("\nWrite your report message (No pipes '|' allowed. Press Enter to submit): Press 0 To return\n> ");
    getchar();
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\r\n")] = 0;
    if (strcmp(message, "0") == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }
    while (1)
    {
        printf("Enter your message (Minimum %d characters) Or Press 0 to Return: ", min_length);

        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;
        if (strcmp(message, "0") == 0)
        {
            printf("\n[CANCELLED] Returning to previous menu...\n");
            return;
        }

        if (strlen(message) < min_length)
        {
            printf("\n[ERROR] Message too short! You only typed %lu characters  Press 0 to Return:.\n", strlen(message));
            printf("Please provide more detail.\n\n");
        }

        else
        {
            printf("\n[SUCCESS] Message accepted.\n");
            break;
        }
    }

    FILE *fRep = fopen("data/system_reports.txt", "a");
    if (fRep != NULL)
    {
        fprintf(fRep, "%s|%s|%s|%s\n", reporter_id, category, target_name, message);
        fclose(fRep);
        printf("\n[SUCCESS] Your report has been submitted to the Administration!\n");
    }
    else if (choice == 5)
    {
        return;
    }

    else
    {
        printf("\n[ERROR] Could not save the report.\n");
    }
}