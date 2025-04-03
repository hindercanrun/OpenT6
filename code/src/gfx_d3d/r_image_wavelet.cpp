#include "types.h"
#include "vars.h"

const WaveletHuffmanDecode waveletDecodeBlue[4096];
const unsigned __int16 waveletEncodeBlue[511];
const WaveletHuffmanDecode waveletDecodeRedGreen[4096];
const unsigned __int16 waveletEncodeRedGreen[1021];
const WaveletHuffmanDecode waveletDecodeAlpha[4096];
const unsigned __int16 waveletEncodeAlpha[511];

/*
==============
TRACK_r_image_wavelet
==============
*/
void TRACK_r_image_wavelet()
{
	track_static_alloc_internal(waveletDecodeBlue, 16384, "waveletDecodeBlue", 21);
	track_static_alloc_internal(waveletEncodeBlue, 1022, "waveletEncodeBlue", 21);
	track_static_alloc_internal(waveletDecodeRedGreen, 16384, "waveletDecodeRedGreen", 21);
	track_static_alloc_internal(waveletEncodeRedGreen, 2042, "waveletEncodeRedGreen", 21);
	track_static_alloc_internal(waveletDecodeAlpha, 16384, "waveletDecodeAlpha", 21);
	track_static_alloc_internal(waveletEncodeAlpha, 1022, "waveletEncodeAlpha", 21);
}

