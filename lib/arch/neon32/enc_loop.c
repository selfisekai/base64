static inline void
enc_loop_neon32 (const uint8_t **s, size_t *slen, uint8_t **o, size_t *olen)
{
	size_t rounds = *slen / 48;

	*slen -= rounds * 48;	// 48 bytes consumed per round
	*olen += rounds * 64;	// 64 bytes produced per round

	while (rounds-- > 0) {

		// Load 48 bytes and deinterleave:
		uint8x16x3_t src = vld3q_u8(*s);

		// Reshuffle:
		uint8x16x4_t out = enc_reshuffle(src);

		// Translate reshuffled bytes to the Base64 alphabet:
		out = enc_translate(out);

		// Interleave and store output:
		vst4q_u8(*o, out);

		*s += 48;
		*o += 64;
	}
}
