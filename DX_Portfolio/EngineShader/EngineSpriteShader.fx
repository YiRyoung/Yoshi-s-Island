struct EngineVertex
{
    float4 COLOR : COLOR;
    float POSITION : POSITION;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_Position;
    float4 COLOR : COLOR;
};

VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = _Vertex.POSITION;
    OutPut.COLOR = _Vertex.COLOR;
    
    return OutPut;
}