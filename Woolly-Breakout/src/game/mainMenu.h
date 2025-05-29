#pragma once
#include "ui/menuWindow.h"

class MainMenu {
    public:

        void start();

    private:

        void startMainMenu();
        void startPlayMenu();
        void startJoinMenu();
        void addBackButton(MenuWindow& menuWindow);
};

