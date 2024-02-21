# PCB-Image-Processing

The software will be provided with images of circuit boards, and using a database of known components, it will map the layout of components detected in the images and the various electrical connections between them using the visible PCB trace lines.


## New Skills Gained From This Project 
🔌 Image Processing: Understanding and implementing algorithms for image recognition and analysis.

🔍 Pattern Matching: Utilizing pattern matching techniques to identify components within images.

🧩 Data Parsing: Parsing binary data files to extract information about component templates.

🛠 Command Line Interface (CLI): Developing programs that interact with users through the command line.

📄 File Handling: Reading and processing data from BMP and custom binary files.

💡 Problem Solving: Addressing challenges such as edge cases and incorrect inputs to ensure robust program behavior.

📊 Data Mapping: Mapping out electrical connections between components based on visual traces in images.

🖥️ Software Development: Building a program with multiple modes of operation to fulfill different functionalities.

🌀 Convolutional Neural Networks: Understanding and implementing convolutions for image processing tasks, such as feature extraction and pattern recognition.


## Overview Of Functionality 
The program you developed reads in two files: (a) a BMP format file that contains an image of the target/manufactured PCB and (b) a custom binary data file which contains image template data for a library of possible components that may appear on the PCB. The program has implemented three key capabilities:

**Output/display template data**: The program will print to the screen information for a selected template component

**List/Map components**: The program will identify the location in the image of electronic components using the template library and report these to the user.

**Map electrical connections**: The program will build a list of which components are electrically connected to one another on the PCB by analysing the traces in the image.

## Program Input Format 

The program will be run from the command line in the following format:

./pcb_check <mode t|l|c> <template_filename> <index or board_image_filename>

The first argument passed to the program is the program mode (can be 't', 'l' or 'c'). The second argument is the file path to the image template library file. The third argument is either an index integer of one of the components in the library file (for mode 't') or the file path to the PCB image file (for modes 'l' and 'c').

The program mode can be one of three possible values:

**Mode 't'**: template mode: in this mode, the program reads the template file and prints to the screen a representation of the component template corresponding to the index provided as an integer in the third argument.

**Mode 'l'**: component list mode: in this mode, the program uses the template library file (argument 2) and the PCB image file (argument 3) to identify any components on the PCB (using template matching) and list their positions and types according to the library.

**Mode 'c'**: check connections mode: in this mode, the program detects and lists components (as for mode 'l') and also lists the electrical connections between each of the components identified.

The program also deals with edge cases and incorrect inputs. 

