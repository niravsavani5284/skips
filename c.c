#include <stdio.h>

#define NUM_SUBJECTS 5
#define NUM_STUDENTS 10

// Define the structure for Student data
struct Student {
    int rollNumber;               // Roll number of the student
    char name[20];                // Name of the student
    float marks[NUM_SUBJECTS];    // Marks in 5 subjects
    float totalMarks;             // Total marks (sum of the 5 subjects)
    float percentage;             // Percentage (totalMarks / 500 * 100)
};

// Function to input student data
void inputStudentData(struct Student* s) {
    printf("Enter roll number: ");
    scanf("%d", &s->rollNumber);

    printf("Enter name: ");
    getchar();  // To consume newline character left by scanf
    fgets(s->name, 20, stdin);
   // s->name[strcspn(s->name, "\n")] = '\0';  // Remove newline character from name

    // Input marks for 5 subjects
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter marks for subject %d: ", i + 1);
        scanf("%f", &s->marks[i]);
    }
}

// Function to calculate total marks and percentage
void calculateMarks(struct Student* s) {
    s->totalMarks = 0;

    // Calculate total marks by summing up marks of all subjects
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        s->totalMarks += s->marks[i];
    }

    // Calculate percentage
    s->percentage = (s->totalMarks / (NUM_SUBJECTS * 100)) * 100;
}

// Function to print student data
void printStudentData(struct Student s) {
    printf("\nRoll Number: %d\n", s.rollNumber);
    printf("Name: %s\n", s.name);
    printf("Marks: ");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%.2f ", s.marks[i]);
    }
    printf("\nTotal Marks: %.2f\n", s.totalMarks);
    printf("Percentage: %.2f%%\n", s.percentage);
}

int main() {
    struct Student students[NUM_STUDENTS];  // Array of 10 students

    // Input data for all students
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        inputStudentData(&students[i]);
    }

    // Calculate total marks and percentage for each student
    for (int i = 0; i < NUM_STUDENTS; i++) {
        calculateMarks(&students[i]);
    }

    // Print data for all students
    printf("\nDisplaying student data:\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("\nStudent %d:\n", i + 1);
        printStudentData(students[i]);
    }

    return 0;
}
