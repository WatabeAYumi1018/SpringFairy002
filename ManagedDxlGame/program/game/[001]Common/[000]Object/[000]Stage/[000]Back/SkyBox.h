#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// スカイボックスの定義と更新描画処理を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class SkyBox : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// スカイボックスの情報
	struct sSkyBoxInfo
	{
		int s_id;
		std::string s_texture_path;
		std::string s_material_path;
		std::string s_screen_effect_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	SkyBox() {}

	~SkyBox();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// OPのみのフラグ(Opカメラでのみ設定)
	bool m_is_op = false;

	// スカイボックスの情報
	std::vector<sSkyBoxInfo> m_skybox_info;
	// スカイボックスのメッシュ
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;
	// メッシュのポインタ
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// スクリーンエフェクトのポインタ
	std::shared_ptr<dxe::ScreenEffect> m_screen_effect = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//----------------------------------メンバ関数----------------------------------//

	// スカイボックスの作成
	void CreateSkyBox();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スカイボックスのOPフラグの設定
	// arg ... OP描画フラグ
	void SetIsOp(bool is_op) { m_is_op = is_op; }

	// メディエータの設定
	// arg ... メディエータのポインタ
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};