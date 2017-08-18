//
// Created by ohrf02 on 8/6/2017.
//
#include <malloc.h>
#include <stdio.h>

/*The Queue and the Node Structs.*/
typedef struct Queue{
    struct Node* head;
    struct Node* last;
    int nodes_count;

}Queue;

typedef struct Node{
    void* value;
    struct Node* next;
    struct Node* prev;
}Node;

/*The initialization of the Queue.*/
Queue* queue_init(){
    Queue* q = malloc(sizeof(Queue));
    q->nodes_count = 0;
    q->head = NULL;
    q->last = NULL;

    return q;
}

/*The initialization of the node.*/
Node* node_init(void* value){
    Node* node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;

    return node;
}

/*The destructor of the queue.*/
void remove_queue(Queue* q) {
    int size = q->nodes_count;
    int i = 0;
    Node* np = q->head;
    for (i; i < size; ++i) {
        free(np);
        ++np;
    }
    free(q);
}

/*Returns the first element of the queue without pop it from the queue.*/
void* peek(Queue* q){
    return q->head->value;
}

/*Returns the queue's length.*/
int get_length(Queue* q){
    return q->nodes_count;
}

/*Adds another element to the queue.*/
void enqueue(Queue* q, Node* node){

    if(q->nodes_count > 0){
        q->last->next = node;
        q->last = node;
    }
    else{
        q->head = node;
        q->last = node;
    }
    q->nodes_count ++;

}

/*Pops and returns the first element in the queue.*/
void* dequeue(Queue* q){
    /*If the queue has values =>*/
    if(q->nodes_count > 0){
        void* return_value = q->head->value;
        Node* node = q->head;

        /*If the queue has more than one value =>*/
        if (q->nodes_count > 1) {
           q->head = q->head->next;
       }
        /*If the queue has only one value*/
        else{
            q->last = NULL;
            q->head = NULL;
       }
        q->nodes_count--;
        free(node);
        return return_value;
    }
    return (void*)0;
}

/*The main function of this file (does not necessary because it is a module...)*/
int main(){
    int value = 44, value1 = 55, value2 = 66;
    Node* n1 = node_init(&value);
    Node* n2 = node_init(&value1);
    Node* n3 = node_init(&value2);

    Queue* queue = queue_init();

    enqueue(queue, n1);
    enqueue(queue, n2);
    enqueue(queue, n3);

    int a = *(int*)dequeue(queue);


    printf("%d", get_length(queue));

    remove_queue(queue);
    return 0;
};
