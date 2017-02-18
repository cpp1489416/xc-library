
cbuffer cbPerObject : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

cbuffer BoolBuffer : register(b1)
{
    bool isSingle;
};

Texture2D objTexture;
SamplerState objSamplerState;
TextureCube skymap;
//
//cbuffer XBuffer
//{
//    float4 buffer;
//};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};



VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD)
{
    //isSingle = true;
    VS_OUTPUT output;

    output.Pos = mul(inPos, world);
    output.Pos = mul(output.Pos, view);
    output.Pos = mul(output.Pos, projection);
    output.Pos.x = output.Pos.x;
    output.TexCoord = inTexCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    return objTexture.Sample(objSamplerState, input.TexCoord);
}


struct skymapVSOutput
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

skymapVSOutput skymap_VS(float3 inPosition : POSITION, float2 inTexCoord : TEXCOORD)
{
    skymapVSOutput output;
    output.position = mul(float4(inPosition, 1.0f), world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    output.position = output.position.xyww;
    output.texCoord = inPosition;
    return output;
}

float4 skymap_PS(skymapVSOutput input)  : SV_Target
{
    return skymap.Sample(objSamplerState, input.texCoord);
}