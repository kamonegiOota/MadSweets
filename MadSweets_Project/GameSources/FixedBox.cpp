/*!
@file FixedBox.cpp
@brief FixedBox����
�S���F�ێR�T��
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
            //���
            float TopBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
            //����
            float BottomBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
            //������
            float LeftSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(-1, 0, 0));
            //�E����
            float RightSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(1, 0, 0));
            //��O����
            float ForeSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, -1));
            //������
            float BackSideBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, 1));
            if (TopBetween < 0.01f || BottomBetween < 0.01f) {
                //�㉺�ʂ̏���
                if (vertices[i].textureCoordinate.x >= 1.0f) {
                    vertices[i].textureCoordinate.x = UCount;
                }
                if (vertices[i].textureCoordinate.y >= 1.0f) {
                    vertices[i].textureCoordinate.y = VCount;
                }
            }
            else {
                //����ȊO�i�܂艡�ʁj
                if (vertices[i].textureCoordinate.x >= 1.0f) {
                    //z�ɒ�����x�ɒ������𔻒f
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

        //�`��R���|�[�l���g�̒ǉ�
        //auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        auto PtrDraw = AddComponent<PNTPointDraw>();
        //PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->CreateOriginalMesh(vertices, indices);

        PtrDraw->SetOriginalMeshUse(true);
        //�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
        PtrDraw->SetOwnShadowActive(true);
        //�`��R���|�[�l���g�e�N�X�`���̐ݒ�
        if (m_texture != L"") {
            PtrDraw->SetTextureResource(m_texture);
        }
        //�^�C�����O�ݒ�
        PtrDraw->SetSamplerState(SamplerState::LinearWrap);

        m_vertices = vertices;
        m_indices = indices;

    }

    void FixedBox::OnUpdate()
    {

    }

}