//
// Created by M on 10/13/2024.
//

#ifndef TEST3DCUBE_INPUTHANDLER_H
#define TEST3DCUBE_INPUTHANDLER_H
#include "Cube.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Cube &actor) = 0;
};

class ReleaseRightCommand : public Command {
public:
    void execute (Cube &cube) override {
        cube.releaseRight();
    }
};
class ReleaseLeftCommand : public Command {
public:
    void execute (Cube &cube) override {
        cube.releaseLeft();
    }
};
class ReleaseUpCommand : public Command {
public:
    void execute (Cube &cube) override {
        cube.releaseUp();
    }
};
class ReleaseDownCommand : public Command {
public:
    void execute (Cube &cube) override {
        cube.releaseDown();
    }
};


class MoveRightCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goRight();
    }
};


class MoveLeftCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goLeft();
    }
};

class MoveUpCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goUp();
    }
};

class MoveDownCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goDown();
    }
};

class MoveAwayCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goAway();
    }
};
class ReleaseAwayCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.releaseAway();
    }
};
class MoveCloseCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.goClose();
    }
};
class ReleaseCloseCommand : public Command {
public:
    void execute(Cube &cube) override {
        cube.releaseClose();
    }
};

class QuitCommand : public Command {
public:
    void execute(Cube &cube) override {
        SDL_Quit();
        exit(10);
    }
};

class PauseOneSecondCommand : public Command {
public:
    void execute(Cube &cube) override {
        SDL_Delay(1000);
    }
};



class InputHandler {
public:

    //constructor
    InputHandler(){
        releaseArrowUp = new ReleaseUpCommand();
        arrowUp = new MoveUpCommand();

        releaseArrowLeft = new ReleaseLeftCommand();
        arrowLeft = new MoveLeftCommand();

        releaseArrowDown = new ReleaseDownCommand();
        arrowDown = new MoveDownCommand();

        releaseArrowRight = new ReleaseRightCommand();
        arrowRight = new MoveRightCommand();

        releaseSpacebar = new ReleaseAwayCommand();
        spacebar = new MoveAwayCommand();

        releaseB = new ReleaseCloseCommand();
        bButton = new MoveCloseCommand();

        pButton = new PauseOneSecondCommand();



        buttonESC = new QuitCommand();





    }

    Command * handleKeyDownInput(SDL_Event e);
    Command * handleKeyUpInput(SDL_Event e);
    Command * handleInput(SDL_Event e);


private:
    Command *arrowUp;
    Command *arrowLeft;
    Command *arrowDown;
    Command *arrowRight;
    Command *spacebar;
    Command *bButton;

    Command *pButton;

    Command *buttonESC;

    Command *releaseArrowUp;
    Command *releaseArrowLeft;
    Command *releaseArrowDown;
    Command *releaseArrowRight;
    Command *releaseSpacebar;
    Command *releaseB;
};

#endif //TEST3DCUBE_INPUTHANDLER_H
