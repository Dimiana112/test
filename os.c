#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void show_menu();
void list_files(int role);
void change_permissions(int role);
void create_delete_files(int role);
void copy_files(int role);
void move_files(int role);
void view_file_content(int role);
void find_files(int role);
void execute_option(int choice, int role);

int main() {
    int role;
    int choice;

    // Display initial role selection
    printf("Welcome to the University File Management System\n");
    printf("Select your role:\n");
    printf("1. Dean\n");
    printf("2. Professor\n");
    printf("3. Student\n");
    printf("Enter your choice: ");
    scanf("%d", &role);

    if (role < 1 || role > 3) {
        printf("Invalid role!\n");
        return 1;
    }

    // Main loop for the menu
    while (1) {
        show_menu(role);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 8) {
            printf("Exiting the system...\n");
            break;
        }

        execute_option(choice, role);
    }

    return 0;
}

// Function to display menu based on the role
void show_menu(int role) {
    printf("\n----- Menu -----\n");
    printf("1. List files/directories\n");
    printf("2. Change permissions\n");
    printf("3. Create/Delete files/directories\n");
    printf("4. Copy files/directories\n");
    printf("5. Move files/directories\n");
    printf("6. View file content\n");
    printf("7. Find files/directories\n");
    printf("8. Exit\n");

    if (role == 1) {
        printf("\n[Dean] Full access to all operations.\n");
    } else if (role == 2) {
        printf("\n[Professor] Limited access to directories.\n");
    } else if (role == 3) {
        printf("\n[Student] Minimal access, only own files.\n");
    }
}

// Function to execute the selected option
void execute_option(int choice, int role) {
    switch (choice) {
        case 1:
            list_files(role);
            break;
        case 2:
            change_permissions(role);
            break;
        case 3:
            create_delete_files(role);
            break;
        case 4:
            copy_files(role);
            break;
        case 5:
            move_files(role);
            break;
        case 6:
            view_file_content(role);
            break;
        case 7:
            find_files(role);
            break;
        case 8:
            break;
        default:
            printf("Invalid choice. Try again.\n");
    }
}

// Function to list files/directories
void list_files(int role) {
    char dir[100];

    if (role == 1) { // Dean
        printf("You have full access to all files in /university.\n");
        system("ls /university");
    } else if (role == 2) { // Professor
        printf("You can access the /professors directory and view files in /students.\n");
        system("ls /university/professors");
        system("ls /university/students");
    } else if (role == 3) { // Student
        printf("You can access your own files in the /students directory.\n");
        system("ls /university/students");
    }
}

// Function to change permissions
void change_permissions(int role) {
    char dir[100], permission[10];
    if (role == 1) { // Dean
        printf("Enter the directory (e.g., /university/dean): ");
        scanf("%s", dir);
        printf("Enter the permission (e.g., 755, 644): ");
        scanf("%s", permission);
        char command[200];
        snprintf(command, sizeof(command), "chmod %s %s", permission, dir);
        system(command);
        printf("Permissions changed for %s.\n", dir);
    } else {
        printf("You do not have permission to change file permissions.\n");
    }
}

// Function to create/delete files/directories
void create_delete_files(int role) {
    char dir[100];
    if (role == 1 || role == 2) { // Dean and Professors
        printf("Enter the directory to create/delete: ");
        scanf("%s", dir);
        printf("Enter command (create or delete): ");
        char command[200];
        char action[10];
        scanf("%s", action);
        if (strcmp(action, "create") == 0) {
            snprintf(command, sizeof(command), "mkdir %s", dir);
        } else if (strcmp(action, "delete") == 0) {
            snprintf(command, sizeof(command), "rmdir %s", dir);
        }
        system(command);
    } else {
        printf("Students can only create files in their own directories.\n");
    }
}

// Function to copy files/directories
void copy_files(int role) {
    char source[100], destination[100];
    if (role == 1 || role == 2) { // Dean and Professors
        printf("Enter source file/directory: ");
        scanf("%s", source);
        printf("Enter destination directory: ");
        scanf("%s", destination);
        char command[200];
        snprintf(command, sizeof(command), "cp -r %s %s", source, destination);
        system(command);
    } else if (role == 3) { // Student
        printf("Enter source file (within your own directory): ");
        scanf("%s", source);
        printf("Enter destination directory (within your own directory): ");
        scanf("%s", destination);
        char command[200];
        snprintf(command, sizeof(command), "cp %s %s", source, destination);
        system(command);
    }
}

// Function to move files/directories
void move_files(int role) {
    char source[100], destination[100];
    if (role == 1 || role == 2) { // Dean and Professors
        printf("Enter source file/directory: ");
        scanf("%s", source);
        printf("Enter destination directory: ");
        scanf("%s", destination);
        char command[200];
        snprintf(command, sizeof(command), "mv %s %s", source, destination);
        system(command);
    } else if (role == 3) { // Student
        printf("Enter source file (within your own directory): ");
        scanf("%s", source);
        printf("Enter destination directory (within your own directory): ");
        scanf("%s", destination);
        char command[200];
        snprintf(command, sizeof(command), "mv %s %s", source, destination);
        system(command);
    }
}

// Function to view file content using cat, head, or tail
void view_file_content(int role) {
    char filename[100];
    if (role == 1 || role == 2 || role == 3) { // All roles can view content
        printf("Enter filename to view: ");
        scanf("%s", filename);
        printf("View content with cat, head, or tail: ");
        char choice[10];
        scanf("%s", choice);
        if (strcmp(choice, "cat") == 0) {
            char command[200];
            snprintf(command, sizeof(command), "cat %s", filename);
            system(command);
        } else if (strcmp(choice, "head") == 0) {
            char command[200];
            snprintf(command, sizeof(command), "head %s", filename);
            system(command);
        } else if (strcmp(choice, "tail") == 0) {
            char command[200];
            snprintf(command, sizeof(command), "tail %s", filename);
            system(command);
        }
    }
}

// Function to find files/directories
void find_files(int role) {
    char search_term[100];
    if (role == 1 || role == 2) { // Dean and Professor
        printf("Enter search term: ");
        scanf("%s", search_term);
        char command[200];
        snprintf(command, sizeof(command), "find /university -name '%s'", search_term);
        system(command);
    } else if (role == 3) { // Student
        printf("Enter search term: ");
        scanf("%s", search_term);
        char command[200];
        snprintf(command, sizeof(command), "find /students -name '%s'", search_term);
        system(command);
    } else {
        printf("Invalid role\n");
    }
}
