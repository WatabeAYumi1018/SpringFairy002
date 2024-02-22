#pragma once
#include "../../../../../library/tnl_sequence.h"
#include "../Character.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �p�[�g�i�[�L�����N�^�[�̍X�V�`����s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Partner : public Character
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Partner();
	~Partner();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�֐�------------------------------------//

	// �s��̍X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateMatrix(const float delta_time);

public:

	void Initialize() override;
	
	void Update(const float delta_time) override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//
};