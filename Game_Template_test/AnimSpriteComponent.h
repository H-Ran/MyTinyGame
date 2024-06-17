#pragma once
#include"SpriteComponent.h"
class AnimSpriteComponent:public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* owner,int drawOrder=100);
	void Update(float deltatime)override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS(float fps) { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	//All textures in the animation
	std::vector<SDL_Texture*>mAnimTextures;
	//当前帧显示时长
	float mCurrFrame;
	//不同Anim以不同帧速率运动
	//加速时可以增加动画帧速率
	float mAnimFPS;

};