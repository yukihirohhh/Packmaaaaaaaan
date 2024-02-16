#pragma once
#include "Engine/GameObject.h"

class Stage;

class PlayerRect
{
public:
	PlayerRect();
	void SetCenterRect(float _cx, float _cy, float _width, float _height);
	void SetUnderRect(float _left, float _top, float _width, float _height);
	~PlayerRect() {};
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetUnder();
	float GetCenterX();
	float GetCenterY();
	float GetWidth();
	float GetHeight();
	float top;
	float under;
	float left;
	float right;
	float centerX;
	float centerY;
	float width;
	float height;
};
class Player :
	public GameObject
{
	int hPlayer_;
	float speed_;
	Stage* pStage_;
	int hpMax_; // �ő�HP
	int hpCrr_; // HP
	PlayerRect rect;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

