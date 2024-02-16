#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Stage.h"
#include "Gauge.h"
#include "Engine/SceneManager.h"


namespace {
	const float PLAYER_MOVE_SPEED{ 0.07f };
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),
	hPlayer_(-1), speed_(PLAYER_MOVE_SPEED), pStage_(nullptr),
	hpCrr_(100), hpMax_(100)
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Player.fbx");
	assert(hPlayer_ >= 0);

	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;

	pStage_ = (Stage*)FindObject("Stage");
	rect.SetCenterRect(transform_.position_.x, transform_.position_.z, 1.0, 1.0);
}

void Player::Update()
{

	enum Dir
	{
		UP,LEFT,DOWN,RIGHT,NONE,
	};

	int moveDir = Dir::NONE;
	XMVECTOR move{ 0,0,0,0 }; //移動
	XMVECTOR vFront = { 0,0,1,0 };

	if (Input::IsKey(DIK_UP))
	{
		//		moveDir = Dir::UP;
		move = XMVECTOR{ 0,0,1,0 };
		moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		//		moveDir = Dir::LEFT;
		move = XMVECTOR{ -1,0,0,0 };
		moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		//		moveDir = Dir::DOWN;
		move = XMVECTOR{ 0,0,-1,0 };
		moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		//		moveDir = Dir::RIGHT;
		move = XMVECTOR{ 1,0,0,0 };
		moveDir = Dir::RIGHT;
	}


	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero(); //ゼロベクトルで初期化
	posTmp = pos + speed_ * move;

	int tx, ty;
	PlayerRect transRect;
	transRect.SetCenterRect(XMVectorGetX(posTmp), XMVectorGetZ(posTmp), 1.0, 1.0);

	switch (moveDir)
	{
	case UP:
		tx = (transRect.centerX + 1);
		ty = pStage_->GetStageHeight() - (int(transRect.top) - 1);
		break;
	case DOWN:
		tx = (int)(transRect.centerX + 1);
		ty = pStage_->GetStageHeight() - (int)(transRect.under) - 1;
		break;
	case LEFT:
		tx = (int)(transRect.left + 1);
		ty = pStage_->GetStageHeight() - (int)(transRect.centerY) - 1;
		break;
	case RIGHT:
		tx = (int)(transRect.right + 1);
		ty = pStage_->GetStageHeight() - (int)(transRect.centerY) - 1;
		break;
	case NONE:
		tx = (int)(transRect.centerX + 1);
		ty = pStage_->GetStageHeight() - (int)(transRect.centerY) - 1;
		break;
	defaulet:
		break;
	}



	tx = (int)(XMVectorGetX(posTmp) + 1.0f);
	ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(posTmp) + 1.0f);
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}
	else
	{
		hpCrr_ = hpCrr_ - 2;
		if (hpCrr_ < 0) hpCrr_ = 0;
	}
	////posTmp.x, posTmp.z -> int tx,ty :配列のインデックスに
	////仮にmapの配列をmap[][]とする
	//if (map[ty][tx] == STAGE_OBJ::FLOOR) {
	//	pos = pos + speed_ * move;// 移動にスピードかける
	//}


	//Debug::Log("(X, Z)=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetX(pos), true);

	Debug::Log("(iX,iZ)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);
	Debug::Log(pStage_->IsWall(tx, ty), true);

	// 移動したら、プレイヤーの向き更新
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}

	if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		float retAngle = 0.0;
		retAngle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
		transform_.rotate_.y = XMConvertToDegrees(retAngle);
	}

	//ゲージのインスタンスをFindObjectで見つけて、
	//ゲージ型にキャストして
	//メンバ変数を呼び出して、パックさんの今のHPを、ゲージに反映させる

	Gauge* gauge = (Gauge*)FindObject("Gauge");
	gauge->SetGaugeVal(hpCrr_, hpMax_);

	if (hpCrr_ <= 0)
	{
		SceneManager* pSceneManager
			= (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
	//	float rotAngle[5]{ 0,-90,180,90,180 };
	//	transform_.rotate_.y = rotAngle[moveDir];
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}

PlayerRect::PlayerRect()
	: top(-1),
	  under(-1),
	left(-1),
	right(-1),
	centerX(-1),
	centerY(-1),
	width(-1),
	height(-1)
{
}

void PlayerRect::SetCenterRect(float _cx, float _cy, float _width, float _height)
{
	centerX = _cx;
	centerY = _cy;
	width = _width;
	height = _height;
	top = centerX + height / 2.0;
	under = centerY - height / 2.0;
	left = centerX - width / 2.0;
	right = centerX + width / 2.0;
}

void PlayerRect::SetUnderRect(float _left, float _top, float _width, float _height)
{
	left = _left;
	top = _top;
	width = _width;
	height = _height;
	centerY = top - height / 2.0;
	under = top - height;
	centerX = left + width / 2.0;
	right = left + width;
}

float PlayerRect::GetLeft()
{
	return left;
}

float PlayerRect::GetRight()
{
	return right;
}

float PlayerRect::GetTop()
{
	return top;
}

float PlayerRect::GetUnder()
{
	return under;
}

float PlayerRect::GetCenterX()
{
	return centerX;
}

float PlayerRect::GetCenterY()
{
	return centerY;
}

float PlayerRect::GetWidth()
{
	return width;
}

float PlayerRect::GetHeight()
{
	return height;
}
