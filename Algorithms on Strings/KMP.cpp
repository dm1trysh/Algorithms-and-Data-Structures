void PrefixFunction(const std::string& res_str, std::vector<size_t>& pi_func) {
  size_t res_size = res_str.size();
  pi_func.resize(res_size, 0);
  for (size_t i = 1; i < res_size; ++i) {
    size_t tmp = pi_func[i - 1];
    while (tmp > 0 && res_str[i] != res_str[tmp]) {
      tmp = pi_func[tmp - 1];
    }
    if (res_str[i] == res_str[tmp]) {
      ++tmp;
    }
    pi_func[i] = tmp;
  }
}

void KMP(std::vector<size_t>& ans, const std::string& pattern, const std::string& text) {
  std::vector<size_t> pi_func;
  PrefixFunction(pattern + "#" + text, pi_func);
  for (size_t i = pattern.size() + 1; i < pi_func.size(); ++i) {
    if (pi_func[i] == pattern.size()) {
      if (ans.size() + 1 > ans.capacity()) {
        ans.reserve(ans.capacity() * 2);
      }
      ans.push_back(i - pattern.size() * 2);
    }
  }
  ans.shrink_to_fit();
}
