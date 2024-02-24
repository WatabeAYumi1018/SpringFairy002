#include "../[002]Mediator/Mediator.h"
#include "../[003]Phase/StagePhase.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// 使用する画面の作成
	m_screen_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);

	// カメラに映る範囲の最近距離
	// 10 : ドアップのため限りなく0に近い数値で（ほぼ変更ないため固定値）
	near_ = 10;

	LoadParameter();
}

CinemaCamera::~CinemaCamera()
{
	// 画面の解放
	DeleteGraph(m_screen_hdl);

	m_csv_parameters.clear();
	m_paras.clear();
}

void CinemaCamera::LoadParameter()
{
	m_csv_parameters
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/camera/cinemaCamera_move.csv");

	// 0行目は説明文なので読み飛ばす
	// 0列目は見やすさのために記入しただけで不要な数値のため読み飛ばす
	// 2列目はパラメータ名、4列目はパラメータの内容となっており、今回は不要
	for (int y = 1; y < m_csv_parameters.size(); ++y)
	{
		CinemaCamera::sCinemaCameraParameter cinemaCamera_parameter;

		cinemaCamera_parameter.s_id
			= m_csv_parameters[y][1].getInt();

		cinemaCamera_parameter.s_num
			= m_csv_parameters[y][3].getFloat();

		m_paras.emplace_back(cinemaCamera_parameter);
	}
}

void CinemaCamera::SetCanvas()
{
	// 画面に描画
	SetDrawScreen(m_screen_hdl);
	ClearDrawScreen();
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);
}

void CinemaCamera::Render()
{
	// 描画対象を表画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// 全画面のため0～Maxまで描画
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH
					, DXE_WINDOW_HEIGHT, m_screen_hdl, FALSE);
}

tnl::Vector3 CinemaCamera::Lerp(const tnl::Vector3& start
								, const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void CinemaCamera::Fixed(const tnl::Vector3& offset)
{
	if (m_mediator->GetButterflyIsCinemaActive())
	{
		target_ = m_mediator->GetButterflyPos();
	}
	else
	{
		target_ = m_mediator->GetCinemaCameraTargetPos();
	}

	pos_.x = target_.x + offset.x;
	pos_.y = target_.y + offset.y;
	pos_.z = target_.z + offset.z;
}

void CinemaCamera::ToSlide(const float delta_time,const tnl::Vector3& offset,float speed)
{
	// 目的の位置を計算
	tnl::Vector3 target_pos
		= tnl::Vector3(target_.x + offset.x, target_.y + offset.y, target_.z + offset.z);

	// 補間を使用してカメラ位置を更新
	// 速度を掛けることで補間の速度を調整(細かい調整のため)
	pos_ = Lerp(pos_, target_pos, delta_time * speed);
}

bool CinemaCamera::SeqTrigger(const float delta_time)
{
	StagePhase::eStagePhase stage_phase
			= m_mediator->GetNowStagePhaseState();

	if (stage_phase == StagePhase::eStagePhase::e_flower)
	{
		tnl_sequence_.change(&CinemaCamera::SeqFirst);
	}
	if (stage_phase == StagePhase::eStagePhase::e_wood)
	{
		tnl_sequence_.change(&CinemaCamera::SeqSecond);
	}
	if (stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		tnl_sequence_.change(&CinemaCamera::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqFirst(const float delta_time)
{
	// 4 秒間のみ実行
	// こういった値もデバッグで調整するためにcsvに記載するのが好ましいですが、
	// 今回は複雑さとプログラム上での調節の簡易さを重視し、固定値で実装しています。
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Fixed({ m_paras[1].s_num,m_paras[2].s_num,m_paras[3].s_num });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, { m_paras[4].s_num,m_paras[5].s_num,m_paras[6].s_num }, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2.4f, delta_time, [&]()
	{
		Fixed({ m_paras[4].s_num,m_paras[5].s_num,m_paras[6].s_num });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqSecond(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed({ m_paras[10].s_num,m_paras[11].s_num,m_paras[12].s_num  });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, { m_paras[13].s_num,m_paras[14].s_num,m_paras[15].s_num },m_paras[16].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(9, delta_time, [&]()
	{
		Fixed({ m_paras[17].s_num,m_paras[18].s_num,m_paras[19].s_num });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqThird(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Fixed({ m_paras[20].s_num,m_paras[21].s_num,m_paras[22].s_num });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		ToSlide(delta_time, { m_paras[23].s_num,m_paras[24].s_num,m_paras[25].s_num }, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		ToSlide(delta_time, { m_paras[26].s_num,m_paras[27].s_num,m_paras[28].s_num }, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		m_mediator->SetButterflyIsCinemaActive(true);

		target_ = m_mediator->GetButterflyPos();

		ToSlide(delta_time, { m_paras[29].s_num,m_paras[30].s_num,m_paras[31].s_num }, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(8, delta_time, [&]()
	{
		Fixed({ m_paras[32].s_num,m_paras[33].s_num,m_paras[34].s_num });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		target_ = m_mediator->GetCinemaCameraTargetPos();

		ToSlide(delta_time, { m_paras[35].s_num,m_paras[36].s_num,m_paras[37].s_num }, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(4.5f, delta_time, [&]()
	{
		Fixed({ m_paras[35].s_num,m_paras[36].s_num,m_paras[37].s_num });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}