#define MAX_DOMAIN_NUM 300
#define MAX_DOMAIN_LEN 110
#define MAX_HASH_INDEX 255
#define MAX_TIMES_LEN 10
struct hashNode{
    char domain[MAX_DOMAIN_LEN];
    int visitTimes;
    struct hashNode *next;
};

void createOneDomainHashNode(char *domain, int visitTimes, struct hashNode **head, struct hashNode *pre, struct hashNode **hashTable)
{
    struct hashNode *node = (struct hashNode *)malloc(sizeof(struct hashNode));
    memset(node, 0, sizeof(struct hashNode));
    memcpy(node->domain, domain, strlen(domain));
    node->visitTimes = visitTimes;
    if (pre == NULL) {
        *head = node;
        node->next = NULL;
    } else {
        pre->next = node;
        node->next = NULL;
    }
}

void putOneLeverDomainVisitTimes2Hash(char *domain, int visitTimes, struct hashNode **hashTable)
{
    if (*domain == 0) {
        return;
    }

    int assicValue = 0;
    char *head = domain;
    while (*head != 0) {
        assicValue += *head++;
    }

    int hashIndex = assicValue % MAX_HASH_INDEX;
    struct hashNode *pre = NULL;
    struct hashNode *node = hashTable[hashIndex];    
    while (node != NULL) {
        if ((strlen(node->domain) == strlen(domain)) && (!memcmp(node->domain, domain, strlen(domain)))) {
            node->visitTimes += visitTimes;
            return;
        }
        pre = node;
        node = node->next;
    }

    createOneDomainHashNode(domain, visitTimes, &hashTable[hashIndex], pre, hashTable);
}

void procOneDomain(char *domain, struct hashNode **hashTable)
{
    char timeStr[MAX_TIMES_LEN] = {0};
    int i = 0;
    while (*domain != 0 && *domain != ' ') {
        timeStr[i++] = *domain++;
    }
    int time = atoi(timeStr);
    if (*domain++ == 0) {
        return;
    }

    while (*domain != 0) {
        putOneLeverDomainVisitTimes2Hash(domain, time, hashTable);
        while ((*domain != 0) && (*domain++ != '.')) {
        }
    }    
}

void adapterReturnValue(struct hashNode *node, char *ret)
{
    char timeStr[MAX_TIMES_LEN] = {0};
    //itoa(node->visitTimes, timeStr, 10);
    sprintf(timeStr, "%d", node->visitTimes);
    memcpy(ret, timeStr, strlen(timeStr));
    ret += strlen(timeStr);
    *ret++ = ' ';
    memcpy(ret, node->domain, strlen(node->domain));
}

void freeHashTable(struct hashNode **hashTable)
{
    int i = 0;
    for (; i < MAX_DOMAIN_NUM; i++) {
        struct hashNode *node = hashTable[i];
        while (node != NULL) {
            struct hashNode *nextNode = node->next;
            free(node);
            node = nextNode;            
        }
    }
}

char **allocReturnMemory()
{
    int i = 0;
    char **ret = (char **)malloc(MAX_DOMAIN_NUM * sizeof(char *));
    for (i = 0; i < MAX_DOMAIN_NUM; i++) {
        ret[i] = (char *)malloc(MAX_DOMAIN_LEN * sizeof(char));
        memset(ret[i], 0, MAX_DOMAIN_LEN * sizeof(char));
    }

    return ret;
}

char ** subdomainVisits(char ** cpdomains, int cpdomainsSize, int* returnSize)
{
    int i = 0;
    struct hashNode *hashTable[MAX_DOMAIN_NUM] = {NULL};

    for (; i < cpdomainsSize; i++) {
        procOneDomain(cpdomains[i], hashTable);
    }

    *returnSize = 0;
    char **ret = allocReturnMemory();
    for (i = 0; i < MAX_DOMAIN_NUM; i++) {
        struct hashNode *node = hashTable[i];
        while (node != NULL) {
            adapterReturnValue(node, ret[*returnSize]);
            (*returnSize)++;
            node = node->next;
        }
    }

    freeHashTable(hashTable);

    return ret;
}
