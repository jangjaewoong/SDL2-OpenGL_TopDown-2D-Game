
#include "Game.h"



// Game-related State data
SpriteRenderer* Renderer;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("vertex.glsl", "fragment.glsl", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load textures
    ResourceManager::LoadTexture("PePE.jpg", true, "pepe");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Texture2D spriteTexture = ResourceManager::GetTexture("pepe");
    Renderer->DrawSprite(spriteTexture, glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 600.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}