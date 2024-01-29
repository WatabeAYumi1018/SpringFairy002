#include "../../../[001]Camera/GameCamera.h"
#include "../[001]Lane/Lane.h"
#include "Floor.h"


Floor::Floor()
{
	int size = Lane::LANE_SIZE;

	// �v���[���T�C�Y�w��(float�^�ɕϊ�)
    float size_f = static_cast<float>(size);

	tnl::Vector3 mesh_size = { size_f,size_f,size_f };

	m_floor = dxe::Mesh::CreatePlaneMV(mesh_size);

	m_floor->setTexture(dxe::Texture::CreateFromFile("graphics/floor/lawn.png"));
	// �v���[�������Ƃ��邽�߉�]
	m_floor->rot_
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90.0f));
	// ���W�𒲐��iY���W�������Ēn�ʂɔz�u)
    float distance = static_cast<float> (Floor::DRAW_DISTANCE);

	m_floor->pos_ = { 0, distance, 0 };
}

void Floor::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // �O���b�h�̃T�C�Y
    int grid_size = 20; 
    // �O���b�h�̔����̃T�C�Y
    int half_grid_size = grid_size / 2; 
    // �t���A�Ԃ̃X�y�[�X
    int spacing = Lane::LANE_SIZE;

    float distance = static_cast<float> (Floor::DRAW_DISTANCE);

    for (int i = -half_grid_size; i < half_grid_size; i++)
    {
        for (int j = -half_grid_size; j < half_grid_size; j++)
        {
            // �e�t���A�̍��W���v�Z
            float x = static_cast<float> (i * spacing);
            float z = static_cast<float> (j * spacing);

            // �t���A�̈ʒu��ݒ�
            m_floor->pos_ = { x, distance, z };

            // �t���A��`��
            m_floor->render(camera);
        }
    }
}

