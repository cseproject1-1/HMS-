#include "patient.h"
#include "utils.h"
#include "fileio.h"
void patient_registration(void) {
    Patient new_patient;

    print_header("PATIENT REGISTRATION");

    // Generate patient ID using user-defined function
    strcpy(new_patient.patient_id, generate_patient_id());
    printf("Generated Patient ID: %s\n", new_patient.patient_id);

    printf("Enter patient name: ");
    clear_input_buffer();
    fgets(new_patient.name, MAX_NAME, stdin);
    new_patient.name[strcspn(new_patient.name, "\n")] = 0;

    printf("Enter age: ");
    scanf("%d", &new_patient.age);

    if (!validate_age(new_patient.age)) {
        printf("Invalid age!\n");
        return;
    }

    printf("Enter gender (M/F): ");
    clear_input_buffer();
    scanf("%c", &new_patient.gender);
    new_patient.gender = toupper(new_patient.gender);

    printf("Enter disease description: ");
    clear_input_buffer();
    fgets(new_patient.disease, MAX_DISEASE, stdin);
    new_patient.disease[strcspn(new_patient.disease, "\n")] = 0;

    printf("Enter assigned doctor ID: ");
    scanf("%s", new_patient.doctor_id);

    printf("Enter admission date (DD-MM-YYYY): ");
    scanf("%s", new_patient.admission_date);

    if (!validate_date(new_patient.admission_date)) {
        printf("Invalid date format!\n");
        return;
    }

    new_patient.status = STATUS_ADMITTED;

    // Add to patients array
    patients[patient_count] = new_patient;
    patient_count++;

    save_patients();
    printf("Patient registered successfully!\n");
}

void view_patient_details(void) {
    char patient_id[MAX_ID];

    print_header("VIEW PATIENT DETAILS");
    printf("Enter Patient ID: ");
    scanf("%s", patient_id);

    // Using pointer arithmetic in loop
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
        printf("2. Register New Patient\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_patient_details();
                break;
            case 2:
                patient_registration();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}
