#pragma once
#include "../[000]GameEngine/[001]Scene/SceneBase.h"
#include "../[001]Common/[000]Object/Object.h"

class OpFactory;
class OpCamera;


class SceneOp : public SceneBase
{

public:

	SceneOp();

	~SceneOp();

private:

	std::shared_ptr<OpFactory> m_factory = nullptr;

	std::shared_ptr<OpCamera> m_opCamera = nullptr;

	std::list<std::shared_ptr<Object>> m_objects;

	// シーケンス
	tnl::Sequence<SceneOp> m_sequence
		= tnl::Sequence<SceneOp>(this, &SceneOp::SeqStart);


	// シーケンス開始
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;
};