#include<iostream>

using namespace std;

struct Node { 
    int data; 
    struct Node *next; 
}; 
struct Node* head = NULL;
struct Node* tail = NULL;
struct Node* tempHead = NULL;
struct Node* tempTail = NULL;

void insert(int new_data, int flag) { 
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node -> data = new_data;  
    new_node -> next = NULL;

    if(flag) {
        if(head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail -> next = new_node;
            tail = new_node;
        }
    } else {
        if(tempHead == NULL) {
            tempHead = new_node;
            tempTail = new_node;
        } else {
            tempTail -> next = new_node;
            tempTail = new_node;
        }
    }
} 

void display(int flag) {
    struct Node* ptr;
    
    if(flag){
        ptr = head;
        while (ptr != NULL) { 
            cout << ptr -> data << " "; 
            ptr = ptr -> next; 
        }
    } else {
        ptr = tempHead;
        while (ptr != NULL) { 
            cout << ptr -> data << " "; 
            ptr = ptr -> next; 
        } 
    }

    cout << endl << endl;
} 

void fragmentation(int mtu) {
    struct Node* ptr = head;
    struct Node* prev = NULL;
    struct Node* temp;

    do {
        if(ptr -> data > mtu) {
            int packet = ptr -> data;
            
            do {
                insert(mtu, 0);
                packet -= mtu;
            } while (packet > mtu);

            insert(packet, 0);

            if(prev == NULL) {
                head = tempHead;

                if(ptr -> next == NULL) {
                    tail = tempTail;
                }
            } else {
                if(ptr -> next != NULL) {
                    prev -> next = tempHead;
                } else {
                    prev -> next = tempHead;
                    tail = tempTail;
                }
            }

            tempTail -> next = ptr -> next;
            ptr = tempHead;

            tempTail = NULL;
            tempHead = NULL;
        }

        prev = ptr;
        ptr = ptr -> next;
   } while(ptr != NULL);
}

int main() { 
    int routers;

    cout << endl << "Enter No. of Routers : ";
    cin >> routers;

    int mtu[routers], temp, packet;

    cout << endl;

    for(int i = 0; i < routers; i++) {
        cout << "Enter MTU for Router" << i+1 << " : ";
        cin >> mtu[i];
    }

    cout << endl << "Enter Packet Size : ";
    cin >> packet;

    insert(packet, 1);

    cout << endl;

    for(int i = 0; i < routers; i++) {
        fragmentation(mtu[i]);

        cout << "The datagram after Router" << i+1 << " is: ";
        display(1);
    }

   return 0;
}