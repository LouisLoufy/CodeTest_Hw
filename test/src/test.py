import unittest

class Solution(object):
    def merge(self, nums):
        # 为什么一定要这么写才能赋给 nums？
        # nums[:] = [1, 2, 2, 3, 5, 6] 
        nums = [1, 2, 2, 3, 5, 6]
        print(nums)

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_merge(self):
        # Test case 1
        nums = [1, 2, 3, 0, 0, 0]
        expected_result = [1, 2, 2, 3, 5, 6]

        self.solution.merge(nums)
        self.assertEqual(nums, expected_result)

if __name__ == '__main__':
    unittest.main()