#ifndef TEMPLATECODE_H
#define TEMPLATECODE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @file templatecode.h
 * @brief Function prototypes for reading and printing bitmap template data.
 *
 * This header file contains the declarations of functions used for reading 
 * bitmap template data from a file into a 2D array and for printing that data.
 */

/**
 * Reads template data from a binary file into a 2D integer array.
 * 
 * @param filePath The path to the binary file containing the template data.
 * @param index The index of the template to read, starting from 0.
 * @return A pointer to a 2D array containing the template data. Each call
 *         to this function allocates memory for the template array which
 *         should be freed after use.
 */
int** readTemplateData(char *filePath, int index);

/**
 * Prints the template data from a 2D array to the console.
 * 
 * @param templateArray A pointer to a 2D array containing the template data.
 *                      Assumes a size of 32x32.
 */
void printTemplateArray(int **templateArray);

/**
 * Reads and prints a specified template from a binary file.
 * 
 * @param filePath The path to the binary file containing the template data.
 * @param index The index of the template to read and print, starting from 0.
 */
void printTemplate(char *filePath, int index);

#endif  // TEMPLATECODE_H
