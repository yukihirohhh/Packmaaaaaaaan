#pragma once
#include "Engine/GameObject.h"
class Gauge :
    public GameObject
{
	int hGaugeBar_;
	int hGaugeFrame_;

	int gaugeMaxVal_;//�Q�[�W�̍ő�l
	int gaugeCrrVal_;//�J�����g�̒l�i���݂̒l)current value

	Transform transformBar;
	Transform transformFrame;

public:
	Gauge(GameObject* parent);
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		gaugeMaxVal_ = _max;
		gaugeCrrVal_ = _crr;
	}
};

