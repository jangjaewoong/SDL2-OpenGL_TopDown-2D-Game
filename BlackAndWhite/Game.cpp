
#include "Game.h"



// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("vertex.glsl", "fragment.glsl", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0); // 0번 슬롯 텍스쳐 사용하라고 지정
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load textures
    ResourceManager::LoadTexture("background.jpg", false, "background");
    ResourceManager::LoadTexture("block.png", false, "block");
    ResourceManager::LoadTexture("block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("paddle.png", true, "paddle");
    GameLevel one; one.Load("one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;

        // SDL2: 현재 프레임의 키 상태 스냅샷을 가져옴
        const Uint8* Keys = SDL_GetKeyboardState(NULL);

        if (Keys[SDL_SCANCODE_A])
        {
            if (Player->Position.x >= 0.0f)
                Player->Position.x -= velocity;
        }
        if (Keys[SDL_SCANCODE_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        Texture2D bgTexture = ResourceManager::GetTexture("background");
        // draw background
        Renderer->DrawSprite(bgTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);
    }
}