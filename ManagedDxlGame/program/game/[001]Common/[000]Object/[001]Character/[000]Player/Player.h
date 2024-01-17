#pragma once
#include "../Character.h"


class Player : public Character
{

public:

	Player();

	~Player();


	//----------------------------------------//

private:

	// �s��̍X�V����
	void UpdateMatrix(float delta_time);

	tnl::Vector3 Forward();

public:

	// ������
	void Initialize() override;
	// �X�V
	void Update(float delta_time) override;
	// �`�揈��
	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	tnl::Vector3 Back();
};