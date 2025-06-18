#include"Test.hlsli"

struct PixcelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;
    
    float32_t2 uv = input.texcoord;
    
    output.color = float32_t4(uv.x, uv.y, 0.0f, 1.0f);
    return output;
}