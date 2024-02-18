#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 座標情報を持つ既定クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Transform
{

protected:

	//-----------------------------------メンバ変数-----------------------------------//

	// 座標
	tnl::Vector3 m_pos;
	// サイズ
	tnl::Vector3 m_size;
	// 回転
	tnl::Quaternion m_rot;
	// 拡大縮小
	tnl::Vector3 m_scale = { 1,1,1 };
	// 当たり判定サイズ
	float m_collision_size;
	// 行列
	MATRIX m_matrix;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// Transformの属性から変換行列を生成
	MATRIX GetTransformMatrix();

	//----------------------------------------------------------------------//

public:

	//----------------------------Setter&Getter----------------------------//

	// 座標の設定
	void SetPos(const tnl::Vector3& pos) { m_pos = pos; }
	// 座標の取得
	const tnl::Vector3& GetPos() const { return m_pos; }
	// サイズの設定
	void SetSize(const tnl::Vector3& size) { m_size = size; }
	// サイズの取得
	const tnl::Vector3& GetSize() const { return m_size; }
	// 回転の設定
	void SetRot(const tnl::Quaternion& rot) { m_rot = rot; }
	// 回転の取得
	const tnl::Quaternion& GetRot() const { return m_rot; }
	// 拡大縮小の設定
	void SetScale(const tnl::Vector3& scale) { m_scale = scale; }
	// 拡大縮小の取得
	const tnl::Vector3& GetScale() const { return m_scale; }
	// 当たり判定サイズの設定
	void SetCollisionSize(float size) { m_collision_size = size; }
	// 当たり判定サイズの取得
	const float GetCollisionSize() const { return m_collision_size; }
	// 行列の設定
	void SetMatrix(const MATRIX& matrix) { m_matrix = matrix; }
	// 行列の取得
	const MATRIX& GetMatrix() const { return m_matrix; }

	//---------------------------------------------------------------------//
};