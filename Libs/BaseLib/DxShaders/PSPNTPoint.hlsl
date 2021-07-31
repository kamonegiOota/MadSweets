//#include "BcINCParameters.hlsli"
#include "PointLightParametors.hlsli"
#include "BcINCStructs.hlsli"
#include "BcINCCommon.hlsli"
#include "BcINCLighting.hlsli"

struct PSIntpuPixelPointLightingTx
{
	float2 TexCoord   : TEXCOORD0;
	float4 PositionWS : TEXCOORD1;
	float3 NormalWS   : TEXCOORD2;
	float4 Diffuse    : COLOR0;
	//float4 A
	//vector<float4> linghtPos : POSITION;
};

//// Pixel shader: pixel lighting + texture.
//// PSBasicPixelLightingTx
//float4 main(PSInputPixelLightingTx pin) : SV_Target0
//{
//
//	float4 color = float4(1,1,1,1);
//	if (Activeflags.y > 0) {
//		color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;
//	}
//
//	if (Activeflags.x > 0) {
//
//		//減衰値
//		//将来的にはコンスタントバッファを利用して受け取りたい
//		float4 Attenuation = float4(0.5f, 0.5f, 0.5f, 0.5f);
//		//float power[3] = { PointLightPower.x, PointLightPower.y, PointLightPower.z };
//		float4 diffuse_total = float4(0, 0, 0, 0);
//
//		for (int i = 0; i < 1; i++) {
//
//			//if (PointLightPositions[i].isActive == false) {
//			//	//break;
//			//}
//
//			//float3 dir = PointLightPositions[i].position.xyz - pin.PositionWS.xyz;
//			//float3 dir = PointLightPositions[i].xyz - pin.PositionWS.xyz;
//			float3 dir = float3(-12.0f,0.0f,12.0f) - pin.PositionWS.xyz;
//			float len = length(dir);
//			//float attenuation = 1.0f / (Attenuation.x * len * len);
//			float attenuation = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));
//
//			diffuse_total += float4(LightDiffuseColor[i], 1.0f) *
//				 pin.Diffuse * attenuation * 1.0f; //* power[i]; //* 2.0f;// * power[i];// * power[i]; //* power[i];// * PointLightPower[i]; //* power[i]
//		}
//
//		color *= diffuse_total;
//
//		ApplyFog(color, pin.PositionWS.w);
//
//		//float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
//		//float3 worldNormal = normalize(pin.NormalWS);
//		//ColorPair lightResult = ComputeLights(eyeVector, worldNormal, Activeflags.x);
//
//		//color.rgb *= lightResult.Diffuse;
//
//		//AddSpecular(color, lightResult.Specular);
//		//ApplyFog(color, pin.PositionWS.w);
//	}
//	else {
//		//ApplyFog(color, pin.PositionWS.w);
//	}
//
//	return color;
//}

// Pixel shader: pixel lighting + texture.
// PSBasicPixelLightingTx
float4 main(PSInputPixelLightingTx pin) : SV_Target0
{

	float4 color = float4(1,1,1,1);
	if (Activeflags.y > 0) {
		color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;
	}

	//float power[3] = { PointLightPower.x, PointLightPower.y, PointLightPower.z };
	if (Activeflags.x > 0) {
		//減衰値
		//将来的にはコンスタントバッファを利用して受け取りたい
		float4 Attenuation = float4(0.5f, 0.5f, 0.5f, 0.5f);
		//float power[3] = { PointLightPower.x, PointLightPower.y, PointLightPower.z };
		float4 diffuse_total = float4(0, 0, 0, 0);

		for (int i = 0; i < 1; i++) {
			float3 dir = PointLightPositions[i].xyz - pin.PositionWS.xyz;
			float len = length(dir);
			//float attenuation = 1.0f / (Attenuation.x * len * len);
			float attenuation = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));

			diffuse_total += float4(LightDiffuseColor[i], 1.0f) *
				pin.Diffuse * attenuation * 3.0f; //* power[i]; //* 2.0f;// * power[i];// * power[i]; //* power[i];// * PointLightPower[i]; //* power[i]
		}

		color *= diffuse_total;
		ApplyFog(color, pin.PositionWS.w);

		//float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
		//float3 worldNormal = normalize(pin.NormalWS);
		//ColorPair lightResult = ComputeLights(eyeVector, worldNormal, Activeflags.x);

		//color.rgb *= lightResult.Diffuse;

		//AddSpecular(color, lightResult.Specular);
		//ApplyFog(color, pin.PositionWS.w);
	}
	else {
		ApplyFog(color, pin.PositionWS.w);
	}

	return color;
}