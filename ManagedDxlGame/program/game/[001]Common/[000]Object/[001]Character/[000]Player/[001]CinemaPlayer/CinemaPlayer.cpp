#include "../../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_pos = { 0, 0, 0 };

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));

	m_mesh = dxe::Mesh::CreateSphereMV(50);
}

CinemaPlayer::~CinemaPlayer()
{

}

void CinemaPlayer::Initialize()
{
	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelHdl();

	SetLight(m_model_hdl);
}

void CinemaPlayer::Update(const float delta_time)
{
	//if (m_mediator->GetIsCinemaCameraActive())
	//{
		m_mediator->UpdateCinemaCameraPlayer(delta_time);

		// ��]�ƍ��W����s����v�Z
		m_matrix = CalcMatrix();

		//m_mesh->pos_ = m_pos;

		// ���f���ɍs���K�p
		MV1SetMatrix(m_model_hdl, m_matrix);
	//}
}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	//if (m_mediator->GetIsCinemaCameraActive())
	//{
	 m_mesh->render(camera);
	// 
		// ���f���`�揈��
		m_mediator->DrawPlayerModel();
	//}
}