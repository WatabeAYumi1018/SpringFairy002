//#pragma once
//#include "../[000]GamEngine/[001]Scene/SceneBase.h"
//
//
//class Factory;
//class GameCamera;
//
//
//class SceneOp : public SceneBase
//{
//
//public:
//
//	SceneOp();
//
//	~SceneOp();
//
//private:
//
//	std::shared_ptr<Factory> m_factory = nullptr;
//
//	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
//
//	std::list<std::shared_ptr<Object>> m_objects;
//
//	// シーケンス
//	tnl::Sequence<SceneTitle> m_sequence
//		= tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqStart);
//
//
//	// シーケンス開始
//	bool SeqStart(const float delta_time);
//
//public:
//
//	void Initialize() override;
//
//	void Update(const float delta_time) override;
//
//	void Draw(const float delta_time) override;
//
//	void Finalize() override;
//};