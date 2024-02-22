#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// シネマカメラ演出時の背景の定義と更新描画を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class CinemaBack : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// シネマカメラ背景画像の情報
	// シネマ３のみスカイボックス使用のため、skyBoxクラスから参照
	struct sCinemaBackInfo
	{
		int s_id;
		int s_back_hdl;
	};

	// シネマカメラで使用するバブルの情報
	struct sBubble
	{
		tnl::Vector3 s_pos;
		int s_alpha;
		float s_size;
		float s_life_time;
		bool s_is_active;
	};

	//--------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	CinemaBack();

	~CinemaBack();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// このあたりの基本情報も本当はデバッグ用に外部から読み取るのが好ましい
	// 今回は時間がないので、ここに記入

	// 透明度
	int m_alpha = 0;
	// バブルの作成数
	int m_bubble_num = 20;
	// 透明度の変化速度
	float m_alpha_speed = 5;
	// バブルの生成サイズ最小値・最大値
	float m_bubble_size_min = 40.0f;
	float m_bubble_size_max = 50.0f;
	// バブルの生成速度最小値・最大値
	float m_bubble_life_time_min = 100.0f;
	float m_bubble_life_time_max = 150.0f;

	// フォグの描画フラグ
	bool m_is_fog = false;
	// バブルの描画フラグ
	bool m_is_bubble = false;

	// シネマカメラ背景画像の情報
	std::vector<sCinemaBackInfo> m_cinema_back_info;
	// 全バブルの情報
	std::vector<sBubble> m_bubbles;
	// メッシュのポインタ
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// スカイボックスの情報を読み込む
	void LoadSkyBackInfo();

	// フォグのブレンド更新処理
	void UpdateFogBlend();

	// バブルのアクティブ更新処理
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateBubblesActive(const float delta_time);

	// バブルの描画座標乱数設定
	void RandomBubbleCalc();


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// 透明化のフラグ設定
	// arg ... 透明化フラグ
	void SetIsFog(bool is_fog) { m_is_fog = is_fog; }
	// バブルのフラグ設定
	// arg ... バブルフラグ
	void SetIsBubble(bool is_bubble) { m_is_bubble = is_bubble; }
	// メディエータの設定
	// arg ... メディエータのポインタ
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};