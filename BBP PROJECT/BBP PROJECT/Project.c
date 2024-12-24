#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include for tolower function

#define MAX_CATEGORIES 10
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    float budget;
    float expenses;
} Category;

void setBudget(Category categories[], int *count);
void addExpense(Category categories[], int count);
void analyzeBudget(const Category categories[], int count);
void saveToFile(const Category categories[], int count);
void loadFromFile(Category categories[], int *count);
void searchCategory(const Category categories[], int count);
void editCategory(Category categories[], int count);
void toLowerCase(char str[]);

int main() {
    Category categories[MAX_CATEGORIES];
    int count = 0, choice;

    loadFromFile(categories, &count);

    while (1) {
        printf("\nPersonal Budget Planner\n");
        printf("1. Set Budget\n2. Add Expense\n3. Analyze Budget\n4. Search Category\n");
        printf("5. Edit Category\n6. Save and Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: setBudget(categories, &count); break;
            case 2: addExpense(categories, count); break;
            case 3: analyzeBudget(categories, count); break;
            case 4: searchCategory(categories, count); break;
            case 5: editCategory(categories, count); break;
            case 6: saveToFile(categories, count); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void setBudget(Category categories[], int *count) {
    if (*count >= MAX_CATEGORIES) {
        printf("Maximum categories reached!\n");
        return;
    }

    char newCategoryName[MAX_NAME_LEN];
    printf("Enter category name: ");
    scanf("%s", newCategoryName);

    // Convert new category name to lowercase
    char newCategoryNameLower[MAX_NAME_LEN];
    strcpy(newCategoryNameLower, newCategoryName);
    toLowerCase(newCategoryNameLower);

    // Check for duplicate category names (case-insensitive)
    for (int i = 0; i < *count; i++) {
        char existingCategoryLower[MAX_NAME_LEN];
        strcpy(existingCategoryLower, categories[i].name);
        toLowerCase(existingCategoryLower);

        if (strcmp(existingCategoryLower, newCategoryNameLower) == 0) {
            printf("Error: A category with the name '%s' already exists (case-insensitive match).\n", categories[i].name);
            return;
        }
    }

    // Add new category
    strcpy(categories[*count].name, newCategoryName);
    printf("Enter budget for %s: ", categories[*count].name);
    scanf("%f", &categories[*count].budget);
    categories[*count].expenses = 0.0;
    (*count)++;
    printf("Category '%s' added successfully with a budget of %.2f!\n", newCategoryName, categories[*count - 1].budget);
}

void addExpense(Category categories[], int count) {
    char name[MAX_NAME_LEN];
    float expense;

    printf("Enter category name: ");
    scanf("%s", name);

    // Convert input to lowercase for comparison
    char nameLower[MAX_NAME_LEN];
    strcpy(nameLower, name);
    toLowerCase(nameLower);

    for (int i = 0; i < count; i++) {
        char existingCategoryLower[MAX_NAME_LEN];
        strcpy(existingCategoryLower, categories[i].name);
        toLowerCase(existingCategoryLower);

        if (strcmp(existingCategoryLower, nameLower) == 0) {
            printf("Enter expense amount: ");
            scanf("%f", &expense);
            categories[i].expenses += expense;
            printf("Expense added successfully!\n");
            return;
        }
    }
    printf("Category not found!\n");
}

void analyzeBudget(const Category categories[], int count) {
    if (count == 0) {
        printf("No categories available for analysis!\n");
        return;
    }

    printf("\n%-20s %-10s %-10s %-10s\n", "Category", "Budget", "Spent", "Remaining");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10.2f %-10.2f %-10.2f\n", 
               categories[i].name, categories[i].budget, categories[i].expenses, 
               categories[i].budget - categories[i].expenses);
    }
}

void saveToFile(const Category categories[], int count) {
    FILE *file = fopen("budget_data.txt", "w");
    if (!file) {
        printf("Error saving to file!\n");
        return;
    }

    // Write a header to explain the data structure
    fprintf(file, "Personal Budget Planner Data\n");
    fprintf(file, "=============================\n");
    fprintf(file, "Total Categories: %d\n\n", count);
    fprintf(file, "Category Name       Budget      Expenses     Remaining\n");
    fprintf(file, "--------------------------------------------------------\n");

    // Write category details in a structured format
    for (int i = 0; i < count; i++) {
        float remaining = categories[i].budget - categories[i].expenses;
        fprintf(file, "%-20s %-10.2f %-10.2f %-10.2f\n", 
                categories[i].name, categories[i].budget, categories[i].expenses, remaining);
    }

    fclose(file);
    printf("Data saved successfully to 'budget_data.txt'.\n");
}


void loadFromFile(Category categories[], int *count) {
    FILE *file = fopen("budget_data.txt", "r");
    if (!file) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    fscanf(file, "%d", count);
    for (int i = 0; i < *count; i++) {
        fscanf(file, "%s %f %f", categories[i].name, &categories[i].budget, &categories[i].expenses);
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

void searchCategory(const Category categories[], int count) {
    if (count == 0) {
        printf("No categories available to search!\n");
        return;
    }

    char categoryName[MAX_NAME_LEN];
    printf("Enter category name to search: ");
    scanf("%s", categoryName);

    // Convert the input category name to lowercase
    char categoryNameLower[MAX_NAME_LEN];
    strcpy(categoryNameLower, categoryName);
    toLowerCase(categoryNameLower);

    int found = 0;
    for (int i = 0; i < count; i++) {
        char existingCategoryLower[MAX_NAME_LEN];
        strcpy(existingCategoryLower, categories[i].name);
        toLowerCase(existingCategoryLower);

        if (strcmp(existingCategoryLower, categoryNameLower) == 0) {
            printf("\nCategory Found:\n");
            printf("Name: %s\n", categories[i].name);
            printf("Budget: %.2f\n", categories[i].budget);
            printf("Expenses: %.2f\n", categories[i].expenses);
            printf("Remaining: %.2f\n", categories[i].budget - categories[i].expenses);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Category not found!\n");
    }
}

void editCategory(Category categories[], int count) {
    char name[MAX_NAME_LEN];
    printf("Enter category name to edit: ");
    scanf("%s", name);

    // Convert input to lowercase for comparison
    char nameLower[MAX_NAME_LEN];
    strcpy(nameLower, name);
    toLowerCase(nameLower);

    for (int i = 0; i < count; i++) {
        char existingCategoryLower[MAX_NAME_LEN];
        strcpy(existingCategoryLower, categories[i].name);
        toLowerCase(existingCategoryLower);

        if (strcmp(existingCategoryLower, nameLower) == 0) {
            printf("Enter new budget (or -1 to keep current): ");
            float newBudget;
            scanf("%f", &newBudget);
            if (newBudget >= 0) categories[i].budget = newBudget;
            printf("Category updated successfully.\n");
            return;
        }
    }
    printf("Category not found!\n");
}
