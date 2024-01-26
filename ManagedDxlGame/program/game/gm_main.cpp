#pragma once
//
////-----------------------------------------------------------------------------------------------------------
////
////
//// �p�[�e�B�N�����p�T���v��
////
//// ���@���̃T���v���̓p�[�e�B�N���G�f�B�^�Ƃ��Ă��@�\���܂�
////
//// ���@[ �d�v ]�@std::shared_ptr �Ŋm�ۂ��� dxe::Particle �͕K�� gameEnd() ��
//// �@�@�^�C�~���O�܂łɎQ�ƃJ�E���^�� 0 �ɂȂ�悤���Z�b�g���Ă������� ( gameEnd �֐����Q�� )
////
//// ���@[ �d�v ]�@���̋@�\�� DxLib �̋@�\�ł͂���܂���
//// �@�@dxe::Particle �� dxe::InstMeshPool �Ȃ� DirectX �𒼐ڐ��䂷��N���X�� render �֐���
////�@�@ dxe::DirectXRenderBegin() dxe::DirectXRenderEnd() �ň͂������ŃR�[�����Ă�������  
////-----------------------------------------------------------------------------------------------------------
//
//
//
//#include <time.h>
//#include <string>
//#include <numbers>
//#include <functional>
//#include "../dxlib_ext/dxlib_ext.h"
//#include "gm_main.h"
//
//
////-------------------------------------------------------------------------------------------------------
////
//// ���W�Ǝp���Ő��䂷��J����
////
//class TransformCamera : public dxe::Camera {
//public:
//
//    TransformCamera() {};
//    TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}
//
//    void update(const float delta_time) override;
//
//
//    inline tnl::Vector3 up() {
//        up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//        return up_;
//    }
//    inline tnl::Vector3 down() { return -up(); }
//
//    inline tnl::Vector3 forward() override {
//        target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//        return tnl::Vector3::Normalize(target_ - pos_);
//    }
//    inline tnl::Vector3 back() override { return -forward(); }
//    inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
//    inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }
//
//    tnl::Quaternion rot_;
//
//};
//
//void TransformCamera::update(const float delta_time) {
//
//    //
//    // �p���p�����[�^����^�[�Q�b�g���W�ƃA�b�p�[�x�N�g�����v�Z
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update(delta_time);
//}
//
//
//
//Shared<TransformCamera> camera = nullptr;
//std::shared_ptr<dxe::Particle> ptcl = nullptr;
//bool is_draw_controller = true;
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//
//    srand(time(0));
//    SetBackgroundColor(32, 32, 32);
//
//    camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    camera->pos_ = { 0, 100, -250 };
//
//    ptcl = std::make_shared<dxe::Particle>("particle/preset/default.bin");
//
//}
//
//
////------------------------------------------------------------------------------------------------------------
//// ���t���[�����s����܂�
//void gameMain(float delta_time) {
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // �J��������
//    //
//    tnl::Input::RunIndexKeyDown(
//        [&](uint32_t index) {
//            tnl::Vector3 v[4] = {
//                camera->left(),
//                camera->right(),
//                tnl::Vector3::up,
//                tnl::Vector3::down
//            };
//            camera->pos_ += v[index] * 3.0f;
//
//        }, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);
//
//    if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT)) {
//        tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
//        camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
//        camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
//    }
//    camera->pos_ += camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;
//
//
//    // GUI �`�� ON / OFF
//    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F3)) is_draw_controller = !is_draw_controller;
//
//    // �J�����A�b�v�f�[�g
//    camera->update(delta_time);
//
//
//
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // �`�揈��
//    //
//
//    DrawGridGround(camera);
//
//
//    //---------------------------------------------------------------------------
//    //
//    // �p�[�e�B�N���̕`��J�n
//    //
//    dxe::DirectXRenderBegin();
//
//    // �p�[�e�B�N�� A ��`��
//    ptcl->render(camera);
//
//    // �p�[�e�B�N�� B ��`��
//    // �p�[�e�B�N�� C ��...
//
//    //---------------------------------------------------------------------------
//    //
//    // �p�[�e�B�N���̕`��I��
//    //
//    dxe::DirectXRenderEnd();
//
//
//
//
//    if (is_draw_controller) ptcl->drawGuiController({ 0, 0 });
//
//    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);
//
//    DrawString(DXE_WINDOW_WIDTH - 260, 20, "�E�N���b�N : ����", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 40, "�z�C�[�� : �O��", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 60, "A D : ���E�ړ�", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 80, "W S : �㉺�ړ�", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 100, "F3 : GUI �`�� ON/OFF", -1);
//
//}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
//void gameEnd() {
//    ptcl.reset();
//}

////-------------------------------------------------------------------------------------------------------
//
//// ���W�Ǝp���Ő��䂷��J����
//
//class TransformCamera : public dxe::Camera {
//public:
//
//    TransformCamera() {};
//    TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}
//
//    void update(const float delta_time) override;
//
//
//    inline tnl::Vector3 up()
//    {
//        up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//        return up_;
//    }
//    inline tnl::Vector3 down() { return -up(); }
//
//    //inline tnl::Vector3 forward() override {
//    //    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    //    return tnl::Vector3::Normalize(target_ - pos_);
//    //}
//    //inline tnl::Vector3 back() override { return -forward(); }
//    //inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
//    //inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }
//
//    tnl::Quaternion rot_;
//
//};
//
//void TransformCamera::update(const float delta_time) {
//
//    //
//    // �p���p�����[�^����^�[�Q�b�g���W�ƃA�b�p�[�x�N�g�����v�Z
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update(delta_time);
//}
//
//
//
//Shared<TransformCamera> camera = nullptr;
//Shared<dxe::Mesh> mesh = nullptr;
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//
//    srand(time(0));
//    SetBackgroundColor(32, 32, 32);
//
//    camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    mesh = dxe::Mesh::CreateSphereMV(50);
//    camera->pos_ = { 0, 100, -250 };
//}
//
//
////------------------------------------------------------------------------------------------------------------
//// ���t���[�����s����܂�
//void gameMain(float delta_time) {
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // �J��������
//    //
//    tnl::Input::RunIndexKeyDown(
//        [&](uint32_t index) {
//            tnl::Vector3 v[4] = {
//                camera->left(),
//                camera->right(),
//                tnl::Vector3::up,
//                tnl::Vector3::down
//            };
//            camera->pos_ += v[index] * 3.0f;
//
//        }, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);
//
//    if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT)) {
//        tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
//        camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
//        camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
//    }
//    camera->pos_ += camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;
//
//    mesh->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
//
//    camera->update(delta_time);
//
//    for (int i = 0; i < 4; ++i)
//    {
//        tnl::Vector3 v = camera->getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));
//        tnl::Vector3 np = tnl::GetNearestPointPlane(mesh->pos_, v, camera->pos_);
//
//        if ((np - mesh->pos_).length() < 50)
//        {
//            mesh->pos_ = np + (v * 50);
//        }
//    }
//
//    mesh->render(camera);
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // �`�揈��
//    //
//
//    DrawGridGround(camera);
//
//    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);
//}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
//void gameEnd() {
//}
//
//
//
////-----------------------------------------------------------------------------------------------------------
////
////
//// �X�N���[���G�t�F�N�g�K�p�T���v��
////
////
////-----------------------------------------------------------------------------------------------------------
//
//
//#include <time.h>
//#include <string>
//#include <numbers>
//#include <functional>
//#include "../dxlib_ext/dxlib_ext.h"
//#include "gm_main.h"
//
//
//
//Shared<dxe::Camera> camera = nullptr;
//Shared<dxe::Mesh> mesh = nullptr;
//Shared<dxe::Mesh> ground = nullptr;
//Shared<dxe::ScreenEffect> screen_efct = nullptr;
//
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//	srand(time(0));
//
//	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
//	SetBackgroundColor(32, 32, 32);
//
//	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//	camera->pos_ = { 0, 300, -700 };
//
//	mesh = dxe::Mesh::CreateSphereMV(100, 20, 20);
//	mesh->setTexture(dxe::Texture::CreateFromFile("graphics/test.jpg"));
//	mesh->pos_ = { 0, 100, 0 };
//
//	ground = dxe::Mesh::CreatePlaneMV({ 2000, 2000, 0 }, 20, 20);
//	ground->setTexture(dxe::Texture::CreateFromFile("graphics/lawn.png"));
//	ground->rot_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
//
//	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//	//screen_efct->loadStatus("screen_effect.bin");
//
//
//}
//
//
////------------------------------------------------------------------------------------------------------------
//// ���t���[�����s����܂�
//void gameMain(float delta_time) {
//
//
//	mesh->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
//
//
//	camera->update(delta_time);
//
//
//	screen_efct->renderBegin();
//
//	ground->render(camera);
//	mesh->render(camera);
//
//	screen_efct->renderEnd();
//
//
//	screen_efct->drawGuiController({ 0, 0 });
//
//	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
//
//}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
//void gameEnd() {
//}
//
//






#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GameEngine/[001]Scene/SceneManager.h"
#include "[002]SceneOP/SceneOp.h"
#include "[003]ScenePlay/ScenePlay.h"

#include "../wta_library/wta_Convert.h"

//Shared<dxe::Camera> camera = nullptr;
//Shared<dxe::Mesh> mesh = nullptr;
//Shared<dxe::Mesh> group = nullptr;


//int model_handle = 0;
//int tex_handle = 0;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() 
{
	//mesh = dxe::Mesh::CreateFromFileMV("model/stage/flowers/marguerite.mv1");
	//mesh->setTexture(dxe::Texture::CreateFromFile("model/stage/flowers/plant.png"));
	//mesh->setBlendMode(DX_BLENDMODE_ALPHA);
	//mesh->pos_ = { 0, 0, 0 };

	//std::vector<tnl::Matrix> mats;
	//mats.emplace_back(tnl::Matrix::Translation({ 0, 0, 0 }));
	//mats.emplace_back(tnl::Matrix::Translation({ 50, 0, 0 }));
	//group = dxe::Mesh::CreateStaticMeshGroupMV(mesh, mats);
	//group->setTexture(dxe::Texture::CreateFromFile("model/stage/flowers/plant.png"));
	//group->scl_ = { 100 };

	tnl::SetSeedMersenneTwister32(time(0));

	srand(time(0));
	SetWindowText("Spring Fairy");

	//// �w�i�̐F��ݒ�(������F)
	//SetBackgroundColor(255, 222, 233);

	// �D�F�̔w�i
	//SetBackgroundColor(32, 32, 32);

	//model_handle = MV1LoadModel("model/stage/flowers/marguerite.mv1");
	//tex_handle = LoadGraph("model/stage/flowers/plant.png");
	//MV1SetTextureGraphHandle(model_handle, 0, tex_handle, true);

	//camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	//camera->pos_ = { 0, 10, -300 };
	SceneManager::GetInstance(new ScenePlay());
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) 
{
	//camera->update(delta_time);

	//group->render(camera);

	SceneManager::GetInstance()->Update(delta_time);

	//MV1SetPosition(model_handle, VGet(-100, 0, 0));
	//MV1DrawModel(model_handle);

	//MV1SetPosition(model_handle, VGet(100, 0, 0));
	//MV1DrawModel(model_handle);


	//DrawDefaultLightGuiController();

	//mesh->render(camera);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() 
{
	SceneManager::GetInstance()->Finalize();
}
