#pragma once
#include<GameObject/GameObject.h>
#include<Component/Component.h>

class SpriteComponent :public Component
{
public:
	SpriteComponent(GameObject* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder()const { return mDrawOrder; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};