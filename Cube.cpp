//
// Created by M on 10/8/2024.
//
#include "Cube.h"

#define SLIDE_SCALE .1


void Cube::clockAroundY(float ms, int spr) {
    /* Clockwise around positive Y axis
     * f:r^3 --> r^3
     *   _                   _    _ _
     *  |  cos(t)   0  sin(t) |  | x |
     *  |   0       1   0     |  | y |
     *  |_ -sin(t)  0  cos(t)_|  |_z_|
     */
    float newX, newZ, dx, dz;
    float radians = (ms / (spr * 1000)) * (2 * M_PI);


    for (int x=0;x<8;x++){

        newX = (std::cos(radians) * cornersFromCubeCenter[x].x) + (std::sin(radians) * cornersFromCubeCenter[x].z);
        newZ = (-1)*(std::sin(radians) * cornersFromCubeCenter[x].x) + (std::cos(radians) * cornersFromCubeCenter[x].z);

        dx = newX - cornersFromCubeCenter[x].x;
        dz = newZ - cornersFromCubeCenter[x].z;

        cornersFromCubeCenter[x].x = newX;
        corners[x].x += dx;

        cornersFromCubeCenter[x].z  = newZ;
        corners[x].z += dz;
    }

}

void Cube::clockAroundX(float ms, int spr) {
    /* Clockwise around positive Y axis
     * f:r^3 --> r^3
     *   _                   _    _ _
     *  |   1       0       0 |  | x |
     *  |   0   cos(t) -sin(t)|  | y |
     *  |_  0   sin(t) cos(t)_|  |_z_|
     */

    float newY, newZ, dy, dz;
    float radians = (ms / (spr * 1000)) * (2 * M_PI);
    for (int x=0;x<8;x++) {
        newY = (std::cos(radians) * cornersFromCubeCenter[x].y) - (std::sin(radians) * cornersFromCubeCenter[x].z);
        newZ = (std::sin(radians) * cornersFromCubeCenter[x].y) +
               (std::cos(radians) * cornersFromCubeCenter[x].z);

        dy = newY - cornersFromCubeCenter[x].y;
        dz = newZ - cornersFromCubeCenter[x].z;

        cornersFromCubeCenter[x].y = newY;
        corners[x].y += dy;

        cornersFromCubeCenter[x].z = newZ;
        corners[x].z += dz;
    }
}

void Cube::clockAroundZ(float ms, int spr) {
    /* Clockwise around positive Y axis
     * f:r^3 --> r^3
     *   _                   _    _ _
     *  |  cos(t) -sin(t)  0  |  | x |
     *  |  sin(t)  cos(t)  0  |  | y |
     *  |_ 0        0      1 _|  |_z_|
     */
    float newY, newX, dy, dx;
    float radians = (ms / (spr * 1000)) * (2 * M_PI);
    for (int x=0;x<8;x++) {

        newX = (std::cos(radians) * cornersFromCubeCenter[x].x) -
               (std::sin(radians) * cornersFromCubeCenter[x].y);

        newY = (std::sin(radians) * cornersFromCubeCenter[x].x) +
                (std::cos(radians) * cornersFromCubeCenter[x].y);


        dy = newY - cornersFromCubeCenter[x].y;
        dx = newX - cornersFromCubeCenter[x].x;

        cornersFromCubeCenter[x].y = newY;
        corners[x].y += dy;

        cornersFromCubeCenter[x].x = newX;
        corners[x].x += dx;
    }
}


void Cube::goUp() {
    auto it = yMovement.begin();
    if (it == yMovement.end()) yMovement.push_back('U');
    else if (*it != 'U') { //if first entry isn't End or L.
        ++it;
        if (it == yMovement.end()){
            yMovement.push_back('U'); // if second entry is end, add L to vector at front.
        }else if (*it == 'U'){
            yMovement.erase(it);
            yMovement.push_back('U');
        } else yMovement.clear();
    }
}
void Cube::goDown() {
    auto it = yMovement.begin();
    if (it == yMovement.end()) yMovement.push_back('D');
    else if (*it != 'D') { //if first entry isn't End or L.
        ++it;
        if (it == yMovement.end()){
            yMovement.push_back('D'); // if second entry is end, add L to vector at front.
        }else if (*it == 'D'){
            yMovement.erase(it);
            yMovement.push_back('D');
        } else yMovement.clear();
    }
}


void Cube::goLeft() {
    auto it = xMovement.begin();
    if (it == xMovement.end()) xMovement.push_back('L');
    else if (*it != 'L') { //if first entry isn't End or L.
        ++it;
        if (it == xMovement.end()){
            xMovement.push_back('L'); // if second entry is end, add L to vector at front.
        }else if (*it == 'L'){
            xMovement.erase(it);
            xMovement.push_back('L');
        } else xMovement.clear();
    }

}

void Cube::goRight() {
    auto it = xMovement.begin();
    if (it == xMovement.end()) xMovement.push_back('R');
    else if (*it != 'R') { //if first entry isn't End or L.
        ++it;
        if (it == xMovement.end()){
            xMovement.push_back('R'); // if second entry is end, add L to vector at front.
        }else if (*it == 'R'){
            xMovement.erase(it);
            xMovement.push_back('R');
        } else xMovement.clear();
    }
}

void Cube::releaseLeft() {
    auto it = xMovement.begin();
    if (*it == 'L'){
        xMovement.erase(it);
    } else {
        ++it;
        if (*it == 'L'){
            xMovement.erase(it);
        }
    }
}

void Cube::releaseRight() {
    auto it = xMovement.begin();
    if (*it == 'R'){
        xMovement.erase(it);
    } else {
        ++it;
        if (*it == 'R'){
            xMovement.erase(it);
        }
    }
}

void Cube::releaseUp() {
    auto it = yMovement.begin();
    if (*it == 'U'){
        yMovement.erase(it);
    } else {
        ++it;
        if (*it == 'U'){
            yMovement.erase(it);
        }
    }
}

void Cube::releaseDown() {
    auto it = yMovement.begin();
    if (*it == 'D'){
        yMovement.erase(it);
    } else {
        ++it;
        if (*it == 'D'){
            yMovement.erase(it);
        }
    }
}

void Cube::goAway(){
    auto it = zMovement.begin();
    if (it == zMovement.end()) zMovement.push_back('A');
    else if (*it != 'A') { //if first entry isn't End or L.
        ++it;
        if (it == zMovement.end()){
            zMovement.push_back('A'); // if second entry is end, add L to vector at front.
        }else if (*it == 'A'){
            zMovement.erase(it);
            zMovement.push_back('A');
        } else zMovement.clear();
    }
}
void Cube::releaseAway(){
    auto it = zMovement.begin();
    if (*it == 'A'){
        zMovement.erase(it);
    } else {
        ++it;
        if (*it == 'A'){
            zMovement.erase(it);
        }
    }
}

void Cube::goClose(){
    auto it = zMovement.begin();
    if (it == zMovement.end()) zMovement.push_back('C');
    else if (*it != 'C') { //if first entry isn't End or L.
        ++it;
        if (it == zMovement.end()){
            zMovement.push_back('C'); // if second entry is end, add L to vector at front.
        }else if (*it == 'C'){
            zMovement.erase(it);
            zMovement.push_back('C');
        } else zMovement.clear();
    }
}
void Cube::releaseClose(){
    auto it = zMovement.begin();
    if (*it == 'C'){
        zMovement.erase(it);
    } else {
        ++it;
        if (*it == 'C'){
            zMovement.erase(it);
        }
    }
}


void Cube::moveCube(float ms) {
    if (!xMovement.empty()){

        if(corners[0].x < 300 && xMovement.back() == 'R') {
            for (auto &it: corners) {
                it.x += ms * SLIDE_SCALE;
            }
        } else if (corners[0].x > -300 && xMovement.back() == 'L'){
            for (auto &it: corners) {
                it.x -= ms * SLIDE_SCALE;
            }
        }

    }
    if (!yMovement.empty()){

        if(corners[0].y < 300 && yMovement.back() == 'D') {
            for (auto &it: corners) {
                it.y += ms * (SLIDE_SCALE+.2);
            }
        } else if (corners[0].x > -300 && yMovement.back() == 'U'){
            for (auto &it: corners) {
                it.y -= ms * (SLIDE_SCALE+.2);
            }
        }

    }

    if (!zMovement.empty()){

        if(corners[0].z < 800 && zMovement.back() == 'A') {
            for (auto &it: corners) {
                it.z += ms * SLIDE_SCALE;
            }
        } else if (corners[0].z > 100 && zMovement.back() == 'C'){
            for (auto &it: corners) {
                it.z -= ms * SLIDE_SCALE;
            }
        }

    }
}
