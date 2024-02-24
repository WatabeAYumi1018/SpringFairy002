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

		// A*�A���S���Y���ɂ��ړI�n�܂ł̌o�H�T��
		struct sNode
		{
			// �S�[���n�_
			std::pair<int, int> s_pos;
			// �X�^�[�g����̈ړ��R�X�g
			// �X�^�[�g�n�_���炱�̃m�[�h�܂ł̈ړ��R�X�g
			// �X�^�[�g���牽�X�e�b�v�ł����ɓ��B������
			int s_g_cost;
			// �S�[���܂ł̐���R�X�g(�q���[���X�e�B�b�N�R�X�g)
			// �S�[���ɂǂꂾ���߂����̐���l
			int s_h_cost;
			// �p�X��ǐՂ��邽�߂̐e�m�[�h(�X�^�[�g�`�S�[���̌o�H�ǐ�)
			sNode* s_parent;

			// sNode �^�̃C���X�^���X���m���r
			// �D��x�t���L���[�ł̃m�[�h��r
			// sNode �� operator< �͈�ʓI�Ȕ�r�̂���
			bool operator < (const sNode& other) const
			{
				// �D��x�������m�[�h���ɏ���
				return s_h_cost > other.s_h_cost;
			}
		};

		// �n�b�V���e�[�u���́A�L�[�ƒl�̃y�A���i�[����f�[�^�\��
		struct pair_hash
		{
			//�n�b�V���e�[�u���́A�L�[�Ɋ�Â��ăf�[�^�������I�Ɋi�[�A�����A�X�V�A�폜���邽�߂̃f�[�^�\��
			// �e���v���[�g�N���X�̃y�A���󂯎��A�n�b�V���l��Ԃ�
			template <class T1, class T2>
			// �y�A�̃n�b�V���l��Ԃ�
			std::size_t operator () (const std::pair<T1, T2>& pair) const
			{
				auto hash1 = std::hash<T1>{}(pair.first);

				auto hash2 = std::hash<T2>{}(pair.second);
				// �r���I�_���a(XOR)��p���ē�̃n�b�V���l��g�ݍ��킹��
				// ��̃r�b�g���قȂ�ꍇ��1�A�����ꍇ��0
				return hash1 ^ hash2;
			}
		};

		// �L���[���ł̃m�[�h��r
		// std::priority_queue : ��O�̃e���v���[�g�p�����[�^�Ƃ��Ĕ�r�֐�������
		// ���̔�r�֐��̓L���[���̗v�f�̗D�揇�ʂ����肷�邽�ߎg�p
		struct CompareNode
		{
			// �D��x�t���L���[�ł̃m�[�h��r���s���֐�
			// std::priority_queue�̃J�X�^���D�揇�ʂ̒�`�̂���
			bool operator()(const sNode& a, const sNode& b) const
			{
				// �L���[���ł̗D�揇�ʕt��
				return a.s_h_cost > b.s_h_cost;
			}
		};

		// �㉺���E�̕�����
		static const int DIRECTION_MAX = 8;

		// �m�[�h�̈ړ��������`
		// 0 1 2
		// 3   4
		// 5 6 7

		const int DIRECTION[DIRECTION_MAX][2] =
		{
			// ����
			{ -1, -1 },	
			// ��
			{ 0, -1 },	
			// �E��
			{ 1, -1 },	
			// ��
			{ -1, 0 },	
			// �E
			{ 1, 0 },	
			// ����
			{ -1, 1 },	
			// ��
			{ 0, 1 },	
			// �E��
			{ 1, 1 },	
		};

		// �o�H���i�[����x�N�^�[(A*)
		std::vector<std::pair<int, int>> m_goal_process;

		// �ړ���̃^�C��
		T  m_move_tile;

		// �}�b�v�͈͓̔�������
		bool InMapRange(const std::pair<int, int>& grid_pos, int witdh, int height);

		// �o�H�̍č\�z
		std::vector<std::pair<int, int>> ReconstructPath(sNode* goalNode);

	public:

		// �^�C��ID���擾
		int getTileID(const std::pair<int, int>& grid_pos
						, const std::vector<T>& map_tiles
						, int size);


		//A���ōœK��ID�Ƃ��̓������擾
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
	// �}�b�v�͈͓̔�������
	bool Astar<T>::InMapRange(const std::pair<int, int>& grid_pos, int witdh, int height)
	{
		// �}�b�v�͈͓̔�������
		return	grid_pos.first >= 0
				&& grid_pos.first < witdh
				&& grid_pos.second >= 0
				&& grid_pos.second < height;
	}

	template <class T>
	// ID���擾����
	int Astar<T>::getTileID(const std::pair<int, int>& grid_pos
							, const std::vector<T>& map_tiles
							, int size)
	{
		// �^�C��ID���擾����
		for (const T& tile : map_tiles)
		{
			auto [tile_x, tile_z] = wta::ConvertFloatToGridInt(tile.s_pos, size);
			// ���v������W�������ID��Ԃ�
			if (grid_pos.first == tile_x && grid_pos.second == tile_z)
			{
				return tile.s_id;
			}
		}
		// �Y���Ȃ�
		return -1;
	}

	template <class T>
	// �o�H�̍č\�z
	std::vector<std::pair<int, int>> Astar<T>::ReconstructPath(sNode* goalNode)
	{
		// �o�H���i�[����x�N�^�[
		std::vector<std::pair<int, int>> path;

		// �S�[������X�^�[�g�܂ł̌o�H���t���Ɋi�[
		for (sNode* node = goalNode; node != nullptr; node = node->s_parent)
		{
			// �ߒ��ɂ���e�^�C���̃O���b�h���W���i�[
			// A*�Ŋ��Ɋi�[����Ă���̂ŁA���̂܂܊i�[
			path.emplace_back(node->s_pos);
		}

		// reverse�Ŕ��]����
		std::reverse(path.begin(), path.end());
		// �o�H��Ԃ�
		return path;
	}

	template <class T>
	// A*�ɂ��o�H�̎擾
	void Astar<T>::SearchTileID_AStar(const tnl::Vector3& start_pos
										, T goal_tile
										, int size
										, const std::vector<T>& map_tiles
										, int width, int height)
	{
		// �L���[���ł̃m�[�h��r
		std::priority_queue<sNode, std::vector<sNode>, CompareNode> open_set;
		// �N���[�Y�h���X�g
		std::unordered_map<std::pair<int, int>, sNode, pair_hash> all_nodes;
		// �K��ς݂̃m�[�h�i�܂��͈ʒu�A���W�j��ǐՂ���f�[�^�\��
		std::set<std::pair<int, int>> visited;
		// �X�^�[�g�n�_���O���b�h���W�ɕϊ�
		std::pair<int, int> start_grid_pos 
			= wta::ConvertFloatToGridInt(start_pos, size);
		// �S�[���n�_���O���b�h���W�ɕϊ�
		std::pair<int, int> goal_grid_pos 
			= wta::ConvertFloatToGridInt(goal_tile.s_pos, size);
		// �X�^�[�g�n�_�̃m�[�h���쐬
		sNode start_node = { start_grid_pos, 0, 0, nullptr };
		// �I�[�v�����X�g�ɃX�^�[�g�n�_��Ǌi�[
		// �I�[�v�����X�g : �������̃m�[�h���i�[���郊�X�g
		open_set.emplace(start_node);
		// �X�^�[�g�n�_�̃m�[�h��K��ς݂ɒǉ�
		all_nodes[start_grid_pos] = start_node;
		// �������̃��X�g����ɂȂ�܂Ń��[�v
		while (!open_set.empty()) 
		{
			// A*�A���S���Y�����L���[���̊e�v�f����x�����������A
			// �ŗǂ̌o�H�������I�Ɍ����邽�߂ɕK�v�ȓ���
			sNode current = open_set.top();
			// �I�[�v�����X�g�̐擪���폜
			// �I�[�v�����X�g�̐擪�͏�ɍő�̗v�f�i�D��x���ł������v�f�j
			open_set.pop();
			// �S�[���n�_�ɓ��B�����ꍇ
			if (current.s_pos == goal_grid_pos)
			{
				// �o�H���i�[����x�N�^�[�Ɍo�H���i�[
				m_goal_process = ReconstructPath(&current);
			
				return;
			}
			// �K��ς݂̃m�[�h�ɒǉ�
			// insert() : �v�f������
			visited.insert(current.s_pos);

			// �㉺���E�΂߂�8������T��
			for (int dir = 0; dir < DIRECTION_MAX; ++dir)
			{
				// ���̃m�[�h�̍��W���擾
				std::pair<int, int> next_grid_pos
					= { current.s_pos.first + DIRECTION[dir][0]
						, current.s_pos.second + DIRECTION[dir][1] };

				// �}�b�v�͈̔͊O�܂��͖K��ς݂̏ꍇ�̓X�L�b�v
				if (!InMapRange(next_grid_pos, width, height)
					|| visited.count(next_grid_pos))
				{
					continue;
				}

				// ���̃m�[�h�̃^�C��ID���擾
				int tile_id = getTileID(next_grid_pos, map_tiles, size);
				
				// �i�s�s�܂��̓S�[���łȂ��ꍇ�̓X�L�b�v
				if (tile_id == -1)
				{
					continue;
				}

				// ���̃m�[�h�̈ړ��R�X�g���v�Z(���R�X�g)
				int g_cost = current.s_g_cost + 1;
				// ���̃m�[�h�̐���R�X�g���v�Z
				int h_cost = std::abs(next_grid_pos.first - goal_grid_pos.first)
					+ std::abs(next_grid_pos.second - goal_grid_pos.second);
				// �V�����o�H���������I�i�R�X�g���Ⴂ�j�ł���ꍇ
				if (!all_nodes.count(next_grid_pos)
					|| h_cost < all_nodes[next_grid_pos].s_h_cost)
				{
					// ���̃m�[�h�̏����쐬
					sNode next_node
						= { next_grid_pos, g_cost, h_cost, &all_nodes[current.s_pos] };
					// �I�[�v�����X�g�ɒǉ�
					open_set.emplace(next_node);
					// �K��ς݂̃m�[�h�ɒǉ�
					all_nodes[next_grid_pos] = next_node;
				}
			}	
		}
	}
}

