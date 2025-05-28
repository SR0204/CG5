#include "KamataEngine.h"
#include "PipelineState.h"
#include "RootSignature.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include <Windows.h>

using namespace KamataEngine;

// 関数プロトタイプ宣言
void SetupPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// 初期化処理

	// エンジンの初期化
	KamataEngine::Initialize(L"LE3C_13_スズキレオ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// DirectXCommonクラスが管理している、ウィンドウの幅と高さ
	int32_t w = dxCommon->GetBackBufferWidth();
	int32_t h = dxCommon->GetBackBufferHeight();
	DebugText::GetInstance()->ConsolePrintf(std::format("width:{},height:{}\n", w, h).c_str());

	// DirectXCommmonクラスが管理している、コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

	//-------------------------------RootSignatureを作成--------------------------------------------//
	RootSignature rs;
	rs.Create();

	//-------------------------------InputLayoutを設定--------------------------------------------//
	/*D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);*/

	//-------------------------------BlendState 今回は不透明--------------------------------------------//
	// D3D12_BLEND_DESC blendDesc{};
	//// 全ての色要素を書き込む
	// blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//-------------------------------RasterizerState--------------------------------------------//
	// D3D12_RASTERIZER_DESC rasterizerDesc{};
	//// 裏面(反時計回り)をカリングする
	// rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//// 塗りつぶしモードをソリッドにする(ワイヤーフレームなら、D3D12_FIll_MODE_WIREFRAME)
	// rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// 頂点シェーダーの読み込みとコンパイル
	Shader vs;
	vs.LoadDxc(L"Resources/shaders/TestVS.hlsl", L"vs_6_0");
	assert(vs.GetDxcBlob() != nullptr);

	// ピクセルシェーダーの読み込みとコンパイル
	Shader ps;
	ps.LoadDxc(L"Resources/shaders/TestPS.hlsl", L"ps_6_0");
	assert(ps.GetDxcBlob() != nullptr);

	//-----------------------PSO(PipelineStateOnject)の設定------------------------------//
	// D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	// graphicsPipelineStateDesc.pRootSignature = rs.Get();                                                    // RootSignature
	// graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;                                                // InputLayoutDesc
	// graphicsPipelineStateDesc.VS = {vs.GetDxcBlob()->GetBufferPointer(), vs.GetDxcBlob()->GetBufferSize()}; // VertexShader
	// graphicsPipelineStateDesc.PS = {ps.GetDxcBlob()->GetBufferPointer(), ps.GetDxcBlob()->GetBufferSize()}; // PixelShader
	// graphicsPipelineStateDesc.BlendState = blendDesc;                                                       // BlendState
	// graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;                                             // RasterizerState
	//// 書き込むRTVの情報
	// graphicsPipelineStateDesc.NumRenderTargets = 1; // 1つのRTVに書き込む
	// graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//// 利用するトポロジ(形状)のタイプ。三角形
	// graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//// どのように画面に色を打ち込むかの設定
	// graphicsPipelineStateDesc.SampleDesc.Count = 1;
	// graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	//// 準備は整った。PSOを生成する
	// ID3D12PipelineState* graphicsPipelineState = nullptr;
	// HRESULT hr = dxCommon->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
	// assert(SUCCEEDED(hr));

	PipelineState pipelineState;
	SetupPipelineState(pipelineState, rs, vs, ps);

	//-----------------------VertexResourceの生成------------------------------//
	// 頂点リソース用のヒープの設定
	// D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	// uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; // CPUから書き込むヒープ
	//// 頂点リソースの設定
	// D3D12_RESOURCE_DESC vertexResourceDesc{};
	// vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // バッファ
	// vertexResourceDesc.Width = sizeof(Vector4) * 3;                 // リソースのサイズ今回はVector4を3頂点分
	//// バッファの場合はこれらを1にする決まり
	// vertexResourceDesc.Height = 1;
	// vertexResourceDesc.DepthOrArraySize = 1;
	// vertexResourceDesc.MipLevels = 1;
	// vertexResourceDesc.SampleDesc.Count = 1;
	//// バッファの場合はこれにする決まり
	// vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//// 実際に頂点リソースを生成する
	// ID3D12Resource* vertexResource = nullptr;
	// HRESULT hr =
	//     dxCommon->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource));
	// assert(SUCCEEDED(hr)); // 上手くいかなかった時は起動できない

	////-----------------------VertexBufferViewを作成する------------------------------//
	// D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//// リソースの先頭アドレスから使う
	// vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//// 使用するリソースのサイズは頂点三つ分のサイズ
	// vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;
	//// 1つの頂点サイズ
	// vertexBufferView.StrideInBytes = sizeof(Vector4);

	VertexBuffer vb;
	vb.Create(sizeof(Vector4) * 3, sizeof(Vector4));

	//-----------------------頂点リソースにデータを書き込む------------------------------//
	Vector4* vertexData = nullptr;
	vb.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = {-0.5f, -0.5f, 0.0f, 1.0f}; // 左下
	vertexData[1] = {0.0f, 0.5f, 0.0f, 1.0f};   // 上
	vertexData[2] = {0.5f, -0.5f, 0.0f, 1.0f};  // 右下
	// 頂点リソースのマップを解除するa
	// vertexResource->Unmap(0, nullptr);

	// 更新処理
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// 描画開始
		dxCommon->PreDraw();

		// ここに描画処理を書く

		// コマンドを積む
		commandList->SetGraphicsRootSignature(rs.Get());     // RootSignatureの設定
		commandList->SetPipelineState(pipelineState.Get());  // PSOの設定をする
		commandList->IASetVertexBuffers(0, 1, vb.GetView()); // VBVの設定をする
		// トロポジの設定
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// 頂点数、インデックス数、インデックスの開始位置、インデックスのオフセット
		commandList->DrawInstanced(3, 1, 0, 0);

		dxCommon->PostDraw();
	}

	// 解放処理
	//vertexResource->Release();
	// graphicsPipelineState->Release();
	/*signatureBlob->Release();
	rootSignature->Release();*/

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

// インプットレイアウト,ブレンドステート,ラスタライザステート
// 引数として空のpipelineState,RootSignature,頂点シェーダーvs,ピクセルシェーダーpsを参照で受け取る
void SetupPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps) {
	//-------------------------------InputLayoutを設定--------------------------------------------//
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// BlendState-------------------- 今回は不透明
	D3D12_BLEND_DESC blendDesc{};

	// 全ての色を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//-------------------------------RasterizerState--------------------------------------------//
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	// 裏面(反時計回り)をカリングする
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 塗りつぶしモードをソリッドにする(ワイヤーフレームなら、D3D12_FIll_MODE_WIREFRAME)
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//-----------------------PSO(PipelineStateOnject)の設定------------------------------//
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = rs.Get();                                                    // RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;                                                // InputLayoutDesc
	graphicsPipelineStateDesc.VS = {vs.GetDxcBlob()->GetBufferPointer(), vs.GetDxcBlob()->GetBufferSize()}; // VertexShader
	graphicsPipelineStateDesc.PS = {ps.GetDxcBlob()->GetBufferPointer(), ps.GetDxcBlob()->GetBufferSize()}; // PixelShader
	graphicsPipelineStateDesc.BlendState = blendDesc;                                                       // BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;
	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1; // 1つのRTVに書き込む
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// 利用するトポロジ(形状)のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// どのように画面に色を打ち込むかの設定
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// 準備は整った。PSOを生成する
	pipelineState.Create(graphicsPipelineStateDesc);
}
