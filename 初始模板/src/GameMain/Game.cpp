/*
	��Ϸ������
	Game() ���캯��
	Initialize() ��ʼ������
	RunLoop()	��ѭ��
	ProcessInput() ��Ϸȫ������
	UpdateGame() ��Ϸ����
*/


#include<GameMain/Game.h>

#include <Math/math.h>
#include <SDL/SDL_image.h>
#include <algorithm>
#include <GameObject/GameObject.h>
#include <Component/Sprite/SpriteComponent.h>

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunningGame(true)
,mUpadatingGameObjects(false)
{
	
}


bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDL�޷���ʼ��:%s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("HuRan's Game", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("���ڴ���ʧ��: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("��Ⱦ������ʧ�� %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_image��ʼ��ʧ��: %s", SDL_GetError());
		return false;
	}

	//������Ϸ����
	LoadData();

	//��ȡ��ǰʱ��
	mTicksCountOnGame = SDL_GetTicks();
	
	return true;
}


void Game::RunLoop()
{
	while (mIsRunningGame)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}


void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunningGame = false;
				break;
		}
	}
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunningGame = false;
	}

	//��ȡ������Ĳ����󣬶�������Ϸ��ɫ���������½�ɫ���������
	mUpadatingGameObjects = true;
	for (auto GameObject : GameObjectsOnExist)
	{
		GameObject->ProcessInput(keyState);
	}
	mUpadatingGameObjects = false;
}


void Game::UpdateGame()
{
	//Ӳ����ÿ֡ˢ��Ƶ��
	//�ȴ������ϴθ��¹���16ms��ʱ��
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCountOnGame + 16))
		;

	//�����ϴξ�����ʱ��
	float deltaTime = (SDL_GetTicks() - mTicksCountOnGame) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	//������Ϸ�ܼ�ʱ
	mTicksCountOnGame = SDL_GetTicks();

	//�������н�ɫ

	//��ø��½�ɫ������
	mUpadatingGameObjects = true;
	for (auto GameObject : GameObjectsOnExist)
	{
		GameObject->Update(deltaTime);
	}
	//�ͷŸ��½�ɫ������
	mUpadatingGameObjects = false;

	//������׼���¼������Ϸ��ɫPendingGameObject
	//�����ɫ������
	for (auto pending : GameObjectsOnPending)
	{
		GameObjectsOnExist.emplace_back(pending);
	}
	GameObjectsOnPending.clear();//���׼������

	// ��Ҫ�����ٵĽ�ɫ��������ٶ���
	std::vector<GameObject*> deadGameObjects;
	for (auto GameObject : GameObjectsOnExist)
	{
		if (GameObject->GetState() == ActorState::EDead)
		{
			deadGameObjects.emplace_back(GameObject);
		}
	}

	// ɾ�������ٶ����еĽ�ɫ
	for (auto GameObject : deadGameObjects)
	{
		delete GameObject;
	}
}


void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 220, 220, 255);
	SDL_RenderClear(mRenderer);
	
	// ��Ⱦ��ͼ
	for (auto sprite : Sprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}


void Game::LoadData()
{

}


void Game::UnloadData()
{
	//ɾ�����н�ɫ
	while (!GameObjectsOnExist.empty())
	{
		delete GameObjectsOnExist.back();
	}

	// ������ͼ
	for (auto i : TexturesMap)
	{
		SDL_DestroyTexture(i.second);
	}
	TexturesMap.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//����ͼӳ�����ҵ�
	auto iter = TexturesMap.find(fileName);
	if (iter != TexturesMap.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		//surface����Ϊtexture
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			//����ʧ��
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		TexturesMap.emplace(fileName.c_str(), tex);
	}
	return tex;
}



void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddGameObject(GameObject* GameObject)
{
	// If we're updating GameObjects, need to add to pending
	if (mUpadatingGameObjects)
	{
		GameObjectsOnPending.emplace_back(GameObject);
	}
	else
	{
		GameObjectsOnExist.emplace_back(GameObject);
	}
}

void Game::RemoveGameObject(GameObject* GameObject)
{
	// Is it in pending GameObjects?
	auto iter = std::find(GameObjectsOnPending.begin(), GameObjectsOnPending.end(), GameObject);
	if (iter != GameObjectsOnPending.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, GameObjectsOnPending.end() - 1);
		GameObjectsOnPending.pop_back();
	}

	// Is it in GameObjects?
	iter = std::find(GameObjectsOnExist.begin(), GameObjectsOnExist.end(), GameObject);
	if (iter != GameObjectsOnExist.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, GameObjectsOnExist.end() - 1);
		GameObjectsOnExist.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = Sprites.begin();
	for ( ;
		iter != Sprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	Sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(Sprites.begin(), Sprites.end(), sprite);
	Sprites.erase(iter);
}
