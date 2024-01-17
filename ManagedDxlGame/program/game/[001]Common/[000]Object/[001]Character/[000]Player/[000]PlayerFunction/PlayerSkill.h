#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GamEngine/[000]Engine/Engine.h"

class Mediator;

class PlayerSkill
{

public:

	enum class ePlayerSkill
	{
		// �\�͖���
		e_normal,
		// �򉻔\��
		e_bouquet,
		// �����̕��i�{�X��p�j
		e_dance,
	};

private:

	ePlayerSkill m_now_player_skill = ePlayerSkill::e_normal;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerSkill, &PlayerSkill::SeqNormal);

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// �m�[�}��
	bool SeqNormal(const float delta_time);
	// �򉻔\��
	bool SeqBouquet(const float delta_time);
	// �����̕�
	bool SeqDance(const float delta_time);

public:

	void Update(float delta_time);

	ePlayerSkill GetNowPlayerSkill() { return m_now_player_skill; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}	
};