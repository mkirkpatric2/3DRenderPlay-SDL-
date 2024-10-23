//
// Created by M on 10/10/2024.
//

#include "LineManager.h"



void LineManager::renderLines(SDL_Renderer *rend, std::vector<int> drawList, TwoDMathManager *d2) {

    //Determine which lines to draw (have 2 adjacent corners drawable)
    int len = drawList.size();
    for (int x=0;x<(len-1);x++){
        for(int y=x+1;y<len;y++){
            if (d2->adjacentsMap[drawList[x]].a==drawList[y] || d2->adjacentsMap[drawList[x]].b==drawList[y] || d2->adjacentsMap[drawList[x]].c==drawList[y]) {
                line l = {drawList[x], drawList[y]};
                lines.push_back(l);
            }
        }
    }



    //draw lines. Screen is 700x700, origin is the top left corner. Centering cube w/ +350
//    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
//    for(auto& it : lines){
//        SDL_RenderDrawLine(rend, d2->frameCoords[it.p1].x+350, d2->frameCoords[it.p1].y+350,
//                           d2->frameCoords[it.p2].x+350, d2->frameCoords[it.p2].y+350);
//    }
//    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
//    SDL_RenderPresent(rend);

    //shift centering to projection
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    for(auto& it : lines){
        SDL_RenderDrawLine(rend, d2->frameCoords[it.p1].x, d2->frameCoords[it.p1].y,
                           d2->frameCoords[it.p2].x, d2->frameCoords[it.p2].y);
    }
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderPresent(rend);



}
