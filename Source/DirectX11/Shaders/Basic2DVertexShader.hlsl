
struct VertexShaderInput
{
    float3 position : POSITION;
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

    output.position = position;
	
    output.color = float4(1, 0, 1, 1);

    return output;

}