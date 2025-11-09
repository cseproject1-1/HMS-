#include "common.h"
#include "auth.h"
#include "fileio.h"
#include "utils.h"

// Global variables definition
User* users = NULL;
Patient* patients = NULL;
int user_count = 0;
int patient_count = 0;

int main(int argc, char* argv[]) {
    // Command line parameters demonstration
    printf("Hospital Management System\n");
    if (argc > 1) {
        printf("Command line parameter: %s\n", argv[1]);
    }

    // Dynamic memory allocation for users and patients
    users = (User*)malloc(MAX_USERS * sizeof(User));
    patients = (Patient*)malloc(MAX_PATIENTS * sizeof(Patient));

    if (users == NULL || patients == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize files and load data
    initialize_files();
    load_users();
    load_patients();

    int choice;

    // Main program loop
    while (1) {
        print_header("MAIN MENU");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        // Decision making with switch case
        switch (choice) {
            case 1:
                if (login_system()) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed!\n");
                }
                break;

            case 2:
                register_user();
                break;

            case 3:
                save_users();
                save_patients();
                free(users);
                free(patients);
                printf("Thank you for using Hospital Management System!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
