#pragma once
#include "../Object.h"


class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// タイトルの一括処理を行うクラス
// ※Loadクラスに分けるまでもないため、本クラス内でcsvロードも行う
//
///////////////////////////////////////////////////////////////////////////


class Title : public Object
{

public:

	Title();

	~Title();

private:

	int m_model_hdl = 0;
	int m_texture_game_hdl = 0;

	tnl::Quaternion m_end_rot;
	
	// アニメーションの速度
	float m_elapsed_time = 0;
	// 経過時間
	float m_total_time = 5.0f;
	// アルファ値
	float m_alpha = 0.0f;
	// アニメーションの速度
	float m_alpha_speed = 0.5f;

	// 描画フラグ
	bool m_is_draw = false;
	// アニメーション状態
	bool m_is_animated = false; 
	// 消去フラグ
	bool m_is_disappear = false;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);


	// 描画開始処理
	void StartDraw(const float delta_time);
	// 描画終了処理
	void EndDraw(const float delta_time);
	// タイトル移動処理
	void MoveTitle(const float delta_time);

	// トリガー処理
	bool SeqTrigger(const float delta_time);
	// 通常描画
	bool SeqStay(const float delta_time);
	// 消える処理
	bool SeqOpen(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	bool GetIsDisappear() const { return m_is_disappear; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator; 
	}
};
