#include <filesystem>
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[005]Message/[001]CharaGraph/CharaGraph.h"
#include "ScreenShot.h"


ScreenShot::~ScreenShot() 
{
	// �n���h���̉��
	DeleteGraph(m_screen_hdl);
	m_chara_graph.clear();
}

void ScreenShot::SaveScreenShot()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))
	{
		m_chara_graph = m_mediator->GetCharaGraphLoadInfo();

		// �ۑ�����X�N���[���̍쐬�i�擾�j
		m_screen_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, false);

		// �ۑ�����X�N���[���̐ݒ�
		SetDrawScreen(m_screen_hdl);

		// �X�^���v�摜�̐ݒ�
		CharaGraph::sGraphInfo player_graph = m_chara_graph[0];
		CharaGraph::sGraphInfo partner_graph = m_chara_graph[1];

		// �X�^���v�摜��ǉ�
		DrawGraph(m_chara_graph[0].s_graph_pos.x
				  , m_chara_graph[0].s_graph_pos.y
				  , m_chara_graph[0].s_graph_hdl, TRUE);

		// �ŏI�I�ȃX�N���[���V���b�g���t�@�C���ɕۑ�
		std::string final_path
			= GetNextFileName(m_directry, m_base_name);

		// �ŏI�摜��ۑ�
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

    // �f�B���N�g�������݂��Ȃ��ꍇ�͍쐬
    std::filesystem::path dir_path 
		= std::filesystem::current_path() / m_directry;
    
	std::filesystem::create_directories(dir_path);

    // �f�B���N�g�����̃t�@�C�����C�e���[�V����
    for (auto& p : std::filesystem::directory_iterator(dir_path))
    {
        std::string file_name = p.path().filename().string();

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