//
// Created by jun on 5/25/17.
// Implementations of counting inversions in a 1D array.
//

#ifndef INVERSION_COUNT_INVERSION_COUNT_H
#define INVERSION_COUNT_INVERSION_COUNT_H

#include <iostream>
#include <algorithm>


//
// count the number of inversions using brute force (double for-loops)
//
// @param a: input 1D array
//
template<typename T>
inline long inversionCountBruteForce(const T& a)
{
  long count = 0;

  for (int i=0; i<a.size()-1; ++i)
  {
    for (int j=i+1; j<a.size(); ++j)
    {
      if (a[i] > a[j]) { ++count; }
    }
  }

  return count;
}

//
// computer the No. of splitting inversions in two arrays
//
// @param b: left 1D array
// @param c: right 1D array
//
template <typename T>
inline long splitInversion(const T& b, const T& c)
{
  long count = 0;

  int l_b = b.size();
  int l_c = c.size();

  if ( l_b < 1 || l_c < 1 ) { return 0; }

  int j = 0;
  int k = 0;
  for (int i=0; i<l_b+l_c; ++i)
  {
    if (b[j] > c[k])
    {
      ++k;
      // If an element j in the left array is bigger than the element k
      // in the right array, it means that the element j and the rest
      // elements after it in the left array are all inversions to the
      // element k in the right array.
      count += l_b - j;
      if (k == l_c) { break; }
    }
    else if (b[j] < c[k])
    {
      ++j;
      if (j == l_b) { break; }
    }

  }

  return count;
}

//
// compute the number of inversions by splitting algorithm
//
// @param a: input 1D array
//
template <typename T>
inline long quickInversion(const T& a)
{
  long count = 0;

  if (a.size() < 2) { return 0; }

  int split = a.size()/2;

  // divide the original vector by left vector and right vector
  T b (a.begin(), a.begin() + split);
  T c (a.begin() + split, a.end());

  // recursively calculate the number of inversions in the left and right vectors
  count += quickInversion(b);
  count += quickInversion(c);

  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());
  count += splitInversion(b, c);

  return count;
}

#endif //INVERSION_COUNT_INVERSION_COUNT_H
