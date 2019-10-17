#include "main.h"

//----------------------RSA-----------------
void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed)
{
       RandomPool randPool;
       randPool.Put((byte *)seed, strlen(seed));

       RSAES_OAEP_SHA_Decryptor priv(randPool, keyLength);
       HexEncoder privFile(new FileSink(privFilename));
       priv.DEREncode(privFile);
       privFile.MessageEnd();

       RSAES_OAEP_SHA_Encryptor pub(priv);
       HexEncoder pubFile(new FileSink(pubFilename));
       pub.DEREncode(pubFile);
       pubFile.MessageEnd();
}

string RSAEncryptString(const char *pubFilename, const char *seed, const char *message)
{
       FileSource pubFile(pubFilename, true, new HexDecoder);
       RSAES_OAEP_SHA_Encryptor pub(pubFile);

       RandomPool randPool;
       randPool.Put((byte *)seed, strlen(seed));

       string result;
       StringSource(message, true, new PK_EncryptorFilter(randPool, pub, new HexEncoder(new StringSink(result))));
       return result;
}

string RSADecryptString(const char *privFilename, const char *ciphertext)
{
       FileSource privFile(privFilename, true, new HexDecoder);
       RSAES_OAEP_SHA_Decryptor priv(privFile);

       string result;
       StringSource(ciphertext, true, new HexDecoder(new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(result))));
       return result;

}

//------------------------
// define static random pool
//------------------------
RandomPool & GlobalRNG()
{
       static RandomPool randomPool;
       return randomPool;
}


//------------------AES--------------------------

void HexPrint(string datas)
{
    int datasize = datas.size();
    for (int i = 0; i < datasize; i++)
    {
        std::cout << std::hex << (0xFF & static_cast<uint8_t>(datas[i]));
    }
    std::cout << "/nhex: " <<std::dec << std::endl;
    return;
}


//====== aes 128 cbc cts no_padding ======
string AES_CBCCTS_En(string datas)
{
    string strCiphertext = "";
    CryptoPP::CBC_CTS_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
    //CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
    StringSource(datas, true,
        new StreamTransformationFilter(
            encrypt,
            // new StringSink(strCiphertext),
            new Base64Encoder(new StringSink(strCiphertext)),
            BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,
            true)
            );
    return strCiphertext;
}

//======aes 128 cbc cts no_padding ======
string AES_CBCCTS_De(string endatas)
{
    string strDecryptedText = "";
//     CryptoPP::AES::Decryption aesDecryption(key, sizeof(key));
//     CryptoPP::CBC_Mode_ExternalCipher::Decryption decrypt(aesDecryption, iv);
    CryptoPP::CBC_CTS_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    //CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    //CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    StringSource(
        endatas,
        true,
        new Base64Decoder(new StreamTransformationFilter(decrypt,new StringSink(strDecryptedText),
            BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,
            true))
        );
    return strDecryptedText;
}


///======AES 128 CBC  PKCS_PADDING============= {@link https://www.cryptopp.com/wiki/CBC_Mode}
string AES_CBC_En(string data){
    std::string encrypt_str;
	try {
		//CBC_Mode
		CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption cbc_encription(key, sizeof(key), iv);
		
		CryptoPP::StreamTransformationFilter stf_encription(cbc_encription,
			//new CryptoPP::StringSink(encrypt_str)
			new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encrypt_str)),
			// if you want to change padding ,pls choose one:NO_PADDING, ZEROS_PADDING, PKCS_PADDING, ONE_AND_ZEROS_PADDING,W3C_PADDING, DEFAULT_PADDING
			CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
	
		stf_encription.Put(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
		stf_encription.MessageEnd();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	return encrypt_str;
}

//AES 128 CBC  PKCS_PADDING De
string AES_CBC_De(string base64_data){
   try {
        //1.decodes base64_data to set aes_encrypt_data
		string aes_encrypt_data; 
        new StringSource(base64_data, true,
            new Base64Decoder(new StringSink(aes_encrypt_data)) 
        );
        //2.decrypt
		string decrypt_data;
		CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption cbc_description(key, sizeof(key), iv);
		CryptoPP::StreamTransformationFilter stf_description(cbc_description,
			new CryptoPP::StringSink(decrypt_data), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
		stf_description.Put(reinterpret_cast<const unsigned char*>(aes_encrypt_data.c_str()), aes_encrypt_data.length());
		stf_description.MessageEnd();
		return decrypt_data;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return "";
	}
    
}

//====== AES 128 ECB PKCS_PADDING ====== {@link https://www.cryptopp.com/wiki/ECB_Mode}
string AES_ECB_En(string datas)
{
    try {
        string strCiphertext = "";
        CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
        StringSource(datas, true,
            new StreamTransformationFilter(
                encrypt,
                new Base64Encoder(new StringSink(strCiphertext)),
                BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING,
                true)
                );
        return strCiphertext;
    }
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}

string AES_ECB_De(string endatas)
{
    string strDecryptedText = "";
    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    StringSource(
        endatas,
        true,
        new Base64Decoder(new StreamTransformationFilter(decrypt,new StringSink(strDecryptedText),
            BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING,
            true))
        );
    return strDecryptedText;
}

//====== AES 128 CTR ====== {@link https://www.cryptopp.com/wiki/CTR_Mode}
string AES_CTR_En(string datas)
{
    try {
        string strCiphertext = "";
        CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
        StringSource(datas, true,
            new StreamTransformationFilter(
                encrypt,
                new Base64Encoder(new StringSink(strCiphertext)),
                BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,//only NO_PADDING
                true)
                );
        return strCiphertext;
    }
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}

string AES_CTR_De(string endatas)
{
    string strDecryptedText = "";
    CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    StringSource(
        endatas,
        true,
        new Base64Decoder(new StreamTransformationFilter(decrypt,new StringSink(strDecryptedText),
            BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,
            true))
        );
    return strDecryptedText;
}


//====== AES 128 CFB ====== {@link https://www.cryptopp.com/wiki/CFB_Mode}
string AES_CFB_En(string datas)
{
    try {
        string strCiphertext = "";
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
        StringSource(datas, true,
            new StreamTransformationFilter(
                encrypt,
                new Base64Encoder(new StringSink(strCiphertext)),
                BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,//only NO_PADDING
                true)
                );
        return strCiphertext;
    }
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}

string AES_CFB_De(string endatas)
{
    string strDecryptedText = "";
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    StringSource(
        endatas,
        true,
        new Base64Decoder(new StreamTransformationFilter(decrypt,new StringSink(strDecryptedText),
            BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,//only NO_PADDING
            true))
        );
    return strDecryptedText;
}


//====== AES 128 OFB ====== {@link https://www.cryptopp.com/wiki/OFB_Mode}
string AES_OFB_En(string datas)
{
    try {
        string strCiphertext = "";
        CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption encrypt(key, sizeof(key), iv);
        StringSource(datas, true,
            new StreamTransformationFilter(
                encrypt,
                new Base64Encoder(new StringSink(strCiphertext)),
                BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,//only NO_PADDING
                true)
                );
        return strCiphertext;
    }
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}

string AES_OFB_De(string endatas)
{
    string strDecryptedText = "";
    CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption decrypt(key, sizeof(key), iv);
    StringSource(
        endatas,
        true,
        new Base64Decoder(new StreamTransformationFilter(decrypt,new StringSink(strDecryptedText),
            BlockPaddingSchemeDef::BlockPaddingScheme::NO_PADDING,//only NO_PADDING
            true))
        );
    return strDecryptedText;
}


//------------------------
// the function is a no java test entry, after run ndk-build,you can execute 'sh build_and_run_in_avd.sh'
//------------------------
int main()
{

    cout << "\t================RSA================" << endl;
    //1.RSA begin
    char priKey[128] = {0};
    char pubKey[128] = {0};
    char seed[1024] = {0};

    //  generate a set of RSA key.
    strcpy(priKey, "pri"); // generate a private key
    strcpy(pubKey, "pub"); // generate a public key
    strcpy(seed, "seed");
    GenerateRSAKey(1024, priKey, pubKey, seed);

    char message[1024] = "Hello World ...";
    cout << "Origin Text:\t" << message << endl;
    string encryptedText = RSAEncryptString(pubKey, seed, message); // RSA encrypting
    cout << "Encrypted Text:\t" << encryptedText<< endl;
    string decryptedText = RSADecryptString(priKey, encryptedText.c_str()); // RSA decrypting
    cout << "Decrypted Text:\t" << decryptedText << endl;
    //RSA end
    
    //2.AES begin
    cout << "\t================AES================" << endl;

    cout << "Origin Text: " << plaintext << endl;
    cout << endl;

    string aes_en,aes_de;


    //AES CBC 
    aes_en = AES_CBC_En(plaintext);
    cout << "CBC Encrypt: " << aes_en;
    aes_de  = AES_CBC_De(aes_en);
    cout<< "CBC Decrypt: " << aes_de << endl;
    cout << endl;

    //AES CBC_CTS 
    aes_en = AES_CBCCTS_En(plaintext);
    cout << "CBC_CTS Encrypt: " << aes_en;
    aes_de = AES_CBCCTS_De(aes_en);
    cout << "CBC_CTS Decrypt: " << aes_de << endl;
    cout << endl;
    
    //AES ECB 
    aes_en = AES_ECB_En(plaintext);
    cout << "ECB Encrypt: " << aes_en;
    aes_de = AES_ECB_De(aes_en);
    cout << "ECB Decrypt: " << aes_de << endl;
    cout << endl;

    //AES CTR 
    aes_en = AES_CTR_En(plaintext);
    cout << "CTR Encrypt: " << aes_en;
    aes_de = AES_CTR_De(aes_en);
    cout << "CTR Decrypt: " << aes_de << endl;
    cout << endl;

    //AES CFB 
    aes_en = AES_CFB_En(plaintext);
    cout << "CFB Encrypt: " << aes_en;
    aes_de = AES_CFB_De(aes_en);
    cout << "CFB Decrypt: " << aes_de << endl;
    cout << endl;
    
    //AES OFB 
    aes_en = AES_OFB_En(plaintext);
    cout << "OFB Encrypt: " << aes_en;
    aes_de = AES_OFB_De(aes_en);
    cout << "OFB Decrypt: " << aes_de << endl;
    cout << endl;

    //AES end.
    cout << endl;

    return 0;
}
