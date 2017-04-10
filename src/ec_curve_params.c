/* This tables defines aliases for curve names.  */
static const struct
{
  const char *name;  /* Our name.  */
  const char *other; /* Other name. */
} curve_aliases[] =
  {
    { "Curve25519", "1.3.6.1.4.1.3029.1.5.1" },
    { "Ed25519",    "1.3.6.1.4.1.11591.15.1" },

    { "NIST P-192", "1.2.840.10045.3.1.1" }, /* X9.62 OID  */
    { "NIST P-192", "prime192v1" },          /* X9.62 name.  */
    { "NIST P-192", "secp192r1"  },          /* SECP name.  */
    { "NIST P-192", "nistp192"   },          /* rfc5656.  */

    { "NIST P-224", "secp224r1" },
    { "NIST P-224", "1.3.132.0.33" },        /* SECP OID.  */
    { "NIST P-224", "nistp224"   },          /* rfc5656.  */

    { "NIST P-256", "1.2.840.10045.3.1.7" }, /* From NIST SP 800-78-1.  */
    { "NIST P-256", "prime256v1" },
    { "NIST P-256", "secp256r1"  },
    { "NIST P-256", "nistp256"   },          /* rfc5656.  */

    { "NIST P-384", "secp384r1" },
    { "NIST P-384", "1.3.132.0.34" },
    { "NIST P-384", "nistp384"   },          /* rfc5656.  */

    { "NIST P-521", "secp521r1" },
    { "NIST P-521", "1.3.132.0.35" },
    { "NIST P-521", "nistp521"   },          /* rfc5656.  */

    { "brainpoolP160r1", "1.3.36.3.3.2.8.1.1.1" },
    { "brainpoolP192r1", "1.3.36.3.3.2.8.1.1.3" },
    { "brainpoolP224r1", "1.3.36.3.3.2.8.1.1.5" },
    { "brainpoolP256r1", "1.3.36.3.3.2.8.1.1.7" },
    { "brainpoolP320r1", "1.3.36.3.3.2.8.1.1.9" },
    { "brainpoolP384r1", "1.3.36.3.3.2.8.1.1.11"},
    { "brainpoolP512r1", "1.3.36.3.3.2.8.1.1.13"},

    { "GOST2001-test", "1.2.643.2.2.35.0" },
    { "GOST2001-CryptoPro-A", "1.2.643.2.2.35.1" },
    { "GOST2001-CryptoPro-B", "1.2.643.2.2.35.2" },
    { "GOST2001-CryptoPro-C", "1.2.643.2.2.35.3" },
    { "GOST2001-CryptoPro-A", "GOST2001-CryptoPro-XchA" },
    { "GOST2001-CryptoPro-C", "GOST2001-CryptoPro-XchB" },
    { "GOST2001-CryptoPro-A", "1.2.643.2.2.36.0" },
    { "GOST2001-CryptoPro-C", "1.2.643.2.2.36.1" },

    { "GOST2012-tc26-A", "1.2.643.7.1.2.1.2.1" },
    { "GOST2012-tc26-B", "1.2.643.7.1.2.1.2.2" },

    { "secp256k1", "1.3.132.0.10" },

    { NULL, NULL}
  };


typedef struct
{
  const char *desc;           /* Description of the curve.  */
  unsigned int nbits;         /* Number of bits.  */
  unsigned int fips:1;        /* True if this is a FIPS140-2 approved curve. */

  const char *p;              /* The prime defining the field.  */
  const char *a, *b;          /* The coefficients.  For Twisted Edwards
                                 Curves b is used for d.  For Montgomery
                                 Curves (a,b) has ((A-2)/4,B^-1).  */
  const char *n;              /* The order of the base point.  */
  const char *g_x, *g_y;      /* Base point.  */
  const char *h;              /* Cofactor.  */
} ecc_domain_parms_t;


/* This static table defines all available curves.  */
static const ecc_domain_parms_t domain_parms[] =
  {
    {
      /* (-x^2 + y^2 = 1 + dx^2y^2) */
      "Ed25519", 256, 0,
      "0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFED",
      "-0x01",
      "-0x2DFC9311D490018C7338BF8688861767FF8FF5B2BEBE27548A14B235ECA6874A",
      "0x1000000000000000000000000000000014DEF9DEA2F79CD65812631A5CF5D3ED",
      "0x216936D3CD6E53FEC0A4E231FDD6DC5C692CC7609525A7B2C9562D608F25D51A",
      "0x6666666666666666666666666666666666666666666666666666666666666658",
      "0x08"
    },
    {
      /* (y^2 = x^3 + 486662*x^2 + x) */
      "Curve25519", 256, 0,
      "0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFED",
      "0x01DB41",
      "0x01",
      "0x1000000000000000000000000000000014DEF9DEA2F79CD65812631A5CF5D3ED",
      "0x0000000000000000000000000000000000000000000000000000000000000009",
      "0x20AE19A1B8A086B4E01EDD2C7748D14C923D4D7E6D7C61B229E9C5A27ECED3D9",
      "0x08"
    },
    {
      "NIST P-192", 192, 0,
      "0xfffffffffffffffffffffffffffffffeffffffffffffffff",
      "0xfffffffffffffffffffffffffffffffefffffffffffffffc",
      "0x64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1",
      "0xffffffffffffffffffffffff99def836146bc9b1b4d22831",

      "0x188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012",
      "0x07192b95ffc8da78631011ed6b24cdd573f977a11e794811",
      "0x01"
    },
    {
      "NIST P-224", 224, 1,
      "0xffffffffffffffffffffffffffffffff000000000000000000000001",
      "0xfffffffffffffffffffffffffffffffefffffffffffffffffffffffe",
      "0xb4050a850c04b3abf54132565044b0b7d7bfd8ba270b39432355ffb4",
      "0xffffffffffffffffffffffffffff16a2e0b8f03e13dd29455c5c2a3d" ,

      "0xb70e0cbd6bb4bf7f321390b94a03c1d356c21122343280d6115c1d21",
      "0xbd376388b5f723fb4c22dfe6cd4375a05a07476444d5819985007e34",
      "0x01"
    },
    {
      "NIST P-256", 256, 1,
      "0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff",
      "0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc",
      "0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b",
      "0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551",

      "0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",
      "0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5",
      "0x01"
    },
    {
      "NIST P-384", 384, 1,
      "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
      "ffffffff0000000000000000ffffffff",
      "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
      "ffffffff0000000000000000fffffffc",
      "0xb3312fa7e23ee7e4988e056be3f82d19181d9c6efe8141120314088f5013875a"
      "c656398d8a2ed19d2a85c8edd3ec2aef",
      "0xffffffffffffffffffffffffffffffffffffffffffffffffc7634d81f4372ddf"
      "581a0db248b0a77aecec196accc52973",

      "0xaa87ca22be8b05378eb1c71ef320ad746e1d3b628ba79b9859f741e082542a38"
      "5502f25dbf55296c3a545e3872760ab7",
      "0x3617de4a96262c6f5d9e98bf9292dc29f8f41dbd289a147ce9da3113b5f0b8c0"
      "0a60b1ce1d7e819d7a431d7c90ea0e5f",
      "0x01"
    },
    {
      "NIST P-521", 521, 1,
      "0x01ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
      "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
      "0x01ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
      "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffc",
      "0x051953eb9618e1c9a1f929a21a0b68540eea2da725b99b315f3b8b489918ef10"
      "9e156193951ec7e937b1652c0bd3bb1bf073573df883d2c34f1ef451fd46b503f00",
      "0x1fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
      "ffa51868783bf2f966b7fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409",

      "0x00c6858e06b70404e9cd9e3ecb662395b4429c648139053fb521f828af606b4d"
      "3dbaa14b5e77efe75928fe1dc127a2ffa8de3348b3c1856a429bf97e7e31c2e5bd66",
      "0x011839296a789a3bc0045c8a5fb42c7d1bd998f54449579b446817afbd17273e"
      "662c97ee72995ef42640c550b9013fad0761353c7086a272c24088be94769fd16650",
      "0x01"
    },

    { "brainpoolP160r1", 160, 0,
      "0xe95e4a5f737059dc60dfc7ad95b3d8139515620f",
      "0x340e7be2a280eb74e2be61bada745d97e8f7c300",
      "0x1e589a8595423412134faa2dbdec95c8d8675e58",
      "0xe95e4a5f737059dc60df5991d45029409e60fc09",
      "0xbed5af16ea3f6a4f62938c4631eb5af7bdbcdbc3",
      "0x1667cb477a1a8ec338f94741669c976316da6321",
      "0x01"
    },

    { "brainpoolP192r1", 192, 0,
      "0xc302f41d932a36cda7a3463093d18db78fce476de1a86297",
      "0x6a91174076b1e0e19c39c031fe8685c1cae040e5c69a28ef",
      "0x469a28ef7c28cca3dc721d044f4496bcca7ef4146fbf25c9",
      "0xc302f41d932a36cda7a3462f9e9e916b5be8f1029ac4acc1",
      "0xc0a0647eaab6a48753b033c56cb0f0900a2f5c4853375fd6",
      "0x14b690866abd5bb88b5f4828c1490002e6773fa2fa299b8f",
      "0x01"
    },

    { "brainpoolP224r1", 224, 0,
      "0xd7c134aa264366862a18302575d1d787b09f075797da89f57ec8c0ff",
      "0x68a5e62ca9ce6c1c299803a6c1530b514e182ad8b0042a59cad29f43",
      "0x2580f63ccfe44138870713b1a92369e33e2135d266dbb372386c400b",
      "0xd7c134aa264366862a18302575d0fb98d116bc4b6ddebca3a5a7939f",
      "0x0d9029ad2c7e5cf4340823b2a87dc68c9e4ce3174c1e6efdee12c07d",
      "0x58aa56f772c0726f24c6b89e4ecdac24354b9e99caa3f6d3761402cd",
      "0x01"
    },

    { "brainpoolP256r1", 256, 0,
      "0xa9fb57dba1eea9bc3e660a909d838d726e3bf623d52620282013481d1f6e5377",
      "0x7d5a0975fc2c3057eef67530417affe7fb8055c126dc5c6ce94a4b44f330b5d9",
      "0x26dc5c6ce94a4b44f330b5d9bbd77cbf958416295cf7e1ce6bccdc18ff8c07b6",
      "0xa9fb57dba1eea9bc3e660a909d838d718c397aa3b561a6f7901e0e82974856a7",
      "0x8bd2aeb9cb7e57cb2c4b482ffc81b7afb9de27e1e3bd23c23a4453bd9ace3262",
      "0x547ef835c3dac4fd97f8461a14611dc9c27745132ded8e545c1d54c72f046997",
      "0x01"
    },

    { "brainpoolP320r1", 320, 0,
      "0xd35e472036bc4fb7e13c785ed201e065f98fcfa6f6f40def4f92b9ec7893ec28"
      "fcd412b1f1b32e27",
      "0x3ee30b568fbab0f883ccebd46d3f3bb8a2a73513f5eb79da66190eb085ffa9f4"
      "92f375a97d860eb4",
      "0x520883949dfdbc42d3ad198640688a6fe13f41349554b49acc31dccd88453981"
      "6f5eb4ac8fb1f1a6",
      "0xd35e472036bc4fb7e13c785ed201e065f98fcfa5b68f12a32d482ec7ee8658e9"
      "8691555b44c59311",
      "0x43bd7e9afb53d8b85289bcc48ee5bfe6f20137d10a087eb6e7871e2a10a599c7"
      "10af8d0d39e20611",
      "0x14fdd05545ec1cc8ab4093247f77275e0743ffed117182eaa9c77877aaac6ac7"
      "d35245d1692e8ee1",
      "0x01"
    },

    { "brainpoolP384r1", 384, 0,
      "0x8cb91e82a3386d280f5d6f7e50e641df152f7109ed5456b412b1da197fb71123"
      "acd3a729901d1a71874700133107ec53",
      "0x7bc382c63d8c150c3c72080ace05afa0c2bea28e4fb22787139165efba91f90f"
      "8aa5814a503ad4eb04a8c7dd22ce2826",
      "0x04a8c7dd22ce28268b39b55416f0447c2fb77de107dcd2a62e880ea53eeb62d5"
      "7cb4390295dbc9943ab78696fa504c11",
      "0x8cb91e82a3386d280f5d6f7e50e641df152f7109ed5456b31f166e6cac0425a7"
      "cf3ab6af6b7fc3103b883202e9046565",
      "0x1d1c64f068cf45ffa2a63a81b7c13f6b8847a3e77ef14fe3db7fcafe0cbd10e8"
      "e826e03436d646aaef87b2e247d4af1e",
      "0x8abe1d7520f9c2a45cb1eb8e95cfd55262b70b29feec5864e19c054ff9912928"
      "0e4646217791811142820341263c5315",
      "0x01"
    },

    { "brainpoolP512r1", 512, 0,
      "0xaadd9db8dbe9c48b3fd4e6ae33c9fc07cb308db3b3c9d20ed6639cca70330871"
      "7d4d9b009bc66842aecda12ae6a380e62881ff2f2d82c68528aa6056583a48f3",
      "0x7830a3318b603b89e2327145ac234cc594cbdd8d3df91610a83441caea9863bc"
      "2ded5d5aa8253aa10a2ef1c98b9ac8b57f1117a72bf2c7b9e7c1ac4d77fc94ca",
      "0x3df91610a83441caea9863bc2ded5d5aa8253aa10a2ef1c98b9ac8b57f1117a7"
      "2bf2c7b9e7c1ac4d77fc94cadc083e67984050b75ebae5dd2809bd638016f723",
      "0xaadd9db8dbe9c48b3fd4e6ae33c9fc07cb308db3b3c9d20ed6639cca70330870"
      "553e5c414ca92619418661197fac10471db1d381085ddaddb58796829ca90069",
      "0x81aee4bdd82ed9645a21322e9c4c6a9385ed9f70b5d916c1b43b62eef4d0098e"
      "ff3b1f78e2d0d48d50d1687b93b97d5f7c6d5047406a5e688b352209bcb9f822",
      "0x7dde385d566332ecc0eabfa9cf7822fdf209f70024a57b1aa000c55b881f8111"
      "b2dcde494a5f485e5bca4bd88a2763aed1ca2b2fa8f0540678cd1e0f3ad80892",
      "0x01"
    },
    {
      "GOST2001-test", 256, 0,
      "0x8000000000000000000000000000000000000000000000000000000000000431",
      "0x0000000000000000000000000000000000000000000000000000000000000007",
      "0x5fbff498aa938ce739b8e022fbafef40563f6e6a3472fc2a514c0ce9dae23b7e",
      "0x8000000000000000000000000000000150fe8a1892976154c59cfc193accf5b3",

      "0x0000000000000000000000000000000000000000000000000000000000000002",
      "0x08e2a8a0e65147d4bd6316030e16d19c85c97f0a9ca267122b96abbcea7e8fc8",
      "0x01"
    },
    {
      "GOST2001-CryptoPro-A", 256, 0,
      "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffd97",
      "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffd94",
      "0x00000000000000000000000000000000000000000000000000000000000000a6",
      "0xffffffffffffffffffffffffffffffff6c611070995ad10045841b09b761b893",
      "0x0000000000000000000000000000000000000000000000000000000000000001",
      "0x8d91e471e0989cda27df505a453f2b7635294f2ddf23e3b122acc99c9e9f1e14",
      "0x01"
    },
    {
      "GOST2001-CryptoPro-B", 256, 0,
      "0x8000000000000000000000000000000000000000000000000000000000000c99",
      "0x8000000000000000000000000000000000000000000000000000000000000c96",
      "0x3e1af419a269a5f866a7d3c25c3df80ae979259373ff2b182f49d4ce7e1bbc8b",
      "0x800000000000000000000000000000015f700cfff1a624e5e497161bcc8a198f",
      "0x0000000000000000000000000000000000000000000000000000000000000001",
      "0x3fa8124359f96680b83d1c3eb2c070e5c545c9858d03ecfb744bf8d717717efc",
      "0x01"
    },
    {
      "GOST2001-CryptoPro-C", 256, 0,
      "0x9b9f605f5a858107ab1ec85e6b41c8aacf846e86789051d37998f7b9022d759b",
      "0x9b9f605f5a858107ab1ec85e6b41c8aacf846e86789051d37998f7b9022d7598",
      "0x000000000000000000000000000000000000000000000000000000000000805a",
      "0x9b9f605f5a858107ab1ec85e6b41c8aa582ca3511eddfb74f02f3a6598980bb9",
      "0x0000000000000000000000000000000000000000000000000000000000000000",
      "0x41ece55743711a8c3cbf3783cd08c0ee4d4dc440d4641a8f366e550dfdb3bb67",
      "0x01"
    },
    {
      "GOST2012-test", 511, 0,
      "0x4531acd1fe0023c7550d267b6b2fee80922b14b2ffb90f04d4eb7c09b5d2d15d"
      "f1d852741af4704a0458047e80e4546d35b8336fac224dd81664bbf528be6373",
      "0x0000000000000000000000000000000000000000000000000000000000000007",
      "0x1cff0806a31116da29d8cfa54e57eb748bc5f377e49400fdd788b649eca1ac4"
      "361834013b2ad7322480a89ca58e0cf74bc9e540c2add6897fad0a3084f302adc",
      "0x4531acd1fe0023c7550d267b6b2fee80922b14b2ffb90f04d4eb7c09b5d2d15d"
      "a82f2d7ecb1dbac719905c5eecc423f1d86e25edbe23c595d644aaf187e6e6df",

      "0x24d19cc64572ee30f396bf6ebbfd7a6c5213b3b3d7057cc825f91093a68cd762"
      "fd60611262cd838dc6b60aa7eee804e28bc849977fac33b4b530f1b120248a9a",
      "0x2bb312a43bd2ce6e0d020613c857acddcfbf061e91e5f2c3f32447c259f39b2"
      "c83ab156d77f1496bf7eb3351e1ee4e43dc1a18b91b24640b6dbb92cb1add371e",
      "0x01"
    },
    {
      "GOST2012-tc26-A", 512, 0,
      "0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffdc7",
      "0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffdc4",
      "0xe8c2505dedfc86ddc1bd0b2b6667f1da34b82574761cb0e879bd081cfd0b6265"
        "ee3cb090f30d27614cb4574010da90dd862ef9d4ebee4761503190785a71c760",
      "0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
        "27e69532f48d89116ff22b8d4e0560609b4b38abfad2b85dcacdb1411f10b275",
      "0x0000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000003",
      "0x7503cfe87a836ae3a61b8816e25450e6ce5e1c93acf1abc1778064fdcbefa921"
        "df1626be4fd036e93d75e6a50e3a41e98028fe5fc235f5b889a589cb5215f2a4",
      "0x01"
    },
    {
      "GOST2012-tc26-B", 512, 0,
      "0x8000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000006f",
      "0x8000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000006c",
      "0x687d1b459dc841457e3e06cf6f5e2517b97c7d614af138bcbf85dc806c4b289f"
        "3e965d2db1416d217f8b276fad1ab69c50f78bee1fa3106efb8ccbc7c5140116",
      "0x8000000000000000000000000000000000000000000000000000000000000001"
        "49a1ec142565a545acfdb77bd9d40cfa8b996712101bea0ec6346c54374f25bd",
      "0x0000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000002",
      "0x1a8f7eda389b094c2c071e3647a8940f3c123b697578c213be6dd9e6c8ec7335"
        "dcb228fd1edf4a39152cbcaaf8c0398828041055f94ceeec7e21340780fe41bd",
      "0x01"
    },

    {
      "secp256k1", 256, 0,
      "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F",
      "0x0000000000000000000000000000000000000000000000000000000000000000",
      "0x0000000000000000000000000000000000000000000000000000000000000007",
      "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141",
      "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798",
      "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8",
      "0x01"
    },

    { NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
  };



/* Return the index of the domain_parms table for a curve with NAME.
   Return -1 if not found.  */
static int
find_domain_parms_idx (const char *name)
{
  int idx, aliasno;

  /* First check our native curves.  */
  for (idx = 0; domain_parms[idx].desc; idx++)
    if (!strcmp (name, domain_parms[idx].desc))
      return idx;

  /* If not found consult the alias table.  */
  if (!domain_parms[idx].desc)
    {
      for (aliasno = 0; curve_aliases[aliasno].name; aliasno++)
        if (!strcmp (name, curve_aliases[aliasno].other))
          break;
      if (curve_aliases[aliasno].name)
        {
          for (idx = 0; domain_parms[idx].desc; idx++)
            if (!strcmp (curve_aliases[aliasno].name, domain_parms[idx].desc))
              return idx;
        }
    }

  return -1;
}
