#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

#define DEBUG 1

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

using namespace std;

bool regex_match(string pattern, string test) {
    if (pattern.empty() && test.empty())
        return true;
    else if (pattern.empty())
        return false;

    unsigned long p_idx;
    unsigned long t_idx;
    unsigned long p = pattern.length();
    unsigned long t = test.length();

    vector<vector<int>> cached_bt(t + 1, vector<int>(p + 1, 0));

    cached_bt[0][0] = 1;
    for (t_idx = 0; t_idx <= t; t_idx++) {
        for (p_idx = 1; p_idx <= p; p_idx++) {
            if (pattern[p_idx - 1] != '*') {
                if (t_idx > 0) {
                    if (cached_bt[t_idx - 1][p_idx - 1]) {
                        if (pattern[p_idx - 1] == test[t_idx - 1] || pattern[p_idx - 1] == '.') {
                            cached_bt[t_idx][p_idx] = 1;
                        } else {
                            cached_bt[t_idx][p_idx] = 0;
                        }
                    } else {
                        cached_bt[t_idx][p_idx] = 0;
                    }
                } else {
                    cached_bt[t_idx][p_idx] = 0;
                }
            } else {
                if (cached_bt[t_idx][p_idx - 2]) {
                    cached_bt[t_idx][p_idx] = 1;
                } else {
                    if (t_idx > 0 && (pattern[p_idx - 2] == test[t_idx - 1] || pattern[p_idx - 2] == '.') &&
                        cached_bt[t_idx - 1][p_idx]) {
                        cached_bt[t_idx][p_idx] = 1;
                    } else {
                        cached_bt[t_idx][p_idx] = 0;
                    }
                }
            }

            for (auto &rs:cached_bt) {
                printf("\n");
                for (auto &cs:rs) {
                    printf("%d ", cs);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    return cached_bt[t][p] == 1;
}

#if DEBUG == 1

int main() {
    assert(!regex_match("ab+c", "abc"));
    assert(!regex_match("a.+c", "abc"));
    assert(!regex_match("a.+c", "ac"));

    assert(regex_match("abc", "abc"));

    assert(!regex_match("abc", "abcd"));
    assert(!regex_match("abcd", "abc"));

    assert(!regex_match("a.cd", "abc"));
    assert(regex_match("a.cd", "abcd"));
    assert(!regex_match("a.cd", "abcde"));
    assert(regex_match("a.cd", "accd"));

    assert(regex_match("a.*bc", "abc"));
    assert(regex_match("a.*bc", "abbc"));
    assert(regex_match("a*bc", "aaaabc"));
    assert(!regex_match("a*bc", "aaaabbbc"));

    assert(!regex_match("a.*.bc", "abc"));
    assert(regex_match("a.*.bc", "abbbbc"));
    assert(regex_match("a.*.bc", "abbcdbc"));
    assert(!regex_match("a.*.bc", "abbcdbcd"));

    assert(!regex_match("a", "aa"));
    assert(regex_match("aa", "aa"));
    assert(!regex_match("aa", "aaa"));

    assert(regex_match(".*a", "a"));

    assert(regex_match("c*a*b", "aab"));
    assert(!regex_match(".", "aa"));
    assert(regex_match("..", "aa"));
    assert(regex_match("c*a*b", "aab"));
    assert(regex_match("c*c*c*c*a*b", "aab"));

    assert(regex_match("cb*", "cbbb"));
    assert(regex_match("a*", "aa"));
    assert(regex_match(".*", "ab"));
    assert(regex_match(".*", "aa"));
    assert(regex_match(".", "a"));
    assert(regex_match("c.c", "cac"));
    assert(!regex_match("c.c", "cacc"));

    assert(!regex_match(".*c", "ab"));

    assert(regex_match("c*b*b*.*ac*.*bc*a*", "abcab"));
    assert(regex_match("c*b*b*.*ac*.*bc*a*", "cbaacacaaccbaabcb"));
    assert(regex_match(".*a*aa*.*", "aabcbc"));
    assert(regex_match(".*a*aa*.*b*.c*.*a*", "aabcbcbcaccbcaabc"));
    assert(!regex_match("b*c", "a"));
    assert(regex_match(".*", ""));
    assert(!regex_match("b", "a"));

    printf(KGRN "All passed" KNRM);

    return 0;
}

#endif

class Solution {
public:
    bool isMatch(string s, string p) {
        return regex_match(std::move(p), std::move(s));
    }
};
