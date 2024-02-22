#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../[002]Floor/Floor.h"
#include "Model.h"


Model::~Model()
{
	// ���f���̏������
	for (sModelInfo& model : m_models_info)
	{
		MV1DeleteModel(model.s_model_hdl);
	}
	for (sTreeInfo& tree : m_trees_info)
	{
		MV1DeleteModel(tree.s_model_hdl);
	}

    m_models_info.clear();
    m_trees_info.clear();
}

void Model::Initialize()
{
	// �X�e�[�W���f���̏����擾
	m_models_info = m_mediator->GetStageModelInfo();
    m_trees_info = m_mediator->GetStageTreeInfo();
    // �ÓI���f���Ŗ��t���[���Z�o����K�v�͂Ȃ�
    SetTreePos();
}

void Model::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// ���ʌ����̎��̏���
	if (!m_mediator->GetIsGimmickGroundActive())
	{
		if (m_mediator->GetNowStagePhaseState()
					== StagePhase::eStagePhase::e_flower)
		{
			DrawStageNormal(m_models_info, 0);
		}
		else if(m_mediator->GetNowStagePhaseState() 
					== StagePhase::eStagePhase::e_wood)
		{
			DrawStageNormal(m_models_info, 1);
		}
		else
		{
            if (m_look_side_front)
            {
                DrawStageRot(m_models_info, 2);
            }
            else
            {
                DrawStageNormal(m_models_info, 2);
            }
            
            DrawTree();
        }
	}
	// �T�C�h�����������̏���
	else
	{
        if (m_mediator->GetNowStagePhaseState()
            == StagePhase::eStagePhase::e_flower)
        {
            DrawStageRot(m_models_info, 0);
        }
        else if (m_mediator->GetNowStagePhaseState()
                == StagePhase::eStagePhase::e_wood)
        {
          DrawStageRot(m_models_info, 1);
        }
        else
        {
          DrawStageRot(m_models_info, 2);
          DrawTree();
        }
	}
}

void Model::CalcGridPos(int grid_size)
{
	tnl::Vector3 target_pos 
        = m_mediator->GetCameraTargetPlayerPos();

	// �v���C���[�̌��݈ʒu����O���b�h���W���擾
    m_grid_x = static_cast<int>(target_pos.x / grid_size);
    m_grid_z = static_cast<int>(target_pos.z / grid_size);
}

tnl::Vector3 Model::CalcModelPos(int x, int z,int grid_size)
{
	tnl::Vector3 pos;

	pos.x = static_cast<float>(x * grid_size);
	pos.y = Floor::DRAW_OFFSET;

    if (m_mediator->GetNowStagePhaseState() 
        == StagePhase::eStagePhase::e_wood)
    {
		// �G���Awood�̎��͓��ʂȏ����i��: �t���A�̕`��ʒu��������j
		pos.y *= 2;
	}

	// ���f���̑O���I�t�Z�b�g��K�p
	pos.z = static_cast<float>(z * grid_size);

	return pos;
}

void Model::DrawStageNormal(std::vector<sModelInfo>& models_info, int id)
{
    // �`��͈͂̐ݒ�i�^�[�Q�b�g�̈ʒu�𒆐S�ɑS�����Ɍ����āj
    // �G���A�ɂ���Ė��x�𕪂����������l�����邽�߁A�����Őݒ�
    // ���{���͂��̂�����A�f�o�b�O�ŊO������ύX�ł���悤�ɂ���̂��D�܂���
    // ������K�͂Ə����̕��G�����l�����āA����͌Œ�l�Őݒ�i�ȍ~�����l�j
    int draw_range = 5;
    // �O���b�h�̃T�C�Y�i�l���������قǖ��x�������Ȃ�j
    // �G���A�ɂ���Ė��x�𕪂����������l�����邽�߁A�����Őݒ�
    int grid_size = 1500;

    CalcGridPos(grid_size);

    for (int z = m_grid_z - draw_range; z <= m_grid_z + draw_range; z++)
    {
        for (int x = m_grid_x - draw_range; x <= m_grid_x + draw_range; x++)
        {  
            m_pos = CalcModelPos(x, z,grid_size);
            // �P�ʃN�H�[�^�j�I����ݒ�
            m_rot = { 0,0,0,1 };

            MATRIX matrix = GetTransformMatrix();

            MV1SetMatrix(models_info[id].s_model_hdl, matrix);

            // ���f����`��
            MV1DrawModel(models_info[id].s_model_hdl);
        }
    }
}

void Model::DrawStageRot(std::vector<sModelInfo>& models_info,int id)
{
    // �`��͈͂̐ݒ�i�^�[�Q�b�g�̈ʒu�𒆐S�ɑS�����Ɍ����āj
    // �G���A�ɂ���Ė��x�𕪂����������l�����邽�߁A�����Őݒ�
    int draw_range = 5;
    // �O���b�h�̃T�C�Y�i�l���������قǖ��x�������Ȃ�j
    // �G���A�ɂ���Ė��x�𕪂����������l�����邽�߁A�����Őݒ�
    int grid_size = 1500;

    CalcGridPos(grid_size);

    for (int z = m_grid_z - draw_range; z <= m_grid_z + draw_range; z++)
    {
        for (int x = m_grid_x - draw_range; x <= m_grid_x + draw_range; x++)
        {
            m_pos = CalcModelPos(x, z,grid_size);

            if (m_mediator->GetPlayerLookSideRight())
            {
				m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
			}
            else if(m_mediator->GetPlayerLookSideLeft())
            {
				m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 0));
			}
            else if (m_look_side_front)
            {
                m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));
            }

            MATRIX matrix = GetTransformMatrix();

            MV1SetMatrix(models_info[id].s_model_hdl, matrix);

            MV1DrawModel(models_info[id].s_model_hdl);
        }
    }
}

void Model::SetTreePos()
{
    // �X�e�[�W3�`��̂��߁A�f�t�H���g���W�����O�ɐݒ�
    tnl::Vector3 pos;

    // �ǂݎ�����O���b�h�̍Ō�̗���擾
    int width = m_mediator->GetStageLaneWidth();

    // �Ō�̗񂩂���͈͓̔��Ń����_���Ɏ��؂�z�u
    // 4 : �Ȃ�ׂ��L�߂ɔz�u���邽�߂̒l
    int range = 4;

    // ���؃��f����10�{�`��
    for (int i = 0; i < m_tree_create_num; ++i)
    {
        // ���[���h���W�ɕϊ�
        float max_x = static_cast<float>((width + range) * Lane::LANE_SIZE);
        float min_x = static_cast<float>((width - range) * Lane::LANE_SIZE);

        pos.x = tnl::GetRandomDistributionFloat(min_x, max_x);
        pos.y = Floor::DRAW_OFFSET;
        // 2 : ������x�̂�Ƃ���������邽�߂̒l
        // ���̕ӂ�̐��l���f�o�b�O�ŊO������ύX�ł���悤�ɂ���̂��D�܂���
        pos.z += Lane::LANE_SIZE * 2 * i;

		VECTOR pos_vec = wta::ConvertToVECTOR(pos);

        m_trees_pos.emplace_back(pos_vec);
	}
}

void Model::DrawTree()
{
    for (VECTOR tree_pos : m_trees_pos)
    {
        // ���C�e�B���O�ݒ�
        SetLight(m_trees_info[1].s_model_hdl);
        // �ۑ����ꂽ�ʒu�����g�p���ĕ`��
        MV1SetPosition(m_trees_info[1].s_model_hdl, tree_pos);
        // ���f����`��
        MV1DrawModel(m_trees_info[1].s_model_hdl);
    }
}