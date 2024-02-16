#pragma once
#include "ChangeGraph.h"


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
