#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace wta
{
    // tnl::Vector3をVECTORに変換する
    // args ... tnl::Vector3
    // return ... VECTOR
    // ex ... 	VECTOR vec = wta::ConvertToVECTOR(tl_vec);
    inline VECTOR ConvertToVECTOR(const tnl::Vector3& tnl_pos)
    {
        return VGet(tnl_pos.x, tnl_pos.y, tnl_pos.z);
    }

    // VECTORをtnl::Vector3に変換する
    // args ... VECTOR
    // return ... tnl::Vector3
    // ex ... 	tnl::Vector3 tnl_vec = wta::ConvertToVECTOR(vec);
    inline tnl::Vector3 ConvertToTnl(const VECTOR& vec_pos)
    {
        return tnl::Vector3(vec_pos.x, vec_pos.y, vec_pos.z);
    }

    // ワールド座標(tnl::Vector3)をグリッド座標(int)に変換する関数
    // args1 ... tnl::Vector3
    // args2 ... グリッドのサイズ
    // ex ... std::pair<int, int> grid_pos = wta::ConvertFloatToGridInt(tnl_vec);
    inline std::pair<int, int> ConvertFloatToGridInt(const tnl::Vector3& pos, int size)
    {
        int x = static_cast<int>(pos.x / size);
        int z = static_cast<int>(pos.z / size);

        return { x, z };
    }

    // グリッド座標(int)をワールド座標(tnl::Vector3)に変換する関数
    // args1 ... グリッド座標
    // args2 ... グリッドのサイズ
    // ex ... tnl::Vector3 tnl_vec = wta::ConvertGridIntToFloat(grid_pos);
    inline tnl::Vector3 ConvertGridIntToFloat(const std::pair<int, int>& pos, int size)
    {
        float x = static_cast<float>(pos.first * size);
        float z = static_cast<float>(pos.second * size);

        return { x, 0, z };
    }

    // tnl::QuaternionからDXlibのMATRIXへの変換
    // args ... tnl::Quaternion
    // ex ... 	MATRIX matrix = wta::ConvertToVECTOR(tnl_quaternion);
    inline MATRIX ConvertQuaternionToMatrix(const tnl::Quaternion& quaternion)
    {
        // 1. tnl::QuaternionからDirectX::XMVECTORを生成
        DirectX::XMVECTOR quaternion_vector = DirectX::XMLoadFloat4(&quaternion);

        // 2. DirectX::XMVECTORを使ってDirectX::XMMATRIXを生成
        DirectX::XMMATRIX matrix_rotation
            = DirectX::XMMatrixRotationQuaternion(quaternion_vector);

        // 3. DirectX::XMMATRIXをDirectX::XMFLOAT4X4に変換
        DirectX::XMFLOAT4X4 matrixF4_rotation;
        DirectX::XMStoreFloat4x4(&matrixF4_rotation, matrix_rotation);

        // 4. DirectX::XMFLOAT4X4をtnl::Matrixにキャスト
        // （tnl::MatrixのコンストラクタがXMFLOAT4X4を受け取る場合）
        tnl::Matrix tnl_matrix(matrixF4_rotation);

        // 5. tnl::MatrixをDXライブラリのMATRIX型に変換
        // （メモリレイアウトが同じであることが必要）
        MATRIX dx_matrix;

        std::memcpy(&dx_matrix, &tnl_matrix, sizeof(MATRIX));

        return dx_matrix;
    }

    //inline MATRIX ConvertQuaternionToMatrix(const tnl::Quaternion& quaternion)
    //{
    //    tnl::Matrix mat = quaternion.getMatrix();

    //    MATRIX dxm;

    //    memcpy(&dxm, &mat.m, sizeof(float) * 16);

    //    return dxm;
    //}

    // tnl::MatrixからDXlibのMATRIXへの変換
    inline MATRIX ConvertTnlToDxMatrix(const tnl::Matrix& tnl_matrix)
    {
        MATRIX dx_matrix;

        // tnl::MatrixのデータをDXライブラリのMATRIXにコピー
        // tnl::MatrixがDirectX::XMFLOAT4X4と同じメモリレイアウトを持っていると仮定
        std::memcpy(&dx_matrix, &tnl_matrix, sizeof(MATRIX));

        return dx_matrix;
    }

    // DXlibのMATRIXからtnl::Matrixへの変換
    inline tnl::Matrix ConvertDxToTnlMatrix(const MATRIX& dx_matrix)
    {
		tnl::Matrix tnl_matrix;

		// DXライブラリのMATRIXのデータをtnl::Matrixにコピー
		// tnl::MatrixがDirectX::XMFLOAT4X4と同じメモリレイアウトを持っていると仮定
		std::memcpy(&tnl_matrix, &dx_matrix, sizeof(MATRIX));

		return tnl_matrix;
	}

    // tnl::Vector3をtnl::Matrixに変換する
    inline tnl::Matrix ConvertTnlToMatrix(const tnl::Vector3& tnl_pos)
	{
		tnl::Matrix mat;
		
        mat.Translation(tnl_pos);
		
        return mat;
	}

    // tnl::Matrixをtnl::Vector3に変換する
    inline tnl::Vector3 ConvertMatrixToTnl(const tnl::Matrix& tnl_matrix)
    {
        return tnl::Vector3(tnl_matrix.m[3][0], tnl_matrix.m[3][1], tnl_matrix.m[3][2]);
	}


}