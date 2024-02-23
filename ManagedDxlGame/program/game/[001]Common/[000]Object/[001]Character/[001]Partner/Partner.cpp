#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Partner.h"


Partner::Partner()
{
	m_collision_size = 60;
}

Partner::~Partner()
{
	MV1DeleteModel(m_model_hdl);
}

void Partner::Initialize()
{
	StartPos();

	m_mediator->InitializePartnerDraw();

	m_model_hdl = m_mediator->GetPartnerModelHdl();

	SetLight(m_model_hdl);
}

void Partner::Update(const float delta_time)
{
	// �A�j���[�V�����X�V����
	m_mediator->UpdatePartnerAnim(delta_time);

	// �s��v�Z�̍X�V
	UpdateMatrix(delta_time);
}

void Partner::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// ���f���`�揈��
	m_mediator->DrawPartnerModel();

	if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_wood)
	{
		// �p�[�g�i�[�����X�ɖ��邭���邽��emmisive��ύX
		// ���{���̓f�o�b�O�����ŊO������ύX����̂��D�܂���
		// �@�����̕��G��������邽�߁A�����ŏ������s���Ă���
		DxLib::COLOR_F emissive = { 0.7f,0.7f,0.7f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
	else if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_fancy)
	{
		// �p�[�g�i�[�����X�ɖ��邭���邽��emmisive��ύX
		// ���{���̓f�o�b�O�����ŊO������ύX����̂��D�܂���
		// �@�����̕��G��������邽�߁A�����ŏ������s���Ă���
		DxLib::COLOR_F emissive = { 0.9f,0.9f,0.9f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
}

void Partner::UpdateMatrix(const float delta_time)
{
	// �ړ��ɂ����W�Ɖ�]�̍X�V
	m_mediator->UpdatePartnerMoveMatrix(delta_time);

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);
}