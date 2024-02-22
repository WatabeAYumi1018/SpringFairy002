#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// プレイヤーのcsvファイルの読み込みクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerLoad
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PlayerLoad();

	~PlayerLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	//-----Player用変数-----//

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
	
	//----------------------//


	//--CinemaPlayer用変数--//

	// モデル
	int m_model_cinema_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_cinema_hdl = 0;
	// danceボーン
	int m_anim_bone_dance_cinema_hdl = 0;
	// テクスチャ
	int m_texture_cinema_hdl = 0;

	//----------------------//


	//-------共用変数-------//

	// 移動速度
	float m_move_speed = 0;
	// 移動回転速度
	float m_move_rot = 0;

	//----------------------//


	//----------------------//
	// ※以下パラメータについては現在使用していませんが
	// 　今後の拡張を考えて残してます。(実装は大方完了済みで使用箇所を模索中)
	 
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

	//----------------------//

	// プレイヤーの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<float>> m_csv_move;
	// プレイヤーのモデル情報読み取り専用（csvファイル）
	std::vector<std::vector<std::string>> m_csv_model;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// プレイヤーのパラメータ情報読み取り専用（csvファイル）
	// tips ... 初期化時に一度だけ呼び出す
	void LoadPlayerMoveInfo();

	// プレイヤーのモデル情報読み取り専用（csvファイル）
	// tips ... 初期化時に一度だけ呼び出す
	void LoadPlayerModelInfo();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// ゲームプレイヤーのモデルハンドル取得
	int GetModelGameHdl() const { return m_model_game_hdl; }
	
	// シネマプレイヤーのモデルハンドル取得
	int GetModelCinemaHdl() const { return m_model_cinema_hdl; }
	
	// ゲームプレイヤーのmoveボーンハンドル取得
	int GetAnimBoneMoveGameHdl() const { return m_anim_bone_move_game_hdl; }
	
	// ゲームプレイヤーのbloomボーンハンドル取得
	int GetAnimBoneBloomGameHdl() const { return m_anim_bone_bloom_game_hdl; }
	
	// ゲームプレイヤーのdanceボーンハンドル取得
	int GetAnimBoneDanceGameHdl() const { return m_anim_bone_dance_game_hdl; }
	
	// シネマプレイヤーのidleボーンハンドル取得
	int GetAnimBoneIdleCinemaHdl() const { return m_anim_bone_idle_cinema_hdl; }
	
	// シネマプレイヤーのdanceボーンハンドル取得
	int GetAnimBoneDanceCinemaHdl() const { return m_anim_bone_dance_cinema_hdl; }

	// 移動速度取得
	float GetMoveSpeed() const { return m_move_speed; }

	// 移動回転速度取得
	float GetMoveRot() const { return m_move_rot; }

	//----------------------//
	// ※以下パラメータについては現在使用していませんが
	// 　今後の拡張を考えて残してます。(実装は大方完了済みで使用箇所を模索中)

	// 宙返りの総時間取得
	float GetSaltoTotalTime() const { return m_salto_total_time; }
	// 宙返りの軌道半径取得
	float GetSaltoRadius() const { return m_salto_radius; }
	// 宙返りの回転速度取得
	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }

	//----------------------//

	//---------------------------------------------------------------------------------//
};