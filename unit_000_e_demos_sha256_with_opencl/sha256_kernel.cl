__constant uchar k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

inline uchar rotateRight(uchar n, uchar d) {
    return (n >> d) | (n << (32 - d));
}

inline uchar choice(uchar x, uchar y, uchar z) {
    return (x & y) ^ (~x & z);
}

inline uchar majority(uchar x, uchar y, uchar z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

inline uchar sigma0(uchar x) {
    return rotateRight(x, 2) ^ rotateRight(x, 13) ^ rotateRight(x, 22);
}

inline uchar sigma1(uchar x) {
    return rotateRight(x, 6) ^ rotateRight(x, 11) ^ rotateRight(x, 25);
}

inline uchar delta0(uchar x) {
    return rotateRight(x, 7) ^ rotateRight(x, 18) ^ (x >> 3);
}

inline uchar delta1(uchar x) {
    return rotateRight(x, 17) ^ rotateRight(x, 19) ^ (x >> 10);
}

__kernel void sha256(__global const uchar* data, __global uchar* hash) {
    uchar a, b, c, d, e, f, g, h, T1, T2;
    uchar W[64];
    uchar temp1, temp2;

    // Initialize hash values
    uchar h0 = 0x6a09e667;
    uchar h1 = 0xbb67ae85;
    uchar h2 = 0x3c6ef372;
    uchar h3 = 0xa54ff53a;
    uchar h4 = 0x510e527f;
    uchar h5 = 0x9b05688c;
    uchar h6 = 0x1f83d9ab;
    uchar h7 = 0x5be0cd19;

    // Pre-processing
    // Append "1" bit to message
    // Append "0" bits until message length in bits ≡ 448 (mod 512)
    // Append bit length of message as 64-bit big-endian integer
    // (This step is simplified for example purposes)

    // Process the message in successive 512-bit chunks:
    // for each 512-bit chunk of padded message
    // break chunk into sixteen 32-bit big-endian words w[i], 0 ≤ i ≤ 15

    // Message schedule: extend the sixteen 32-bit words into sixty-four 32-bit words:
    for (int i = 0; i < 64; i++) {
        if (i < 16) W[i] = data[i]; // Directly from the message
        else W[i] = delta1(W[i-2]) + W[i-7] + delta0(W[i-15]) + W[i-16];
    }

    // Initialize working variables to current hash value:
    a = h0;
    b = h1;
    c = h2;
    d = h3;
    e = h4;
    f = h5;
    g = h6;
    h = h7;

    // Compression function main loop:
    for (int i = 0; i < 64; i++) {
        T1 = h + sigma1(e) + choice(e, f, g) + k[i] + W[i];
        T2 = sigma0(a) + majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Add the compressed chunk to the current hash value:
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;

    // Produce the final hash value (big-endian):
    hash[0] = h0;
    hash[1] = h1;
    hash[2] = h2;
    hash[3] = h3;
    hash[4] = h4;
    hash[5] = h5;
    hash[6] = h6;
    hash[7] = h7;
}
