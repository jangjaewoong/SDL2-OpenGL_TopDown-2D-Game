#include "Animator.h"

void Animator::AddSheet(const std::string& name, SpriteSheet sheet) {
    this->sheets.emplace(name, sheet);
}

void Animator::Play(const std::string& name) {
    if (currentAnim != name) {
        currentAnim = name;
        currentFrame = 0;
        elapsedTime = 0.0f;
    }
}

void Animator::Update(float dt) {
    elapsedTime += dt;
    auto& sheet = sheets[currentAnim];
    if (elapsedTime >= frameInterval) {
        currentFrame = (currentFrame + 1) % sheet.frames.size();
        elapsedTime = 0.0f;
    }
}