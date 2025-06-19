/**
 * Trend Analysis Header File
 * Contains structures and function declarations for trend analysis
 */

#ifndef TREND_ANALYSIS_H
#define TREND_ANALYSIS_H

#include <stdbool.h>

/**
 * Run the trend analysis module
 */
void runTrendAnalysis();

/**
 * Generate sales trend data for visualization
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @param interval Interval for data points (daily, weekly, monthly)
 * @return true if successful, false otherwise
 */
bool generateSalesTrend(const char *startDate, const char *endDate, const char *interval);

/**
 * Generate product sales trend data for visualization
 * @param productId Product ID to analyze (0 for all products)
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @param interval Interval for data points (daily, weekly, monthly)
 * @return true if successful, false otherwise
 */
bool generateProductSalesTrend(int productId, const char *startDate, const char *endDate, const char *interval);

/**
 * Generate category sales trend data for visualization
 * @param category Category to analyze (empty for all categories)
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @param interval Interval for data points (daily, weekly, monthly)
 * @return true if successful, false otherwise
 */
bool generateCategorySalesTrend(const char *category, const char *startDate, const char *endDate, const char *interval);

/**
 * Generate profit trend data for visualization
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @param interval Interval for data points (daily, weekly, monthly)
 * @return true if successful, false otherwise
 */
bool generateProfitTrend(const char *startDate, const char *endDate, const char *interval);

/**
 * Generate expense trend data for visualization
 * @param category Expense category to analyze (empty for all categories)
 * @param startDate Start date of the period
 * @param endDate End date of the period
 * @param interval Interval for data points (daily, weekly, monthly)
 * @return true if successful, false otherwise
 */
bool generateExpenseTrend(const char *category, const char *startDate, const char *endDate, const char *interval);

/**
 * Export trend data to CSV file for visualization
 * @param trendType Type of trend to export (sales, product_sales, category_sales, profit, expense)
 * @param filename Name of the file to export to
 * @return true if successful, false otherwise
 */
bool exportTrendData(const char *trendType, const char *filename);

/**
 * Show sales graph using Python script
 * @param dataFile Path to CSV data file
 * @param title Title for the graph
 * @param xLabel Label for x-axis
 * @param yLabel Label for y-axis
 * @return true if successful, false otherwise
 */
bool showSalesGraph(const char *dataFile, const char *title, const char *xLabel, const char *yLabel);

/**
 * Calculate revenue forecast
 * @param months Number of months to forecast
 * @return Forecasted revenue
 */
double calculateRevenueForecast(int months);

/**
 * Calculate expense forecast
 * @param months Number of months to forecast
 * @return Forecasted expenses
 */
double calculateExpenseForecast(int months);

/**
 * Calculate profit forecast
 * @param months Number of months to forecast
 * @return Forecasted profit
 */
double calculateProfitForecast(int months);

/**
 * Generate sales forecast report
 * @param months Number of months to forecast
 */
void generateSalesForecastReport(int months);

#endif /* TREND_ANALYSIS_H */