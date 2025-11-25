#include <stdio.h>
#include <string.h>

#define BOOK_LIMIT 100
#define SIZE 50

struct Item {
    int uniqueId;
    char title[SIZE];
    char author[SIZE];
    int Loaned;
};

struct Item shelfItems[BOOK_LIMIT];
int itemCount = 0;
int currentId = 1;

void showOptions();
void clearInputBuffer();
void addNewItem();
void showAllItems();
void updateStatus(int idToFind, int statusValue);
void lendItem();
void getItemBack();
void searchItemByID();
void displayTotalCount();
void showLoanedItems();
void deleteItemByID();

void showOptions() {
    printf(" Welcome to the library\n");
    printf("1. Add New Item\n");
    printf("2. Show All Items\n");
    printf("3. Lend Item\n");
    printf("4. Get Item Back\n");
    printf("5. Search Item by ID\n");
    printf("6. Display Total Item Count\n");
    printf("7. Show All Loaned Items\n");
    printf("8. Delete Item by ID\n");
    printf("9. Quit\n");
    printf("Enter number: ");
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void addNewItem() {
    if (itemCount >= BOOK_LIMIT) {
        printf("?? Shelf is full. Cannot add.\n");
        return;
    }

    struct Item newItem;
    newItem.uniqueId = currentId++;
    newItem.Loaned = 0;

    printf("Enter title (one word): ");
    scanf("%s", newItem.title);
    clearInputBuffer();

    printf("Enter author (one word): ");
    scanf("%s", newItem.author);
    clearInputBuffer();

    shelfItems[itemCount] = newItem;
    itemCount++;
    printf("? Item added successfully! ID: %d\n", newItem.uniqueId);
}

void showAllItems() {
    if (itemCount == 0) {
        printf("No items currently on shelf.\n");
        return;
    }

    printf("\n--- ?? Item List (%d Total) ---\n", itemCount);
    int i;
    for (i = 0; i < itemCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Status: %s\n",
               shelfItems[i].uniqueId,
               shelfItems[i].title,
               shelfItems[i].author,
               shelfItems[i].Loaned ? "? OUT" : "? IN STOCK");
    }
    printf("\n");
}

void updateStatus(int idToFind, int statusValue) {
    int found = 0;
    int i;
    for (i = 0; i < itemCount; i++) {
        if (shelfItems[i].uniqueId == idToFind) {
            shelfItems[i].Loaned = statusValue;
            found = 1;
            break;
        }
    }
    if (found) {
        printf("Status updated: Item ID %d is now %s.\n", idToFind, statusValue ? "Loaned Out" : "Returned");
    } else {
        printf("?? Item ID %d is not found.\n", idToFind);
    }
}

void lendItem() {
    int id;
    printf("Enter the Item ID you want to lend: ");
    if (scanf("%d", &id) != 1) {
        printf("Incorrect input,please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    updateStatus(id, 1);
}

void getItemBack() {
    int id;
    printf("Enter Item ID for return: ");
    if (scanf("%d", &id) != 1) {
        printf("Incorrect input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    updateStatus(id, 0);
}

void searchItemByID() {
    int idToFind;
    printf(" Search Item\n");
    printf("Enter Item ID to search: ");
    if (scanf("%d", &idToFind) != 1) {
        printf("Incorrect input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int found = 0;
    int i;
    for (i = 0; i < itemCount; i++) {
        if (shelfItems[i].uniqueId == idToFind) {
            printf("\n--- Found Item ---\n");
            printf("ID: %d\n", shelfItems[i].uniqueId);
            printf("Title: %s\n", shelfItems[i].title);
            printf("Author: %s\n", shelfItems[i].author);
            printf("Status: %s\n", shelfItems[i].Loaned ? "? Loaned Out" : "? In Stock");
            printf("------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d was not found.\n", idToFind);
    }
}

void displayTotalCount() {
    printf(" Catalog Count\n");
    printf("Total items in the library: %d / %d (Max Capacity)\n", itemCount, BOOK_LIMIT);
    printf("\n");
}

void showLoanedItems() {
    int loanedCount = 0;
    printf(" Items Currently Loaned Out \n");
    int i;
    for (i = 0; i < itemCount; i++) {
        if (shelfItems[i].Loaned == 1) {
            printf("ID: %d, Title: %s, Author: %s\n",
                   shelfItems[i].uniqueId,
                   shelfItems[i].title,
                   shelfItems[i].author);
            loanedCount++;
        }
    }

    if (loanedCount == 0) {
        printf("All items are currently in stock!\n");
    }
    printf("Total items loaned: %d\n", loanedCount);
    printf("\n");
}

void deleteItemByID() {
    int idToDelete;
    printf(" Delete Item \n");
    printf("Enter Item ID you want to delete: ");
    if (scanf("%d", &idToDelete) != 1) {
        printf("Incorrect input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = -1;
    int i;
    for (i = 0; i < itemCount; i++) {
        if (shelfItems[i].uniqueId == idToDelete) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (shelfItems[index].Loaned == 1) {
            printf("?? ERROR: Cannot delete item ID %d. It is currently loaned out.\n", idToDelete);
            return;
        }
        
        printf("Removing item ID %d: %s.\n", idToDelete, shelfItems[index].title);

        for (i = index; i < itemCount - 1; i++) {
            shelfItems[i] = shelfItems[i + 1];
        }
        itemCount--;
        printf("? Item successfully deleted.\n");
    } else {
        printf("?? Item with ID %d was not found.\n", idToDelete);
    }
}


int main() {
    int choice;

    while (1) {
        showOptions();

        if (scanf("%d", &choice) != 1) {
            printf("Enter a valid number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewItem();
                break;
            case 2:
                showAllItems();
                break;
            case 3:
                lendItem();
                break;
            case 4:
                getItemBack();
                break;
            case 5:
                searchItemByID();
                break;
            case 6:
                displayTotalCount();
                break;
            case 7:
                showLoanedItems();
                break;
            case 8:
                deleteItemByID();
                break;
            case 9:
                printf("program is ending!\n");
                return 0;
            default:
                printf("Choose a number from 1 to 9\n");
        }
    }
    return 0;
}
