#ifndef UTILS_H
#define UTILS_H

#include "common.h"

// Function declarations
void clear_input_buffer(void);
void print_header(const char* title);
int validate_date(const char* date);
int validate_age(int age);
char* role_to_string(UserRole role);
char* status_to_string(PatientStatus status);
void to_upper_case(char* str);
char* generate_patient_id(void);

#endif
