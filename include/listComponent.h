#ifndef LISTCOMPONENT_H
#define LISTCOMPONENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "bitmap.h"

#define threshold 127

/**
 * Structure to store dimensions of an image.
 */
typedef struct {
    int width;  // The width of the image in pixels.
    int height; // The height of the image in pixels.
} Dimensions;

/**
 * Structure to represent a single image component (detected feature).
 */
typedef struct {
    int type; // Type identifier of the component.
    int row;  // Row position of the component in the image.
    int col;  // Column position of the component in the image.
} Component;

/**
 * Structure to hold a list of matched components within an image.
 */
typedef struct {
    Component* components;  // Array of matched components.
    int count;              // Number of matched components.
} MatchedComponentsList;

/**
 * Applies a threshold to convert an image to binary format.
 *
 * @param inputPath Path to the input image file.
 * @param outputPath Path where the binary image will be saved.
 * @return Dimensions of the thresholded image.
 */
Dimensions applyThreshold(char *inputPath, char *outputPath);

/**
 * Reads a bitmap image file into a 2D integer array with binary values.
 *
 * @param filename Path to the image file.
 * @param height The height of the image in pixels.
 * @param width The width of the image in pixels.
 * @return A pointer to the 2D array of integers representing the binary image.
 */
int** read_bmp_into_array(char *filename, int height, int width);

/**
 * Frees the memory allocated for a 2D integer array.
 *
 * @param array The 2D array to be freed.
 * @param height The number of rows in the array.
 */
void free_array(int** array, int height);

/**
 * Checks if a template matches the image at the specified location.
 *
 * @param image A 2D array representing the binary image.
 * @param templateData A 2D array representing the binary template.
 * @param row The row position to start matching.
 * @param col The column position to start matching.
 * @param M The dimension of the template (assumed square).
 * @return True if the template matches, false otherwise.
 */
bool matchTemplateAtPosition(int** image, int** templateData, int row, int col, int M);

/**
 * Finds and lists all components in an image that match a given template.
 *
 * @param templateFile Path to the file containing the template data.
 * @param inputPath Path to the input image file.
 * @param outputPath Path to save the output image with matched components highlighted.
 * @return A MatchedComponentsList structure containing all matched components.
 */
MatchedComponentsList listComponents(char *templateFile, char *inputPath, char *outputPath);


/**
 * Comparator function for sorting components based on their position in the image.
 *
 * @param a The first component to compare.
 * @param b The second component to compare.
 * @return An integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater than the second.
 */
int compareComponents(const void *a, const void *b);


/**
 * Finds all matches of the template in the given image at all possible positions.
 *
 * @param templateFilePath Path to the template file.
 * @param image A 2D array representing the binary image.
 * @param H The height of the image.
 * @param W The width of the image.
 */
void findComponentMatch(char *templateFilePath, int** image, int H, int W);


#endif /* LISTCOMPONENT_H */
