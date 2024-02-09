#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../[003]Phase/CameraPhase.h"
#include "../../../[003]Phase/StagePhase.h"
#include "EffectLoad.h"


class Mediator;

class EffectHandle 
{

public:

	EffectHandle();

	~EffectHandle();

private:

	tnl::Vector3 m_game_pos;
	tnl::Vector3 m_cinema_pos;

	CameraPhase::eCameraPhase m_camera_phase 
			= CameraPhase::eCameraPhase::e_cinema;
	
	StagePhase::eStagePhase m_stage_phase 
			= StagePhase::eStagePhase::e_flower;

	std::vector<Effect::sEffectType> m_effects_type;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	// 状況に応じたエフェクトのベクターを生成
	// プレイヤーのアクションエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_player_action_particles;
	// ギミックエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_gimmick_particles;
	// キャラクターの軌道エフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_chara_path_particles;
	// スクリーンエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_screen_particles;
	// イベントエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_event_particles;


	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 各アクティブエフェクトの取得
	void EffectStocker(int start,int end
						,std::vector<std::shared_ptr<dxe::Particle>>& particles);

	// シネマ画面のエフェクト遷移
	void EffectTransCinema();

	// ゲーム画面のエフェクト遷移
	void EffectTransGame();

	// 各アクティブエフェクトの座標補正
	void AttackOffset();


public:

	void Initialize();

	// 実行エフェクトの更新
	void Update();

	const tnl::Vector3& GetGamePos() const	{ return m_game_pos; }

	const std::vector<std::shared_ptr<dxe::Particle>>& GetPlayerActionParticles() const
	{
		return m_player_action_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetGimmickParticles() const
	{
		return m_gimmick_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetCharaPathParticles() const
	{
		return m_chara_path_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetScreenParticles() const
	{
		return m_screen_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetEventParticles() const
	{
		return m_event_particles;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
