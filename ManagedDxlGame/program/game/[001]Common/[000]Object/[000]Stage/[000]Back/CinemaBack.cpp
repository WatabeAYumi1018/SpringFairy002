#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "CinemaBack.h"


CinemaBack::CinemaBack()
{
	RandomBubbleCalc();
}

CinemaBack::~CinemaBack()
{
	for (const sCinemaBackInfo& cinema_back : m_cinema_back_info)
	{
		DeleteGraph(cinema_back.s_back_hdl);
	}

	m_cinema_back_info.clear();
}

void CinemaBack::Initialize()
{
	m_cinema_back_info = m_mediator->GetCinemaBackGraphInfo();

	LoadSkyBackInfo();
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
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
						, m_cinema_back_info[0].s_back_hdl, TRUE);
	}
	else if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_wood)
	{
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
						, m_cinema_back_info[1].s_back_hdl, TRUE);
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

		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
						, m_cinema_back_info[2].s_back_hdl, TRUE);
	
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
								, m_cinema_back_info[3].s_back_hdl, TRUE);

				// ブレンドモードを通常に戻す
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void CinemaBack::LoadSkyBackInfo()
{
	std::vector<SkyBox::sSkyBoxInfo> m_sky_box;

	m_sky_box = m_mediator->GetSkyBoxGraphInfo();

	// 2000 : 背景についてはサイズ変更することはないため固定値
	float size = 2000.0f;

	m_mesh = dxe::Mesh::CreateCubeMV(size);
	m_mesh->setTexture(dxe::Texture::CreateFromFile(m_sky_box[2].s_texture_path.c_str()));
	m_mesh->loadMaterial(m_sky_box[2].s_material_path.c_str());
}

void CinemaBack::UpdateFogBlend()
{
	// 透明度の増加
	m_alpha += m_alpha_speed;
	
	if (m_alpha > 255)
	{
		m_alpha = 255;
	}
}

void CinemaBack::UpdateBubblesActive(const float delta_time)
{
	for (sBubble& bubble : m_bubbles)
	{
		// 透明度を時間に比例して変化させる
		bubble.s_alpha += bubble.s_life_time * delta_time;
		// シャボン玉の大きさを時間に比例して変化させる
		bubble.s_size += bubble.s_life_time * delta_time;

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

void CinemaBack::RandomBubbleCalc()
{
	for (int i = 0; i < m_bubble_num; ++i)
	{
		sBubble bubble;
		
		// サイズをランダムに設定
		bubble.s_size 
			= tnl::GetRandomDistributionFloat(m_bubble_size_min, m_bubble_size_max);

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
		// 0 ~ 255 : 透明 ~ 不透明
		bubble.s_alpha = tnl::GetRandomDistributionFloat(0, 255);
		// 透明度の変化速度をランダムに設定
		bubble.s_life_time 
			= tnl::GetRandomDistributionFloat(m_bubble_life_time_min, m_bubble_life_time_max);

		m_bubbles.emplace_back(bubble);
	}
}

