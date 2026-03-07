#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "Game.h"
#include "Shader.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <fstream>


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow(
        "BlackAndWhite",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL 
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL Version: "
        << glGetString(GL_VERSION) << std::endl;

    Game game(800, 600);
    game.Init();

    SDL_Event event;
    bool running = true;
    Uint32 lastFrame = SDL_GetTicks();
    while (running)
    {
        Uint32 currentFrame = SDL_GetTicks();
        float deltaTime = (currentFrame - lastFrame) / 1000.0f; // ms → 초
        lastFrame = currentFrame;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    running = false;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        game.ProcessInput(deltaTime);  // ← 추가
        game.Update(deltaTime);        // ← 추가
        game.Render();
        SDL_GL_SwapWindow(window);  
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
