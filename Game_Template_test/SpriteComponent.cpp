#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect rect;
		float scale = mOwner->GetScale();
		Vector2 position = mOwner->GetPosition();
		rect.w = static_cast<int>(mTexWidth * scale);
		rect.h = static_cast<int>(mTexHeight * scale);
		rect.x = static_cast<int>(position.x - rect.w / 2);
		rect.y = static_cast<int>(position.y - rect.h / 2);
		
		//To Draw
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&rect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
