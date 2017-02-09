
cbuffer ModelViewProjectionConstantBuffer
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VertexShaderInput
{
    float3 position : POSITION;
    float3 color : COLOR0;
};

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR0;
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;

    float4 position = float4(input.position, 1.0f);

    position = mul(position, model);
    position = mul(position, view);
    position = mul(position, projection);
    output.position = position;

    output.color = input.color;

    return output;

}