#pragma once
#include "../dxlib_ext/dxlib_ext.h"



class OpFactory 
{

public:

	OpFactory() {}

	~OpFactory() {}

private:

	// 各オブジェクトの生成と初期化
	void CreateObject();
	// 各オブジェクト同士の参照を設定
	// 生成の順番を考慮せず、後付けで参照できるように
	void SetObjectReference();
	// モデルオブジェクトのプール
	//void PoolModelObject();
	// アイテムオブジェクトのプール
	void PoolGimmickType(const std::vector<Gimmick::sGimmickTypeInfo>& gimmick_types);
	// 生成したオブジェクトをlistに格納
	void StorageObject();


public:

	// listに格納したオブジェクトの取得
	const std::list<std::shared_ptr<Object>>& GetObjects() const
	{
		return m_objects;
	}

	// カメラの取得
	const std::shared_ptr<GameCamera>& GetGameCamera() const
	{
		return m_gameCamera;
	}

};