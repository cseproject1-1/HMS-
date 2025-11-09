#include "admin.h"
#include "utils.h"
#include "fileio.h"
void admin_menu(void) {
    int choice;

    while (1) {
        print_header("ADMIN MENU");
        printf("1. Manage Doctors\n");
        printf("2. View All Patients\n");
        printf("3. Generate Reports\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                manage_doctors();
                break;
            case 2:
                view_all_patients();
                break;
            case 3:
                generate_reports();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void manage_doctors(void) {
    int choice;

    while (1) {
        print_header("MANAGE DOCTORS");
        printf("1. View All Doctors\n");
        printf("2. Add Doctor\n");
        printf("3. Remove Doctor\n");
        printf("4. Back\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

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
                // Add doctor logic
                printf("Use Register option from main menu to add doctors.\n");
                break;
            case 3:
                printf("Enter doctor username to remove: ");
                char username[MAX_NAME];
                scanf("%s", username);

                for (int i = 0; i < user_count; i++) {
                    if (users[i].role == ROLE_DOCTOR &&
                        strcmp(users[i].username, username) == 0) {
                        // Shift array elements
                        for (int j = i; j < user_count - 1; j++) {
                            users[j] = users[j + 1];
                        }
                        user_count--;
                        save_users();
                        printf("Doctor removed successfully!\n");
                        goto found; // Using goto statement
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

void view_all_patients(void) {
    print_header("ALL PATIENTS");

    if (patient_count == 0) {
        printf("No patients found!\n");
        return;
    }

    printf("%-10s %-20s %-5s %-6s %-20s %-10s %-15s\n",
           "ID", "Name", "Age", "Gender", "Disease", "Doctor ID", "Status");
    printf("--------------------------------------------------------------------------------\n");

    // Loop with continue statement
    for (int i = 0; i < patient_count; i++) {
        // Skip discharged patients
        if (patients[i].status == STATUS_DISCHARGED) {
            continue;
        }

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

    int admitted_count = 0, discharged_count = 0, critical_count = 0;

    // Using operators in loop
    for (int i = 0; i < patient_count; i++) {
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
    printf("Total Doctors: %d\n", user_count - 1); // Exclude admin
}
