#define MAX_NUM_COUNT 20001
typedef struct hashNode {
    int key;
    int value;
    struct hashNode *next;
};

void PutOneNode2Hash(struct hashNode **hashTable,  int hashSize, int prefixSum)
{
    int hashIndex = abs(prefixSum) % hashSize;
    struct hashNode *node = hashTable[hashIndex];
    struct hashNode *pre = NULL;
    while (node != NULL) {
        if (node->key == prefixSum) {
            node->value++;
            return;
        }
        pre = node;
        node = node->next;
    }

    node = (struct hashNode *)malloc(sizeof(struct hashNode));
    node->key = prefixSum;
    node->value = 1;
    if (pre == NULL) {
        hashTable[hashIndex] = node;
        node->next = NULL;       
    } else {
        pre->next = node;
        node->next = NULL;
    }
}

int GetHashValue(struct hashNode **hashTable, int hashSize, int prefixSum)
{
    int hashIndex = abs(prefixSum) % hashSize;
    struct hashNode *node = hashTable[hashIndex];
    while (node != NULL) {
        if (node->key == prefixSum) {
            return node->value;
        }
        node = node->next;
    }

    return -1;
}

void FreeHashTable(struct hashNode **hashTable)
{
    int i = 0;
    for (; i < MAX_NUM_COUNT; i++) {
        struct hashNode *node = hashTable[i];
        struct hashNode *next = NULL;
        while (node != NULL) {
            next = node->next;
            free(node);
            node = next;
        }
    }
}

int subarraySum(int* nums, int numsSize, int k)
{
    int prefixSum = 0;
    int i = 1;
    int count = 0;
    struct hashNode *hashTable[MAX_NUM_COUNT] = {0};

    PutOneNode2Hash(hashTable, numsSize, 0); //处理第一次prefixSum刚好等于K的场景
    for (; i <= numsSize; i++) {
        prefixSum += nums[i - 1];
        int curCount = GetHashValue(hashTable, numsSize, prefixSum - k);
        if (curCount != -1) {
            count += curCount;
        }
        PutOneNode2Hash(hashTable, numsSize, prefixSum);
    }
    FreeHashTable(hashTable);
    return count;
}