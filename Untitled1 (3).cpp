
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

/* ---------- STACK IMPLEMENTATION USING ARRAY ----------- */
struct Student stack[MAX];
int top = -1;

/* ----------- STACK FUNCTIONS -------------- */

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

void push(struct Student s) {
    if (isFull()) {
        printf("Stack Full! Cannot add more students.\n");
        return;
    }
    stack[++top] = s;
}

void pop() {
    if (isEmpty()) {
        printf("Stack Empty! No student to delete.\n");
        return;
    }
    top--;
}

/* --------- SAVE STACK TO FILE ---------- */
void saveToFile() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    for (int i = 0; i <= top; i++) {
        fprintf(fp, "%d %s %.2f\n", stack[i].roll, stack[i].name, stack[i].marks);
    }
    fclose(fp);
}

/* --------- LOAD STACK FROM FILE -------- */
void loadFromFile() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student s;
    top = -1;

    if (fp == NULL) return;

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        push(s);
    }
    fclose(fp);
}

/* -------- LOGIN SYSTEM ---------- */
int loginSystem() {
    FILE *fp = fopen(CREDENTIAL_FILE, "r");

    if (fp == NULL) {
        fp = fopen(CREDENTIAL_FILE, "w");
        fprintf(fp, "admin admin123\n");
        fclose(fp);

        fp = fopen(CREDENTIAL_FILE, "r");
    }

    char savedUser[50], savedPass[50];
    fscanf(fp, "%s %s", savedUser, savedPass);
    fclose(fp);

    char user[50], pass[50];
    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    return (strcmp(user, savedUser) == 0 && strcmp(pass, savedPass) == 0);
}

/* ---------- ADD STUDENT (PUSH) ------------ */

void addStudent() {
    loadFromFile();

    struct Student s;
    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    getchar();
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    push(s);
    saveToFile();

    printf("Student Added Successfully!\n");
}

/* -------- DISPLAY STACK ---------- */

void displayStudents() {
    loadFromFile();

    if (isEmpty()) {
        printf("\nNo Students Found.\n");
        return;
    }

    printf("\n----- STUDENT STACK -----\n");
    for (int i = 0; i <= top; i++) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",
               stack[i].roll, stack[i].name, stack[i].marks);
    }
}

/* ---------- SEARCH STUDENT --------- */

void searchStudent() {
    loadFromFile();

    if (isEmpty()) {
        printf("No Records Available.\n");
        return;
    }

    int roll;
    printf("Enter Roll No to Search: ");
    scanf("%d", &roll);

    for (int i = 0; i <= top; i++) {
        if (stack[i].roll == roll) {
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
                   stack[i].roll, stack[i].name, stack[i].marks);
            return;
        }
    }

    printf("Student Not Found!\n");
}

/* ---------- DELETE STUDENT (POP) ---------- */

void deleteStudent() {
    loadFromFile();

    if (isEmpty()) {
        printf("Stack Empty! No student to delete.\n");
        return;
    }

    printf("Deleting Top Student (LIFO)...\n");
    pop();
    saveToFile();

    printf("Top Student Deleted Successfully!\n");
}

/* -------------- UPDATE STUDENT ---------------- */

void updateStudent() {
    loadFromFile();

    int roll, found = 0;
    printf("Enter Roll No to Update: ");
    scanf("%d", &roll);

    for (int i = 0; i <= top; i++) {
        if (stack[i].roll == roll) {

            printf("Enter New Name: ");
            getchar();
            fgets(stack[i].name, 50, stdin);
            stack[i].name[strcspn(stack[i].name, "\n")] = 0;

            printf("Enter New Marks: ");
            scanf("%f", &stack[i].marks);

            saveToFile();
            found = 1;
            break;
        }
    }

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Student Not Found!\n");
}

/* ------------ MAIN MENU ---------- */

int main() {
    if (!loginSystem()) {
        printf("Login Failed. Exiting...\n");
        return 0;
    }

    int choice;

    do {
        printf("\n===== STACK-BASED STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student (PUSH)\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student (POP)\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid Choice! Try Again.\n");
        }
    } while (choice != 6);

    return 0;
}
