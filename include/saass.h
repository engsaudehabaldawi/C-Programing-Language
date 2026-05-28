#ifndef SAASS_H
#define SAASS_H

// Include standard libraries here 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>

#define MAX 200

// ==============================================================================
//                               STRUCTS
// ==============================================================================

/**
 * @struct Patient
 * @brief Represents a patient in the hospital.
 */
struct Patient
{
    char patient_id[20];
    char patient_name[50];
    int patient_age;
    char patient_disease[50];
    char ppasword[50];
};

/**
 * @struct doctors
 * @brief Represents a doctor employed by the hospital.
 */
struct doctors
{
    char doctor_id[20];
    char doctor_name[50];
    int doctor_age;
    char doctor_speciallization[50];
    char dpasword[50];
};

/**
 * @struct nurse
 * @brief Represents a nurse and their assigned ward.
 */
struct nurse
{
    char nurse_id[20];
    char nurse_name[50];
    int nurse_age;
    char nurse_assigned_ward[50];
    char npasword[50];
};

/**
 * @struct Appointment
 * @brief Represents a medical appointment booking.
 */
struct Appointment
{
    char patientID[20];
    char doctorName[50];
    char date[15];
    char time[10];
    char status[20];
    char priority[20];
};

/**
 * @struct supply
 * @brief Represents medical inventory and stock items.
 */
struct supply
{
    char name[50];
    int qty;
    float price;
};

// ==============================================================================
//                               PROTOTYPES
// ==============================================================================

// Utility & Main
int id_exists(char *filename, char *searchid);
void print_ascii_art(void);
void display_hospital_info(void);
void unified_login(void);
void submit_system_report(void);

// Director 
void directorMen(void);
int director_sign_system(void);
void manageAdmin(void);
void addAdmin(void);
void searchAdmin(void);
void viewAllAdmins(void);
void staffReport(void);
void appointmentTrendReport(void);
void remove_admin(void);;

// Admin 
int sign_system(void);
int main_admistration_mnue(void);
void Register_Patient(void);
void Register_Doctor(void);
void Register_Nurse(void);
int View_data_base(void);
int delete_hospital_files(void);
void admin_manage_reports(void);
void admin_view_all_patients(void);

// Patient
void patientMenu(char userID[]);
void bookAppointment(char userID[]);
void viewAppointments(char userID[]);
void updateAppointment(char userID[], int mode);
void viewMedicalInfo(char userID[]);

// Doctor & Nurse 
void doc_menu(char dr_id[], char dr_name[]);
void show_schedule(char dr_name[]);
void find_patient(void);
void change_status(void);
void write_meds(char dr_id[]);
void show_history(char dr_id[]);

void nurse_menu(char n_id[], char n_name[]);
void show_stock(void);
void find_item(void);
void add_stock(void);
void low_stock(void);

#endif