#include <iostream>
#include <SDL.h>
#include "Cube.h"
#include "LineManager.h"
#include "TwoDMathManager.h"
#include "InputHandler.h"


#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700


int main(int argv, char** args) {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        SDL_Log("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);


    SDL_Window *window = SDL_CreateWindow("Playing w/ random shit",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //inst classes.
    Cube cube;
    TwoDMathManager twoDMathManager(&cube);
    LineManager lineManager;
    InputHandler inputHandler;
    twoDMathManager.populateAdjacents();

    SDL_Delay(100);

    // for movement and frame calculation
    Uint32 frameStart;
    int frameTime;
    float deltaTime;
    Uint32 lastTime = SDL_GetTicks();

    while(true){
        frameStart = SDL_GetTicks();


        Uint32 currentTime = SDL_GetTicks(); //in milliseconds
        deltaTime = (currentTime - lastTime);
        lastTime = currentTime;

        SDL_Event e;
        while (SDL_PollEvent(&e)){

            //instead, going - inputhandler handle input
            Command *command = inputHandler.handleInput(e);

            if (command) {
                command->execute(cube);
            }

        }
        cube.moveCube(deltaTime);



        //current movement functions.
        cube.clockAroundY(deltaTime, 6);
        cube.clockAroundX(deltaTime, 3);
//        cube.clockAroundZ(deltaTime);


        //render calculations begin.
        twoDMathManager.calcMagnitudes();
        twoDMathManager.projectCubeToFrame(); //testing scaling using this method 2

        twoDMathManager.sortMagnitudes();

//        std::vector<int> drawableCorners = twoDMathManager.findDrawableCorners();
        std::vector<int> drawableCorners = twoDMathManager.findDrawableCorners();

        SDL_RenderClear(rend);
        lineManager.renderLines(rend, drawableCorners, &twoDMathManager);

        //FLUSH VECTORS THAT REPOPULATE each frame.
        twoDMathManager.magnitudes.clear();
        lineManager.lines.clear();

        //max fps = X (denominator)
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000/60) {
            SDL_Delay(1000/60 - frameTime);
        }

    }

}
