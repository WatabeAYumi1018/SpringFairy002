#include <filesystem>
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[005]Message/[001]CharaGraph/CharaGraph.h"
#include "ScreenShot.h"


ScreenShot::~ScreenShot() 
{
	// ハンドルの解放
	DeleteGraph(m_screen_hdl);
	m_chara_graph.clear();
}

void ScreenShot::SaveScreenShot()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))
	{
		m_chara_graph = m_mediator->GetCharaGraphLoadInfo();

		// 保存するスクリーンの作成（取得）
		m_screen_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, false);

		// 保存するスクリーンの設定
		SetDrawScreen(m_screen_hdl);

		// スタンプ画像の設定
		CharaGraph::sGraphInfo player_graph = m_chara_graph[0];
		CharaGraph::sGraphInfo partner_graph = m_chara_graph[1];

		// スタンプ画像を追加
		DrawGraph(m_chara_graph[0].s_graph_pos.x
				  , m_chara_graph[0].s_graph_pos.y
				  , m_chara_graph[0].s_graph_hdl, TRUE);

		// 最終的なスクリーンショットをファイルに保存
		std::string final_path
			= GetNextFileName(m_directry, m_base_name);

		// 最終画像を保存
		SaveDrawScreenToPNG(0, 0
							, DXE_WINDOW_WIDTH
							, DXE_WINDOW_HEIGHT
							, final_path.c_str()
							, m_screen_hdl);
	}
}

std::string ScreenShot::GetNextFileName(const std::string& directry
										, const std::string& base_name)
{
    int max_num = 0;

    // ディレクトリが存在しない場合は作成
    std::filesystem::path dir_path 
		= std::filesystem::current_path() / m_directry;
    
	std::filesystem::create_directories(dir_path);

    // ディレクトリ内のファイルをイテレーション
    for (auto& p : std::filesystem::directory_iterator(dir_path))
    {
        std::string file_name = p.path().filename().string();

        // ファイルが基本名で始まり、.pngで終わるかチェック
        if (file_name.rfind(base_name, 0) == 0 
			&& file_name.find(".png") != std::string::npos) 
        {   
            // ファイル名から数字を抽出
            int num = std::stoi(file_name.substr(base_name.size()
								, file_name.size() - base_name.size() - 4)); 
            
            // 現在のファイル番号がより高い場合は最大番号を更新
            if (num > max_num) max_num = num;
        }
    }

    // 新しいファイル名を構築
    std::string new_file_name 
		= base_name + std::to_string(max_num + 1) + ".png";

    // 新しいファイルへの相対パスを返す
    return (dir_path / new_file_name).string();
}