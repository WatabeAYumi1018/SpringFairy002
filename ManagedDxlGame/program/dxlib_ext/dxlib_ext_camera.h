#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace dxe {

	class Camera {
	public :

		Camera(){}
		Camera(int screen_w, int screen_h)
		{
			screen_w_ = screen_w;
			screen_h_ = screen_h;
			aspect_ = (float)screen_w_ / (float)screen_h_;
		}
		virtual ~Camera() {}

		int screen_w_ = 0 ;

		int screen_h_ = 0 ;

		// �J�����̂R�������W
		tnl::Vector3 pos_ = { 0,0,-500 };
		// �J�������R�����̂ǂ�����ʂ̒����ɂƂ炦�Ă��邩
		tnl::Vector3 target_ = tnl::Vector3(0, 0, 0);
		// �J�����́w��x���`����A�b�p�[�x�N�g��
		tnl::Vector3 up_ = tnl::Vector3(0, 1, 0);

		// �J�����̉�p ( �x )
		float angle_ = tnl::ToRadian(60.0f);
		// �J�����̃A�X�y�N�g�� ( �c���� )
		float aspect_ = 1.0f;
		// �J�����ɉf��͈͂̍ŋߋ���
		float near_ = 100.0f;
		// �J�����ɉf��͈͂̍ŉ�����
		float far_ = 50000.0f;

		// �J�����̃r���[�s�� : �J�����̈ʒu�ƌ�����\���s��
		// �V�[�����̃I�u�W�F�N�g���J�����̎��_���猩���ʒu�ɕϊ�����s��
		// ���E���W�n����r���[���W�n�i�J�������W�n�j�ւ̕ϊ�
		tnl::Matrix view_;
		// �J�����̎ˉe�s�� : �J�����̎���͈͂�\���s��
		// �I�u�W�F�N�g��3D��Ԃ���2D��ʋ�Ԃɓ��e
		// �I�u�W�F�N�g���J�����̃r���[�|�[�g�i�\���̈�j�Ƀt�B�b�g�����邽�߂̉��ߊ��𐶐�
		tnl::Matrix proj_;

		// �J�����̑O����
		virtual inline tnl::Vector3 forward()
		{
			return tnl::Vector3::Normalize(target_ - pos_);
		}
		// ������
		virtual inline tnl::Vector3 left()
		{
			// �O�Ə�(Y���A{0, 1, 0})�̊O�ςŎZ�o
			return tnl::Vector3::Cross(forward(), { 0, 1, 0 });
		}
		// �E����
		virtual inline tnl::Vector3 right()
		{
			// ��(Y���A{0, 1, 0})�ƑO�̊O�ςŎZ�o
			return tnl::Vector3::Cross({ 0, 1, 0 }, forward());
		}
		// ������
		virtual inline tnl::Vector3 back()
		{
			return tnl::Vector3::Normalize(pos_ - target_);
		}

		//----------------------------------------------------------------------------------------------
		// work... �����䕽�ʂ̖@�����擾����
		// arg1... 6�̕��ʂ̂ǂꂩ
		// ret.... �����䕽�ʂ̖@��
		// tips... none
		enum class eFlustum { Left, Right, Bottom, Top, Near, Far, Max };
		tnl::Vector3 getFlustumNormal(eFlustum flusum);




		virtual void update(float delta_time)
		{
			view_ = tnl::Matrix::LookAtLH(pos_, target_, up_);
			proj_ = tnl::Matrix::PerspectiveFovLH(angle_, aspect_, near_, far_);
		}

		void render(float scale, uint32_t color = 0xffffff00);


		const tnl::Vector3& GetPos() const { return pos_; }

		const tnl::Matrix& GetView() const { return view_; }

		const tnl::Matrix& GetProj() const { return proj_; }
	};

}
