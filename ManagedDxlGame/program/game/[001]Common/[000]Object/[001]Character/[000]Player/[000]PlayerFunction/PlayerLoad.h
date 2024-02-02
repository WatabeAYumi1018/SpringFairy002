#include "../dxlib_ext/dxlib_ext.h"


class PlayerLoad
{

public:

	PlayerLoad();

	~PlayerLoad();

private:

	// ���f��
	int m_model_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_hdl = 0;
	// bloom�{�[��
	int m_anim_bone_bloom_hdl = 0;
	// dance�{�[��
	int m_anim_bone_dance_hdl = 0;
	// �e�N�X�`��
	int m_texture_hdl = 0;

	// �ړ����x
	float m_move_speed = 0;
	// �ړ���]���x
	float m_move_rot = 0;
	// �󋵂ɂ��ړ����x�ω�
	float m_move_change_speed = 0;

	// ���Ԃ�̈ړ����x
	float m_salto_move_speed = 0;
	// ���Ԃ�̉�]���x
	float m_salto_rot = 0;
	// ���Ԃ�̋O�����a
	float m_salto_radius = 0;
	// ���Ԃ�̏��v����
	float m_salto_total_time = 6.0f;

	// ���[���̉�]���x
	float m_rolling_rot = 10;
	// ���̎��̉�]���x
	float m_figure_eight_rot = 10;

	// �v���C���[�̈ړ����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<float>> m_csv_move;

	std::vector<std::vector<std::string>> m_csv_model;

	void LoadPlayerMoveInfo();

	void LoadPlayerModelInfo();

public:

	int GetModelHdl() const { return m_model_hdl; }

	int GetAnimBoneIdleHdl() const { return m_anim_bone_idle_hdl; }

	int GetAnimBoneMoveHdl() const { return m_anim_bone_move_hdl; }

	int GetAnimBoneBloomHdl() const { return m_anim_bone_bloom_hdl; }

	int GetAnimBoneDanceHdl() const { return m_anim_bone_dance_hdl; }

	float GetMoveSpeed() const { return m_move_speed; }

	float GetMoveRot() const { return m_move_rot; }

	float GetSaltoTotalTime() const { return m_salto_total_time; }

	float GetSaltoRadius() const { return m_salto_radius; }

	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }
	//// �ړ����x�ω���ݒ�
	//void SetMoveChangeSpeed(float speed) { m_move_change_speed = speed; }

};