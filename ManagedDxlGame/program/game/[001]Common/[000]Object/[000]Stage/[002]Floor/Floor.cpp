#include "../../../[001]Camera/GameCamera.h"
#include "../[001]Lane/Lane.h"
#include "Floor.h"


Floor::Floor()
{
	int size = Lane::LANE_SIZE;

	// プレーンサイズ指定(float型に変換)
    float size_f = static_cast<float>(size);

	tnl::Vector3 mesh_size = { size_f,size_f,size_f };

	m_floor = dxe::Mesh::CreatePlaneMV(mesh_size);

	m_floor->setTexture(dxe::Texture::CreateFromFile("graphics/floor/lawn.png"));
	// プレーンを床とするため回転
	m_floor->rot_
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90.0f));
	// 座標を調整（Y座標を下げて地面に配置)
    float distance = static_cast<float> (Floor::DRAW_DISTANCE);

	m_floor->pos_ = { 0, distance, 0 };
}

void Floor::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // グリッドのサイズ
    int grid_size = 20; 
    // グリッドの半分のサイズ
    int half_grid_size = grid_size / 2; 
    // フロア間のスペース
    int spacing = Lane::LANE_SIZE;

    float distance = static_cast<float> (Floor::DRAW_DISTANCE);

    for (int i = -half_grid_size; i < half_grid_size; i++)
    {
        for (int j = -half_grid_size; j < half_grid_size; j++)
        {
            // 各フロアの座標を計算
            float x = static_cast<float> (i * spacing);
            float z = static_cast<float> (j * spacing);

            // フロアの位置を設定
            m_floor->pos_ = { x, distance, z };

            // フロアを描画
            m_floor->render(camera);
        }
    }
}

