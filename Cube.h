//
// Created by M on 10/7/2024.
//

/* Atrocious ASCII cube showing how corners are labeled.
 *  (1)+------+(2)
 *     | \    |\
 *     |  \   | \
 *  (4)+---\--+  \(3)
 *      \(5)+--\---+(6)
 *       \  |   \  |
 *        \ |    \ |
 *       (8)+------+(7)
 * viewing the cube from above, 1-4 are the top corners counter clockwise.
 * 5-8 sit below 1-4 respectively.
 *
 * Thus the connections are as follows: 1:[2, 5, 4], 2:[3, 1, 6] ...
 * or more discretely:
 * line1: 1-2  line7:  3-4
 * line2: 1-5  line8:  4-8
 * line3: 1-4  line9:  5-6
 * line4: 2-3  line10: 6-7
 * line5: 2-6  line11: 7-8
 * line6: 3-7  line12: 8-5
 */

#ifndef TEST3DCUBE_CUBE_H
#define TEST3DCUBE_CUBE_H
#include <SDL.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>




typedef struct cornerCoord {
    float x;
    float y;
    float z;
} corner;

typedef struct adjacents {
    int a;
    int b;
    int c;
} adjacents;

typedef struct magnitudeCard {
    int cornerNo;
    float magnitude;
}magCard;

typedef struct triangle {
    int a;
    int b;
    int c;
} triangle;

class Cube {
public:
    corner corner1{};
    corner corner2{};
    corner corner3{};
    corner corner4{};
    corner corner5{};
    corner corner6{};
    corner corner7{};
    corner corner8{};

    //corners from frame origin
    std::vector<corner> corners;

    std::vector<char> xMovement;
    std::vector<char> yMovement;
    std::vector<char> zMovement;

    //Using additional vector of corners of vectors with respect to centerpoint of cube
    //operations on this will be local and then translated
    //Really, this is all I need - as I can translate these values based on center
    //position from frame origin. But not doing that atm.
    std::vector<corner> cornersFromCubeCenter;

    Cube(){
        //Spawn cube w/ given dimensions.
        corner1.x = -50;
        corner1.y = 50;
        corner1.z = 100;
        corners.push_back(corner1);
        corner1.z = -50;
        cornersFromCubeCenter.push_back(corner1);

        corner2.x = 50;
        corner2.y = 50;
        corner2.z = 100;
        corners.push_back(corner2);
        corner2.z = -50;
        cornersFromCubeCenter.push_back(corner2);

        corner3.x = 50;
        corner3.y = 50;
        corner3.z = 200;
        corners.push_back(corner3);
        corner3.z = 50;
        cornersFromCubeCenter.push_back(corner3);

        corner4.x = -50;
        corner4.y = 50;
        corner4.z = 200;
        corners.push_back(corner4);
        corner4.z = 50;
        cornersFromCubeCenter.push_back(corner4);

        corner5.x = -50;
        corner5.y = -50;
        corner5.z = 100;
        corners.push_back(corner5);
        corner5.z = -50;
        cornersFromCubeCenter.push_back(corner5);

        corner6.x = 50;
        corner6.y = -50;
        corner6.z = 100;
        corners.push_back(corner6);
        corner6.z = -50;
        cornersFromCubeCenter.push_back(corner6);

        corner7.x = 50;
        corner7.y = -50;
        corner7.z = 200;
        corners.push_back(corner7);
        corner7.z = 50;
        cornersFromCubeCenter.push_back(corner7);

        corner8.x = -50;
        corner8.y = -50;
        corner8.z = 200;
        corners.push_back(corner8);
        corner8.z = 50;
        cornersFromCubeCenter.push_back(corner8);

    }

    void clockAroundY(float ms, int spr);
    void clockAroundX(float ms, int spr);
    void clockAroundZ(float ms, int spr);


    //consolidate movement
    void moveCube(float ms);


    void goUp();
    void releaseUp();

    void goDown();
    void releaseDown();

    void goLeft();
    void releaseLeft();

    void goRight();
    void releaseRight();

    void goAway();
    void releaseAway();

    void goClose();
    void releaseClose();






};



#endif //TEST3DCUBE_CUBE_H
