#include <random>
#include <algorithm>
#include "ModelPool.h"


void ModelPool::AddModel(std::shared_ptr<Model>& model)
{
    m_models.emplace_back(model);
}

//
//void ModelPool::IsActivateAllModels()
//{
//    for (auto& model : m_models)
//    {
//        // 与えられた世界タイプに一致するモデルのみアクティブ化
//        if (model->GetWorldType() == worldType)
//        {
//            model->SetIsWorldActive(true);
//        }
//        else
//        {
//            model->SetIsWorldActive(false);
//        }
//    }
//
//}

//std::shared_ptr<Model> ModelPool::GetRandomModel(Model::eWorldType world_type)
//{
//    // ベクターをクリア
//    m_filtered_models.clear();
//
//    for (auto& model : m_models)
//    {
//        if (model->GetWorldType() == world_type)
//        {
//            m_filtered_models.emplace_back(model);
//        }
//    }
//
//    if (m_filtered_models.empty())
//    {
//        return nullptr;
//    }
//
//    // 乱数生成器のインスタンスを一度だけ作成する
//    static std::random_device rnd;
//
//    static std::mt19937 gen(rnd());
//
//    std::uniform_int_distribution<> rand(0, m_filtered_models.size() - 1);
//
//    return m_filtered_models[rand(gen)];
//}
//
//void ModelPool::IsActivateAllModels(Model::eWorldType worldType)
//{
//    for (auto& model : m_models)
//    {
//        // 与えられた世界タイプに一致するモデルのみアクティブ化
//        if (model->GetWorldType() == worldType)
//        {
//            model->SetIsWorldActive(true);
//        }
//        else
//        {
//            model->SetIsWorldActive(false);
//        }
//    }
//}
//

//// モデルが存在する場合はランダムにモデルを取得
//
//// 乱数生成
//// random_device : ハードウェアの乱数生成器
//std::random_device rnd;
//// 乱数生成器に乱数シードを与える
//// 乱数生成器 : 乱数を生成する機械のこと
//// 乱数シード : 乱数生成器の初期値
//// mt19937 : メルセンヌ・ツイスター法による乱数生成器
//std::mt19937 gen(rnd());
//// 乱数の範囲を指定
//// uniform_int_distribution : 一様整数分布
//// 一様整数分布 : どの値も同じ確率で出現するように整数を生成する
//// 引数 : 乱数の最小値, 乱数の最大値
//std::uniform_int_distribution<> rand(0, m_filtered_models.size() - 1);
//// 乱数を生成
//return m_filtered_models[rand(gen)];
