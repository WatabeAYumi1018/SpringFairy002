#include "ChildChangeGraph.h"


ChildChangeGraph::ChildChangeGraph()
{

}

ChildChangeGraph::~ChildChangeGraph()
{

}

void ChildChangeGraph::Initialize()
{
	ChangeGraph::Initialize();
}

void ChildChangeGraph::Update(float delta_time)
{
	ChangeGraph::Update(delta_time);
}

void ChildChangeGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	ChangeGraph::Draw(camera);
}
