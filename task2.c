#include <stdio.h>
#include <stdint.h>

uint16_t convert_big_endian(uint16_t string)
{
	uint8_t *c = (uint8_t *)&string;
	// interchange first and second memory zones
	uint8_t temp = *c;
	*c = *(c + 1);
	*(c + 1) = temp;
	return string;
}

uint8_t invert_bits(uint8_t msg)
{
	for (int i = 0; i < 4; i++) {
		// get left and right bit
		char left = (msg >> (7 - i)) & 1;
		char right = (msg >> i) & 1;
		// interchange
		char temp = left;
		left = right;
		right = temp;
		// update in place
		msg &= ~((1 << (7 - i)) + (1 << i));
		msg |= (left << (7 - i)) + (right << i);
	}
	return msg;
} 

uint16_t encrypt_message(uint8_t msg, uint8_t key) 
{
	msg ^= key;
	msg = invert_bits(msg);
	uint16_t ans = 0;
	for (int i = 0; i < 8; i++) {
		// set bits (ignore if 0 as we have set ans = 0)
		ans |= (msg & (1 << (7 - i))) << (8 - i);
		if (((msg >> (7 - i)) & 1) == ((key >> (7 - i)) & 1))
			ans |= 1 << (14 - 2 * i);
	}
	ans = convert_big_endian(ans);
	return ans; 
}

int main()
{
	unsigned int msg, key;
	scanf("%X", &msg);
	scanf("%X", &key);
	printf("0x%X", encrypt_message((uint8_t)msg, (uint8_t)key));
	return 0;
}
