#include "mainMenu.h"
#include "ui/menuWindow.h"
#include "ui/elements.h"
#include "../constants/constants.h"
#include "game.h"
#include "SDL.h"
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
            Constants::Window::bigPadding * 1 + i * Constants::Window::mediumPadding * 0.75 + ((!isPoint) ? 0 : Constants::Window::smallPadding * 0.4),
            Constants::Window::largePadding * 1.35 + ( (!isPoint) ? 0 : Constants::Window::smallPadding * 0.5),
            (!isPoint) ? Constants::Window::mediumPadding * 0.75 : Constants::Window::mediumPadding * 0.5,
            (!isPoint) ? Constants::Window::mediumPadding * 0.75 : Constants::Window::mediumPadding * 0.5
        );
    } 

    joinMenu.run([&](SDL::Event& event) {
        const bool isInputFull{ ip_address.length() >= 15 };
        const bool isInputEmpty{ ip_address.length() <= 0 };

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_0:
                    if (!isInputFull) {
                        ip_address += '0';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_1:
                    if (!isInputFull) {
                        ip_address += '1';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_2:
                    if (!isInputFull) {
                        ip_address += '2';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_3:
                    if (!isInputFull) {
                        ip_address += '3';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_4:
                    if (!isInputFull) {
                        ip_address += '4';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_5:
                    if (!isInputFull) {
                        ip_address += '5';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_6:
                    if (!isInputFull) {
                        ip_address += '6';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_7:
                    if (!isInputFull) {
                        ip_address += '7';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_8:
                    if (!isInputFull) {
                        ip_address += '8';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_9:
                    if (!isInputFull) {
                        ip_address += '9';
                        startJoinMenu(); 
                    }
                    break;
                    case SDLK_PERIOD:
                    if (!isInputFull) {
                        ip_address += '.';
                        startJoinMenu(); 
                    }
                    break;
                case SDLK_BACKSPACE:
                    if (!isInputEmpty) {
                        ip_address = ip_address.substr(0, ip_address.length() - 1);
                        startJoinMenu(); 
                    }
                    break;
                default:
                    break;
            }
        }
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
