#include "../dxlib_ext/dxlib_ext.h"


class PlayerLoad
{

public:

	PlayerLoad();

	~PlayerLoad();

private:


	//-----Player-----//
	
	// モデル
	int m_model_game_hdl = 0;
	// moveボーン
	int m_anim_bone_move_game_hdl = 0;
	// bloomボーン
	int m_anim_bone_bloom_game_hdl = 0;
	// danceボーン
	int m_anim_bone_dance_game_hdl = 0;
	// テクスチャ
	int m_texture_game_hdl = 0;
	
	//-----------------//

	//--CinemaPlayer--//

	// モデル
	int m_model_cinema_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_cinema_hdl = 0;
	// moveボーン
	int m_anim_bone_move_cinema_hdl = 0;
	// danceボーン
	int m_anim_bone_dance_cinema_hdl = 0;
	// テクスチャ
	int m_texture_cinema_hdl = 0;

	//-----------------//


	// 移動速度
	float m_move_speed = 0;
	// 移動回転速度
	float m_move_rot = 0;
	// 状況による移動速度変化
	float m_move_change_speed = 0;

	// 宙返りの移動速度
	float m_salto_move_speed = 0;
	// 宙返りの回転速度
	float m_salto_rot = 0;
	// 宙返りの軌道半径
	float m_salto_radius = 0;
	// 宙返りの所要時間
	float m_salto_total_time = 6.0f;

	// ロールの回転速度
	float m_rolling_rot = 10;
	// 八の字の回転速度
	float m_figure_eight_rot = 10;

	// プレイヤーの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<float>> m_csv_move;

	std::vector<std::vector<std::string>> m_csv_model;

	void LoadPlayerMoveInfo();

	void LoadPlayerModelInfo();

public:

	int GetModelGameHdl() const { return m_model_game_hdl; }

	int GetModelCinemaHdl() const { return m_model_cinema_hdl; }

	int GetAnimBoneMoveGameHdl() const { return m_anim_bone_move_game_hdl; }

	int GetAnimBoneBloomGameHdl() const { return m_anim_bone_bloom_game_hdl; }

	int GetAnimBoneDanceGameHdl() const { return m_anim_bone_dance_game_hdl; }

	int GetAnimBoneIdleCinemaHdl() const { return m_anim_bone_idle_cinema_hdl; }

	int GetAnimBoneDanceCinemaHdl() const { return m_anim_bone_dance_cinema_hdl; }

	int GetAnimBoneMoveCinemaHdl() const { return m_anim_bone_move_cinema_hdl; }

	float GetMoveSpeed() const { return m_move_speed; }

	float GetMoveRot() const { return m_move_rot; }

	float GetSaltoTotalTime() const { return m_salto_total_time; }

	float GetSaltoRadius() const { return m_salto_radius; }

	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }
	//// 移動速度変化を設定
	//void SetMoveChangeSpeed(float speed) { m_move_change_speed = speed; }

};