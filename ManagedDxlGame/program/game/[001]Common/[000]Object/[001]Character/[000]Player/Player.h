#pragma once
#include "../Character.h"


///////////////////////////////////////////////////////////////////////////
//
// プレイヤーの更新描画を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class Player : public Character
{

public:

	Player();

	~Player() {}


	//----------------------------------------//

private:

	// メッシュ
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	// 行列の更新処理
	void UpdateMatrix(float delta_time);
	// メッシュの更新処理
	void UpdateMesh(float delta_time);

public:

	// 前方向の算出
	tnl::Vector3 Forward();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(float delta_time) override;
	// 描画処理
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	// メッシュの取得
	const std::vector<std::shared_ptr<dxe::Mesh>>& GetMeshs() const
	{
		return m_meshs;
	}
};