#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "templateCode.h"
#include "connectionsFinder.h"
#include "listComponent.h"

// Mode definitions for clarity
#define t 't' // Template reading mode
#define l 'l' // Component listing mode
#define c 'c' // Connectivity checking mode

/**
 * The main function to execute different modes based on command line arguments.
 * 
 * @param argc The count of command line arguments.
 * @param argv The argument vector containing command line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char *argv[]) 
{ 
    // Error Handling: Checks for the correct number of command line arguments
    if (argc != 4){
        printf("Invalid arguements!\n");
        return 1; // Exit with status 1 indicating error
    }
    // Error Handling: Checks if the selected mode is valid
    else if (*argv[1] != t && *argv[1] != l && *argv[1] != c){
        printf("Invalid mode selected!\n");
        return 1; // Exit with status 1 indicating error
    }

    // Template reading mode
    if (*argv[1] == t){
        // Call function to print template information based on given arguments
        printTemplate(argv[2], atoi(argv[3]));
    }
    
    // Component listing mode
    if (*argv[1] == l){
        // Call function to apply thresholding and list components
        listComponents(argv[2], argv[3], "images/pcbThreshold.bmp");
    }
    
    // Connectivity checking mode
    if (*argv[1] == c){
        // Generate and store the list of matched components
        MatchedComponentsList components = listComponents(argv[2], argv[3], "images/pcbThreshold.bmp");
        
        // Apply thresholding and get dimensions of the processed image
        Dimensions dims = applyThreshold(argv[3], "images/pcbThreshold.bmp");

        // Read bitmap image into an array for processing
        int **binArray = read_bmp_into_array("images/pcbThreshold.bmp", dims.height, dims.width);

        // Call function to find connections between components
        findConnections(components, binArray, dims.height, dims.width);
        free_array(binArray, dims.height);
    }

    return 0;
}


