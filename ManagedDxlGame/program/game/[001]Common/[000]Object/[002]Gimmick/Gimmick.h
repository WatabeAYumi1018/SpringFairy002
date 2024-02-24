#pragma once
#include "../../[000]Object/Object.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �M�~�b�N�̒�`�ƍX�V�`�揈�����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class Gimmick : public Object
{

public:

	//-----------------------------------enum class------------------------------------//

	// �M�~�b�N�̎��
	enum class eGimmickType
	{
		e_ground_flower,
		e_wood,
		e_sky_flower,
		e_butterfly,
		e_max
	};

	//---------------------------------------------------------------------------------//


	//-------------------------------------�\����--------------------------------------//

	// Factory�Ő��������e���f����hdl��Ή������邽��string�^�Ńp�X���i�[
	struct sGimmickTypeInfo
	{
		int s_id = 0;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		std::string s_model_path;
		std::string s_texture_a_path;
		std::string s_texture_b_path;
		eGimmickType s_type;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Gimmick();
	~Gimmick();

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�------------------------------------//

	// �M�~�b�N�̓����蔻��̔��a�i�G���A�P�ƃG���A�R�̑��ԁj
	static const int GIMMICK_SIZE_FLOWER = 250;
	// �M�~�b�N�̓����蔻��̔��a(�G���A�Q�̎���)
	static const int GIMMICK_SIZE_WOOD = 500;

private:

	// �G�~�b�V�u�̒l
	float m_emissive_value = 0.0f;

	// �ʂ̃A�N�e�B�u���
	bool m_is_active = false;
	// �����蔻������B�̍��}
	bool m_is_hit = false;
	// �Փ˔���
	bool m_is_collision = false;
	// �ʂ̕`���ԕω�
	bool m_is_draw_change = false;

	//���Ȕ���
	DxLib::COLOR_F m_emissive = { 0.3f,0.3f,0.3f,1 };

	// csv����ǂݎ�������f���̏��
	sGimmickTypeInfo m_gimmick_data;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Gimmick, &Gimmick::SeqNormal);

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �A�C�e���t�����[�̗�������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveFlower(const float delta_time);

	// �������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqNormal(const float delta_time);

	// �����蔻��˒����̃��C�g�A�b�v
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqHit(const float delta_time);

	// �Փ˂ɂ�郉�C�g�A�b�v�J�n
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqLightUp(const float delta_time);

	// ���C�g�A�b�v�I���ƃe�N�X�`���ύX
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqLightDown(const float delta_time);

	// �ω�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqChangeEnd(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// ���f���̏��ǂݍ���(Factory�N���X�ɂĐݒ�)
	// arg ... �M�~�b�N�̎��
	void LoadGimmickData(const Gimmick::sGimmickTypeInfo& gimmick_info);

	// ���f���̏������i��A�N�e�B�u���j
	void Reset();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �M�~�b�N�̊������t���O��ݒ�
	void SetIsActive(bool is_active) { m_is_active = is_active; }

	// �M�~�b�N�̊������t���O���擾
	bool GetIsActive() const { return m_is_active; }

	// �Փ˔���̍��}��ݒ�
	void SetIsHit(bool is_hit) { m_is_hit = is_hit; }

	// �Փ˔���̍��}���擾
	bool GetIsHit() const { return m_is_hit; }

	// �Փ˂̃t���O��ݒ�
	void SetIsCollision(bool is_collision) { m_is_collision = is_collision; }

	// �Փ˂̃t���O���擾
	bool GetIsCollision() const { return m_is_collision; }

	// �`���ԕω��̃t���O��ݒ�
	void SetIsDrawChange(bool is_draw_change) { m_is_draw_change = is_draw_change; }

	// �`���ԕω��̃t���O���擾
	bool GetIsDrawChange() const { return m_is_draw_change; }

	// �M�~�b�N�̎�ނ�ݒ�
	void SetGimmickData(sGimmickTypeInfo gimmick_info) 
	{
		m_gimmick_data =  gimmick_info;
	}

	// ���f�B�G�[�^�̃|�C���^��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};