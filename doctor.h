#ifndef DOCTOR_H
#define DOCTOR_H

#include "common.h"

void doctor_menu(const char* doctor_id);
void view_my_patients(const char* doctor_id);
void update_patient_record(const char* doctor_id);
void search_patient(void);

#endif
