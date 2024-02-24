#include "Object.h"


void Object::SetLight(int model_hdl)
{
	// 自己発光
	DxLib::COLOR_F emissive = { 0.5f,0.5f,0.5f,1 };
	// 環境光
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	// 拡散光
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	// 鏡面反射光
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(model_hdl, 0, ambient);
	MV1SetMaterialDifColor(model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(model_hdl, 0, specular);
	// 0.5f : 鏡面反射光の強さは強くても弱くても見にくく、値の変更もほとんどない。
	MV1SetMaterialSpcPower(model_hdl, 0, 0.5f);	
}