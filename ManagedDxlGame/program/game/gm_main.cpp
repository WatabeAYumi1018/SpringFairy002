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
//    ptcl = std::make_shared<dxe::Particle>("effect/bloom/bubble_blue.bin");
//
//}
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

//カメラ分割のテスト用
//
//// 座標と姿勢で制御するカメラ
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
//    // 姿勢パラメータからターゲット座標とアッパーベクトルを計算
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update();
//}
//
//// サブカメラを作成する
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
//    // 姿勢パラメータからターゲット座標とアッパーベクトルを計算
//    //
//
//    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
//    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
//    dxe::Camera::update();
//}
//
//// カメラのビューを描画する
//void DrawCameraView(int x, int y, Shared<dxe::Camera> camera)
//{
//    // カメラのビューを描画
//    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
//    DrawCameraView(x, y, camera);
//}
//
//Shared<TransformCamera> camera = nullptr;
//Shared<SubCamera> subcamera = nullptr;
//Shared<dxe::Mesh> mesh_trans = nullptr;
//Shared<dxe::Mesh> mesh_sub = nullptr;
//
////// 通常分割
////// 分割比率（0.0から1.0）
////float splitRatio = 0.0f; 
//
////// Go
////// メインカメラの幅の比率（初期値は1/3）
////float mainCameraWidthRatio = 1.0f / 3.0f; 
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム起動時に１度だけ実行されます
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
//    // 描画処理
//    //
//
//    // 基本的な分割実装
//
//    // 画面を左右二分割して描画
//    int halfWidth = DXE_WINDOW_WIDTH / 2;
//    // 画面を上下に分割して描画
//    int halfHeight = DXE_WINDOW_HEIGHT / 2;
//
//    // 左半分にTransformCameraからの描画
//    SetDrawArea(0, 0, halfWidth, DXE_WINDOW_HEIGHT);
//    DrawGridGround(camera, 50, 50);
//    mesh_trans->render(camera);
//
//    // 右半分にSubCameraからの描画
//    SetDrawArea(halfWidth, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    DrawGridGround(subcamera, 30, 50);
//    mesh_sub->render(subcamera);
//
//    //// 上半分にTransformCameraからの描画
//    //SetDrawArea(0, 0, DXE_WINDOW_WIDTH, halfHeight);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// 下半分にSubCameraからの描画
//    //SetDrawArea(0, halfHeight, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    // 描画領域をリセット
//    SetDrawArea(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//    // 画面分割比率を更新（例：毎秒0.1ずつ増加させる）(どんどんメインカメラになっていく)
//
//    //// 分割比率を更新：毎秒0.1ずつ増加させる
//    //splitRatio += 0.1f * delta_time;
//    //if (splitRatio > 1.0f)
//    //{
//    //    // 最大値は1.0 : 完全な横分割
//    //    splitRatio = 1.0f; 
//    //}
//
//    //// 画面分割比率に基づいて描画領域を計算
//    //int splitWidth = static_cast<int>(DXE_WINDOW_WIDTH * splitRatio);
//    //int splitHeight = DXE_WINDOW_HEIGHT - static_cast<int>(DXE_WINDOW_HEIGHT * splitRatio);
//
//    //// 分割比率に基づいて描画
//    //// 上半分または左半分にTransformCameraからの描画
//    //SetDrawArea(0, 0, splitWidth, DXE_WINDOW_HEIGHT);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// 下半分または右半分にSubCameraからの描画
//    //SetDrawArea(splitWidth, 0, DXE_WINDOW_WIDTH, splitHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// 描画領域をリセット
//    //SetDrawArea(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//    //// Go風
//
//    //// メインカメラの幅の比率を更新（例：毎秒0.05ずつ増加させる）
//    //mainCameraWidthRatio += 0.05f * delta_time;
//    //if (mainCameraWidthRatio > 1.0f)
//    //{
//    //    // 最大値は1.0（全画面がメインカメラ）
//    //    mainCameraWidthRatio = 1.0f; 
//    //}
//
//    //// 画面幅の計算
//    //int screenWidth = DXE_WINDOW_WIDTH;
//    //int screenHeight = DXE_WINDOW_HEIGHT;
//
//    //// カメラの描画領域を計算
//    //int mainCameraWidth = static_cast<int>(screenWidth * mainCameraWidthRatio);
//    //// 残りの幅を2で割る
//    //int subCameraWidth = (screenWidth - mainCameraWidth) / 2; 
//
//    //// 左サブカメラの描画
//    //SetDrawArea(0, 0, subCameraWidth, screenHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// メインカメラの描画
//    //SetDrawArea(subCameraWidth, 0, subCameraWidth + mainCameraWidth, screenHeight);
//    //DrawGridGround(camera, 50, 50);
//    //mesh_trans->render(camera);
//
//    //// 右サブカメラの描画
//    //SetDrawArea(subCameraWidth + mainCameraWidth, 0, screenWidth, screenHeight);
//    //DrawGridGround(subcamera, 30, 50);
//    //mesh_sub->render(subcamera);
//
//    //// 描画領域をリセット
//    //SetDrawArea(0, 0, screenWidth, screenHeight);
//
//
//    // ----------------------------------------------------------------------------------------------------
//
//
//    // フレームレート表示
//    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);
//}
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム終了時に１度だけ実行されます
//void gameEnd()
//{
//
//}


//// Go
//// メインカメラの幅の比率（初期値は1/3）
//// 最初の分割比率
//float split_rate = 1.0f / 3.0f;
//
//
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム起動時に１度だけ実行されます
//void gameStart() {
//
//    srand(time(0));
//    SetBackgroundColor(32, 32, 32);
// 
//    // 3つのスクリーンを作成する
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
//    // カメラのビューをスクリーンに関連付ける
//    camera->setScreenHandle(screenMiddle);
//    subcamera_right->setScreenHandle(screenRight);
//    subcamera_left->setScreenHandle(screenLeft);
//}
////------------------------------------------------------------------------------------------------------------
//// 毎フレーム実行されます
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
//    // メインが大きくなる    
//
//    // 分割比率に基づいて各スクリーンの幅を計算します。
//    int split_width_left = static_cast<int>(DXE_WINDOW_WIDTH * (1.0f - split_rate) / 2);
//    int split_width_right = DXE_WINDOW_WIDTH - split_width_left;
//
//    // 左側のカメラビューを更新して描画
//    SetDrawScreen(subcamera_left->getScreenHandle());
//    ClearDrawScreen();
//    subcamera_left->update();
//    mesh_trans->render(subcamera_left);
//
//    // 中央のカメラビューを更新して描画
//    SetDrawScreen(camera->getScreenHandle());
//    ClearDrawScreen();
//    camera->update();
//    mesh_sub->render(camera);
//
//    // 右側のカメラビューを更新して描画
//    SetDrawScreen(subcamera_right->getScreenHandle());
//    ClearDrawScreen();
//    subcamera_right->update();
//    mesh_trans->render(subcamera_right);
//
//    // 描画対象を表画面に設定
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
// ゲーム起動時に１度だけ実行されます
void gameStart() 
{
	srand(time(0));
	SetWindowText("Spring Fairy");

	SetFontSize(20);

	//文字フォント
	tnl::AddFontTTF("font/work.ttf");

	SceneManager::GetInstance(new SceneOp());

	// 音楽の読み込み
	MusicManager::GetInstance().LoadBGM();
	MusicManager::GetInstance().LoadSE();
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) 
{
	ChangeFont("font/work.ttf", DX_CHARSET_DEFAULT);

	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
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
//// スカイボックス利用サンプル
////
//// ※ フォグを利用する場合はスカイボックスを描画した後に設定しましょう
//// ※ スカイボックスは大きく作るのでカメラの far 設定次第では描画されなくなるので注意
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
//// ゲーム起動時に１度だけ実行されます
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
//// 毎フレーム実行されます
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
//// ゲーム終了時に１度だけ実行されます
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
