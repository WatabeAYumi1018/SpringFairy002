#include "../../../[002]Mediator/Mediator.h"
#include "../../../[001]Camera/CinemaCamera.h"
#include "CinemaBack.h"


CinemaBack::CinemaBack()
{
	LoadCinemaBackInfo();
}

CinemaBack::~CinemaBack()
{
	DeleteGraph(m_first_back_hdl);
}

void CinemaBack::LoadCinemaBackInfo()
{

	m_first_back_hdl = LoadGraph("graphics/illust/background-green.jpg");
	m_second_back_hdl = LoadGraph("graphics/illust/flower.jpg");
	//// csv�t�@�C���̓ǂݍ���
	//m_csv_skybox_info
	//	= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_Info.csv");

	//// �}�b�v�^�C���̑������擾
	//int max_num = m_csv_skybox_info.size();

	//// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	//for (int y = 1; y < max_num; ++y)
	//{
	//	sSkyBoxInfo sky_info;

	//	sky_info.s_id = m_csv_skybox_info[y][0].getInt();

	//	sky_info.s_texture_path = m_csv_skybox_info[y][1].getString();

	//	sky_info.s_material_path = m_csv_skybox_info[y][2].getString();

	//	sky_info.s_screen_effect_path = m_csv_skybox_info[y][3].getString();

	//	m_skybox_info.emplace_back(sky_info);
	//}
}

void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_all ||
		m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_third_left ||
		m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_third_right)
	{
		// ������second_back_hdl��S��ʗp�ɕ`��
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, TRUE);
	}
	else
	{
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH
			, DXE_WINDOW_HEIGHT, m_first_back_hdl, TRUE);
	}
}