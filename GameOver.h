#pragma once
#include "Engine/GameObject.h"
class GameOver :
    public GameObject
{
	int hPict_;
public:
	//�R���X�g���N�^
	GameOver(GameObject* parent);

	//�f�X�g���N�^
	~GameOver();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};