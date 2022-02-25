#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <regex>

using namespace sol471;
using namespace std;

/*takeaways
  - use "abbbabbbcabbbabbbc" as an example

  - break it down to two parts in all possible combinations
    if the parts are made of patterns:
    - "abbbabbbcabbbabbbc" -> "abbbabbb" & "cabbbabbbc"

  - we can now encode the "abbbabbb" part to "2[abbb]" using
    the pattern "abbb"

  - now we are dealing with "2[abbb]cabbbabbbc"
    - focus on "cabbbabbbc"
    - try all combinations recursively
      "cabbbabbbc" -> "c" & "abbbabbbc" -> "c" & ("abbbabbb" & "c")
    - find pattern "abbb" and encode the string
      "c2[abbb]c"
    - so the string now become "2[abbb]c2[abbb]c"
    - find the pattern "2[abbb]c", encode the string:
      "2[2[abbb]c}"

*/

string Solution::encode(string &input)
{
  const auto n = (int)input.size();

  /* record the shortest encoded string for
     the substr from i to j in input*/
  auto dp = vector<vector<string>>(n, vector<string>(n, ""));

  function<string(string &, int, int)> _encode =
      [&](string &s, int i, int j)
  {
    if (!dp[i][j].empty())
      return dp[i][j];
    const auto &cur = s.substr(i, j - i + 1);
    dp[i][j] = cur;
    /* not worth it to encode the string */
    if (dp[i][j].length() < 5)
      return dp[i][j];

    /*
      - break a string into two parts in
        all possible combinations
      - pick the combinations that will have
        the shortest length after being encoded
        - we pick the very last one among those
          who have the shortest length
    */
    for (auto k = i; k < j; k++)
    {
      const auto &e1 = _encode(s, i, k);
      const auto &e2 = _encode(s, k + 1, j);
      if (e1.length() + e2.length() < dp[i][j].length())
        dp[i][j] = e1 + e2;
    }

    /* perfect match
       - you still need the above code to try all combinations
         as the following logic works only if s is made of
         just the patterns you are looking for
       - let say if s ="abcabcd" the code will do nothing
         unless it has been broken down two parts
         "abcabc" and "d" 
    */

    /* encode the string
       - scan through all the possible patterns
         on cur
       - check if cur is made of a given pattern
         if cur is abcabc we can compress it
         to 2[abc] but not really worth it
         as the size is still 6
    */
    for (auto k = i; k <= j; k++)
    {
      const auto &pattern = s.substr(i, k - i + 1);
      /*pattern found
        - the length of s should be a multiple of
          the pattern
        - and replace the pattern with an empty string
          in s should result in an empty string
          s: aacaac -> s: "" if the pattern is aac
      */
      if (cur.length() % pattern.length() == 0 &&
          regex_replace(cur, regex(pattern), "").empty())
      {
        /* you also need to check if the pattern itself can
           be encoded to further reduce the length
        */
        const auto &test = to_string(cur.length() / pattern.length()) +
                           "[" + _encode(s, i, k) + "]";
        if (test.length() < dp[i][j].length())
          dp[i][j] = test;
      }
    }

    return dp[i][j];
  };

  return _encode(input, 0, n - 1);
}