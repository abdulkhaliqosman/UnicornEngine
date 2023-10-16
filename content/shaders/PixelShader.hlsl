struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
};

float4 BlinnPhong(float4 pos, float4 normal, float4 lightPos, float4 diffuseColor);
float4 main(PSInput input) : SV_TARGET
{
	const float4 lightPos = {5.0f, 5.0f, 5.0f, 1.0f};

	// return input.color;
	return BlinnPhong(input.position, input.normal, lightPos, input.color);
}

float4 BlinnPhong(float4 pos, float4 normal, float4 lightPos, float4 diffuseColor)
{
	float specPower = 32.0f;
	float ambient = 0.2f;

	float4 specColor = { 0.5f, 0.5f, 0.5f, 1.0f };

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