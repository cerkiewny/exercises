#include <assert.h>
#include <map>
#include <limits>
#ifdef TESTING
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#endif

#ifdef TESTING
using std::vector;
#define TESTVALUERANGE 50000
#define MAXTESTVALUE 30000
#define TESTREPS 30000
#endif
/**

interval_map<K, V> is a data stnucture that efficiently associates intervals
of keys of type K with values of type V. Your task is to implement the
assign member function of this data structure, which is outlined below.
interval_map<K, V> is implemented on top of std::map. In case you are
not entirely sure which functions std::map provides, what they do and which
guarantees they provide, we have attached an excerpt of the C++1x draft
standard at the end of this file for your convenience.

Each key-value-pair (k, v) in the m_map member means that the value v is
associated to the interval from k (including) to the next key (excluding)
in m_map. Example: the std::map (0, 'A'), (3, 'B'), (5, 'A') represents the
mapping

0 -> 'A'
1 -> 'A'
2 -> 'A'
3 -> 'B'
4 -> 'B'
5 -> 'A'
6 -> 'A'
7 -> 'A'
... all the way to numeric_limits<key>::max()

The representation in m_map must be canonical, that is,
 consecutive map entries must not have the same value:
..., (0, 'A'), (3, 'A'), ... is not allowed.
Initially, the whole range of K is associated with a given initial value,
passed to the constructor.

**/

template < class K, class V >
class interval_map {
  friend void IntervalMapTest();

  private:
  std::map < K, V > m_map;

  public:
  // constructor associates whole range of K with val by inserting
  // (K_min, val) into the map
  explicit interval_map(V const& val) {
    m_map.insert(m_map.begin(),
            std::make_pair(std::numeric_limits < K >::min(), val));
  };

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Do not change values outside this interval.
  // Conforming to the C++ Standard Library conventions,
  // the interval includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  void assign(K const& keyBegin, K const& keyEnd, const V& val) {
    // Fail silently if keyBegin is not < than key End
    // const time compare
    if (!(keyBegin < keyEnd)) {
      return;
    }
    // for red black tree of map this operation is O(logN)
    V tmpVal = (--m_map.upper_bound(keyEnd))->second;

    // values inside the keyBegin keyEnd need to be deleted

    // this operationr is O(K) - amortised where K is
    // the distance however if the granulity of the intervals
    // is good (big intervals) the K will be small
    m_map.erase(m_map.upper_bound(keyBegin)
          , m_map.lower_bound(keyEnd));
    /**
       we have now deleted all the elements inside
       the added interval now we need to make sure
       we will not add the interval which has value
       the same as the begeninng and the end example:
        01234
       |33133|

       assign(1, 3, 3)
        0 12 34
       |3|33|33|
       the | marks interval stop/start

       should be:
        01234
       |33333|
       this asspect is not influancing the bound of
       running speed of the algorithm however it will help
       with the granulity of the stored intervals as well as store
       some space.
       **/
    if ((--m_map.upper_bound(keyBegin))->second == val && tmpVal == val)
       return;
    m_map[keyEnd] = tmpVal;
    m_map[keyBegin] = val;
  }

  // look-up of the value associated with key
  V const& operator[](K const& key) const {
    return (--m_map.upper_bound(key))->second;
  }
};


#ifdef TESTING
class testIntervalMapImpl {
  private:
    vector < int > testV;
  public:
    explicit testIntervalMapImpl(int in) : testV(TESTVALUERANGE) {
      for (int j = 0; j < TESTVALUERANGE; j++) {
        testV[j] = in;
      }
    }
    void assign(int start, int end, int val) {
      if (end <= start)
        return;
      for (int i = start; i < end; i++) {
        testV[i] = val;
      }
    }

  int const& operator[](int const& key) const {
    return testV[key];
  }
};

/**
  perform some random tests
  over the implementation
  as the reference use the trivial
  implementation using the vector
**/
void random_tests() {
  srand(time(NULL));
  testIntervalMapImpl testMap(13);
  interval_map< int, int > map(13);
  for (int i = 0; i < TESTREPS; i++) {
    int val = rand() % MAXTESTVALUE;
    int begin = rand() % TESTVALUERANGE;
    int end = rand() % TESTVALUERANGE;
    map.assign(begin, end, val);
#ifndef PERFORMANCETEST
    testMap.assign(begin, end, val);
    for (int j = 0; j< TESTVALUERANGE; j++) {
      assert(testMap[j] == map[j]);
    }
#endif
  }
}

// first the testing usecases created by developer

void IntervalMapTest() {
  // trivial case test with trivial classes
  interval_map< int, int > test1(3);
  test1.assign(3, 2, 2);
  assert(test1[3] == 3);
  assert(test1[0] == 3);
  assert(test1[11] == 3);
  assert(test1[std::numeric_limits< int >::max()] == 3);

  // first "real" test case override all values but the biggest one
  test1.assign(std::numeric_limits< int >::min(),
         std::numeric_limits< int >::max(), 2);
  assert(test1[std::numeric_limits< int >::min()] == 2);
  assert(test1[11] == 2);
  assert(test1[std::numeric_limits< int >::max() - 1] == 2);
  assert(test1[std::numeric_limits< int >::max()] == 3);

  // now the test case of single range change without intersections
  test1.assign(1, 5, 4);
  assert(test1[1] == 4);
  assert(test1[2] == 4);
  assert(test1[5] == 2);

  assert(test1[12] == 2);
  assert(test1[1] == 4);

  // another test case starting with the empty map for clarity
  interval_map< int, int > test2(100);
  // adding two intervals with the intersection
  test2.assign(15, 50, 20);
  assert(test2[50] == 100);
  test2.assign(25, 100, 30);
  // test if we havent lost first value at the end
  assert(test2[100] == 100);
  // check intersections
  assert(test2[15] == 20);
  assert(test2[24] == 20);
  assert(test2[40] == 30);
  assert(test2[49] == 30);
  assert(test2[101] == 100);

  // now add the interval covering previous intervals

  test2.assign(14, 101, 7);
  for (int i = 0; i < 500; i++) {
    if (i >= 14 && i < 101) {
      assert(test2[i] == 7);
    } else {
      assert(test2[i] == 100);
    }
  }

  interval_map< int, int > test3(100);
  test3.assign(1, 2, 3);
  assert(test3[1] == 3);
  // first sanity tests passed lets now do the random tests
  random_tests();
}
#endif

int main(int argc, char* argv[]) {
#ifdef TESTING
  IntervalMapTest();
#endif
  return 0;
}

