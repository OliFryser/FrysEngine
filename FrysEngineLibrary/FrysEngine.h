#pragma once
#include "SDL3/SDL_render.h"

class FrysEngine {
public:
    void Init();
    void ProcessInput(SDL_Event* event);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Quit();
};
