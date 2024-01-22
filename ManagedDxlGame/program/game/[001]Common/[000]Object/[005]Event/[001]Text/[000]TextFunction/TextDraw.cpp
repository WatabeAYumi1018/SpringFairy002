#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"


void TextDraw::ResetText()
{    
    // 行のインデックスを初期化
    m_index_line = 0;
    // 文字のインデックスを初期化
    m_index_char = 0;
    // 表示間隔のカウントを初期化
    m_elapsed_time_last_char = 0.0f;
}

void TextDraw::Update(float delta_time)
{
    // 現在のレーンに対応する全IDの全テキストを取得
    m_text_line = m_mediator->GetTextsLoadLane();

    // テキストの表示が終了している場合は何もしない
    if (m_index_line < m_text_line.size())
    {
        // 1文字ずつ表示する間隔を経過時間で計算
        m_elapsed_time_last_char += delta_time;

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
}

void TextDraw::Draw()
{
    int draw_x = 300;
    int draw_y = 530;
    int draw_y_interval = 60;

    // 現在の行がidのサイズを越える（描画終了）
    for (int i = 0; i <= m_index_line && i < m_text_line.size(); i++)
    {
        // 現在の行の文字列を取得
        std::string line_to_draw = m_text_line[i];

        if (i == m_index_line) 
        {
            // 描画中の文字のみ表示
            line_to_draw = line_to_draw.substr(0, m_index_char);
        }

        // 1 : 黒色の文字
        DrawStringEx( draw_x, draw_y + draw_y_interval * i
                      ,1, line_to_draw.c_str());
    }
}

bool TextDraw::IsTextEnd()
{
    // 現在の行がidのサイズを越える（描画終了）
    return m_index_line >= m_text_line.size();
}


/*

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
