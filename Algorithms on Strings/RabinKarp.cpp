#Rabin-Karp wihout checking collisions

const int64_t prime = 37;
const int64_t mod = 1ll << 31 - 1;

template <typename S>
void BuildHash(std::vector<int64_t>& hash, const S& str,
               const std::vector<int64_t>& pows) {
  size_t str_sz = str.size();
  for (size_t i = 0; i < str_sz; ++i) {
    hash[i] = (str[i] - 'a' + 1) % mod;
    if (i > 0) {
      hash[i] = (hash[i] + (hash[i - 1] * prime) % mod) % mod;
    }
  }
}

int64_t CountEqual(size_t pattern_sz, size_t text_sz,
                   std::vector<int64_t>& text_hashes, int64_t pattern_hash,
                   std::vector<int64_t>& pows) {
  int64_t cnt = 0;
  for (size_t i = 0; i + pattern_sz - 1 < text_sz; ++i) {
    int64_t cur_hash = text_hashes[i + pattern_sz - 1];
    if (i > 0) {
      cur_hash =
          (cur_hash - (pows[pattern_sz] * text_hashes[i - 1]) % mod) % mod;
    }
    if (cur_hash == pattern_hash) {
      std::cout << i << " ";
      cnt++;
    }
  }
  return cnt;
}

template <typename S>
void RabinKarp(const S& pattern, const S& text) {
  std::vector<int64_t> pows(text.size(), 1);
  for (size_t i = 1; i < pows.size(); ++i) {
    pows[i] = (pows[i - 1] * prime) % mod;
  }
  std::vector<int64_t> pattern_hashes(pattern.size());
  BuildHash<std::string>(pattern_hashes, pattern, pows);
  std::vector<int64_t> text_hashes(text.size());
  BuildHash<std::string>(text_hashes, text, pows);
  int64_t cnt = CountEqual(pattern.size(), text.size(), text_hashes,
                           pattern_hashes[pattern.size() - 1], pows);
  std::cout << "\n" << cnt;
}
