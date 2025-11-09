#ifndef AUTH_H
#define AUTH_H

#include "common.h"

// Function declarations
int login_system(void);
void register_user(void);
UserRole authenticate_user(const char* username, const char* password);
int user_exists(const char* username);

#endif
