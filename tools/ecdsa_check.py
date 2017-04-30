from fastecdsa.curve import secp192k1
from fastecdsa.point import Point
from fastecdsa import curve, ecdsa, keys
from hashlib import sha256

xs = 0xDB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D
ys = 0x9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D
S = Point(xs, ys, curve=secp192k1)



'''
xt = 0x55a8b00f8da1d44e62f6b3b25316212e39540dc861c89575bb8cf92e35e0986b
yt = 0x5421c3209c2d6c704835d82ac4c3dd90f61a8a52598b9e7ab656e9d8c8b24316
T = Point(xt, yt, curve=secp256k1)
'''


# Point Doubling
R = 3 * S   # S * 2 works fine too i.e. order doesn't matter

d = 0xc51e4753afdec1e6b6c6a5b992f43f8dd0c7a8933072708b6522468b2ffb06fd

# Scalar Multiplication
R = d * S  # S * d works fine too i.e. order doesn't matter

print R

#m = "a message to sign via ECDSA"  # some message
with open('../certificates/sample_tbscertificate.txt', 'r') as myfile:
    m=myfile.read()
#print m
#private_key = keys.gen_private_key(curve.P256)
#xor of 0x f89c265291674f656c2218676274d71794e95ba8270b2fa4
#and    0x ebb125a0cd2fea04687f5e96a57d6005b4de2c1d8851b888
# 		0x 132D03F25C48A561045D46F1C709B712203777B5AF5A972C


private_key = 0x132D03F25C48A561045D46F1C709B712203777B5AF5A972C
public_key = keys.get_public_key(private_key, secp192k1)
print public_key

#the signature will be different because you've generated a different random number
''' specify a different hash function to use with ECDSA '''
r, s = ecdsa.sign(m, private_key, curve=secp192k1, hashfunc=sha256)
valid = ecdsa.verify((r, s), m, public_key, hashfunc=sha256, curve=secp192k1)



