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

		// カメラの３次元座標
		tnl::Vector3 pos_ = { 0,0,-500 };
		// カメラが３次元のどこを画面の中央にとらえているか
		tnl::Vector3 target_ = tnl::Vector3(0, 0, 0);
		// カメラの『上』を定義するアッパーベクトル
		tnl::Vector3 up_ = tnl::Vector3(0, 1, 0);

		// カメラの画角 ( 度 )
		float angle_ = tnl::ToRadian(60.0f);
		// カメラのアスペクト比 ( 縦横比 )
		float aspect_ = 1.0f;
		// カメラに映る範囲の最近距離
		float near_ = 100.0f;
		// カメラに映る範囲の最遠距離
		float far_ = 50000.0f;

		// カメラのビュー行列 : カメラの位置と向きを表す行列
		// シーン内のオブジェクトをカメラの視点から見た位置に変換する行列
		// 世界座標系からビュー座標系（カメラ座標系）への変換
		tnl::Matrix view_;
		// カメラの射影行列 : カメラの視野範囲を表す行列
		// オブジェクトを3D空間から2D画面空間に投影
		// オブジェクトをカメラのビューポート（表示領域）にフィットさせるための遠近感を生成
		tnl::Matrix proj_;

		// カメラの前方向
		virtual inline tnl::Vector3 forward()
		{
			return tnl::Vector3::Normalize(target_ - pos_);
		}
		// 左方向
		virtual inline tnl::Vector3 left()
		{
			// 前と上(Y軸、{0, 1, 0})の外積で算出
			return tnl::Vector3::Cross(forward(), { 0, 1, 0 });
		}
		// 右方向
		virtual inline tnl::Vector3 right()
		{
			// 上(Y軸、{0, 1, 0})と前の外積で算出
			return tnl::Vector3::Cross({ 0, 1, 0 }, forward());
		}
		// 後ろ方向
		virtual inline tnl::Vector3 back()
		{
			return tnl::Vector3::Normalize(pos_ - target_);
		}

		//----------------------------------------------------------------------------------------------
		// work... 視錐台平面の法線を取得する
		// arg1... 6つの平面のどれか
		// ret.... 視錐台平面の法線
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
