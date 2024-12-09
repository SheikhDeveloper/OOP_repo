#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "cloud.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const std::string IMAGE_DIR = "images";
int img_x = WINDOW_WIDTH / 2;
int img_y = WINDOW_HEIGHT / 2;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
    if (!texture) {
        throw std::runtime_error("Could not load texture: " + filename);
    }
    return texture;
}

void drawImage(SDL_Renderer* renderer, SDL_Texture* texture) {
    int width = 250, height = 100;
    SDL_Rect rect = {img_x - width / 2, img_y - height / 2, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void drawOcean(SDL_Renderer* renderer, std::vector<SDL_Texture*>& textures) {
    // Set the color for the ocean (blue)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Draw the ocean as a rectangle covering the bottom half of the window
    SDL_Rect oceanRect = { 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
    SDL_RenderFillRect(renderer, &oceanRect);

    // Optionally, you can draw some waves
    SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); // Darker blue for waves
    for (int i = 0; i < WINDOW_WIDTH; i += 20) {
        SDL_RenderDrawLine(renderer, i, static_cast<float>(WINDOW_HEIGHT) / 2,
                           i + 20, static_cast<float>(WINDOW_HEIGHT) / 2);
        for (auto& texture : textures) {
            drawImage(renderer, texture);
        }
    }

}

bool initializeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Ocean", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void cleanUp(SDL_Window* window, SDL_Renderer* renderer, std::vector<SDL_Texture*>& textures) {
    for (SDL_Texture* &texture : textures)
        if (texture)
            SDL_DestroyTexture(texture);
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initializeSDL(window, renderer)) {
        return -1; // Exit if initialization fails
    }

    // Load the aircraft carrier texture once
    SDL_Texture* aircraftCarrierTexture = loadTexture(renderer, IMAGE_DIR + "/aircraft_carrier.png");
    SDL_Texture* aircraftCruiserTexture = loadTexture(renderer, IMAGE_DIR + "/aircraft_cruiser.png");
    SDL_Texture* coveringShipTexture = loadTexture(renderer, IMAGE_DIR + "/covering_ship.png");
    std::vector<SDL_Texture*> textures = {aircraftCarrierTexture, aircraftCruiserTexture, coveringShipTexture};
    bool running = true;
    SDL_Event event;

    srand(static_cast<unsigned>(time(0)));

    std::vector<Cloud> clouds;
    for (int i = 0; i < 10; ++i) { // Create 10 clouds
        int radius = 30;
        int density = 100;
        int speedX = rand() % 3 + 1; // Random speed between 1 and 3
        int startY = rand() % (WINDOW_HEIGHT - radius * 2) + radius; // Random vertical position
        clouds.emplace_back(WINDOW_WIDTH + radius + i * 100, startY, radius, density, speedX); // Start off-screen to the right
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky color
        SDL_RenderClear(renderer);

        // Draw the ocean
        drawOcean(renderer, textures);

        // Update the clouds
        updateClouds(clouds);

        for (auto& cloud : clouds) {
            drawPixelCloud(renderer, cloud);
        }

        // Present the back buffer
        SDL_RenderPresent(renderer);
    }

    cleanUp(window, renderer, textures);
    return 0;
}
