#pragma once
#include "Engine/GameObject.h"
class Gauge :
    public GameObject
{
	int hGaugeBar_;
	int hGaugeFrame_;

	int gaugeMaxVal_;//ゲージの最大値
	int gaugeCrrVal_;//カレントの値（現在の値)current value

	Transform transformBar;
	Transform transformFrame;

public:
	Gauge(GameObject* parent);
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		gaugeMaxVal_ = _max;
		gaugeCrrVal_ = _crr;
	}
};

