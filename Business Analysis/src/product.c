/**
 * Product Management Implementation File
 * Contains implementations of product management functions
 */

#include "product.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "globals.h"

// Global array to store products
extern Product products[MAX_ARRAY_SIZE];
extern int productCount;

// Function to run the product management module
void runProductManagement() {
    int choice;
    bool running = true;

    // Load product data
    loadProductData();

    while (running) {
        clearScreen();
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m        PRODUCT MANAGEMENT\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("1. Add Product\n");
        printf("2. View All Products\n");
        printf("3. Search Product by ID\n");
        printf("4. Search Products by Name\n");
        printf("5. Filter Products by Category\n");
        printf("6. Manage Inventory\n");
        printf("7. Edit Product\n");
        printf("8. Delete Product\n");
        printf("9. Check Low Stock\n");
        printf("10. Back to Main Menu\n");
        printf("\033[1;36m========================================\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addProduct();
                pressEnterToContinue();
                break;
            case 2:
                displayAllProducts();
                pressEnterToContinue();
                break;
            case 3: {
                int id;
                printf("Enter product ID to search: ");
                scanf("%d", &id);
                clearInputBuffer();
                searchProductById(id);
                pressEnterToContinue();
                break;
            }
            case 4: {
                char name[MAX_STRING_LENGTH];
                printf("Enter product name (or part of name) to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                searchProductsByName(name);
                pressEnterToContinue();
                break;
            }
            case 5: {
                // Get all unique categories
                char categories[MAX_ARRAY_SIZE][30];
                int numCategories = getProductCategories(categories, MAX_ARRAY_SIZE);
                
                if (numCategories > 0) {
                    printf("\nAvailable Categories:\n");
                    for (int i = 0; i < numCategories; i++) {
                        printf("%d. %s\n", i + 1, categories[i]);
                    }
                    
                    int categoryChoice;
                    printf("\nSelect a category (1-%d): ", numCategories);
                    scanf("%d", &categoryChoice);
                    clearInputBuffer();
                    
                    if (categoryChoice >= 1 && categoryChoice <= numCategories) {
                        displayProductsByCategory(categories[categoryChoice - 1]);
                    } else {
                        printf("Invalid category selection.\n");
                    }
                } else {
                    printf("No categories found.\n");
                }
                pressEnterToContinue();
                break;
            }
            case 6: {
                int id, quantity;
                printf("Enter product ID to update inventory: ");
                scanf("%d", &id);
                clearInputBuffer();
                
                int index = findProductById(id);
                if (index != -1) {
                    printf("Current stock for %s: %d\n", products[index].name, products[index].quantity);
                    printf("Enter quantity to add (positive) or remove (negative): ");
                    scanf("%d", &quantity);
                    clearInputBuffer();
                    
                    updateProductInventory(id, quantity);
                } else {
                    displayError("Product not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 7: {
                int id;
                printf("Enter product ID to edit: ");
                scanf("%d", &id);
                clearInputBuffer();
                editProduct(id);
                pressEnterToContinue();
                break;
            }
            case 8: {
                int id;
                printf("Enter product ID to delete: ");
                scanf("%d", &id);
                clearInputBuffer();
                deleteProduct(id);
                pressEnterToContinue();
                break;
            }
            case 9: {
                int threshold;
                printf("Enter low stock threshold: ");
                scanf("%d", &threshold);
                clearInputBuffer();
                
                int lowStockCount = checkLowStock(threshold);
                if (lowStockCount > 0) {
                    printf("\n\033[1;33mWarning: %d products are below the threshold of %d units.\033[0m\n", 
                           lowStockCount, threshold);
                } else {
                    printf("\n\033[1;32mAll products are above the threshold of %d units.\033[0m\n", threshold);
                }
                pressEnterToContinue();
                break;
            }
            case 10:
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                pressEnterToContinue();
        }
    }
}

// Function to add a new product
bool addProduct() {
    if (productCount >= MAX_ARRAY_SIZE) {
        displayError("Product database is full. Cannot add more products.");
        return false;
    }

    Product newProduct;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           ADD NEW PRODUCT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Enter ID: ");
    scanf("%d", &newProduct.id);
    clearInputBuffer();
    
    // Check if ID already exists
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == newProduct.id) {
            displayError("A product with this ID already exists.");
            return false;
        }
    }
    
    printf("Enter Name: ");
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove newline character
    
    printf("Enter Price: ");
    scanf("%lf", &newProduct.price);
    clearInputBuffer();
    
    printf("Enter Quantity: ");
    scanf("%d", &newProduct.quantity);
    clearInputBuffer();
    
    printf("Enter Category: ");
    fgets(newProduct.category, sizeof(newProduct.category), stdin);
    newProduct.category[strcspn(newProduct.category, "\n")] = 0;
    
    printf("Enter Description: ");
    fgets(newProduct.description, sizeof(newProduct.description), stdin);
    newProduct.description[strcspn(newProduct.description, "\n")] = 0;
    
    // Add the new product to the array
    products[productCount] = newProduct;
    productCount++;
    
    // Sort products by ID
    sortProductsById();
    
    // Save product data
    if (saveProductData()) {
        displaySuccess("Product added successfully.");
        return true;
    } else {
        displayError("Failed to save product data.");
        return false;
    }
}

// Function to search for a product by ID
bool searchProductById(int id) {
    int index = findProductById(id);
    
    if (index != -1) {
        printf("\n\033[1;36m========================================\033[0m\n");
        printf("\033[1;32m            PRODUCT FOUND\033[0m\n");
        printf("\033[1;36m========================================\033[0m\n");
        displayProductDetails(&products[index]);
        return true;
    } else {
        displayError("Product not found.");
        return false;
    }
}

// Function to search for products by name
void searchProductsByName(const char *name) {
    bool found = false;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           SEARCH RESULTS\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < productCount; i++) {
        // Case-insensitive search
        char lowerName[MAX_STRING_LENGTH];
        char lowerProductName[MAX_STRING_LENGTH];
        
        // Convert both strings to lowercase
        strcpy(lowerName, name);
        strcpy(lowerProductName, products[i].name);
        
        for (int j = 0; lowerName[j]; j++) {
            lowerName[j] = tolower(lowerName[j]);
        }
        
        for (int j = 0; lowerProductName[j]; j++) {
            lowerProductName[j] = tolower(lowerProductName[j]);
        }
        
        // Check if substring exists
        if (strstr(lowerProductName, lowerName) != NULL) {
            displayProductDetails(&products[i]);
            printf("-------------------\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No products found matching '%s'.\n", name);
    }
}

// Function to search for products by category
void searchProductsByCategory(const char *category) {
    displayProductsByCategory(category);
}

// Function to display all products
void displayAllProducts() {
    if (productCount == 0) {
        printf("No products in the database.\n");
        return;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           ALL PRODUCTS\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < productCount; i++) {
        displayProductDetails(&products[i]);
        printf("-------------------\n");
    }
}

// Function to display products filtered by category
void displayProductsByCategory(const char *category) {
    bool found = false;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m         PRODUCTS IN CATEGORY: %s\033[0m\n", category);
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].category, category) == 0) {
            displayProductDetails(&products[i]);
            printf("-------------------\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No products found in category '%s'.\n", category);
    }
}

// Function to display details for a specific product
void displayProductDetails(const Product *product) {
    printf("ID: %d\n", product->id);
    printf("Name: %s\n", product->name);
    printf("Price: $%.2f\n", product->price);
    printf("Quantity: %d\n", product->quantity);
    printf("Category: %s\n", product->category);
    printf("Description: %s\n", product->description);
    
    // Highlight low stock
    if (product->quantity <= 5 && product->quantity > 0) {
        printf("\033[1;33mLow Stock!\033[0m\n");
    } else if (product->quantity == 0) {
        printf("\033[1;31mOut of Stock!\033[0m\n");
    }
}

// Function to edit a product's information
bool editProduct(int id) {
    int index = findProductById(id);
    
    if (index == -1) {
        displayError("Product not found.");
        return false;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           EDIT PRODUCT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Editing product with ID: %d\n", id);
    printf("Current details:\n");
    displayProductDetails(&products[index]);
    
    printf("\nEnter new details (leave blank to keep current):\n");
    
    char buffer[MAX_STRING_LENGTH];
    
    printf("Name [%s]: ", products[index].name);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(products[index].name, buffer);
    }
    
    printf("Price [%.2f]: ", products[index].price);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        products[index].price = atof(buffer);
    }
    
    printf("Quantity [%d]: ", products[index].quantity);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        products[index].quantity = atoi(buffer);
    }
    
    printf("Category [%s]: ", products[index].category);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(products[index].category, buffer);
    }
    
    printf("Description [%s]: ", products[index].description);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(products[index].description, buffer);
    }
    
    // Save product data
    if (saveProductData()) {
        displaySuccess("Product updated successfully.");
        return true;
    } else {
        displayError("Failed to save product data.");
        return false;
    }
}

// Function to delete a product
bool deleteProduct(int id) {
    int index = findProductById(id);
    
    if (index == -1) {
        displayError("Product not found.");
        return false;
    }
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           DELETE PRODUCT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    printf("Are you sure you want to delete the following product?\n");
    displayProductDetails(&products[index]);
    
    printf("\nConfirm deletion (y/n): ");
    char confirmation;
    scanf("%c", &confirmation);
    clearInputBuffer();
    
    if (confirmation == 'y' || confirmation == 'Y') {
        // Remove product by shifting all elements down
        for (int i = index; i < productCount - 1; i++) {
            products[i] = products[i + 1];
        }
        
        productCount--;
        
        // Save product data
        if (saveProductData()) {
            displaySuccess("Product deleted successfully.");
            return true;
        } else {
            displayError("Failed to save product data.");
            return false;
        }
    } else {
        printf("Deletion cancelled.\n");
        return false;
    }
}

// Function to update product inventory
bool updateProductInventory(int id, int quantity) {
    int index = findProductById(id);
    
    if (index == -1) {
        displayError("Product not found.");
        return false;
    }
    
    // Check if removing more than available
    if (quantity < 0 && abs(quantity) > products[index].quantity) {
        displayError("Cannot remove more than available quantity.");
        return false;
    }
    
    // Update quantity
    products[index].quantity += quantity;
    
    // Save product data
    if (saveProductData()) {
        char message[100];
        if (quantity > 0) {
            snprintf(message, sizeof(message), "Added %d units to inventory. New quantity: %d", 
                     quantity, products[index].quantity);
        } else {
            snprintf(message, sizeof(message), "Removed %d units from inventory. New quantity: %d", 
                     abs(quantity), products[index].quantity);
        }
        displaySuccess(message);
        return true;
    } else {
        displayError("Failed to save product data.");
        return false;
    }
}

// Function to save product data to file
bool saveProductData() {
    FILE *file = fopen(PRODUCT_FILE, "wb");
    
    if (!file) {
        return false;
    }
    
    // Write the number of products
    fwrite(&productCount, sizeof(int), 1, file);
    
    // Write the product data
    fwrite(products, sizeof(Product), productCount, file);
    
    fclose(file);
    return true;
}

// Function to load product data from file
bool loadProductData() {
    FILE *file = fopen(PRODUCT_FILE, "rb");
    
    if (!file) {
        productCount = 0;
        return false;
    }
    
    // Read the number of products
    fread(&productCount, sizeof(int), 1, file);
    
    // Check if the number of products is valid
    if (productCount < 0 || productCount > MAX_ARRAY_SIZE) {
        productCount = 0;
        fclose(file);
        return false;
    }
    
    // Read the product data
    fread(products, sizeof(Product), productCount, file);
    
    fclose(file);
    return true;
}

// Function to sort products by ID
void sortProductsById() {
    // Selection sort algorithm
    for (int i = 0; i < productCount - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < productCount; j++) {
            if (products[j].id < products[minIndex].id) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            Product temp = products[i];
            products[i] = products[minIndex];
            products[minIndex] = temp;
        }
    }
}

// Function to sort products by name
void sortProductsByName() {
    // Selection sort algorithm
    for (int i = 0; i < productCount - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < productCount; j++) {
            if (strcmp(products[j].name, products[minIndex].name) < 0) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            Product temp = products[i];
            products[i] = products[minIndex];
            products[minIndex] = temp;
        }
    }
}

// Function to sort products by price (low to high)
void sortProductsByPrice() {
    // Selection sort algorithm
    for (int i = 0; i < productCount - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < productCount; j++) {
            if (products[j].price < products[minIndex].price) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            Product temp = products[i];
            products[i] = products[minIndex];
            products[minIndex] = temp;
        }
    }
}

// Function to sort products by quantity (high to low)
void sortProductsByQuantity() {
    // Selection sort algorithm
    for (int i = 0; i < productCount - 1; i++) {
        int maxIndex = i;
        
        for (int j = i + 1; j < productCount; j++) {
            if (products[j].quantity > products[maxIndex].quantity) {
                maxIndex = j;
            }
        }
        
        if (maxIndex != i) {
            Product temp = products[i];
            products[i] = products[maxIndex];
            products[maxIndex] = temp;
        }
    }
}

// Function to get product categories
int getProductCategories(char categories[][30], int maxCategories) {
    int count = 0;
    
    if (productCount == 0) {
        return 0;
    }
    
    // Add first category
    strcpy(categories[count++], products[0].category);
    
    // Check all products
    for (int i = 1; i < productCount && count < maxCategories; i++) {
        bool exists = false;
        
        // Check if category already exists
        for (int j = 0; j < count; j++) {
            if (strcmp(products[i].category, categories[j]) == 0) {
                exists = true;
                break;
            }
        }
        
        // Add new category
        if (!exists) {
            strcpy(categories[count++], products[i].category);
        }
    }
    
    return count;
}

// Function to find a product by ID
int findProductById(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    
    return -1; // Not found
}

// Function to find a product by name
int findProductByName(const char *name) {
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return i;
        }
    }
    
    return -1; // Not found
}

// Function to check if any products are low in stock
int checkLowStock(int threshold) {
    int count = 0;
    
    printf("\n\033[1;36m========================================\033[0m\n");
    printf("\033[1;32m           LOW STOCK REPORT\033[0m\n");
    printf("\033[1;36m========================================\033[0m\n");
    
    for (int i = 0; i < productCount; i++) {
        if (products[i].quantity <= threshold) {
            printf("ID: %d, Name: %s, Current Stock: %d\n", 
                   products[i].id, products[i].name, products[i].quantity);
            count++;
        }
    }
    
    return count;
}