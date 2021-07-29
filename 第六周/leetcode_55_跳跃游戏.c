bool dfs(int* nums, int numsSize, int *dp)
{
    if (dp[numsSize] != -1) {
        return dp[numsSize];
    }
    if (numsSize == 1) {
        dp[numsSize] = 1;
        return true;
    }
    if (numsSize < 1) {
        dp[numsSize] = 0;
        return false;
    }
    int maxStep = nums[0];
    int i = 1;
    for (; i <= maxStep; i++) {
        if (dfs(nums + i, numsSize - i, dp)) {
            dp[numsSize - i] = 1;
            return true;
        }
    }

    dp[numsSize] = 0;
    return false;
}

bool canJump(int* nums, int numsSize)
{
    int *dp = (int *)malloc((numsSize + 1) * sizeof(int));
    int i = 0;
    for (; i <= numsSize; i++) {
        dp[i] = -1;
    }
    bool isCanJump = dfs(nums, numsSize, dp);
    free(dp);
    return isCanJump;
}
