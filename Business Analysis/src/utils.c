/**
 * Utils Implementation File
 * Contains utility functions for the Business Analysis and Management System
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "globals.h"
#ifdef _WIN32
    #include <direct.h>  // For _mkdir on Windows
    #define MKDIR(dir) _mkdir(dir)  // Windows version takes one argument
#else
    #include <sys/stat.h>  // For mkdir on Unix-like systems
    #define MKDIR(dir) mkdir(dir, 0700)  // Unix version takes two arguments
#endif

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Function to display a pause message and wait for user to press Enter
void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Function to initialize the system - create necessary directories
void initializeSystem() {
    createDirectory("data");
}

// Function to validate a numeric input
bool validateNumericInput(double value, double minValue, double maxValue) {
    return (value >= minValue && value <= maxValue);
}

// Function to check if a file exists
bool fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

// Function to create directory if it doesn't exist
bool createDirectory(const char *directoryName) {
    struct stat st = {0};
    
    if (stat(directoryName, &st) == -1) {
        int result = MKDIR(directoryName);  // Use our platform-specific macro
        if (result == 0) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

// Function to display an error message
void displayError(const char *message) {
    printf("\033[1;31mERROR: %s\033[0m\n", message);
}

// Function to display a success message
void displaySuccess(const char *message) {
    printf("\033[1;32mSUCCESS: %s\033[0m\n", message);
}

// Function to generate a unique ID based on current time
void generateUniqueId(const char *prefix, char *idBuffer, size_t bufferSize) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    snprintf(idBuffer, bufferSize, "%s-%04d%02d%02d%02d%02d%02d",
             prefix,
             tm_now->tm_year + 1900,
             tm_now->tm_mon + 1,
             tm_now->tm_mday,
             tm_now->tm_hour,
             tm_now->tm_min,
             tm_now->tm_sec);
}

// Function to get the current date and time as a formatted string
void getCurrentDateTime(char *buffer, size_t bufferSize) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", tm_now);
}

// Function to encrypt a string (basic encryption for demonstration)
void encryptString(const char *input, char *output, size_t outputSize) {
    size_t inputLen = strlen(input);
    size_t i;
    
    for (i = 0; i < inputLen && i < outputSize - 1; i++) {
        output[i] = input[i] + 1; // Simple Caesar cipher with shift of 1
    }
    
    output[i] = '\0';
}

// Function to decrypt a string (basic decryption for demonstration)
void decryptString(const char *input, char *output, size_t outputSize) {
    size_t inputLen = strlen(input);
    size_t i;
    
    for (i = 0; i < inputLen && i < outputSize - 1; i++) {
        output[i] = input[i] - 1; // Simple Caesar cipher with shift of -1
    }
    
    output[i] = '\0';
}

// Function for safe string copy to prevent buffer overflows
size_t safeStringCopy(char *dest, size_t destSize, const char *src) {
    size_t srcLen = strlen(src);
    size_t copyLen = srcLen < destSize - 1 ? srcLen : destSize - 1;
    
    memcpy(dest, src, copyLen);
    dest[copyLen] = '\0';
    
    return copyLen;
}