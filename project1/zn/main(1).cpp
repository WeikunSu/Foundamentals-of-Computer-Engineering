#include <algorithm>
#include <iostream>
#include <vector>

template <typename T, typename T2>
auto min_max_grouping(std::vector<T> A, const T2 M, const T2 N) {
  std::vector<std::vector<T>> C(
      N + 1, std::vector<T>(M + 1, std::numeric_limits<T>::max()));
  std::vector<std::vector<T>> S(N + 1, std::vector<T>(N + 1, 0));
  auto B = C;

  for (size_t i = 0; i < N; i++) {
    for (size_t j = i; j < N; j++) {
      S[i][j] = (j <= 0) ? A[j] : S[i][j - 1] + A[j];
    }
  }

  for (size_t j = 1; j <= M; j++) {
    for (size_t i = j; i <= N; i++) {
      T max_num = 0, max_k = j - 1;
      for (size_t k = j - 1; k <= i; k++) {
        auto min_num = std::min(C[k][j - 1], S[k][i - 1]);
        if (min_num > max_num) {
          max_num = min_num;
          max_k = k;
        }
      }
      C[i][j] = max_num;
      B[i][j] = max_k;
    }
  }
  T tot_number = N;
  std::vector<T> G(M + 1, 0);
  for (size_t j = M; j >= 1; --j) {
    G[j] = tot_number - B[tot_number][j];
    tot_number -= G[j];
  }
  return G;
}

int main() {
  std::vector<uint16_t> A{3, 9, 7, 8, 2, 6, 5, 10, 1, 7, 6, 4};
  const int N = 12;
  const int M = 3;

  auto grouping = min_max_grouping(A, M, N);
  for (auto i : grouping) std::cout << i << '\t';

  return 0;
}