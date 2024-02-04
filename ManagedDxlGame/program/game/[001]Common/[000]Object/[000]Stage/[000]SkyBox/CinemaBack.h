#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"


class CinemaBack : public Object
{

public:


	CinemaBack();

	~CinemaBack();

private:

	int m_first_back_hdl = 0;


	void LoadCinemaBackInfo();

public:

	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};