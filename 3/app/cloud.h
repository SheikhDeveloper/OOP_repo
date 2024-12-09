#ifndef LAB3_APP_CLOUD_H
#define LAB3_APP_CLOUD_H

#include <SDL2/SDL.h>
#include <vector>


struct Cloud {
    int x;          // Position of the cloud
    int y;          // Vertical position of the cloud
    int radius;     // Radius of the cloud
    int density;    // Number of pixels in the cloud
    int speedX;     // Speed of movement in X direction

    Cloud(int startX, int startY, int r, int d, int sX)
        : x(startX), y(startY), radius(r), density(d), speedX(sX) {}
};

void drawPixelCloud(SDL_Renderer* renderer, const Cloud& cloud);
void updateClouds(std::vector<Cloud>& clouds);

#endif //LAB3_APP_CLOUD_H
