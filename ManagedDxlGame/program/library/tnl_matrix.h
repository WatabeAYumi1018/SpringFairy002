#pragma once
#include <DirectXMath.h>
#include "tnl_vector3.h"

namespace tnl {

	class Quaternion;
	class Matrix final : public DirectX::XMFLOAT4X4 {
	public:
		Matrix() noexcept :
			XMFLOAT4X4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1)
		{}
		explicit Matrix(DirectX::XMMATRIX& m) noexcept { DirectX::XMStoreFloat4x4(this, m); }
		explicit Matrix(DirectX::XMFLOAT4X4& m) noexcept : DirectX::XMFLOAT4X4(m) {}


		//-----------------------------------------------------------------------------------------------------
		//
		// operator
		//
		Matrix& operator = (DirectX::XMMATRIX& other) noexcept;
		Matrix operator * (const Matrix& other) const noexcept;
		Matrix& operator *= (const Matrix& other) noexcept;


		//-----------------------------------------------------------------------------------------------------
		//
		// inline function
		//
		inline void translation(const float x, const float y, const float z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixTranslation(x, y, z);
			XMStoreFloat4x4(this, xm);
		}
		inline void scaling(const float x, const float y, const float z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixScaling(x, y, z);
			XMStoreFloat4x4(this, xm);
		}
		inline void rotationX(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationX(radian);
			XMStoreFloat4x4(this, xm);
		}
		inline void rotationY(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationY(radian);
			XMStoreFloat4x4(this, xm);
		}
		inline void rotationZ(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationZ(radian);
			XMStoreFloat4x4(this, xm);
		}
		inline void rotationPitchYawRoll(const float pitch, const float yaw, const float roll) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
			XMStoreFloat4x4(this, xm);
		}
		inline void rotationAxis(Vector3& v, const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&v), radian);
			XMStoreFloat4x4(this, xm);
		}
		inline void inverse() noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(this));
			XMStoreFloat4x4(this, xm);
		}
		inline void transpose() noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(this));
			XMStoreFloat4x4(this, xm);
		}

		inline void lookAtLH(const Vector3& eye, const Vector3& look, const Vector3& vup) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixLookAtLH(
				DirectX::XMLoadFloat3(&eye),
				DirectX::XMLoadFloat3(&look),
				DirectX::XMLoadFloat3(&vup));
			XMStoreFloat4x4(this, xm);
		}

		inline Matrix perspectiveFovLH(const float angle, const float aspect, const float near_z, const float far_z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixPerspectiveFovLH(angle, aspect, near_z, far_z);
			XMStoreFloat4x4(this, xm);
		}

		inline Matrix orthoLH(const float width, const float height, const float near_z, const float far_z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixOrthographicLH(width, height, near_z, far_z);
			XMStoreFloat4x4(this, xm);
		}

		inline Matrix billboard(const Vector3& eye, const Vector3& look, const Vector3& vup) noexcept {
			*this = LookAtLH(eye, look, vup);
			this->inverse();
			_41 = _42 = _43 = 0;
		}

		inline std::string toString(const std::string& format = "%f") {
			std::string str;
			for (uint32_t i = 0; i < 4; ++i) {
				for (uint32_t k = 0; k < 4; ++k) {
					str += "[ "; str += FloatToString(m[i][k], format);	str += " ] ";
				}
				str += "\n";
			}
			return str;
		}

		//-----------------------------------------------------------------------------------------------------
		//
		// static inline function
		//

		// 単位行列を生成
		static inline Matrix Translation(const float x, const float y, const float z) noexcept 
		{
			// XMMATRIX : Mathライブラリにおける4x4の行列
			// XMMatrixTranslation : x, y, zの値を基に移動行列を計算
			DirectX::XMMATRIX xm = DirectX::XMMatrixTranslation(x, y, z);
			// XMFLOAT4X4は、4x4の行列を表す構造体
			DirectX::XMFLOAT4X4 f4x4;
			// XMStoreFloat4x4 : XMMATRIXのデータをXMFLOAT4X4に変換して格納
			XMStoreFloat4x4(&f4x4, xm);
			// XMFLOAT4X4をMatrixクラスのインスタンスにキャスト
			return static_cast<Matrix>(f4x4);
		}

		static inline Matrix Translation(const tnl::Vector3& v) noexcept {
			return Translation(v.x, v.y, v.z);
		}

		static inline Matrix Scaling(const float x, const float y, const float z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixScaling(x, y, z);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix Scaling(const tnl::Vector3& v) noexcept {
			return Scaling(v.x, v.y, v.z);
		}
		static inline Matrix RotationX(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationX(radian);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix RotationY(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationY(radian);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix RotationZ(const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationZ(radian);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix RotationPitchYawRoll(const float pitch, const float yaw, const float roll) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix RotationPitchYawRoll(const Vector3& rot) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix RotationAxis(const Vector3& v, const float radian) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&v), radian);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}
		// 逆行列を生成
		// 逆行列は、元の行列と掛け合わせると単位行列になる行列
		// 逆行列を求めることで、元の行列を逆方向に変換することができる
		static inline Matrix Inverse(const Matrix& m) noexcept
		{
			// XMMATRIX : 4x4の行列を表す構造体
			// nullptr : 計算中に特定の成分が0になった場合、0にするかどうか指定
			DirectX::XMMATRIX xm
				= DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&m));

			DirectX::XMFLOAT4X4 f4x4;

			// XMLoadFloat4x4 : XMFLOAT4X4のデータをXMMATRIXに変換
			// XMFLOAT4X4 : 軽量な構造体で、行列の値を格納するのに仕様
			// メモリ上のレイアウトがシンプル。
			// ファイル入出力やネットワーク通信、シリアライズ（データ保存）に適する
			// 高度な数学的操作（行列の乗算、逆行列の計算など）には最適化されていない
			// XMMATRIX : 行列の計算に特化した構造体
			// メモリ上のレイアウトが複雑で使用量も大きい
			// 一般的にはXMFLOAT4X4でデータを格納しXMMATRIX を使って計算
			// 計算後は再び XMFLOAT4X4 形式に変換して格納する
			XMStoreFloat4x4(&f4x4, xm);

			return static_cast<Matrix>(f4x4);
		}
		static inline Matrix Transpose(const Matrix& m) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m));
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}

		// 透視投影行列を生成する(左手座標系)
		// args1 ... 視野角（カメラの位置）
		// args2 ... アスペクト比（カメラが向いている方向のターゲットポイントを指定）
		// args3 ... カメラの上方向を示すベクトルを指定
		static inline Matrix LookAtLH(const Vector3& eye, const Vector3& look, const Vector3& vup) noexcept
		{
			// XMMATRIX : Mathライブラリにおける4x4の行列
			// XMMatrixLookAtLH : eye、look、vupベクトルを基にビュー行列を計算 
			DirectX::XMMATRIX xm = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye),
				DirectX::XMLoadFloat3(&look),
				DirectX::XMLoadFloat3(&vup));
			// DirectX::XMFLOAT4X4は、4x4の行列を表す構造体
			// DirectXMathのXMMATRIXと異なり、メモリ上での配置が異なるため変換が必要
			DirectX::XMFLOAT4X4 f4x4;

			// XMStoreFloat4x4 : XMMATRIXのデータをXMFLOAT4X4に変換して格納
			XMStoreFloat4x4(&f4x4, xm);

			// XMFLOAT4X4をMatrixクラスのインスタンスにキャストして返す
			return static_cast<Matrix>(f4x4);
		}

		// 透視投影行列を生成する(左手座標系)
		// args1 ... 視野角（カメラの位置）
		// args2 ... アスペクト比（カメラが向いている方向のターゲットポイントを指定）
		// args3 ... カメラに映る最近距離
		// args4 ... カメラに映る最遠距離
		static inline Matrix PerspectiveFovLH(const float angle, const float aspect
			, const float near_z, const float far_z) noexcept
		{
			// XXMATRIX : 4x4の行列を表す構造体
			// XMMatrixPerspectiveFovLH : 視野角、アスペクト比、最近距離、最遠距離を基に射影行列を計算
			DirectX::XMMATRIX xm = DirectX::XMMatrixPerspectiveFovLH(angle, aspect, near_z, far_z);
			// XMFLOAT4X4は、4x4の行列を表す構造体
			DirectX::XMFLOAT4X4 f4x4;
			// XMStoreFloat4x4 : XMMATRIXのデータをXMFLOAT4X4に変換して格納
			XMStoreFloat4x4(&f4x4, xm);
			// XMFLOAT4X4をMatrixクラスのインスタンスにキャストして返す
			return static_cast<Matrix>(f4x4);
		}

		static inline Matrix OrthoLH(const float width, const float height, const float near_z, const float far_z) noexcept {
			DirectX::XMMATRIX xm = DirectX::XMMatrixOrthographicLH(width, height, near_z, far_z);
			DirectX::XMFLOAT4X4 f4x4;
			XMStoreFloat4x4(&f4x4, xm);
			return static_cast<Matrix>(f4x4);
		}

		static inline Matrix Billboard(const Vector3& eye, const Vector3& look, const Vector3& vup) noexcept {
			Matrix m = LookAtLH(eye, look, vup);
			m.inverse();
			m._41 = m._42 = m._43 = 0;
			return m;
		}


		//-----------------------------------------------------------------------------------------------------
		//
		// function
		//
		void rotationQuaternion(const tnl::Quaternion& q) noexcept;

		//-----------------------------------------------------------------------------------------------------
		//
		// static function
		//
		static Matrix RotationQuaternion(const tnl::Quaternion& q) noexcept;
		static Matrix AffineTransformation(const Vector3& pos, const Vector3& scl, const Quaternion& rot, const Vector3& origin = { 0, 0, 0 }) noexcept;
	};


	inline Matrix& Matrix::operator = (DirectX::XMMATRIX& other) noexcept {
		DirectX::XMStoreFloat4x4(this, other);
		return *this;
	}

	inline Matrix Matrix::operator * (const Matrix& other) const noexcept {
		DirectX::XMMATRIX xm1 = DirectX::XMLoadFloat4x4(this);
		DirectX::XMMATRIX xm2 = DirectX::XMLoadFloat4x4(&other);
		DirectX::XMMATRIX xm3 = DirectX::XMMatrixMultiply(xm1, xm2);
		DirectX::XMFLOAT4X4 f4x4;
		DirectX::XMStoreFloat4x4(&f4x4, xm3);
		return static_cast<Matrix>(f4x4);
	}

	inline Matrix& Matrix::operator *= (const Matrix& other) noexcept {
		Matrix m = other;
		*this = *this * m;
		return *this;
	}


}
