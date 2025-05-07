#include "Shader.h"
#include <cassert>       //assert
#include <d3dcompiler.h> //D3DCompileFromFile]

// シェーダーを読み込み、コンパイルする
void Shader::Load(const std::wstring& filePath, const std::string& shaderModel) {

	//----------------------------------シェーダーコンパイル関数-----------------------------
	// filePath    : シェーダーファイルのパス　　例 L"Resources/shaders/TestVS.hlsl"
	// shaderModel : シェーダーモデル   例 "vs_5.0"
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
	    filePath.c_str(), // シェーダーファイル名
	    nullptr,
	    D3D_COMPILE_STANDARD_FILE_INCLUDE,               // インクルード可能にする
	    "main", shaderModel.c_str(),                     // エントリーポイント名、シェーダーモデル指定
	    D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
	    0, &shaderBlob, &errorBlob);

	// エラーが発生した場合、止める
	if (FAILED(hr)) {
		if (errorBlob) {
			OutputDebugStringA(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
		}
		assert(false);
	}
	// 生成したshaderBlobをとっておく
	blob_ = shaderBlob;
}

ID3DBlob* Shader::GetBlob() { return blob_; }

Shader::Shader() {}

Shader::~Shader() {
	if (blob_ != nullptr) {
		blob_->Release();
		blob_ = nullptr;
	}
}
