#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "student_records.txt"

/* in case of multiple marks
   float marks2;
   float marks3;
   float average;

*/

/*Data Storage
and other declarations
*/




typedef struct {
   char  name[50];
   int   roll;
   float marks;
} Student;

Student* students = NULL;
int student_count = 0;

float cutoff = 40;



/* Should grades be part of the struct
and show up after inputing or is it a separate function
*/

void greet_user();
void add_student();
void display_students();
void modify_student();
void delete_student();
void find_student();
void calculate_average();
void sort_students();
void save_to_file();
void load_from_file();
void clear_memory();








#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()


//What does the User want to do
{
    load_from_file();
    greet_user();

      int task;
    do {
        printf("\n--- Student Record Management Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Modify Student Record\n");
        printf("4. Delete Student Record\n");
        printf("5. Search Student by Roll Number\n");
        printf("6. Calculate Average Marks\n");
        printf("7. Sort Students by Marks\n");
        printf("8. Save and Exit\n");
        printf("Enter the task you would like to perform: ");
        scanf("%d", &task);

        switch (task) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                modify_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                find_student();
                break;
            case 6:
                calculate_average();
                break;
            case 7:
                sort_students(); break;
            case 8:
                save_to_file();
                break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (task != 8);

    clear_memory();
    return 0;
}



/*
 Welcome Message
*/



void greet_user() {

char username[100];

printf("Welcome to the Student Record System \n");
printf("What is your name, please? \n");
scanf("%s", username);
printf("Greetings, %s \n", username);
}



/*
Input Array of Student Structs
this is where calloc, free & realloc are supposed to be
*/


void add_student() {
    student_count++;
    students = realloc(students, student_count * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter Student Name: ");
    scanf("%s", students[student_count - 1].name);
    printf("Enter Roll Number: ");
    scanf("%d", &students[student_count - 1].roll);
    printf("Enter Marks: ");
    scanf("%f", &students[student_count - 1].marks);

    printf("Student added successfully!\n");
}

/*
Delete Record
*/

void delete_student() {
    int roll_number;
    printf("Enter Roll Number of student to delete: ");
    scanf("%d", &roll_number);

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll_number) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            students = realloc(students, student_count * sizeof(Student));
            printf("Student record deleted!\n");
            return;
        }
    }
    printf("Student not found.\n");
}


/*
Update Instance within Record
*/
void modify_student() {
    int roll_number;
    printf("Enter Roll Number of student to modify: ");
    scanf("%d", &roll_number);

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll_number) {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            printf("Student record updated!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

/*
Print Whole Array
Add ability to sort by asc or desc marks somewhere
Are there multiple marks T_T
Maybe pass-fail is here instead
*/


void display_students() {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        printf("\nName: %s, Roll Number: %d, Marks: %.2f", students[i].name, students[i].roll, students[i].marks);
        if (students[i].marks >= cutoff) {
            printf(" - Passed\n");
        } else {
            printf(" - Failed\n");
        }
    }
}



/*
Search by Roll Number Part
*/

void find_student() {
    int roll_number;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll_number);

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll_number) {
            printf("Name: %s, Roll Number: %d, Marks: %.2f\n", students[i].name, students[i].roll, students[i].marks);
            return;
        }
    }
    printf("Student not found.\n");
}


/*
Average Marks
*/

void calculate_average() {
    if (student_count == 0) {
        printf("No student records available to calculate average.\n");
        return;
    }
    float sum = 0;
    for (int i = 0; i < student_count; i++) {
        sum += students[i].marks;
    }
    printf("Average Marks: %.2f\n", sum / student_count);
}

/* Sort by Marks
*/

void sort_students() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].marks > students[j].marks) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Students sorted by marks!\n");
}



/* Save student record to file
*/
void save_to_file() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].roll, students[i].marks);
    }
    fclose(file);
    printf("Records saved to file.\n");
}


/* Load students from file
*/
void load_from_file() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        return;
    }
    while (!feof(file)) {
        Student student;
        if (fscanf(file, "%s %d %f", student.name, &student.roll, &student.marks) == 3) {
            student_count++;
            students = realloc(students, student_count * sizeof(Student));
            students[student_count - 1] = student;
        }
    }
    fclose(file);
}


/* Free allocated memory
*/
void clear_memory() {
    free(students);
}

