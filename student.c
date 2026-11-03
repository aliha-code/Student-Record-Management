
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *head = NULL;

// Save records to file
void saveRecords() {
    FILE *fp = fopen("students.dat", "w");
    struct Student *temp = head;

    if (fp == NULL) {
        printf("Unable to save records!\n");
        return;
    }

    while (temp != NULL) {
        fprintf(fp, "%d|%s|%.2f\n",
                temp->rollNo, temp->name, temp->marks);
        temp = temp->next;
    }

    fclose(fp);
}

// Load records from file
void loadRecords() {
    FILE *fp = fopen("students.dat", "r");

    if (fp == NULL)
        return;

    int roll;
    char name[50];
    float marks;

    while (fscanf(fp, "%d|%49[^|]|%f",
                  &roll, name, &marks) == 3) {

        struct Student *newStudent = malloc(sizeof(struct Student));

        if (newStudent == NULL)
            break;

        newStudent->rollNo = roll;
        strcpy(newStudent->name, name);
        newStudent->marks = marks;
        newStudent->next = NULL;

        if (head == NULL) {
            head = newStudent;
        } else {
            struct Student *temp = head;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newStudent;
        }
    }

    fclose(fp);
}

// Add Student
void addStudent() {
    struct Student *newStudent, *temp;

    newStudent = malloc(sizeof(struct Student));

    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &newStudent->rollNo);

    temp = head;

    while (temp != NULL) {
        if (temp->rollNo == newStudent->rollNo) {
            printf("Roll number already exists!\n");
            free(newStudent);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", newStudent->name);

    printf("Enter Marks: ");
    scanf("%f", &newStudent->marks);

    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
    } else {
        temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newStudent;
    }

    saveRecords();
    printf("Student added successfully!\n");
}

// Display Students
void displayStudents() {
    struct Student *temp = head;

    if (head == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("%-12s %-20s %-8s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------\n");

    while (temp != NULL) {
        printf("%-12d %-20s %-8.2f\n",
               temp->rollNo, temp->name, temp->marks);
        temp = temp->next;
    }

    printf("---------------------------------------------\n");
}

// Search Student
void searchStudent() {
    int roll;
    struct Student *temp = head;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            printf("\nStudent Found!\n");
            printf("Roll Number: %d\n", temp->rollNo);
            printf("Name: %s\n", temp->name);
            printf("Marks: %.2f\n", temp->marks);
            return;
        }

        temp = temp->next;
    }

    printf("Student not found!\n");
}

// Update Student
void updateStudent() {
    int roll;
    struct Student *temp = head;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", temp->name);

            printf("Enter New Marks: ");
            scanf("%f", &temp->marks);

            saveRecords();
            printf("Student updated successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Student not found!\n");
}

// Delete Student
void deleteStudent() {
    int roll;
    struct Student *temp = head;
    struct Student *prev = NULL;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (temp != NULL && temp->rollNo != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found!\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    saveRecords();

    printf("Student deleted successfully!\n");
}

// Main Function
int main() {
    int choice;

    loadRecords();

    while (1) {
        printf("\n===== STUDENT RECORD MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
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
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Thank you for using the system!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}