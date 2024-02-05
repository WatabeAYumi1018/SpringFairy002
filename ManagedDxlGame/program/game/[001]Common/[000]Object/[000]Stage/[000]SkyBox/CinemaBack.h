#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"

class CinemaCamera;
class Mediator;


class CinemaBack : public Object
{

public:


	CinemaBack();

	~CinemaBack();

private:

	int m_fog_hdl = 0;
	int m_first_back_hdl = 0;
	int m_second_back_hdl = 0;

	int m_alpha = 0;

	bool m_is_fog = false;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void LoadCinemaBackInfo();

	void UpdateFogBlend();

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	void SetIsFog(bool is_fog) { m_is_fog = is_fog; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};