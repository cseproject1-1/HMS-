#include "fileio.h"
#include "utils.h"

void load_users(void) {
    FILE* file = fopen("data/users.dat", "rb");
    if (file == NULL) {
        printf("No existing user data found. Starting fresh.\n");
        return;
    }

    user_count = fread(users, sizeof(User), MAX_USERS, file);
    fclose(file);

    printf("Loaded %d users\n", user_count);
}

void save_users(void) {
    FILE* file = fopen("data/users.dat", "wb");
    if (file == NULL) {
        printf("Error saving user data!\n");
        return;
    }

    fwrite(users, sizeof(User), user_count, file);
    fclose(file);
}

void load_patients(void) {
    FILE* file = fopen("data/patients.dat", "rb");
    if (file == NULL) {
        printf("No existing patient data found. Starting fresh.\n");
        return;
    }

    patient_count = fread(patients, sizeof(Patient), MAX_PATIENTS, file);
    fclose(file);

    printf("Loaded %d patients\n", patient_count);
}

void save_patients(void) {
    FILE* file = fopen("data/patients.dat", "wb");
    if (file == NULL) {
        printf("Error saving patient data!\n");
        return;
    }

    fwrite(patients, sizeof(Patient), patient_count, file);
    fclose(file);
}

void initialize_files(void) {
    // Create data directory if it doesn't exist
    system("mkdir -p data");
}
