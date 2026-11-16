#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;
    while (1) {
        printf("\n========================================\n");
        printf("    STUDENT RECORD MANAGEMENT SYSTEM    \n");
        printf("========================================\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Student Records\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student Record\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("\nExiting program. Good luck with your submission!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct Student s;
    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name); // Reads string with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("\n[Success] Student record added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo student records found yet!\n");
        return;
    }
    struct Student s;
    printf("\n----------------------------------------------------\n");
    printf("%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("----------------------------------------------------\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%-10d %-30s %-10.2f\n", s.rollNo, s.name, s.marks);
    }
    printf("----------------------------------------------------\n");
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo student records found yet!\n");
        return;
    }
    int roll, found = 0;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    struct Student s;
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            printf("\n[Record Found]\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("\n[Not Found] Student with Roll Number %d does not exist.\n", roll);
    }
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo student records found yet!\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error opening temporary file!\n");
        fclose(fp);
        return;
    }
    int roll, found = 0;
    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    struct Student s;
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("\n[Success] Student record deleted successfully!\n");
    } else {
        printf("\n[Not Found] Student with Roll Number %d does not exist.\n", roll);
    }
}