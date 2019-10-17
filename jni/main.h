#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include "cryptopp/aes.h"
#include "cryptopp/md5.h"
#include "cryptopp/modes.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/base64.h"


//-------------------
//some namespace are necessary
using namespace std;
using namespace CryptoPP;
//-----------RSA-------------
void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed);
string RSAEncryptString(const char *pubFilename, const char *seed, const char *message);
string RSADecryptString(const char *privFilename, const char *ciphertext);
RandomPool & GlobalRNG();



//----------AES----------
/* key is simple,if you need a complex key, click {@link "https://asecuritysite.com/encryption/keygen"}
** initialization vector, if u dont understand, look at {@link "https://en.wikipedia.org/wiki/Initialization_vector"}
** key="0000000000123456"  ： this is 128 bit key,if you wanna else,you can choose MIN_KEYLENGTH and MAX_KEYLENGTH.
** pls look at {@link "https://www.cryptopp.com/wiki/Advanced_Encryption_Standard#Default_Key_Length"} 
*/
#define USING AES256 true

//IV="0000000000123456" 
static uint8_t iv[CryptoPP::AES::BLOCKSIZE] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '3', '4', '5', '6' };

//128 "0000000000123456" 
//static uint8_t key[CryptoPP::AES::DEFAULT_KEYLENGTH] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '3', '4', '5', '6' };
//256 "00000000001234560000000000123456" 
static uint8_t key[CryptoPP::AES::MAX_KEYLENGTH] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '3', '4', '5', '6','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '3', '4', '5', '6' };






static string plaintext = "中文|English|!@#$%^&*()<>.";
//static string plaintext = "中文|English|!@#$%^&*()<>\n this is next line.";
