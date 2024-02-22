#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Object;

class SkyBox;
class BackLoad;

class Butterfly;
class ButterflyLoad;

class Title;

class Gate;
class GateLoad;

class EnterGraph;

class Mediator;

class OpCamera;


///////////////////////////////////////////////////////////////////////////
//
// OPシーンのオブジェクト生成クラス
//
///////////////////////////////////////////////////////////////////////////


class OpFactory 
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	OpFactory();
	~OpFactory();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 生成したオブジェクトを格納するlist
	std::list<std::shared_ptr<Object>> m_objects;

	// 各クラスのポインタ

	std::shared_ptr<Object> m_object = nullptr;

	std::shared_ptr<SkyBox> m_skyBox = nullptr;
	std::shared_ptr<BackLoad> m_backLoad = nullptr;

	std::shared_ptr<Butterfly> m_butterfly = nullptr;
	std::shared_ptr<ButterflyLoad> m_butterflyLoad = nullptr;

	std::shared_ptr<Title> m_title = nullptr;

	std::shared_ptr<Gate> m_gate = nullptr;
	std::shared_ptr<GateLoad> m_gateLoad = nullptr;

	std::shared_ptr<EnterGraph> m_enterGraph = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;
	std::shared_ptr<OpCamera> m_opCamera = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// ※実行順として、CreateObject() -> SetObjectReference() -> StorageObject()
	
	// 各オブジェクトの生成と初期化
	// tips ... 初期化時に一度だけ呼び出す
	void CreateObject();

	// 各オブジェクト同士の参照を設定
	// tips ... 初期化時に一度だけ呼び出す
	//          生成の順番を考慮せず、後付けで参照できるように
	void SetObjectReference();
	
	// 生成したオブジェクトをlistに格納
	// tips ... 初期化時に一度だけ呼び出す
	//          オブジェクト型のみを格納し、ポリモーフィズムで扱う
	void StorageObject();

	//--------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// listに格納したオブジェクトの取得
	const std::list<std::shared_ptr<Object>>& GetObjects() const
	{
		return m_objects;
	}

	// カメラの取得
	const std::shared_ptr<OpCamera>& GetGameCamera() const
	{
		return m_opCamera;
	}

	//--------------------------------------------------------------------------------//
};