#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
    : GameObject(), currentFrame(0)
{
    std::vector<std::pair<std::string, std::string>> textures = {
        { "Images/Characters/Char_Idle_Down.png", "Char_Idle_Down" },
        { "Images/Characters/Char_Idle_Left.png",  "Char_Idle_Left" },
        { "Images/Characters/Char_Idle_Right.png", "Char_Idle_Right" },
        { "Images/Characters/Char_Idle_Up.png",    "Char_Idle_Up" },
        { "Images/Characters/Char_Run_Down.png",   "Char_Run_Down" },
        { "Images/Characters/Char_Run_Left.png",   "Char_Run_Left" },
        { "Images/Characters/Char_Run_Right.png",  "Char_Run_Right" },
        { "Images/Characters/Char_Run_Up.png",     "Char_Run_Up" }
    };
    for (auto& [path, name] : textures) {
        ResourceManager::LoadTexture(path.c_str(), true, name);
    }
    Position = pos;
    Size = size;
    Color = color;
    animator = new Animator();
    animator->AddSheet("idle_down", SpriteSheet(ResourceManager::GetTexture("Char_Idle_Down"), 6, 1));
    animator->AddSheet("idle_up", SpriteSheet(ResourceManager::GetTexture("Char_Idle_Up"), 6, 1));
    animator->AddSheet("idle_left", SpriteSheet(ResourceManager::GetTexture("Char_Idle_Left"), 6, 1));
    animator->AddSheet("idle_right", SpriteSheet(ResourceManager::GetTexture("Char_Idle_Right"), 6, 1));
    animator->AddSheet("run_down", SpriteSheet(ResourceManager::GetTexture("Char_Run_Down"), 6, 1));
    animator->AddSheet("run_up", SpriteSheet(ResourceManager::GetTexture("Char_Run_Up"), 6, 1));
    animator->AddSheet("run_left", SpriteSheet(ResourceManager::GetTexture("Char_Run_Left"), 6, 1));
    animator->AddSheet("run_right", SpriteSheet(ResourceManager::GetTexture("Char_Run_Right"), 6, 1));
    animator->Play("idle_down"); // 기본 상태
}



void Player::Update(float dt)
{
    
    float velocity = moveSpeed * dt;
    const Uint8* Keys = SDL_GetKeyboardState(NULL);

    glm::vec2 dir(0.0f, 0.0f);
    if (Keys[SDL_SCANCODE_A]) dir.x -= 1.0f;
    if (Keys[SDL_SCANCODE_D]) dir.x += 1.0f;
    if (Keys[SDL_SCANCODE_W]) dir.y -= 1.0f;
    if (Keys[SDL_SCANCODE_S]) dir.y += 1.0f;
    if (glm::length(dir) > 0.0f) {
        if (dir.y > 0.0f) { animator->Play("run_down");  lastDir = "down"; }
        else if (dir.y < 0.0f) { animator->Play("run_up");    lastDir = "up"; }
        else if (dir.x < 0.0f) { animator->Play("run_left");  lastDir = "left"; }
        else if (dir.x > 0.0f) { animator->Play("run_right"); lastDir = "right"; }
        dir = glm::normalize(dir);
    }
    else {
        if (lastDir == "down")  animator->Play("idle_down");
        else if (lastDir == "up")    animator->Play("idle_up");
        else if (lastDir == "left")  animator->Play("idle_left");
        else if (lastDir == "right") animator->Play("idle_right");
    }
    
        

    this->Position += dir * velocity;
    animator->Update(dt);
}

