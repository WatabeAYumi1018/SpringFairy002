#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"



void TextDraw::Update(const float delta_time)
{
    m_mediator->GetTextsLoadLane();

    // テキストを取得する
    m_lane_text_data = m_mediator->GetTextsLoadForLane();

    tnl_sequence_.update(delta_time);
}

void TextDraw::Draw()
{
    int draw_x = 500;
    int draw_y = 500;
    int draw_y_interval = 50;

    // 現在表示するべきテキスト行を決定
    std::string line_to_draw_first
        = m_lane_text_data[m_now_text_id].s_text_line_first;
    // 2行目が存在し、かつ描画タイミングであれば描画
    std::string line_to_draw_second
        = m_lane_text_data[m_now_text_id].s_text_line_second;

    // 1行目のテキストを描画
    DrawStringEx(draw_x, draw_y, 1, line_to_draw_first.substr(0, m_index_char_first).c_str());

    DrawStringEx(draw_x, draw_y + draw_y_interval, 1, line_to_draw_second.substr(0, m_index_char_second).c_str());    
}

// 一行一文字ずつ表示する処理
void TextDraw::DrawTextData(const float delta_time, std::string text_line)
{
    m_elapsed_time_last_char += delta_time;

    if (m_elapsed_time_last_char >= m_char_interval)
    {
        m_elapsed_time_last_char = 0.0f;

        // 文字を1つずつ表示
        if (m_now_text_lane_num == 0)
        {
            m_index_char_first += 2;
        }
        else
        {
            m_index_char_second += 2;
        }
    }

    if (m_index_char_first > text_line.length() * 2)
    {
        if (m_now_text_lane_num == 0)
        {
            m_now_text_lane_num= 1;
        }
        
        if(m_index_char_second > text_line.length() * 2)
        {
            // 描画を停止し、ウェイトタイムに入る
            m_is_interval = true;
        }
    }
}

// 2行の文字の表示が全て終えた後の待機時間
void TextDraw::SetNextText(const float delta_time)
{
    // 次の行の文字表示までの待機時間
    float wait_time = 0.5f;

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
		DrawTextData(delta_time, m_lane_text_data[m_now_text_id].s_text_line_first);
    });

    TNL_SEQ_CO_END;
}

bool TextDraw::SeqSetNextText(const float delta_time)
{
    if (!m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }

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


//bool TextDraw::IsTextEnd()
//{
//    // 現在の行がidのサイズを越える（描画終了）
//    return m_index_line >= m_text_lines.size();
//}
//
//void TextDraw::SetNextText(float delta_time, std::vector<std::string> id)
//{
//    // 次のテキストの表示までの待機時間
//
//	float wait_time = 2.0f;
//
//	m_elasped_time += delta_time;
//
//	if (m_elasped_time >= wait_time)
//	{
//		m_now_text_index++;
//
//		m_elasped_time = 0.0f;
//
//		if (m_now_text_index < id.size())
//		{
//			// 次のテキストIDの準備
//			
//		}
//	}
//}
//



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
