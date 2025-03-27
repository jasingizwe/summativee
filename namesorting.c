#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

void sortNames(char names[][NAME_LENGTH], int count, int (*compare)(const char*, const char*));
int compareAscending(const char *a, const char *b);
int compareDescending(const char *a, const char *b);
int countNames(char names[][NAME_LENGTH], int count);
void executeSorting();
void executeCounting();


void (*functions[])(void) = {executeSorting, executeCounting};

// Function to sort names 
void sortNames(char names[][NAME_LENGTH], int count, int (*compare)(const char*, const char*)) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (compare(names[i], names[j]) > 0) {
                char temp[NAME_LENGTH];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
}


int compareAscending(const char *a, const char *b) {
    return strcmp(a, b);
}

int compareDescending(const char *a, const char *b) {
    return strcmp(b, a);
}

// Function to count names
int countNames(char names[][NAME_LENGTH], int count) {
    return count;
}


void executeSorting() {
    char names[MAX_STUDENTS][NAME_LENGTH] = {
        "Aubin Saiba", "Collette Joie", "Luca Davis", "Muzira Kellia", "Keny Cyusa"
    };
    int studentCount = 5;

    char order[5];
    printf("Enter sorting order (asc/desc): ");
    scanf("%s", order);

    if (strcmp(order, "asc") == 0) {
        sortNames(names, studentCount, compareAscending);
    } else if (strcmp(order, "desc") == 0) {
        sortNames(names, studentCount, compareDescending);
    } else {
        printf("Invalid sorting order.\n");
        return;
    }

    printf("Sorted names:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%s\n", names[i]);
    }
}


void executeCounting() {
    char names[MAX_STUDENTS][NAME_LENGTH] = {
        "Aubin Saiba", "Collette Joie", "Luca Davis", "Muzira Kellia", "Keny Cyusa"
    };
    int studentCount = 5;

    printf("Total number of students: %d\n", countNames(names, studentCount));
}


int main() {
    int choice;
    
    printf("Select an option:\n");
    printf("1 - Sort students names\n");
    printf("2 - Count students names\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        functions[choice - 1]();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
