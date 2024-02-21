#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "listComponent.h"
#include "templateCode.h"

// Assuming a component is 32x32 pixels
#define COMPONENT_SIZE 32

int **adjacencyMatrix;
int **visited;
int numOfComponents;

// Directions for traversal
int dx[] = {-1, 1, 0, 0}; 
int dy[] = {0, 0, -1, 1};

// Utility functions
int isInside(int x, int y, int height, int width) {
    return x >= 0 && x < height && y >= 0 && y < width;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Updated isPartOfComponent function to exclude start and end component
int isPartOfComponent(int x, int y , MatchedComponentsList components, int excludeStart, int excludeEnd) {
    for (int i = 0; i < components.count; i++) {
        if (i == excludeStart || i == excludeEnd) continue; // Skip start and end component
        int bottomLeftX = components.components[i].row;
        int bottomLeftY = components.components[i].col;
        if (x >= bottomLeftX && x < bottomLeftX + COMPONENT_SIZE &&
            y >= bottomLeftY && y < bottomLeftY + COMPONENT_SIZE) {
            return 1;
        }
    }
    return 0;
}


// Find the nearest path pixel to the bottom-left corner of a component
void findNearestPathPixel(int *x, int *y, int **binArray, int height, int width) {
    if (binArray[*x][*y] == 1) return; // Already a path pixel

    // Search for the nearest path pixel
    int found = 0;
    for (int distance = 1; !found && distance < max(height, width); ++distance) {
        for (int i = -distance; i <= distance && !found; ++i) {
            for (int j = -distance; j <= distance && !found; ++j) {
                int newX = *x + i;
                int newY = *y + j;
                if (isInside(newX, newY, height, width) && binArray[newX][newY] == 1) {
                    *x = newX;
                    *y = newY;
                    found = 1;
                    break;
                }
            }
        }
    }
}

// Depth-First Search to find path from start to end without crossing any other component
// Modified DFS_path function to include component exclusion logic
int DFS_path(int startX, int startY, int endX, int endY, int **array, MatchedComponentsList components, int height, int width, int startComponent, int endComponent) {
    if(startX == endX && startY == endY) return 1;

    visited[startX][startY] = 1;

    for(int i = 0; i < 4; i++) {
        int newX = startX + dx[i];
        int newY = startY + dy[i];

        if(isInside(newX, newY, height, width) && array[newX][newY] == 1 && !visited[newX][newY]) {
            // Check if the new coordinates are part of any component other than the start and end
            if (!isPartOfComponent(newX, newY, components, startComponent, endComponent)) {
                if(DFS_path(newX, newY, endX, endY, array, components, height, width, startComponent, endComponent)) return 1;
            }
        }
    }
    return 0;
}


void findConnections(MatchedComponentsList components, int **binArray, int height, int width) {
    numOfComponents = components.count;

    // Memory allocation for adjacencyMatrix
    adjacencyMatrix = (int **)malloc(numOfComponents * sizeof(int *));
    for (int i = 0; i < numOfComponents; i++) {
        adjacencyMatrix[i] = (int *)malloc(numOfComponents * sizeof(int));
        memset(adjacencyMatrix[i], 0, numOfComponents * sizeof(int));
    }

    // Memory allocation for visited matrix
    visited = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        visited[i] = (int *)malloc(width * sizeof(int));
        memset(visited[i], 0, width * sizeof(int));
    }

    // Iterating over all pairs of components to check for connections
    for (int i = 0; i < numOfComponents; i++) {
        for (int j = 0; j < numOfComponents; j++) {
            if (i == j) continue; // Skip same component check

            // Clear visited before each new search
            for (int k = 0; k < height; k++) {
                memset(visited[k], 0, width * sizeof(int));
            }

            int startX = components.components[i].row; // bottom-left corner of component i
            int startY = components.components[i].col;
            int endX = components.components[j].row; // bottom-left corner of component j
            int endY = components.components[j].col;

            // Move to the nearest path pixel to the bottom-left corner
            findNearestPathPixel(&startX, &startY, binArray, height, width);
            findNearestPathPixel(&endX, &endY, binArray, height, width);

            // If a path is found, set adjacency matrix to 1
            if (DFS_path(startX, startY, endX, endY, binArray, components, height, width, i, j)) {
                adjacencyMatrix[i][j] = 1;
                // Note: No need to set j,i since it's an undirected graph and will be set when j is the start component
            }
        }
    }

    // Printing connections
    for (int i = 0; i < numOfComponents; i++) {
        printf("Component %d connected to ", i);
        int connections = 0;
        for (int j = 0; j < numOfComponents; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                printf("%d ", j);
                connections++;
            }
        }
        if (connections == 0) {
            printf("nothing");
        }
        printf("\n");
    }

    // Free the visited matrix memory
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);

    // Free the adjacency matrix memory
    for (int i = 0; i < numOfComponents; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);
}


