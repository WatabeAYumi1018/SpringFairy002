#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"

class CinemaCamera;
class Mediator;


class CinemaBack : public Object
{

public:

	struct sBubble
	{
		tnl::Vector3 s_pos;
		int s_alpha;
		int s_size;
		float s_life_time;
		bool s_is_active;
	};

	CinemaBack();

	~CinemaBack();

private:

	int m_first_back_hdl = 0;
	int m_second_back_hdl = 0;
	int m_third_back_hdl = 0;

	int m_fog_hdl = 0;
	int m_bubble_hdl = 0;

	int m_alpha = 0;

	float m_elapsed_time = 0.0f;
	float m_total_active_time = 2.0f;

	bool m_is_first = false;
	bool m_is_second = false;
	bool m_is_third = false;

	bool m_is_fog = false;
	bool m_is_bubble = false;

	std::vector<sBubble> m_bubbles;

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void LoadCinemaBackInfo();

	void UpdateFogBlend();

	void RandomBubbleCalc();

	void UpdateBubblesActive(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	void SetIsFirst(bool is_first) { m_is_first = is_first; }

	void SetIsSecond(bool is_second) { m_is_second = is_second; }

	void SetIsThird(bool is_third) { m_is_third = is_third; }

	void SetIsFog(bool is_fog) { m_is_fog = is_fog; }

	void SetIsBubble(bool is_bubble) { m_is_bubble = is_bubble; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};