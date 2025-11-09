#include "auth.h"
#include "admin.h"
#include "doctor.h"
#include "patient.h"
#include "fileio.h"
#include "utils.h"

int login_system(void) {
    char username[MAX_NAME];
    char password[MAX_NAME];

    print_header("LOGIN");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    UserRole role = authenticate_user(username, password);

    // Decision making with if-else
    if (role == ROLE_ADMIN) {
        printf("Welcome Admin!\n");
        admin_menu();
        return 1;
    } else if (role == ROLE_DOCTOR) {
        // Find doctor ID
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0) {
                printf("Welcome Doctor %s!\n", username);
                doctor_menu(users[i].doctor_id);
                return 1;
            }
        }
    } else if (role == ROLE_PATIENT) {
        printf("Welcome Patient!\n");
        patient_menu();
        return 1;
    }

    return 0;
}

void register_user(void) {
    User new_user;

    print_header("REGISTER");
    printf("Enter username: ");
    scanf("%s", new_user.username);

    // Check if user exists using string functions
    if (user_exists(new_user.username)) {
        printf("Username already exists!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", new_user.password);

    printf("Select role (1. Doctor, 2. Patient): ");
    int role_choice;
    scanf("%d", &role_choice);

    // Type conversion and decision making
    if (role_choice == 1) {
        new_user.role = ROLE_DOCTOR;
        printf("Enter Doctor ID: ");
        scanf("%s", new_user.doctor_id);
    } else {
        new_user.role = ROLE_PATIENT;
        strcpy(new_user.doctor_id, "");
    }

    // Array usage - add to users array
    users[user_count] = new_user;
    user_count++;

    save_users();
    printf("Registration successful!\n");
}

UserRole authenticate_user(const char* username, const char* password) {
    // Using pointers for string comparison
    const char* admin_user = ADMIN_USERNAME;
    const char* admin_pass = ADMIN_PASSWORD;

    // String comparison using pointers
    if (strcmp(username, admin_user) == 0 && strcmp(password, admin_pass) == 0) {
        return ROLE_ADMIN;
    }

    // Loop through users array
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return users[i].role;
        }
    }

    return -1; // Invalid credentials
}

int user_exists(const char* username) {
    // Using pointer for string comparison in loop
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}
