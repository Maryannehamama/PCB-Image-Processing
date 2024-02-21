#ifndef CONNECTIONSFINDER_H
#define CONNECTIONSFINDER_H

#include "listComponent.h"

// Constants
#define COMPONENT_SIZE 32 // Represents the fixed size for a component in pixels.

/**
 * Function to check if the given coordinates are within the bounds of the image.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @param height The height of the image.
 * @param width The width of the image.
 * @return 1 if inside the bounds, 0 otherwise.
 */
int isInside(int x, int y, int height, int width);

/**
 * Function to return the maximum of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return The larger of the two integers.
 */
int max(int a, int b);

/**
 * Function to check if a given pixel is part of a component, excluding start and end components.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param components List of all components.
 * @param excludeStart Index of the start component to exclude from check.
 * @param excludeEnd Index of the end component to exclude from check.
 * @return 1 if the pixel is part of a component (other than start/end), 0 otherwise.
 */
int isPartOfComponent(int x, int y , MatchedComponentsList components, int excludeStart, int excludeEnd);

/**
 * Function to find the nearest path pixel to the bottom-left corner of a component.
 * @param x Pointer to the x-coordinate, will be updated with the new position.
 * @param y Pointer to the y-coordinate, will be updated with the new position.
 * @param binArray The binary array representing the image.
 * @param height The height of the image.
 * @param width The width of the image.
 */
void findNearestPathPixel(int *x, int *y, int **binArray, int height, int width);

/**
 * Recursive function that uses Depth-First Search to find a path from start to end.
 * It avoids crossing any other component except for start and end.
 * @param startX The starting x-coordinate.
 * @param startY The starting y-coordinate.
 * @param endX The ending x-coordinate.
 * @param endY The ending y-coordinate.
 * @param array The binary array representing the image.
 * @param components List of all matched components.
 * @param height The height of the image.
 * @param width The width of the image.
 * @param startComponent The index of the starting component.
 * @param endComponent The index of the ending component.
 * @return 1 if a path is found, 0 otherwise.
 */
int DFS_path(int startX, int startY, int endX, int endY, int **array, MatchedComponentsList components, int height, int width, int startComponent, int endComponent);

/**
 * Function to find and print all the connections between components based on paths found in binArray.
 * @param components List of all matched components.
 * @param binArray The binary array representing the image.
 * @param height The height of the image.
 * @param width The width of the image.
 */
void findConnections(MatchedComponentsList components, int **binArray, int height, int width);

#endif // CONNECTIONSFINDER_H
