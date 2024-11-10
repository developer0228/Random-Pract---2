// 2) Write a program to implement an address book with options given below: a) Create 
// address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify 
// a record. f) Exit

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "address_book.dat"
#define MAX_NAME_LEN 100
#define MAX_DETAIL_LEN 200

typedef struct {
    char name[MAX_NAME_LEN];
    char details[MAX_DETAIL_LEN];
} Record;

void create_address_book() {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fclose(file);
        printf("Address book created.\n");
    }
}

void view_address_book() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        Record r;
        while (fread(&r, sizeof(Record), 1, file))
            printf("Name: %s\nDetails: %s\n\n", r.name, r.details);
        fclose(file);
    } else {
        printf("Address book is empty.\n");
    }
}

void insert_record() {
    FILE *file = fopen(FILENAME, "ab");
    if (file) {
        Record r;
        printf("Enter name: "); getchar(); fgets(r.name, MAX_NAME_LEN, stdin);
        printf("Enter details: "); fgets(r.details, MAX_DETAIL_LEN, stdin);
        r.name[strcspn(r.name, "\n")] = '\0';
        r.details[strcspn(r.details, "\n")] = '\0';
        fwrite(&r, sizeof(Record), 1, file);
        fclose(file);
        printf("Record added.\n");
    }
}

void delete_record() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (file && temp) {
        Record r;
        char name[MAX_NAME_LEN];
        int found = 0;
        printf("Enter name to delete: "); getchar(); fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = '\0';
        while (fread(&r, sizeof(Record), 1, file)) {
            if (strcmp(r.name, name) != 0)
                fwrite(&r, sizeof(Record), 1, temp);
            else found = 1;
        }
        fclose(file); fclose(temp);
        if (found) {
            remove(FILENAME);
            rename("temp.dat", FILENAME);
            printf("Record deleted.\n");
        } else {
            printf("Record not found.\n");
            remove("temp.dat");
        }
    }
}

void modify_record() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (file && temp) {
        Record r;
        char name[MAX_NAME_LEN];
        int found = 0;
        printf("Enter name to modify: "); getchar(); fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = '\0';
        while (fread(&r, sizeof(Record), 1, file)) {
            if (strcmp(r.name, name) == 0) {
                printf("Enter new details: ");
                fgets(r.details, MAX_DETAIL_LEN, stdin);
                r.details[strcspn(r.details, "\n")] = '\0';
                found = 1;
            }
            fwrite(&r, sizeof(Record), 1, temp);
        }
        fclose(file); fclose(temp);
        if (found) {
            remove(FILENAME);
            rename("temp.dat", FILENAME);
            printf("Record updated.\n");
        } else {
            printf("Record not found.\n");
            remove("temp.dat");
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Create Address Book\n2. View Address Book\n3. Insert a Record\n4. Delete a Record\n5. Modify a Record\n6. Exit\n");
        printf("Choice: ");
        printf("By Onkar - T1905308657\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: create_address_book(); break;
            case 2: view_address_book(); break;
            case 3: insert_record(); break;
            case 4: delete_record(); break;
            case 5: modify_record(); break;
            case 6: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}
