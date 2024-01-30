#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../library/tnl_sequence.h"
#include "../Character.h"


class Partner : public Character
{

public:

	enum class ePartnerType
	{
		green,
		black,
		pink
	};

	Partner();

	~Partner() {}


	//----------------------------------------//

private:

	// 行列の更新処理
	void UpdateMatrix(float delta_time);

public:

	// 初期化
	void Initialize() override;
	// 更新
	void Update(float delta_time) override;
	// 描画処理
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};