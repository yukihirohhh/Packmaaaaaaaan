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
	int hpMax_; // 最大HP
	int hpCrr_; // HP
	PlayerRect rect;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

