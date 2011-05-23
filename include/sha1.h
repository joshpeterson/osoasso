#ifndef __SHA1_H
#define __SHA1_H

// Taken from Steve Reid's public domain SHA1 implementation

#include <vector>
#include <string>

#define SHA1_DIGEST_SIZE 20

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/* blk0() and blk() perform the initial expand. */
/* I got the idea of expanding during the round function from SSLeay */
/* FIXME: can we do this in an endian-proof way? */
#ifdef WORDS_BIGENDIAN
#define blk0(i) block->l[i]
#else
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00) \
    |(rol(block->l[i],8)&0x00FF00FF))
#endif
#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15] \
    ^block->l[(i+2)&15]^block->l[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);

namespace osoasso
{

class sha1
{
public:
    sha1();
    ~sha1();

    std::string hash(const std::vector<unsigned char>& data);

private:
    typedef struct {
        uint32_t state[5];
        uint32_t count[2];
        uint8_t  buffer[64];
    } sha1_ctx;

    sha1_ctx* context;

    void update(const uint8_t* data, const size_t len);
    void final(uint8_t digest[SHA1_DIGEST_SIZE]);
    void transform(uint32_t state[5], const uint8_t buffer[64]);
    void digest_to_hex(const uint8_t digest[SHA1_DIGEST_SIZE], char *output);
};

}

#endif // __SHA1_H
