//
// Created by M on 10/13/2024.
//
#include "InputHandler.h"

Command * InputHandler::handleKeyDownInput(SDL_Event e) {
    switch (e.key.keysym.sym) {
        case SDLK_a:
        case SDLK_LEFT:
            return arrowLeft;
        case SDLK_d:
        case SDLK_RIGHT:
            return arrowRight;
        case SDLK_w:
        case SDLK_UP:
            return arrowUp;
        case SDLK_s:
        case SDLK_DOWN:
            return arrowDown;
        case SDLK_ESCAPE:
            return buttonESC;
        case SDLK_SPACE:
            return spacebar;
        case SDLK_b:
            return bButton;
        default:
            return nullptr;
    }
}

Command *InputHandler::handleKeyUpInput(SDL_Event e) {
    switch (e.key.keysym.sym) {
        case SDLK_a:
        case SDLK_LEFT:
            return releaseArrowLeft;
        case SDLK_d:
        case SDLK_RIGHT:
            return releaseArrowRight;
        case SDLK_w:
        case SDLK_UP:
            return releaseArrowUp;
        case SDLK_s:
        case SDLK_DOWN:
            return releaseArrowDown;
        case SDLK_SPACE:
            return releaseSpacebar;
        case SDLK_b:
            return releaseB;
        case SDLK_p:
            return pButton;
        default:
            return nullptr;
    }
}

Command *InputHandler::handleInput(SDL_Event e){
    switch (e.type) {
        case SDL_QUIT:
            SDL_Log("Clicked X\n");
            SDL_Quit();
            exit(10);
        case SDL_KEYDOWN:
            return handleKeyDownInput(e);
        case SDL_KEYUP:
            return handleKeyUpInput(e);
        default:
            return nullptr;
    }
}