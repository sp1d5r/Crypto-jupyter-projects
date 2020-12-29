# Implement Repeating-Key XOR
Okay, so for this problem, we have an input string, and we want to XOR that with a key. But this time, we are repeating the key to match the characters in the input string. 
For example:
input string - "Burning 'em, if you ain't quick and nimble"
key - "ICE"

we'd XOR the following together 
input string XOR "ICEICEICEICEICE...ICE"

Make sense? 

Okay cool.

The way i am going to do this is to convert the input string into a byte array, then for each byte xor it with the corresponding element in the key. I'll use a modulus operator to grab the corresponding index of the key. So if i have the 5th element in the string, and i have a key of length 3, i will do 5%3 which tells us it's the 3'rd element in the list which is 'I' which makes sense since it's zero indexed. 

```python
import binascii
input_string = "Burning 'em, if you ain't quick and nimble"
key = "ICE"
bytearr = bytes(input_string, "ascii")
result = []


for idx, byte in enumerate(bytearr):
    result.append(bytes(key[idx%len(key)],"ascii")[0] ^ byte)

answer = ''.join('{:02x}'.format(x) for x in result)

answer
```

> '0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20'

Okay, done! 
That was a quick one but only due to the fact I am getting the hang of bytes and manipulating them now.

