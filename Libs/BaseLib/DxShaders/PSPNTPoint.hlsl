//#include "BcINCParameters.hlsli"
#include "PointLightParametors.hlsli"
#include "BcINCStructs.hlsli"
#include "BcINCCommon.hlsli"
//#include "BcINCLighting.hlsli"
#include "PointLighting.hlsli"

struct PSIntpuPixelPointLightingTx
{
	float2 TexCoord   : TEXCOORD0;
	float4 PositionWS : TEXCOORD1;
	float3 NormalWS   : TEXCOORD2;
	float4 Diffuse    : COLOR0;
	//float4 A
	//vector<float4> linghtPos : POSITION;
};

float4 main(PSInputPixelLightingTx pin) : SV_Target0
{

	float4 color = float4(1,1,1,1);
	if (Activeflags.y > 0) {
		color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;
	}

	//float power[3] = { PointLightPower.x, PointLightPower.y, PointLightPower.z };
	if (Activeflags.x > 0) {

		float4 diffuseTotal = float4(0, 0, 0, 0);

		//平行ライトのDiffuse計算
        float4 parallelLDiffuse = ComputeParallelLightDiffuse(pin.NormalWS, Activeflags.x);
		//ポイントライトのDiffuse計算
        float4 pointDiffuse = ComputePointLightDiffuse(pin.PositionWS, NumUsePointLight);
		
		//合計
        diffuseTotal += parallelLDiffuse + pointDiffuse;
		
        color *= diffuseTotal;
		ApplyFog(color, pin.PositionWS.w);
	}
	else {
		ApplyFog(color, pin.PositionWS.w);
	}

	return color;
}