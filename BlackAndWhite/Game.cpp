
#include "Game.h"
#include <nlohmann/json.hpp>
#include <fstream>

// Game-related State data
SpriteRenderer* Renderer;
Player* player;
Camera* camera;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete player;
    delete camera;
    ResourceManager::Clear();
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
    camera = new Camera(glm::vec2(this->Width, this->Height));
    Renderer = new SpriteRenderer(spriteShader, camera);
    // load textures
    // 사용되는 158개만 로드
    std::vector<std::string> usedTiles = {
    "0", "1", "3", "4", "5", "6", "7", "9", "10", "12", "13", "14", "15", "16", "17", "18", "21", "22", "23", "24",
    "25", "27", "28", "30", "31", "32", "33", "34", "35", "39", "40", "41", "42", "43", "44", "46", "47", "48", "49", "50",
    "51", "52", "53", "54", "56", "57", "58", "59", "60", "61", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75",
    "76", "78", "80", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "99", "100", "101",
    "102", "103", "108", "109", "110", "114", "115", "116", "117", "118", "119", "120", "121", "126", "128", "132", "133", "134", "135", "136",
    "137", "138", "139", "144", "145", "146", "150", "151", "152", "153", "154", "155", "156", "157", "162", "163", "164", "165", "166", "167",
    "168", "169", "170", "171", "172", "173", "174", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "198",
    "199", "201", "202", "203", "204", "207", "209", "211", "212", "216", "217", "222", "223", "224", "225", "227", "229", "230",
    "water", "water_edge", "waterplant1", "waterplant2"
    };

    for (std::string i : usedTiles) {
        std::string path = "Images/Tiles/" + i + ".png";
        ResourceManager::LoadTexture(path.c_str(), true, i);
    }
        
    std::ifstream f("Maps/Village_Map.tmj");
    if (!f) {
        std::cerr << "TMJ 파일 못 찾음!" << std::endl;
    }
    nlohmann::json j;
    try {
        j = nlohmann::json::parse(f);
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Game.cpp 파싱 오류: " << e.what() << std::endl;
        return;
    }

    std::cerr << "파싱 성공, 레이어 수 세는 중..." << std::endl;

    int layerCount = 0;
    for (auto& layer : j["layers"])
        if (layer["type"] == "tilelayer") layerCount++;

    std::cerr << "레이어 수: " << layerCount << std::endl;

    Maps.clear();
    for (int i = 0; i < layerCount; i++) {
        GameLevel level;
        level.Load("Maps/Village_Map.tmj", i, 80, 80);
        Maps.push_back(level);
    }



    // configure game objects
    glm::vec2 playerPos = { 128 * 80 / 2.0f, 128 * 80 / 2.0f }; // 맵 중앙
    player = new Player(playerPos, PLAYER_SIZE);
    camera->Follow(player->Position + player->Size / 2.0f);
    
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        for (auto& layer : Maps)
            for (auto& tile : layer.Tiles)
                tile.Update(dt);
        player->Update(dt);
        camera->Follow(player->Position + player->Size / 2.0f);
    }
}



void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
       for (auto& layer : Maps)  // 전부 순서대로
           layer.Draw(*Renderer, camera, glm::vec2(this->Width, this->Height));
       player->Draw(*Renderer);
        
    }
}