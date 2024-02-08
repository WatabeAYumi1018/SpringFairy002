#pragma once
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "../library/tnl_intersect.h"


namespace wta
{
	template<class T1,class T2>
	// ����������s���֐��̌^�G�C���A�X
	// �G�C�A���X : �ʖ�
	// �Փˌ��o�֐��̌^�� Intersected �Ƃ��Ē�`
	// 2��T�^�I�u�W�F�N�g�̃|�C���^�������Ƃ���void�֐�
	// 2�̃I�u�W�F�N�g�̏Փ˔���𔻒肵�A�Փ˂����ꍇ�͂Ȃ�炩�̏��������s
	// std::function : �֐��I�u�W�F�N�g��\���N���X�e���v���[�g
	using Intersected 
		= std::function<void(std::shared_ptr<T1> a, std::shared_ptr<T2> b)>;

	//template<class T>
	//using IntersectedCheck =std::function<bool(T*, T*)>;

	template<class T1, class T2>
	// �L�[�͕�����A�l��Intersected�^�̊֐������n�b�V���}�b�v�̌^�G�C���A�X
	// �قȂ�I�u�W�F�N�g�y�A�ɑ΂��āA�قȂ�Փ˔���֐���o�^�ł���
	// �L�[ : �Փ˂���I�u�W�F�N�g�̃y�A�����ʂ��邽�߂̕�����
	// �l : �Փ˂������������Ɏ��s�����֐�(�R�[���o�b�N)
	// std::unordered_map : �n�b�V���e�[�u����p�����A�z�z��
	using Intersected_map = std::unordered_map<std::string, Intersected<T1,T2>>;

	template<class T1, class T2>
	class Collision
	{

	public:

		Collision() {}
		~Collision() {}

		// ��������̊֐��̃}�b�v
		Intersected_map<T1,T2> m_intersect_map;

		// ��������̊֐��̓o�^
		// arg1 : �o�^����֐��̃L�[(�Փ˂���I�u�W�F�N�g�̃y�A������)
		// arg2 : �Փ˂������������Ɏ��s�����֐�)(�R�[���o�b�N)
		// ex : registerIntersect("����", [](Player* p, Enemy* e){...});
		void registerIntersect( const std::string& key
								,const Intersected<T1,T2>& intersect)
		{
			// �w�肳�ꂽ�L�[�ɑ΂��Č�������֐����}�b�v�ɓo�^
			m_intersect_map[key] = intersect;
		}

		// 2�̌�������
		// arg1 : �Փ˔�����s���I�u�W�F�N�g(1��)
		// arg2 : �Փ˔�����s���I�u�W�F�N�g(2��)
		// ex : Intersect(player, enemy);
		void Intersect(std::shared_ptr<T1> a, std::shared_ptr<T2> b)
		{
			// �Փ˂���2�̃I�u�W�F�N�g�̌^�����ӂȃL�[�𐶐�
			// typeid : �^�����擾���邽�߂̉��Z�q
			// typeid(�^��).name() : �^���𕶎���Ŏ擾
			// std::string(typeid(�^��).name()) : �^���𕶎���ɕϊ�
			// std::string ... + std::string ... : 2�̕����������
			// 2�̃I�u�W�F�N�g�^�C�v�Ԃ̏Փ˔���֐��� m_intersect_map ���猟��
			std::string key
				= std::string(typeid(*a).name()) + std::string(typeid(*b).name());

			// ��������̊֐����o�^����Ă��Ȃ��ꍇ�͏������I��
			if (m_intersect_map.find(key) == m_intersect_map.end())
			{
				return;
			}
			// ��������̊֐������s
			// �I�u�W�F�N�g�ւ̃|�C���^a��b���󂯎��A��̓I�ȏ��������s
			m_intersect_map[key](a, b);
		}

		// �~���m��������(�ʓ��m�̔���)
		bool IsIntersectSphere( std::shared_ptr<T1> object1, float object1_radius
								, std::shared_ptr<T2> object2, float object2_radius,bool pos_up = false)
		{
			// null�`�F�b�N
			if (object1 == nullptr || object2 == nullptr)
			{
				return false;
			}

			tnl::Vector3 pos1 = object1->GetPos();

			tnl::Vector3 pos2 = object2->GetPos();

			if (pos_up)
			{
				pos2.y += 500;
			}

			// 2�̋������Z�o
			tnl::Vector3 distance = pos1 - pos2;
			// ��Βl���Z�o
			distance.abs();
			// 2�̔��a���Z�o
			float radius = object1_radius + object2_radius;

			// 2�̋��������a��菬�����ꍇ�͏Փ�
			if (distance.x < radius
				&& distance.y < radius
				&& distance.z < radius)
			{
				return true;
			}
			return false;
		}

		// �~���m�̕␳����(Object2���e�����)
		void CorrectSphere(std::shared_ptr<T1> object1, float object1_radius
							, std::shared_ptr<T2> object2, float object2_radius)
		{
			tnl::Vector3 pos1 = object1->GetPos();
			tnl::Vector3 pos2 = object2->GetPos();

			// 2�̃I�u�W�F�N�g�Ԃ̋����x�N�g�����v�Z
			tnl::Vector3 distance_vec = pos2 - pos1;
			// �����x�N�g���𐳋K�����ĕ����𓾂�
			distance_vec.normalize();
			// 2�̃I�u�W�F�N�g�Ԃ̋������Z�o
			float distance = distance_vec.length();

			// 2�̃I�u�W�F�N�g�̔��a�̍��v
			float total_radius = object1_radius + object2_radius;

			// �Փ˂��������Ă���ꍇ�A�ʒu��␳����
			if (distance < total_radius)
			{
				// �d�Ȃ�̗ʂ��v�Z
				float overlap = total_radius - distance;

				// �␳���邽�߂̈ړ��x�N�g�����v�Z�i�Е��܂��͗����̃I�u�W�F�N�g�𓮂����j
				tnl::Vector3 correct_vec = distance_vec * overlap;

				// �I�u�W�F�N�g�̈ʒu��␳
				object1->SetPos(pos1 - correct_vec * 0.03f);
				object2->SetPos(pos2 + correct_vec * 0.03f);
			}
		}

		// �~�ƒ����̂̌�������(�ʓ��m�̔���)
		// �����̂̑傫����䗦�͈قȂ邽�߁A�����Ŏw�肷��
		bool IsIntersectSphereAABB( std::shared_ptr<T1> object1
									, float object1_radius
									, std::shared_ptr<T2> object2
									, float object2_half_width
									, float object2_half_height
									,float object2_half_depth)
		{
			// null�`�F�b�N
			if (object1 == nullptr || object2 == nullptr)
			{
				return false;
			}

			tnl::Vector3 pos1 = object1->GetPos();
			tnl::Vector3 pos2 = object2->GetPos();

			tnl::Vector3 object2_half_size 
				= tnl::Vector3(object2_half_width, object2_half_height, object2_half_depth);

			// AABB�̍ŏ��l�ƍő�l���Z�o
			tnl::Vector3 aabb_min = pos2 - object2_half_size;
			tnl::Vector3 aabb_max = pos2 + object2_half_size;

			// ���̒��S��AABB�̍ł��߂��_�Ƃ̍ŒZ�������Z�o
			float distance = 0;

			// object1��AABB�̊O���ɂ��邩����
			if (pos1.x < aabb_min.x)
			{
				// �I�u�W�F�N�g�Ԃ̋������Z�o
				distance += (aabb_min.x - pos1.x) * (aabb_min.x - pos1.x);
			}
			if (pos1.x > aabb_max.x) 
			{
				distance += (pos1.x - aabb_max.x) * (pos1.x - aabb_max.x);
			}

			// Y���Ɋւ���v�Z
			if (pos1.y < aabb_min.y)
			{
				distance += (aabb_min.y - pos1.y) * (aabb_min.y - pos1.y);
			}
			if (pos1.y > aabb_max.y) 
			{
				distance += (pos1.y - aabb_max.y) * (pos1.y - aabb_max.y);
			}

			// Z���Ɋւ���v�Z
			if (pos1.z < aabb_min.z)
			{
				distance += (aabb_min.z - pos1.z) * (aabb_min.z - pos1.z);
			}
			if (pos1.z > aabb_max.z) 
			{
				distance += (pos1.z - aabb_max.z) * (pos1.z - aabb_max.z);
			}

			// �ŒZ���������a��菬�����ꍇ�͏Փ�
			return distance < object1_radius * object1_radius;
		}

		//// ��������(�̂ƃO���[�v�̔���)
		//// �x�N�^�[���̃I�u�W�F�N�g�̒��ł����ꂩ�����肳�ꂽ�瑼���S�ĕς��
		//bool IsIntersectAllSpheres( std::shared_ptr<T1> object1
		//							, std::vector<std::shared_ptr<T2>>& objects2)
		//{
		//	// null�`�F�b�N
		//	if (object1 == nullptr)
		//	{
		//		return false;
		//	}

		//	tnl::Vector3 pos1 = object1->GetPos();
		//	float size1 = object1->GetCollisionSize();

		//	for (std::shared_ptr<T2> object2 : objects2)
		//	{
		//		tnl::Vector3 pos2 = object2->GetPos();
		//		float size2 = object2->GetCollisionSize();

		//		// 2�̋������Z�o
		//		tnl::Vector3 distance = pos1 - pos2;
		//		// ��Βl���Z�o
		//		distance.abs();
		//		// 2�̔��a���Z�o
		//		float radius = size1 + size2;

		//		// 2�̋��������a��菬�����ꍇ�͏Փ�
		//		if (distance.x < radius
		//			&& distance.y < radius
		//			&& distance.z < radius)
		//		{
		//			return true;
		//		}
		//	}
		//	return false;
		//}
	};
}

/* 
�@std::function : �قȂ���̊֐��𓯈�̌^�Ƃ��Ĉ�����

�錾) std::function<R(args...)> : R�͖߂�l�̌^�Aargs... �͈����̌^

��) std::function<int(int)> : ������int�^��int�^�֐�

�ʏ�̊֐� : int doublenumber(int x) {return x * 2;}
�����_�� : auto doubleNumber = [](int x) {return x * 2;}
�֐��I�u�W�F�N�g : struct DN {int operator()(int x) {return x * 2;}}DoubleNumber;

std::function<int(int)> f1 = doublenumber;
std::function<int(int)> f2 = doubleNumber;
std::function<int(int)> f3 = DoubleNumber;

f1(2); // 4
f2(2); // 4
f3(2); // 4

std::function<int(int)> f4 = f1;
f4(2); // 4

�قȂ�^�̊֐��𓯈�̌^�Ƃ��ē����悤�Ɉ�����

----------------------------------------------

�Astd::unordered_map : �n�b�V���e�[�u����p�����A�z�z��

�A�z�z�� : �L�[���g�p���ăf�[�^(�l)��v���Ɍ����A�}���A�폜�ł���
�L�[�Ɋ�Â��ăf�[�^��v���ɃA�N�Z�X����K�v������ꍇ�ɓ��ɗL�p

�錾) std::unordered_map<key, value> : key�̓L�[�̌^�Avalue�͒l�̌^

��) std::unordered_map<std::string, int> : �L�[��������A�l��int�^�̘A�z�z��

*/

//void CheckCollision(T* object1
//					, std::vector<T*>& objects
//					, const IntersectedCheck<T>& intersect_check)
//{
//	for (T* object2 : objects)
//	{
//		// ��������֐������s
//		if (intersect_check(object1, object2))
//		{
//			// �Փ˂����ꍇ�́A�Փ˔���֐������s
//			Intersect(object1, object2);
//		}
//	}
//
//}

