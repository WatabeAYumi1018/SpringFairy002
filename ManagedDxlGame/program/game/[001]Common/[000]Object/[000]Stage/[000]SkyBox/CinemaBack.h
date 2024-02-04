#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"

class Mediator;


class CinemaBack : public Object
{

public:


	CinemaBack();

	~CinemaBack();

private:

	int m_first_back_hdl = 0;
	int m_second_back_hdl = 0;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void LoadCinemaBackInfo();

public:

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};