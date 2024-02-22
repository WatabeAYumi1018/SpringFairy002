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

	struct sEffectType
	{
		int s_id;
		std::string s_effect_path;
	};

	Effect();

	~Effect();


private:

	int m_start_id = 0;
	int m_end_id = 0;

	// オフセット値
	float m_offset = 150.0f;

	bool m_is_screen = false;
	bool m_is_not_draw = false;

	CameraPhase::eCameraPhase m_camera_phase
		= CameraPhase::eCameraPhase::e_cinema;

	StagePhase::eStagePhase m_stage_phase
		= StagePhase::eStagePhase::e_flower;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	std::vector<Effect::sEffectType> m_effects_type;
	// エフェクトのアクティブ状態
	std::unordered_map<int,bool> m_active_effects;

	std::shared_ptr<Mediator> m_mediator = nullptr;
	
	// シネマ画面のエフェクト処理
	void EffectTransCinema();
	// ゲーム画面のエフェクト処理
	void EffectTransGame();

	// エフェクトのアクティブ設定
	void SetEffectActive(int start, int end, bool is_active);
	// エフェクトのオフセット設定
	void EffectOffset(int start,int end,tnl::Vector3& pos);
	// プレイヤーアクションエフェクト設定
	void EffectPlayerAction(int start, int end,bool is_game = true);
	// 軌跡エフェクト設定
	void EffectPath(int start, int end, bool is_player = true);
	// 蝶エフェクト設定
	void EffectButterfly(int id);
	// ギミックエフェクト設定
	void EffectGimmick(int id);
	// スクリーンエフェクト設定
	void EffectScreen(int start, int end, bool is_game = true);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsScreen(bool is_screen) { m_is_screen = is_screen; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};