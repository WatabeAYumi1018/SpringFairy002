#include "Text.h"
#include "../../../[002]Mediator/Mediator.h"


Text::Text()
{
	//文字フォント（作中で変更がないため直接入力）
	SetFontSize(20);
	tnl::AddFontTTF("font/Yomogi-Regular.ttf");
	ChangeFont("Yomogi", DX_CHARSET_DEFAULT);

	m_window_hdl
		= LoadGraph("graphics/ui/message/window.png");
}

Text::~Text()
{
	DeleteGraph(m_window_hdl);
}

void Text::Initialize()
{
	m_mediator->InitializeText();
}

void Text::Update(const float delta_time)
{
	UpdateWindow(delta_time);

	m_mediator->UpdateText(delta_time);
}

void Text::Draw(std::shared_ptr<dxe::Camera> camera)
{
	DrawWindow();

	m_mediator->DrawTextMessage();
}

void Text::UpdateWindow(const float delta_time)
{
	// 描画開始
	if (!m_mediator->GetIsTextDrawEnd())
	{
		m_window_alpha += delta_time * m_alpha_speed;

		// 255 : 完全不透明
		if (m_window_alpha > 255)
		{
			m_window_alpha = 255;
		}
	}
	// 描画終了
	else
	{
		// プレイヤーとパートナーをスライドアウト
		m_mediator->SetGraphIsSlidOutPlayer(true);
		m_mediator->SetGraphIsSlidOutPartner(true);

		m_window_alpha -= delta_time * m_alpha_speed;

		// 0 : 完全透明
		if (m_window_alpha < 0)
		{
			m_window_alpha = 0;
		}
	}
}

void Text::DrawWindow()
{
	int start_x = 490;
	int start_y = 500;

	// アルファブレンドを設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_window_alpha);

	// alphaが0より大きい場合のみウィンドウ描画
	if (m_window_alpha > 0)
	{
		DrawExtendGraph(start_x, start_y
						, start_x + 300, start_y + 200
						, m_window_hdl, TRUE);
	}

	// アルファブレンドを解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
