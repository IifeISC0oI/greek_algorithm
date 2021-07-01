#define MAX_KEY_VALUE 9000
typedef struct keyPair{
    int key;
    int value;
    struct keyPair *pre;
    struct keyPair *next;
};

typedef struct {
    int capacity;
    int cacheNum;
    struct keyPair cacheList;
    struct keyPair *hashMap[MAX_KEY_VALUE];
} LRUCache;

#define INIT_CACHE_LIST(listHead) \
do { \
    (listHead)->pre = (listHead); \
    (listHead)->next = (listHead); \
} while (0)

#define DELETE_NODE_FROM_LIST(node) \
do { \
    (node)->pre->next = (node)->next; \
    (node)->next->pre = (node)->pre; \
} while (0)

//设置cache时如果添加到链表头部，则cache容量超限时链表尾部节点则是最近未使用节点
#define ADD_NODE_TO_LIST_HEAD(listHead, node) \
do { \
    (listHead)->next->pre = (node); \
    (node)->next = (listHead)->next; \
    (listHead)->next = (node); \
    (node)->pre = (listHead); \
} while (0)

//设置cache时如果添加到链表尾，则cache容量超限时链表头部节点则是最近未使用节点
#define ADD_NODE_TO_LIST_TAIL(listHead, node) \
do { \
    (listHead)->pre->next = (node); \
    (node)->pre = (listHead)->pre; \
    (listHead)->pre = (node); \
    (node)->next = (listHead); \
} while (0)

LRUCache* lRUCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    if (cache == NULL) {
        return NULL;
    }
    cache->capacity = capacity;
    cache->cacheNum = 0;

    INIT_CACHE_LIST(&cache->cacheList);
    
    memset(cache->hashMap, 0, MAX_KEY_VALUE * sizeof(struct keyPair *));
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key)
{
    if (obj->hashMap[key] == NULL) {
        return -1;
    }

    struct keyPair *node = obj->hashMap[key];
    DELETE_NODE_FROM_LIST(node);
    ADD_NODE_TO_LIST_HEAD(&obj->cacheList, node);

    return node->value;
}

void updateCacheValue(LRUCache* obj, int key, int value)
{
    struct keyPair *node = obj->hashMap[key];
    DELETE_NODE_FROM_LIST(node);
    ADD_NODE_TO_LIST_HEAD(&obj->cacheList, node);
    node->value = value;
}

void delLeastRecentlyUsedCache(LRUCache* obj, int key, int value)
{
    struct keyPair *leastRecentlyUsedNode = obj->cacheList.pre;
    DELETE_NODE_FROM_LIST(leastRecentlyUsedNode);
    obj->hashMap[leastRecentlyUsedNode->key] = NULL;
    free(leastRecentlyUsedNode);
    obj->cacheNum--;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
    if (obj->capacity == 0) {
        return;
    }
    if (obj->hashMap[key] != NULL) {
        updateCacheValue(obj, key, value);
        return;
    }

    if (obj->cacheNum == obj->capacity) {
        delLeastRecentlyUsedCache(obj, key, value);
    }

    struct keyPair *node = (struct keyPair *)malloc(sizeof(struct keyPair));
    node->key = key;
    node->value = value;
    ADD_NODE_TO_LIST_HEAD(&obj->cacheList, node);

    obj->hashMap[key] = node;    
    obj->cacheNum++;
}

void lRUCacheFree(LRUCache* obj)
{
    struct keyPair *head = &obj->cacheList;
    struct keyPair *node = obj->cacheList.next;
    while (node != head) {
        struct keyPair *nextNode = node->next;
        free(node);
        node = nextNode;
    }
    obj->cacheList.pre = &obj->cacheList;
    obj->cacheList.next = &obj->cacheList;
    memset(obj->hashMap, 0, MAX_KEY_VALUE * sizeof(struct keyPair *));

    free(obj);
}
