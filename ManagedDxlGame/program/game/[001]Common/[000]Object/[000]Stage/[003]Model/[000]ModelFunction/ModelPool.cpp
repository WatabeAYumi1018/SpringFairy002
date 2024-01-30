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
//        // �^����ꂽ���E�^�C�v�Ɉ�v���郂�f���̂݃A�N�e�B�u��
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
//    // �x�N�^�[���N���A
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
//    // ����������̃C���X�^���X����x�����쐬����
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
//        // �^����ꂽ���E�^�C�v�Ɉ�v���郂�f���̂݃A�N�e�B�u��
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

//// ���f�������݂���ꍇ�̓����_���Ƀ��f�����擾
//
//// ��������
//// random_device : �n�[�h�E�F�A�̗���������
//std::random_device rnd;
//// ����������ɗ����V�[�h��^����
//// ���������� : �����𐶐�����@�B�̂���
//// �����V�[�h : ����������̏����l
//// mt19937 : �����Z���k�E�c�C�X�^�[�@�ɂ�闐��������
//std::mt19937 gen(rnd());
//// �����͈̔͂��w��
//// uniform_int_distribution : ��l�������z
//// ��l�������z : �ǂ̒l�������m���ŏo������悤�ɐ����𐶐�����
//// ���� : �����̍ŏ��l, �����̍ő�l
//std::uniform_int_distribution<> rand(0, m_filtered_models.size() - 1);
//// �����𐶐�
//return m_filtered_models[rand(gen)];
