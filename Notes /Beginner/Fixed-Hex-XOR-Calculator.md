# Fixed Hex XOR Calculator 
You get two fixed buffers, both strings which are hex values then you convert them into a binary value then use XOR on each of those bits to produce an output value.

```python
import math 

def get_digits_from_hex(binary_value):
    return int (math.log(binary_value) / 
                math.log(16)) + 1  # divide log of number by log of 2 since that's the same as doing log 2
```

My approach will be similar to the one I used last time, I'm going to mask each bit. I don't need to do that i could listerally do hex_value_1 xor hex_value_2, but let's do this a bit more interestingly.

(by that i mean go bit by bit...)

```python
def XOR_hex_calculator(hex_value_1, hex_value_2, digits):
    mask = 1 << digits
    result = 0
    while (digits != 0):
        mask = 1 << digits
        digits -= 1;
        result = result + ((mask & hex_value_1) ^ (mask & hex_value_2))
    return result
```

And we will test it here: 
```python
hex(XOR_hex_calculator(0x1c0111001f010100061a024b53535009181c, 0x686974207468652062756c6c277320657965, get_digits_from_hex(0x686974207468652062756c6c277320657965) *4))
```
>'0x746865206b696420646f6e277420706c6178'

As you can see this time i used the number of hex digits, this is useful because it'll tell me the number of bytes not the number bits (helps with leading zeros).

The equivalent c code is here too!
```c 
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
```