#include <iostream>
#include <openssl/evp.h>

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

#define GCM_AUTH_TAG_LEN 16

void Create_Context(EVP_CIPHER_CTX** ctx);
int Destroy_Context(EVP_CIPHER_CTX* ctx);
int Init_Context(EVP_CIPHER_CTX* ctx, const EVP_CIPHER** evp, const uint8_t* key, int KeySize);
int Set_IV(EVP_CIPHER_CTX* ctx, uint8_t* iv, int isEncDir);
int Set_aad(EVP_CIPHER_CTX* ctx, unsigned char* inbuf, int tagLen, int addLen, unsigned char dummy_tag[GCM_AUTH_TAG_LEN]);
void Encrypt_Data(EVP_CIPHER_CTX* ctx, unsigned char* inbuf, unsigned char* Outbuf, int encLen, unsigned char* AuthTag, int tag_len);
int Decrypt_Data(EVP_CIPHER_CTX* ctx, unsigned char* EncData, unsigned char* DecData, int encLen, int tag_len);
void print_buffer(const char* name, unsigned char* data, int len);


int main()
{
    //Declaration: Start
    //EVP_CIPHER_CTX* ctxEnc;
    //const EVP_CIPHER* evpEnc = NULL;

    EVP_CIPHER_CTX* ctxDec;
    const EVP_CIPHER* evpDec = NULL;

    int tag_len = 16;
    int encLen;
    unsigned char dummy_tag[GCM_AUTH_TAG_LEN] = { 0 };

    //const uint8_t key[] = { 0x8d,0x50,0x03,0x49,0xe1,0xe2,0x07,0xaa,0xcf,0x03,0x94,0x02,0xbe,0xa8,0x16,0xef };
    const uint8_t key[] = { 0x21 ,0x60 ,0x41 ,0xcf ,0x6f ,0x9a ,0xe9 ,0xec ,0xad ,0xe9 ,0x48 ,0x4b ,0x5f ,0xab ,0xfe ,0x03 };

    int KeySize = 16;
    //uint8_t iv[] = { 0xe9,0x73,0x7c,0x39,0x5e,0xf0,0x0c,0x82,0x05,0x11,0x86,0x94 };
    uint8_t iv[] = { 0x3a ,0xaf ,0x78 ,0x8e ,0xfb ,0x80 ,0xfc ,0x02 ,0x4b ,0xbb ,0xe8 ,0x62 };

    unsigned char aad_4Bytes[] = { 0x80,0x00,0x00,0x01 };
    //ASCII Data: "This is Test String. AESGCM128 algorithm is being used for encryption and decryption" (In Encrypted Format)
    unsigned char inbuf[] = { 0x9b, 0xcc, 0x00, 0x16, 0x96, 0xfc, 0x98, 0xc7, 0x9d, 0x0b, 0x44, 0x40, 0x03, 0x9f, 0x8a, 0xf1, 0x88, 0x30, 0x1b, 0x5c, 0x15, 0x06, 0x00, 0x85, 0xab, 0x5a, 0x64, 0x5d, 0x7f, 0x52, 0x49, 0x57, 0x9c, 0xb6, 0xbb, 0x39, 0x06, 0x27, 0xad, 0xce, 0x85, 0x98, 0xee, 0x84, 0x23, 0x1a, 0xc6, 0x8c, 0x09, 0x7d, 0x0e, 0x84, 0x31, 0x04, 0x85, 0xcd, 0x31, 0x0b, 0x1a, 0x92, 0x7d, 0x68, 0xc3, 0xe7, 0x3b, 0x1d, 0xca, 0x92, 0x6e, 0x37, 0xbb, 0xcb, 0x0f, 0xe5, 0xf1, 0xf4, 0x65, 0x84, 0x52, 0xb9, 0xc7, 0x6e, 0x80, 0x22, 0x15, 0x89, 0xae, 0x58, 0xce, 0x0c, 0x22, 0x7c, 0x6b, 0x16, 0x58, 0xea, 0xc1, 0x22, 0x10, 0xa7, 0xf1, 0x7d, 0xe5, 0xf8, 0xbb, 0xd2, 0xae, 0x28 };
    
    unsigned char Outbuf[256] = { 0 };
    unsigned char EncPacket[256] = { 0 };
    unsigned char DecPacket[256] = { 0 };
    //unsigned char WolfDecPacket[256] = { 0 };
    unsigned char AuthTag[16] = { 0 };
    //Declaration: End

    //Decrypting Data(by WolfSSL) which is Encrypted by OpenSSL lib
   
    print_buffer("\nOpenSSL Encrypted Packet Data:", inbuf, sizeof(inbuf));

    // ========================== Decryption END ========================== //

    //Create & Init Context
    Create_Context(&ctxDec);
    Init_Context(ctxDec, &evpDec, key, KeySize);    
    
    encLen = sizeof(inbuf) - 8 - 16; //8(aad) + 16(Auth Tag)
    
    //Setting IV
    if (0 != Set_IV(ctxDec, iv, 0)) //Dec Direction - 0, Enc Direction - 1
    {
        printf("Set_IV Failed\n");
        return -1;
    }

    //Setting aad : 8 Bytes
    if (0 != Set_aad(ctxDec, inbuf, 16, 8, dummy_tag))
    {
        printf("Set_aad_8 Failed\n");
        return -1;
    }

    //Setting aad : 4 Bytes
    if (0 != Set_aad(ctxDec, aad_4Bytes, 16, 4, dummy_tag))
    {
        printf("Set_aad_4 Failed\n");
        return -1;
    }

    memcpy(DecPacket, inbuf, 8);   //Copying First 8 Bytes to Decrypt Buffer
    memcpy(DecPacket + 8 + encLen, inbuf + 8 + encLen, 16);   //Copying Auth Tag to Decrypt Buffer

    if (0 != Decrypt_Data(ctxDec, inbuf, Outbuf, encLen, tag_len))
    {
        printf("\nDecryption Failed\n");
        return -1;
    }

    print_buffer("\n\nPacket Data (Decrypted by WolfSSL):", Outbuf, 8 + encLen);

    Destroy_Context(ctxDec);
    
    // ========================== Decryption END ========================== //
}

void Create_Context(EVP_CIPHER_CTX** ctx)
{
    *ctx = EVP_CIPHER_CTX_new();
}

int Init_Context(EVP_CIPHER_CTX* ctx, const EVP_CIPHER** evp, const uint8_t* key, int KeySize)
{
    switch (KeySize) {
    case 32/*SRTP_AES_256_KEY_LEN*/:
        *evp = EVP_aes_256_gcm();
        break;
    case 16/*SRTP_AES_128_KEY_LEN*/:
        *evp = EVP_aes_128_gcm();
        break;
    }

    if (!EVP_CipherInit_ex(ctx, *evp, NULL, key, NULL, 0)) {
        return -1;
    }

    return 0;
}

int Set_IV(EVP_CIPHER_CTX* ctx, uint8_t* iv, int isEncDir)
{
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, 0)) {
        return -1;
    }
    if (!EVP_CipherInit_ex(ctx, NULL, NULL, NULL, iv, isEncDir))
    {
        return -1;
    }
    return 0;
}

int Set_aad(EVP_CIPHER_CTX* ctx, unsigned char* inbuf, int tagLen, int addLen, unsigned char dummy_tag[GCM_AUTH_TAG_LEN])
{
    int retVal;
    memset(dummy_tag, 0x0, GCM_AUTH_TAG_LEN);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tagLen, &dummy_tag);

    retVal = EVP_Cipher(ctx, NULL, inbuf, addLen);
    if (retVal != addLen) {
        return -1;
    }
    return 0;
}

void Encrypt_Data(EVP_CIPHER_CTX* ctx, unsigned char* inbuf, unsigned char* Outbuf, int encLen, unsigned char* AuthTag, int tag_len)
{
    //Encrypt Data
    EVP_Cipher(ctx, inbuf + 8, inbuf + 8, encLen);

    // Calculate the tag
    EVP_Cipher(ctx, NULL, NULL, 0);

    // Retreive the tag
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag_len, AuthTag);
}

int Decrypt_Data(EVP_CIPHER_CTX* ctx, unsigned char* EncData, unsigned char* DecData, int encLen, int tag_len)
{
    int retVal;

    retVal = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag_len, EncData + 8 + encLen);

    retVal = EVP_Cipher(ctx, DecData + 8, EncData + 8, encLen);

    if (-1 == retVal) 
    //if (0 == retVal)
    {
        printf("\nEVP_Cipher FAILED\n");
        return -1;
    }
    /*
    * Check the tag
    */
    //Auth Tag Check Failing due to EVP_Cipher API's conditional check
   if (EVP_Cipher(ctx, NULL, NULL, 0)) {
        printf("\nTag Check FAILED\n");
        return -1;
    }

    return 0;
}

int Destroy_Context(EVP_CIPHER_CTX* ctx)
{
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }

    return 0;
}

//Print Buffer in HEX
void print_buffer(const char* name, unsigned char* data, int len)
{
    int i; printf("%s", name); for (i = 0; i < len; i++) { if ((i % 8) == 0) printf("\n "); printf("0x%02x, ", data[i]); } printf("\n");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   5. In the future, to open this project again, go to File > Open > Project and select the .sln file