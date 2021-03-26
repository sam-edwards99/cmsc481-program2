#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int LAYER_1_NODES = 10;
const int LAYER_2_NODES = 20;
const int LAYER_3_NODES = 40;

//define node structure
typedef struct node{
    char name[3];
    struct node * link1;
    struct node * link2;
} node;

//create global arrays of nodes to represent connections
node layer1[10];
node layer2[20];
node layer3[40];

//create node layers and give each node a proper name
void populate_layers(){
    char intToChar[2] = "";
    for(int i = 0; i < LAYER_1_NODES; i++){
        //sprintf(intToChar,"%d",i+1);
        snprintf(intToChar, 2, "%d", i+1);
        //itoa(i+1, intToChar,10);
        strcpy(layer1[i].name, "A");
        strcat(layer1[i].name, intToChar);
    }

    for(int i = 0; i < LAYER_2_NODES; i++){
        //sprintf(intToChar,"%d",i+1);
        snprintf(intToChar, 2, "%d", i+1);
        //itoa(i+1, intToChar,10);
        strcpy(layer2[i].name, "B");
        strcat(layer2[i].name, intToChar);
    }

    for(int i = 0; i < LAYER_3_NODES; i++){
        //sprintf(intToChar,"%d",i+1);
        snprintf(intToChar, 2, "%d", i+1);
        //itoa(i+1, intToChar,10);
        strcpy(layer3[i].name, "C");
        strcat(layer3[i].name, intToChar);
    }
    return;
}

//helper function to link one node to a node of another layer
void link(node * link_src, node * link_dest){
    if(link_src->link1 == NULL){
        link_src->link1 = link_dest;
    }
    else if(link_src->link2 == NULL){
        link_src->link2 = link_dest;
    }
    else{
        printf("Error: can only link a node once or twice\n");
    }
}

//link the node layers as specified
void link_layers(){
    //link layer3 -> layer2
    //printf("Link Layer3 -> Layer2\n\n");
    for(int i = 0; i < LAYER_3_NODES; i++){
        //link directly to layer2 "parent/node"
        link(&layer3[i], &layer2[i/2]);
        //printf("Linked %s -> %s\n", layer3[i].name, layer2[i/2].name);
        link(&layer3[i], &layer2[((i/2) + 1) % LAYER_2_NODES]);
        //printf("Linked %s -> %s\n", layer3[i].name, layer2[((i/2) + 1) % LAYER_2_NODES].name);
    }

    //link layer2 -> layer1
   // printf("\nLink Layer2 -> Layer1\n\n");
    for(int i = 0; i < LAYER_2_NODES; i++){
        //link directly to layer2 "parent/node"
        link(&layer2[i], &layer1[i/2]);
        //printf("Linked %s -> %s\n", layer2[i].name, layer1[i/2].name);
        link(&layer2[i], &layer1[((i/2) + 1) % LAYER_1_NODES]);
        //printf("Linked %s -> %s\n", layer2[i].name, layer1[((i/2) + 1) % LAYER_1_NODES].name);
    }
}

//this function prints the final output traversing the inter-layer node-to-node connections
void check_connections(){
    //layer 1 -> layer 2
    printf("Output: \n");
    printf("Layer 1 to Layer 2: \n");
    for(int i = 0; i < LAYER_1_NODES; i++){
        printf("%s ", layer1[i].name);
        for(int j = 0; j < LAYER_2_NODES; j++) {
            if(layer2[j].link1 == &layer1[i] || layer2[j].link2 == &layer1[i]){
                printf("%s,", layer2[j].name);
            }
        }
        printf("\n");
    }
    printf("\n");

    //layer 2 -> layer 1
    printf("Layer 2 to Layer 1: \n");
    for(int i = 0; i < LAYER_2_NODES; i++) {
        printf("%s ", layer2[i].name);
        printf("%s, %s\n" ,layer2[i].link1->name, layer2[i].link2->name);
    }
    printf("\n");

    //layer 2 -> layer 3
    printf("Layer 2 to Layer 3: \n");
    for(int i = 0; i < LAYER_2_NODES; i++){
        printf("%s ", layer2[i].name);
        for(int j = 0; j < LAYER_3_NODES; j++) {
            if(layer3[j].link1 == &layer2[i] || layer3[j].link2 == &layer2[i]){
                printf("%s,", layer3[j].name);
            }
        }
        printf("\n");
    }
    printf("\n");

    //layer 3 -> layer 2
    printf("Layer 3 to Layer 2: \n");
    for(int i = 0; i < LAYER_3_NODES; i++) {
        printf("%s ", layer3[i].name);
        printf("%s, %s\n" ,layer3[i].link1->name, layer3[i].link2->name);
    }


}

//unused test function
void print_names(){
    printf("Printing Names...\n");
    printf("Layer 1\n");
    for(int i = 0; i < LAYER_1_NODES; i++) {
        printf("%s,", layer1[i].name);
    }

    printf("\nLayer 2\n");
    for(int i = 0; i < LAYER_2_NODES; i++) {
        printf("%s,", layer2[i].name);
    }

    printf("\nLayer 3\n");
    for(int i = 0; i < LAYER_3_NODES; i++) {
        printf("%s,", layer3[i].name);
    }

    printf("\n\n");
}

int main() {
    populate_layers();
    print_names();
    link_layers();
    check_connections();
    return 0;
}
