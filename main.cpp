#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol471;

/*
Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter
than the input string, so we do not encode it.
*/
tuple<string, string>
testFixture1()
{
  return make_tuple("aaa", "aaa");
}

/*
Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
*/
tuple<string, string>
testFixture2()
{
  return make_tuple("aaaaa", "5[a]");
}

/*
Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions,
both of them have the same length = 5, which is the same as "10[a]".
*/
tuple<string, string>
testFixture3()
{
  return make_tuple("aaaaaaaaaa", "10[a]");
}

/*
Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
*/
tuple<string, string>
testFixture4()
{
  return make_tuple("aabcaabcd", "2[aabc]d");
}

/*
Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc"
can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/
tuple<string, string>
testFixture5()
{
  return make_tuple("abbbabbbcabbbabbbc", "2[2[abbb]c]");
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << get<1>(f) << endl;
  auto result = Solution::encode(get<0>(f));
  cout << "result: " << result << endl;
}
void test2()
{
  auto f = testFixture1();
  cout << "Test 2 - exepct to see " << get<1>(f) << endl;
  auto result = Solution::encode(get<0>(f));
  cout << "result: " << result << endl;
}

void test3()
{
  auto f = testFixture3();
  cout << "Test 3 - exepct to see " << get<1>(f) << endl;
  auto result = Solution::encode(get<0>(f));
  cout << "result: " << result << endl;
}
void test4()
{
  auto f = testFixture4();
  cout << "Test 4 - exepct to see " << get<1>(f) << endl;
  auto result = Solution::encode(get<0>(f));
  cout << "result: " << result << endl;
}
void test5()
{
  auto f = testFixture5();
  cout << "Test 5 - exepct to see " << get<1>(f) << endl;
  auto result = Solution::encode(get<0>(f));
  cout << "result: " << result << endl;
}

main()
{
  test1();
  test2();
  test3();
  test4();
  test5();
  return 0;
}