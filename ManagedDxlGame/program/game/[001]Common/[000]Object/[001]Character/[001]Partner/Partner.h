#pragma once
#include "../../../../../library/tnl_sequence.h"
#include "../Character.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// パートナーキャラクターの更新描画を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Partner : public Character
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Partner();
	~Partner();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ関数------------------------------------//

	// 行列の更新処理
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateMatrix(const float delta_time);

public:

	void Initialize() override;
	
	void Update(const float delta_time) override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//
};