#pragma once
#include "../Character.h"


class Player : public Character
{

public:

	Player();

	~Player();


	//----------------------------------------//

private:

	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	// 行列の更新処理
	void UpdateMatrix(float delta_time);

	void UpdateMesh(float delta_time);

public:

	tnl::Vector3 Forward();

	tnl::Vector3 Back();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(float delta_time) override;
	// 描画処理
	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	const std::vector<std::shared_ptr<dxe::Mesh>>& GetMeshs() const
	{
		return m_meshs;
	}
};