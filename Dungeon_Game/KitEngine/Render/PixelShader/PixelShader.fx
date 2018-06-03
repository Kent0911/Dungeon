
struct PS_IN
{
	float4 pos   :	SV_POSITION;
	float4 color :	COLOR0;
};

float4 ps_main(PS_IN input) : SV_Target
{
	PS_IN OUT;
	OUT.color = input.color;
	return OUT.color;
}