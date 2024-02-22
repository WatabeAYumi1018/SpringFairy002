#pragma once
#include "../../../[000]Object/Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 床のプレーンの定義、読み取りから描画処理に関するクラス
// ※Loadクラスに分けるまでもないため、本クラス内でcsvロードも行う
//
/////////////////////////////////////////////////////////////////////////////////////////


class Floor : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// 床の種類
	struct sFloorType
	{
		int s_id;
		std::string s_graph_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Floor();
	~Floor();

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数------------------------------------//

	// 床のｙ座標オフセット
	static const int DRAW_OFFSET = -400;

private:

	// ステージモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_floor_info;
	// ステージモデルの情報格納用
	std::vector<sFloorType> m_floor_info;

	// メッシュのポインタ
	std::shared_ptr<dxe::Mesh> m_floor = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Floor, &Floor::SeqFlower);

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 床の情報読み取り
	void LoadFloorTypeInfo();
	// 床の描画
	void DrawFloor(std::shared_ptr<dxe::Camera> camera);

	// フラワーエリア
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFlower(const float delta_time);
	// ウッドエリア
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqWood(const float delta_time);
	// ファンシーエリア
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFancy(const float delta_time);

public:

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
