
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
    std::vector<std::string> usedTiles = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
    "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
    "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119",
    "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
    "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159",
    "160", "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
    "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199",
    "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219",
    "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "water", "water_edge", "waterplant1", "waterplant2",
    };

    for (std::string i : usedTiles) {
        std::string path = "Images/Tiles/" + i + ".png";
        ResourceManager::LoadTexture(path.c_str(), true, i);
    }
        
    std::ifstream f("Maps/Map_v1.tmj");
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
        level.solidGIDs = {
    "0", "1", "3", "4", "5", "7", "18", "19", "20", "21", "22", "23",
    "25", "36", "37",
    "39", "40", "41", "43", "55", "58", "59", "60", "64", "65", "75", "76", "77", "78", "79",
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
    "92", "93", "94", "95", "96", "97", "98", "104", "105", "106", "107", "114", "115", "116", "122", "123", "124", "125", "132", "133",
    "134", "140", "141", "142", "143",
    "150", "151", "152", "153", "154", "155", "156", "157", "158", "159",
    "160", "161", "162", "163", "164", "169",
    "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
    "180", "181", "182", "187", "188", "189",
    "190", "192", "193", "194", "195", "196", "197", "198", "199", "200",
    "201", "202", "203", "204", "205", "206", "207", "208", "210", "211",
    "212", "213", "214", "215", "216", "217", "218", "219", "220", "221",
    "225", "226", "228", "229", "230", "231", "232", "233",
        };
        level.Load("Maps/Map_v1.tmj", i, 80, 80);
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
        glm::vec2 oldPos = player->Position; // 이동 전 위치 저장

        player->Update(dt);
        for (auto& layer : Maps)
            for (auto& tile : layer.Tiles)
                tile.Update(dt);
        // 충돌 체크
        for (auto& layer : Maps) {
            for (auto& tile : layer.Tiles) {
                if (!tile.isSolid) continue;

                float feetLeft = player->Position.x + player->Size.x / 4.0f;
                float feetRight = player->Position.x + player->Size.x / 4.0f * 3.0f;
                float feetTop = player->Position.y + player->Size.y / 3.0f;
                float feetBottom = player->Position.y + player->Size.y;

                // 겹치면 충돌
                if (feetLeft   < tile.Position.x + tile.Size.x &&
                    feetRight  > tile.Position.x &&
                    feetTop    < tile.Position.y + tile.Size.y &&
                    feetBottom > tile.Position.y)
                {
                    player->Position = oldPos;
                    break;
                }

            }
        }
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