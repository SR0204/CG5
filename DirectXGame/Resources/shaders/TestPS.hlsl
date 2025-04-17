struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixcelShaderOutput main()
{
    PixcelShaderOutput output;
    output.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    return output;
}