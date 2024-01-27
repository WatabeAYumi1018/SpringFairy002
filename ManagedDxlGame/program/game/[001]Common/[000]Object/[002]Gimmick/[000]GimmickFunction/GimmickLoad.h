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
	std::vector<std::vector<tnl::CsvCell>> m_csv_plants;
	std::vector<Gimmick::sGimmickTypeInfo> m_plants;
	// �A���؂̃M�~�b�N���f��(�ÓI)
	std::vector<std::vector<tnl::CsvCell>> m_csv_trees;
	std::vector<Gimmick::sGimmickTypeInfo> m_trees;
	// �B�����Ԃ̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_sky_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	// �C���̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_butterflys;
	std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;


	// �A�C�e�����f���̏��ǂݍ���
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks
							 ,Gimmick::eGimmickType type);

public:

	//// �A�C�e�����f����id�擾
	//Gimmick::sGimmickTypeInfo GetGimmickInfoById(int id
	//											 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmick_type);

	const std::vector<Gimmick::sGimmickTypeInfo>& GetPlants() const
	{
		return m_plants;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetTrees() const
	{
		return m_trees;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetSkyFlowers() const
	{
		return m_sky_flowers;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetButterflys() const
	{
		return m_butterflys;
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
