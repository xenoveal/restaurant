#include<iostream>
#include<string.h>
using namespace std;

struct Order_Items{
    char item_name[50];
    int price;
    int quantity;
    Order_Items* next;
};

struct Orders{
    int order_number;
    char customer_name[50];
    int total_price;
    Order_Items* items;
    Orders* next;
};

struct Queue{
    Orders* front;
    Orders* back;
};

int order_number = 0;
// Initialize
Queue Q;
Orders* served_list = NULL;

int menu();
void add_order(Queue& Q);
void add_items(Order_Items* &items);
void print(Orders* front);
void served(Queue& Q, Orders* &Served);

main(){
    Q.front = NULL;
    Q.back = NULL;
    menu();
}

int menu(){
    int m;
    cout<<"========================================"<<endl;
    cout<<"Integrated Restaurant Management Program"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
    cout<<"1. Add New Order\n2. Serve Order\n3. Order List\n4. Complete Order\n5. Order Completed\n6. Exit Program"<<endl;
    cout<<"========================================"<<endl;
    cout<<"Select Menu: ";cin>>m;
    switch (m)
    {
    case 1:
        add_order(Q);
        cout<<"\nAdded!"<<endl;
        break;
    case 2:
        served(Q, served_list);
        cout<<"\nServed List"<<endl;
        print(served_list);
        break;
    case 3:
        cout<<"\nOrder List"<<endl;
        print(Q.front);
        break;
    default:
        return 0;
        break;
    }
    return menu();
}

void add_order(Queue& Q){
    Orders* new_order = new Orders;
    new_order->next = NULL;

    // Increment 1 to order number and add to order number
    order_number++;
    new_order->order_number = order_number; 

    // Get customer name
    char name[50];
    cout<<"Customer Name: ";
    cin.ignore();
    cin.getline(name, 50);
    strcpy(new_order->customer_name, name);

    // Assign the item list that cust buy in the order
    Order_Items* Item_List = NULL;
    char add_new_item = 'y';
    while(add_new_item == 'y'){
        add_items(Item_List);
        cout<<"New Item? y for yes, other key for no\n";
        cin>>add_new_item;
    }
    new_order->items = Item_List;

    // Calculate total price
    int total_price = 0;
    while(Item_List != NULL){
        total_price += (Item_List->price * Item_List->quantity);
        Item_List = Item_List->next;
    }
    new_order->total_price = total_price;

    // Insert into queue
    if(Q.front == NULL){
        Q.front = new_order;
        Q.back = new_order;
    }else{
        Q.back->next = new_order;
        Q.back = Q.back->next;
    }
}

void add_items(Order_Items* &items){
    Order_Items* new_item = new Order_Items;
    new_item->next = NULL;

    // Select item name
    int select_item;
    cout<<"Items"<<endl;
    cout<<"1. Nasi Goreng\t\tRp. 14000\n2. Indomie Goreng\tRp. 8.000\n3. Kwetiau Goreng\tRp. 18.000\n4.Indomie Rebus\tRp. 8.000"<<endl;
    cout<<"Select Item: ";cin>>select_item;
    cout<<"Quantity: ";cin>>new_item->quantity;
    switch (select_item)
    {
    case 1:
        strcpy(new_item->item_name, "Nasi Goreng");
        new_item->price = 14000;
        break;  
    case 2:
        strcpy(new_item->item_name, "Indomie Goreng");
        new_item->price = 8000;  
    case 3:
        strcpy(new_item->item_name, "Kwetiau Goreng");
        new_item->price = 18000;    
    case 4:
        strcpy(new_item->item_name, "Indomie Rebus");
        new_item->price = 8000;      
    default:
        break;
    }

    // Insert into linked list
    if(items == NULL){
        items = new_item;
    }else if(items->next == NULL){
        items->next = new_item;
    }else{
        Order_Items* pointer = items;
        while(pointer->next != NULL){
            pointer = pointer->next;
        }
        pointer->next = new_item;
    }
}

void print(Orders* front){
    if(front != NULL){
        do{
            cout<<"Order Number: "<< front->order_number<<endl;
            cout<<"Customer Name: "<< front->customer_name<<endl;
            cout<<"Total Price: " << front->total_price<<endl;
            cout<<"List Order: "<<endl;
            cout<<"\tItem Name\tPrice\tQuantity"<<endl;
            Order_Items* items;
            items = front->items;
            while (items != NULL){
                cout<<"\t"<<items->item_name<<"\t"<<items->price<<"\t"<<items->quantity<<endl;
                items = items->next;
            }
            front = front->next;
        }while(front!=NULL);
    }
    else{
        cout<<"No Order!"<<endl;
    }
}

void served(Queue &Q, Orders* &Served){
    Orders* now_served = Q.front;
    if(now_served != NULL){
        Q.front = now_served->next;
        now_served->next = NULL;
        if(Served == NULL){
            Served = now_served;
        }else if(Served->next == NULL){
            Served->next = now_served;
        }else{
            Orders* pointer = Served;
            while(pointer->next!=NULL){
                pointer = pointer->next;
            }
            pointer->next = now_served;
        }
    }else{
        cout<<"No Orders to serve!"<<endl;
    }
}