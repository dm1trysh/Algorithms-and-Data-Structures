void Zfunction(const std::string& res_string, std::vector<int64_t>& z_func) {
  int64_t length = res_string.length();
  z_func.resize(length, 0);
  for (int64_t i = 1, left = 0, right = 0; i < length; ++i) {
    if (i <= right) {
      z_func[i] = std::min(z_func[i - left], right - i + 1);
    }
    while ((i + z_func[i] < length) &&
      (res_string[i + z_func[i]] == res_string[z_func[i]])) {
      z_func[i]++;
    }
    if (i + z_func[i] - 1 > right) {
      right = i + z_func[i] - 1;
      left = i;
    }
  }
}
