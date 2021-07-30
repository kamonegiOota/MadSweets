/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "PNTPointDraw.h"

namespace basecross {

	//コンスタントバッファに渡したいパラメータのみ記述する
	struct PNTPointDraw::Impl : public DrawObjectBase {
		//頂点変更する場合のメッシュ（オリジナル）
		shared_ptr<MeshResource> m_OriginalMeshResource;
		//オリジナルメッシュを使うかどうか
		bool m_UseOriginalMeshResource;
		//テクスチャリソース
		weak_ptr<TextureResource> m_TextureResource;
		//NormalMapテクスチャ
		weak_ptr<TextureResource> m_NormalMapTextureResource;
		vector<weak_ptr<TextureResource>> m_NormalMapTextureResourceVec;
		//エミッシブ色
		Col4 m_Emissive;
		//デフューズ色
		Col4 m_Diffuse;
		//透明度
		float m_Alpha;
		//スペキュラーとパワー色
		Col4 m_SpecularColorAndPower;
		//ライティングするかどうか
		bool m_LightingEnabled;
		//ピクセルライティングをするかどうか
		bool m_PreferPerPixelLighting;
		//法線にバイアスをかけるかどうか
		bool m_BiasedNormals;
		//アンビエント
		Col4 m_AmbientLightColor;
		//ライトのMAX
		static const int MaxDirectionalLights = 3;
		//ライトが有効かどうか
		bool m_LightEnabled[MaxDirectionalLights];
		//ライトの向き
		Vec3 m_LightDirection[MaxDirectionalLights];
		//ライトのデフューズ色
		Col4 m_LightDiffuseColor[MaxDirectionalLights];
		//ライトのスペキュラー色
		Col4 m_LightSpecularColor[MaxDirectionalLights];
		//フォグが有効かどうか
		bool m_FogEnabled;
		//フォグの開始位置
		float m_FogStart;
		//フォグの終了位置
		float m_FogEnd;
		//フォグ色
		Col4 m_FogColor;
		//フォグベクトル
		Vec3 m_FogVector;
		//影を投影するかどうか
		bool m_OwnShadowActive;
		//モデルに入っているDiffuseを使うかどうか
		bool m_ModelDiffusePriority;
		//モデルに入っているEmissiveを使うかどうか
		bool m_ModelEmissivePriority;
		//モデルに入っているテクスチャを使うかどうか
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
	//	//NULLのシェーダリソースの準備
	//	ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
	//	//サンプラーの準備
	//	ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
	//	//各オブジェクト共通処理
	//	//シェーダの設定
	//	//頂点シェーダ
	//	pD3D11DeviceContext->VSSetShader(T_VShader::GetPtr()->GetShader(), nullptr, 0);
	//	//インプットレイアウトの設定
	//	pD3D11DeviceContext->IASetInputLayout(T_VShader::GetPtr()->GetInputLayout());
	//	//ピクセルシェーダ
	//	pD3D11DeviceContext->PSSetShader(T_PShader::GetPtr()->GetShader(), nullptr, 0);
	//	//ライトを設定
	//	SetLightingParamaters(); //必要ないかもしれない
	//	//個別処理
	//	BasicConstants BcCb  //使用するバッファによって変わる
	//	//コンスタントバッファの作成
	//		SetConstants(BcCb, data);  //これそもそも書き換える
	//		//テクスチャ
	//	auto shTex = GetTextureResource();
	//	if (shTex) {
	//		//テクスチャがある
	//		BcCb.activeFlg.y = 1;
	//	}
	//	else {
	//		//描画コンポーネントにはテクスチャがない
	//		if (shTex = data.m_TextureResource.lock()) {
	//			//テクスチャがある
	//			BcCb.activeFlg.y = 1;
	//		}
	//		else {
	//			BcCb.activeFlg.y = 0;
	//		}
	//	}
	//	//コンスタントバッファの更新
	//	//バッファの三洋は変わる
	//	pD3D11DeviceContext->UpdateSubresource(CBBasic::GetPtr()->GetBuffer(), 0, nullptr, &BcCb, 0, 0);
	//	//コンスタントバッファの設定
	//	ID3D11Buffer* pConstantBuffer = CBBasic::GetPtr()->GetBuffer();
	//	ID3D11Buffer* pNullConstantBuffer = nullptr;
	//	//頂点シェーダに渡す
	//	pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//	//ピクセルシェーダに渡す
	//	pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
	//	//ストライドとオフセット
	//	UINT stride = data.m_NumStride;
	//	UINT offset = 0;
	//	//描画方法のセット
	//	pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
	//	//頂点バッファのセット
	//	pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
	//	//インデックスバッファのセット
	//	pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	//	//各レンダリングステートの設定
	//	//ブレンドステート
	//	RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
	//	//デプスステンシルステート
	//	RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
	//	//テクスチャとサンプラー
	//	if (shTex) {
	//		pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
	//		//サンプラーを設定
	//		RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
	//		//法線マップ
	//		if (GetNormalMapTextureResource()) {
	//			if (IsOwnShadowActive()) {
	//				//２番目に入れる
	//				pD3D11DeviceContext->PSSetShaderResources(2, 1, GetNormalMapTextureResource()->GetShaderResourceView().GetAddressOf());
	//				//サンプラーを設定
	//				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 2);
	//			}
	//			else {
	//				//1番目に入れる
	//				pD3D11DeviceContext->PSSetShaderResources(1, 1, GetNormalMapTextureResource()->GetShaderResourceView().GetAddressOf());
	//				//サンプラーを設定
	//				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 1);
	//			}
	//		}
	//	}
	//	else {
	//		//シェーダーリソースもクリア
	//		pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
	//		//サンプラーもクリア
	//		RenderState->SetSamplerAllClear(pD3D11DeviceContext);
	//	}
	//	//影とサンプラー
	//	if (IsOwnShadowActive()) {
	//		//シャドウマップのレンダラーターゲット
	//		auto ShadowmapPtr = Dev->GetShadowMapRenderTarget();
	//		ID3D11ShaderResourceView* pShadowSRV = ShadowmapPtr->GetShaderResourceView();
	//		pD3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);
	//		//シャドウマップサンプラー
	//		ID3D11SamplerState* pShadowSampler = RenderState->GetComparisonLinear();
	//		pD3D11DeviceContext->PSSetSamplers(1, 1, &pShadowSampler);
	//	}
	//	//ラスタライザステートと描画
	//	if (GetRasterizerState() == RasterizerState::DoubleDraw) {
	//		//透明処理用
	//		//ラスタライザステート(裏描画)
	//		pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
	//		//描画
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//		//ラスタライザステート（表描画）
	//		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
	//		//描画
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//	}
	//	else {
	//		RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
	//		//描画
	//		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	//	}
	//	//後始末
	//	//Dev->InitializeStates();
	//}
	

	//引数が自分で生成したコンスタントバッファ用のコンストラクトに変える。
	//void PNTPointDraw::SetConstants2(BasicConstants& BcCb, const MeshPrimData& data) {
	//	//行列の定義
	//	auto PtrTrans = GetGameObject()->GetComponent<Transform>();
	//	//カメラを得る
	//	auto CameraPtr = GetGameObject()->OnGetDrawCamera();
	//	//ライトを得る
	//	auto PtrLightObj = GetGameObject()->GetStage()->GetLight();
	//	auto PtrMultiLight = dynamic_pointer_cast<MultiLight>(PtrLightObj);
	//	if (PtrMultiLight) {
	//		//マルチライトだった
	//		BcCb.activeFlg.x = 3;
	//	}
	//	else {
	//		//そうではない
	//		BcCb.activeFlg.x = 1;
	//	}
	//	auto StageLight = GetGameObject()->OnGetDrawLight();
	//	//ワールド行列
	//	bsm::Mat4x4 world;
	//	if (data.m_UseMeshToTransformMatrix) {
	//		world = data.m_MeshToTransformMatrix * GetMeshToTransformMatrix();
	//		world *= PtrTrans->GetWorldMatrix();
	//	}
	//	else {
	//		world = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
	//	}
	//	//ビュー行列
	//	bsm::Mat4x4 view = CameraPtr->GetViewMatrix();
	//	//射影行列
	//	bsm::Mat4x4 projection = CameraPtr->GetProjMatrix();

	//	//行列の設定
	//	auto worldView = world * view;
	//	BcCb.worldViewProj = XMMatrixTranspose(XMMatrixMultiply(worldView, projection));

	//	//フォグの設定
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
	//	//ライトの設定
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

	//	//影用
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
	//		//ライトのビューと射影を計算
	//		LightView = XMMatrixLookAtLH(LightEye, LightAt, bsm::Vec3(0, 1.0f, 0));
	//		LightProj = XMMatrixOrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
	//			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
	//		BcCb.lightView = bsm::transpose(LightView);
	//		BcCb.lightProjection = bsm::transpose(LightProj);
	//	}
	//	//ボーンの設定
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
	//		//マルチメッシュのボーンがあった
	//		//ボーンの設定
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
		//マルチライトの設定
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
		
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//シェーダの設定
			if (IsPerPixelLighting()) {
				//ピクセルライティング
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
			else {
				//頂点ライティング
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
		}

		//マルチメッシュリソースの取得
		auto PtrMultiMeshResource = GetMultiMeshResource();
		if (PtrMultiMeshResource) {
			size_t count = PtrMultiMeshResource->GetMeshVecCount();
			auto& vec = PtrMultiMeshResource->GetMeshVec();
			for (size_t i = 0; i < count; i++) {
				if (GetMultiMeshIsDraw(i)) {
					//シェーダの設定
					if (IsPerPixelLighting()) {
						//ピクセルライティング
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
					else {
						//頂点ライティング
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
				}
			}
		}

		//後始末
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

}

//endbasecross