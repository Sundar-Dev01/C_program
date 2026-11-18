#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book
{
    int id;
    char title[50];
    char author[50];
    int department;
};

struct Book books[MAX_BOOKS];
int bookCount = 0;

int currentDepartment = 0;

void clearInput(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
    }
}

const char *getDepartmentName(int department)
{
    if (department == 1)
        return "Mathematics";
    if (department == 2)
        return "Physics";
    if (department == 3)
        return "Chemistry";

    return "Unknown";
}

int bookIdExists(int id)
{
    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
            return 1;
    }

    return 0;
}

void selectDepartment(void)
{
    int choice;

    do
    {
        printf("\n===== SELECT DEPARTMENT =====\n");
        printf("1. Mathematics\n");
        printf("2. Physics\n");
        printf("3. Chemistry\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 3)
            printf("Invalid department! Try again.\n");

    } while (choice < 1 || choice > 3);

    currentDepartment = choice;

    printf("\nYou are now in the %s Department.\n",
           getDepartmentName(currentDepartment));
}

void addBook(void)
{
    int id;

    if (bookCount >= MAX_BOOKS)
    {
        printf("Library is full!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &id);

    if (bookIdExists(id))
    {
        printf("Book ID already exists!\n");
        return;
    }

    books[bookCount].id = id;
    clearInput();

    printf("Enter Book Title: ");
    scanf(" %49[^\n]", books[bookCount].title);

    printf("Enter Author Name: ");
    scanf(" %49[^\n]", books[bookCount].author);

    books[bookCount].department = currentDepartment;

    bookCount++;

    printf("\nBook added successfully to %s Department!\n",
           getDepartmentName(currentDepartment));
}

void viewBooks(void)
{
    int found = 0;

    printf("\n===== %s DEPARTMENT BOOKS =====\n",
           getDepartmentName(currentDepartment));

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].department == currentDepartment)
        {
            printf("\nBook ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            found = 1;
        }
    }

    if (!found)
        printf("No books found in this department!\n");
}

void updateBook(void)
{
    int id;
    int found = 0;

    printf("\nEnter Book ID to update: ");
    scanf("%d", &id);
    clearInput();

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id &&
            books[i].department == currentDepartment)
        {
            printf("Enter new Book Title: ");
            scanf(" %49[^\n]", books[i].title);

            printf("Enter new Author Name: ");
            scanf(" %49[^\n]", books[i].author);

            printf("\nBook updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found in %s Department!\n",
               getDepartmentName(currentDepartment));
}

void deleteBook(void)
{
    int id;
    int found = 0;

    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id &&
            books[i].department == currentDepartment)
        {
            for (int j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1];
            }

            bookCount--;

            printf("\nBook deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found in %s Department!\n",
               getDepartmentName(currentDepartment));
}

void searchBook(void)
{
    int id;
    int found = 0;

    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id &&
            books[i].department == currentDepartment)
        {
            printf("\nBook Found!\n");
            printf("Book ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Department: %s\n",
                   getDepartmentName(books[i].department));

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found in %s Department!\n",
               getDepartmentName(currentDepartment));
}

int main(void)
{
    char username[30];
    char password[30];
    int attempts = 0;
    int choice;

    printf("===== LIBRARY MANAGEMENT SYSTEM =====\n");

    while (attempts < 3)
    {
        printf("\nAdmin Username: ");
        scanf("%29s", username);

        printf("Admin Password: ");
        scanf("%29s", password);

        if (strcmp(username, "admin") == 0 &&
            strcmp(password, "1234") == 0)
        {
            printf("\nLogin Successful!\n");
            break;
        }

        printf("Invalid Username or Password!\n");
        attempts++;
    }

    if (attempts == 3)
    {
        printf("\nMaximum login attempts reached!\n");
        return 0;
    }

    selectDepartment();

    do
    {
        printf("\n===== %s DEPARTMENT MENU =====\n",
               getDepartmentName(currentDepartment));

        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Update Book\n");
        printf("4. Delete Book\n");
        printf("5. Search Book\n");
        printf("6. Change Department\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                updateBook();
                break;

            case 4:
                deleteBook();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                selectDepartment();
                break;

            case 7:
                printf("\nThank you for using LMS!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
                break;
        }

    } while (choice != 7);

    return 0;
}
