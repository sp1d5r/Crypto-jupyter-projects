# Single-Byte XOR Cipher 
Encryption is the process of encoding messages such that it can only be read by the intended parties. Encryption scrambles the the message using a key. The strength of the encryption would be to depend on the number of bits in the key <- since brute force algorithms check every single possible combination.  

Okay, so working with bits was getting a bit tedious. I think i have the appropriate foundations for bitwise manipulation, now i'm going to start using the binascii. 

Binascii has a useful function "unhexlify", which takes in a hex string (minus the 0x) and converts it into a byte array. The byte array gets stores either as a hex value or a string. I'm not sure how it really determines this i need to look into it some more. 

So the plan is to take in the hex value, convert it into a string, then call unhexlify on it. This will convert it into a byte array. Then we will compare each byte with a single value. We will XOR this value. Then we should use a ETAOIN SHRDLU, which are the most frequently used chars. 

```python
start = 0x1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736

import binascii

def single_byte_xor_combinations(initial_hex):
    hex_string = hex(initial_hex)[2:]
    byte = binascii.unhexlify(hex_string) # convert the hex into byte array (stores as ascii)
    combinations = []
    for key in range (0,256):
        char_array = []
        for num in nums:
            char_array.append(chr(num^key))
        char_array = ''.join(char_array)
        combinations.append(char_array)
    
    return combinations

results = single_byte_xor_combinations(start)
```

Okay, so what have we done? 

We have created an array of all of the combinations of keys available. Since we know that the encryption method is xoring each byte with a single byte. So we get the byte array equivalence from the hex value. Then we need to get every combination of key available, starting from 0b0000 0000, ending at 0b1111 1111. 

That's what we've done, we've iterated through every possible key value and then xor it with each byte. 
we've stored it in character_frequencies.

```python
character_frequencies = {
        'a': .08167, 'b': .01492, 'c': .02782, 'd': .04253,
        'e': .12702, 'f': .02228, 'g': .02015, 'h': .06094,
        'i': .06094, 'j': .00153, 'k': .00772, 'l': .04025,
        'm': .02406, 'n': .06749, 'o': .07507, 'p': .01929,
        'q': .00095, 'r': .05987, 's': .06327, 't': .09056,
        'u': .02758, 'v': .00978, 'w': .02360, 'x': .00150,
        'y': .01974, 'z': .00074, ' ': .13000
    }
```

So, I looked on wikipedia and got the frequency of each alphabet. Thats what the above dictionary shows.

The next thing I need to make is a frequency function that returns the frequency of a certain string. 

```python
# Get frequency of character
def frequency_of(initial_string, character, length):
    result = 0
    for i in initial_string:
        if i == character :
            result += 1
    return result / length
```

Okay now, we need to get the differences in frequencies compared to the difference in frequencies that we were expecting. The one with the smallest difference is the one we were expecting. Then we sort it by the size of the difference. finally we just get the last one. 

```python
answers = []
for result in results:
    # get the frequency of each alphabetical letter in the result
    # compare each and check the difference abs ( expected_freq - actual )
    current_difference = 0
    for character in character_frequencies:
        current_difference = character_frequencies[character] - frequency_of(result, character, len(result))
    answers.append((result, current_difference))

answers.sort(key = lambda x: x[1])

answers[0][0]
```

> "Cooking MC's like a pound of bacon"

Boom!

Mission accomplished.

Say. No. More.

