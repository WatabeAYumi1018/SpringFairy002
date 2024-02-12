#pragma once
#include "../Object.h"


class Mediator;


class Gate : public Object
{

public:

	struct sGateInfo
	{
		int s_id;
		std::string s_texture_path;
	};

	Gate();

	~Gate() {}

private:


	// ゲートの動き開始フラグ
	bool m_is_active = false;
	// ゲートが開いたフラグ
	bool m_is_opend = false;

	// ゲートデータを格納
	std::vector<sGateInfo> m_gates_info;

	std::vector<std::shared_ptr<dxe::Mesh>> m_meshes;


	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Gate, &Gate::SeqTrigger);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// メッシュの生成
	void CreateMesh();
	// メッシュの配置指定
	void SetMeshMatrix();

	// トリガー処理
	bool SeqTrigger(const float delta_time);
	// イラストの変更処理
	bool SeqDrawChange(const float delta_time);
	// ゲートオープン処理
	bool SeqOpen(const float delta_time);


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
