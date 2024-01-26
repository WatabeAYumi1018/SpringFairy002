#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickLoad
{

public:

	GimmickLoad();

	~GimmickLoad();

private:
	
	// �@���Ԃ̃M�~�b�N���f��(�ÓI)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_plants;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_plants;
	// �A���؂̃M�~�b�N���f��(�ÓI)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_trees;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_trees;
	// �B�����Ԃ̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_sky_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_sky_flowers;
	// �C���̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_butterfly;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_butterfly;


	// �A�C�e�����f���̏��ǂݍ���
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks
							 ,Gimmick::eGimmickType type);

public:

	// �A�C�e�����f����id�擾
	Gimmick::sGimmickTypeInfo GetGimmickInfoById(int id);

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypePlants() const
	{
		return m_gimmick_plants;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeTrees() const
	{
		return m_gimmick_trees;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeSkyFlowers() const
	{
		return m_gimmick_sky_flowers;
	}

};

//int m_id_num = 0;

//// ���[���z��̍���
//int m_lane_height = 0;
//// ���[���z��̕�
//int m_lane_width = 0;

// �M�~�b�N�̓��[���z��łȂ��A�J������Ԃő��삷����������I�����B�i�������׌y���j

//// ���[���z��ǂݎ���p�icsv�t�@�C���j
//std::vector<std::vector<int>> m_csv_gimmick_lane;
//// ���[���z����i�[�p
//std::vector<Gimmick::sGimmick> m_gimmick_lanes;

//// ���f���̏��ǂݎ���p�icsv�t�@�C���j
//std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_type_info;
//// �A�C�e�����f���̏��i�[�p
//std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_type;


//// ���[���z��̓ǂݍ���
//void LoadGimmickVector();

//int GetIdNum() const { return m_id_num; }

//const std::vector<Gimmick::sGimmick>& GetGimmickLane() const
//{
//	return m_gimmick_lanes;
//}

//const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeInfo() const
//{
//	return m_gimmick_type;
//}
