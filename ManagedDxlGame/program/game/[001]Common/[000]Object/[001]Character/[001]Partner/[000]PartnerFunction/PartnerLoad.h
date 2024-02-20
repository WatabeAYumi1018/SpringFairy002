#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// パートナーのcsvファイルの読み込みクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerLoad
{

public:

	PartnerLoad();

	~PartnerLoad();

private:

	// モデル
	int m_model_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_cinema_hdl = 0;
	// moveボーン
	int m_anim_bone_move_game_hdl = 0;
	// テクスチャ
	int m_texture_game_hdl = 0;

	// パートナーの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<std::string>> m_csv_model;

	void LoadPartnerModelInfo();

public:

	int GetModelGameHdl() const { return m_model_hdl; }

	int GetAnimBoneIdleHdl() const { return m_anim_bone_idle_cinema_hdl; }

	int GetAnimBoneMoveGameHdl() const { return m_anim_bone_move_game_hdl; }
};