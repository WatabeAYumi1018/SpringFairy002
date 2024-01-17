#pragma once
#include "../[000]GamEngine/[001]Scene/SceneBase.h"
#include "../[002]ScenePlay/[000]Object/Object.h"


class Factory;
class GameCamera;
class StagePhase;
class ItemGenerator;


class ScenePlay : public SceneBase
{

public:

	ScenePlay();

	~ScenePlay();

private:

	std::shared_ptr<Factory> m_factory = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<StagePhase> m_stagePhase = nullptr;
	std::shared_ptr<ItemGenerator> m_itemGenerator = nullptr;

	std::list<std::shared_ptr<Object>> m_objects;

	// シーケンス
	tnl::Sequence<ScenePlay> m_sequence
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqStart);


	// シーケンス開始
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;
};