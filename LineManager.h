//
// Created by M on 10/10/2024.
//

#ifndef TEST3DCUBE_LINEMANAGER_H
#define TEST3DCUBE_LINEMANAGER_H
#include <SDL.h>
#include <vector>
#include "Cube.h"
#include "TwoDMathManager.h"

typedef struct line2draw {
    int p1;
    int p2;
} line;



class LineManager {
public:
    std::vector<line> lines;

    void renderLines(SDL_Renderer *rend, std::vector<int> drawList, TwoDMathManager *d2);
};


#endif //TEST3DCUBE_LINEMANAGER_H
