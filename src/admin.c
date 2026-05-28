#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include "../include/saass.h"
const char admin_user[20] = " jamel";
const char admin_password[20] = "jamel1234";
int sign_system(void)
{
    int choice_1;
    char sign_name[50], sign_password[50];

    printf("\n===== Admin Sign In =====\n");

    while (1)
    {
        printf("1. Sign In \n2. Go Back\nChoose A Number: ");

        if (scanf("%d", &choice_1) != 1)
        {
            printf("\n[ERROR] Invalid Input!\n");
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
            printf("-----------Press 0 To Return-----------------\nEnter User Name: ");
            scanf("%49s", sign_name);
            if (strcmp(sign_name, "0") == 0)
            {
                printf("\nReturning to Main Menu...\n");
                return 0;
            }
            printf("Enter Password:  ");
            scanf("%49s", sign_password);
            if (strcmp(sign_password, "0") == 0)
            {
                printf("\nReturning to Main Menu...\n");
                return 0;
            }

            int authenticated = 0;
            FILE *f = fopen("data/users.txt", "r");

            if (f == NULL)
            {
                if (strcmp(sign_name, admin_user) == 0 && strcmp(sign_password, admin_password) == 0)
                {
                    authenticated = 1;
                    printf("\n[INFO] Logged In Using Emergency Admin Account.\n");
                }
            }
            else
            {
                char line[300], f_id[20], f_user[50], f_pass[50], f_role[30], f_name[100];

                while (fgets(line, sizeof(line), f))
                {
                    if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", f_id, f_user, f_pass, f_role, f_name) == 5)
                    {
                        if (strcmp(f_role, "Administrator") == 0 && strcmp(f_user, sign_name) == 0 && strcmp(f_pass, sign_password) == 0)
                        {
                            authenticated = 1;
                            break;
                        }
                    }
                }
                fclose(f);
            }

            if (authenticated)
            {
                printf("\n------ Successfully Logged In ------\n");
                return 1;
            }
            else if (i <= 1)
            {
                printf("\n------ Too Many Tries  ------\n");
                return 0;
            }
            else
            {
                i--;
                printf("\n------ Wrong Input! %d Tries Left ------\n", i);
            }
        }
    }
    else
    {
        printf("\n------ Going To Back ------\n");
        return 0;
    }
    return 0;
}

int main_admistration_mnue(void)
{
    if (sign_system() == 0)
    {
        return 0;
    }

    int choice;

    while (1)
    {
        printf("\n===== ADMINISTRATOR MENU =====\n");
        printf("1. Register Patient\n");
        printf("2. Register Doctor\n");
        printf("3. Register Nurse\n");
        printf("4. Database Management\n");
        printf("5. Mange Reports\n");
        printf("6. Viwe All Ptients Medical Record\n");
        printf("7. Logout\n");
        printf("Choose A Number: ");

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
            Register_Patient();
        }
        else if (choice == 2)
        {
            Register_Doctor();
        }
        else if (choice == 3)
        {
            Register_Nurse();
        }
        else if (choice == 4)
        {
            View_data_base();
        }
        else if (choice == 5)
        {
            admin_manage_reports();
        }
        else if (choice == 6)
        {
            admin_view_all_patients();
        }
        else if (choice == 7)
        {
            printf("\nLogging Out...\n");
            return 0;
        }
        else
        {
            printf("\n[ERROR] Invalid Choice!\n");
        }
    }

    return 0;
}

void Register_Patient(void)
{
    struct Patient p;
    int id_number;
    char pasword[50];
    int max_id = 99999;
    char least_tletters = 8;

    printf("\n--- Register Patient Enter 0 to return ---\n");

    while (1)
    {
        printf("Enter Patient ID (Numbers Only): ");

        if (scanf("%d", &id_number) != 1)
        {
            printf("\n[ERROR] Invalid Input. Numbers Only!\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }
        if (id_number == 0)
        {
            printf("\nReturning to previous menu...\n");
            return;
        }

        if (id_number > max_id)
        {
            printf(" Maximum ID Number Is 5 ");
            continue;
        }

        sprintf(p.patient_id, "P%d", id_number);

        if (id_exists("data/patients.txt", p.patient_id))
        {
            printf("[ERROR] ID Already Exists! %s\n", p.patient_id);
            return;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Enter Your Password: \n");
        scanf("%49s", pasword);
        if (strcmp(pasword, "0") == 0)
        {
            printf("\nReturning to previous menu...\n");
            return;
        }
        if (strlen(pasword) < least_tletters)
        {
            printf("Pasword Must Be At Leat 8 Letters!\n");
            continue;
        }

        else
        {
            sprintf(p.ppasword, "%s", pasword);
            printf("Your Password Is : %s\n", p.ppasword);
            break;
        }
    }
    printf("Enter Name (Use_Underscores): ");
    scanf(" %49s", p.patient_name);
    if (strcmp(p.patient_name, "0") == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }

    printf("Enter Age: ");
    scanf("%d", &p.patient_age);
    if (p.patient_age == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }

    printf("Enter Disease (Use_Underscores): ");
    scanf(" %49s", p.patient_disease);
    if (strcmp(p.patient_disease, "0") == 0)
    {
        printf("\nReturning to previous menu...\n");
        return;
    }

    FILE *file = fopen("data/patients.txt", "a");

    if (file)
    {
        fprintf(file, "%s %s %d %s %s\n", p.patient_id, p.patient_name, p.patient_age, p.patient_disease, p.ppasword);
        fclose(file);
        printf("\n[SUCCESS] Patient Registered: %s | ID: %s\n", p.patient_name, p.patient_id);
    }
}

void Register_Doctor(void)
{
    struct doctors p;
    int id_number;
    int max_id = 99999;
    char least_tletters = 8;
    char pasword[50];

    printf("\n--- Register Doctor ---\n");

    while (1)
    {
        printf("Enter Doctor ID (Numbers Only): ");

        if (scanf("%d", &id_number) != 1)
        {
            printf("\n[ERROR] Invalid Input!\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }
        if (id_number > max_id)
        {
            printf(" Maximum ID Number Is 5 \n");
            continue;
        }

        sprintf(p.doctor_id, "D%d", id_number);

        if (id_exists("data/doctors.txt", p.doctor_id))
        {
            printf("[ERROR] ID Already Exists! %s\n", p.doctor_id);
            continue;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Enter Your Password: ");
        scanf("%49s", pasword);
        if (strlen(pasword) < least_tletters)
        {
            printf("Pasword Must Be At Leat 8 Letters!\n");
            continue;
        }

        else
        {
            sprintf(p.dpasword, "%s", pasword);
            printf("Your Password Is : %s\n", p.dpasword);
            break;
        }
    }
    printf("Enter Name (Use_Underscores): ");
    scanf(" %49s", p.doctor_name);

    printf("Enter Age: ");
    scanf("%d", &p.doctor_age);

    printf("Enter Specialization (Use_Underscores): ");
    scanf(" %49s", p.doctor_speciallization);

    FILE *file = fopen("data/doctors.txt", "a");

    if (file)
    {
        fprintf(file, "%s %s %d %s %s\n", p.doctor_id, p.doctor_name, p.doctor_age, p.doctor_speciallization, p.dpasword);
        fclose(file);
        printf("\n[SUCCESS] Doctor Registered: %s\n", p.doctor_name);
    }
}

void Register_Nurse(void)
{
    struct nurse p;
    int id_number;
    int max_id = 99999;
    char least_tletters = 8;
    char pasword[50];

    printf("\n--- Register Nurse ---\n");

    while (1)
    {
        printf("Enter Nurse ID (Numbers Only): ");

        if (scanf("%d", &id_number) != 1)
        {
            printf("\n[ERROR] Invalid Input!\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }
        if (id_number > max_id)
        {
            printf(" Maximum ID Number Is 5 ");
            continue;
        }

        sprintf(p.nurse_id, "N%d", id_number);

        if (id_exists("data/nurse.txt", p.nurse_id))
        {
            printf("[ERROR] ID Already Exists %s\n", p.nurse_id);
            continue;
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("Enter Your Password: ");
        scanf("%49s", pasword);
        if (strlen(pasword) < least_tletters)
        {
            printf("Pasword Must Be At Leat 8 Letters!\n");
            continue;
        }

        else
        {
            sprintf(p.npasword, "%s", pasword);
            printf("Your Password Is : %s\n", p.npasword);
            break;
        }
    }
    printf("Enter Name (Use_Underscores): ");
    scanf(" %49s", p.nurse_name);

    printf("Enter Age: ");
    scanf("%d", &p.nurse_age);

    printf("Enter Ward (Use_Underscores): ");
    scanf(" %49s", p.nurse_assigned_ward);

    FILE *file = fopen("data/nurse.txt", "a");

    if (file)
    {
        fprintf(file, "%s %s %d %s %s\n", p.nurse_id, p.nurse_name, p.nurse_age, p.nurse_assigned_ward, p.npasword);
        fclose(file);
        printf("\n[SUCCESS] Nurse Registered: %s\n", p.nurse_name);
    }
}

int View_data_base(void)
{
    int choice_1;
    char search_info[50];

    while (1)
    {
        printf("\n|======================================================|\n");
        printf("|                     Database Management              |\n");
        printf("|======================================================|\n");
        printf("1. View All Stored Data\n");
        printf("2. Super Search\n");
        printf("3. Delete Txt Files!\n");
        printf("4. Go Back To Main Menu\n");
        printf("Choose A Number: ");

        if (scanf("%d", &choice_1) != 1)
        {
            printf("\n[ERROR] Invalid Input. Numbers Only.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        // ==========================================================
        //                  VIEW ALL DATA
        // ==========================================================
        if (choice_1 == 1)
        {

            {
                struct Patient p;
                FILE *f = fopen("data/patients.txt", "r");
                if (f)
                {
                    printf("\n--- Patients Database ---\n%-15s | %-20s | %-5s | %-20s\n", "ID", "Name", "Age", "Disease");
                    while (fscanf(f, "%19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease, p.ppasword) == 5)
                        printf("%-15s | %-20s | %-5d | %-20s\n", p.patient_id, p.patient_name, p.patient_age, p.patient_disease);
                    fclose(f);
                }
            }

            {
                struct doctors d;
                FILE *f = fopen("data/doctors.txt", "r");
                if (f)
                {
                    printf("\n--- Doctors Database ---\n%-15s | %-20s | %-5s | %-20s\n", "ID", "Name", "Age", "Specialization");
                    while (fscanf(f, "%19s %49s %d %49s %49s", d.doctor_id, d.doctor_name, &d.doctor_age, d.doctor_speciallization, d.dpasword) == 5)
                        printf("%-15s | %-20s | %-5d | %-20s\n", d.doctor_id, d.doctor_name, d.doctor_age, d.doctor_speciallization);
                    fclose(f);
                }
            }

            {
                struct nurse n;
                FILE *f = fopen("data/nurse.txt", "r");
                if (f)
                {
                    printf("\n--- Nurses Database ---\n%-15s | %-20s | %-5s | %-20s\n", "ID", "Name", "Age", "Ward");
                    while (fscanf(f, "%19s %49s %d %49s %49s", n.nurse_id, n.nurse_name, &n.nurse_age, n.nurse_assigned_ward, n.npasword) == 5)
                        printf("%-15s | %-20s | %-5d | %-20s\n", n.nurse_id, n.nurse_name, n.nurse_age, n.nurse_assigned_ward);
                    fclose(f);
                }
            }

            {
                struct Appointment a;
                FILE *f = fopen("data/appointments.txt", "r");
                if (f)
                {
                    printf("\n--- Appointments Database ---\n%-15s | %-20s | %-12s | %-8s | %-10s\n", "Patient ID", "Doctor", "Date", "Time", "Status");
                    while (fscanf(f, " %19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^|]|%19[^\n]\n", a.patientID, a.doctorName, a.date, a.time, a.status, a.priority) == 6)
                        printf("%-15s | %-20s | %-12s | %-8s | %-10s\n", a.patientID, a.doctorName, a.date, a.time, a.status);
                    fclose(f);
                }
            }

            {
                struct supply s;
                FILE *f = fopen("data/supplies.txt", "r");
                if (f)
                {
                    printf("\n--- Supplies Inventory ---\n%-20s | %-10s | %-10s\n", "Item Name", "Quantity", "Price");
                    while (fscanf(f, " %49[^|]|%d|%f\n", s.name, &s.qty, &s.price) == 3)
                        printf("%-20s | %-10d | %.2f\n", s.name, s.qty, s.price);
                    fclose(f);
                }
            }

            {
                FILE *f = fopen("data/PatientsPrescription.txt", "r");
                if (f)
                {
                    char pid[20], did[20], ill[100], med[100], note[100];
                    printf("\n--- Prescription History ---\n%-15s | %-15s | %-20s\n", "Patient ID", "Doctor ID", "Medicine");
                    while (fscanf(f, " %19[^|]|%19[^|]|%99[^|]|%99[^|]|%99[^\n]\n", pid, did, ill, med, note) == 5)
                        printf("%-15s | %-15s | %-20s\n", pid, did, med);
                    fclose(f);
                }
            }
        }
        // ==========================================================
        //              SUPER SEARCH & DELETE PORTAL
        // ==========================================================
        else if (choice_1 == 2)
        {
            int choice_mode;
            int global_found = 0;

            while (1)
            {
                printf("\n--- Super Search Mode Selection ---\n1. Mode: Search Only\n2. Mode: Search And Delete\n3. Return To Database Menu\nChoice: ");
                if (scanf("%d", &choice_mode) != 1)
                {
                    while (getchar() != '\n')
                    {
                    }
                    continue;
                }
                break;
            }

            if (choice_mode == 3)
                continue;

            printf("Enter Information To Search (Name, ID, Or Disease): ");
            scanf("%49s", search_info);
            int target_age = atoi(search_info);

            if (choice_mode == 1)
            {
                printf("\n--- Searching All Databases For: %s ---\n", search_info);
                // Patients
                {
                    struct Patient p;
                    FILE *f = fopen("data/patients.txt", "r");
                    if (f)
                    {
                        while (fscanf(f, "%19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease , p.ppasword ) == 5)
                            if (strcasecmp(p.patient_id, search_info) == 0 || strcasecmp(p.patient_name, search_info) == 0)
                            {
                                printf("[PATIENT] ID: %s | Name: %s | Disease: %s\n", p.patient_id, p.patient_name, p.patient_disease);
                                global_found = 1;
                            }
                        fclose(f);
                    }
                }

                {
                    struct doctors d;
                    FILE *f = fopen("data/doctors.txt", "r");
                    if (f)
                    {
                        while (fscanf(f, "%19s %49s %d %49s  %49s", d.doctor_id, d.doctor_name, &d.doctor_age, d.doctor_speciallization , d.dpasword) == 5)
                            if (strcasecmp(d.doctor_id, search_info) == 0 || strcasecmp(d.doctor_name, search_info) == 0)
                            {
                                printf("[DOCTOR]  ID: %s | Name: %s | Spec: %s\n", d.doctor_id, d.doctor_name, d.doctor_speciallization);
                                global_found = 1;
                            }
                        fclose(f);
                    }
                }

                {
                    struct nurse n;
                    FILE *f = fopen("data/nurse.txt", "r");
                    if (f)
                    {
                        while (fscanf(f, "%19s %49s %d %49s %49s", n.nurse_id, n.nurse_name, &n.nurse_age, n.nurse_assigned_ward , n.npasword) == 5)
                            if (strcasecmp(n.nurse_id, search_info) == 0 || strcasecmp(n.nurse_name, search_info) == 0)
                            {
                                printf("[NURSE]   ID: %s | Name: %s | Ward: %s\n", n.nurse_id, n.nurse_name, n.nurse_assigned_ward);
                                global_found = 1;
                            }
                        fclose(f);
                    }
                }
            }

            else if (choice_mode == 2)
            {

                {
                    struct Patient p;
                    int f_p = 0;
                    FILE *f = fopen("data/patients.txt", "r");
                    FILE *t = fopen("data/temp_p.txt", "w");
                    if (f && t)
                    {
                        while (fscanf(f, " %19s %49s %d %49s %49s", p.patient_id, p.patient_name, &p.patient_age, p.patient_disease , p.ppasword) == 5)
                        {
                            if (strcasecmp(p.patient_id, search_info) == 0 || strcasecmp(p.patient_name, search_info) == 0)
                            {
                                printf("[DELETED] Patient: %s From Patients.txt\n", p.patient_name);
                                f_p = 1;
                                global_found = 1;
                            }
                            else
                                fprintf(t, "%s %s %d %s %s\n", p.patient_id, p.patient_name, p.patient_age, p.patient_disease , p.ppasword);
                        }
                        fclose(f);
                        fclose(t);
                        if (f_p)
                        {
                            remove("data/patients.txt");
                            rename("data/temp_p.txt", "data/patients.txt");
                        }
                        else
                            remove("data/temp_p.txt");
                    }
                }

                {
                    struct doctors d;
                    int f_d = 0;
                    FILE *f = fopen("data/doctors.txt", "r");
                    FILE *t = fopen("data/temp_d.txt", "w");
                    if (f && t)
                    {
                        while (fscanf(f, " %19s %49s %d %49s %49s", d.doctor_id, d.doctor_name, &d.doctor_age, d.doctor_speciallization , d.dpasword) == 5)
                        {
                            if (strcasecmp(d.doctor_id, search_info) == 0 || strcasecmp(d.doctor_name, search_info) == 0)
                            {
                                printf("[DELETED] Doctor: %s From Doctors.txt\n", d.doctor_name);
                                f_d = 1;
                                global_found = 1;
                            }
                            else
                                fprintf(t, "%s %s %d %s %s\n", d.doctor_id, d.doctor_name, d.doctor_age, d.doctor_speciallization , d.dpasword);
                        }
                        fclose(f);
                        fclose(t);
                        if (f_d)
                        {
                            remove("data/doctors.txt");
                            rename("data/temp_d.txt", "data/doctors.txt");
                        }
                        else
                            remove("data/temp_d.txt");
                    }
                }

                {
                    struct nurse n;
                    int f_n = 0;
                    FILE *f = fopen("data/nurse.txt", "r");
                    FILE *t = fopen("data/temp_n.txt", "w");
                    if (f && t)
                    {
                        while (fscanf(f, " %19s %49s %d %49s %49s", n.nurse_id, n.nurse_name, &n.nurse_age, n.nurse_assigned_ward , n.npasword) == 5)
                        {
                            if (strcasecmp(n.nurse_id, search_info) == 0 || strcasecmp(n.nurse_name, search_info) == 0)
                            {
                                printf("[DELETED] Nurse: %s From Nurse.txt\n", n.nurse_name);
                                f_n = 1;
                                global_found = 1;
                            }
                            else
                                fprintf(t, "%s %s %d %s %s\n", n.nurse_id, n.nurse_name, n.nurse_age, n.nurse_assigned_ward , n.npasword);
                        }
                        fclose(f);
                        fclose(t);
                        if (f_n)
                        {
                            remove("data/nurse.txt");
                            rename("data/temp_n.txt", "data/nurse.txt");
                        }
                        else
                            remove("data/temp_n.txt");
                    }
                }

                {
                    struct Appointment a;
                    int f_a = 0;
                    FILE *f = fopen("data/appointments.txt", "r");
                    FILE *t = fopen("data/temp_a.txt", "w");
                    if (f && t)
                    {
                        while (fscanf(f, " %19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^|]|%19[^\n]\n", a.patientID, a.doctorName, a.date, a.time, a.status, a.priority) == 6)
                        {
                            if (strcasecmp(a.patientID, search_info) == 0 || strcasecmp(a.doctorName, search_info) == 0)
                            {
                                printf("[DELETED] Appointment Record For: %s\n", a.patientID);
                                f_a = 1;
                                global_found = 1;
                            }
                            else
                                fprintf(t, "%s|%s|%s|%s|%s|%s\n", a.patientID, a.doctorName, a.date, a.time, a.status, a.priority);
                        }
                        fclose(f);
                        fclose(t);
                        if (f_a)
                        {
                            remove("data/appointments.txt");
                            rename("data/temp_a.txt", "data/appointments.txt");
                        }
                        else
                            remove("data/temp_a.txt");
                    }
                }

                {
                    struct supply s;
                    int f_s = 0;
                    FILE *f = fopen("data/supplies.txt", "r");
                    FILE *t = fopen("data/temp_s.txt", "w");
                    if (f && t)
                    {
                        while (fscanf(f, " %49[^|]|%d|%f\n", s.name, &s.qty, &s.price) == 3)
                        {
                            if (strcasecmp(s.name, search_info) == 0)
                            {
                                printf("[DELETED] Supply Item: %s From Supplies.txt\n", s.name);
                                f_s = 1;
                                global_found = 1;
                            }
                            else
                                fprintf(t, "%s|%d|%.2f\n", s.name, s.qty, s.price);
                        }
                        fclose(f);
                        fclose(t);
                        if (f_s)
                        {
                            remove("data/supplies.txt");
                            rename("data/temp_s.txt", "data/supplies.txt");
                        }
                        else
                            remove("data/temp_s.txt");
                    }
                }
            }

            if (!global_found)
                printf("\n[INFO] Target Information '%s' Was Not Found In Any Database.\n", search_info);
        }
        else if (choice_1 == 3)
            delete_hospital_files();
        else if (choice_1 == 4)
            return 0;
    }
}

int delete_hospital_files(void)
{

    int auth = sign_system();
    int choice;
    char confirm[10];
    if (auth == 1)
    {
        while (1)
        {
            printf("\n|======================================================|\n");
            printf("|              SECURITY ALERT: DELETE FILES            |\n");
            printf("|======================================================|\n");
            printf("\n1. DELETE PATIENTS FILE\n");
            printf("2. DELETE DOCTORS FILE\n");
            printf("3. DELETE NURSES FILE\n");
            printf("4. DELETE APPOINTMENTS FILE\n");
            printf("5. DELETE SUPPLIES FILE\n");
            printf("6. DELETE PRESCRIPTIONS FILE\n");
            printf("7. DELETE ALL OPERATIONAL FILES!\n");
            printf("8. Go Back To Main Menu\n");
            printf("Choice: ");

            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                {
                }
                continue;
            }

            if (choice == 8)
            {
                return 0;
            }

            if (choice >= 1 && choice <= 7)
            {
                printf("\nARE YOU SURE YOU WANT TO DELETE? (ENTER 'Yes' OR 'No'): ");
                scanf("%9s", confirm);

                if (strcasecmp(confirm, "yes") == 0)
                {
                    if (choice == 1)
                        remove("data/patients.txt");
                    else if (choice == 2)
                        remove("data/doctors.txt");
                    else if (choice == 3)
                        remove("data/nurse.txt");
                    else if (choice == 4)
                        remove("data/appointments.txt");
                    else if (choice == 5)
                        remove("data/supplies.txt");
                    else if (choice == 6)
                        remove("data/PatientsPrescription.txt");
                    else if (choice == 7)
                    {
                        remove("data/patients.txt");
                        remove("data/doctors.txt");
                        remove("data/nurse.txt");
                        remove("data/appointments.txt");
                        remove("data/supplies.txt");
                        remove("data/PatientsPrescription.txt");
                    }
                    printf("\n[SUCCESS] Files Deleted.\n");
                    return 0;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    else if (auth == 0)
    {
        return 0;
    }
    else if (auth == -1)
    {
        printf("\n|-----------------------------------------|\n");
        printf("\n|-----------------------------------------|\n");
        printf("\n|------[SECURITY ALRERT!] Loging out...---|\n");
        printf("\n|-----------------------------------------|\n");
        printf("\n|-----------------------------------------|\n");
        return 0;
    }
    return 0;
}

void admin_manage_reports(void)
{
    int choice;

    while (1)
    {
        printf("\n|====================================================================|\n");
        printf("|                   ADMIN SYSTEM REPORTS HELPDESK                    |\n");
        printf("|====================================================================|\n");
        printf("1. View & Resolve Active Reports\n");
        printf("2. View History of Resolved Reports\n");
        printf("3. Return to Admin Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
            {
            }
            printf("\n[ERROR] Invalid input.\n");
            continue;
        }

        // ==========================================
        //      VIEW AND RESOLVE ACTIVE REPORTS
        // ==========================================
        if (choice == 1)
        {
            char line[400];
            char r_id[20], cat[30], target[100], msg[300];
            int count = 0;

            FILE *fRep = fopen("data/system_reports.txt", "r");
            if (fRep == NULL)
            {
                printf("\n[INFO] No active reports found! The hospital is running perfectly.\n");
                continue;
            }

            printf("\n--- ACTIVE SYSTEM REPORTS ---\n");
            printf("%-3s | %-10s | %-10s | %-15s | %s\n", "No.", "Reporter", "Category", "Target", "Message");
            printf("--------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), fRep))
            {
                if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^\n]", r_id, cat, target, msg) >= 4)
                {
                    count++;
                    r_id[strcspn(r_id, "\r\n ")] = 0;
                    cat[strcspn(cat, "\r\n ")] = 0;
                    target[strcspn(target, "\r\n ")] = 0;
                    printf("%-3d | %-10s | %-10s | %-15s | %s\n", count, r_id, cat, target, msg);
                }
            }
            fclose(fRep);

            if (count == 0)
            {
                printf("[INFO] No active reports found.\n");
                continue;
            }

            int resolve_choice;
            printf("\nEnter the NUMBER of the report to mark as RESOLVED (or 0 to go back): ");
            if (scanf("%d", &resolve_choice) != 1)
            {
                while (getchar() != '\n')
                {
                }
                printf("\n[ERROR] Invalid input.\n");
                continue;
            }

            if (resolve_choice == 0)
            {
                printf("\nReturning...\n");
                continue;
            }
            else if (resolve_choice > 0 && resolve_choice <= count)
            {

                FILE *fOld = fopen("data/system_reports.txt", "r");
                FILE *fTemp = fopen("data/temp_reports.txt", "w");
                FILE *fRes = fopen("data/resolved_reports.txt", "a");

                if (fOld && fTemp && fRes)
                {
                    int current_line = 1;
                    while (fgets(line, sizeof(line), fOld))
                    {
                        if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^\n]", r_id, cat, target, msg) >= 4)
                        {
                            if (current_line == resolve_choice)
                            {

                                fputs(line, fRes);
                                printf("\n[SUCCESS] Report #%d has been RESOLVED and moved to history.\n", resolve_choice);
                            }
                            else
                            {

                                fputs(line, fTemp);
                            }
                            current_line++;
                        }
                    }
                }

                if (fOld)
                    fclose(fOld);
                if (fTemp)
                    fclose(fTemp);
                if (fRes)
                    fclose(fRes);

                remove("data/system_reports.txt");
                rename("data/temp_reports.txt", "data/system_reports.txt");
            }
            else
            {
                printf("\n[ERROR] Invalid report number.\n");
            }
        }

        // ==========================================
        //            VIEW RESOLVED HISTORY
        // ==========================================
        else if (choice == 2)
        {
            char line[400];
            char r_id[20], cat[30], target[100], msg[300];
            int count = 0;

            FILE *fRes = fopen("data/resolved_reports.txt", "r");
            if (fRes == NULL)
            {
                printf("\n[INFO] No resolved reports history found yet.\n");
                continue;
            }

            printf("\n--- RESOLVED REPORTS HISTORY ---\n");
            printf("%-3s | %-10s | %-10s | %-15s | %s\n", "No.", "Reporter", "Category", "Target", "Message");
            printf("--------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), fRes))
            {
                if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^\n]", r_id, cat, target, msg) >= 4)
                {
                    count++;
                    r_id[strcspn(r_id, "\r\n ")] = 0;
                    cat[strcspn(cat, "\r\n ")] = 0;
                    target[strcspn(target, "\r\n ")] = 0;
                    printf("%-3d | %-10s | %-10s | %-15s | %s\n", count, r_id, cat, target, msg);
                }
            }
            fclose(fRes);

            if (count == 0)
            {
                printf("[INFO] History is empty.\n");
            }

            printf("\nPress Enter to return...");
            getchar();
            getchar();
        }

        // ==========================================
        // CHOICE 3: EXIT
        // ==========================================
        else if (choice == 3)
        {
            printf("\nReturning to Main Admin Menu...\n");
            break;
        }
        else
        {
            printf("\n[ERROR] Invalid choice!\n");
        }
    }
}
void admin_view_all_patients(void)
{
    char line[300];
    char p_id[20], d_id[20], diag[50], med_name[50], extra[50];
    int count = 0;

    printf("\n|======================================================================|\n");
    printf("|                    ALL PATIENT CLINICAL RECORDS                      |\n");
    printf("|======================================================================|\n\n");

    FILE *fPres = fopen("data/PatientsPrescription.txt", "r");
    if (fPres == NULL)
        fPres = fopen("data/PatientsPrescription", "r");

    if (fPres == NULL)
    {
        printf("[INFO] No patient records or prescriptions found.\n");
        return;
    }

    printf("%-12s | %-12s | %-25s | %-20s\n", "Patient ID", "Doctor ID", "Diagnosis", "Medicine");
    printf("-------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fPres))
    {

        if (sscanf(line, " %[^|] | %[^|] | %[^|] | %[^|] | %[^\n]", p_id, d_id, diag, med_name, extra) >= 4)
        {

            p_id[strcspn(p_id, "\r\n")] = 0;
            d_id[strcspn(d_id, "\r\n")] = 0;
            diag[strcspn(diag, "\r\n")] = 0;
            med_name[strcspn(med_name, "\r\n")] = 0;

            printf("%-12s | %-12s | %-25s | %-20s\n", p_id, d_id, diag, med_name);
            count++;
        }
    }
    fclose(fPres);

    printf("-------------------------------------------------------------------------------\n");
    printf("Total Records Found: %d\n", count);
    printf("===============================================================================\n");
}