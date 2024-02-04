#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;


class OpCamera : public dxe::Camera
{

public:

	OpCamera();

	~OpCamera() {}

private:

	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 300, -300 };
	tnl::Vector3 m_new_offset = { 0,300,-300 };
	// ��]
	tnl::Quaternion m_rot;

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(OpCamera, &OpCamera::SeqNormal);

	// ���`��Ԋ֐�
	tnl::Vector3 Lerp(const tnl::Vector3& start
			 		, const tnl::Vector3& end, float t);

	// �Œ�J����
	void Fixed(tnl::Vector3& offset);
	// �J�����ڍs
	void ToOffset(const float delta_time, tnl::Vector3& offset);

	// �ʏ�
	bool SeqNormal(const float delta_time);
	// �ʏ킩��A�b�v�ֈڍs
	bool SeqNormalToUp(const float delta_time);
	// �A�b�v
	bool SeqUp(const float delta_time);
	// �A�b�v��������ֈڍs
	bool SeqUpToBack(const float delta_time);
	// ����
	bool SeqBack(const float delta_time);

public:

	void update(const float delta_time) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};