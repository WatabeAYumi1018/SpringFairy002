#pragma once
#include <queue>
#include <unordered_set>
#include <set>
#include <utility>
#include "../dxlib_ext/dxlib_ext.h"
#include "wta_Convert.h"


namespace wta
{
	template <class T>

	class Astar
	{

	private:

		// A*アルゴリズムによる目的地までの経路探索
		struct sNode
		{
			// ゴール地点
			std::pair<int, int> s_pos;
			// スタートからの移動コスト
			// スタート地点からこのノードまでの移動コスト
			// スタートから何ステップでここに到達したか
			int s_g_cost;
			// ゴールまでの推定コスト(ヒューリスティックコスト)
			// ゴールにどれだけ近いかの推定値
			int s_h_cost;
			// パスを追跡するための親ノード(スタート～ゴールの経路追跡)
			sNode* s_parent;

			// sNode 型のインスタンス同士を比較
			// 優先度付きキューでのノード比較
			// sNode の operator< は一般的な比較のため
			bool operator < (const sNode& other) const
			{
				// 優先度が高いノードを先に処理
				return s_h_cost > other.s_h_cost;
			}
		};

		// ハッシュテーブルは、キーと値のペアを格納するデータ構造
		struct pair_hash
		{
			//ハッシュテーブルは、キーに基づいてデータを効率的に格納、検索、更新、削除するためのデータ構造
			// テンプレートクラスのペアを受け取り、ハッシュ値を返す
			template <class T1, class T2>
			// ペアのハッシュ値を返す
			std::size_t operator () (const std::pair<T1, T2>& pair) const
			{
				auto hash1 = std::hash<T1>{}(pair.first);

				auto hash2 = std::hash<T2>{}(pair.second);
				// 排他的論理和(XOR)を用いて二つのハッシュ値を組み合わせる
				// 二つのビットが異なる場合は1、同じ場合は0
				return hash1 ^ hash2;
			}
		};

		// キュー内でのノード比較
		// std::priority_queue : 第三のテンプレートパラメータとして比較関数を取れる
		// この比較関数はキュー内の要素の優先順位を決定するため使用
		struct CompareNode
		{
			// 優先度付きキューでのノード比較を行う関数
			// std::priority_queueのカスタム優先順位の定義のため
			bool operator()(const sNode& a, const sNode& b) const
			{
				// キュー内での優先順位付け
				return a.s_h_cost > b.s_h_cost;
			}
		};

		// 上下左右の方向数
		static const int DIRECTION_MAX = 8;

		// ノードの移動方向を定義
		// 0 1 2
		// 3   4
		// 5 6 7

		const int DIRECTION[DIRECTION_MAX][2] =
		{
			// 左上
			{ -1, -1 },	
			// 上
			{ 0, -1 },	
			// 右上
			{ 1, -1 },	
			// 左
			{ -1, 0 },	
			// 右
			{ 1, 0 },	
			// 左下
			{ -1, 1 },	
			// 下
			{ 0, 1 },	
			// 右下
			{ 1, 1 },	
		};

		// 経路を格納するベクター(A*)
		std::vector<std::pair<int, int>> m_goal_process;

		// 移動先のタイル
		T  m_move_tile;

		// マップの範囲内か判定
		bool InMapRange(const std::pair<int, int>& grid_pos, int witdh, int height);

		// 経路の再構築
		std::vector<std::pair<int, int>> ReconstructPath(sNode* goalNode);

	public:

		// タイルIDを取得
		int getTileID(const std::pair<int, int>& grid_pos
						, const std::vector<T>& map_tiles
						, int size);


		//A＊で最適なIDとその道順を取得
		void SearchTileID_AStar(const tnl::Vector3& pos
								, T goal_tile
								, int size
								, const std::vector<T>& map_tiles
								, int width, int height);

		std::vector<std::pair<int, int>> GetGoalProcess() const
		{
			return m_goal_process;
		}
	};

	template <class T>
	// マップの範囲内か判定
	bool Astar<T>::InMapRange(const std::pair<int, int>& grid_pos, int witdh, int height)
	{
		// マップの範囲内か判定
		return	grid_pos.first >= 0
				&& grid_pos.first < witdh
				&& grid_pos.second >= 0
				&& grid_pos.second < height;
	}

	template <class T>
	// IDを取得する
	int Astar<T>::getTileID(const std::pair<int, int>& grid_pos
							, const std::vector<T>& map_tiles
							, int size)
	{
		// タイルIDを取得する
		for (const T& tile : map_tiles)
		{
			auto [tile_x, tile_z] = wta::ConvertFloatToGridInt(tile.s_pos, size);
			// 合致する座標があればIDを返す
			if (grid_pos.first == tile_x && grid_pos.second == tile_z)
			{
				return tile.s_id;
			}
		}
		// 該当なし
		return -1;
	}

	template <class T>
	// 経路の再構築
	std::vector<std::pair<int, int>> Astar<T>::ReconstructPath(sNode* goalNode)
	{
		// 経路を格納するベクター
		std::vector<std::pair<int, int>> path;

		// ゴールからスタートまでの経路を逆順に格納
		for (sNode* node = goalNode; node != nullptr; node = node->s_parent)
		{
			// 過程にある各タイルのグリッド座標を格納
			// A*で既に格納されているので、そのまま格納
			path.emplace_back(node->s_pos);
		}

		// reverseで反転処理
		std::reverse(path.begin(), path.end());
		// 経路を返す
		return path;
	}

	template <class T>
	// A*による経路の取得
	void Astar<T>::SearchTileID_AStar(const tnl::Vector3& start_pos
										, T goal_tile
										, int size
										, const std::vector<T>& map_tiles
										, int width, int height)
	{
		// キュー内でのノード比較
		std::priority_queue<sNode, std::vector<sNode>, CompareNode> open_set;
		// クローズドリスト
		std::unordered_map<std::pair<int, int>, sNode, pair_hash> all_nodes;
		// 訪問済みのノード（または位置、座標）を追跡するデータ構造
		std::set<std::pair<int, int>> visited;
		// スタート地点をグリッド座標に変換
		std::pair<int, int> start_grid_pos 
			= wta::ConvertFloatToGridInt(start_pos, size);
		// ゴール地点をグリッド座標に変換
		std::pair<int, int> goal_grid_pos 
			= wta::ConvertFloatToGridInt(goal_tile.s_pos, size);
		// スタート地点のノードを作成
		sNode start_node = { start_grid_pos, 0, 0, nullptr };
		// オープンリストにスタート地点を追格納
		// オープンリスト : 未処理のノードを格納するリスト
		open_set.emplace(start_node);
		// スタート地点のノードを訪問済みに追加
		all_nodes[start_grid_pos] = start_node;
		// 未処理のリストが空になるまでループ
		while (!open_set.empty()) 
		{
			// A*アルゴリズムがキュー内の各要素を一度だけ処理し、
			// 最良の経路を効率的に見つけるために必要な動作
			sNode current = open_set.top();
			// オープンリストの先頭を削除
			// オープンリストの先頭は常に最大の要素（優先度が最も高い要素）
			open_set.pop();
			// ゴール地点に到達した場合
			if (current.s_pos == goal_grid_pos)
			{
				// 経路を格納するベクターに経路を格納
				m_goal_process = ReconstructPath(&current);
			
				return;
			}
			// 訪問済みのノードに追加
			// insert() : 要素を入れる
			visited.insert(current.s_pos);

			// 上下左右斜めの8方向を探索
			for (int dir = 0; dir < DIRECTION_MAX; ++dir)
			{
				// 次のノードの座標を取得
				std::pair<int, int> next_grid_pos
					= { current.s_pos.first + DIRECTION[dir][0]
						, current.s_pos.second + DIRECTION[dir][1] };

				// マップの範囲外または訪問済みの場合はスキップ
				if (!InMapRange(next_grid_pos, width, height)
					|| visited.count(next_grid_pos))
				{
					continue;
				}

				// 次のノードのタイルIDを取得
				int tile_id = getTileID(next_grid_pos, map_tiles, size);
				
				// 進行不可またはゴールでない場合はスキップ
				if (tile_id == -1)
				{
					continue;
				}

				// 次のノードの移動コストを計算(実コスト)
				int g_cost = current.s_g_cost + 1;
				// 次のノードの推定コストを計算
				int h_cost = std::abs(next_grid_pos.first - goal_grid_pos.first)
					+ std::abs(next_grid_pos.second - goal_grid_pos.second);
				// 新しい経路がより効率的（コストが低い）である場合
				if (!all_nodes.count(next_grid_pos)
					|| h_cost < all_nodes[next_grid_pos].s_h_cost)
				{
					// 次のノードの情報を作成
					sNode next_node
						= { next_grid_pos, g_cost, h_cost, &all_nodes[current.s_pos] };
					// オープンリストに追加
					open_set.emplace(next_node);
					// 訪問済みのノードに追加
					all_nodes[next_grid_pos] = next_node;
				}
			}	
		}
	}
}

