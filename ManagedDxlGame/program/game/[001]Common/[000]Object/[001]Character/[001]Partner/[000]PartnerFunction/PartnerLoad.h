#include "../dxlib_ext/dxlib_ext.h"


class PartnerLoad
{

public:

	PartnerLoad();

	~PartnerLoad();

private:

	// モデル
	int m_model_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_hdl = 0;
	// moveボーン
	int m_anim_bone_move_hdl = 0;
	// テクスチャ
	int m_texture_hdl = 0;

	// パートナーの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<std::string>> m_csv_model;

	void LoadPartnerModelInfo();

public:

	int GetModelHdl() const { return m_model_hdl; }

	int GetAnimBoneIdleHdl() const { return m_anim_bone_idle_hdl; }

	int GetAnimBoneMoveHdl() const { return m_anim_bone_move_hdl; }
};