#include "GameLevel.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>




void GameLevel::Load(const char* file, int layerIndex, unsigned int TileSizeX, unsigned int TileSizeY)
{
    this->Tiles.clear();

    std::ifstream f(file);
    if (!f) {
        std::cerr << "Failed to Open Map Data: " << file << std::endl;
        return;
    }

    nlohmann::json j = nlohmann::json::parse(f);
    int mapWidth = j["width"]; // 키로 값 접근 j["키이름"] (최상위 객체)
    int mapHeight = j["height"];

    // tilelayer만 추출
    std::vector<nlohmann::json> tileLayers;
    for (auto& layer : j["layers"]) {
        if (layer["type"] == "tilelayer")
            tileLayers.push_back(layer);
    }

    if (layerIndex >= (int)tileLayers.size()) {
        std::cerr << "Layer index out of range" << std::endl;
        return;
    }

    auto& layer = tileLayers[layerIndex];
    std::vector<int> flatData = layer["data"].get<std::vector<int>>(); // data 키 내부 값을 vector로 변환하는 json함수

    std::vector<std::vector<unsigned int>> tileData(
        mapHeight, std::vector<unsigned int>(mapWidth, (unsigned int)-1)); // 벡터 unsigned int -1(실제론 int의 최댓값, 관용적으로 많이씀)로 초기화 후 실제 타일 있는 곳만 GID 값으로 덮어씀


    for (int i = 0; i < (int)flatData.size(); i++) { // json형태의 data는 1차원이기 때문에 2차원으로 변환해줌.
        if (flatData[i] == 0) continue;
        tileData[i / mapWidth][i % mapWidth] = flatData[i];
    }

    this->init(tileData, TileSizeX, TileSizeY);
}

void GameLevel::Draw(SpriteRenderer& renderer, Camera* camera, glm::vec2 screenSize)
{
    float left = camera->position.x - screenSize.x / 2;
    float right = camera->position.x + screenSize.x / 2;
    float top = camera->position.y - screenSize.y / 2;
    float bottom = camera->position.y + screenSize.y / 2;

    for (GameObject& tile : this->Tiles) {
        // 화면 밖이면 스킵
        if (tile.Position.x + tile.Size.x < left)  continue;
        if (tile.Position.x > right)                continue;
        if (tile.Position.y + tile.Size.y < top)    continue;
        if (tile.Position.y > bottom)               continue;

        tile.Draw(renderer);
    }
}



void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int TileSizeX, unsigned int TileSizeY)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            {
                unsigned int gid = tileData[y][x]; // 원본 GID
                if (gid == (unsigned int)-1) continue; // ← 이거 추가!
                if (gid >= 235) {
                    // 애니메이션 타일
                    std::string texKey;
                    if (gid <= 242) texKey = "water";
                    else if (gid <= 250) texKey = "water_edge";
                    else if (gid <= 258) texKey = "waterplant1";
                    else                 texKey = "waterplant2";

                    glm::vec2 pos(TileSizeX * x, TileSizeY * y);
                    glm::vec2 size(TileSizeX, TileSizeY);
                    Texture2D tex = ResourceManager::GetTexture(texKey);
                    GameObject obj(pos, size, tex, glm::vec2(0, 0), glm::vec2(1, 1), glm::vec3(1, 1, 1));
                    obj.sheet = new SpriteSheet(tex, 8, 1);
                    obj.frameInterval = 0.12f;
                    this->Tiles.push_back(obj);
                    continue;
                }

                // 일반 타일 (GID 1~234)
                std::string key = std::to_string(gid - 1); // 여기서 -1
                Texture2D tex = ResourceManager::GetTexture(key);
                if (tex.ID == 0) continue;

                glm::vec2 pos(TileSizeX * x, TileSizeY * y);
                glm::vec2 size(TileSizeX, TileSizeY);
                GameObject obj(pos, size, tex, glm::vec2(0, 0), glm::vec2(1, 1), glm::vec3(1, 1, 1));
                this->Tiles.push_back(obj);
            }
           
        }
    }
}