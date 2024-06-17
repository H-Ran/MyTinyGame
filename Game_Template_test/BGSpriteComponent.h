#pragma once
#include"SpriteComponent.h"

class BGSpriteComponent :public SpriteComponent
{
public:
	BGSpriteComponent(Actor* mOwner, int drawOrder = 10);
	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer)override;
	//Set Textures uesed for the background
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	//Get/Set screen size and scroll speed
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;//每一张背景图的偏移量
	};
	std::vector<BGTexture>mBGTextures;
	Vector2 mScreenSize;//整个视图的大小
	float mScrollSpeed;
};
