#pragma once
//
////-----------------------------------------------------------------------------------------------------------
////
////
//// パーティクル利用サンプル
////
//// ※　このサンプルはパーティクルエディタとしても機能します
////
//// ※　[ 重要 ]　std::shared_ptr で確保した dxe::Particle は必ず gameEnd() の
//// 　　タイミングまでに参照カウンタが 0 になるようリセットしてください ( gameEnd 関数を参照 )
////
//// ※　[ 重要 ]　この機能は DxLib の機能ではありません
//// 　　dxe::Particle や dxe::InstMeshPool など DirectX を直接制御するクラスの render 関数は
////　　 dxe::DirectXRenderBegin() dxe::DirectXRenderEnd() で囲った中でコールしてください  
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
//// 座標と姿勢で制御するカメラ
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
//    // 姿勢パラメータからターゲット座標とアッパーベクトルを計算
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
//// ゲーム起動時に１度だけ実行されます
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
//// 毎フレーム実行されます
//void gameMain(float delta_time) {
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // カメラ制御
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
//    // GUI 描画 ON / OFF
//    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F3)) is_draw_controller = !is_draw_controller;
//
//    // カメラアップデート
//    camera->update(delta_time);
//
//
//
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // 描画処理
//    //
//
//    DrawGridGround(camera);
//
//
//    //---------------------------------------------------------------------------
//    //
//    // パーティクルの描画開始
//    //
//    dxe::DirectXRenderBegin();
//
//    // パーティクル A を描画
//    ptcl->render(camera);
//
//    // パーティクル B を描画
//    // パーティクル C を...
//
//    //---------------------------------------------------------------------------
//    //
//    // パーティクルの描画終了
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
//    DrawString(DXE_WINDOW_WIDTH - 260, 20, "右クリック : 向き", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 40, "ホイール : 前後", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 60, "A D : 左右移動", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 80, "W S : 上下移動", -1);
//    DrawString(DXE_WINDOW_WIDTH - 260, 100, "F3 : GUI 描画 ON/OFF", -1);
//
//}
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム終了時に１度だけ実行されます
//void gameEnd() {
//    ptcl.reset();
//}

////-------------------------------------------------------------------------------------------------------
//
//// 座標と姿勢で制御するカメラ
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
//    // 姿勢パラメータからターゲット座標とアッパーベクトルを計算
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
//// ゲーム起動時に１度だけ実行されます
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
//// 毎フレーム実行されます
//void gameMain(float delta_time) {
//
//    //----------------------------------------------------------------------------------------------------
//    //
//    // カメラ制御
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
//    // 描画処理
//    //
//
//    DrawGridGround(camera);
//
//    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);
//}
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム終了時に１度だけ実行されます
//void gameEnd() {
//}
//
//
//
////-----------------------------------------------------------------------------------------------------------
////
////
//// スクリーンエフェクト適用サンプル
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
//// ゲーム起動時に１度だけ実行されます
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
//// 毎フレーム実行されます
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
//// ゲーム終了時に１度だけ実行されます
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
// ゲーム起動時に１度だけ実行されます
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

	//// 背景の色を設定(さくら色)
	//SetBackgroundColor(255, 222, 233);

	// 灰色の背景
	//SetBackgroundColor(32, 32, 32);

	//model_handle = MV1LoadModel("model/stage/flowers/marguerite.mv1");
	//tex_handle = LoadGraph("model/stage/flowers/plant.png");
	//MV1SetTextureGraphHandle(model_handle, 0, tex_handle, true);

	//camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	//camera->pos_ = { 0, 10, -300 };
	SceneManager::GetInstance(new ScenePlay());
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
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
// ゲーム終了時に１度だけ実行されます
void gameEnd() 
{
	SceneManager::GetInstance()->Finalize();
}
