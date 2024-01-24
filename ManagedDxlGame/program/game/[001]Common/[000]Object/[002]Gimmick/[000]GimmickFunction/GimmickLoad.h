#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickLoad
{

public:

	GimmickLoad();

	~GimmickLoad();

private:

	int m_id_num = 0;
	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	// ���[���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_gimmick_lane;
	// ���[���z����i�[�p
	std::vector<Gimmick::sGimmick> m_gimmick_lanes;
	// �A�C�e�����f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_type_info;
	// �A�C�e�����f���̏��i�[�p
	std::vector<Gimmick::sGimmickType> m_gimmick_type;


	// ���[���z��̓ǂݍ���
	void LoadGimmickVector();

	// �A�C�e�����f���̏��ǂݍ���
	void LoadGimmickTypeInfo();

public:

	// �A�C�e�����f����id�擾
	Gimmick::sGimmickType GetGimmickInfoById(int id);


	int GetIdNum() const{ return m_id_num; }

	const std::vector<Gimmick::sGimmick>& GetGimmickLane() const
	{
		return m_gimmick_lanes;
	}

	const std::vector<Gimmick::sGimmickType>& GetGimmickTypeInfo() const
	{
		return m_gimmick_type;
	}
};
