//
// Created by M on 10/11/2024.
//

#ifndef TEST3DCUBE_TWODMATHMANAGER_H
#define TEST3DCUBE_TWODMATHMANAGER_H
#include "Cube.h"
#include <vector>


class TwoDMathManager {

//store projected points
public:
    //cube
    Cube *cube;

    //points as projected onto 2dimensions
    // struct SDL_Point just has an x int and a y int
    // corner no (1-8) is the key
    std::map<int, SDL_Point> frameCoords{};

    //store magnitudes of each vector from origin to point in 3 space.
    //Origin is center point of the viewing frame
    std::vector<magCard> magnitudes{};

    float avgMag;
    float avgZ;




    //constructor
    explicit TwoDMathManager(Cube *cuber){
        cube = cuber;
    }


    void projectCubeToFrame();
    void populateAdjacents();
    void calcMagnitudes();
    void sortMagnitudes();


    std::vector<int> findDrawableCorners();



    std::map<int, adjacents> adjacentsMap;

    int isNotWithinSquare(int hypot1, int c1, int c2, int c3, int c4, int newC);
    int quantAdjacentsAmongGiven(int toCheck, int c1, int c2, int c3);


};


#endif //TEST3DCUBE_TWODMATHMANAGER_H
