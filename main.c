
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Book {
    int id;
    char title[100];
    char author[100];
    int available;
};

struct Book books[MAX] = {
    {101, "Data Structures", "Seymour Lipschutz", 1},
    {102, "C Programming", "Dennis Ritchie", 1},
    {103, "Computer Networks", "Andrew Tanenbaum", 0},
    {104, "Operating Systems", "Galvin", 1},
    {105, "Database Systems", "Korth", 1}
};

int count = 5;

/* Find a book by ID using Binary Search */
int binarySearch(int id) {
    int low = 0, high = count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (books[mid].id == id)
            return mid;
        else if (books[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* Sort books by ID for Binary Search */
void sortByID() {
    int i, j;
    struct Book temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (books[j].id > books[j + 1].id) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

/* Sort books alphabetically using Bubble Sort */
void sortByTitle() {
    int i, j;
    struct Book temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (strcmp(books[j].title,
                       books[j + 1].title) > 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

/* Search by title or author using Linear Search */
void searchBook() {
    char key[100];
    int i, found = 0;

    printf("Enter title or author: ");
    scanf(" %99[^\n]", key);

    for (i = 0; i < count; i++) {
        if (strstr(books[i].title, key) != NULL ||
            strstr(books[i].author, key) != NULL) {
            printf("\nID: %d | Title: %s | Author: %s | %s\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].available ? "Available" : "Borrowed");
            found = 1;
        }
    }

    if (!found)
        printf("No matching book found.\n");
}

/* Display all books */
void displayBooks() {
    int i;

    if (count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n%-6s %-25s %-22s %-12s\n",
           "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-6d %-25s %-22s %-12s\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].available ? "Available" : "Borrowed");
    }
}

/* Add a new book */
void addBook() {
    int id, i;

    if (count >= MAX) {
        printf("Library is full.\n");
        return;
    }

    printf("Enter Book ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    for (i = 0; i < count; i++) {
        if (books[i].id == id) {
            printf("Book ID already exists.\n");
            return;
        }
    }

    books[count].id = id;

    printf("Enter Book Title: ");
    scanf(" %99[^\n]", books[count].title);

    printf("Enter Author Name: ");
    scanf(" %99[^\n]", books[count].author);

    books[count].available = 1;
    count++;

    printf("Book added successfully.\n");
}

/* Borrow or return a book */
void updateBook(int borrow) {
    int id, index;

    printf("Enter Book ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    sortByID();
    index = binarySearch(id);

    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    if (borrow == 1) {
        if (books[index].available == 1) {
            books[index].available = 0;
            printf("Book borrowed successfully.\n");
        } else {
            printf("Book is already borrowed.\n");
        }
    } else {
        if (books[index].available == 0) {
            books[index].available = 1;
            printf("Book returned successfully.\n");
        } else {
            printf("Book is already available.\n");
        }
    }
}

int main() {
    int choice;

    do {
        printf("\n===== LIBRARY BOOK AVAILABILITY FINDER =====\n");
        printf("1. Display All Books\n");
        printf("2. Search by Title or Author\n");
        printf("3. Search by Book ID\n");
        printf("4. Sort Books by Title\n");
        printf("5. Add New Book\n");
        printf("6. Borrow Book\n");
        printf("7. Return Book\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                displayBooks();
                break;

            case 2:
                searchBook();
                break;

            case 3: {
                int id, index;

                printf("Enter Book ID: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID.\n");
                    while (getchar() != '\n');
                    break;
                }

                sortByID();
                index = binarySearch(id);

                if (index != -1) {
                    printf("Book found: %s by %s - %s\n",
                           books[index].title,
                           books[index].author,
                           books[index].available
                               ? "Available" : "Borrowed");
                } else {
                    printf("Book not found.\n");
                }
                break;
            }

            case 4:
                sortByTitle();
                printf("Books sorted alphabetically.\n");
                displayBooks();
                break;

            case 5:
                addBook();
                break;

            case 6:
                updateBook(1);
                break;

            case 7:
                updateBook(0);
                break;

            case 8:
                printf("Thank you for using the system.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 8);

    return 0;
}