#include "../../../[002]Mediator/Mediator.h"
#include "../../../[001]Camera/CinemaCamera.h"
#include "CinemaBack.h"


CinemaBack::CinemaBack()
{
	m_mesh = dxe::Mesh::CreateCubeMV(2000);
	m_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/event/cinema.png"));
	m_mesh->loadMaterial("graphics/event/material.bin");

	LoadCinemaBackInfo();

	RandomBubbleCalc();

}

CinemaBack::~CinemaBack()
{
	DeleteGraph(m_first_back_hdl);
}

void CinemaBack::LoadCinemaBackInfo()
{
	m_first_back_hdl = LoadGraph("graphics/event/background-green.jpg");
	m_second_back_hdl = LoadGraph("graphics/event/flower_arch.jpg");

	m_fog_hdl = LoadGraph("graphics/event/fog.png");
	m_bubble_hdl = LoadGraph("graphics/event/cinema_bubble.png");
}

void CinemaBack::Update(const float delta_time)
{
	if (m_is_fog)
	{
		UpdateFogBlend();
	}

	if (m_is_bubble)
	{
		UpdateBubblesActive(delta_time);
	}
}

void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_flower)
	{
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_first_back_hdl, TRUE);
	}
	else if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_wood)
	{
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, TRUE);
	}
	else if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_fancy)
	{
		m_mesh->render(camera);
	}

	// レーンが5の時の追加背景
	if(m_is_fog)
	{
		// 画像の透明度を設定（0〜255）
		SetDrawBlendMode(DX_BLENDMODE_ADD, m_alpha);

		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_fog_hdl, TRUE);
	
		// ブレンドモードを通常に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// レーンがpの時の追加背景
	if (m_is_bubble)
	{
		for (sBubble& bubble : m_bubbles)
		{
			if (bubble.s_is_active)
			{
				// シャボン玉の透明度を設定
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(bubble.s_alpha));

				// シャボン玉を描画
				DrawExtendGraph(bubble.s_pos.x - bubble.s_size /2 
								,bubble.s_pos.y - bubble.s_size /2
								,bubble.s_pos.x + bubble.s_size /2
								,bubble.s_pos.y + bubble.s_size /2
								,m_bubble_hdl, TRUE);

				// ブレンドモードを通常に戻す
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void CinemaBack::UpdateFogBlend()
{
	// 透明度の増加
	m_alpha += 5;
	
	if (m_alpha > 255)
	{
		m_alpha = 255;
	}
}

void CinemaBack::RandomBubbleCalc()
{
	for (int i = 0; i < 20; ++i)
	{
		sBubble bubble;
		
		// サイズをランダムに設定
		bubble.s_size = tnl::GetRandomDistributionFloat(400.0f, 500.0f); 

		// 位置を画面端に設定
		int edge = GetRand(3);
		
		switch (edge)
		{
		
		// 上
		case 0: 

			bubble.s_pos.x 
				= tnl::GetRandomDistributionFloat(0, DXE_WINDOW_WIDTH);
			
			bubble.s_pos.y = 0;
		
			break;
		
		// 右
		case 1: 

			bubble.s_pos.x = DXE_WINDOW_WIDTH;
			
			bubble.s_pos.y 
				= tnl::GetRandomDistributionFloat(0, DXE_WINDOW_HEIGHT);
		
			break;
		
		// 下
		case 2: 

			bubble.s_pos.x 
				= tnl::GetRandomDistributionFloat(0, DXE_WINDOW_WIDTH);
			
			bubble.s_pos.y = DXE_WINDOW_HEIGHT;
			
			break;
		
		// 左
		case 3:
			
			bubble.s_pos.x =0;
			
			bubble.s_pos.y 
				= tnl::GetRandomDistributionFloat(0, DXE_WINDOW_HEIGHT );
			
			break;
		}

		// 初期透明度をランダムに設定
		bubble.s_alpha = tnl::GetRandomDistributionFloat(0, 255);
		// 透明度の変化速度をランダムに設定
		bubble.s_life_time = tnl::GetRandomDistributionFloat(100.0f, 150.0f);

		m_bubbles.emplace_back(bubble);
	}
}

void CinemaBack::UpdateBubblesActive(const float delta_time)
{
	for (sBubble& bubble : m_bubbles)
	{
		// 透明度を時間に比例して変化させる
		bubble.s_alpha += bubble.s_life_time * delta_time;

		bubble.s_size += bubble.s_life_time * delta_time * 0.5f;

		// 透明度が範囲外に行った場合は方向を反転
		if (bubble.s_alpha > 255)
		{
			// 透明度が最大に達したら減少させるための速度を設定
			bubble.s_life_time = -bubble.s_life_time;
		}
		if (bubble.s_alpha < 0)
		{
			// 透明度が最小に達したら増加させるための速度を設定
			bubble.s_life_time = -bubble.s_life_time;
		}
	}
}


//void CinemaBack::LoadCinemaBackInfo()
//{
//
//	m_first_back_hdl = LoadGraph("graphics/illust/background-green.jpg");
//	m_second_third_hdl = LoadGraph("graphics/illust/background-green_third.jpg");
//	m_second_back_hdl = LoadGraph("graphics/illust/flower.jpg");
//	//// csvファイルの読み込み
//	//m_csv_skybox_info
//	//	= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_Info.csv");
//
//	//// マップタイルの総数を取得
//	//int max_num = m_csv_skybox_info.size();
//
//	//// 0行目は説明文なので読み飛ばす
//	//for (int y = 1; y < max_num; ++y)
//	//{
//	//	sSkyBoxInfo sky_info;
//
//	//	sky_info.s_id = m_csv_skybox_info[y][0].getInt();
//
//	//	sky_info.s_texture_path = m_csv_skybox_info[y][1].getString();
//
//	//	sky_info.s_material_path = m_csv_skybox_info[y][2].getString();
//
//	//	sky_info.s_screen_effect_path = m_csv_skybox_info[y][3].getString();
//
//	//	m_skybox_info.emplace_back(sky_info);
//	//}
//}
//
//void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
//{
//	//// アクティブなカメラタイプに基づいて背景を描画
//	//CinemaCamera::eCameraSplitType activeType = m_cinema_camera->GetActiveType();
//
//	//if (activeType == CinemaCamera::eCameraSplitType::e_all)
//	//{
//	// 
//
//	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_half_right)
//	//{
//	//	DrawExtendGraph(DXE_WINDOW_WIDTH / 2, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, FALSE);
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_third_left)
//	//{
//	//	DrawExtendGraph(0, 0, m_mediator->GetCinemaSplitWidthLeft(), DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_third_right)
//	//{
//	//	DrawExtendGraph(m_mediator->GetCinemaSplitWidthRight(), 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//	//}
//}