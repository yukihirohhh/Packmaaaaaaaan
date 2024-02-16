#include "GameOver.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

GameOver::GameOver(GameObject* parent)
	:GameObject(parent, "GameOver"), hPict_(-1)
{
}

GameOver::~GameOver()
{
	
}

void GameOver::Initialize()
{
	hPict_ = Image::Load("GameOver.png");
	assert(hPict_ >= 0);
}

void GameOver::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager
			= (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOver::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void GameOver::Release()
{
}
