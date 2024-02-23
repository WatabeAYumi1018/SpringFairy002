#include "../../../../[000]GameEngine/[001]Music/MusicManager.h"
#include "../../../[001]Camera/CinemaCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_rot
		= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));
}

CinemaPlayer::~CinemaPlayer()
{
	MV1DeleteModel(m_model_hdl);
	m_paras.clear();
}

void CinemaPlayer::Initialize()
{
	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelCinemaHdl();

	SetLight(m_model_hdl);

	m_paras = m_mediator->GetCinemaPlayerParameters();
	
	m_pos = { m_paras[1].s_num,m_paras[2].s_num,m_paras[3].s_num };
}

void CinemaPlayer::Update(const float delta_time)
{
	tnl_sequence_.update(delta_time);

	if (m_is_idle)
	{
		m_mediator->CinemaPlayerAnimIdle(delta_time);
	}
	else if (m_is_dance)
	{
		m_mediator->CinemaPlayerAnimDance(delta_time);
	}
	
	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

	// モデルに行列を適用
	MV1SetMatrix(m_model_hdl, m_matrix);
}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// モデル描画処理
	MV1DrawModel(m_model_hdl);
}

// Lerp関数の定義（線形補間）
float CinemaPlayer::Lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}

void CinemaPlayer::MoveRoundFrontToBack(const float delta_time)
{
	// 時間経過の更新
	m_elapsed_time_circle += delta_time;

	// 中心座標
	tnl::Vector3 pos 
		= { m_paras[5].s_num,m_paras[6].s_num , m_paras[7].s_num };

	// 円運動の半径。初期座標と中心座標から計算
	// pow : べき乗の計算
	// sqrt : 平方根の計算
	// 2 : 2乗(変更なし)
	float radius
		= sqrt(pow(m_pos.x - pos.x, 2) + pow(m_pos.z - pos.z, 2));

	// 円運動の更新
	float angle 
		= (m_elapsed_time_circle / m_paras[4].s_num) 
		* tnl::ToRadian(m_paras[8].s_num);

	// x座標の位置を計算
	// 360 : 360度を超えたら戻る(変更なし)
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.x = pos.x + m_paras[9].s_num;
	}
	else
	{
		m_pos.x = pos.x + sin(angle) * radius;
	}

	// y座標の位置を計算
	// 360度を超えたら戻る
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.y = pos.y + m_paras[10].s_num;
	}
	else
	{
		// 現在の角度に応じてY軸の位置を計算
		m_pos.y = (1 - (angle / tnl::ToRadian(m_paras[8].s_num))) * m_pos.y
					+ (angle / tnl::ToRadian(m_paras[8].s_num)) * pos.y;
	}

	// Z座標の位置を計算
	// 360度を超えたら戻る
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.z = pos.z;
	}
	else
	{
		m_pos.z = pos.z + cos(angle) * radius;
	}

	// 円運動中の移動方向を向くための回転を計算(常に中心を向くように)
	// 90 : どのような円運動かによりますが、
	//		基本的にはモデルのデフォルトに起因するため固定値
	tnl::Vector3 nextPos 
		= pos + tnl::Vector3(sin(angle + tnl::ToRadian(90.0f)), 0
		, cos(angle + tnl::ToRadian(90.0f)));
	
	// 向きを変える
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, nextPos, tnl::Vector3(0, 1, 0));

	// X軸周りに一定角度傾ける
	// 50 : 50度(変更の可能性あり。）
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(m_paras[12].s_num));

	// 回転の組み合わせ
	m_rot = direction_rot * tilt_rot;
}

void CinemaPlayer::MoveRotUpDown(const float delta_time,float speed,bool up)
{
	// 総回転角度
	static float total_rot = 0.0f; 
	const float rot_speed = speed;

	// 総回転角度を更新
	total_rot += rot_speed * delta_time;

	// 720度を超えたらリセット
	if (total_rot > tnl::ToRadian(m_paras[19].s_num))
	{
		total_rot -= tnl::ToRadian(m_paras[19].s_num);
	}

	// Y軸周りの回転クォータニオンを生成
	tnl::Quaternion axis_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), total_rot);

	if (up)
	{
		// 滑らかに回転
		m_rot.slerp(axis_rot, m_paras[0].s_num);
	}
	else
	{
		// Z軸周りに30度傾けるクォータニオンを生成
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
											, tnl::ToRadian(m_paras[16].s_num));

		// 既存の回転と傾斜の回転を合成
		tnl::Quaternion comb_rot = axis_rot * tilt_rot;

		m_rot.slerp(comb_rot, m_paras[0].s_num);
	}
}

void CinemaPlayer::MoveBackCenter(const float delta_time)
{
	// 開始座標を現在の座標に設定
	static tnl::Vector3 start_pos = m_pos;
	// 終了座標を中心座標に設定
	tnl::Vector3 end_pos
		= { m_paras[22].s_num, m_paras[23].s_num, m_paras[24].s_num };

	static float total_time = m_paras[25].s_num;
	static float elapsed_time = 0.0f;

	if (elapsed_time < total_time)
	{
		elapsed_time += delta_time * m_paras[26].s_num;
		float phase = elapsed_time / total_time;

		// Y座標をサイン波で補間（大きな弧を描く）
		// 弧の高さ
		float amplitude = m_paras[27].s_num;

		// サイン波の利用
		// 180 : 0度から180度の範囲でサイン波の値を計算。（変更はほぼ無し）
		// Y座標は開始位置から上に弧を描きながら移動し、中心へと進む。
		m_pos.y = start_pos.y + sin(phase * tnl::ToRadian(180.0f)) * amplitude; 

		// 等加速運動での位置の補間
		m_pos.x = Lerp(start_pos.x, end_pos.x, phase);
		m_pos.y = Lerp(start_pos.y, end_pos.y, phase);
		m_pos.z = Lerp(start_pos.z, end_pos.z, phase);
	}
}

void CinemaPlayer::MoveRoundBackToFront(const float delta_time,float radian,bool up)
{
	// 移動速度の定義
	const float speed = m_paras[33].s_num;

	// 円運動の中心座標（スタート位置と同じ）
	tnl::Vector3 center_pos 
		= { m_paras[35].s_num,m_paras[36].s_num,m_paras[37].s_num };

	// 終了位置
	tnl::Vector3 end_pos 
		= { m_paras[38].s_num,m_paras[39].s_num,m_paras[40].s_num };

	// 移動時間の更新
	m_elapsed_time_circle += delta_time;

	// 全体の動作時間
	const float total_time = m_paras[34].s_num;

	// 現在のフェーズの進行度合いを計算
	float progress = m_elapsed_time_circle / total_time;

	// 角度の計算
	float angle = progress * tnl::ToRadian(radian);

	// 円運動の半径（終了位置と中心座標から計算）
	// 2 : 2乗(変更なし)
	float radius = sqrt(pow(end_pos.x - center_pos.x, 2) 
					+ pow(end_pos.z - center_pos.z, 2));

	// 円運動
	m_pos.x = center_pos.x + sin(angle) * radius;
	
	if (up)
	{
		// 2 : 2で割ることでより自然な動き、振幅を表現。
		// 主に視覚的な動きを表現するために使用し、基本的には変更なし。
		// 但し、より適した値があれば変更の可能性あり。
		m_pos.y = center_pos.y - cos(angle) * radius / 2;
	}
	else
	{
		m_pos.y = center_pos.y + cos(angle) * radius / 2;
	}

	m_pos.z = center_pos.z + cos(angle) * radius;

	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
										, tnl::ToRadian(m_paras[41].s_num));

	// 移動方向を向くための回転を計算
	// 90 : どのような回転かによりますが、
	//		モデルのデフォルトに起因するため固定値
	tnl::Vector3 next_direction 
		= tnl::Vector3(sin(angle + tnl::ToRadian(90.0f)), 0
					  , cos(angle + tnl::ToRadian(90.0f)));
	
	tnl::Quaternion direction_rot 
		= tnl::Quaternion::LookAt(m_pos, m_pos + next_direction, tnl::Vector3(0, 1, 0));
	
	// 進行方向の回転と体を傾ける回転を組み合わせる
	m_rot = tilt_rot * direction_rot;
}

bool CinemaPlayer::SeqTrigger(const float delta_time)
{
	// １番のイベントの場合（登場カメラ）
	if (m_mediator->GetCurrentEventLane().s_id == 1)
	{
		// 最初の紹介
		tnl_sequence_.change(&CinemaPlayer::SeqFirst);
	}
	if (m_mediator->GetCurrentEventLane().s_id == 7)
	{
		// エリア２へ移行
		tnl_sequence_.change(&CinemaPlayer::SeqSecond);
	}
	if (m_mediator->GetCurrentEventLane().s_id == 10)
	{
		// エリア３へ移行
		tnl_sequence_.change(&CinemaPlayer::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqFirst(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_dance = true;
	}

	// 4秒間の実行
	// このあたりのタイムもデバッグ管理が好ましいかもしれませんが、
	// 今回は簡易的に実装しています。
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		MoveRoundFrontToBack(delta_time);

		MusicManager::GetInstance().PlaySE(3);
	});

	// 2秒間の実行
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_rot 
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 1));

		m_is_dance = false;
		m_is_idle = true;
	});

	// 1秒間の実行
	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() 
	{
		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		m_rot.slerp(target_rot, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		tnl::Quaternion back_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		// モデルを前かがみに傾ける
		// 45 : 45度(変更の可能性あり)
		// 本来デバッグで行います。IDの変更が必要なため、後ほど修正します。
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

		// 回転合成
		tnl::Quaternion comb_rot =  tilt_rot * back_rot;

		m_rot.slerp(comb_rot, m_paras[0].s_num);

		// モデルの前への移動速度。
		m_pos.y -= delta_time * m_paras[20].s_num;
		m_pos.z += delta_time * m_paras[21].s_num;

		m_mediator->SetChangeGraphIsFlower(true);
		m_mediator->SetChildGraphIsFlower(true);
	});

	m_is_idle = false;

	m_mediator->SetAnimElapsedTimeDance();

	MusicManager::GetInstance().StopSE(3);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	if(tnl_sequence_.isStart())
	{
		m_is_idle= true;
		m_pos = { m_paras[13].s_num,m_paras[14].s_num,m_paras[15].s_num };
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveRotUpDown(delta_time, m_paras[17].s_num,false);

		m_pos.x -= delta_time * m_paras[18].s_num;
		m_pos.y -= delta_time * m_paras[18].s_num;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{	
		m_is_idle = false;

		// 前方に70度傾斜
		// 70 : 70度(変更の可能性あり)
		// 本来デバッグで行います。IDの変更が必要なため、後ほど修正します。
		m_rot = tnl::Quaternion::RotationAxis(tnl::Vector3(0, -1, -1), tnl::ToRadian(70));

		MoveBackCenter(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_idle = true;

		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		m_rot.slerp(target_rot, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_pos = { 0 };

		// emmisiveを少しずつ強くする
		// 1: 基本的にemmissiveの限界値は1のため、変更はほぼ無し。
		m_emissive.r += delta_time;
		m_emissive.g += delta_time;
		m_emissive.b += delta_time;
		m_emissive.a = 1;

		if (m_emissive.r >= m_emissive.a
			&& m_emissive.g >= m_emissive.a
			&& m_emissive.b >= m_emissive.a)
		{
			m_emissive.r = m_emissive.a;
			m_emissive.g = m_emissive.a;
			m_emissive.b = m_emissive.a;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackFog(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&](){});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_idle = false;	
		m_is_dance = true;

		MusicManager::GetInstance().PlaySE(3);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_mediator->SetChangeGraphIsWood(true);
		m_mediator->SetChildGraphIsWood(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2.5f, delta_time, [&]()
	{
		m_mediator->SetChangeGraphIsActiveWhite(true);
		m_mediator->SetChildGraphIsActiveWhite(true);
	});

	MusicManager::GetInstance().StopSE(3);

	SetDefaultLightParameter("directional_light_parameter.bin");

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance();

	m_mediator->SetIsCinemaBackFog(false);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqThird(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_idle = true;

		m_pos = { m_paras[28].s_num,m_paras[29].s_num,m_paras[30].s_num };
		// 限りなく1に近い値にして幻想的な雰囲気を出す
		DxLib::COLOR_F m_emissive = { 0.9f,0.9f,0.9f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackBubble(true);
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		MoveRotUpDown(delta_time, m_paras[31].s_num);
		
		m_pos.y += delta_time * m_paras[32].s_num;

		if (m_pos.y >= 0)
		{
			m_pos.y = 0;
		}
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		// 360度回転
		MoveRoundBackToFront(delta_time, m_paras[42].s_num,false);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		// -360度回転
		MoveRoundBackToFront(delta_time, m_paras[43].s_num);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// 回転による座標の変更を強制リセット
		// 1フレームでの変更のため、固定値
		m_pos = tnl::Vector3( 0,0,0 );
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(11, delta_time, [&](){});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		// 100 : y座標補正(あまり見栄えに直結しない補正のため固定値)
		float offset = 100.0f;

		m_pos.y -= offset;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		m_is_idle = false;
		m_is_dance = true;

		MusicManager::GetInstance().PlaySE(4);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_mediator->SetEffectIsScreen(true);
		m_mediator->SetChangeGraphIsActiveWhite(true);
		m_mediator->SetChildGraphIsActiveWhite(true);
	});

	MusicManager::GetInstance().StopSE(4);

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance();

	m_mediator->SetEffectIsScreen(false);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}