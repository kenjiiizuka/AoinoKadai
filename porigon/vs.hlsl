 
// 頂点シェーダーのメイン関数
//役割　各頂点に対して行いたい移動　回転　縮小などを実行する
// 戻り値：このシェーダーの処理の結果を、頂点のデータとして戻す
// 引数 inputPos：VRAMに転送された頂点データ（のうち１つ）が渡される

//return用の構造体

struct VS_OUTPUT
{
	float4 pos : SV_Position; //システムで決められてる名前
	float2 uv : TEXCOORD; //システムで決められてる名前
};

VS_OUTPUT vs_main(float4 inputPos : POSITION,/*xy*/ float2 uv:TEX /*uv*/)
{
	VS_OUTPUT output;

	output.pos = inputPos;  // 渡された頂点をそのままreturnする。（そのまま使う）
	output.uv = uv;
	//移動
	//outputPos.x += 0.2f;
	//outputPos.y += 0.3f;
	//拡大縮小
	output.pos.x *= (480.0f/640.0f);
	output.pos.y *= 1.0f;

    return output;
}