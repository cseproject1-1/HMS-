#include "patient.h"
#include "utils.h"
#include "fileio.h"

void view_patient_details(void) {
    char patient_id[MAX_ID];
    print_header("VIEW PATIENT DETAILS");
    printf("Enter Patient ID: ");
    fgets(patient_id, sizeof(patient_id), stdin);
    patient_id[strcspn(patient_id, "\n")] = 0;
    Patient* ptr = patients;
    for (int i = 0; i < patient_count; i++, ptr++) {
        if (strcmp(ptr->patient_id, patient_id) == 0) {
            printf("Patient ID: %s\n", ptr->patient_id);
            printf("Name: %s\n", ptr->name);
            printf("Age: %d\n", ptr->age);
            printf("Gender: %c\n", ptr->gender);
            printf("Disease: %s\n", ptr->disease);
            printf("Doctor ID: %s\n", ptr->doctor_id);
            printf("Status: %s\n", status_to_string(ptr->status));
            printf("Admission Date: %s\n", ptr->admission_date);
            return;
        }
    }
    printf("Patient not found!\n");
}

void patient_menu(void) {
    int choice;
    while (1) {
        print_header("PATIENT MENU");
        printf("1. View My Details\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice);
        switch (choice) {
            case 1:
                view_patient_details();
                break;
            case 2:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}
