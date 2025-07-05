#pragma once
#include "Prerequisites.h"

class
CryptoGenerator {
public:
	
	CryptoGenerator() {
	  std::random_device rd;  
		m_engine.seed(rd());    
	}

	~CryptoGenerator() = default;

	std::string
	generatePassword(unsigned int length,
									 bool useUpper = true,
									 bool useLower = true,
									 bool useDigits = true,
									 bool useSymbols = false) {
		const std::string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string lowers = "abcdefghijklmnopqrstuvwxyz";
		const std::string digits = "0123456789";
		const std::string symbols = "!@#$%^&*()-_=+[]{}|;:',.<>?/";

		std::string pool;
		if (useUpper) pool += uppers;
		if (useLower) pool += lowers;
		if (useDigits) pool += digits;
		if (useSymbols) pool += symbols;

		if (pool.empty()) {
			throw std::runtime_error("No character types enabled for password generation.");
		}

		std::uniform_int_distribution<unsigned int> dist(0, pool.size() - 1);
		std::string password;
		password.reserve(length);  

		for (unsigned int i = 0; i < length; ++i) {
			password += pool[dist(m_engine)];
		}
		return password; 
	}


	std::vector<uint8_t>
	generateBytes(unsigned int numBytes) {
		std::vector<uint8_t> bytes(numBytes);
		std::uniform_int_distribution<int> dist(0, 255); 
		for (unsigned int i = 0; i < numBytes; ++i) {
			bytes[i] = static_cast<uint8_t>(dist(m_engine));  
		}
		return bytes;  
	}

	std::string
	toHex(const std::vector<uint8_t>& data) {
		std::ostringstream oss;

		for (const auto& byte : data) {
			oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
		}
		return oss.str();  
	}

	std::vector<uint8_t>
	fromHex(const std::string& hex) {
		if (hex.size() % 2 != 0)
			throw std::runtime_error("Hex inválido (longitud impar).");

		std::vector<uint8_t> data(hex.size() / 2);
		for (size_t i = 0; i < data.size(); ++i) {
			unsigned int byte;
			std::istringstream(hex.substr(2 * i, 2)) >> std::hex >> byte;
			data[i] = static_cast<uint8_t>(byte);
		}
		return data;
	}

	std::vector<uint8_t>
	generateKey(unsigned int bits) {
		if (bits % 8 != 0) {
			throw std::runtime_error("Bits debe ser múltiplo de 8.");
		}
		return generateBytes(bits / 8);
	}

	std::vector<uint8_t>
	generateIV(unsigned int blockSize) {
		return generateBytes(blockSize);  
	}

	
	std::vector<uint8_t>
	generateSalt(unsigned int length) {
		return generateBytes(length);
	}

	std::string
	toBase64(const std::vector<uint8_t>& data) {
		static const char* table =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";
		std::string b64;
		unsigned int i = 0;

		
		while (i + 2 < data.size()) {
			unsigned int block = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
			b64 += table[(block >> 18) & 0x3F];
			b64 += table[(block >> 12) & 0x3F];
			b64 += table[(block >> 6) & 0x3F];
			b64 += table[(block) & 0x3F];
			i += 3;
		}

		if (i < data.size()) {
			uint32_t block = data[i] << 16;
			b64 += table[(block >> 18) & 0x3F];
			if (i + 1 < data.size()) {
				block |= data[i + 1] << 8;
				b64 += table[(block >> 12) & 0x3F];
				b64 += table[(block >> 6) & 0x3F];
				b64 += '=';
			}
			else {
				b64 += table[(block >> 12) & 0x3F];
				b64 += "==";
			}
		}

		return b64; 
	}

	std::vector<uint8_t>
		fromBase64(const std::string& b64) {
		std::lock_guard<std::mutex> lock(_mtx);
		std::vector<uint8_t> out;
		size_t len = b64.size();
		size_t pad = 0;

		if (len >= 1 && b64[len - 1] == '=') pad++;
		if (len >= 2 && b64[len - 2] == '=') pad++;
		out.reserve(((len / 4) * 3) - pad);

		unsigned int i = 0;
		while (i < len) {
			uint32_t block = 0;
			unsigned int chars = 0;
			for (unsigned int j = 0; j < 4 && i < len; ++j, ++i) {
				uint8_t v = _decTable[(unsigned char)b64[i]];
				if (v == 0xFF) { j--; continue; }
				block = (block << 6) | v;  
				chars++;
			}
			for (unsigned int k = 0; k < chars - 1; ++k) {
				out.push_back((block >> (8 * (chars - 2 - k))) & 0xFF);
			}
		}
		return out
	}

	void
	secureWipe(std::vector<uint8_t>& data) {
		std::fill(data.begin(), data.end(), 0);
	}

	bool
	validatePassword(const std::string& password) {
		if (password.size() < 8) return false;
		bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbols = false;
		for (char c : password) {
			if (std::isupper((unsigned char)c)) {
				hasUpper = true;
			}
			else if (std::islower((unsigned char)c)) {
				hasLower = true;
			}
			else if (std::isdigit((unsigned char)c)) {
				hasDigit = true;
			}
			else if (std::ispunct((unsigned char)c)) {
				hasSymbols = true;
			}
		}

		return hasUpper && hasLower && hasDigit && hasSymbols;
	}

private:
	std::mt19937 m_engine;  // Motor de generación de números aleatorios Mersenne Twister.
	std::mutex _mtx;          // Mutex para uso thread-safe.
	std::array<uint8_t, 256> _decTable;  // Tabla de decodificación Base64.

};