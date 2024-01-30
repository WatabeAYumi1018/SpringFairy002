#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[002]Gimmick/Gimmick.h"
#include "../[000]Object/Object.h"

class GameCamera;


class OpFactory 
{

public:

	OpFactory() {}

	~OpFactory() {}

private:

	std::list<std::shared_ptr<Object>> m_objects;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;

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