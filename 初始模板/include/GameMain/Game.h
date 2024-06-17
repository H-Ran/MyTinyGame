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
	/// ��ʼ����Ϸ����
	/// </summary>
	/// <returns>�Ƿ��ʼ���ɹ�</returns>
	bool Initialize();

	/// <summary>
	/// ��Ϸѭ��������
	/// </summary>
	void RunLoop();

	/// <summary>
	/// ������Ϸ����
	/// </summary>
	void Shutdown();

	void AddGameObject(class GameObject* GameObject);
	void RemoveGameObject(class GameObject* GameObject);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	
	SDL_Texture* GetTexture(const std::string& fileName);

private:
    /// <summary>
    /// ���������¼�
    /// </summary>
	void ProcessInput();

    /// <summary>
    /// �������н�ɫ�������
    /// </summary>
	void UpdateGame();

    /// <summary>
    /// ���ɲ���Ⱦ���
    /// </summary>
	void GenerateOutput();

    /// <summary>
    /// ������Ϸ����
    /// </summary>
	void LoadData();

    /// <summary>
    /// ж����Ϸ����
    /// </summary>
    void UnloadData();
	
	/// <summary>
	/// ��ͼӳ�䴢��
	/// </summary>
	std::unordered_map<std::string, SDL_Texture*> TexturesMap;

	/// <summary>
	/// �����Դ��ڵ���Ϸ����
	/// </summary>
	std::vector<class GameObject*> GameObjectsOnExist;
	
	/// <summary>
	/// ���еȴ����ٵ���Ϸ����
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
