#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace wta
{
    // tnl::Vector3��VECTOR�ɕϊ�����
    // args ... tnl::Vector3
    // return ... VECTOR
    // ex ... 	VECTOR vec = wta::ConvertToVECTOR(tl_vec);
    inline VECTOR ConvertToVECTOR(const tnl::Vector3& tnl_pos)
    {
        return VGet(tnl_pos.x, tnl_pos.y, tnl_pos.z);
    }

    // VECTOR��tnl::Vector3�ɕϊ�����
    // args ... VECTOR
    // return ... tnl::Vector3
    // ex ... 	tnl::Vector3 tnl_vec = wta::ConvertToVECTOR(vec);
    inline tnl::Vector3 ConvertToTnl(const VECTOR& vec_pos)
    {
        return tnl::Vector3(vec_pos.x, vec_pos.y, vec_pos.z);
    }

    // ���[���h���W(tnl::Vector3)���O���b�h���W(int)�ɕϊ�����֐�
    // args1 ... tnl::Vector3
    // args2 ... �O���b�h�̃T�C�Y
    // ex ... std::pair<int, int> grid_pos = wta::ConvertFloatToGridInt(tnl_vec);
    inline std::pair<int, int> ConvertFloatToGridInt(const tnl::Vector3& pos, int size)
    {
        int x = static_cast<int>(pos.x / size);
        int z = static_cast<int>(pos.z / size);

        return { x, z };
    }

    // �O���b�h���W(int)�����[���h���W(tnl::Vector3)�ɕϊ�����֐�
    // args1 ... �O���b�h���W
    // args2 ... �O���b�h�̃T�C�Y
    // ex ... tnl::Vector3 tnl_vec = wta::ConvertGridIntToFloat(grid_pos);
    inline tnl::Vector3 ConvertGridIntToFloat(const std::pair<int, int>& pos, int size)
    {
        float x = static_cast<float>(pos.first * size);
        float z = static_cast<float>(pos.second * size);

        return { x, 0, z };
    }

    // tnl::Quaternion����DXlib��MATRIX�ւ̕ϊ�
    // args ... tnl::Quaternion
    // ex ... 	MATRIX matrix = wta::ConvertToVECTOR(tnl_quaternion);
    inline MATRIX ConvertQuaternionToMatrix(const tnl::Quaternion& quaternion)
    {
        // 1. tnl::Quaternion����DirectX::XMVECTOR�𐶐�
        DirectX::XMVECTOR quaternion_vector = DirectX::XMLoadFloat4(&quaternion);

        // 2. DirectX::XMVECTOR���g����DirectX::XMMATRIX�𐶐�
        DirectX::XMMATRIX matrix_rotation
            = DirectX::XMMatrixRotationQuaternion(quaternion_vector);

        // 3. DirectX::XMMATRIX��DirectX::XMFLOAT4X4�ɕϊ�
        DirectX::XMFLOAT4X4 matrixF4_rotation;
        DirectX::XMStoreFloat4x4(&matrixF4_rotation, matrix_rotation);

        // 4. DirectX::XMFLOAT4X4��tnl::Matrix�ɃL���X�g
        // �itnl::Matrix�̃R���X�g���N�^��XMFLOAT4X4���󂯎��ꍇ�j
        tnl::Matrix tnl_matrix(matrixF4_rotation);

        // 5. tnl::Matrix��DX���C�u������MATRIX�^�ɕϊ�
        // �i���������C�A�E�g�������ł��邱�Ƃ��K�v�j
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

    // tnl::Matrix����DXlib��MATRIX�ւ̕ϊ�
    inline MATRIX ConvertTnlToDxMatrix(const tnl::Matrix& tnl_matrix)
    {
        MATRIX dx_matrix;

        // tnl::Matrix�̃f�[�^��DX���C�u������MATRIX�ɃR�s�[
        // tnl::Matrix��DirectX::XMFLOAT4X4�Ɠ������������C�A�E�g�������Ă���Ɖ���
        std::memcpy(&dx_matrix, &tnl_matrix, sizeof(MATRIX));

        return dx_matrix;
    }

    // DXlib��MATRIX����tnl::Matrix�ւ̕ϊ�
    inline tnl::Matrix ConvertDxToTnlMatrix(const MATRIX& dx_matrix)
    {
		tnl::Matrix tnl_matrix;

		// DX���C�u������MATRIX�̃f�[�^��tnl::Matrix�ɃR�s�[
		// tnl::Matrix��DirectX::XMFLOAT4X4�Ɠ������������C�A�E�g�������Ă���Ɖ���
		std::memcpy(&tnl_matrix, &dx_matrix, sizeof(MATRIX));

		return tnl_matrix;
	}

    // tnl::Vector3��tnl::Matrix�ɕϊ�����
    inline tnl::Matrix ConvertTnlToMatrix(const tnl::Vector3& tnl_pos)
	{
		tnl::Matrix mat;
		
        mat.Translation(tnl_pos);
		
        return mat;
	}

    // tnl::Matrix��tnl::Vector3�ɕϊ�����
    inline tnl::Vector3 ConvertMatrixToTnl(const tnl::Matrix& tnl_matrix)
    {
        return tnl::Vector3(tnl_matrix.m[3][0], tnl_matrix.m[3][1], tnl_matrix.m[3][2]);
	}


}