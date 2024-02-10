#include "../../../wta_library/wta_Convert.h"
#include "Transform.h"


MATRIX Transform::GetTransformMatrix()
{
	// �@�g��k����ݒ肷��

	// tnl::m_scale��VECTOR�^�ɕϊ�
	VECTOR vecter_scale = wta::ConvertToVECTOR(m_scale);

	// �X�P�[����ݒ肷��
	// VECTOR�^����MATRIX�^�ɕϊ�
	MATRIX matrix_scale = MGetScale(vecter_scale);

	// ------------------------

	// �A��]��ݒ肷��

	// �N�H�[�^�j�I�������]�s���ݒ肷��
	MATRIX matrix_rotation = wta::ConvertQuaternionToMatrix(m_rot);

	// ------------------------

	// �B���W��ݒ肷��

	// tnl::m_pos��VECTOR�^�ɕϊ�
	VECTOR vecter_pos = wta::ConvertToVECTOR(m_pos);

	// �ړ���ݒ肷��
	MATRIX matrix_translation = MGetTranslate(vecter_pos);

	// ------------------------

	// �C�s��̍����i�X�P�[���A��]�A���s�ړ��j

	// MMult�֐� : ��̍s��̏�Z���s��
	MATRIX matrix_transform = MMult(matrix_scale, matrix_rotation);

	// �X�ɍs��̏�Z���s���iDXlib�ł͂R�ȏ�̏�Z�͂Ȃ����߁A�����Čv�Z�j
	// ��ʓI�ɂ͊g��k������]�����s�ړ��̏����ŏ�Z
	matrix_transform = MMult(matrix_transform, matrix_translation);

	return matrix_transform;
}