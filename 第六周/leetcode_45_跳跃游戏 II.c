int jump(int* nums, int numsSize)
{
    int i = 0;
    int hopLen = 0;
    while (i < numsSize - 1) {
        if  (nums[i] >= numsSize - 1 - i) {
            hopLen++;
            break;
        }
        int j = 1;
        int maxPos = i + nums[i];
        int jumpMaxStep = nums[i];
        for (; j <= nums[i] && (i + j) < numsSize; j++) {
            if (i + j + nums[i + j] > maxPos) {
                maxPos = i + j + nums[i + j];
                jumpMaxStep = j;
            }
        }
        hopLen++;
        i += jumpMaxStep;        
    }

    return hopLen;    
}
