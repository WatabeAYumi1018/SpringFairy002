#pragma once
#include "../../../[000]Object/Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ���̃v���[���̒�`�A�ǂݎ�肩��`�揈���Ɋւ���N���X
// ��Load�N���X�ɕ�����܂ł��Ȃ����߁A�{�N���X����csv���[�h���s��
//
/////////////////////////////////////////////////////////////////////////////////////////


class Floor : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// ���̎��
	struct sFloorType
	{
		int s_id;
		std::string s_graph_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Floor();
	~Floor();

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���̂����W�I�t�Z�b�g
	static const int DRAW_OFFSET = -400;

private:

	// �X�e�[�W���f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_floor_info;
	// �X�e�[�W���f���̏��i�[�p
	std::vector<sFloorType> m_floor_info;

	// ���b�V���̃|�C���^
	std::shared_ptr<dxe::Mesh> m_floor = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Floor, &Floor::SeqFlower);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���̏��ǂݎ��
	void LoadFloorTypeInfo();
	// ���̕`��
	void DrawFloor(std::shared_ptr<dxe::Camera> camera);

	// �t�����[�G���A
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFlower(const float delta_time);
	// �E�b�h�G���A
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqWood(const float delta_time);
	// �t�@���V�[�G���A
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFancy(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
