#pragma once
#include "../Object.h"


class Title : public Object
{

public:

	Title();

	~Title();

private:

	// 画像ハンドル
	int m_graph_hdl = 0;

	// ロゴの角度
	float m_angle = 0.0f; 
	// アニメーションの速度
	float m_anim_speed = 90.0f;
	// アルファ値
	float m_alpha = 0.0f;
	// 経過時間
	float m_alpha_speed = 30.0f;

	// 描画フラグ
	bool m_is_draw = false;
	// アニメーション状態
	bool m_is_animating = false; 

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);


	void WakeUp(const float delta_time);

	void Disappear(const float delta_time);

	// トリガー処理
	bool SeqTrigger(const float delta_time);
	// 起き上がる処理
	bool SeqWakeUp(const float delta_time);
	// 消える処理
	bool SeqDisappear(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	bool GetIsDraw() const { return m_is_draw; }
};
