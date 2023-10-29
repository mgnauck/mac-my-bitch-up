#ifndef H_BLENDING__
#define H_BLENDING__

// slow shit!

class Blending {
public:
	static unsigned int		average(unsigned int v1, unsigned int v2);
	static unsigned int		additive(unsigned int v1, unsigned int v2);
	static unsigned int		subtractive(unsigned int v1, unsigned int v2);
	static unsigned int		multiplicative(unsigned int v1, unsigned int v2);
	static unsigned int		alpha(unsigned int v1, unsigned int v2);			// SRC_ALPHA, ONE_MINUS_SRC_ALPHA
	static unsigned int		alphaWithTest(unsigned int v1, unsigned int v2);	// + test if 0 or 0xff
	static unsigned char	multiplicativeByte(unsigned char v1, unsigned char v2);
	static unsigned int		multiplicativeByteInt(unsigned char v1, unsigned int v2);
};

#endif