#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../library/tnl_sequence.h"
#include "../Character.h"


class Partner : public Character
{

public:

	enum class ePartnerType
	{
		green,
		black,
		pink
	};

	Partner();

	~Partner() {}


	//----------------------------------------//

private:

	// �s��̍X�V����
	void UpdateMatrix(float delta_time);

public:

	// ������
	void Initialize() override;
	// �X�V
	void Update(float delta_time) override;
	// �`�揈��
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};