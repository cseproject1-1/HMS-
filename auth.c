#include "auth.h"
#include "admin.h"
#include "doctor.h"
#include "patient.h"
#include "fileio.h"
#include "utils.h"

int login_system(void){
    char username[MAX_NAME];
    char password[MAX_NAME];
    print_header("LOGIN");
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
    UserRole role = authenticate_user(username, password);
    if(role==ROLE_ADMIN){
        printf("Welcome Admin!\n");
        admin_menu();
        return 1;
    }
    else if (role == ROLE_DOCTOR)
    {
        for(int i=0;i<user_count;i++){
            if(strcmp(users[i].username,username)==0){
                printf("Welcome Doctor %s!\n",username);
                doctor_menu(users[i].doctor_id);
                return 1;
            }
        }
    }
    else if(role==ROLE_PATIENT)
    {
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
    fgets(new_user.username, sizeof(new_user.username), stdin);
    new_user.username[strcspn(new_user.username, "\n")] = 0;
    if(user_exists(new_user.username)){
        printf("Username already exists!\n");
        return;
    }
    printf("Enter password: ");
    fgets(new_user.password, sizeof(new_user.password), stdin);
    new_user.password[strcspn(new_user.password, "\n")] = 0;
    printf("Select role (1. Doctor, 2. Patient): ");
    int role_choice;
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &role_choice);
    if(role_choice==1){
        new_user.role=ROLE_DOCTOR;
        printf("Enter Doctor ID: ");
        fgets(new_user.doctor_id, sizeof(new_user.doctor_id), stdin);
        new_user.doctor_id[strcspn(new_user.doctor_id, "\n")] = 0;
    }else{
        new_user.role = ROLE_PATIENT;
        strcpy(new_user.doctor_id, "");
    }
    users[user_count] = new_user;
    user_count++;
    save_users();
    printf("Registration successful!\n");
}
UserRole authenticate_user(const char* username, const char* password) {
    for(int i=0;i<user_count;i++){
        if(strcmp(users[i].username,username)==0&&strcmp(users[i].password,password)==0){
            return users[i].role;
        }
    }
return -1;
}
int user_exists(const char* username) {
    for (int i=0;i<user_count;i++){
        if(strcmp(users[i].username,username)==0){
            return 1;
        }
    }
    return 0;
}
