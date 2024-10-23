//
// Created by M on 10/11/2024.
//

#include "TwoDMathManager.h"

void TwoDMathManager::projectCubeToFrame() {

    float newX, newY;
//    float scale = std::sqrt(150/avgMag);
    float scale = std::sqrt(150/avgZ);



    for (int x=1;x<9; x++){

        newX = cube->corners[x-1].x*scale;
        newY = cube->corners[x-1].y*scale;
        frameCoords[x] = {static_cast<int>(newX+350), static_cast<int>(newY+350)};
    }



}

void TwoDMathManager::calcMagnitudes() {
    float sum = 0;
    float sumZ = 0;
    for (int x = 0; x<8;x++){
        float mag = std::sqrt((float)
                                      (cube->corners[x].x*cube->corners[x].x +
                                       cube->corners[x].y*cube->corners[x].y +
                                       cube->corners[x].z*cube->corners[x].z));
        magCard mg = {x+1, mag};
        magnitudes.push_back(mg);
        sum+=mag;
        sumZ+=cube->corners[x].z;
    }
    avgMag = sum/8;
    avgZ = sumZ/8;
}


//sort foo
bool compareMags(const magCard& a, const magCard&b){
    return a.magnitude < b.magnitude;
}
void TwoDMathManager::sortMagnitudes() {
    std::sort(magnitudes.begin(), magnitudes.end(), compareMags);
}

int triArea(SDL_Point a, SDL_Point b, SDL_Point c){
    return std::abs(a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));
}

bool isWithinTriangle(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point p){

    int bigT = triArea(a, b, c);

    int littleT1, littleT2, littleT3;

    littleT1 = triArea(p, b, c);
    littleT2 = triArea(a, p, c);
    littleT3 = triArea(a, b, p);

    if (bigT == (littleT1+littleT2+littleT3)) return true;
    else return false;



}

int TwoDMathManager::isNotWithinSquare(int hypot1, int c1, int c2, int c3, int c4, int newC){

    bool t1, t2;
    if (hypot1 == c2) {
        t1 = isWithinTriangle(frameCoords[c1], frameCoords[c2], frameCoords[c3], frameCoords[newC]);
        t2 = isWithinTriangle(frameCoords[c1], frameCoords[c2], frameCoords[c4], frameCoords[newC]);
    }else if (hypot1 == c3){
        t1 = isWithinTriangle(frameCoords[c1], frameCoords[c3], frameCoords[c2], frameCoords[newC]);
        t2 = isWithinTriangle(frameCoords[c1], frameCoords[c3], frameCoords[c4], frameCoords[newC]);
    } else if (hypot1 == c4){
        t1 = isWithinTriangle(frameCoords[c1], frameCoords[c4], frameCoords[c2], frameCoords[newC]);
        t2 = isWithinTriangle(frameCoords[c1], frameCoords[c4], frameCoords[c3], frameCoords[newC]);
    } else {
        SDL_Log("Error. no non-adjacent cornerNo recorded despite counting 2 adjacents in pass 1. Fix. \n see linemanager::finddrawablecorners");
        exit(99);
    }

    if(!t1 && !t2){
        return newC;
    } else return 0;
}

int TwoDMathManager::quantAdjacentsAmongGiven(int toCheck, int c1, int c2, int c3){
    int noAdj = 0;
    if (adjacentsMap[toCheck].a==c1 || adjacentsMap[toCheck].b==c1 || adjacentsMap[toCheck].c==c1) noAdj++;
    if (adjacentsMap[toCheck].a==c2 || adjacentsMap[toCheck].b==c2 || adjacentsMap[toCheck].c==c2) noAdj++;
    if (adjacentsMap[toCheck].a==c3 || adjacentsMap[toCheck].b==c3 || adjacentsMap[toCheck].c==c3) noAdj++;
    return noAdj;
}

std::vector<int> TwoDMathManager::findDrawableCorners() {

    int c1, c2, c3, c4, c5, c6, c7, c8;
    std::vector<int> drawableCorners;
    std::vector<int> addCorners;


    c1=magnitudes[0].cornerNo; drawableCorners.push_back(c1);
    c2=magnitudes[1].cornerNo; drawableCorners.push_back(c2);
    c3=magnitudes[2].cornerNo; drawableCorners.push_back(c3);
    c4=magnitudes[3].cornerNo; drawableCorners.push_back(c4);

    //check adjacents relative to one. .
    int noAdjC1 = 0, hypot1; //hypotenuse endpoint will always be c1.
    if (adjacentsMap[c1].a==c2 || adjacentsMap[c1].b==c2 || adjacentsMap[c1].c==c2) noAdjC1++;
    else hypot1 = c2;
    if (adjacentsMap[c1].a==c3 || adjacentsMap[c1].b==c3 || adjacentsMap[c1].c==c3) noAdjC1++;
    else hypot1 = c3;
    if (adjacentsMap[c1].a==c4 || adjacentsMap[c1].b==c4 || adjacentsMap[c1].c==c4) noAdjC1++;
    else hypot1 = c4;


    if (noAdjC1 == 2){ //First 4 present a square, not a cross.

        c5 = isNotWithinSquare(hypot1, c1, c2, c3, c4, magnitudes[4].cornerNo);
        c6 = isNotWithinSquare(hypot1, c1, c2, c3, c4, magnitudes[5].cornerNo);
        c7 = isNotWithinSquare(hypot1, c1, c2, c3, c4, magnitudes[6].cornerNo);
        c8 = isNotWithinSquare(hypot1, c1, c2, c3, c4, magnitudes[7].cornerNo);


        if(c5!=0) addCorners.push_back(c5);
        if(c6!=0) addCorners.push_back(c6);
        if(c7!=0) addCorners.push_back(c7);
        if(c8!=0) addCorners.push_back(c8);

        //LOG - logging coordinates when furthest 4 are all outside the closest 4
        if(addCorners.size()==4){
            for(int x = 0; x<8; x++){
                SDL_Log("C%d -- xy: (%d,%d)\nCube x:%f - y:%f -- magnitude: %f -"
                        "- proj: %d", x+1, frameCoords[x+1].x, frameCoords[x+1].y,
                cube->corners[x].x, cube->corners[x].y, magnitudes[x].magnitude, static_cast<int>((cube->corners[x].x)*(1/(.0066*magnitudes[x].magnitude))));
            }
        }
        //END


        for (auto& it : addCorners){
            drawableCorners.push_back(it);
        }

        return drawableCorners;

    } else {
        //Projected 4 take a cross shape...
//        *     |
//        *     *
//        *    / \
        //Step 1. Determine the center point.
        int spoke1, spoke2, spoke3;
        if(quantAdjacentsAmongGiven(c1, c2, c3, c4)==3){
            spoke1=c2; spoke2=c3; spoke3=c4;
        } else if(quantAdjacentsAmongGiven(c2, c3, c4, c1)==3){
            spoke1=c1; spoke2=c3; spoke3=c4;
        } else if(quantAdjacentsAmongGiven(c3, c4, c1, c2)==3){
            spoke1=c2; spoke2=c1; spoke3=c4;
        }else {
            spoke1=c2; spoke2=c3; spoke3=c1;
        }


        triangle tri1;
        tri1.a=spoke1; tri1.b=spoke2; tri1.c=spoke3;


        c5 = magnitudes[4].cornerNo;
        c6 = magnitudes[5].cornerNo;
        c7 = magnitudes[6].cornerNo;
        c8 = magnitudes[7].cornerNo;


        //thus I just check each against the big (or until I hit a false, prob gonna do em all atm)
        if(!isWithinTriangle(frameCoords[tri1.a], frameCoords[tri1.b], frameCoords[tri1.c], frameCoords[c5]))
            drawableCorners.push_back(c5);
        if(!isWithinTriangle(frameCoords[tri1.a], frameCoords[tri1.b], frameCoords[tri1.c], frameCoords[c6]))
            drawableCorners.push_back(c6);
        if(!isWithinTriangle(frameCoords[tri1.a], frameCoords[tri1.b], frameCoords[tri1.c], frameCoords[c7]))
            drawableCorners.push_back(c7);
        if(!isWithinTriangle(frameCoords[tri1.a], frameCoords[tri1.b], frameCoords[tri1.c], frameCoords[c8]))
            drawableCorners.push_back(c8);

        return drawableCorners;
    }
}

void TwoDMathManager::populateAdjacents() {
    adjacents l1 = {2, 4, 5};
    adjacents l2 = {1, 3, 6};
    adjacents l3 = {2, 4, 7};
    adjacents l4 = {1, 3, 8};
    adjacents l5 = {1, 8, 6};
    adjacents l6 = {2, 7, 5};
    adjacents l7 = {3, 6, 8};
    adjacents l8 = {4, 7, 5};

    adjacentsMap[1] = l1;
    adjacentsMap[2] = l2;
    adjacentsMap[3] = l3;
    adjacentsMap[4] = l4;
    adjacentsMap[5] = l5;
    adjacentsMap[6] = l6;
    adjacentsMap[7] = l7;
    adjacentsMap[8] = l8;
}
