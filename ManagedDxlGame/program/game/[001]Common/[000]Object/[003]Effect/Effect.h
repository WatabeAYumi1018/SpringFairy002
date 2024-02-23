#pragma once
#include "../../[003]Phase/CameraPhase.h"
#include "../../[003]Phase/StagePhase.h"
#include "../Object.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// エフェクトパーティクルの定義と更新描画処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class Effect : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	struct sEffectType
	{
		int s_id;
		std::string s_effect_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	Effect() {}
	~Effect();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// オフセット値
	float m_offset = 150.0f;

	// スクリーンエフェクトの活性化フラグ
	bool m_is_screen = false;
	// 描画を行わないフラグ（ループ再生で毎フレームのスタートを防ぐため）
	bool m_is_not_draw = false;

	// カメラフェーズ
	CameraPhase::eCameraPhase m_camera_phase
		= CameraPhase::eCameraPhase::e_cinema;

	// ステージフェーズ
	StagePhase::eStagePhase m_stage_phase
		= StagePhase::eStagePhase::e_flower;

	// パーティクルポインタのベクター
	std::vector<std::shared_ptr<dxe::Particle>> m_particles;
	
	// エフェクトタイプのベクター
	std::vector<Effect::sEffectType> m_effects_type;
	
	// エフェクトのIDとアクティブ状態
	std::unordered_map<int,bool> m_active_effects;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// シネマ画面のエフェクト処理
	void EffectTransCinema();
	// ゲーム画面のエフェクト処理
	void EffectTransGame();

	// エフェクトのアクティブ設定
	// arg1 ... 開始ID
	// arg2 ... 終了ID
	// arg3 ... 活性化非活性化の設定
	void SetEffectActive(int start, int end, bool is_active);

	// エフェクトのオフセット設定
	// arg1 ... 開始ID
	// arg2 ... 終了ID
	// arg3 ... 座標
	void EffectOffset(int start,int end,tnl::Vector3& pos);

	// プレイヤーアクションエフェクト設定
	// arg1 ... 開始ID
	// arg2 ... 終了ID
	// arg3 ... ゲーム画面かどうか(デフォルトでゲーム画面。falseでシネマ画面)
	void EffectPlayerAction(int start, int end,bool is_game = true);

	// 軌跡エフェクト設定
	// arg1 ... 開始ID
	// arg2 ... 終了ID
	// arg3 ... プレイヤーかどうか(デフォルトでプレイヤー。falseで蝶)
	void EffectPath(int start, int end, bool is_player = true);

	// 蝶エフェクト設定
	// arg ... 該当ID
	void EffectButterfly(int id);

	// ギミックエフェクト設定
	// arg ... 該当ID
	void EffectGimmick(int id);

	// スクリーンエフェクト設定
	// arg1 ... 開始ID
	// arg2 ... 終了ID
	// arg3 ... ゲーム画面かどうか(デフォルトでゲーム画面。falseでシネマ画面)
	void EffectScreen(int start, int end, bool is_game = true);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スクリーンエフェクトの活性化フラグの設定
	void SetIsScreen(bool is_screen) { m_is_screen = is_screen; }

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};