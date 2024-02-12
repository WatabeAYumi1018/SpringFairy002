#include <filesystem>
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"
#include "ScreenShot.h"


ScreenShot::ScreenShot()
{
	LoadBack();
}

ScreenShot::~ScreenShot() 
{
    DeleteGraph(m_back_hdl);
}

void ScreenShot::LoadBack()
{
    m_back_hdl = LoadGraph("graphics/event/flower_arch.jpg");
}

void ScreenShot::SaveScreenShot()
{
    // テキストで"ハイチーズ"の掛け声の後にスクリーンショットを撮る
    if (!m_is_shot 
        && (m_mediator->GetEventLane().s_id == 13
            || tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)))
    {
        // スクリーンショットをファイルに保存
        std::string final_path 
            = GetNextFileName(m_directry, m_base_name);

        // 画像を保存
        SaveDrawScreenToPNG(0, 0, DXE_WINDOW_WIDTH
                            , DXE_WINDOW_HEIGHT, final_path.c_str());

        m_is_shot = true;
    }

    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))
    {
		m_is_shot = false;
	}
}

void ScreenShot::ShowScreenShot()
{
    std::string latestFilePath = GetLatestFileName();

    // 最新のファイルが見つからない
    if (latestFilePath.empty())
    {
        return;
    }

    int image_hdl = LoadGraph(latestFilePath.c_str());

    // 画像のロードに失敗
    if (image_hdl == -1)
    {
        return;
    }

    // 画像の中心を基点にして回転させる
    int image_width, image_height;

    GetGraphSize(image_hdl, &image_width, &image_height);
    // 描画モードを設定して画質を向上
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    // 背景の描画
    DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
                    , m_back_hdl, TRUE);

    DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2
                  , 1, tnl::ToRadian(10), image_hdl, TRUE, FALSE);

    // 画像ハンドルの解放
    DeleteGraph(image_hdl);
}

std::string ScreenShot::GetNextFileName(const std::string& directry
										, const std::string& base_name)
{
    int max_num = 0;

    // ディレクトリが存在しない場合は作成
    // std::filesystem::path : ファイルシステムのパスを表す
    // std::filesystem::current_path() : 現在の作業ディレクトリを取得
    std::filesystem::path dir_path 
		= std::filesystem::current_path() / m_directry;

    // std::filesystem::create_directories : ディレクトリを作成
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

std::string ScreenShot::GetLatestFileName() 
{
    int max_num = -1;
    std::string latest_file_name;

    std::filesystem::path dir_path 
        = std::filesystem::current_path() / m_directry;

    if (!std::filesystem::exists(dir_path) 
        || !std::filesystem::is_directory(dir_path))
    {
        // ディレクトリが存在しない場合は空文字を返す
        return ""; 
    }

    for (auto& p : std::filesystem::directory_iterator(dir_path)) 
    {
        std::string file_name = p.path().filename().string();

        if (file_name.rfind(m_base_name, 0)
            == 0 && file_name.find(".png") != std::string::npos)
        {
            int num = std::stoi(file_name.substr(m_base_name.size()
                                , file_name.size() - m_base_name.size() - 4));
            
            if (num > max_num) 
            {
                max_num = num;
                latest_file_name = file_name;
            }
        }
    }

    if (latest_file_name.empty())
    {
        return "";
    }

    return (dir_path / latest_file_name).string();
}