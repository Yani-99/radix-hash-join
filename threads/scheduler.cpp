#include "scheduler.hpp"

Queue * globalQueue;

Queue * newQueue(){
    Queue * queue = new Queue;
    *queue = (Queue){0};
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

QueueNode * newNode(Job * job){
    QueueNode * node = new QueueNode;
    node->job = job;
    node->next = NULL;
    return node;
}

void addToQueue(Queue * queue, Job * job){
    if(queue->first == NULL){
        queue->first = newNode(job);
        queue->last = queue->first;
    }
    else{
        queue->last->next = newNode(job);
        queue->last = queue->last->next;
	}
}

Job * popFromQueue(Queue * queue){
    QueueNode * node = queue->first;
    queue->first = queue->first->next;

    Job * job = node->job;
    delete node;
    return job;
}

char notEmpty(Queue * queue){
    return !(queue->first == NULL);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * myRoutine(void *arg){

    pthread_mutex_lock(&mutex);
    std::cout << "Hello from thread " << pthread_self() << '\n';

    Job * curJob = popFromQueue(globalQueue);

    curJob->Run();

    pthread_mutex_unlock(&mutex);
    
    delete curJob;

    return NULL;
}

bool JobScheduler::Init(uint64_t num_of_threads){
    threadNum = num_of_threads;
    threadPool = createThreadPool(&myRoutine,threadNum);
    return true;
}

bool JobScheduler::Destroy(){
    delete[] threadPool;
}

void JobScheduler::Barrier(){
    return;
}

bool JobScheduler::Schedule(Job* job){
    addToQueue(globalQueue,job);
    return true;
}

void JobScheduler::Stop(){
    for( uint64_t i = 0; i < threadNum; i ++ ){
        joinThread(threadPool[i]);
    }
}
