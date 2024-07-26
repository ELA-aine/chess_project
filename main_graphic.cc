#include <iostream>
#include <string>
#include <X11/Xlib.h>
#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

int stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument&) {
        return 0;
    }
}

// Function to initialize X11 and create a window
void initX11(Display*& display, Window& window, GC& gc, int width, int height) {
    display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open X display" << std::endl;
        exit(1);
    }
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    gc = XCreateGC(display, window, 0, nullptr);
}

// Function to draw the chessboard
void drawChessBoard(Display* display, Window window, GC gc, const Game& game) {
    // Implement drawing logic here
}

int main() {
    Game game;
    std::string command;

    Display* display;
    Window window;
    GC gc;
    initX11(display, window, gc, 400, 400); // Set window size as needed

    while (std::cin >> command) {
        if (command == "game") {
            std::string whitePlayerType, blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType;

            std::unique_ptr<Player> whitePlayer = nullptr;
            std::unique_ptr<Player> blackPlayer = nullptr;

            if (whitePlayerType == "human") {
                whitePlayer = std::make_unique<HumanPlayer>(true);
            } else if (whitePlayerType.rfind("computer", 0) == 0) {
                int level = stringToInt(whitePlayerType.substr(8));
                whitePlayer = std::make_unique<ComputerPlayer>(true, level);
            }

            if (blackPlayerType == "human") {
                blackPlayer = std::make_unique<HumanPlayer>(false);
            } else if (blackPlayerType.rfind("computer", 0) == 0) {
                int level = stringToInt(blackPlayerType.substr(8));
                blackPlayer = std::make_unique<ComputerPlayer>(false, level);
            }

            game.start(std::move(whitePlayer), std::move(blackPlayer));

        } else if (command == "move") {
            std::string from, to, promotion;
            std::cin >> from >> to;
            if (std::cin.peek() != '\n') {
                std::cin >> promotion;
            }
            game.makeMove(from, to, promotion);
            // Refresh the display after each move
            drawChessBoard(display, window, gc, game);
        } else if (command == "resign") {
            game.resign();
        } else if (command == "setup") {
            game.setup();
        } else if (command == "undo") {
            game.undoMove();
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }

        // Handle X11 events
        XEvent event;
        XNextEvent(display, &event);
        if (event.type == Expose) {
            drawChessBoard(display, window, gc, game);
        }
    }

    XCloseDisplay(display);
    game.printFinalScore();
    return 0;
}
