#include "admin.h"
#include "utils.h"
#include "fileio.h"

void admin_menu(void){
    int choice;
    while(1)
    {
        print_header("ADMIN MENU");
        printf("1. Manage Doctors\n");
        printf("2. View All Patients\n");
        printf("3. Add Patient\n");
        printf("4. Generate Reports\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice);
        switch(choice){
            case 1:
                manage_doctors();
                break;
            case 2:
                view_all_patients();
                break;
            case 3:
                patient_registration();
                break;
            case 4:
                generate_reports();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void patient_registration(void) {
    Patient new_patient;
    print_header("PATIENT REGISTRATION");
    strcpy(new_patient.patient_id, generate_patient_id());
    printf("Generated Patient ID: %s\n", new_patient.patient_id);
    printf("Enter patient name: ");
    clear_input_buffer();
    fgets(new_patient.name, MAX_NAME, stdin);
    new_patient.name[strcspn(new_patient.name, "\n")] = 0;
    printf("Enter age: ");
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &new_patient.age);
    if (!validate_age(new_patient.age)) {
        printf("Invalid age!\n");
        return;
    }
    printf("Enter gender (M/F): ");
    clear_input_buffer();
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %c", &new_patient.gender);
    new_patient.gender = toupper(new_patient.gender);
    printf("Enter disease description: ");
    clear_input_buffer();
    fgets(new_patient.disease, MAX_DISEASE, stdin);
    new_patient.disease[strcspn(new_patient.disease, "\n")] = 0;
    printf("Enter assigned doctor ID: ");
    fgets(new_patient.doctor_id, sizeof(new_patient.doctor_id), stdin);
    new_patient.doctor_id[strcspn(new_patient.doctor_id, "\n")] = 0;
    printf("Enter admission date (DD-MM-YYYY): ");
    fgets(new_patient.admission_date, sizeof(new_patient.admission_date), stdin);
    new_patient.admission_date[strcspn(new_patient.admission_date, "\n")] = 0;
    if (!validate_date(new_patient.admission_date)) {
        printf("Invalid date format!\n");
        return;
    }
    new_patient.status = STATUS_ADMITTED;
    patients[patient_count] = new_patient;
    patient_count++;
    save_patients();
    printf("Patient registered successfully!\n");
}

void manage_doctors(void){
    int choice;
    while(1){
        print_header("MANAGE DOCTORS");
        printf("1. View All Doctors\n");
        printf("2. Add Doctor\n");
        printf("3. Remove Doctor\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice);
        switch (choice) {
            case 1:
                printf("\n--- All Doctors ---\n");
                for (int i = 0; i < user_count; i++) {
                    if (users[i].role == ROLE_DOCTOR) {
                        printf("Username: %s, Doctor ID: %s\n",
                               users[i].username, users[i].doctor_id);
                    }
                }
                break;
            case 2:
                printf("Use Register option from main menu to add doctors.\n");
                break;
            case 3:
                printf("Enter doctor username to remove: ");
                char username[MAX_NAME];
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;

                for (int i = 0; i < user_count; i++) {
                    if (users[i].role == ROLE_DOCTOR && strcmp(users[i].username,username)==0) {
                        for(int j=i;j<user_count-1;j++) users[j] = users[j + 1];
                        user_count--;
                        save_users();
                        printf("Doctor removed successfully!\n");
                        goto found;
                    }
                }
                printf("Doctor not found!\n");
                found:
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void view_all_patients(void){
    print_header("ALL PATIENTS");
    if(patient_count==0){
    printf("No patients found!\n");
    return;
    }
    printf("%-10s %-20s %-5s %-6s %-20s %-10s %-15s\n",
           "ID", "Name", "Age", "Gender", "Disease", "Doctor ID", "Status");
    printf("--------------------------------------------------------------------------------\n");
    for (int i=0;i<patient_count;i++){
        if (patients[i].status == STATUS_DISCHARGED) continue;
        printf("%-10s %-20s %-5d %-6c %-20s %-10s %-15s\n",
               patients[i].patient_id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].disease,
               patients[i].doctor_id,
               status_to_string(patients[i].status));
    }
}

void generate_reports(void) {
    print_header("GENERATE REPORTS");
    int admitted_count=0,discharged_count=0,critical_count=0;
    for (int i=0;i<patient_count;i++){
        switch (patients[i].status) {
            case STATUS_ADMITTED:
                admitted_count++;
                break;
            case STATUS_DISCHARGED:
                discharged_count++;
                break;
            case STATUS_CRITICAL:
                critical_count++;
                break;
        }
    }
    printf("Hospital Statistics:\n");
    printf("Total Patients: %d\n", patient_count);
    printf("Admitted Patients: %d\n", admitted_count);
    printf("Discharged Patients: %d\n", discharged_count);
    printf("Critical Patients: %d\n", critical_count);
    printf("Total Doctors: %d\n", user_count - 1);
}
