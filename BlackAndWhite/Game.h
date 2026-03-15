#ifndef CLASS_GAME_H
#define CLASS_GAME_H

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "GameLevel.h"
#include "Player.h"
#include "Camera.h"
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

const glm::vec2 PLAYER_SIZE(80.0f, 80.0f);

const float PLAYER_VELOCITY(500.0f);

class Game
{
public:
    // game state
    GameState    State;
    unsigned int Width, Height;
    std::vector<GameLevel> Maps;
    unsigned int map;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void Update(float dt);
    void Render();
};

#endif;