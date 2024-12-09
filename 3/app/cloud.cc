#include "cloud.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 250;

void drawPixelCloud(SDL_Renderer* renderer, const Cloud& cloud) {
    for (int i = 0; i < cloud.density; ++i) {
        // Generate random offsets within the radius
        int offsetX = rand() % (cloud.radius * 2) - cloud.radius;
        int offsetY = rand() % (cloud.radius * 2) - cloud.radius;

        // Calculate the position of the pixel
        int pixelX = cloud.x + offsetX;
        int pixelY = cloud.y + offsetY;

        SDL_Rect pixelRect = {pixelX, pixelY, 10, 10};

        // Check if the pixel is within the window bounds
        if (pixelX >= 0 && pixelX < WINDOW_WIDTH && pixelY >= 0 && pixelY < WINDOW_HEIGHT) {
            // Set the pixel color (white in this case)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &pixelRect);
        }
    }
}

void updateClouds(std::vector<Cloud>& clouds) {
    for (auto& cloud : clouds) {
        // Update the position based on speed
        cloud.x -= cloud.speedX;

        // Wrap around the screen edges
        if (cloud.x + cloud.radius < 0) { // If cloud moves off-screen to the left
            cloud.x = WINDOW_WIDTH + cloud.radius; // Reposition to the right side
            cloud.y = rand() % (WINDOW_HEIGHT - cloud.radius * 2) + cloud.radius; // Random vertical position
        }
    }
}
