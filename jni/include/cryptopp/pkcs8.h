// pkcs8.h - PKCS8 read and write routines. Written and placed in the public domain by Jeffrey Walton
//
// Crypto++ Library is copyrighted as a compilation and (as of version 5.6.2) licensed
// under the Boost Software License 1.0, while the individual files in the compilation
// are all public domain.

///////////////////////////////////////////////////////////////////////////
// For documentation on the PEM read and write routines, see
//   http://www.cryptopp.com/wiki/PKCS8_Pack
///////////////////////////////////////////////////////////////////////////

// Why Not Specialize Function Templates?
//   http://www.gotw.ca/publications/mill17.htm

#ifndef CRYPTOPP_PKCS8_H
#define CRYPTOPP_PKCS8_H

#include "pubkey.h"
#include "eccrypto.h"
#include "integer.h"
#include "dsa.h"
#include "rsa.h"

NAMESPACE_BEGIN(CryptoPP)

//////////////////////////////////////////////////////////////////////////////////////////

// Begin the Read routines.
//
// On failure, any number of Crypto++ exceptions are thrown. No custom
//   exceptions are thrown.

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, RSA::PrivateKey& rsa);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, RSA::PrivateKey& rsa,
                             const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DSA::PrivateKey& dsa);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DSA::PrivateKey& dsa,
                             const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_PrivateKey_EC<ECP>& ec);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_PrivateKey_EC<ECP>& ec,
                             const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_PrivateKey_EC<EC2N>& ec);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_PrivateKey_EC<EC2N>& ec,
                             const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_Keys_ECDSA<ECP>::PrivateKey& ecdsa);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_Keys_ECDSA<ECP>::PrivateKey& ecdsa,
                             const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_Keys_ECDSA<EC2N>::PrivateKey& ecdsa);
CRYPTOPP_DLL void PKCS8_Load(BufferedTransformation& bt, DL_Keys_ECDSA<EC2N>::PrivateKey& ecdsa,
                             const char* password, size_t length);

//////////////////////////////////////////////////////////////////////////////////////////

// Begin the Write routines.
//
// On failure, any number of Crypto++ exceptions are thrown. No custom
//   exceptions are thrown.

CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const RSA::PrivateKey& rsa);
CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const RSA::PrivateKey& rsa,
                             const std::string& algorithm, const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DSA::PrivateKey& dsa);
CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DSA::PrivateKey& dsa,
                             const std::string& algorithm, const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_PrivateKey_EC<ECP>& ec);
CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_PrivateKey_EC<ECP>& ec,
                             const std::string& algorithm, const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_PrivateKey_EC<EC2N>& ec);
CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_PrivateKey_EC<EC2N>& ec,
                             const std::string& algorithm, const char* password, size_t length);

CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_Keys_ECDSA<ECP>::PrivateKey& ecdsa);
CRYPTOPP_DLL void PKCS8_Save(BufferedTransformation& bt, const DL_Keys_ECDSA<ECP>::PrivateKey& ecdsa,
                             const std::string& algorithm, const char* password, size_t length);

NAMESPACE_END

#endif // CRYPTOPP_PKCS8_H
