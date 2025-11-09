#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_ID 10
#define MAX_DISEASE 100
#define MAX_USERS 100
#define MAX_PATIENTS 500

typedef enum {
    ROLE_ADMIN,
    ROLE_DOCTOR,
    ROLE_PATIENT
} UserRole;

typedef enum {
    STATUS_ADMITTED,
    STATUS_DISCHARGED,
    STATUS_CRITICAL
} PatientStatus;

typedef struct {
    char username[MAX_NAME];
    char password[MAX_NAME];
    UserRole role;
    char doctor_id[MAX_ID];
} User;

typedef struct {
    char patient_id[MAX_ID];
    char name[MAX_NAME];
    int age;
    char gender;
    char disease[MAX_DISEASE];
    char doctor_id[MAX_ID];
    PatientStatus status;
    char admission_date[11];
} Patient;

extern User* users;
extern Patient* patients;
extern int user_count;
extern int patient_count;

#endif
