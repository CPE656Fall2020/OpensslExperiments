#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <openssl/aes.h>

//forward declarations
static int test_encrypt_ecb(void);

int main(void)
{
    return test_encrypt_ecb();
}

void print(const char *str, unsigned char *in, unsigned char *out)
{
    int i;

    printf("%s\n", str);
    printf("Input:\t");
    for (i = 0; i < AES_BLOCK_SIZE; i++)
        printf("%x", in[i]);
    printf("\n");
    printf("Output:\t");
    for (i = 0; i < AES_BLOCK_SIZE; i++)
        printf("%x", out[i]);
    printf("\n\n");
}

static int test_encrypt_ecb(void)
{
    unsigned char key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                      0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
    unsigned char expected_out[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
    unsigned char in[]  = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
    unsigned char out[]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    unsigned int i;
    unsigned int success = 0;
    unsigned int failure = 0;
    unsigned long num_encryptions = 0;

    //Set encryption key
    AES_KEY encrypt_key;
    AES_set_encrypt_key(key, 256, &encrypt_key);


    time_t start, end;
    start = time(NULL);

    printf("Beginning ECB Encryption!\n");
    do {
        AES_ecb_encrypt(in, out, &encrypt_key, AES_ENCRYPT);
        time(&end);
        num_encryptions++;

        if (0 == memcmp(out, expected_out, 16)) {
            success++;
        } else {
            failure++;
        }
        for(i=15; i<16; i--) out[i]=0x00;
    } while(end - start < 100);
    if(success > 0 && failure == 0) {
        printf("Success!\n");
        printf("Bytes processed: %lu\n", (num_encryptions*16));
        printf("Time total: %ld\n", (end-start));
        return 0;
    }
    else {
        printf("Failure!\n");
        return 1;
    }
}
