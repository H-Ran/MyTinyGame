#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>


class Game
{
public:

	Game();

	/// <summary>
	/// 初始化游戏进程
	/// </summary>
	/// <returns>是否初始化成功</returns>
	bool Initialize();

	/// <summary>
	/// 游戏循环主程序
	/// </summary>
	void RunLoop();

	/// <summary>
	/// 结束游戏进程
	/// </summary>
	void Shutdown();

	void AddGameObject(class GameObject* GameObject);
	void RemoveGameObject(class GameObject* GameObject);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	
	SDL_Texture* GetTexture(const std::string& fileName);

private:
    /// <summary>
    /// 处理输入事件
    /// </summary>
	void ProcessInput();

    /// <summary>
    /// 更新所有角色及其组件
    /// </summary>
	void UpdateGame();

    /// <summary>
    /// 生成并渲染输出
    /// </summary>
	void GenerateOutput();

    /// <summary>
    /// 加载游戏数据
    /// </summary>
	void LoadData();

    /// <summary>
    /// 卸载游戏数据
    /// </summary>
    void UnloadData();
	
	/// <summary>
	/// 贴图映射储存
	/// </summary>
	std::unordered_map<std::string, SDL_Texture*> TexturesMap;

	/// <summary>
	/// 所有仍存在的游戏对象
	/// </summary>
	std::vector<class GameObject*> GameObjectsOnExist;
	
	/// <summary>
	/// 所有等待销毁的游戏对象
	/// </summary>
	std::vector<class GameObject*> GameObjectsOnPending;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> Sprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCountOnGame;
	bool mIsRunningGame;
	// Track if we're updating GameObjects right now
	bool mUpadatingGameObjects;
};
