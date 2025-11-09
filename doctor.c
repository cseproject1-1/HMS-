#include "doctor.h"
#include "utils.h"
#include "fileio.h"
void doctor_menu(const char* doctor_id) {
    int choice;

    while (1) {
        print_header("DOCTOR MENU");
        printf("1. View My Patients\n");
        printf("2. Update Patient Record\n");
        printf("3. Search Patient\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_my_patients(doctor_id);
                break;
            case 2:
                update_patient_record(doctor_id);
                break;
            case 3:
                search_patient();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void view_my_patients(const char* doctor_id) {
    print_header("MY PATIENTS");

    int found = 0;

    for (int i = 0; i < patient_count; i++) {
        // Using pointer and string comparison
        if (strcmp(patients[i].doctor_id, doctor_id) == 0) {
            printf("Patient ID: %s\n", patients[i].patient_id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %c\n", patients[i].gender);
            printf("Disease: %s\n", patients[i].disease);
            printf("Status: %s\n", status_to_string(patients[i].status));
            printf("Admission Date: %s\n", patients[i].admission_date);
            printf("------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No patients assigned to you.\n");
    }
}

void update_patient_record(const char* doctor_id) {
    char patient_id[MAX_ID];

    printf("Enter Patient ID to update: ");
    scanf("%s", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 0 &&
            strcmp(patients[i].doctor_id, doctor_id) == 0) {

            printf("Current Disease: %s\n", patients[i].disease);
            printf("Enter new disease description: ");
            clear_input_buffer();
            fgets(patients[i].disease, MAX_DISEASE, stdin);
            patients[i].disease[strcspn(patients[i].disease, "\n")] = 0;

            printf("Current Status: %s\n", status_to_string(patients[i].status));
            printf("Select new status (1. Admitted, 2. Discharged, 3. Critical): ");
            int status_choice;
            scanf("%d", &status_choice);

            // Type conversion from int to enum
            patients[i].status = (PatientStatus)(status_choice - 1);

            save_patients();
            printf("Patient record updated successfully!\n");
            return;
        }
    }

    printf("Patient not found or not under your care!\n");
}

void search_patient(void) {
    char search_term[MAX_NAME];
    int search_choice;

    printf("Search by:\n");
    printf("1. Patient ID\n");
    printf("2. Patient Name\n");
    printf("Enter choice: ");
    scanf("%d", &search_choice);

    printf("Enter search term: ");
    scanf("%s", search_term);

    to_upper_case(search_term);

    int found = 0;
    for (int i = 0; i < patient_count; i++) {
        char temp_name[MAX_NAME];
        strcpy(temp_name, patients[i].name);
        to_upper_case(temp_name);

        if ((search_choice == 1 && strcmp(patients[i].patient_id, search_term) == 0) ||
            (search_choice == 2 && strstr(temp_name, search_term) != NULL)) {

            printf("Patient ID: %s\n", patients[i].patient_id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %c\n", patients[i].gender);
            printf("Disease: %s\n", patients[i].disease);
            printf("Doctor ID: %s\n", patients[i].doctor_id);
            printf("Status: %s\n", status_to_string(patients[i].status));
            printf("Admission Date: %s\n", patients[i].admission_date);
            printf("------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No patients found!\n");
    }
}
