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
//    ptcl = std::make_shared<dxe::Particle>("effect/bloom/bubble_blue.bin");
//
//}
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

//�J���������̃e�X�g�p
//
//// ���W�Ǝp���Ő��䂷��J����
//
//class TransformCamera : public dxe::Camera {
//public:
//
//    TransformCamera() {};
//    TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}
//
//    void update();
//
//
//    inline tnl::Vector3 up()
//    {
//        up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//        return up_;
//    }
//    inline tnl::Vector3 down() { return -up(); }
//
//    tnl::Quaternion rot_;
//};
//
//void TransformCamera::update() {
//
//    //
//    // �p���p�����[�^����^�[�Q�b�g���W�ƃA�b�p�[�x�N�g�����v�Z
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update();
//}
//
//// �T�u�J�������쐬����
//
//class SubCamera : public dxe::Camera
//{
//public:
//
//    SubCamera() {};
//    SubCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}
//
//    void update();
//
//
//    inline tnl::Vector3 up()
//    {
//        up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//        return up_;
//    }
//    inline tnl::Vector3 down() { return -up(); }
//
//    tnl::Quaternion rot_;
//};
//
//void SubCamera::update() {
//
//    //
//    // �p���p�����[�^����^�[�Q�b�g���W�ƃA�b�p�[�x�N�g�����v�Z
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update();
//}
//
//// �J�����̃r���[��`�悷��
//void DrawCameraView(int x, int y, Shared<dxe::Camera> camera)
//{
//    // �J�����̃r���[��`��
//    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
//    DrawCameraView(x, y, camera);
//}
//
//Shared<TransformCamera> camera = nullptr;
//Shared<SubCamera> subcamera = nullptr;
//Shared<dxe::Mesh> mesh_trans = nullptr;
//Shared<dxe::Mesh> mesh_sub = nullptr;
//
////// �ʏ핪��
////// �����䗦�i0.0����1.0�j
////float splitRatio = 0.0f; 
//
////// Go
////// ���C���J�����̕��̔䗦�i�����l��1/3�j
////float mainCameraWidthRatio = 1.0f / 3.0f; 
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//
//    srand(time(0));
//    SetBackgroundColor(32, 32, 32);
//
//    camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    subcamera = std::make_shared<SubCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    mesh_trans = dxe::Mesh::CreateSphereMV(50);
//    mesh_sub = dxe::Mesh::CreateCubeMV(0);
//    camera->pos_ = { 0, 100, -250 };
//    subcamera->pos_ = { 0, 500, -250 };
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
//    if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT))
//    {
//        tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
//        camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
//        camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
//    }
//    camera->pos_ += camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;
//
//    if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT))
//    {
//        tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
//        subcamera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
//        subcamera->rot_ *= tnl::Quaternion::RotationAxis(subcamera->right(), tnl::ToRadian(mvel.y * 0.2f));
//    }
//    subcamera->pos_ += subcamera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;
//
//    mesh_trans->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
//    mesh_sub->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
//
//    camera->update();
//    subcamera->update();
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // �`�揈��
//    //
//
//    // ��{�I�ȕ�������
//
//    // ��ʂ����E�񕪊����ĕ`��
//    int halfWidth = DXE_WINDOW_WIDTH / 2;
//    // ��ʂ��㉺�ɕ������ĕ`��
//    int halfHeight = DXE_WINDOW_HEIGHT / 2;
//
//    // ��������TransformCamera����̕`��
//    SetDrawArea(0, 0, halfWidth, DXE_WINDOW_HEIGHT);
//    DrawGridGround(camera, 50, 50);
//    mesh_trans->render(camera);
//
//    // �E������SubCamera����̕`��
//    SetDrawArea(halfWidth, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    DrawGridGround(subcamera, 30, 50);
//    mesh_sub->render(subcamera);
//
//    //// �㔼����TransformCamera����̕`��
//    //SetDrawArea(0, 0, DXE_WINDOW_WIDTH, halfHeight);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// ��������SubCamera����̕`��
//    //SetDrawArea(0, halfHeight, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    // �`��̈�����Z�b�g
//    SetDrawArea(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//    // ��ʕ����䗦���X�V�i��F���b0.1������������j(�ǂ�ǂ񃁃C���J�����ɂȂ��Ă���)
//
//    //// �����䗦���X�V�F���b0.1������������
//    //splitRatio += 0.1f * delta_time;
//    //if (splitRatio > 1.0f)
//    //{
//    //    // �ő�l��1.0 : ���S�ȉ�����
//    //    splitRatio = 1.0f; 
//    //}
//
//    //// ��ʕ����䗦�Ɋ�Â��ĕ`��̈���v�Z
//    //int splitWidth = static_cast<int>(DXE_WINDOW_WIDTH * splitRatio);
//    //int splitHeight = DXE_WINDOW_HEIGHT - static_cast<int>(DXE_WINDOW_HEIGHT * splitRatio);
//
//    //// �����䗦�Ɋ�Â��ĕ`��
//    //// �㔼���܂��͍�������TransformCamera����̕`��
//    //SetDrawArea(0, 0, splitWidth, DXE_WINDOW_HEIGHT);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// �������܂��͉E������SubCamera����̕`��
//    //SetDrawArea(splitWidth, 0, DXE_WINDOW_WIDTH, splitHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// �`��̈�����Z�b�g
//    //SetDrawArea(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//    //// Go��
//
//    //// ���C���J�����̕��̔䗦���X�V�i��F���b0.05������������j
//    //mainCameraWidthRatio += 0.05f * delta_time;
//    //if (mainCameraWidthRatio > 1.0f)
//    //{
//    //    // �ő�l��1.0�i�S��ʂ����C���J�����j
//    //    mainCameraWidthRatio = 1.0f; 
//    //}
//
//    //// ��ʕ��̌v�Z
//    //int screenWidth = DXE_WINDOW_WIDTH;
//    //int screenHeight = DXE_WINDOW_HEIGHT;
//
//    //// �J�����̕`��̈���v�Z
//    //int mainCameraWidth = static_cast<int>(screenWidth * mainCameraWidthRatio);
//    //// �c��̕���2�Ŋ���
//    //int subCameraWidth = (screenWidth - mainCameraWidth) / 2; 
//
//    //// ���T�u�J�����̕`��
//    //SetDrawArea(0, 0, subCameraWidth, screenHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// ���C���J�����̕`��
//    //SetDrawArea(subCameraWidth, 0, subCameraWidth + mainCameraWidth, screenHeight);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// �E�T�u�J�����̕`��
//    //SetDrawArea(subCameraWidth + mainCameraWidth, 0, screenWidth, screenHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// �`��̈�����Z�b�g
//    //SetDrawArea(0, 0, screenWidth, screenHeight);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//
//    // �t���[�����[�g�\��
//    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);
//}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
//void gameEnd()
//{
//
//}


//// Go
//// ���C���J�����̕��̔䗦�i�����l��1/3�j
//// �ŏ��̕����䗦
//float split_rate = 1.0f / 3.0f;
//
//
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//
//    srand(time(0));
//    SetBackgroundColor(32, 32, 32);
// 
//    // 3�̃X�N���[�����쐬����
//    int screenLeft = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);
//    int screenMiddle = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);
//    int screenRight = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);
//
//    camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    subcamera_right = std::make_shared<SubCamera>(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT);
//    subcamera_left = std::make_shared<SubCamera>(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT);
//
//    mesh_trans = dxe::Mesh::CreateSphereMV(50);
//    mesh_sub = dxe::Mesh::CreateCubeMV(50);
//
//    camera->pos_ = { 0, 100, -250 };
//    subcamera_right->pos_ = { 0, 100, -250 };
//    subcamera_left->pos_ = { 0, 100, -250 };
//
//    mesh_trans->pos_ = { 0, 100, 0 };
//    mesh_sub->pos_ = { 0 , 100 , 0 };
//
//    camera->target_ = mesh_trans->pos_;
//    subcamera_right->target_ = mesh_sub->pos_;
//    subcamera_left->target_ = mesh_sub->pos_;
//
//    // �J�����̃r���[���X�N���[���Ɋ֘A�t����
//    camera->setScreenHandle(screenMiddle);
//    subcamera_right->setScreenHandle(screenRight);
//    subcamera_left->setScreenHandle(screenLeft);
//}
////------------------------------------------------------------------------------------------------------------
//// ���t���[�����s����܂�
//void gameMain(float delta_time) {
//
//
//    //----------------------------------------------------------------------------------------------------
//
//    if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_RETURN))
//    {
//        split_rate += delta_time * 10;
//
//        if (split_rate >= 1.0f)
//        {
//            split_rate = 1.0f;
//        }
//    }
//
//    // ���C�����傫���Ȃ�    
//
//    // �����䗦�Ɋ�Â��Ċe�X�N���[���̕����v�Z���܂��B
//    int split_width_left = static_cast<int>(DXE_WINDOW_WIDTH * (1.0f - split_rate) / 2);
//    int split_width_right = DXE_WINDOW_WIDTH - split_width_left;
//
//    // �����̃J�����r���[���X�V���ĕ`��
//    SetDrawScreen(subcamera_left->getScreenHandle());
//    ClearDrawScreen();
//    subcamera_left->update();
//    mesh_trans->render(subcamera_left);
//
//    // �����̃J�����r���[���X�V���ĕ`��
//    SetDrawScreen(camera->getScreenHandle());
//    ClearDrawScreen();
//    camera->update();
//    mesh_sub->render(camera);
//
//    // �E���̃J�����r���[���X�V���ĕ`��
//    SetDrawScreen(subcamera_right->getScreenHandle());
//    ClearDrawScreen();
//    subcamera_right->update();
//    mesh_trans->render(subcamera_right);
//
//    // �`��Ώۂ�\��ʂɐݒ�
//    SetDrawScreen(DX_SCREEN_BACK);
//
//    DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera->getScreenHandle(), FALSE);
//    DrawExtendGraph(0, 0, split_width_left, DXE_WINDOW_HEIGHT, subcamera_left->getScreenHandle(), FALSE);
//    DrawExtendGraph(split_width_right, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, subcamera_right->getScreenHandle(), FALSE);
//


#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GameEngine/[001]Scene/SceneManager.h"
#include "[000]GameEngine/[002]Music/MusicManager.h"
#include "[002]SceneOP/SceneOp.h"


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() 
{
	srand(time(0));
	SetWindowText("Spring Fairy");

	SetFontSize(20);

	//�����t�H���g
	tnl::AddFontTTF("font/work.ttf");

	SceneManager::GetInstance(new SceneOp());

	// ���y�̓ǂݍ���
	MusicManager::GetInstance().LoadBGM();
	MusicManager::GetInstance().LoadSE();
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) 
{
	ChangeFont("font/work.ttf", DX_CHARSET_DEFAULT);

	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() 
{
	SceneManager::GetInstance()->Finalize();
}


//#pragma once
//
//
//
////-----------------------------------------------------------------------------------------------------------
////
//// �X�J�C�{�b�N�X���p�T���v��
////
//// �� �t�H�O�𗘗p����ꍇ�̓X�J�C�{�b�N�X��`�悵����ɐݒ肵�܂��傤
//// �� �X�J�C�{�b�N�X�͑傫�����̂ŃJ������ far �ݒ莟��ł͕`�悳��Ȃ��Ȃ�̂Œ���
////
////-----------------------------------------------------------------------------------------------------------
//
//#include <time.h>
//#include <string>
//#include <numbers>
//#include <functional>
//#include "../dxlib_ext/dxlib_ext.h"
//#include "gm_main.h"
//
//Shared<dxe::Camera> camera = nullptr;
//Shared<dxe::Mesh> skybox = nullptr;
//dxe::GuiMenuSelector* gui_menu_selector = nullptr;
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���N�����ɂP�x�������s����܂�
//void gameStart() {
//	srand(time(0));
//
//	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
//	SetBackgroundColor(32, 32, 32);
//	SetDefaultLightParameter("directional_light_parameter.bin");
//
//	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//
//	skybox = dxe::Mesh::CreateCubeMV(30000, 20, 20);
//	skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_a.png"));
//	skybox->loadMaterial("material.bin");
//
//	gui_menu_selector = new dxe::GuiMenuSelector(
//		[&](uint32_t select_index) {
//
//			std::string path[5] = {
//				"graphics/skybox/_skybox_a.png",
//				"graphics/skybox/_skybox_b.png",
//				"graphics/skybox/_skybox_c.png"
//			};
//			skybox->setTexture(dxe::Texture::CreateFromFile(path[select_index]));
//
//
//		}, "skybox_a", "skybox_b", "skybox_c"
//	);
//	gui_menu_selector->setPosition({ 330, 0 });
//	gui_menu_selector->setLocation(dxe::GuiMenuSelector::eLocation::DOWN);
//}
//
//
////------------------------------------------------------------------------------------------------------------
//// ���t���[�����s����܂�
//void gameMain(float delta_time) {
//
//	//-------------------------------------------------------------------------------
//	//
//	// update
//	//
//	//-------------------------------------------------------------------------------
//
//	skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));
//
//	camera->update(delta_time);
//	gui_menu_selector->update();
//
//
//	//-------------------------------------------------------------------------------
//	//
//	// draw
//	//
//	//-------------------------------------------------------------------------------
//
//	skybox->render(camera);
//
//	DrawGridGround(camera);
//	DrawDefaultLightGuiController();
//
//	skybox->drawGuiMaterialControlloer();
//
//	gui_menu_selector->draw();
//
//	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
//
//}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
//void gameEnd() {
//
//}
//
//#pragma once
//
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
