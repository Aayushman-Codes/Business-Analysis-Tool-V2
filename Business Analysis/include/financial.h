/**
 * Financial Analysis Header File
 * Contains structures and function declarations for financial analysis
 */

#ifndef FINANCIAL_H
#define FINANCIAL_H

#include <stdbool.h>

// Financial record structure
typedef struct {
    char date[20];            // Date of the record
    char category[30];        // Category (e.g., Sales, Expense, Profit)
    double amount;            // Amount
    char type[10];            // Type (Income or Expense)
    char description[200];    // Description
} FinancialRecord;

/**
 * Run the financial analysis module
 */
void runFinancialAnalysis();

/**
 * Add a new financial record
 * @param date Date of the record
 * @param category Category of the record
 * @param amount Amount
 * @param type Type of record (Income or Expense)
 * @param description Description of the record
 * @return true if successful, false otherwise
 */
bool addFinancialRecord(const char *date, const char *category, double amount, const char *type, const char *description);

/**
 * Calculate income for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @return Total income for the period
 */
double calculateIncome(const char *startDate, const char *endDate);

/**
 * Calculate expenses for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @return Total expenses for the period
 */
double calculateExpenses(const char *startDate, const char *endDate);

/**
 * Calculate profit for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @return Profit for the period
 */
double calculateProfit(const char *startDate, const char *endDate);

/**
 * Calculate profit margin for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @return Profit margin as a percentage
 */
double calculateProfitMargin(const char *startDate, const char *endDate);

/**
 * Generate income statement for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 */
void generateIncomeStatement(const char *startDate, const char *endDate);

/**
 * Generate expense report for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 */
void generateExpenseReport(const char *startDate, const char *endDate);

/**
 * Generate profit and loss report for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 */
void generateProfitLossReport(const char *startDate, const char *endDate);

/**
 * Display financial records for a given period
 * @param startDate Start date of the period
 * @param endDate End date of the period
 */
void displayFinancialRecords(const char *startDate, const char *endDate);

/**
 * Save financial data to file
 * @return true if successful, false otherwise
 */
bool saveFinancialData();

/**
 * Load financial data from file
 * @return true if successful, false otherwise
 */
bool loadFinancialData();

/**
 * Export financial data to CSV file
 * @param filename Name of the file to export to
 * @param startDate Start date for filtering (optional)
 * @param endDate End date for filtering (optional)
 * @return true if successful, false otherwise
 */
bool exportFinancialData(const char *filename, const char *startDate, const char *endDate);

#endif /* FINANCIAL_H */