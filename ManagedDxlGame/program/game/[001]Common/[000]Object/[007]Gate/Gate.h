#pragma once
#include "../Object.h"


class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// OPゲートイラストの定義と更新描画処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class Gate : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	struct sGateInfo
	{
		int s_id;
		std::string s_texture_path;
		tnl::Vector3 s_pos;
		tnl::Vector3 s_scale;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	Gate() {}
	~Gate();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// ゲートの動き開始フラグ
	bool m_is_active = false;
	// ゲートが開いたフラグ
	bool m_is_opend = false;

	// 種類ごとのゲートデータのベクター
	std::vector<sGateInfo> m_gates_info;

	// ゲートメッシュのベクター
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshes;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Gate, &Gate::SeqTrigger);

	// メッシュのポインタ
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// メッシュの生成
	void CreateMesh();

	// トリガー処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqTrigger(const float delta_time);

	// イラストの変更処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStay(const float delta_time);

	// ゲートオープン処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqOpen(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
