#include "fileio.h"

void save_users(void) {
    FILE *fp = fopen("data/users.dat", "wb");
    if (fp == NULL) {
        printf("Error opening users.dat for writing.\n");
        return;
    }
    fwrite(&user_count, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), user_count, fp);
    fclose(fp);
}

void load_users(void) {
    FILE *fp = fopen("data/users.dat", "rb");
    if (fp == NULL) {
        printf("No existing user data found. Starting fresh.\n");
        user_count = 1;
        users = (User*)malloc(MAX_USERS * sizeof(User));
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        users[0].role = ROLE_ADMIN;
        strcpy(users[0].doctor_id, "");
        save_users();
        return;
    }
    fread(&user_count, sizeof(int), 1, fp);
    users = (User*)malloc(MAX_USERS * sizeof(User));
    fread(users, sizeof(User), user_count, fp);
    fclose(fp);
}

void save_patients(void) {
    FILE *fp = fopen("data/patients.dat", "wb");
    if (fp == NULL) {
        printf("Error opening patients.dat for writing.\n");
        return;
    }
    fwrite(&patient_count, sizeof(int), 1, fp);
    fwrite(patients, sizeof(Patient), patient_count, fp);
    fclose(fp);
}

void load_patients(void) {
    FILE *fp = fopen("data/patients.dat", "rb");
    if (fp == NULL) {
        printf("No existing patient data found. Starting fresh.\n");
        patient_count = 0;
        patients = (Patient*)malloc(MAX_PATIENTS * sizeof(Patient));
        return;
    }
    fread(&patient_count, sizeof(int), 1, fp);
    patients = (Patient*)malloc(MAX_PATIENTS * sizeof(Patient));
    fread(patients, sizeof(Patient), patient_count, fp);
    fclose(fp);
}