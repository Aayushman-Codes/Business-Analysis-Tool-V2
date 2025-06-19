/**
 * Product Management Header File
 * Contains structures and function declarations for product management
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdbool.h>

// Product structure definition
typedef struct {
    int id;                // Unique identifier for the product
    char name[50];         // Product name
    double price;          // Product price
    int quantity;          // Current stock quantity
    char category[30];     // Product category
    char description[200]; // Product description
} Product;

/**
 * Run the product management module
 */
void runProductManagement();

/**
 * Add a new product
 * @return true if successful, false otherwise
 */
bool addProduct();

/**
 * Search for a product by ID
 * @param id The ID to search for
 * @return true if found, false otherwise
 */
bool searchProductById(int id);

/**
 * Search for products by name
 * @param name The name (or part of name) to search for
 */
void searchProductsByName(const char *name);

/**
 * Search for products by category
 * @param category The category to search for
 */
void searchProductsByCategory(const char *category);

/**
 * Display all products
 */
void displayAllProducts();

/**
 * Display products filtered by category
 * @param category The category to filter by
 */
void displayProductsByCategory(const char *category);

/**
 * Display details for a specific product
 * @param product Pointer to the product to display
 */
void displayProductDetails(const Product *product);

/**
 * Edit a product's information
 * @param id The ID of the product to edit
 * @return true if successful, false otherwise
 */
bool editProduct(int id);

/**
 * Delete a product
 * @param id The ID of the product to delete
 * @return true if successful, false otherwise
 */
bool deleteProduct(int id);

/**
 * Update product inventory
 * @param id The ID of the product to update
 * @param quantity The quantity to add (positive) or remove (negative)
 * @return true if successful, false otherwise
 */
bool updateProductInventory(int id, int quantity);

/**
 * Save product data to file
 * @return true if successful, false otherwise
 */
bool saveProductData();

/**
 * Load product data from file
 * @return true if successful, false otherwise
 */
bool loadProductData();

/**
 * Sort products by ID
 */
void sortProductsById();

/**
 * Sort products by name
 */
void sortProductsByName();

/**
 * Sort products by price (low to high)
 */
void sortProductsByPrice();

/**
 * Sort products by quantity (high to low)
 */
void sortProductsByQuantity();

/**
 * Get product categories
 * @param categories Array to store unique categories
 * @param maxCategories Maximum number of categories to store
 * @return Number of unique categories found
 */
int getProductCategories(char categories[][30], int maxCategories);

/**
 * Find a product by ID
 * @param id The ID to search for
 * @return Index of the product if found, -1 otherwise
 */
int findProductById(int id);

/**
 * Find a product by name
 * @param name The exact name to search for
 * @return Index of the product if found, -1 otherwise
 */
int findProductByName(const char *name);

/**
 * Check if any products are low in stock
 * @param threshold The threshold quantity
 * @return Number of products below the threshold
 */
int checkLowStock(int threshold);

#endif /* PRODUCT_H */