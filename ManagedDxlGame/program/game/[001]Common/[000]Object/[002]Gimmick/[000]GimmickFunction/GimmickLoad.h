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
	std::vector<std::vector<tnl::CsvCell>> m_csv_ground_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_ground_flowers;
	// �A���؂̃M�~�b�N���f��(�ÓI)
	std::vector<std::vector<tnl::CsvCell>> m_csv_woods;
	std::vector<Gimmick::sGimmickTypeInfo> m_woods;
	// �B�����Ԃ̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_sky_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	// �C���̃M�~�b�N���f��(���I)
	std::vector<std::vector<tnl::CsvCell>> m_csv_butterflys;
	std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;


	// ���f���̏��ǂݍ���
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks);

public:

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmicksType(Gimmick::eGimmickType type) const;
};
