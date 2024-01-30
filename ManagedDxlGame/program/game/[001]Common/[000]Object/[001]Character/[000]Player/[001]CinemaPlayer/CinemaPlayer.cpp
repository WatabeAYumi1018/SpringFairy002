#include "../../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_pos = { 0, 3000, 0 };
}

CinemaPlayer::~CinemaPlayer()
{

}

void CinemaPlayer::Update(const float delta_time)
{
	if (m_mediator->GetIsCinemaCameraActive())
	{
		m_mediator->UpdateCinemaCameraPlayer(delta_time);

		// ��]�ƍ��W����s����v�Z
		m_matrix = CalcMatrix();



		// ���f���ɍs���K�p
		MV1SetPosition(m_model_hdl, VGet(0,3000,0));
	}
}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_mediator->GetIsCinemaCameraActive())
	{
		// ���f���`�揈��
		m_mediator->DrawPlayerModel();
	}
}