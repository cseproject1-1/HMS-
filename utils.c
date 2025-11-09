#include "utils.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_header(const char* title) {
    printf("\n");
    printf("========================================\n");
    printf("    %s\n", title);
    printf("========================================\n");
}

int validate_date(const char* date) {
    // Simple date validation (DD-MM-YYYY format)
    if (strlen(date) != 10) return 0;
    if (date[2] != '-' || date[5] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return 0;
    }

    return 1;
}

int validate_age(int age) {
    return (age > 0 && age < 150);
}

char* role_to_string(UserRole role) {
    switch (role) {
        case ROLE_ADMIN: return "Admin";
        case ROLE_DOCTOR: return "Doctor";
        case ROLE_PATIENT: return "Patient";
        default: return "Unknown";
    }
}

char* status_to_string(PatientStatus status) {
    switch (status) {
        case STATUS_ADMITTED: return "Admitted";
        case STATUS_DISCHARGED: return "Discharged";
        case STATUS_CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

void to_upper_case(char* str) {
    // Using pointer arithmetic
    char* ptr = str;
    while (*ptr) {
        *ptr = toupper(*ptr);
        ptr++;
    }
}

char* generate_patient_id(void) {
    static char id[MAX_ID];
    // Simple ID generation - in real system, this would be more sophisticated
    sprintf(id, "P%04d", patient_count + 1);
    return id;
}
