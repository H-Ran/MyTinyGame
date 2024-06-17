#include"AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	int mAnimTexturesSize = mAnimTextures.size();
	if (mAnimTexturesSize > 0)
	{
		mCurrFrame += mAnimFPS * deltaTime;
		while (mCurrFrame >= mAnimTexturesSize)
		{
			mCurrFrame -= mAnimTexturesSize;
		}
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}
void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
