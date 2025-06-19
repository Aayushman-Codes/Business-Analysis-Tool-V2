/**
 * Utils Header File
 * Contains utility functions for the Business Analysis and Management System
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>  // For size_t
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>   // For tolower()
// For mkdir()
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

// File path constants
#define CUSTOMER_FILE "data/customers.dat"
#define PRODUCT_FILE "data/products.dat"
#define TRANSACTION_FILE "data/transactions.dat"
#define FINANCIAL_FILE "data/financial.dat"
#define SALES_DATA_CSV "data/sales_data.csv"

// Maximum array sizes
#define MAX_ARRAY_SIZE 100
#define MAX_STRING_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200

// Error codes
#define SUCCESS 0
#define ERROR_FILE_NOT_FOUND 1
#define ERROR_MEMORY_ALLOCATION 2
#define ERROR_INVALID_INPUT 3
#define ERROR_DUPLICATE_ID 4
#define ERROR_ID_NOT_FOUND 5

/**
 * Clear the console screen
 */
void clearScreen();

/**
 * Clear the input buffer
 */
void clearInputBuffer();

/**
 * Display a pause message and wait for user to press Enter
 */
void pressEnterToContinue();

/**
 * Initialize the system - create necessary directories
 */
void initializeSystem();

/**
 * Validate a numeric input
 * @param value The value to validate
 * @param minValue The minimum allowed value
 * @param maxValue The maximum allowed value
 * @return true if the value is valid, false otherwise
 */
bool validateNumericInput(double value, double minValue, double maxValue);

/**
 * Check if a file exists
 * @param filename The name of the file to check
 * @return true if the file exists, false otherwise
 */
bool fileExists(const char *filename);

/**
 * Create directory if it doesn't exist
 * @param directoryName The name of the directory to create
 * @return true if successful, false otherwise
 */
bool createDirectory(const char *directoryName);

/**
 * Display an error message
 * @param message The error message to display
 */
void displayError(const char *message);

/**
 * Display a success message
 * @param message The success message to display
 */
void displaySuccess(const char *message);

/**
 * Generate a unique ID based on current time
 * @param prefix The prefix to use for the ID
 * @param idBuffer The buffer to store the generated ID
 * @param bufferSize The size of the buffer
 */
void generateUniqueId(const char *prefix, char *idBuffer, size_t bufferSize);

/**
 * Get the current date and time as a formatted string
 * @param buffer The buffer to store the formatted date and time
 * @param bufferSize The size of the buffer
 */
void getCurrentDateTime(char *buffer, size_t bufferSize);

/**
 * Encrypt a string (basic encryption for demonstration)
 * @param input The input string to encrypt
 * @param output The buffer to store the encrypted string
 * @param outputSize The size of the output buffer
 */
void encryptString(const char *input, char *output, size_t outputSize);

/**
 * Decrypt a string (basic decryption for demonstration)
 * @param input The input string to decrypt
 * @param output The buffer to store the decrypted string
 * @param outputSize The size of the output buffer
 */
void decryptString(const char *input, char *output, size_t outputSize);

/**
 * Safe string copy function to prevent buffer overflows
 * @param dest The destination buffer
 * @param destSize The size of the destination buffer
 * @param src The source string
 * @return The number of characters copied
 */
size_t safeStringCopy(char *dest, size_t destSize, const char *src);

#endif /* UTILS_H */