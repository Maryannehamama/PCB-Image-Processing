#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "bitmap.h"
#include "templateCode.h"

#define threshold 127

typedef struct {
    int width;
    int height;
} Dimensions;

typedef struct {
    int type;
    int row;
    int col;
} Component;

typedef struct {
    Component* components;  
    int count;            
} MatchedComponentsList;


Dimensions applyThreshold(char *inputPath, char *outputPath) {
    // Load the BMP file
    Bmp bmp = read_bmp(inputPath);

    int width = bmp.width;
    int height = bmp.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char red = bmp.pixels[y][x][RED];
            unsigned char green = bmp.pixels[y][x][GREEN];
            unsigned char blue = bmp.pixels[y][x][BLUE];
            int sum = (red + green + blue) / 3;

            if (sum > threshold) {
                bmp.pixels[y][x][RED] = 255;
                bmp.pixels[y][x][GREEN] = 255;
                bmp.pixels[y][x][BLUE] = 255;
            } else {
                bmp.pixels[y][x][RED] = 0;
                bmp.pixels[y][x][GREEN] = 0;
                bmp.pixels[y][x][BLUE] = 0;
            }
        }
    }

    // Save the modified BMP file
    write_bmp(bmp, outputPath);

    // Clean up
    free_bmp(bmp);

    Dimensions dims;
    dims.width = width;
    dims.height = height;

    return dims;
}


int** read_bmp_into_array(char *filename, int height, int width) {
    // Read the BMP file using the provided function
    Bmp bmp = read_bmp(filename);

    // Confirm the dimensions from the BMP match the provided dimensions
    if(bmp.height != height || bmp.width != width) {
        fprintf(stderr, "Provided dimensions don't match the BMP dimensions.\n");
        exit(1);
    }

    // Allocate memory for the 2D array
    int **array = malloc(height * sizeof(int*));
    if(array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for(int i = 0; i < height; i++) {
        array[i] = malloc(width * sizeof(int));
        if(array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d.\n", i);
            exit(1);
        }
    }

    // Loop through each pixel and fill the array
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            unsigned char red = bmp.pixels[y][x][RED];
            unsigned char green = bmp.pixels[y][x][GREEN];
            unsigned char blue = bmp.pixels[y][x][BLUE];

            if(red == 255 && green == 255 && blue == 255) {
                array[y][x] = 1;
            } else {
                array[y][x] = 0;
            }
        }
    }

    // Free the bmp data
    free_bmp(bmp);

    return array;
}


void free_array(int** array, int height) {
    for(int i = 0; i < height; i++) {
        free(array[i]);
    }
    free(array);
}


bool matchTemplateAtPosition(int** image, int** templateData, int row, int col, int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (image[row + i][col + j] != templateData[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Component *matchedComponents; 
int matchedCount = 0;      


 void findComponentMatch(char *templateFilePath, int** image, int H, int W) {
    int M = 32;
    unsigned char byte;
    FILE *file = fopen(templateFilePath, "rb");
    if (file == NULL) {
        printf("Can't load template file\n");
        exit(1);
    }
    fread(&byte, sizeof(unsigned char), 1, file);
    int numOfTemplates = (int)byte;
    fclose(file);

    for (int templateIndex = 0; templateIndex < numOfTemplates; templateIndex++) {
        int** templateData = readTemplateData(templateFilePath, templateIndex);
        for (int row = 0; row <= H - M; row++) {
            for (int col = 0; col <= W - M; col++) {
                if (matchTemplateAtPosition(image, templateData, row, col, M)) {
                    matchedComponents[matchedCount].type = templateIndex;
                    matchedComponents[matchedCount].row = row;
                    matchedComponents[matchedCount].col = col;
                    matchedCount++;
                }
            }
        }
        for (int i = 0; i < M; i++) {
            free(templateData[i]);
        }
        free(templateData);
    }
}


 int compareComponents(const void *a, const void *b) {
    Component *compA = (Component *)a;
    Component *compB = (Component *)b;
    if (compA->row != compB->row) {
        return compA->row - compB->row;
    }
    return compA->col - compB->col;
}


MatchedComponentsList listComponents(char *templateFile, char *inputPath, char *outputPath) {
    FILE *file;

    file = fopen(templateFile, "rb");
    if (file == NULL) {
        printf("Can't load template file\n");
        exit(1);
    }

    Dimensions dims = applyThreshold(inputPath, outputPath);

    // Allocate maximum possible size (considering every position matches a template)
    matchedComponents = malloc(dims.height * dims.width * sizeof(Component));

    int **array = read_bmp_into_array(outputPath, dims.height, dims.width);
    findComponentMatch(templateFile, array, dims.height, dims.width);

    // Sort matched components
    qsort(matchedComponents, matchedCount, sizeof(Component), compareComponents);

    // Print matched components in sorted order
    printf("Found %d components:\n", matchedCount);
    for (int i = 0; i < matchedCount; i++) {
        printf("type: %d, row: %d, column: %d\n", matchedComponents[i].type, matchedComponents[i].row, matchedComponents[i].col);
    }

    MatchedComponentsList resultList;
    resultList.components = matchedComponents;
    resultList.count = matchedCount;

    // Cleanup
    free_array(array, dims.height);

    return resultList; // Return the list of matched components and their count
}

