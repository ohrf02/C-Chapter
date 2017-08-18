#include <stdio.h>
#include <malloc.h>
#include "Queue.h"

/*The node and the list structs*/
typedef struct Node {
    void* value;
    struct Node* next;
    struct Node* back;
}Node;

typedef struct List {
    struct Node* head;
    struct Node* last;
    int number_of_nodes;
    int sum_of_values;
}List;

/*The list and the node initialization*/
List* list_init(){
    List *l = (List*)malloc(sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->number_of_nodes = 0;
    l->sum_of_values = 0;
    return l;
}

Node* Node_init(void* value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->back = NULL;
    return node;

}

/*Removes all of the nodes in the list and the list itself.*/
void remove_list(List* list) {
    int size = list->number_of_nodes;
    int i = 0;
    Node* np = list->head;
    for (i; i < size; ++i) {
        free(np);
        ++np;
    }
    free(list);
}

void add_node(List* list, Node* node){

    /*If the node is not the first node in the list =>*/
    if(list->number_of_nodes > 0){
        list->last->next = node;
        node->back = list->last;
        list->last = node;

        printf("-> %d ", *(int *)node->value);

    }
        /*If the node is the first on in the list.*/
    else {
        list->head = node;
        list-> last = node;
        printf("%d ", *(int *)node->value);
    }

    /*Adds the node's value to the sum in the list and add one to the nodes count in the list.*/
    list->sum_of_values += *(int *)node->value;
    list->number_of_nodes ++;

}

/*Removes specific node from the list(and frees it's memory).*/
void remove_node(List* list, Node* node){

    Node* next = node->next;
    Node* back = node->back;

    /*If the node is the header of that list =>*/
    if(next != NULL && back == NULL) {
        list->head = next;
        next->back = NULL;
    }
    else {
        /*If the node is in the middle of the list =>*/
        if (next != NULL) {
            back->next = next;
            next->back = back;
        } else{
            /*If the node is the last on the list =>*/
            if(back != NULL ){
                list->last = list->last->back;
                back->next = NULL;
            }
        }
    }

    /*Frees the memory of the required node and change the sum of the nodes' values
     * and the nodes' count in the list.*/
    --list->number_of_nodes;
    list->sum_of_values -= *(int*)node->value;
    free(&node);
}

/*Returns the next node of the given node.*/
Node* get_next(Node* node){
    return node->next;
}

/*Returns a pointer to the first node of the given list.*/
Node* get_first(List* list){
    return list->head;
}

/*Returns a pointer to the last node of the given list.*/
Node* get_last(List* list){
    return list->last;
}

/*Returns the length of a given list.*/
int get_length(List* list){
    return list->number_of_nodes;
}
/*Returns the previous node of the given node.*/
Node* get_back(Node* node){
    return node->back;
}

/*Returns a pointer to the node's value.*/
void* get_value(Node* node){
    return node->value;
}

/*Returns the average of the nodes' values (as a double).*/
double get_average(List* list){
    return (double)list->sum_of_values / list->number_of_nodes;
}

/*The main function.*/
int main() {
    List* list = list_init();

    int value = 44, value1 = 55, value2 = 100;
    Node* n1 = Node_init(&value);
    Node* n2 = Node_init(&value1);
    Node* n3 = Node_init(&value2);

    add_node(list, n1);
    add_node(list, n2);
    add_node(list, n3);

    remove_node(list, n2);

    printf("%d %d %f, %d", *(int *)get_value(get_back((n3))), *(int*)get_value(list->head), get_average(list), get_length(list));
    remove_list(list);
    return 0;
}
