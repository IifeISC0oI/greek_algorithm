/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_DEGE_NUM 10000
struct node {
    int num;
    int inDegree;
    int edge[MAX_DEGE_NUM];
};

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
    struct node *course = (struct node *)malloc(numCourses * sizeof(struct node));
    memset(course, 0, numCourses * sizeof(struct node));
    int i = 0;
    int que[MAX_DEGE_NUM] = {0};
    int front = 0;
    int rear = 0;
    int *ret = (int *)malloc(MAX_DEGE_NUM * sizeof(int));
    int retNum = 0;
    
    for (; i < prerequisitesSize; i++) {
        int src = prerequisites[i][1];
        int dest =  prerequisites[i][0];
        course[src].edge[course[src].num++] = dest;
        course[dest].inDegree++;
    }
    for (i = 0; i < numCourses; i++) {
        if (course[i].inDegree == 0) {
            que[rear++] = i;
        }
    }

    while (front != rear) {
        int cur = que[front++];
        ret[retNum++] = cur; 
        int i = 0;
        for (; i < course[cur].num; i++) {
            int dest = course[cur].edge[i];
            course[dest].inDegree--;
            if (course[dest].inDegree == 0) {
                que[rear++] = dest;
            }
        }
    }

    free(course);
    if (retNum != numCourses) {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = retNum;

    return ret;
}
