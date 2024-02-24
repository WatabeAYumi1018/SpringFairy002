#include "Object.h"


void Object::SetLight(int model_hdl)
{
	// ���Ȕ���
	DxLib::COLOR_F emissive = { 0.5f,0.5f,0.5f,1 };
	// ����
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	// �g�U��
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	// ���ʔ��ˌ�
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(model_hdl, 0, ambient);
	MV1SetMaterialDifColor(model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(model_hdl, 0, specular);
	// 0.5f : ���ʔ��ˌ��̋����͋����Ă��キ�Ă����ɂ����A�l�̕ύX���قƂ�ǂȂ��B
	MV1SetMaterialSpcPower(model_hdl, 0, 0.5f);	
}