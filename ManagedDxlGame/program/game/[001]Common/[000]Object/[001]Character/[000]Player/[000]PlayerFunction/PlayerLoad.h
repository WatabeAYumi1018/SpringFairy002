#include "../dxlib_ext/dxlib_ext.h"


class PlayerLoad
{

public:

	PlayerLoad();

	~PlayerLoad();

private:

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
	std::vector<std::vector<float>> m_csv_player_move;


	void LoadPlayerMoveInfo();

public:

	float GetMoveSpeed() const { return m_move_speed; }

	float GetMoveRot() const { return m_move_rot; }

	float GetSaltoTotalTime() const { return m_salto_total_time; }

	float GetSaltoRadius() const { return m_salto_radius; }

	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }
	//// �ړ����x�ω���ݒ�
	//void SetMoveChangeSpeed(float speed) { m_move_change_speed = speed; }

};