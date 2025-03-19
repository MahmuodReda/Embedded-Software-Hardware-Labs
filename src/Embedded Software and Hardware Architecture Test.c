#include <stdio.h>
#include <stdint.h>

/*
 * =============================================================================
 * Example 1: Weather Sample Structure
 * =============================================================================
 * This structure stores weather data such as temperature, wind speed, wind direction,
 * humidity, and a timestamp for the measurement.
 *
 * Memory Consideration:
 * - The structure variables are typically stored on the Stack if declared locally
 *   or in the Data Section if declared globally.
 * - Using typedef simplifies the declaration of variables of this structure type.
 */
typedef struct {
    float temperature;      // Temperature in Celsius
    float windSpeed;        // Wind speed in km/h
    uint8_t windDirection;  // Wind direction in degrees (0-359)
    uint8_t humidity;       // Humidity in percentage (0-100)
    uint32_t timestamp;     // Timestamp representing the time of measurement
} WeatherSample;

/*
 * printWeather - Prints the contents of a WeatherSample structure.
 * @param sample: A pointer to a WeatherSample variable.
 *
 * This function encapsulates the process of accessing the structure's members.
 * If the structure definition changes, only this function needs to be updated.
 * Memory: Uses the pointer passed as parameter, typically on the Stack.
 */
void printWeather(const WeatherSample* sample) {
    printf("Temperature: %.2f °C\n", sample->temperature);   // Expected: e.g., 25.50 °C
    printf("Wind Speed: %.2f km/h\n", sample->windSpeed);       // Expected: e.g., 15.20 km/h
    printf("Wind Direction: %u°\n", sample->windDirection);     // Expected: e.g., 90°
    printf("Humidity: %u%%\n", sample->humidity);                // Expected: e.g., 75%
    printf("Timestamp: %u\n", sample->timestamp);               // Expected: e.g., 1623678000
}

/*
 * =============================================================================
 * Example 2: Ball Movement Structure
 * =============================================================================
 * This structure represents the movement of a ball in 3D space.
 * It includes coordinates (x, y, z), a timestamp, and a count of data points.
 *
 * Memory Consideration:
 * - As with other structures, instances are stored on the Stack (if local) or in the Data Section (if global).
 */
typedef struct {
    float x;           // X coordinate
    float y;           // Y coordinate
    float z;           // Z coordinate
    uint32_t time;     // Timestamp of the measurement
    uint16_t dataPoints; // Number of data points recorded
} BallMovement;

/*
 * updateBallMovement - Updates the ball movement structure with new data.
 * @param bm: Pointer to a BallMovement structure.
 * @param newX: New x coordinate.
 * @param newY: New y coordinate.
 * @param newZ: New z coordinate.
 * @param newTime: New timestamp.
 *
 * This function encapsulates the process of updating the ball movement data,
 * including incrementing the data points counter. It prevents repetitive code and errors.
 * Memory: Uses a pointer parameter (Stack), and updates the structure in its allocated memory.
 */
void updateBallMovement(BallMovement* bm, float newX, float newY, float newZ, uint32_t newTime) {
    bm->x = newX;
    bm->y = newY;
    bm->z = newZ;
    bm->time = newTime;
    bm->dataPoints++;  // Increment the number of data points
}

/*
 * printBallMovement - Prints the details of a BallMovement structure.
 * @param bm: A pointer to a BallMovement structure.
 *
 * This function provides a clear interface for displaying the ball movement data.
 * Memory: Uses the pointer passed as parameter.
 */
void printBallMovement(const BallMovement* bm) {
    printf("Ball Position: (%.2f, %.2f, %.2f)\n", bm->x, bm->y, bm->z); // Expected: e.g., (0.00, 0.00, 0.00) or updated values
    printf("Timestamp: %u\n", bm->time);                                  // Expected: e.g., 0 or updated timestamp
    printf("Data Points: %u\n", bm->dataPoints);                           // Expected: e.g., 0 initially, then incremented
}

/*
 * =============================================================================
 * Main Function: Combining All Examples
 * =============================================================================
 * This main function demonstrates:
 * 1. Using a WeatherSample structure to store and print weather data.
 * 2. Using a BallMovement structure to track a ball's movement and update its data.
 *
 * Each structure instance is handled via functions that encapsulate the operations,
 * ensuring the code remains maintainable and portable.
 */
int main() {
    printf("\n--- Weather Sample Example ---\n\n");

    // Example 1: Weather Sample
    WeatherSample ws = {25.5, 15.2, 90, 75, 1623678000}; // Initialize with sample data
    printWeather(&ws);  // Expected output: Temperature: 25.50 °C, Wind Speed: 15.20 km/h, Wind Direction: 90°, Humidity: 75%, Timestamp: 1623678000

    printf("\n--- Ball Movement Example ---\n\n");

    // Example 2: Ball Movement
    BallMovement bm = {0.0, 0.0, 0.0, 0, 0}; // Initialize with zero values
    printf("Initial Ball Movement:\n");
    printBallMovement(&bm); // Expected output: Ball Position: (0.00, 0.00, 0.00), Timestamp: 0, Data Points: 0

    // Update the ball movement with new data.
    updateBallMovement(&bm, 10.5, 20.5, 30.5, 1623678100);
    printf("\nAfter Updating Ball Movement:\n");
    printBallMovement(&bm); // Expected output: Ball Position: (10.50, 20.50, 30.50), Timestamp: 1623678100, Data Points: 1

    return 0;
}


//
//		--- Weather Sample Example ---
//
//		Temperature: 25.50 °C
//		Wind Speed: 15.20 km/h
//		Wind Direction: 90°
//		Humidity: 75%
//		Timestamp: 1623678000
//
//		--- Ball Movement Example ---
//
//		Initial Ball Movement:
//		Ball Position: (0.00, 0.00, 0.00)
//		Timestamp: 0
//		Data Points: 0
//
//		After Updating Ball Movement:
//		Ball Position: (10.50, 20.50, 30.50)
//		Timestamp: 1623678100
//		Data Points: 1
