#include "../dxlib_ext/dxlib_ext.h"


class PlayerMoveLoad
{

public:

	PlayerMoveLoad();

	~PlayerMoveLoad();

private:

	// 移動速度
	float m_move_speed = 0;
	// 移動回転速度
	float m_move_rot = 0;
	// 状況による移動速度変化
	float m_move_change_speed = 0;

	// 宙返りの移動速度
	float m_salto_move_speed = 0;
	// 宙返りの回転速度
	float m_salto_rot = 0;
	// 宙返りの軌道半径
	float m_salto_radius = 0;
	// 宙返りの所要時間
	float m_salto_total_time = 6.0f;

	// ロールの回転速度
	float m_rolling_rot = 10;
	// 八の字の回転速度
	float m_figure_eight_rot = 10;

	// プレイヤーの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<float>> m_csv_player_move;


	void LoadPlayerMoveInfo();

public:

	float GetMoveSpeed() const { return m_move_speed; }

	float GetMoveRot() const { return m_move_rot; }

	float GetSaltoTotalTime() const { return m_salto_total_time; }

	float GetSaltoRadius() const { return m_salto_radius; }

	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }
	//// 移動速度変化を設定
	//void SetMoveChangeSpeed(float speed) { m_move_change_speed = speed; }

};