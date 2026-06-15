#include <stdio.h>
#include <string.h>

struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
};

int main() {
    struct Item items[100];
    int count = 0;
    int choice, i;

    FILE *fp;

    // ===== Load Existing Data From File =====
    fp = fopen("store.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %s %f %d",
                      &items[count].id,
                      items[count].name,
                      &items[count].price,
                      &items[count].quantity) != EOF) {
            count++;
        }
        fclose(fp);
    }

    while (1) {
        printf("\n===== Grocery Store =====\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Generate Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // --- Add new item ---
            printf("Enter Item ID: ");
            scanf("%d", &items[count].id);

            printf("Enter Item Name: ");
            scanf("%s", items[count].name);

            printf("Enter Price: ");
            scanf("%f", &items[count].price);

            printf("Enter Quantity: ");
            scanf("%d", &items[count].quantity);

            count++;

            // --- Save to file ---
            fp = fopen("store.txt", "w");
            for (i = 0; i < count; i++) {
                fprintf(fp, "%d %s %.2f %d\n",
                        items[i].id,
                        items[i].name,
                        items[i].price,
                        items[i].quantity);
            }
            fclose(fp);

            printf("Item added successfully!\n");
        }

        else if (choice == 2) {
            // --- Display items ---
            if (count == 0) {
                printf("No items found!\n");
            } else {
                printf("\nID\tName\tPrice\tQuantity\n");
                printf("-----------------------------------\n");
                for (i = 0; i < count; i++) {
                    printf("%d\t%s\t%.2f\t%d\n",
                           items[i].id,
                           items[i].name,
                           items[i].price,
                           items[i].quantity);
                }
            }
        }

        else if (choice == 3) {
            // --- Generate Bill ---
            int id, qty;
            float total = 0;
            int found = 0;

            printf("Enter Item ID to buy: ");
            scanf("%d", &id);

            printf("Enter Quantity: ");
            scanf("%d", &qty);

            for (i = 0; i < count; i++) {
                if (items[i].id == id) {
                    found = 1;
                    if (qty <= items[i].quantity) {
                        total = qty * items[i].price;
                        items[i].quantity -= qty;

                        printf("\n----- BILL -----\n");
                        printf("Item: %s\n", items[i].name);
                        printf("Price: %.2f\n", items[i].price);
                        printf("Quantity: %d\n", qty);
                        printf("Total Bill: %.2f\n", total);
                        printf("----------------\n");
                    } else {
                        printf("Not enough stock!\n");
                    }
                    break;
                }
            }

            if (!found) {
                printf("Item not found!\n");
            }

            // --- Update file after billing ---
            fp = fopen("store.txt", "w");
            for (i = 0; i < count; i++) {
                fprintf(fp, "%d %s %.2f %d\n",
                        items[i].id,
                        items[i].name,
                        items[i].price,
                        items[i].quantity);
            }
            fclose(fp);
        }

        else if (choice == 4) {
            printf("Exiting program...\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}