#pragma once
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "../library/tnl_intersect.h"


namespace wta
{
	template<class T1,class T2>
	// 交差判定を行う関数の型エイリアス
	// エイアリス : 別名
	// 衝突検出関数の型を Intersected として定義
	// 2つのT型オブジェクトのポインタを引数とするvoid関数
	// 2つのオブジェクトの衝突判定を判定し、衝突した場合はなんらかの処理を実行
	// std::function : 関数オブジェクトを表すクラステンプレート
	using Intersected 
		= std::function<void(std::shared_ptr<T1> a, std::shared_ptr<T2> b)>;

	//template<class T>
	//using IntersectedCheck =std::function<bool(T*, T*)>;

	template<class T1, class T2>
	// キーは文字列、値はIntersected型の関数を持つハッシュマップの型エイリアス
	// 異なるオブジェクトペアに対して、異なる衝突判定関数を登録できる
	// キー : 衝突するオブジェクトのペアを識別するための文字列
	// 値 : 衝突が発生した時に実行される関数(コールバック)
	// std::unordered_map : ハッシュテーブルを用いた連想配列
	using Intersected_map = std::unordered_map<std::string, Intersected<T1,T2>>;

	template<class T1, class T2>
	class Collision
	{

	public:

		Collision() {}
		~Collision() {}

		// 交差判定の関数のマップ
		Intersected_map<T1,T2> m_intersect_map;

		// 交差判定の関数の登録
		// arg1 : 登録する関数のキー(衝突するオブジェクトのペアを識別)
		// arg2 : 衝突が発生した時に実行される関数)(コールバック)
		// ex : registerIntersect("名称", [](Player* p, Enemy* e){...});
		void registerIntersect( const std::string& key
								,const Intersected<T1,T2>& intersect)
		{
			// 指定されたキーに対して交差判定関数をマップに登録
			m_intersect_map[key] = intersect;
		}

		// 2つの交差判定
		// arg1 : 衝突判定を行うオブジェクト(1つ目)
		// arg2 : 衝突判定を行うオブジェクト(2つ目)
		// ex : Intersect(player, enemy);
		void Intersect(std::shared_ptr<T1> a, std::shared_ptr<T2> b)
		{
			// 衝突する2つのオブジェクトの型から一意なキーを生成
			// typeid : 型情報を取得するための演算子
			// typeid(型名).name() : 型名を文字列で取得
			// std::string(typeid(型名).name()) : 型名を文字列に変換
			// std::string ... + std::string ... : 2つの文字列を結合
			// 2つのオブジェクトタイプ間の衝突判定関数を m_intersect_map から検索
			std::string key
				= std::string(typeid(*a).name()) + std::string(typeid(*b).name());

			// 交差判定の関数が登録されていない場合は処理を終了
			if (m_intersect_map.find(key) == m_intersect_map.end())
			{
				return;
			}
			// 交差判定の関数を実行
			// オブジェクトへのポインタaとbを受け取り、具体的な処理を実行
			m_intersect_map[key](a, b);
		}

		// 円同士交差判定(個別同士の判定)
		bool IsIntersectSphere( std::shared_ptr<T1> object1, float object1_radius
								, std::shared_ptr<T2> object2, float object2_radius,bool pos_up = false)
		{
			// nullチェック
			if (object1 == nullptr || object2 == nullptr)
			{
				return false;
			}

			tnl::Vector3 pos1 = object1->GetPos();

			tnl::Vector3 pos2 = object2->GetPos();

			if (pos_up)
			{
				pos2.y += 500;
			}

			// 2つの距離を算出
			tnl::Vector3 distance = pos1 - pos2;
			// 絶対値を算出
			distance.abs();
			// 2つの半径を算出
			float radius = object1_radius + object2_radius;

			// 2つの距離が半径より小さい場合は衝突
			if (distance.x < radius
				&& distance.y < radius
				&& distance.z < radius)
			{
				return true;
			}
			return false;
		}

		// 円同士の補正処理(Object2が弾かれる)
		void CorrectSphere(std::shared_ptr<T1> object1, float object1_radius
							, std::shared_ptr<T2> object2, float object2_radius)
		{
			tnl::Vector3 pos1 = object1->GetPos();
			tnl::Vector3 pos2 = object2->GetPos();

			// 2つのオブジェクト間の距離ベクトルを計算
			tnl::Vector3 distance_vec = pos2 - pos1;
			// 距離ベクトルを正規化して方向を得る
			distance_vec.normalize();
			// 2つのオブジェクト間の距離を算出
			float distance = distance_vec.length();

			// 2つのオブジェクトの半径の合計
			float total_radius = object1_radius + object2_radius;

			// 衝突が発生している場合、位置を補正する
			if (distance < total_radius)
			{
				// 重なりの量を計算
				float overlap = total_radius - distance;

				// 補正するための移動ベクトルを計算（片方または両方のオブジェクトを動かす）
				tnl::Vector3 correct_vec = distance_vec * overlap;

				// オブジェクトの位置を補正
				object1->SetPos(pos1 - correct_vec * 0.03f);
				object2->SetPos(pos2 + correct_vec * 0.03f);
			}
		}

		// 円と直方体の交差判定(個別同士の判定)
		// 直方体の大きさや比率は異なるため、引数で指定する
		bool IsIntersectSphereAABB( std::shared_ptr<T1> object1
									, float object1_radius
									, std::shared_ptr<T2> object2
									, float object2_half_width
									, float object2_half_height
									,float object2_half_depth)
		{
			// nullチェック
			if (object1 == nullptr || object2 == nullptr)
			{
				return false;
			}

			tnl::Vector3 pos1 = object1->GetPos();
			tnl::Vector3 pos2 = object2->GetPos();

			tnl::Vector3 object2_half_size 
				= tnl::Vector3(object2_half_width, object2_half_height, object2_half_depth);

			// AABBの最小値と最大値を算出
			tnl::Vector3 aabb_min = pos2 - object2_half_size;
			tnl::Vector3 aabb_max = pos2 + object2_half_size;

			// 球の中心とAABBの最も近い点との最短距離を算出
			float distance = 0;

			// object1がAABBの外側にあるか判定
			if (pos1.x < aabb_min.x)
			{
				// オブジェクト間の距離を算出
				distance += (aabb_min.x - pos1.x) * (aabb_min.x - pos1.x);
			}
			if (pos1.x > aabb_max.x) 
			{
				distance += (pos1.x - aabb_max.x) * (pos1.x - aabb_max.x);
			}

			// Y軸に関する計算
			if (pos1.y < aabb_min.y)
			{
				distance += (aabb_min.y - pos1.y) * (aabb_min.y - pos1.y);
			}
			if (pos1.y > aabb_max.y) 
			{
				distance += (pos1.y - aabb_max.y) * (pos1.y - aabb_max.y);
			}

			// Z軸に関する計算
			if (pos1.z < aabb_min.z)
			{
				distance += (aabb_min.z - pos1.z) * (aabb_min.z - pos1.z);
			}
			if (pos1.z > aabb_max.z) 
			{
				distance += (pos1.z - aabb_max.z) * (pos1.z - aabb_max.z);
			}

			// 最短距離が半径より小さい場合は衝突
			return distance < object1_radius * object1_radius;
		}

		//// 交差判定(個体とグループの判定)
		//// ベクター内のオブジェクトの中でいずれかが判定されたら他も全て変わる
		//bool IsIntersectAllSpheres( std::shared_ptr<T1> object1
		//							, std::vector<std::shared_ptr<T2>>& objects2)
		//{
		//	// nullチェック
		//	if (object1 == nullptr)
		//	{
		//		return false;
		//	}

		//	tnl::Vector3 pos1 = object1->GetPos();
		//	float size1 = object1->GetCollisionSize();

		//	for (std::shared_ptr<T2> object2 : objects2)
		//	{
		//		tnl::Vector3 pos2 = object2->GetPos();
		//		float size2 = object2->GetCollisionSize();

		//		// 2つの距離を算出
		//		tnl::Vector3 distance = pos1 - pos2;
		//		// 絶対値を算出
		//		distance.abs();
		//		// 2つの半径を算出
		//		float radius = size1 + size2;

		//		// 2つの距離が半径より小さい場合は衝突
		//		if (distance.x < radius
		//			&& distance.y < radius
		//			&& distance.z < radius)
		//		{
		//			return true;
		//		}
		//	}
		//	return false;
		//}
	};
}

/* 
①std::function : 異なる方の関数を同一の型として扱える

宣言) std::function<R(args...)> : Rは戻り値の型、args... は引数の型

例) std::function<int(int)> : 引数がint型のint型関数

通常の関数 : int doublenumber(int x) {return x * 2;}
ラムダ式 : auto doubleNumber = [](int x) {return x * 2;}
関数オブジェクト : struct DN {int operator()(int x) {return x * 2;}}DoubleNumber;

std::function<int(int)> f1 = doublenumber;
std::function<int(int)> f2 = doubleNumber;
std::function<int(int)> f3 = DoubleNumber;

f1(2); // 4
f2(2); // 4
f3(2); // 4

std::function<int(int)> f4 = f1;
f4(2); // 4

異なる型の関数を同一の型として同じように扱える

----------------------------------------------

②std::unordered_map : ハッシュテーブルを用いた連想配列

連想配列 : キーを使用してデータ(値)を迅速に検索、挿入、削除できる
キーに基づいてデータを迅速にアクセスする必要がある場合に特に有用

宣言) std::unordered_map<key, value> : keyはキーの型、valueは値の型

例) std::unordered_map<std::string, int> : キーが文字列、値がint型の連想配列

*/

//void CheckCollision(T* object1
//					, std::vector<T*>& objects
//					, const IntersectedCheck<T>& intersect_check)
//{
//	for (T* object2 : objects)
//	{
//		// 交差判定関数を実行
//		if (intersect_check(object1, object2))
//		{
//			// 衝突した場合は、衝突判定関数を実行
//			Intersect(object1, object2);
//		}
//	}
//
//}

