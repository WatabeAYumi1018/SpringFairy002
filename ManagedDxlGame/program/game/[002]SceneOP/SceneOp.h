#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"
#include "../[001]Common/[000]Object/Object.h"

class OpFactory;
class OpCamera;


///////////////////////////////////////////////////////////////////////////
//
// OPシーンの一括処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class SceneOp : public SceneBase
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	SceneOp();
	~SceneOp();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// オブジェクトリスト
 	std::list<std::shared_ptr<Object>> m_objects;
	
	// Opファクトリーのポインタ
	std::shared_ptr<OpFactory> m_factory = nullptr;
	// Opカメラのポインタ
	std::shared_ptr<OpCamera> m_opCamera = nullptr;


	// シーケンス
	tnl::Sequence<SceneOp> m_sequence
		= tnl::Sequence<SceneOp>(this, &SceneOp::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// シーケンス開始
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};