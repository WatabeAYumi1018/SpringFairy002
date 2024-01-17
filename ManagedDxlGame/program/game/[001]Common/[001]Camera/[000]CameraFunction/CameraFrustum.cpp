//#include "../../[002]Mediator/Mediator.h"
//#include "CameraFrustum.h"
//
//
//
//void CameraFrustum::Update()
//{
//	m_pos = m_mediator->GetCameraPos();
//
//	m_view = m_mediator->GetCameraView();
//
//	m_proj = m_mediator->GetCameraProj();
//
//	UpdateFrustumPlane();
//
//	ReturnPlayerPos(m_mediator->GetPlayerPos());
//
//	// ���W�f�o�b�O�p
//	DrawStringEx(1000, 500, -1, "CameraFrustumPos_x:%f", m_pos.x);
//	DrawStringEx(1000, 520, -1, "CameraFrustumPos_y:%f", m_pos.y);
//	DrawStringEx(1000, 540, -1, "CameraFrustumPos_z:%f", m_pos.z);
//}
//
//// �t���X�^���̊e���ʂ̖@���x�N�g�����v�Z���A
//// �萔���ł��̕��ʂ̈ʒu����肷�邱�Ƃɂ��A�t���X�^���̋��E���`
//void CameraFrustum::UpdateFrustumPlane()
//{
//	// �r���[�s��Ǝˉe�s�������
//	// �I�u�W�F�N�g�̐��E���W�n����2D��ʋ�Ԃւ̒��ړI�ȕϊ�
//	tnl::Matrix view_proj = m_view * m_proj ;
//
//	// ���s��̏�Z : ���W�ϊ��i��]�A�g��k���A���s�ړ��j
//	// ���s��̉��Z : ���W�ϊ��̍����i�����̍��W�ϊ�����x�ɍs���A�V�����x�N�g�������j
//
//	// ������
//	// �����ʂ̖@���x�N�g��(���ʂɑ΂��鐂���x�N�g��)���Z�o
//	// view_proj._11 �` view_proj._31 : �����s���1�s�ځi�J������Ԃɂ�����E�����x�N�g���j
//	// view_proj._12 �` view_proj._32 : �����s���2�s�ځi�J������Ԃɂ����������x�N�g���j
//	// view_proj._13 �` view_proj._33 : �����s���3�s�ځi�J������Ԃɂ�����O�����x�N�g���j
//	// view_proj._14 �` view_proj._34 : �����s���4�s�ځi�J������Ԃ̌��_����̕ϊ��x�N�g���j
//	// ���Z���邱�Ƃō����ʂ̖@���x�N�g�����Z�o�i�t���X�^���̍����ʂƑ��̕����Ƃ̋��E�j
//
//	float d = view_proj._44 + view_proj._14;
//	float a = ( view_proj._41 + view_proj._11 ) ;
//	float b = ( view_proj._42 + view_proj._12 ) ;
//	float c = ( view_proj._43 + view_proj._13 ) ;
//
//	m_frustum_param[0].s_normal = tnl::Vector3(view_proj._41 + view_proj._11,
//												view_proj._42 + view_proj._12,
//												view_proj._43 + view_proj._13);
//
//	//m_frustum_param[0].s_normal = m_mediator->GetCameraRight();
//
//	// �t���X�^�����ʍ����ʂ̕������ɂ�����萔�����Z�o
//	// ������ : Ax+By+Cz+D=0 (A,B,C : �@���x�N�g���̐��� �E�@D : �萔��)
//	// ���ʂ� 0 ���傫���ꍇ: �_�͕��ʂ̈���̑��i�ʏ�́u�����v�j
//	// ���ʂ� 0 ��菬�����ꍇ: �_�͕��ʂ̑����̑��i�ʏ�́u�O���v�j
//	// ���ʂ� 0 �̏ꍇ: �_�͕��ʏ�
//	// _44 : Z���ɉ������[�x�i���s���j�̏����X�P�[��
//	// _41 : X���ɉ����������̈ʒu�����X�P�[��
//	// ���Z���邱�Ƃō����ʂ�3D��ԓ��łǂ̂悤�Ɉʒu���邩�����i�J�������猩�Ăǂꂾ���������j
//	m_frustum_param[0].s_d = view_proj._44 + view_proj._14;
//
//	// �E����
//	m_frustum_param[1].s_normal = tnl::Vector3(view_proj._41 - view_proj._11,
//												view_proj._42 - view_proj._12,
//												view_proj._43 - view_proj._13);
//
////	m_frustum_param[1].s_normal = m_mediator->GetCameraLeft();
//
//	m_frustum_param[1].s_d = view_proj._44 - view_proj._14;
//
//	//// �㕽��
//	m_frustum_param[2].s_normal = tnl::Vector3(view_proj._41 - view_proj._21,
//												view_proj._42 - view_proj._22,
//												view_proj._43 - view_proj._23);
//
//	//m_frustum_param[1].s_normal = m_mediator->GetCameraBack();
//
//
//	m_frustum_param[2].s_d = view_proj._44 - view_proj._24;
//
//	//// ������
//	m_frustum_param[3].s_normal = tnl::Vector3(view_proj._41 + view_proj._21,
//												view_proj._42 + view_proj._22,
//												view_proj._43 + view_proj._23);
//
////	m_frustum_param[3].s_normal = m_mediator->GetCameraForward();
//
//	m_frustum_param[3].s_d = view_proj._44 + view_proj._24;
//
//	// �e���ʂ̖@���x�N�g���𐳋K��
//	// �@���x�N�g���̒��������i�ʏ��1�j�ł��邱�Ƃ�ۏ؂��邱�ƂŁA
//	// �t���X�^���̕��ʂƃI�u�W�F�N�g�Ƃ̋����v�Z����т������̂ɂȂ�
//	// �_�ƕ��ʂƂ̋����́A�_�̈ʒu�x�N�g���Ɩ@���x�N�g���̓���
//	// �����Ē萔�������Z���邾���ŎZ�o�ł���
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		m_frustum_param[i].s_normal.normalize();
//	}
//}
//
//bool CameraFrustum::IsInFrustum(const tnl::Vector3& pos)
//{
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		// ���ς��v�Z���A�萔�������Z
//		// �_�ƕ��ʂƂ̋������Z�o
//		// �_�ƕ��ʂƂ̋�����0��菬�����ꍇ�A�_�͕��ʂ̊O���ɂ���
//		float dot = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos);
//
//		dot += m_frustum_param[i].s_d;
//
//		if (dot < 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void CameraFrustum::ReturnPlayerPos(const tnl::Vector3& player_pos)
//{
//	// �t���X�^�����E�O�Ƀv���C���[�̍��W���ړ������ꍇ
//	if (!IsInFrustum(player_pos))
//	{
//		DrawStringEx(1000, 700, -1, "�O��");
//
//		// �t���X�^���̊e�ʂƃv���C���[�̋������i�[����z��
//		float distance[4];
//
//		int min_index = -1;
//
//		float min_distance = 1e38f;
//
//		// �t���X�^���̊e�ʂƃv���C���[�̋������v�Z
//		for (int i = 0; i < m_frustum_plane_num; i++)
//		{
//			distance[i] = tnl::Vector3::Dot(m_frustum_param[i].s_normal, player_pos)
//				+ m_frustum_param[i].s_d;
//
//			// ���������ł���A�ł����������̂�������
//			if (distance[i] > 0 && distance[i] < min_distance) 
//			{
//				min_distance = distance[i];
//				min_index = i;
//			}
//		}
//		//// ��ԋ߂��t���X�^���̖ʂɃv���C���[��߂�
//		//  // �t���X�^���̋��E�ɍł��߂����ʂ�������
//		//int min_index
//		//	= std::min_element(distance, distance + m_frustum_plane_num) - distance;
//
//		if (min_index != -1)
//		{
//			tnl::Vector3 return_pos 
//				= player_pos - m_frustum_param[min_index].s_normal * min_distance;
//			m_mediator->SetPlayerPos(return_pos);
//		}
//	}
//}
//
//
////// �ߕ���
////// �ߕ��ʂ̓J�����̖@���x�N�g���͑O�����x�N�g���ƕ��s
////m_frustum_param[4].s_normal = tnl::Vector3(view_proj._13,
////	view_proj._23,
////	view_proj._33);
////m_frustum_param[4].s_d = view_proj._44 + view_proj._43;
//
////// ������
////m_frustum_param[5].s_normal = tnl::Vector3(view_proj._14 - view_proj._13,
////	view_proj._24 - view_proj._23,
////	view_proj._34 - view_proj._33);
////m_frustum_param[5].s_d = view_proj._44 - view_proj._43;
//
////void CameraFrustum::CollisionRegister()
////{
////	std::string key
////		= typeid(Player).name() + std::string(typeid(GameCamera).name());
////
////	m_collision->registerIntersect( key
////									, [this](std::shared_ptr<Player> player
////									, std::shared_ptr<GameCamera> gameCamera)
////	{
////		for (int i = 0; i < m_frustum_plane_num; ++i)
////		{
////			// �t���X�^���̖ʂ��擾
////			sFrustumParam frustum_plane = m_frustum_param[i];
////			// �t���X�^���̔����̃T�C�Y���擾
////			float frustum_half_size_height = gameCamera->screen_h_ / 2;
////			float frustum_half_size_width = gameCamera->screen_w_ / 2;
////
////			if (m_collision->IsIntersectSphereAABB( player, player->GetCollisionSize()
////													, gameCamera, frustum_half_size_width
////													, frustum_half_size_height,0))
////			{
////
////				DrawStringEx(1000, 500, -1, "�O��");
////			}
////		}
////	});
////}
////
////void CameraFrustum::CollisionCheck()
////{
////	m_collision->Intersect(m_player,m_gameCamera);
////
////	// ���W�f�o�b�O�p
////	DrawStringEx(0, 100, -1, "CameraFrustum_x:%f", pos_.x);
////	DrawStringEx(0, 120, -1, "CameraFrustum_y:%f", pos_.y);
////	DrawStringEx(0, 140, -1, "CameraFrustum_z:%f", pos_.z);
////}
//
////// ���̂̒��S���W�Ɣ��a���`
////Vector3 sphereCenter = // ���̂̒��S���W
////float sphereRadius = // ���̂̔��a
////
////// �e�t���X�^���ʂɑ΂��ċ������v�Z���A�����蔻����`�F�b�N
////for (int i = 0; i < NUM_FRUSTUM_PLANES; i++) {
////	float distance = abs(Vector3::Dot(frustumPlanes[i].normal, sphereCenter) + frustumPlanes[i].d);
////	if (distance < sphereRadius) {
////		// �����蔻�肪����
////		Vector3 correction = frustumPlanes[i].normal * (sphereRadius - distance);
////		sphereCenter += correction;
////		// �␳��̍��W���g�p
////	}
////}