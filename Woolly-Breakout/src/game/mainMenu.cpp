#include "mainMenu.h"
#include "ui/menuWindow.h"
#include "../constants/constants.h"
#include "game.h"
#include <string>

void MainMenu::start() {
    startMainMenu();
}

void MainMenu::startMainMenu() {
    MenuWindow mainMenu{};

    mainMenu.addTexture(
        "logo", 
        Constants::Window::halfSize * 0.7,
        Constants::Window::largePadding * 0.65,
        Constants::Window::largePadding * 1.25,
        Constants::Window::largePadding * 1.25
    );

    mainMenu.addButton(
        "play",
        MenuWindow::Button { 
            int(Constants::Window::halfSize * 0.66),
            int(Constants::Window::halfSize),
            int(Constants::Window::largePadding * 1.35),
            int(Constants::Window::bigPadding * 1.2),
            [&]() { startPlayMenu(); }
        }
    );
    
    mainMenu.run();
}

void MainMenu::startJoinMenu() {
    MenuWindow joinMenu{};

    constexpr int horizontalPadding{ int(Constants::Window::halfSize * 0.7) };
    constexpr int verticalPadding{ int(Constants::Window::halfSize * 1.2) };
    constexpr int width{int(Constants::Window::largePadding * 1.2 )};
    constexpr int length{int(Constants::Window::bigPadding * 1.2 )};

    static std::string ip_address = "127.0.0.1";

    joinMenu.addButton("join", MenuWindow::Button{ horizontalPadding, verticalPadding, width, length, [&]() { 
        Game lanGame{ip_address};
        lanGame.run(); 
        startMainMenu();
    }});

    addBackButton(joinMenu);

    joinMenu.addTexture(
        "text-box", 
        Constants::Window::bigPadding * 0.75,
        Constants::Window::largePadding * 1.2,
        Constants::Window::halfSize * 1.7,
        Constants::Window::bigPadding * 1.2
    );

    joinMenu.addTexture(
        "IP", 
        Constants::Window::halfSize * 0.95,
        Constants::Window::bigPadding * 1.5,
        Constants::Window::mediumPadding * 1.2,
        Constants::Window::mediumPadding * 1.2
    );

    for (int i{0}; i < ip_address.length(); ++i) {
        bool isPoint{ ip_address[i] < '0' };

        joinMenu.addTexture(
            (!isPoint) ? std::string{ip_address[i]} : std::string{"point"}, 
            Constants::Window::bigPadding * 1.55 + i * Constants::Window::mediumPadding * 1.25 + ((!isPoint) ? 0 : Constants::Window::smallPadding * 0.75),
            Constants::Window::largePadding * 1.3 + ( (!isPoint) ? 0 : Constants::Window::smallPadding),
            (!isPoint) ? Constants::Window::mediumPadding * 1.2 : Constants::Window::mediumPadding * 0.65,
            (!isPoint) ? Constants::Window::mediumPadding * 1.2 : Constants::Window::mediumPadding * 0.651
        );
    }

    joinMenu.run([&](){

    });
}

void MainMenu::startPlayMenu() {
    MenuWindow playMenu{};

    constexpr int horizontalPadding{ int(Constants::Window::halfSize * 0.7) };
    constexpr int verticalPadding{ int(Constants::Window::largePadding * 0.75) };
    constexpr int width{int(Constants::Window::largePadding * 1.2 )};
    constexpr int length{int(Constants::Window::bigPadding * 1.2 )};

    constexpr int buttonsPadding{ int(Constants::Window::bigPadding * 1.65) };

    playMenu.addButton("solo", MenuWindow::Button{ horizontalPadding, verticalPadding, width, length, [&]() { 
        Game soloGame{};
        soloGame.run(); 
        startMainMenu();
    }});

    playMenu.addButton("host", MenuWindow::Button{ horizontalPadding, verticalPadding + buttonsPadding, width, length, [&]() { 
        Game lanGame{"host"};
        lanGame.run(); 
        startMainMenu();
    }});
    
    playMenu.addButton("join", MenuWindow::Button{ horizontalPadding, verticalPadding + buttonsPadding * 2, width, length, [&]() { 
        startJoinMenu();
    }});

    addBackButton(playMenu);
    
    playMenu.run();
}

void MainMenu::addBackButton(MenuWindow& menuWindow) {
    constexpr int horizontalPadding{ int(Constants::Window::halfSize * 1.7) };
    constexpr int verticalPadding{ int(Constants::Window::smallPadding * 1.2) };
    constexpr int width{int(Constants::Window::bigPadding)};
    constexpr int length{int(Constants::Window::mediumPadding)};

    menuWindow.addButton("back", MenuWindow::Button{ horizontalPadding, verticalPadding, width, length, [&]() { 
        startMainMenu(); 
    }});
}
