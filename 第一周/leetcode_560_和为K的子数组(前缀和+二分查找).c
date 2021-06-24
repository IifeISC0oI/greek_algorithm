#define MAX_NUM_COUNT 20001
typedef struct {
    int value;
    int index;
} Value2Index;
int compare(const void *a, const void *b)
{
    Value2Index *sum1 = (Value2Index *)a;
    Value2Index *sum2 = (Value2Index *)b;
    return sum1->value - sum2->value;
}
int GetleftIndex(Value2Index *sortPrefixSum, int size, int value)
{
    int left = 1;
    int right = size;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (sortPrefixSum[mid].value >= value) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left == size) {
        return -1;
    }

    return (sortPrefixSum[left].value == value) ? left : -1;
}


int subarraySum(int* nums, int numsSize, int k)
{
    int prefixSum[MAX_NUM_COUNT] = {0};
    Value2Index sortPrefixSum[MAX_NUM_COUNT] = {0};
    int i = 1;
    int count = 0;

    for (; i <= numsSize; i++) {
        prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        sortPrefixSum[i].value = prefixSum[i];
        sortPrefixSum[i].index = i;
    }

    qsort(&sortPrefixSum[1], numsSize, sizeof(Value2Index), compare);

    for (i = 1; i <= numsSize; i++) {
        if (prefixSum[i] == k) {
            count++;
        }
        int leftIndex = GetleftIndex(sortPrefixSum, numsSize + 1,  prefixSum[i] - k);
        if (leftIndex == -1) {
            continue;
        }
        while (sortPrefixSum[leftIndex].value == (prefixSum[i] - k) && (sortPrefixSum[leftIndex].index <= (i - 1))) {
            count++;
            leftIndex++;
        }        
    }
    return count;
}
