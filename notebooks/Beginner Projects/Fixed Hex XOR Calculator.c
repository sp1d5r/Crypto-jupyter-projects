#include <stdio.h>
#include <math.h>

/* This gets the number of nibbles in an integer*/
static int get_digits_from_hex(unsigned long long hex_value){
    return (log(hex_value)/log(16)) + 1;
}

/* Gets the XOR'd hex value from computing the XOR of each bit induviually */
static unsigned long long xor_hex_calculator(unsigned long long hex_value_1, unsigned long long hex_value_2){
    unsigned long long largest = hex_value_1 < hex_value_2 ? hex_value_2 : hex_value_1;
    int digits = get_digits_from_hex(largest)*4 +1;
    
    unsigned long long mask = 1 << digits;
    unsigned long long result = 0;
    while (digits >= 0){
        mask = 1 << digits;
        result = result + ((mask & hex_value_1) ^ (mask & hex_value_2));
        digits --;
    }
    return result;
}

int main(void){
    unsigned long long hex_value_1 = 0x1c0111;
    unsigned long long hex_value_2 = 0x686974;
    unsigned long long result = xor_hex_calculator(hex_value_1, hex_value_2);
    if (result == (hex_value_2 ^ hex_value_1)){
        printf("Success!! \n");
        printf("The XOR value was - %llx \n", result);
    } else {
        printf("Sorry, the hex values you entered were too large :( \n");
    }
}
