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

    m_chara_graph.clear();
}

void ScreenShot::LoadBack()
{
    m_back_hdl = LoadGraph("graphics/gate/flower.jpg");
}

void ScreenShot::SaveScreenShot()
{
    // テキストで"ハイチーズ"の掛け声の後にスクリーンショットを撮る
    if (!m_is_shot 
        && (m_mediator->GetCurrentEventLane().s_id == 13
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
    // 最新のファイルパスを取得
    std::string latest_file_path = GetLatestFileName();

    // 最新のファイルが見つからない
    if (latest_file_path.empty())
    {
        return;
    }

    // 最新の画像をロード
    int image_hdl = LoadGraph(latest_file_path.c_str());

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

    // スクリーンショット画像を中心で回転させて描画
    // 2 : 中心座標(変更なしの固定値)
    DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2
                  , 1, tnl::ToRadian(10.0f), image_hdl, TRUE, FALSE);

    m_mediator->SetEnterGraphIsActive(true);

    // 画像ハンドルの解放
    DeleteGraph(image_hdl);
}

std::string ScreenShot::GetNextFileName(const std::string& directry
										, const std::string& base_name)
{
    int max_num = 0;

    // ディレクトリが存在しない場合は作成
    std::filesystem::path dir_path 
		= std::filesystem::current_path() / m_directry;

    // ディレクトリを作成
	std::filesystem::create_directories(dir_path);

    // ディレクトリ内のファイルをイテレーション
    for (std::filesystem::directory_iterator it(dir_path); it != std::filesystem::end(it); ++it)
    {
        std::filesystem::directory_entry entry = *it;
        // ファイル名を取得
        std::string file_name = entry.path().filename().string();

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

    // ディレクトリが存在しない場合は作成
    std::filesystem::path dir_path
        = std::filesystem::current_path() / m_directry;

    // ディレクトリが存在しない場合は空文字を返す
    if (!std::filesystem::exists(dir_path) 
        || !std::filesystem::is_directory(dir_path))
    {
        return ""; 
    }

    // ディレクトリ内のファイルをイテレーション
    for (std::filesystem::directory_iterator it(dir_path); it != std::filesystem::end(it); ++it)
    {
        std::filesystem::directory_entry entry = *it;
        // ファイル名を取得
        std::string file_name = entry.path().filename().string();

        // ファイルが基本名で始まり、.pngで終わるかチェック
        if (file_name.rfind(m_base_name, 0) == 0 && 
            file_name.find(".png") != std::string::npos)
        {
            // ファイル名から数字を抽出
            int num = std::stoi(file_name.substr(m_base_name.size()
                                , file_name.size() - m_base_name.size() - 4));
            
            // 現在のファイル番号がより高い場合は最大番号を更新
            if (num > max_num) 
            {
                max_num = num;
                latest_file_name = file_name;
            }
        }
    }

    // 最新のファイルが見つからない場合は空文字を返す
    if (latest_file_name.empty())
    {
        return "";
    }

    // 最新のファイルへの相対パスを返す
    return (dir_path / latest_file_name).string();
}