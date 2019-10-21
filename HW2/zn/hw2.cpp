#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

inline auto nanoseconds() {
  std::chrono::high_resolution_clock clock;
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             clock.now().time_since_epoch())
      .count();
}

template <class T1, class T2>
auto find_until_first_not(T1 first, T1 last, T2 comparator) {
  while (first != last) {
    if (!comparator(*first)) return first;
    ++first;
  }
  return last;
}

template <class T1, class T2>
constexpr auto randomized_partition_vec(T1 first, T1 last, T1 begin,
                                        T2 comparator) {
  auto range = std::distance(first, last);
  auto i = rand() % (range + 1) + std::distance(begin, first);
  auto dummy_start = first;
  std::advance(dummy_start, i);
  std::iter_swap(dummy_start, last);

  first = find_until_first_not(first, last, comparator);
  if (first == last) return first;

  for (T1 i = std::next(first); i != last; ++i) {
    if (comparator(*i)) {
      std::iter_swap(i, first);
      ++first;
    }
  }
  return first;
}

template <class T>
auto randomized_quick_sort(T first, T last, T begin) {
  auto range_length = std::distance(first, last);
  if (range_length < 2) {
    return;
  }

  auto pivot = *std::next(first, std::distance(first, last) / 2);

  auto middle1 = randomized_partition_vec(
      first, last, begin, [pivot](const auto &elem) { return elem < pivot; });
  auto middle2 = randomized_partition_vec(
      middle1, last, begin,
      [pivot](const auto &elem) { return !(pivot < elem); });
  randomized_quick_sort(first, middle1, begin);
  randomized_quick_sort(middle2, last, begin);
}

template <class T>
auto randomized_quick_sort(std::vector<T> &vec) {
  randomized_quick_sort(vec.begin(), vec.end(), vec.begin());
}

template <typename T, typename C>
auto insertion_sort(T first, T last, C compare) -> void {
  for (auto cur = std::next(first); cur != last; ++cur) {
    auto sift = cur;
    auto sift_1 = std::prev(cur);
    if (compare(*sift, *sift_1)) {
      auto tmp = std::move(*sift);
      do {
        *sift = std::move(*sift_1);
      } while (--sift != first && compare(tmp, *--sift_1));
      *sift = std::move(tmp);
    }
  }
}

template <typename T, typename S, typename C>
auto sift(T first, S size, C compare) -> void {
  if (size < 2) return;

  auto root = first + (size - 1);
  auto child_root1 = root - 1;
  auto child_root2 = first + (size / 2 - 1);

  while (true) {
    auto max_root = root;
    if (compare(*max_root, *child_root1)) {
      max_root = child_root1;
    }
    if (compare(*max_root, *child_root2)) {
      max_root = child_root2;
    }
    if (max_root == root) return;

    using std::swap;
    swap(*root, *max_root);

    size /= 2;
    if (size < 2) return;

    root = max_root;
    child_root1 = root - 1;
    child_root2 = max_root - (size - size / 2);
  }
}

template <typename T, typename C = std::less<>>
auto heapify(T first, T last, C compare = {}) -> void {
  auto size = std::distance(first, last);
  if (size < 2) return;

  // A sorted collection is a valid heap heap; whenever the heap
  // is small, using insertion sort should be faster
  constexpr auto small_heap_size = 10;
  if (size <= small_heap_size) {
    insertion_sort(std::move(first), std::move(last), std::move(compare));
    return;
  }

  // Determines the "level" of the subtree seen so far; the log2 of this
  // variable will be used to make the binary carry sequence
  auto heap_level = 1;

  auto it = first;
  auto next = std::next(it, small_heap_size);
  while (true) {
    // Make a 15 element heap
    insertion_sort(it, next, compare);

    auto heap_size = small_heap_size;
    // Bit trick iterate without actually having to compute log2(heap_level)
    for (auto i = (heap_level & -heap_level) >> 1; i != 0; i >>= 1) {
      it -= heap_size;
      heap_size = 2 * heap_size + 1;
      sift(it, heap_size, compare);
      ++next;
    }

    if (std::distance(next, last) <= small_heap_size) {
      insertion_sort(std::move(next), std::move(last), std::move(compare));
      return;
    }

    it = next;
    std::advance(next, small_heap_size);
    ++heap_level;
  }
}

// Returns 2^floor(log2(n)), assumes n > 0
template <typename T>
inline constexpr auto hyperfloor(T n) -> T {
  constexpr auto bound = std::numeric_limits<T>::digits / 2;
  for (std::size_t i = 1; i <= bound; i <<= 1) {
    n |= (n >> i);
  }
  return n & ~(n >> 1);
}

template <typename T, typename S, typename C>
auto pop_heap_with_size(T first, T last, S size, C compare) -> void {
  auto heap_size = hyperfloor(size + 1u) - 1u;
  auto last_root = std::prev(last);
  auto bigger = last_root;
  auto bigger_size = heap_size;

  // Look for the bigger heap root
  auto it = first;
  while (true) {
    auto root = std::next(it, heap_size - 1);
    if (root == last_root) break;
    if (compare(*bigger, *root)) {
      bigger = root;
      bigger_size = heap_size;
    }
    it = std::next(root);

    size -= heap_size;
    heap_size = hyperfloor(size + 1u) - 1u;
  }

  // If a heap root was bigger than the last one, exchange
  // them and sift
  if (bigger != last_root) {
    std::iter_swap(bigger, last_root);
    sift(bigger - (bigger_size - 1), bigger_size, std::move(compare));
  }
}

template <typename T, typename C = std::less<>>
auto heap_sort(T first, T last, C compare = {}) -> void {
  auto size = std::distance(first, last);
  if (size < 2) return;

  do {
    pop_heap_with_size(first, last, size, compare);
    --last;
    --size;
  } while (size > 1);
}

template <typename T>
auto count_sort(std::vector<T> vec) -> std::vector<T> {
  auto k = *std::max_element(vec.begin(), vec.end()) + 1;
  std::vector<T> C(k, 0);
  std::vector<T> B(vec.size(), 0);
  for (auto i = 0; i < vec.size(); ++i) C[vec[i]]++;
  for (auto i = 1; i < k; ++i) C[i] += C[i - 1];
  for (auto i = k - 1; i >= 0; --i) B[C[vec[i]]-- - 1] = vec[i];
  return B;
}

template <typename T>
auto sort_digit(std::vector<T> vec, int exp) {
  std::vector<T> B(vec.size(), 0);
  std::vector<T> C(10, 0);
  for (int i = 0; i < vec.size(); i++) C[(vec[i] / exp) % 10]++;
  for (int i = 1; i < 10; i++) C[i] += C[i - 1];
  for (int i = vec.size() - 1; i >= 0; --i)
    B[C[(vec[i] / exp) % 10]-- - 1] = vec[i];
  return B;
}

template <typename T>
auto radix_sort(std::vector<T> vec) {
  int m = *std::max_element(vec.begin(), vec.end());
  for (int exp = 1; m / exp > 0; exp *= 10) vec = sort_digit(vec, exp);
  return vec;
}

int main() {
  auto n_repeat = 1e7;
  auto size = 100;
  std::vector<int> vec(size);
  std::generate(vec.begin(), vec.end(), [n = 1]() mutable { return n++; });
  // std::for_each(vec.begin(), vec.end(), [](const auto i){std::cout << i <<
  // "\n";});

  std::cout << size << ',';

  // Randomized quick sort
  auto dummy_vec = vec;
  auto start_time = nanoseconds();
  for (auto iter = 0; iter < n_repeat; ++iter) {
    randomized_quick_sort(dummy_vec);
  }
  auto end_time = nanoseconds();
  std::cout << (end_time - start_time) * 1.0 / n_repeat << ',';

  // heap sort
  auto dummy_vec2 = vec;
  auto rng = std::default_random_engine{};
  std::shuffle(dummy_vec2.begin(), dummy_vec2.end(), rng);
  std::for_each(dummy_vec2.begin(), dummy_vec2.end(), [](const auto i){std::cout << i <<
  "\t";});
  std::cout << std::endl;
  start_time = nanoseconds();
  for (auto iter = 0; iter < n_repeat; ++iter) {
    heapify(dummy_vec2.begin(), dummy_vec2.end());
    sort_heap(dummy_vec2.begin(), dummy_vec2.end());
  }
  end_time = nanoseconds();
  std::cout << (end_time - start_time) * 1.0 / n_repeat;

  // count sort
  std::vector<int> dummy_vec3{20, 18, 5, 7, 16, 10, 9, 3, 12, 14, 0};
  auto dummy_vec4 = count_sort(dummy_vec3);
  std::cout << std::endl;
  std::for_each(dummy_vec4.begin(), dummy_vec4.end(),
                [](const auto i) { std::cout << i << "\t"; });

  // radix sort
  std::vector<int> dummy_vec5{329, 457, 657, 839, 436, 720, 353};
  auto dummy_vec6 = radix_sort(dummy_vec5);
  std::cout << std::endl;
  std::for_each(dummy_vec6.begin(), dummy_vec6.end(),
                [](const auto i) { std::cout << i << "\t"; });

  return 0;
}