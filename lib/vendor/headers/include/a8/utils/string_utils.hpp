//
// Created by Dalio on 2020/2/14.
//

#ifndef A8_STRING_UTILS_HPP
#define A8_STRING_UTILS_HPP

#include <string>
#include <vector>

enum TransferEncode {
    base16,
    base64
};

// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);

// trim from start (copying)
std::string ltrim_copy(std::string s);

// trim from end (copying)
std::string rtrim_copy(std::string s);

// trim from both ends (copying)
std::string trim_copy(std::string s);

bool iequals(const std::string &a, const std::string &b);

// Try to find in the Haystack the Needle - ignore case
bool ci_find_string(const std::string &strHaystack, const std::string &strNeedle);

long ci_indexof(const std::string &strHaystack, const std::string &strNeedle);

// trim from start (in place)
void trim_char(std::string &s, const char c);

std::vector<std::string> split(const std::string &s, const char delim);

std::vector<std::string> split2(const std::string &s, const char *delims);

std::vector<std::string> split3(const std::string &s, const std::string &delim);

std::string domain_fix(const std::string &domain);

std::string displayname(const std::string &email);

std::string email_fix(const std::string &txt);

std::string root_domain(const std::string &domain);

/**
 domain1 is domain2's sub-domain or domain2 is domain1's sub-domain
 */
bool is_sub_domain(const std::string &domain1, const std::string &domain2);

std::string imap_string_fix(const std::string &str);

std::string base64_encode(const char *in, int in_len, bool urlsafe = false);

std::string base64_decode(const std::string &in, bool urlsafe);

void base16_encode(const char *in, int len, char *out);

void base16_decode(const char *in, int len, char *out);

//the key length is AES_KEYLEN
std::string AESEncode(const std::string &data, const std::string &key, TransferEncode tcode = base64);

std::string AESDecode(const std::string &input, const std::string &key, TransferEncode tcode = base64);

bool TopCountryDomain(const std::string &seg);

class StringUtils {
public:
    static std::string ReadFile(const std::string &filepath);
};


#endif //A8_STRING_UTILS_HPP
