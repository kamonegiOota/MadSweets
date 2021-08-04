/*!
@file FixedBox.cpp
@brief FixedBox実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "FixedBox.h"

#include "PointLight.h"
#include "PNTPointDraw.h"

namespace basecross {

    void FixedBox::OnCreate()
    {
        StageObject::OnCreate();

        auto coll = AddComponent<CollisionObb>();
        coll->SetFixed(true);
        coll->SetMakedSize(0.95f);

        AddTag(L"FixedBox");
        AddTag(L"Wall");
        coll->AddExcludeCollisionTag(L"FixedBox");

        vector<VertexPositionNormalTexture> vertices;
        vector<uint16_t> indices;
        MeshUtill::CreateCube(1.0f, vertices, indices);

        float UCount = m_scale.x; /// m_UPic;
        float VCount = m_scale.z; /// m_VPic;
        float YVCount = m_scale.y;

        for (size_t i = 0; i < vertices.size(); i++) {
            //上面
            float TopBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
            //下面
            float BottomBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
            //左横面
            float LeftSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(-1, 0, 0));
            //右横面
            float RightSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(1, 0, 0));
            //手前横面
            float ForeSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, -1));
            //奥横面
            float BackSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, 1));
            if (TopBetween < 0.01f || BottomBetween < 0.01f) {
                //上下面の処理
                if (vertices[i].textureCoordinate.x >= 1.0f) {
                    vertices[i].textureCoordinate.x = UCount;
                }
                if (vertices[i].textureCoordinate.y >= 1.0f) {
                    vertices[i].textureCoordinate.y = VCount;
                }
            }
            else {
                //それ以外（つまり横面）
                if (vertices[i].textureCoordinate.x >= 1.0f) {
                    //zに長いかxに長いかを判断
                    if (LeftSideBetween < 0.01f || RightSideBetween < 0.01f) {
                        vertices[i].textureCoordinate.x = m_scale.z;
                    }
                    else {
                        vertices[i].textureCoordinate.x = m_scale.x;
                    }
                }

                if (vertices[i].textureCoordinate.y >= 1.0f) {
                    vertices[i].textureCoordinate.y = YVCount;
                }
            }
        }

        //描画コンポーネントの追加
        //auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        auto PtrDraw = AddComponent<PNTPointDraw>();
        //PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->CreateOriginalMesh(vertices, indices);

        PtrDraw->SetOriginalMeshUse(true);
        //描画コンポーネントに形状（メッシュ）を設定
        PtrDraw->SetOwnShadowActive(true);
        //描画コンポーネントテクスチャの設定
        if (m_texture != L"") {
            PtrDraw->SetTextureResource(m_texture);
        }
        //タイリング設定
        PtrDraw->SetSamplerState(SamplerState::LinearWrap);

        m_vertices = vertices;
        m_indices = indices;

    }

    void FixedBox::OnUpdate()
    {

    }

}