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
	//vector<float4> linghtPos : POSITION;
};

// Pixel shader: pixel lighting + texture.
// PSBasicPixelLightingTx
float4 main(PSInputPixelLightingTx pin) : SV_Target0
{

	float4 color = float4(1,1,1,1);
	if (Activeflags.y > 0) {
		color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;
	}

	if (Activeflags.x > 0) {

		float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
		float3 worldNormal = normalize(pin.NormalWS);
		ColorPair lightResult = ComputeLights(eyeVector, worldNormal, Activeflags.x);

		color.rgb *= lightResult.Diffuse;

		AddSpecular(color, lightResult.Specular);
		ApplyFog(color, pin.PositionWS.w);
	}
	else {
		ApplyFog(color, pin.PositionWS.w);
	}


	return color;
}