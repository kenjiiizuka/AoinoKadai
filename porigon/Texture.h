#pragma once
#include "direct3d.h"

//! 画像読み込み用関数
void LoadTexture(const wchar_t * _fileName, ID3D11ShaderResourceView** _outTexture);

