#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include "SDL3/SDL.h"
#include <SDL3/SDL_main.h>

#include "../FrysEngineLibrary/FrysEngine.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

double previousFrameTime = 0.0f;

FrysEngine engine;

#pragma region SDL Init and loop

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "dk.olifrys.frysengine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Frys Engine Test", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    engine.Init();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, key presses, etc.) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event)
{
    engine.ProcessInput(event);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0f;  /* convert from milliseconds to seconds. */
    previousFrameTime = now;
    const double deltaTime = now - previousFrameTime;

    engine.Update(deltaTime);
    engine.Render(renderer);

    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const auto red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    const auto green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const auto blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    engine.Quit();
    /* SDL will clean up the window/renderer for us. */
}

#pragma endregion