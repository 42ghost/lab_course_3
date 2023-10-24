#include <cstdint>

class DES_Encryption
{
    // intital permutation table
    const int IP_table[64] = { 
			58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9 , 1, 59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,};

    // IP^-1
    const int FP[64] = {
			40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
			38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
			36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
			34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9 , 49, 17, 57, 25,};
    
    // E bit selection table
    const int E_table[48] = {   
		 	32, 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,
			8 , 9 , 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 ,
	};
    
    // Si-box
    const int S[8][4][16] = {
    		{
				{14, 4 , 13, 1 , 2 , 15, 11, 8 , 3 , 10, 6 , 12, 5 , 9 , 0 , 7 },
				{0 , 15, 7 , 4 , 14, 2 , 13, 1 , 10, 6 , 12, 11, 9 , 5 , 3 , 8 },
				{4 , 1 , 14, 8 , 13, 6 , 2 , 11, 15, 12, 9 , 7 , 3 , 10, 5 , 0 },
				{15, 12, 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11, 3 , 14, 10, 0 , 6 , 13},
			},
			{
				{15, 1 , 8 , 14, 6 , 11, 3 , 4 , 9 , 7 , 2 , 13, 12, 0 , 5 , 10},
				{3 , 13, 4 , 7 , 15, 2 , 8 , 14, 12, 0 , 1 , 10, 6 , 9 , 11, 5 },
				{0 , 14, 7 , 11, 10, 4 , 13, 1 , 5 , 8 , 12, 6 , 9 , 3 , 2 , 15},
				{13, 8 , 10, 1 , 3 , 15, 4 , 2 , 11, 6 , 7 , 12, 0 , 5 , 14, 9 },
			},
			{
				{10, 0 , 9 , 14, 6 , 3 , 15, 5 , 1 , 13, 12, 7 , 11, 4 , 2 , 8 },
				{13, 7 , 0 , 9 , 3 , 4 , 6 , 10, 2 , 8 , 5 , 14, 12, 11, 15, 1 },
				{13, 6 , 4 , 9 , 8 , 15, 3 , 0 , 11, 1 , 2 , 12, 5 , 10, 14, 7 },
				{1 , 10, 13, 0 , 6 , 9 , 8 , 7 , 4 , 15, 14, 3 , 11, 5 , 2 , 12},
			},
			{
				{7 , 13, 14, 3 , 0 , 6 , 9 , 10, 1 , 2 , 8 , 5 , 11, 12, 4 , 15},
				{13, 8 , 11, 5 , 6 , 15, 0 , 3 , 4 , 7 , 2 , 12, 1 , 10, 14, 9 },
				{10, 6 , 9 , 0 , 12, 11, 7 , 13, 15, 1 , 3 , 14, 5 , 2 , 8 , 4 },
				{3 , 15, 0 , 6 , 10, 1 , 13, 8 , 9 , 4 , 5 , 11, 12, 7 , 2 , 14},
			},
			{
				{2 , 12, 4 , 1 , 7 , 10, 11, 6 , 8 , 5 , 3 , 15, 13, 0 , 14, 9 },
				{14, 11, 2 , 12, 4 , 7 , 13, 1 , 5 , 0 , 15, 10, 3 , 9 , 8 , 6 },
				{4 , 2 , 1 , 11, 10, 13, 7 , 8 , 15, 9 , 12, 5 , 6 , 3 , 0 , 14},
				{11, 8 , 12, 7 , 1 , 14, 2 , 13, 6 , 15, 0 , 9 , 10, 4 , 5 , 3 },
			},
			{
				{12, 1 , 10, 15, 9 , 2 , 6 , 8 , 0 , 13, 3 , 4 , 14, 7 , 5 , 11},
				{10, 15, 4 , 2 , 7 , 12, 9 , 5 , 6 , 1 , 13, 14, 0 , 11, 3 , 8 },
				{9 , 14, 15, 5 , 2 , 8 , 12, 3 , 7 , 0 , 4 , 10, 1 , 13, 11, 6 },
				{4 , 3 , 2 , 12, 9 , 5 , 15, 10, 11, 14, 1 , 7 , 6 , 0 , 8 , 13},
			},
			{
				{4 , 11, 2 , 14, 15, 0 , 8 , 13, 3 , 12, 9 , 7 , 5 , 10, 6 , 1 },
				{13, 0 , 11, 7 , 4 , 9 , 1 , 10, 14, 3 , 5 , 12, 2 , 15, 8 , 6 },
				{1 , 4 , 11, 13, 12, 3 , 7 , 14, 10, 15, 6 , 8 , 0 , 5 , 9 , 2 },
				{6 , 11, 13, 8 , 1 , 4 , 10, 7 , 9 , 5 , 0 , 15, 14, 2 , 3 , 12},
			},
			{
				{13, 2 , 8 , 4 , 6 , 15, 11, 1 , 10, 9 , 3 , 14, 5 , 0 , 12, 7 },
				{1 , 15, 13, 8 , 10, 3 , 7 , 4 , 12, 5 , 6 , 11, 0 , 14, 9 , 2 },
				{7 , 11, 4 , 1 , 9 , 12, 14, 2 , 0 , 6 , 10, 13, 15, 3 , 5 , 8 },
				{2 , 1 , 14, 7 , 4 , 10, 8 , 13, 15, 12, 9 , 0 , 3 , 5 , 6 , 11},
			},
	                };
	
	// permutation function           
    const int P[32] = { 	
				16, 7 , 20, 21, 29, 12, 28, 17, 1 , 15, 23, 26, 5 , 18, 31, 10,
				2 , 8 , 24, 14, 32, 27, 3 , 9 , 19, 13, 30, 6 , 22, 11, 4 , 25,
				      };
    
    // permuted choice 1
    const int pc_11[28] = {
				57, 49, 41, 33, 25, 17, 9 , 1 , 58, 50, 42, 34, 26, 18,
    			10, 2 , 59, 51, 43, 35, 27, 19, 11, 3 , 60, 52, 44, 36,
				};

	const int pc_12[28] = {
				63, 55, 47, 39, 31, 23, 15, 7 , 62, 54, 46, 38, 30, 22,
    			14, 6 , 61, 53, 45, 37, 29, 21, 13, 5 , 28, 20, 12, 4 ,
				};

    // number of bits to shift for each iteration
	int num_leftShift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

    // permuted choice 1
	const int pc_2[48] = {  14, 17, 11, 24, 1,  5,
				            3,  28, 15, 6,  21, 10,
				            23, 19, 12, 4,  26, 8,
				            16, 7,  27, 20, 13, 2,
				            41, 52, 31, 37, 47, 55,
				            30, 40, 51, 45, 33, 48,
				            44, 49, 39, 56, 34, 53,
				            46, 42, 50, 36, 29, 32};

	uint64_t uint8_to_uint64(uint8_t * nums8b){
		uint64_t res;
		for(uint8_t *p = nums8b; p < nums8b + 8; ++p){
			res = (res << 8) | *p;
		}
		return res;
	}

	uint32_t lshift28b(uint32_t num, int k){
		return ((num << k) | (num >> ((-k) & 27))) & (((uint64_t)1 << 32) - 1);
	}

	uint64_t key_permutate2(uint64_t K){
		uint64_t res = 0;
		for (int i = 0; i < 48; ++i){
			res |= ((K >> (64 - pc_2[i])) & 0x01) << (63 - i);
		}

		return res;
	}


	void gen_keys(uint64_t key, uint64_t *keys){
		uint64_t K;
		uint32_t KL = 0, KR = 0; // 28 bit
		// from 64 to 56 (2 * 28)
		for (int i = 0; i < 28; ++i){
			KL |= ((key >> (64 - pc_11[i])) & 0x01) << (31 - i);
			KR |= ((key >> (64 - pc_12[i])) & 0x01) << (31 - i);
		}

		//key from 2*28 to 48
		for (int i = 0; i < 16; ++i){
			KL = lshift28b(KL, num_leftShift[i]);
			KR = lshift28b(KR, num_leftShift[i]);
			K = ((KL << 28) | KR) << 4;
			keys[i] = key_permutate2(K);
		}
	}

	uint64_t initial_permutation(uint64_t input){
		uint64_t res = 0;
		for (int i = 0; i < 64; ++i){
			res |= ((input >> (64 - IP_table[i])) & 0x01) << (63 - i);
		}
		return res;
	}

	void split_IP(uint64_t ip_input, uint32_t *L, uint32_t *R){
		*L = (uint32_t)(ip_input >> 32);
		*R = (uint32_t)(ip_input);
	}

	uint64_t expansion_permutation(uint32_t R){
		uint64_t res = 0;
		for (uint8_t i = 0 ; i < 48; ++i) {
        	res |= (uint64_t)((R >> (32 - E_table[i])) & 0x01) << (63 - i);
		}
		return res;
	}

	void split_48b_to_6bits(uint64_t expR, uint8_t *blocks_6b){
		for (uint8_t i = 0; i < 8; ++i) {
			blocks_6b[i] = (expR >> (58 - (i * 6))) << 2;
		}
	}
	
	void s_6bits_to_4bits(uint8_t *blocks_6b, uint8_t *blocks_4b){
		uint8_t block2b, block4b;
		for (uint8_t i = 0, j = 0; i < 8; i += 2, ++j) {
			block2b = ((blocks_6b[i] >> 6) & 0x2) | ((blocks_6b[i] >> 2) & 0x1);
			block4b = (blocks_6b[i] >> 3) & 0xF;
			blocks_4b[j] = S[i][block2b][block4b];

			block2b = ((blocks_6b[i+1] >> 6) & 0x2) | ((blocks_6b[i+1] >> 2) & 0x1);;
			block4b = (blocks_6b[i+1] >> 3) & 0xF;
			blocks_4b[j] = (blocks_4b[j] << 4) | S[i+1][block2b][block4b];
		}
	}

	uint32_t join(uint8_t *blocks_4b) {
		uint32_t res;
		for (uint8_t *p = blocks_4b; p < blocks_4b + 4; ++p) {
			res = (res << 8) | *p;
		}
		return res;
	}

	uint32_t sboxes(uint64_t expR){
		uint8_t blocks_4b[4] = {0}, blocks_6b[8] = {0};
		split_48b_to_6bits(expR, blocks_6b);
		s_6bits_to_4bits(blocks_6b, blocks_4b);
		return join(blocks_4b);
	}

	uint32_t permutation(uint32_t block32b) {
		uint32_t p = 0;
		for (uint8_t i = 0 ; i < 32; ++i) {
			p |= ((block32b >> (32 - P[i])) & 0x01) << (31 - i);
		}
		return p;
	}
	
	uint32_t f(uint32_t R, uint64_t K){
		uint64_t expR = expansion_permutation(R);
		expR ^= K;
		R = sboxes(expR);
		return permutation(R);
	}

	void round_feistel(uint32_t *L, uint32_t *R, uint64_t K){
		uint32_t tmp = *R;
		*R = *L ^ f(*R, K);;
		*L = tmp;
	}

	void feistel(uint32_t *L, uint32_t *R, uint64_t *keys){
		for (int i = 0; i < 16; ++i){
			round_feistel(L, R, keys[i]);
		}
	}

	void defeistel(uint32_t *L, uint32_t *R, uint64_t *keys){
		for (int i = 15; i >= 0; --i){
			round_feistel(R, L, keys[i]);
		}
	}

	uint64_t uint32_to_uint64(uint32_t L, uint32_t R){
		uint64_t res;
		res = (uint64_t)(L);
		res = (uint64_t)(res << 32) | R;
		return res;
	}

	uint64_t final_permutation(uint64_t preoutput){
		uint64_t res = 0;
		for (int i = 0; i < 64; ++i){
			res |= ((preoutput >> (64 - FP[i])) & 0x01) << (63 - i);
		}
		return res;
	}

	void convert_to_string(uint64_t preoutput, uint8_t *output){
		for (int i = 0; i < 8; ++i){
			output[i] = (uint8_t)(preoutput >> ((7 - i) * 8));
		}
	}
	
	public:
		int encrypt(uint8_t *key, uint8_t *input, uint8_t *output, int len){
			// генерация ключей 16 по 48 бит
			uint64_t keys[16] = {};
			gen_keys(uint8_to_uint64(key), keys);
			
			uint32_t L, R;
			
			for (int i = 0; i < len; i += 8){
				split_IP(initial_permutation(uint8_to_uint64(input + i)), &L, &R);
				feistel(&L, &R, keys);
				convert_to_string(final_permutation(uint32_to_uint64(L, R)), output + i);
			}
			return 0;
		}

		int decrypt(uint8_t *key, uint8_t *input, uint8_t *output, int len){
			// генерация ключей 16 по 48 бит
			uint64_t keys[16] = {};
			gen_keys(uint8_to_uint64(key), keys);
			
			uint32_t L, R;
			for (int i = 0; i < len; i += 8){
				split_IP(initial_permutation(uint8_to_uint64(input + i)), &L, &R);
				defeistel(&L, &R, keys);
				convert_to_string(final_permutation(uint32_to_uint64(L, R)), output + i);
			}
			return 0;
		}
};
