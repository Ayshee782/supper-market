#include <stdio.h>
#include <string.h>
#include <time.h>

#define PRODUCT_COUNT 100
#define CART_SIZE 100

// Structure Definitions
struct Product {
    char name[200];
    char type[200];
    int price;    // Price per unit (kg or liter)
    int stock;    // Available stock
};

struct Customer {
    char name[20];
    char address[20];
    char phone[20];
};

struct CartItem {
    char name[200];
    int quantity; // Quantity in kg for Grocery or liters for Liquid
};

struct BillDetails {
    float subtotal;
    float discount;
    float tax;
    float grandTotal;
};

// Global Variables
struct CartItem cart[CART_SIZE];
int cartItemCount = 0;
struct Customer customer; // Global customer details
float totalBill = 0.0;    // Global total bill

// Function Prototypes
float addProduct(struct Product products[], float totalBill);
float removeProduct(struct Product products[], float totalBill);
void calculateBill(struct Product products[], struct BillDetails *billDetails, float *totalBill);
void returnMoney(float totalBill);
void searchProduct(struct Product products[]);
void editReceipt(struct Product products[], struct BillDetails *billDetails, float *totalBill);
void selectPaymentMethod();
void displayAvailableProducts(struct Product products[]);
void generateReceipt(struct Product products[], struct BillDetails billDetails);
int findProduct(struct Product products[], const char *name);
void clearCart();

int main() {
    // Initialize Products (Add all 200 products as needed)
    struct Product products[PRODUCT_COUNT] = {
        {"apple", "Grocery", 150, 50},
        {"orange", "Grocery", 120, 70},
        {"mango", "Grocery", 80, 40},
        {"grapes", "Grocery", 280, 59},
        {"strawberry", "Grocery", 280, 58},
        {"blueberry", "Grocery", 380, 80},
        {"pineapple", "Grocery", 100, 89},

        {"watermelon", "Grocery", 180, 56},
        {"cherry", "Grocery", 180, 58},
        {"lime", "Grocery", 80, 90},
        {"kiwi", "Grocery", 580, 56},
        {"pomegranate", "Grocery", 380, 60},
        {"papaya", "Grocery", 60, 56},
        {"raspberry", "Grocery", 68, 50},
        {"pear", "Grocery", 280, 56},
        {"guava", "Grocery", 25, 56},
        {"dragonfruit", "Grocery", 180, 60},
        {"passionfruit", "Grocery", 180, 60},
        {"lychee", "Grocery", 180, 56},
        {"honeydew", "Grocery", 280, 50},
        {"lemon", "Grocery", 20, 58},
        {"corn", "Grocery", 50, 80},
        {"mushroom", "Grocery", 180, 80},
        {"beetroot", "Grocery", 280, 80},
        {"eggplant", "Grocery", 80, 80},
        {"peas", "Grocery", 180, 80},
        {"endive", "Grocery", 80, 80},
        {"celery", "Grocery", 280, 80},
        {"leek", "Grocery", 380, 80},
        {"acorn Squash", "Grocery", 280, 80},
        // Liquid Products
        {"oil", "Liquid", 150, 60},
        {"milk", "Liquid", 50, 60},
        {"orange Juice", "Liquid", 50, 60},
        {"apple Juice", "Liquid", 50, 60},
        {"grape Juice", "Liquid", 50, 60},
        {"lemonade", "Liquid", 40, 60},
        {"tomato Juice", "Liquid", 50, 60},
        {"almond Milk", "Liquid", 50, 60},
        {"coconut Water", "Liquid", 50, 60},
        {"guava Juice", "Liquid", 500, 60},
        {"honey", "Liquid", 200, 60},
        {"buttermilk", "Liquid", 500, 60},
        {"fruit Punch", "Liquid", 50, 60},
        {"mango Juice", "Liquid", 50, 60},
        {"sunflower Oil", "Liquid", 500, 60},
        {"peanut Oil", "Liquid", 500, 60},
        {"coconut Oil", "Liquid", 60, 60},
        {"vegetable Oil", "Liquid", 50, 60},
        {"ice Cream", "Liquid", 50, 60},
        {"olive Oil Juice", "Liquid", 50, 60},
        {"pineapple Juice", "Liquid", 50, 60},
        {"chocolate Juice", "Liquid", 50, 60},
        // Skin Care Products
        {"cleanser", "Liquid", 200, 50},
        {"serum", "Liquid", 400, 50},
        {"toner", "Liquid", 50, 50},
        {"scrub", "Liquid", 500, 50},
        // Initialize remaining products as needed...
    };

    struct BillDetails billDetails = {0.0, 0.0, 0.0, 0.0};

    int choice;
    char moreProducts;

    do {
        printf("\n**** Welcome ****\n");
        printf("Menu:\n");
        printf("1. Enter Customer Details\n");
        printf("2. Add Product\n");
        printf("3. Remove Product\n");
        printf("4. Calculate Bill\n");
        printf("5. Edit Receipt\n");  // New option for editing receipt
        printf("6. Select Payment Method\n");
        printf("7. Payback\n");
        printf("8. Search Product\n");
        printf("9. Display Available Products\n");
        printf("10. Generate Receipt\n");
        printf("11. Clear Cart\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Customer Details:\n");
                printf("Name: ");
                scanf("%s", customer.name);
                printf("Address: ");
                scanf("%s", customer.address);
                printf("Phone: ");
                scanf("%s", customer.phone);
                printf("Customer details entered successfully.\n");
                break;

            case 2:
                do {
                    totalBill = addProduct(products, totalBill);
                    printf("Do you want to add more products? (y/n): ");
                    scanf(" %c", &moreProducts);
                } while (moreProducts == 'y' || moreProducts == 'Y');
                break;

            case 3:
                do {
                    totalBill = removeProduct(products, totalBill);
                    printf("Do you want to remove more products? (y/n): ");
                    scanf(" %c", &moreProducts);
                } while (moreProducts == 'y' || moreProducts == 'Y');
                break;

            case 4:
                calculateBill(products, &billDetails, &totalBill);
                break;

            case 5:
                editReceipt(products, &billDetails, &totalBill);
                break;

            case 6:
                selectPaymentMethod();
                break;

            case 7:
                returnMoney(billDetails.grandTotal);
                break;

            case 8:
                searchProduct(products);
                break;

            case 9:
                displayAvailableProducts(products);
                break;

            case 10:
                generateReceipt(products, billDetails);
                break;

            case 11:
                clearCart();
                break;

            case 12:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 12);

    return 0;
}

// Function Implementations

// Add Product to Cart
float addProduct(struct Product products[], float totalBill) {
    char input[200];
    int quantity;
    int found = 0;

    printf("Enter product name to add: ");
    scanf("%s", input);

    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (strcmp(products[i].name, input) == 0) {
            if (products[i].stock <= 0) {
                printf("Sorry, %s is out of stock.\n", products[i].name);
                return totalBill;
            }

            printf("Enter quantity (in kg or liters): ");
            scanf("%d", &quantity);
            if (quantity <= 0) {
                printf("Invalid quantity.\n");
                return totalBill;
            }
            if (products[i].stock < quantity) {
                printf("Not enough stock available for %s.\n", products[i].name);
                return totalBill;
            }
            products[i].stock -= quantity;

            float cost = products[i].price * quantity;
            totalBill += cost;
            strcpy(cart[cartItemCount].name, products[i].name);
            cart[cartItemCount].quantity = quantity;
            cartItemCount++;
            printf("Added %d units of %s to cart. Cost: $%.2f\n", quantity, products[i].name, cost);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
    return totalBill;
}

// Remove Product from Cart
float removeProduct(struct Product products[], float totalBill) {
    char input[200];
    float quantity;
    int found = 0;

    printf("Enter product name to remove: ");
    scanf("%s", input);

    // Find the product in products array
    int productIndex = findProduct(products, input);
    if (productIndex == -1) {
        printf("Product not found in products list.\n");
        return totalBill;
    }

    printf("Enter quantity to remove (in kg or liters): ");
    scanf("%f", &quantity);
    if (quantity <= 0) {
        printf("Invalid quantity.\n");
        return totalBill;
    }

    // Find the product in cart
    int cartIndex = -1;
    for (int i = 0; i < cartItemCount; i++) {
        if (strcmp(cart[i].name, input) == 0) {
            cartIndex = i;
            break;
        }
    }

    if (cartIndex == -1) {
        printf("Product not found in cart.\n");
        return totalBill;
    }

    if (quantity > cart[cartIndex].quantity) {
        printf("Cannot remove more than existing quantity (%d).\n", cart[cartIndex].quantity);
        return totalBill;
    }

    // Update cart and stock
    cart[cartIndex].quantity -= quantity;
    products[productIndex].stock += quantity;
    float cost = products[productIndex].price * quantity;
    totalBill -= cost;
    printf("Removed %.2f units of %s from cart. Cost removed: $%.2f\n", quantity, input, cost);

    if (cart[cartIndex].quantity == 0) {
        // Remove the item from cart by shifting
        for (int i = cartIndex; i < cartItemCount - 1; i++) {
            cart[i] = cart[i + 1];
        }
        cartItemCount--;
    }

    found = 1;

    if (!found) {
        printf("Product not found in cart.\n");
    }
    return totalBill;
}

// Calculate Bill
void calculateBill(struct Product products[], struct BillDetails *billDetails, float *totalBill) {
    float discount = 0.0;
    float subtotal = 0.0;

    // Calculate subtotal
    for (int i = 0; i < cartItemCount; i++) {
        int index = findProduct(products, cart[i].name);
        if (index != -1) {
            subtotal += products[index].price * cart[i].quantity;
        }
    }

    // Apply discount based on subtotal
    if (subtotal > 10000) {
        discount = subtotal * 0.10; // 10% discount
    } else if (subtotal > 5000) {
        discount = subtotal * 0.05; // 5% discount
    } else if (subtotal > 3000) {
        discount = subtotal * 0.03; // 3% discount
    }

    float discountedBill = subtotal - discount;
    float tax = discountedBill * 0.05; // 5% tax
    float grandTotal = discountedBill + tax;

    billDetails->subtotal = subtotal;
    billDetails->discount = discount;
    billDetails->tax = tax;
    billDetails->grandTotal = grandTotal;

    *totalBill = grandTotal;

    printf("\nInvoice:\n");
    printf("Customer Name: %s\n", customer.name);
    printf("Address: %s\n", customer.address);
    printf("Phone: %s\n", customer.phone);
    printf("\nPurchase Details:\n");
    printf("Serial No | Product Name | Price | Quantity | Total Price\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < cartItemCount; i++) {
        int index = findProduct(products, cart[i].name);
        if (index != -1) {
            int price = products[index].price;
            int quantity = cart[i].quantity;
            float totalPrice = price * quantity;
            printf("%-9d | %-12s | $%-5d | %-8d | $%-10.2f\n",
                   i + 1, cart[i].name, price, quantity, totalPrice);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("Total Bill (before discount): $%.2f\n", subtotal);
    printf("Discount: $%.2f\n", discount);
    printf("Total Bill (after discount): $%.2f\n", discountedBill);
    printf("Tax (5%%): $%.2f\n", tax);
    printf("Grand Total: $%.2f\n", grandTotal);
}

// Edit Receipt Function
void editReceipt(struct Product products[], struct BillDetails *billDetails, float *totalBill) {
    int choice;
    printf("\n**** Edit Receipt ****\n");
    printf("1. Change Customer Details\n");
    printf("2. Change Product Quantity\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new customer name (current: %s): ", customer.name);
            scanf("%s", customer.name);
            printf("Enter new address (current: %s): ", customer.address);
            scanf("%s", customer.address);
            printf("Enter new phone (current: %s): ", customer.phone);
            scanf("%s", customer.phone);
            printf("Customer details updated successfully.\n");
            break;

        case 2: {
            char productName[200];
            int newQuantity;
            printf("Enter product name to change quantity: ");
            scanf("%s", productName);

            // Find the product in cart
            int cartIndex = -1;
            for (int i = 0; i < cartItemCount; i++) {
                if (strcmp(cart[i].name, productName) == 0) {
                    cartIndex = i;
                    break;
                }
            }

            if (cartIndex == -1) {
                printf("Product not found in cart.\n");
                break;
            }

            printf("Current quantity of %s: %d\n", cart[cartIndex].name, cart[cartIndex].quantity);
            printf("Enter new quantity: ");
            scanf("%d", &newQuantity);

            if (newQuantity < 0) {
                printf("Invalid quantity. Quantity cannot be negative.\n");
                break;
            }

            int productIndex = findProduct(products, productName);
            if (productIndex == -1) {
                printf("Product not found in products list.\n");
                break;
            }

            // Adjust stock based on new quantity
            products[productIndex].stock += cart[cartIndex].quantity; // Return old quantity to stock

            if (newQuantity > 0) {
                if (products[productIndex].stock < newQuantity) {
                    printf("Not enough stock available for %s. Available stock: %d\n", productName, products[productIndex].stock);
                    // Revert the stock adjustment
                    products[productIndex].stock -= 0; // No change
                    break;
                }
                products[productIndex].stock -= newQuantity;
                cart[cartIndex].quantity = newQuantity;
                printf("Updated quantity for %s to %d.\n", productName, newQuantity);
            } else {
                // Remove the product from cart
                for (int i = cartIndex; i < cartItemCount - 1; i++) {
                    cart[i] = cart[i + 1];
                }
                cartItemCount--;
                printf("Removed %s from cart.\n", productName);
            }

            // Recalculate the bill after editing
            calculateBill(products, billDetails, totalBill);
            break;
        }

        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

// Return Money to Customer
void returnMoney(float totalBill) {
    float money;
    printf("Enter amount given by customer: $");
    scanf("%f", &money);

    if (money >= totalBill) {
        float change = money - totalBill;
        printf("Change to return: $%.2f\n", change);
    } else {
        printf("Insufficient payment! Need $%.2f more.\n", totalBill - money);
    }
}

// Search for a Product
void searchProduct(struct Product products[]) {
    char input[200];
    printf("Enter product name to search: ");
    scanf("%s", input);
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (strcmp(products[i].name, input) == 0) {
            printf("Product found: %s\n", products[i].name);
            printf("Type: %s\n", products[i].type);
            printf("Price: $%d\n", products[i].price);
            printf("Available stock: %d\n", products[i].stock);
            return;
        }
    }
    printf("Product not found.\n");
}

// Select Payment Method
void selectPaymentMethod() {
    int method;
    printf("Select Payment Method:\n");
    printf("1. Cash\n");
    printf("2. Credit Card\n");
    printf("3. Mobile Payment\n");
    printf("Enter your choice: ");
    scanf("%d", &method);

    switch (method) {
        case 1:
            printf("Payment method selected: Cash\n");
            break;
        case 2:
            printf("Payment method selected: Credit Card\n");
            break;
        case 3:
            printf("Payment method selected: Mobile Payment\n");
            break;
        default:
            printf("Invalid choice. Please select a valid payment method.\n");
    }
}

// Display Available Products
void displayAvailableProducts(struct Product products[]) {
    printf("\nAvailable Products:\n");
    printf("-------------------------------------------------------------\n");
    printf("Name\t\tType\t\tPrice\tStock\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (products[i].stock > 0) {
            printf("%-15s %-10s $%-6d %-5d\n",
                   products[i].name,
                   products[i].type,
                   products[i].price,
                   products[i].stock);
        }
    }
    printf("-------------------------------------------------------------\n");
}

// Generate Receipt
void generateReceipt(struct Product products[], struct BillDetails billDetails) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\n**** Receipt ****\n");
    printf("Date: %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("Customer Name: %s\n", customer.name);
    printf("Address: %s\n", customer.address);
    printf("Phone: %s\n", customer.phone);
    printf("\n%-25s %-10s %-10s %-10s\n", "Product Name", "Quantity", "Unit Price", "Total");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < cartItemCount; i++) {
        int productIndex = findProduct(products, cart[i].name);
        if (productIndex != -1) {
            float unitPrice = products[productIndex].price;
            float totalPrice = unitPrice * cart[i].quantity;
            printf("%-25s %-10d $%-9.2f $%-9.2f\n",
                   cart[i].name,
                   cart[i].quantity,
                   unitPrice,
                   totalPrice);
        }
    }

    printf("-----------------------------------------------------------------\n");
    printf("Subtotal: $%.2f\n", billDetails.subtotal);
    printf("Discount: $%.2f\n", billDetails.discount);
    printf("Tax (5%%): $%.2f\n", billDetails.tax);
    printf("Grand Total: $%.2f\n", billDetails.grandTotal);
    printf("-----------------------------------------------------------------\n");
    printf("Thank you for shopping with us!\n");
}

// Find Product Index by Name
int findProduct(struct Product products[], const char *name) {
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return i; // Return index
        }
    }
    return -1; // Not found
}

// Clear the Cart
void clearCart() {
    cartItemCount = 0;
    totalBill = 0.0;
    printf("All items have been removed from your cart.\n");
}
