#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"


TextDraw::~TextDraw()
{
	m_story_texts_all.clear();
	m_lane_text_data.clear();
}

void TextDraw::Initialize()
{
    m_story_texts_all = m_mediator->GetTextsLoadAll();
}

void TextDraw::Update(const float delta_time)
{
    UpdateTexts();

    // テキストが空の場合は更新しない
    if (m_lane_text_data.empty())
    {
        return;
    }

    tnl_sequence_.update(delta_time);
}

void TextDraw::Draw()
{
    // 空の場合は描画しない
    if (m_lane_text_data.empty())
    {
		return;
	}

    int start_x = 510;
    int start_y = 550;
    int draw_y_interval = 50;

    // 現在表示するべきテキスト行を決定
    std::string line_to_draw_first
        = m_lane_text_data[m_now_text_id].s_text_line_first;
    // 2行目が存在し、かつ描画タイミングであれば描画
    std::string line_to_draw_second
        = m_lane_text_data[m_now_text_id].s_text_line_second;

    // 1行目のテキストを描画
    DrawStringEx(start_x, start_y, 1
                 ,line_to_draw_first.substr(0, m_index_char_first).c_str());

    DrawStringEx(start_x, start_y + draw_y_interval, 1
                 ,line_to_draw_second.substr(0, m_index_char_second).c_str());
}

void TextDraw::UpdateTexts()
{
    Lane::sLaneEvent lane_event = m_mediator->GetCurrentEventLane();

    // テキスト描画をしないレーンIDの場合は処理を終了
    if (lane_event.s_id == -1
        || lane_event.s_id == 1
        || lane_event.s_id == 7
        || lane_event.s_id == 10
        || lane_event.s_id == 12
        || lane_event.s_id == 14)
    {
        return;
    }

    // 上記以外であれば描画を開始
    m_is_end = false;

    int lane_id = lane_event.s_id;

    m_lane_text_data.clear();

    // レーン番号に基づいてテキストデータを一括格納
    for (const Text::sTextData& story_text : m_story_texts_all)
    {
        if (story_text.s_lane_id == lane_id)
        {
            m_lane_text_data.emplace_back(story_text);
        }
    }
}

// 一行一文字ずつ表示する処理
void TextDraw::DrawTextData(const float delta_time
                            , std::string text_line_first
                            , std::string text_line_second)
{
    m_elapsed_time_last_char += delta_time * 1.5f;

    if (m_elapsed_time_last_char >= m_char_interval)
    {
        m_elapsed_time_last_char = 0.0f;

        // 文字を1つずつ表示
        if (m_now_text_lane_num == 0 
            && m_index_char_first < text_line_first.length() * 2)
        {
            m_index_char_first += 2;
        }
        else if (m_now_text_lane_num == 1 
            && m_index_char_second < text_line_second.length() * 2)
        {
            m_index_char_second += 2;
        }
    }

    // 両方の行の文字の描画が完了したかどうかをチェック
    if (m_index_char_first >= text_line_first.length() * 2 
        && m_now_text_lane_num == 0)
    {
        m_now_text_lane_num = 1;
        m_index_char_first = text_line_first.length() * 2; // 現在の行の長さを固定
    }

    if (m_index_char_second >= text_line_second.length() * 2 
        && m_now_text_lane_num == 1)
    {
        // 描画を停止し、ウェイトタイムに入る
        m_is_interval = true;
    }
}

// 2行の文字の表示が全て終えた後の待機時間
void TextDraw::SetNextText(const float delta_time)
{
    // 次の行の文字表示までの待機時間
    float wait_time = 0.5f;

    // 最後に描画された行が特定の文字を含むかチェック
    if (m_lane_text_data[m_now_text_id].s_text_line_second.find("Xボタン") != std::string::npos
        ||m_lane_text_data[m_now_text_id].s_text_line_second.find("Zボタン") != std::string::npos) 
    {
        // 操作説明の場合は待機時間を5倍
        wait_time *= 5;  
    }

    m_elasped_time += delta_time;

    // 一定時間経過した場合
    if (m_elasped_time >= wait_time)
    {
        // ウェイトタイムが経過した後の処理
        m_elasped_time = 0.0f;

        // 次のテキストIDへ
        m_now_text_id++;

        // 次のテキストの1行目から再開
        m_now_text_lane_num = 0;

        // 文字のインデックスをリセット
        m_index_char_first = 0;

        m_index_char_second = 0;

        m_is_interval = false;

        // 全てのIDが終了した場合、全てリセット
        if (m_now_text_id == m_lane_text_data.size())
        {
            m_now_text_id = 0;

            m_is_end = true;
        }
    }
}

bool TextDraw::SeqStop(const float delta_time)
{
    if (!m_is_end)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool TextDraw::SeqDrawTextData(const float delta_time)
{
    if (m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqSetNextText);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        // テキストIDが範囲内にあるかを確認
        if (m_now_text_id < m_lane_text_data.size())
        {
            DrawTextData(delta_time
                         , m_lane_text_data[m_now_text_id].s_text_line_first
                         , m_lane_text_data[m_now_text_id].s_text_line_second);
        }
        // 範囲外の場合は描画を停止
        else
        {
			m_is_end = true;
        }
    });

    TNL_SEQ_CO_END;
}

bool TextDraw::SeqSetNextText(const float delta_time)
{
    // ウェイトタイムが経過したら次のテキストIDへ
    if (!m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }
    // テキストの表示が終了している場合はStopへリセット
    if (m_is_end)
    {
        tnl_sequence_.change(&TextDraw::SeqStop);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        SetNextText(delta_time);
    });

    TNL_SEQ_CO_END;
}






/*
* 
* // テキストの表示が終了している場合は何もしない
    if (m_index_line < m_text_line.size())
    {
        // 1文字ずつ表示する間隔を経過時間で計算
        m_elapsed_time_last_char += delta_time * 2;

        // 1文字ずつ表示する間隔を超えた場合
        if (m_elapsed_time_last_char >= m_char_interval)
        {
            // 表示間隔のカウントを初期化
            m_elapsed_time_last_char = 0.0f;
        
            // 1文字ずつ表示(全角文字のため、2ずつ加算)
            m_index_char += 2;

            // 現在の行を全て表示したら、次の行に移行する
            if (m_index_char >= m_text_line[m_index_line].length())
            {
                m_index_line++;

                m_index_char = 0;
            } 
        }
    }
    // テキストの表示が終了している場合は値を初期化
    else
    {
        ResetText();
    }

std::string processed_line = line;
元データを保護するために、元データをコピーしてprocessed_lineに格納
元の文字列 line は sStoryText 構造体の一部であり、他の場所でも使われる可能性がある
直接 line を変更すると、他の場所での使用に影響を与える可能性がある
オリジナルのデータをそのままにしておき、加工用にはコピーを使用
→後で line を別の目的で再利用する場合や、元の文字列を変更せずに保持したい場合に便利

size_t : 非負整数（符号なし整数。負の値を持たない。０または正の整数のみ扱う）
主に配列のサイズやコレクション内の要素のインデックス（位置）を指定するのに使用

npos : string::nposは、string::find()やstring::rfind()の戻り値として使われる特別な値
文字列中に検索文字列が見つからなかった場合にstring::nposを返す
この値もsize_t型

*/
