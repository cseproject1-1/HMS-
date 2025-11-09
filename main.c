#include "common.h"
#include "auth.h"
#include "fileio.h"
#include "utils.h"

User* users = NULL;
Patient* patients = NULL;
int user_count = 0;
int patient_count = 0;

int main(int argc, char* argv[]) {
    printf("Hospital Management System\n");
    if (argc > 1) {
        printf("Command line parameter: %s\n", argv[1]);
    }
    load_users();
    load_patients();
    int choice;
    while (1) {
        print_header("MAIN MENU");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
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
