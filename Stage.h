#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

enum STAGE_OBJ {
	LOAD,
	WALL,
};
class Stage :
	public GameObject
{
	int hFloor_;
	int hBlock_;
	vector<vector<int>>stageData_;
	int stageWidth_;
	int stageHeight_;

public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
	bool IsWall(int _x, int _y);
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

