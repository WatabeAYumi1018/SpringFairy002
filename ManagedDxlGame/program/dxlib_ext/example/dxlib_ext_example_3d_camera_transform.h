#pragma once

/*

//---------------------------------------------------------------------------------------------------------------
//
//
// フラスタムカメラサンプル
//
//
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"


//-------------------------------------------------------------------------------------------------------
//
// 注視点までの「 距離 」「 Y軸角度 」「 X軸角度 」で制御するカメラ
//
class FreeLookCamera : public dxe::Camera {
public:
	FreeLookCamera() {};
	FreeLookCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

	void update(const float delta_time) override;

	// カメラの上方向を取得する関数
	inline tnl::Vector3 up()
	{
		// 
		up_ = tnl::Vector3::TransformCoord({ 0,1,0 }, rot_);
		return up_;
	}

	inline tnl::Vector3 down() { return -up(); }

	inline::tnl::Vector3 forward() override
	{
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0,0,1 }, rot_);
		return tnl::Vector3::Normalize(target_ - pos_);
	}

	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	tnl::Quaternion rot_;
};


void FreeLookCamera::update(const float delta_time) {

	target_ = pos_ + tnl::Vector3::TransformCoord({ 0,0,1 }, rot_);
	up_ = tnl::Vector3::TransformCoord({ 0,1,0 }, rot_);
	// ベースカメラのアップデート
	// ビュー行列・プロジェクション行列の更新
	dxe::Camera::update(delta_time);
}

Shared<FreeLookCamera> camera = nullptr;
Shared<dxe::Mesh> mesh = nullptr;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<FreeLookCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	mesh = dxe::Mesh::CreateSphereMV(100, 20, 20);
	mesh->setTexture(dxe::Texture::CreateFromFile("graphics/test.jpg"));

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				camera->left(),
				camera->right(),
				tnl::Vector3::up,
				tnl::Vector3::down
			};
			camera->pos_ += v[index] * 3.0f;

			camera->target_ = mesh->pos_;

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT))
	{
		tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
		camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
		camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
	}

	camera->pos_ += camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;

	mesh->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));

	camera->update(delta_time);

	for (int i = 0; i < 4; ++i)
	{
		tnl::Vector3 v = camera->getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));
		tnl::Vector3 np = tnl::GetNearestPointPlane(mesh->pos_, v, camera->pos_);

		if ((np - mesh->pos_).length() < 100)
		{
			mesh->pos_ = np + (v * 100);
		}
	}


	DrawGridGround(camera, 50, 20);

	mesh->render(camera);

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
*/

/*

//---------------------------------------------------------------------------------------------------------------
//
//
// トランスフォームカメラサンプル
//
//
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"


//-------------------------------------------------------------------------------------------------------
//
// 座標と姿勢で制御するカメラ
//
class TransformCamera : public dxe::Camera {
public:

	TransformCamera() {};
	TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

	void update();


	inline tnl::Vector3 up() {
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
		return up_ ;
	}
	inline tnl::Vector3 down() { return -up() ; }

	inline tnl::Vector3 forward() override {
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
		return tnl::Vector3::Normalize(target_ - pos_);
	}
	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	tnl::Quaternion rot_ ;

};

void TransformCamera::update() {

	//
	// 姿勢パラメータからターゲット座標とアッパーベクトルを計算
	//

	target_ = pos_ + tnl::Vector3::TransformCoord({0, 0, 1}, rot_);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
	dxe::Camera::update();
}


Shared<TransformCamera> camera = nullptr;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {


	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				camera->left(),
				camera->right(),
				camera->forward().xz(),
				camera->back().xz()
			};
			camera->pos_ += v[index] * 3.0f;

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
	camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.1f));
	camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.1f));


	camera->update();


	DrawGridGround(camera, 50, 20);

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


*/