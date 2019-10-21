#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <class Iterator, class T>
inline auto populate_numbers(Iterator first, Iterator last, T value,
                             bool ascending = false) {
  while (first != last) {
    *first++ = value;
    ascending ? value++ : --value;
  }
}

template <typename T>
auto insertion_sort(std::vector<T> &vec) {
  for (auto j = vec.begin() + 1; j != vec.end(); j++) {
    auto key = *j;
    auto i = j - 1;
    while (i >= vec.begin() && *i > key) {
      *(i + 1) = *i;
      i--;
    }
    *(i + 1) = key;
    // std::cout << std::distance(vec.begin(), j) << ' ';
    // for (auto it : vec) std::cout << it << '\t';
    // std::cout << std::endl;
  }
}

template <class T1, class T2, class T3>
auto merge_vec(T1 first1, T1 last1, T2 first2, T2 last2, T3 d_first) {
  for (; first1 != last1; ++d_first) {
    if (first2 == last2) {
      return std::copy(first1, last1, d_first);
    }
    if (*first2 < *first1) {
      *d_first = *(first2++);
    } else {
      *d_first = *(first1++);
    }
  }
  return std::copy(first2, last2, d_first);
}

template <typename T1, typename T2>
auto merge_sort(T1 source_begin, T1 source_end, T2 target_begin,
                T2 target_end) {
  auto range_length = std::distance(source_begin, source_end);
  if (range_length < 2) {
    return;
  }

  auto left_chunk_length = range_length >> 1;
  auto source_left_chunk_end = source_begin;
  auto target_left_chunk_end = target_begin;

  std::advance(source_left_chunk_end, left_chunk_length);
  std::advance(target_left_chunk_end, left_chunk_length);

  // for (auto dummy_begin = target_begin; dummy_begin != target_end;
  // ++dummy_begin) std::cout << *dummy_begin << '\t';
  // std::cout << std::endl;

  merge_sort(target_begin, target_left_chunk_end, source_begin,
             source_left_chunk_end);

  merge_sort(target_left_chunk_end, target_end, source_left_chunk_end,
             source_end);

  merge_vec(source_begin, source_left_chunk_end, source_left_chunk_end,
            source_end, target_begin);
}

template <typename T>
auto merge_sort(std::vector<T> &vec) {
  auto aux = vec;
  merge_sort(aux.begin(), aux.end(), vec.begin(), vec.end());
}

inline auto nanoseconds() {
  std::chrono::high_resolution_clock clock;
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             clock.now().time_since_epoch())
      .count();
}

int main() {
  auto n_repeat = 100;
  auto stepin = 2;
  for (auto size = stepin; size < 20000; size *= stepin) {
    std::vector<uint64_t> insertion_sort_runtimes(n_repeat);
    std::vector<uint64_t> merge_sort_runtimes(n_repeat);
    std::vector<int> vec(size);

    populate_numbers(vec.begin(), vec.end(), vec.size(), false);

    for (auto repeat = 0; repeat < n_repeat; repeat++) {
      auto vec_for_insertion_sort = vec;
      auto vec_for_merge_sort = vec;

      // insertion sort
      auto start_time = nanoseconds();
      insertion_sort(vec_for_insertion_sort);
      auto end_time = nanoseconds();
      insertion_sort_runtimes.push_back(end_time - start_time);

      // merge sort
      start_time = nanoseconds();
      auto aux = vec_for_merge_sort;
      merge_sort(aux.begin(), aux.end(), vec.begin(), vec.end());
      end_time = nanoseconds();
      merge_sort_runtimes.push_back(end_time - start_time);
    }

    std::cout << size << ','
              << std::accumulate(insertion_sort_runtimes.begin(),
                                 insertion_sort_runtimes.end(), 0.0) /
                     n_repeat
              << ','
              << std::accumulate(merge_sort_runtimes.begin(),
                                 merge_sort_runtimes.end(), 0.0) /
                     n_repeat
              << std::endl;
  }

  // std::vector<int> vec{10, 5, 7, 9, 8, 3};
  // auto vec1 = vec;
  // auto vec2 = vec;
  // insertion_sort(vec1);
  // std::cout << std::endl;
  // merge_sort(vec2);

  return 0;
}