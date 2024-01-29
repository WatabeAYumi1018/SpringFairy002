#include "Object.h"


void Object::SetLight(int model_hdl)
{
	DxLib::COLOR_F emissive = { 0.8f,0.8f,0.8f,1 };
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(model_hdl, 0, ambient);
	MV1SetMaterialDifColor(model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(model_hdl, 0, specular);
	MV1SetMaterialSpcPower(model_hdl, 0, 0.5f);	
}