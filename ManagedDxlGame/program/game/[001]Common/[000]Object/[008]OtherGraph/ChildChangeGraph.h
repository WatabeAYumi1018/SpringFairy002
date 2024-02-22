#pragma once
#include "ChangeGraph.h"


///////////////////////////////////////////////////////////////////////////
//
// カメラ遷移する際のイラストの定義と更新描画処理を行うクラス
// ※遷移を自然にするために、本クラスはゲームカメラのみで使用
// 　ふたつのクラスを同時に使用することで、遷移時のイラストを自然に表示する
//　
///////////////////////////////////////////////////////////////////////////


class ChildChangeGraph : public ChangeGraph
{

public:

	ChildChangeGraph();

	~ChildChangeGraph();

private:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};
