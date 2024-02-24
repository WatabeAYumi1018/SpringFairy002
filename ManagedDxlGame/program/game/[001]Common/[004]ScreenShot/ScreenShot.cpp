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
    // �e�L�X�g��"�n�C�`�[�Y"�̊|�����̌�ɃX�N���[���V���b�g���B��
    if (!m_is_shot 
        && (m_mediator->GetCurrentEventLane().s_id == 13
            || tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)))
    {
        // �X�N���[���V���b�g���t�@�C���ɕۑ�
        std::string final_path 
            = GetNextFileName(m_directry, m_base_name);

        // �摜��ۑ�
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
    // �ŐV�̃t�@�C���p�X���擾
    std::string latest_file_path = GetLatestFileName();

    // �ŐV�̃t�@�C����������Ȃ�
    if (latest_file_path.empty())
    {
        return;
    }

    // �ŐV�̉摜�����[�h
    int image_hdl = LoadGraph(latest_file_path.c_str());

    // �摜�̃��[�h�Ɏ��s
    if (image_hdl == -1)
    {
        return;
    }

    // �摜�̒��S����_�ɂ��ĉ�]������
    int image_width, image_height;

    GetGraphSize(image_hdl, &image_width, &image_height);

    // �`�惂�[�h��ݒ肵�ĉ掿������
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    // �w�i�̕`��
    DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
                    , m_back_hdl, TRUE);

    // �X�N���[���V���b�g�摜�𒆐S�ŉ�]�����ĕ`��
    // 2 : ���S���W(�ύX�Ȃ��̌Œ�l)
    DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2
                  , 1, tnl::ToRadian(10.0f), image_hdl, TRUE, FALSE);

    m_mediator->SetEnterGraphIsActive(true);

    // �摜�n���h���̉��
    DeleteGraph(image_hdl);
}

std::string ScreenShot::GetNextFileName(const std::string& directry
										, const std::string& base_name)
{
    int max_num = 0;

    // �f�B���N�g�������݂��Ȃ��ꍇ�͍쐬
    std::filesystem::path dir_path 
		= std::filesystem::current_path() / m_directry;

    // �f�B���N�g�����쐬
	std::filesystem::create_directories(dir_path);

    // �f�B���N�g�����̃t�@�C�����C�e���[�V����
    for (std::filesystem::directory_iterator it(dir_path); it != std::filesystem::end(it); ++it)
    {
        std::filesystem::directory_entry entry = *it;
        // �t�@�C�������擾
        std::string file_name = entry.path().filename().string();

        // �t�@�C������{���Ŏn�܂�A.png�ŏI��邩�`�F�b�N
        if (file_name.rfind(base_name, 0) == 0 
			&& file_name.find(".png") != std::string::npos) 
        {   
            // �t�@�C�������琔���𒊏o
            int num = std::stoi(file_name.substr(base_name.size()
								, file_name.size() - base_name.size() - 4)); 
            
            // ���݂̃t�@�C���ԍ�����荂���ꍇ�͍ő�ԍ����X�V
            if (num > max_num) max_num = num;
        }
    }

    // �V�����t�@�C�������\�z
    std::string new_file_name 
		= base_name + std::to_string(max_num + 1) + ".png";

    // �V�����t�@�C���ւ̑��΃p�X��Ԃ�
    return (dir_path / new_file_name).string();
}

std::string ScreenShot::GetLatestFileName() 
{
    int max_num = -1;

    std::string latest_file_name;

    // �f�B���N�g�������݂��Ȃ��ꍇ�͍쐬
    std::filesystem::path dir_path
        = std::filesystem::current_path() / m_directry;

    // �f�B���N�g�������݂��Ȃ��ꍇ�͋󕶎���Ԃ�
    if (!std::filesystem::exists(dir_path) 
        || !std::filesystem::is_directory(dir_path))
    {
        return ""; 
    }

    // �f�B���N�g�����̃t�@�C�����C�e���[�V����
    for (std::filesystem::directory_iterator it(dir_path); it != std::filesystem::end(it); ++it)
    {
        std::filesystem::directory_entry entry = *it;
        // �t�@�C�������擾
        std::string file_name = entry.path().filename().string();

        // �t�@�C������{���Ŏn�܂�A.png�ŏI��邩�`�F�b�N
        if (file_name.rfind(m_base_name, 0) == 0 && 
            file_name.find(".png") != std::string::npos)
        {
            // �t�@�C�������琔���𒊏o
            int num = std::stoi(file_name.substr(m_base_name.size()
                                , file_name.size() - m_base_name.size() - 4));
            
            // ���݂̃t�@�C���ԍ�����荂���ꍇ�͍ő�ԍ����X�V
            if (num > max_num) 
            {
                max_num = num;
                latest_file_name = file_name;
            }
        }
    }

    // �ŐV�̃t�@�C����������Ȃ��ꍇ�͋󕶎���Ԃ�
    if (latest_file_name.empty())
    {
        return "";
    }

    // �ŐV�̃t�@�C���ւ̑��΃p�X��Ԃ�
    return (dir_path / latest_file_name).string();
}