// ピクセルシェーダーのメイン関数　→　ポリゴンを描画するのに必要なピクセル数だけ呼び出される
// 各ピクセルの色を指定するのが役目
// 戻り値：　このピクセルを何色にしたいか、RGBAで指定する
// 引数inputPos：　頂点の座標。ウインドウの左上を原点とするピクセル座標

//テクスチャを受け入れるグローバル変数
Texture2D gTexture : register(t0);


//サンプラーのグローバル変数
SamplerState gSampler : register(s0);
/*
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};*/

float4 ps_main( float4 inputPos : SV_POSITION,float2 uv : TEXCOORD ) : SV_Target
{
	
	//グラデーション　セピアいろとかも出せる
	float color = inputPos.x/640.0f;// 座標を横幅でわってあげるといい
	float4 pixelColor = float4(color+0.2f, color, color+0.3f, 1.0f); // RGBA  0.0f-1.0f
	

	//テクスチャの色を出力ピクセル色にする
	pixelColor = gTexture.Sample(gSampler, uv);

	return pixelColor;
}
