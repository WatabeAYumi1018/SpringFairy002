//#pragma once
//#include "../../../../wta_library/wta_Collision.h"
//#include "../dxlib_ext/dxlib_ext.h"
//
//class Mediator;
//
////class Player;
////class Camera;
//
//
//class CameraFrustum
//{
//
//public:
//
//	// �t���X�^���J�����O�̃p�����[�^
//	struct sFrustumParam
//	{
//		// ���ʂ̖@���x�N�g��
//		// 3D��ԓ��̊e���ʂɐ����ȃx�N�g��
//		// �t���X�^���J�����O�ł́A�J�����̃r���[�t���X�^�����\������e���ʂɑ΂��āA
//		// ���̕��ʂɐ����ȕ������w���x�N�g�����v�Z
//		// s_normal : �Y������t���X�^�����ʂɐ����ȕ���������3�����x�N�g��
//		tnl::Vector3 s_normal;
//		// ���ʕ������̒萔��
//		// ���_���畽�ʂ܂ł̋����������l
//		float s_d;
//	};
//
//
//	CameraFrustum() {}
//	
//	~CameraFrustum() {}
//
//private:
//
//	int m_frustum_plane_num = 4;
//
//	tnl::Vector3 m_pos;
//
//	tnl::Matrix m_view;
//
//	tnl::Matrix m_proj;
//
//	// �t���X�^����4���ʂ̃p�����[�^
//	sFrustumParam m_frustum_param[4];
//
//
//	//std::shared_ptr<Player> m_player = nullptr;
//
//	//std::shared_ptr<GameCamera> m_gameCamera = nullptr;
//
//	//std::shared_ptr<wta::Collision<Player, GameCamera>> m_collision = nullptr;
//
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//
//	// ���E���ʂ̍X�V
//	void UpdateFrustumPlane();
//	// �t���X�^���J�����O�̋��E������
//	bool IsInFrustum(const tnl::Vector3& pos);
//	// �v���C���[�̍��W���t���X�^�����ɖ߂�
//	void ReturnPlayerPos(const tnl::Vector3& player_pos);
//
//	//// �t���X�^���J�����O�̃R�[�i�[�v�Z
//	//std::vector<tnl::Vector3> CalculateFrustumCorners(const tnl::Matrix& invViewProj);
//	//// �t���X�^���J�����O��6���ʕ`��
//	//void DrawFrustumPlane();
//
//	//// �t���X�^���J�����O��6���ʂ̃p�����[�^���擾
//	//sFrustumParam GetFrustumParam(int index)
//	//{
//	//	return m_frustum_param[index];
//	//}
//
//	//void DrawFrustumPlane(const tnl::Vector3& normal, float d) ;
//
//public:
//
//	void Update();
//
//	//// �����蔻�菈���̓o�^
//	//void CollisionRegister();
//	//// �L�����Ƃ̓����蔻��
//	//void CollisionCheck();
//
//	// �t���X�^���J�����O��6���ʂ̃p�����[�^���擾
//	sFrustumParam GetFrustumParam(int index)
//	{
//		return m_frustum_param[index];
//	}
//
//	//void SetGameCamera(std::shared_ptr<GameCamera> gameCamera)
//	//{
//	//	m_gameCamera = gameCamera;
//	//}
//
//	//void SetPlayer(std::shared_ptr<Player> player)
//	//{
//	//	m_player = player;
//	//}
//
//	//void SetCollision(std::shared_ptr<wta::Collision<Player, GameCamera>> collision)
//	//{
//	//	m_collision = collision;
//	//}
//
//	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//};