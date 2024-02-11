#include "../../../wta_library/wta_Convert.h"
#include "Transform.h"


MATRIX Transform::GetTransformMatrix()
{
	// ①拡大縮小を設定する

	// tnl::m_scaleをVECTOR型に変換
	VECTOR vecter_scale = wta::ConvertToVECTOR(m_scale);

	// スケールを設定する
	// VECTOR型からMATRIX型に変換
	MATRIX matrix_scale = MGetScale(vecter_scale);

	// ------------------------

	// ②回転を設定する

	// クォータニオンから回転行列を設定する
	MATRIX matrix_rotation = wta::ConvertQuaternionToMatrix(m_rot);

	// ------------------------

	// ③座標を設定する

	// tnl::m_posをVECTOR型に変換
	VECTOR vecter_pos = wta::ConvertToVECTOR(m_pos);

	// 移動を設定する
	MATRIX matrix_translation = MGetTranslate(vecter_pos);

	// ------------------------

	// ④行列の合成（スケール、回転、平行移動）

	// MMult関数 : 二つの行列の乗算を行う
	MATRIX matrix_transform = MMult(matrix_scale, matrix_rotation);

	// 更に行列の乗算を行う（DXlibでは３つ以上の乗算はないため、分けて計算）
	// 一般的には拡大縮小→回転→平行移動の順序で乗算
	matrix_transform = MMult(matrix_transform, matrix_translation);

	return matrix_transform;
}