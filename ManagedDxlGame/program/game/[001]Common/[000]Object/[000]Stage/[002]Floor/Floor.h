#pragma once
#include "../../../[000]Object/Object.h"

class Mediator;


class Floor : public Object
{

public:

	struct sFloorType
	{
		int s_id;
		std::string s_graph_path;
	};

	Floor();
	~Floor();

	static const int DRAW_DISTANCE = -400;

private:

	// ステージモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_floor_info;
	// ステージモデルの情報格納用
	std::vector<sFloorType> m_floor_info;

	std::shared_ptr<dxe::Mesh> m_floor = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Floor, &Floor::SeqFlower);


	void LoadFloorTypeInfo();

	void DrawFloor(std::shared_ptr<dxe::Camera> camera);

	// フラワーエリア
	bool SeqFlower(const float delta_time);
	// ウッドエリア
	bool SeqWood(const float delta_time);
	// ファンシーエリア
	bool SeqFancy(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
