#include "GameObject.h"

GameObject::GameObject()
    : Position(0.0f), Size(1.0f), Velocity(0.0f),
    Color(1.0f), Rotation(0.0f),
    uvOffset(0.0f), uvScale(1.0f, 1.0f),
    Sprite() {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 uvOffset, glm::vec2 uvScale, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), uvOffset(uvOffset), uvScale(uvScale), Sprite(sprite) {
}

void GameObject::Update(float dt) {
    if (sheet) {
        elapsedTime += dt;
        if (elapsedTime >= frameInterval) {
            currentFrame = (currentFrame + 1) % sheet->frames.size();
            elapsedTime = 0.0f;
        }
    }
}
void GameObject::Draw(SpriteRenderer& renderer)
{
    if (animator) {
        // Player, 몬스터 등
        auto& s = animator->sheets[animator->currentAnim];
        const UVRect& frame = s.GetFrame(animator->currentFrame);
        renderer.DrawSprite(s.texture, Position, Size, Rotation, Color, frame.offset, frame.scale);
    }
    else if (sheet) {
        // Water 타일 등 단순 루프 애니메이션
        const UVRect& frame = sheet->GetFrame(currentFrame);
        renderer.DrawSprite(sheet->texture, Position, Size, Rotation, Color, frame.offset, frame.scale);
    }
    else {
        // 일반 정적 타일
        renderer.DrawSprite(Sprite, Position, Size, Rotation, Color, uvOffset, uvScale);
    }
	
}