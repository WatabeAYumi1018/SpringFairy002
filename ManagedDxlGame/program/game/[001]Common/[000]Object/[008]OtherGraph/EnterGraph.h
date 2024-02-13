#pragma once
#include "../Object.h"


class EnterGraph : public Object
{

public:

	EnterGraph();
	~EnterGraph();

private:

	int m_enter_hdl = 0;

	bool m_is_active = false;

	bool m_is_flash = false;

	float m_elasped_time = 0.0f;

public:

	void Update(const float delta_time) override;
	// OP—p
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	// ED—p
	void Draw();

	void SetIsActive(bool is_active){ m_is_active = is_active; }
};