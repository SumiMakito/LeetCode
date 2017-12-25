import sys

class Solution(object):
    def minSubArrayLen(self, s, nums):
        """
        :type s: int
        :type nums: List[int]
        :rtype: int
        """
        min_len_ = sys.maxsize
        sum_ = 0
        m = n = 0  # left & right boundaries
        for i in nums:
            sum_ += i
            if sum_ >= s and min_len_ > n - m + 1:
                min_len_ = n - m + 1
            while 0 < min_len_ <= n - m + 1:
                sum_ -= nums[m]  # remove the head from the segment
                m += 1  # left boundary moves right
                if sum_ >= s and min_len_ > n - m + 1:
                    min_len_ = n - m + 1
            n += 1
        return min_len_ if min_len_ != sys.maxsize else 0
