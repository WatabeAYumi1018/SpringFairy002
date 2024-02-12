#pragma once
#include "../Object.h"


class Mediator;


class Gate : public Object
{

public:

	struct sGateInfo
	{
		int s_id;
		std::string s_texture_path;
	};

	Gate();

	~Gate() {}

private:


	// �Q�[�g�̓����J�n�t���O
	bool m_is_active = false;
	// �Q�[�g���J�����t���O
	bool m_is_opend = false;

	// �Q�[�g�f�[�^���i�[
	std::vector<sGateInfo> m_gates_info;

	std::vector<std::shared_ptr<dxe::Mesh>> m_meshes;


	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Gate, &Gate::SeqTrigger);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���b�V���̐���
	void CreateMesh();
	// ���b�V���̔z�u�w��
	void SetMeshMatrix();

	// �g���K�[����
	bool SeqTrigger(const float delta_time);
	// �C���X�g�̕ύX����
	bool SeqDrawChange(const float delta_time);
	// �Q�[�g�I�[�v������
	bool SeqOpen(const float delta_time);


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
