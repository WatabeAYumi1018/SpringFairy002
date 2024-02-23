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

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	Title();
	~Title();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// モデルハンドル
	int m_model_hdl = 0;
	// テクスチャハンドル
	int m_texture_hdl = 0;
	
	// アルファ値
	float m_alpha = 0.0f;
	// アニメーションの速度
	float m_alpha_speed = 0.5f;

	// 描画フラグ
	bool m_is_draw = false;
	// 消去フラグ
	bool m_is_disappear = false;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 描画開始処理
	// arg ... delta_time(前フレームからの経過時間)
	void StartDraw(const float delta_time);

	// 描画終了処理
	// arg ... delta_time(前フレームからの経過時間)
	void EndDraw(const float delta_time);

	// トリガー処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqTrigger(const float delta_time);

	// 通常描画
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStay(const float delta_time);

	// 消える処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqOpen(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 描画フラグの設定
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	// 消去フラグの取得
	bool GetIsDisappear() const { return m_is_disappear; }

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator; 
	}

	//---------------------------------------------------------------------------------//
};
