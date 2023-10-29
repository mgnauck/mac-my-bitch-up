#include "Blending.h"

unsigned int Blending::average(unsigned int v1, unsigned int v2) {
	
	int r = (((v1 >> 16) & 0xff) + ((v2 >> 16) & 0xff)) >> 1;
	int g = (((v1 >>  8) & 0xff) + ((v2 >>  8) & 0xff)) >> 1;
	int b = (((v1 >>  0) & 0xff) + ((v2 >>  0) & 0xff)) >> 1;
	
	return (r << 16) | (g << 8) | b;
}

unsigned int Blending::additive(unsigned int v1, unsigned int v2) {
	
	int r = ((v1 >> 16) & 0xff) + ((v2 >> 16) & 0xff);
	int g = ((v1 >>  8) & 0xff) + ((v2 >>  8) & 0xff);
	int b = ((v1 >>  0) & 0xff) + ((v2 >>  0) & 0xff);
	
	r = (r > 0xff) ? 0xff : r;
	g = (g > 0xff) ? 0xff : g;
	b = (b > 0xff) ? 0xff : b;
	
	return (r << 16) | (g << 8) | b;
}

unsigned int Blending::subtractive(unsigned int v1, unsigned int v2) {
	
	int r = ((v1 >> 16) & 0xff) - ((v2 >> 16) & 0xff);
	int g = ((v1 >>  8) & 0xff) - ((v2 >>  8) & 0xff);
	int b = ((v1 >>  0) & 0xff) - ((v2 >>  0) & 0xff);
	
	r = (r < 0x0) ? 0x0 : r;
	g = (g < 0x0) ? 0x0 : g;
	b = (b < 0x0) ? 0x0 : b;
	
	return (r << 16) | (g << 8) | b;
}

unsigned int Blending::multiplicative(unsigned int v1, unsigned int v2) {
	
	int r = (((v1 >> 16) & 0xff) * ((v2 >> 16) & 0xff)) >> 8;
	int g = (((v1 >>  8) & 0xff) * ((v2 >>  8) & 0xff)) >> 8;
	int b = (((v1 >>  0) & 0xff) * ((v2 >>  0) & 0xff)) >> 8;
	
	return (r << 16) | (g << 8) | b;
}

unsigned int Blending::alpha(unsigned int v1, unsigned int v2) {
	
	int a = (v1 >> 24) & 0xff;
	int ai = 0xff - a;

	int r = ((((v2 >> 16) & 0xff) * ai) >> 8) + ((((v1 >> 16) & 0xff) * a) >> 8);
	int g = ((((v2 >>  8) & 0xff) * ai) >> 8) + ((((v1 >>  8) & 0xff) * a) >> 8);
	int b = ((((v2 >>  0) & 0xff) * ai) >> 8) + ((((v1 >>  0) & 0xff) * a) >> 8);
			  
	return (r << 16) | (g << 8) | b;
}

unsigned int Blending::alphaWithTest(unsigned int v1, unsigned int v2) {
	
	int a = (v1 >> 24) & 0xff;
	
	if(a == 0x0)
		return v2;
	if(a == 0xff)
		return v1;
	
	int ai = 0xff - a;

	int r = ((((v2 >> 16) & 0xff) * ai) >> 8) + ((((v1 >> 16) & 0xff) * a) >> 8);
	int g = ((((v2 >>  8) & 0xff) * ai) >> 8) + ((((v1 >>  8) & 0xff) * a) >> 8);
	int b = ((((v2 >>  0) & 0xff) * ai) >> 8) + ((((v1 >>  0) & 0xff) * a) >> 8);
			  
	return (r << 16) | (g << 8) | b;
}

unsigned char Blending::multiplicativeByte(unsigned char v1, unsigned char v2) {
	return (v1 * v2) >> 8;
}

unsigned int Blending::multiplicativeByteInt(unsigned char v1, unsigned int v2) {

	int r = (v1 * ((v2 >> 16) & 0xff)) >> 8;
	int g = (v1 * ((v2 >>  8) & 0xff)) >> 8;
	int b = (v1 * ((v2 >>  0) & 0xff)) >> 8;
	
	return (r << 16) | (g << 8) | b;
}
