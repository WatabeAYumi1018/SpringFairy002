#pragma once
#include "ChangeGraph.h"


///////////////////////////////////////////////////////////////////////////
//
// �J�����J�ڂ���ۂ̃C���X�g�̒�`�ƍX�V�`�揈�����s���N���X
// ���J�ڂ����R�ɂ��邽�߂ɁA�{�N���X�̓Q�[���J�����݂̂Ŏg�p
// �@�ӂ��̃N���X�𓯎��Ɏg�p���邱�ƂŁA�J�ڎ��̃C���X�g�����R�ɕ\������
//�@
///////////////////////////////////////////////////////////////////////////


class ChildChangeGraph : public ChangeGraph
{

public:

	ChildChangeGraph();

	~ChildChangeGraph();

private:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};
