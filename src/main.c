#include <stdio.h>
#include "headers/test.h"
#include "solver/solver.h"
#include "gui.h"
#include "neural_network/neural_network.h"


int main(int argc, char *argv[])
{
    Hello();
    GUI(argc, argv);
    //Neural_Network_Main("src/digits/one.png");

    // <===================== PART 1 =====================>
    //
    // Loading Data Set for Neural Network

    // Training Neural Network
    
    // <===================== PART 2 =====================>
    // Preprocessing (color) :
    // 		- Gauss
    // 		- Treshold
    // 		- Binarization, ect..

    // Homography
    
    // Edge detection
    
    // Cut digits grid

    // <===================== PART 3 =====================>
    // Using the Neural Network to detect digits
    
    // <===================== PART 4 =====================>
    // Resolution
    Solve_Sudoku();
    
    // Displaying grid on the final Image
    
    
    // <=====================   UI   =====================>
    

    return 0;
}
