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
int GetleftIndex(Value2Index *sum, int size, int value)
{
    int left = 1;
    int right = size;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (sum[mid].value >= value) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left == size) {
        return -1;
    }

    return (sum[left].value == value) ? left : -1;
}


int subarraySum(int* nums, int numsSize, int k)
{
    int sum[MAX_NUM_COUNT] = {0};
    Value2Index sumSort[MAX_NUM_COUNT] = {0};
    int i = 1;
    int count = 0;

    for (; i <= numsSize; i++) {
        sum[i] = sum[i - 1] + nums[i - 1];
        sumSort[i].value = sum[i];
        sumSort[i].index = i;
    }

    qsort(&sumSort[1], numsSize, sizeof(Value2Index), compare);

    for (i = 1; i <= numsSize; i++) {
        if (sum[i] == k) {
            count++;
        }
        int leftIndex = GetleftIndex(sumSort, numsSize + 1,  sum[i] - k);
        if (leftIndex == -1) {
            continue;
        }
        while (sumSort[leftIndex].value == (sum[i] - k) && (sumSort[leftIndex].index <= (i - 1))) {
            count++;
            leftIndex++;
        }        
    }
    return count;
}
