#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


int** readTemplateData(char *filePath, int index) {
    FILE *file;
    unsigned char byte;
    int numOfTemplates;
    // Allocate memory for a 2D array to store template data
    int** templateArray = (int**)malloc(32 * sizeof(int*));

    // Open the binary file for reading
    file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("Can't load template file\n");
        exit(1); // Exit if file cannot be opened
    }

    // Allocate memory for each row of the template
    for(int i = 0; i < 32; i++) {
        templateArray[i] = (int*)malloc(32 * sizeof(int));
    }

    // Read the first byte to get the number of templates in the file
    fread(&byte, sizeof(unsigned char), 1, file);
    numOfTemplates = (int) byte;

    // Check if the provided index is within the range of available templates
    if(index >= numOfTemplates) {
        printf("Template index out of range\n");
        fclose(file); // Close the file before exiting
        exit(1); // Exit if index is out of range
    }

    // Read the template data into the 2D array
    for (int row = 31; row >= 0; row--) {  // Start from the bottom row
        // Position to the correct row in the binary file for the given index
        fseek(file, 1 + index * 128 + row * 4, SEEK_SET);
        int col = 0;
        for (int colByte = 0; colByte < 4; colByte++) {
            fread(&byte, sizeof(unsigned char), 1, file);
            // Convert each bit in the byte to an integer in the array
            for (int bit = 7; bit >= 0; bit--) {
                templateArray[row][col] = (byte & (1 << bit)) ? 1 : 0;
                col++;
            }
        }
    }
    fclose(file); // Close the file after reading
    return templateArray;
}


void printTemplateArray(int **templateArray) {
    printf("Template data:\n");
    // Iterate through the 2D array and print template data
    for (int i = 31; i >= 0; i--) {  // Start from the bottom-most row
        for (int j = 0; j < 32; j++) {
            // Print 1 for bits set, and space for bits not set
            printf("%c", templateArray[i][j] ? '1' : ' ');
        }
        printf("\n");
    }
}


void printTemplate(char *filePath, int index) {
    // Read template data from the file
    int **templateArray = readTemplateData(filePath, index);
    // Print the template data
    printTemplateArray(templateArray);

    // Free the dynamically allocated memory for the template array
    for(int i = 0; i < 32; i++) {
        free(templateArray[i]);
    }
    free(templateArray);
}




