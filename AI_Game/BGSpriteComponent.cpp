#include"BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;

		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;//ÿ��ͼ������һ�Ż����ϼ�һ��ScreenSize
	}
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		//Update the x offset
		bg.mOffset.x += mScrollSpeed * deltaTime;//�����˶�Speed�Ǹ���
		//if BG is completly off screen,reset offset to the right of the last bg texture
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;//��Ϊ�����Ƿ�ͼ
		}
	}
}
void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	Vector2 pos = mOwner->GetPosition();
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}

}