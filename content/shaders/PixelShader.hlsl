Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float4 worldPosition : POSITION0;
	float4 color : COLOR;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

float4 BlinnPhong(float4 pos, float4 normal, float4 lightPos, float4 diffuseColor);

float4 main(PSInput input) : SV_TARGET
{
	const float4 lightPos = {0.0f, 10.0f, 0.0f, 1.0f};

	float4 texColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	texColor = Texture.Sample( Sampler, input.texcoord );

	return BlinnPhong(input.worldPosition, input.normal, lightPos, input.color*texColor);
}

float4 BlinnPhong(float4 pos, float4 normal, float4 lightPos, float4 diffuseColor)
{
	float specPower = 32.0f;
	float ambient = 0.2f;

	float4 specColor = { 0.8f, 0.8f, 0.8f, 1.0f };

	normal.w = 0;
	pos.w = 0;
	lightPos.w = 0;

	float4 n = normalize(normal);
	float4 v = normalize(-pos);
	float4 l = normalize(lightPos - pos);
	float4 h = normalize(v + l);

	float diffuse = max(dot(n, l), 0.0f);
	float spec = pow(max(dot(n, h), 0.0f), specPower);

	return (ambient + diffuse) * diffuseColor + spec * specColor;
}