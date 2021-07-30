/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "PNTPointDraw.h"

namespace basecross {

	//�R���X�^���g�o�b�t�@�ɓn�������p�����[�^�̂݋L�q����
	struct PNTPointDraw::Impl : public DrawObjectBase {
		//���_�ύX����ꍇ�̃��b�V���i�I���W�i���j
		shared_ptr<MeshResource> m_OriginalMeshResource;
		//�I���W�i�����b�V�����g�����ǂ���
		bool m_UseOriginalMeshResource;
		//�e�N�X�`�����\�[�X
		weak_ptr<TextureResource> m_TextureResource;
		//NormalMap�e�N�X�`��
		weak_ptr<TextureResource> m_NormalMapTextureResource;
		vector<weak_ptr<TextureResource>> m_NormalMapTextureResourceVec;
		//�G�~�b�V�u�F
		Col4 m_Emissive;
		//�f�t���[�Y�F
		Col4 m_Diffuse;
		//�����x
		float m_Alpha;
		//�X�y�L�����[�ƃp���[�F
		Col4 m_SpecularColorAndPower;
		//���C�e�B���O���邩�ǂ���
		bool m_LightingEnabled;
		//�s�N�Z�����C�e�B���O�����邩�ǂ���
		bool m_PreferPerPixelLighting;
		//�@���Ƀo�C�A�X�������邩�ǂ���
		bool m_BiasedNormals;
		//�A���r�G���g
		Col4 m_AmbientLightColor;
		//���C�g��MAX
		static const int MaxDirectionalLights = 3;
		//���C�g���L�����ǂ���
		bool m_LightEnabled[MaxDirectionalLights];
		//���C�g�̌���
		Vec3 m_LightDirection[MaxDirectionalLights];
		//���C�g�̃f�t���[�Y�F
		Col4 m_LightDiffuseColor[MaxDirectionalLights];
		//���C�g�̃X�y�L�����[�F
		Col4 m_LightSpecularColor[MaxDirectionalLights];
		//�t�H�O���L�����ǂ���
		bool m_FogEnabled;
		//�t�H�O�̊J�n�ʒu
		float m_FogStart;
		//�t�H�O�̏I���ʒu
		float m_FogEnd;
		//�t�H�O�F
		Col4 m_FogColor;
		//�t�H�O�x�N�g��
		Vec3 m_FogVector;
		//�e�𓊉e���邩�ǂ���
		bool m_OwnShadowActive;
		//���f���ɓ����Ă���Diffuse���g�����ǂ���
		bool m_ModelDiffusePriority;
		//���f���ɓ����Ă���Emissive���g�����ǂ���
		bool m_ModelEmissivePriority;
		//���f���ɓ����Ă���e�N�X�`�����g�����ǂ���
		bool m_ModelTextureEnabled;

		PNTPointDraw::Impl() :
			m_UseOriginalMeshResource(false),
			m_Emissive(0.0f, 0.0f, 0.0f, 0.0),
			m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
			m_Alpha(1.0f),
			m_SpecularColorAndPower(0.0f, 0.0f, 0.0f, 1.0f),
			m_LightingEnabled(false),
			m_PreferPerPixelLighting(false),
			m_BiasedNormals(false),
			m_AmbientLightColor(0, 0, 0, 0),
			m_FogEnabled(false),
			m_FogStart(-25.0f),
			m_FogEnd(-40.0f),
			m_FogColor(0.8f, 0.8f, 0.8f, 1.0f),
			m_FogVector(0.0, 0.0, 1.0f),
			m_OwnShadowActive(false),
			m_ModelDiffusePriority(true),
			m_ModelEmissivePriority(true),
			m_ModelTextureEnabled(true)
		{
			static const XMVECTORF32 defaultSpecular = { 1, 1, 1, 16 };
			static const bsm::Vec3 defaultLightDirection = { 0, -1, 0 };
			m_SpecularColorAndPower = defaultSpecular;
			for (int i = 0; i < MaxDirectionalLights; i++)
			{
				m_LightDirection[i] = defaultLightDirection;
				m_LightDiffuseColor[i] = g_XMZero;
				m_LightSpecularColor[i] = g_XMZero;
			}
		}
	};

	//void PNTPointDraw::DrawStatic2(const MeshPrimData& data) {
	//	auto Dev = App::GetApp()->GetDeviceResources();
	//	auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
	//	auto RenderState = Dev->GetRenderState();
	//	//NULL�̃V�F�[�_���\�[�X�̏���
	//	ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
	//	//�T���v���[�̏���
	//	ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
	//	//�e�I�u�W�F�N�g���ʏ���
	//	//�V�F�[�_�̐ݒ�
	//	//���_�V�F�[�_
	//	pD3D11DeviceContext->VSSetShader(T_VShader::GetPtr()->GetShader(), nullptr, 0);
	//	//�C���v�b�g���C�A�E�g�̐ݒ�
	//	pD3D11DeviceContext->IASetInputLayout(T_VShader::GetPtr()->GetInputLayout());
	//	//�s�N�Z���V�F�[�_
	//	pD3D11DeviceContext->PSSetShader(T_PShader::GetPtr()->GetShader(), nullptr, 0);
	//	//���C�g��ݒ�
	//	SetLightingParamaters(); //�K�v�Ȃ���������Ȃ�
	//	//�ʏ���
	//	BasicConstants BcCb  //�g�p����o�b�t�@�ɂ���ĕς��
	//	//�R���X�^���g�o�b�t�@�̍쐬
	//		SetConstants(BcCb, data);  //���ꂻ����������������
	//		//�e�N�X�`��
	//	auto shTex = GetTextureResource();
	//	if (shTex) {
	//		//�e�N�X�`��������
	//		BcCb.activeFlg.y = 1;
	//	}
	//	else {
	//		//�`��R���|�[�l���g�ɂ̓e�N�X�`�����Ȃ�
	//		if (shTex = data.m_TextureResource.lock()) {
	//			//�e�N�X�`��������
	//			BcCb.activeFlg.y = 1;
	//		}
	//		else {
	//			BcCb.activeFlg.y = 0;
	//		}
	//	}
	//	//�R���X�^���g�o�b�t�@�̍X�V
	//	//�o�b�t�@�̎O�m�͕ς��
	//	pD3D11DeviceContext->UpdateSubresource(CBBasic::GetPtr()->GetBuffer(), 0, nullptr, &BcCb, 0, 0);
	//	//�R���X�^���g�o�b�t�@�̐ݒ�
	//	ID3D11Buffer* pConstantBuffer = CBBasic::GetPtr()->GetBuffer();
	//	ID3D11Buffer* pNullConstantBuffer = nullptr;
	//	//���_�V�F�[�_�ɓn��
	//	pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//	//�s�N�Z���V�F�[�_�ɓn��
	//	pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
	//	//�X�g���C�h�ƃI�t�Z�b�g
	//	UINT stride = data.m_NumStride;
	//	UINT offset = 0;
	//	//�`����@�̃Z�b�g
	//	pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
	//	//���_�o�b�t�@�̃Z�b�g
	//	pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
	//	//�C���f�b�N�X�o�b�t�@�̃Z�b�g
	//	pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	//	//�e�����_�����O�X�e�[�g�̐ݒ�
	//	//�u�����h�X�e�[�g
	//	RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
	//	//�f�v�X�X�e���V���X�e�[�g
	//	RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
	//	//�e�N�X�`���ƃT���v���[
	//	if (shTex) {
	//		pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
	//		//�T���v���[��ݒ�
	//		RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
	//		//�@���}�b�v
	//		if (GetNormalMapTextureResource()) {
	//			if (IsOwnShadowActive()) {
	//				//�Q�Ԗڂɓ����
	//				pD3D11DeviceContext->PSSetShaderResources(2, 1, GetNormalMapTextureResource()->GetShaderResourceView().GetAddressOf());
	//				//�T���v���[��ݒ�
	//				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 2);
	//			}
	//			else {
	//				//1�Ԗڂɓ����
	//				pD3D11DeviceContext->PSSetShaderResources(1, 1, GetNormalMapTextureResource()->GetShaderResourceView().GetAddressOf());
	//				//�T���v���[��ݒ�
	//				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 1);
	//			}
	//		}
	//	}
	//	else {
	//		//�V�F�[�_�[���\�[�X���N���A
	//		pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
	//		//�T���v���[���N���A
	//		RenderState->SetSamplerAllClear(pD3D11DeviceContext);
	//	}
	//	//�e�ƃT���v���[
	//	if (IsOwnShadowActive()) {
	//		//�V���h�E�}�b�v�̃����_���[�^�[�Q�b�g
	//		auto ShadowmapPtr = Dev->GetShadowMapRenderTarget();
	//		ID3D11ShaderResourceView* pShadowSRV = ShadowmapPtr->GetShaderResourceView();
	//		pD3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);
	//		//�V���h�E�}�b�v�T���v���[
	//		ID3D11SamplerState* pShadowSampler = RenderState->GetComparisonLinear();
	//		pD3D11DeviceContext->PSSetSamplers(1, 1, &pShadowSampler);
	//	}
	//	//���X�^���C�U�X�e�[�g�ƕ`��
	//	if (GetRasterizerState() == RasterizerState::DoubleDraw) {
	//		//���������p
	//		//���X�^���C�U�X�e�[�g(���`��)
	//		pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
	//		//�`��
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//		//���X�^���C�U�X�e�[�g�i�\�`��j
	//		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
	//		//�`��
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//	}
	//	else {
	//		RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
	//		//�`��
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//	}
	//	//��n��
	//	//Dev->InitializeStates();
	//}
	

	//�����������Ő��������R���X�^���g�o�b�t�@�p�̃R���X�g���N�g�ɕς���B
	//void PNTPointDraw::SetConstants2(BasicConstants& BcCb, const MeshPrimData& data) {
	//	//�s��̒�`
	//	auto PtrTrans = GetGameObject()->GetComponent<Transform>();
	//	//�J�����𓾂�
	//	auto CameraPtr = GetGameObject()->OnGetDrawCamera();
	//	//���C�g�𓾂�
	//	auto PtrLightObj = GetGameObject()->GetStage()->GetLight();
	//	auto PtrMultiLight = dynamic_pointer_cast<MultiLight>(PtrLightObj);
	//	if (PtrMultiLight) {
	//		//�}���`���C�g������
	//		BcCb.activeFlg.x = 3;
	//	}
	//	else {
	//		//�����ł͂Ȃ�
	//		BcCb.activeFlg.x = 1;
	//	}
	//	auto StageLight = GetGameObject()->OnGetDrawLight();
	//	//���[���h�s��
	//	bsm::Mat4x4 world;
	//	if (data.m_UseMeshToTransformMatrix) {
	//		world = data.m_MeshToTransformMatrix * GetMeshToTransformMatrix();
	//		world *= PtrTrans->GetWorldMatrix();
	//	}
	//	else {
	//		world = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
	//	}
	//	//�r���[�s��
	//	bsm::Mat4x4 view = CameraPtr->GetViewMatrix();
	//	//�ˉe�s��
	//	bsm::Mat4x4 projection = CameraPtr->GetProjMatrix();

	//	//�s��̐ݒ�
	//	auto worldView = world * view;
	//	BcCb.worldViewProj = XMMatrixTranspose(XMMatrixMultiply(worldView, projection));

	//	//�t�H�O�̐ݒ�
	//	if (IsFogEnabled())
	//	{
	//		auto start = GetFogStart();
	//		auto end = GetFogEnd();
	//		if (start == end)
	//		{
	//			// Degenerate case: force everything to 100% fogged if start and end are the same.
	//			static const XMVECTORF32 fullyFogged = { 0, 0, 0, 1 };
	//			BcCb.fogVector = fullyFogged;
	//		}
	//		else
	//		{
	//			XMMATRIX worldViewTrans = worldView;
	//			// _13, _23, _33, _43
	//			XMVECTOR worldViewZ = XMVectorMergeXY(XMVectorMergeZW(worldViewTrans.r[0], worldViewTrans.r[2]),
	//				XMVectorMergeZW(worldViewTrans.r[1], worldViewTrans.r[3]));
	//			XMVECTOR wOffset = XMVectorSwizzle<1, 2, 3, 0>(XMLoadFloat(&start));
	//			BcCb.fogVector = (worldViewZ + wOffset) / (start - end);
	//		}
	//		BcCb.fogColor = GetFogColor();
	//	}
	//	else
	//	{
	//		BcCb.fogVector = g_XMZero;
	//		BcCb.fogColor = g_XMZero;

	//	}
	//	//���C�g�̐ݒ�
	//	if (IsLightingEnabled())
	//	{
	//		if (BcCb.activeFlg.x == 1) {
	//			BcCb.lightDirection[0] = GetLightDirection(0);
	//			BcCb.lightDiffuseColor[0] = GetLightDiffuseColor(0);
	//			BcCb.lightSpecularColor[0] = GetLightSpecularColor(0);
	//		}
	//		else {
	//			for (int i = 0; i < GetMaxDirectionalLights(); i++) {
	//				if (IsLightEnabled(i)) {
	//					BcCb.lightDirection[i] = GetLightDirection(i);
	//					BcCb.lightDiffuseColor[i] = GetLightDiffuseColor(i);
	//					BcCb.lightSpecularColor[i] = GetLightSpecularColor(i);
	//				}
	//			}
	//		}
	//		BcCb.world = XMMatrixTranspose(world);

	//		XMMATRIX worldInverse = XMMatrixInverse(nullptr, world);

	//		BcCb.worldInverseTranspose[0] = worldInverse.r[0];
	//		BcCb.worldInverseTranspose[1] = worldInverse.r[1];
	//		BcCb.worldInverseTranspose[2] = worldInverse.r[2];


	//		XMMATRIX viewInverse = XMMatrixInverse(nullptr, view);

	//		BcCb.eyePosition = viewInverse.r[3];
	//	}
	//	XMVECTOR diffuse = GetDiffuse();
	//	XMVECTOR alphaVector = XMVectorReplicate(GetAlpha());
	//	XMVECTOR emissiveColor = GetEmissive();
	//	XMVECTOR ambientLightColor = GetAmbientLightColor();
	//	if (IsLightingEnabled())
	//	{
	//		// Merge emissive and ambient light contributions.
	//		BcCb.emissiveColor = (emissiveColor + ambientLightColor * diffuse) * alphaVector;
	//		BcCb.specularColorAndPower = GetSpecularColorAndPower();
	//	}
	//	else
	//	{
	//		BcCb.activeFlg.x = 0;
	//		// Merge diffuse and emissive light contributions.
	//		diffuse += emissiveColor;
	//		BcCb.specularColorAndPower = GetSpecularColorAndPower();
	//	}
	//	// xyz = diffuse * alpha, w = alpha.
	//	BcCb.diffuseColor = XMVectorSelect(alphaVector, diffuse * alphaVector, g_XMSelect1110);

	//	//�e�p
	//	if (GetOwnShadowActive()) {
	//		bsm::Vec3 CalcLightDir(StageLight.m_Directional * -1.0);
	//		bsm::Vec3 LightAt(CameraPtr->GetAt());
	//		bsm::Vec3 LightEye(CalcLightDir);
	//		LightEye *= Shadowmap::GetLightHeight();
	//		LightEye = LightAt + LightEye;
	//		bsm::Vec4 LightEye4(LightEye, 1.0f);
	//		LightEye4.w = 1.0f;
	//		BcCb.lightPos = LightEye4;
	//		bsm::Vec4 eyePos4(CameraPtr->GetEye(), 1.0f);
	//		eyePos4.w = 1.0f;
	//		BcCb.eyePos = eyePos4;
	//		bsm::Mat4x4 LightView, LightProj;
	//		//���C�g�̃r���[�Ǝˉe���v�Z
	//		LightView = XMMatrixLookAtLH(LightEye, LightAt, bsm::Vec3(0, 1.0f, 0));
	//		LightProj = XMMatrixOrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
	//			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
	//		BcCb.lightView = bsm::transpose(LightView);
	//		BcCb.lightProjection = bsm::transpose(LightProj);
	//	}
	//	//�{�[���̐ݒ�
	//	size_t BoneSz = pImpl->m_BcDrawObject.m_LocalBonesMatrix.size();
	//	if (BoneSz > 0) {
	//		UINT cb_count = 0;
	//		for (size_t b = 0; b < BoneSz; b++) {
	//			bsm::Mat4x4 mat = pImpl->m_BcDrawObject.m_LocalBonesMatrix[b];
	//			mat.transpose();
	//			BcCb.bones[cb_count] = ((XMMATRIX)mat).r[0];
	//			BcCb.bones[cb_count + 1] = ((XMMATRIX)mat).r[1];
	//			BcCb.bones[cb_count + 2] = ((XMMATRIX)mat).r[2];
	//			cb_count += 3;
	//		}
	//	}
	//	else if (pImpl->m_BcDrawObject.m_MultiLocalBonesMatrix.size() > data.m_MultiMeshIndex) {
	//		//�}���`���b�V���̃{�[����������
	//		//�{�[���̐ݒ�
	//		BoneSz = pImpl->m_BcDrawObject.m_MultiLocalBonesMatrix[data.m_MultiMeshIndex].size();
	//		if (BoneSz > 0) {
	//			UINT cb_count = 0;
	//			for (size_t b = 0; b < BoneSz; b++) {
	//				bsm::Mat4x4 mat = pImpl->m_BcDrawObject.m_MultiLocalBonesMatrix[data.m_MultiMeshIndex][b];
	//				mat.transpose();
	//				BcCb.bones[cb_count] = ((XMMATRIX)mat).r[0];
	//				BcCb.bones[cb_count + 1] = ((XMMATRIX)mat).r[1];
	//				BcCb.bones[cb_count + 2] = ((XMMATRIX)mat).r[2];
	//				cb_count += 3;
	//			}
	//		}
	//	}
	//}

	PNTPointDraw::PNTPointDraw(const std::shared_ptr<GameObject>& objPtr)
		:BcBaseDraw(objPtr), m_pImpl(new Impl())
	{}

	void PNTPointDraw::OnCreate() {
		SetLightingEnabled(true);
		//�}���`���C�g�̐ݒ�
		for (int i = 0; i < GetMaxDirectionalLights(); i++) {
			SetLightEnabled(i, true);
		}
	}

	void PNTPointDraw::OnDraw() {

		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::DoubleDraw);
		}
		
		//���b�V�����\�[�X�̎擾
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//�V�F�[�_�̐ݒ�
			if (IsPerPixelLighting()) {
				//�s�N�Z�����C�e�B���O
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
			else {
				//���_���C�e�B���O
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
		}

		//�}���`���b�V�����\�[�X�̎擾
		auto PtrMultiMeshResource = GetMultiMeshResource();
		if (PtrMultiMeshResource) {
			size_t count = PtrMultiMeshResource->GetMeshVecCount();
			auto& vec = PtrMultiMeshResource->GetMeshVec();
			for (size_t i = 0; i < count; i++) {
				if (GetMultiMeshIsDraw(i)) {
					//�V�F�[�_�̐ݒ�
					if (IsPerPixelLighting()) {
						//�s�N�Z�����C�e�B���O
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
					else {
						//���_���C�e�B���O
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
				}
			}
		}

		//��n��
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

}

//endbasecross