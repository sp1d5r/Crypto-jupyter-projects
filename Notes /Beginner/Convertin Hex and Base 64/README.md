# Converting Hex into Base 64

So, what is Hex?

Hex is a base 16 character set It goes from 0-9, A-F. Where A=11, B=11, ..., F=16. This is useful since each hex character is 4 bits (nibble). We write hex characters with an 0x at the start, so 0x0, is 0 in hex. Below is the table of conversions:

![Hex to Decimal to Binary conversion table](http://www.matrixlab-examples.com/image-files/hex_to_binary_001.gif)

So, what is Base 64?

Base 64, is the binary to text encoding system that lets you convert binary into an ASCII format. It takes in binary values and outputs characters between A-Z, a-z, 0-9, +,/, It really shines when converting ASCII text. 

Converting Hex to Base 64 should be easy, a hex character is 4 bits long, a base 64 character is 7 bits long. Just convert the hex into binary and then read out the values you get. 

Got it?

Okay let's go!

```python
# Getting a binary representation of something 
binaryRepresentationOfHex = bin(0x49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d)
print(binaryRepresentationOfHex)
```

> 0b10010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101

So getting the binary representation from a hex value returns a string... Not too useful, in the notes he said don't work with encoded strings, try and work with byte values. Which I haven't been able to figure out properly, so for now instead of getting the digits in the binary value by counting bytes i'll just get it using logs.   

```python
import math 

def get_digits_from_bin(binary_value):
    return int (math.log(binary_value) / 
                math.log(2)) + 1  # divide log of number by log of 2 since that's the same as doing log 2
```

Okay cool, the approach I'm going to have will be as follows:
* I will get the number of digits inside the hex value using the log method described above. 
* Then we'll use a bit mask of 0b11111 since base 64 goes from 0-63 and 7 bits holds all of those values. 
* This bit mask needs to be shifted from the MSB (most-significant-bit LHS) all the way down the binary representation to the end of the binary value, comparing the value in a array i have stored.
* For each of the bit masks i will append the result to a final answer array 
* This will return a string.

```python
# Defining denary-to-base-64 mapping
toB64 = [chr(ord('A')+x) for x in range(0,26)]
toB64.extend([chr(ord('a')+x) for x in range(0,26)])
toB64.extend([chr(ord('0')+x)for x in range(0,10)])
toB64.extend(['+', '/'])
```

Now let's bring it all together:
```python
def convertHexToString(hex_value):
    answer = []

    digits = get_digits_from_bin(hex_value)
    
    # Check if there would be a leading 0 
    if (digits %4 == 0):
        shiftValue = digits - 4
    else:
        shiftValue = digits - 5 
        
    initialMask = 0x3f << (shiftValue-1)
    
    while (shiftValue > 0):
        answer.append(toB64[(hex_value & initialMask) >> shiftValue])
        shiftValue = shiftValue - 6
        initialMask = 0x3f << (shiftValue)
    answer.append(array[(hex_value & initialMask)])

    return (''.join(answer))
```

Here is an example of it working properly!

```python
inputVal = 0x49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
convertHexToString(inputVal)
```

> 'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'

TADA!!

Done, that was a bit more complicated than i was expecting, mostly due to the fact that masking the value given most ASCII characters are padded on the leading bit (there is an extra 0 at the start), means that you have to mask the first 6 bits. To fix this we included an additional if statement at the start. Overall the time complexity for this function is O(n) (given a hex length n/4) since it iterates through the binary version of that hex representation. 

What did i learn from this task?

Operating on bytes and bits is much more efficient than operating on encoded string, when transferring string data over the internet to make sure we don't lose any information during transmition. But I personally see it used on websites all the time, and the reason for this is because its around 33% shorter.