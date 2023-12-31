//+------------------------------------------------------------------------------------
//                          Family Tree Manaement system
//
//                                  Minor Project 
//         Team: Aman sheoran || Milan singh || Mayank Garg || Steve Yadav 
//  

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define Linux

void welcome()
{
    int n;
    cout << "***********************************************************************\n";
    cout << "          Welcome to Family Tree Management C++ Application       \n";
    cout << "***********************************************************************\n";
    cout << "- Simplify the process of building and maintaining family trees." <<endl;
    cout << "- Store detailed information about each family member." <<endl;
    cout << "- Automatically generate and update the tree structure." <<endl;
    cout << "- Features for searching, filtering, and exporting family tree data." << endl;
    cout << "- An accessible and enjoyable tool for preserving genealogy." << endl << endl;
    cout << "Warm regards," << endl <<  endl;
    cout<<"Press Enter to Continue!!";
    cin.ignore();
    system("cls");
}
// this is the node , each person will be a node 
struct node
{
    char name[50];
    short int age,x;    // x - height of node
    bool g;             // g- gender
    node* fc;           // Pointer to first child
    node* ns;           // Pointer to next sibiling

    node();             // constructor 
    void getData();     // function to get person data
};

node::node()             // node data member defination with null value
{
    fc=ns=NULL;
    g=0;
    strcpy(name,"");
    age=x=0;
}

void node::getData()
{
    int choice;
    cout<<"\nName of the Person: ";
    cin>>name;
    cout<<"Age of "<<name<<": ";
    cin>>age;
    gender:
	    cout <<"Choose the gender of"<< name <<endl;
	    cout<<"1. Male"<<endl;
	    cout<<"2. Female"<<endl;
	    cout<<"Enter Choice: ";
	    cin >> choice;
	    switch(choice){
	    	case 1:
	    		g=1;
	    		break;
	    	case 2:
	    		g=0;
	    		break;
	    	default:
	    		cout<<endl<<"Wrong choice! choose the correct option."<<endl;
	    		goto gender;
	}
}

class family
{

public:

    node* start;

    family();

    node* traverseDown(node*,char[]);   // Search functions
    node* traverseRight(node*,char[]);
    node* search(char[]);

    void addSib(node*,node*);           // Functions for adding new members
    void addChild(node*,node*);
    void addNew();

    void find();                        // Function to find relations
    void show(node*);                   // Function to show details of particular person
    void display(node*);                // Function to display full tree
    void destroy(node*);                // Function to destroy full tree
    void updateX(node*,int);

};
family::family()
{
    start = NULL;
}
void family::destroy(node* ptr)
{
    node* temp = ptr;

    if(ptr==NULL)
        return;

    while(ptr!=NULL)
    {
        destroy(ptr->fc);
        temp = ptr;
        ptr = ptr->ns;
        delete temp;
    }

    start = NULL;
}
void family::show(node* ptr)
{
    char g[10];
    strcpy(g,"Female");
    if(ptr->g)
        strcpy(g,"Male");
    cout<<"\n\nName: "<< ptr->name <<endl;
    cout<<"Age: "<< ptr->age <<endl;
    cout<<"Gender: "<<g<<endl;
}
void family::updateX(node* ptr,int x)
{
    if(ptr==NULL)
        return;

    while(ptr!=NULL)
    {
        updateX(ptr->fc,x++);
        if(ptr->ns!=NULL)
            ptr->ns->x = x;
        ptr = ptr->ns;
    }
}
node* family::search(char s[50])
{
    node *ptr = start;

    if(strcmp(ptr->name,s)==0)
        return ptr;
    else if(traverseRight(start,s)!=NULL)
        return traverseRight(start,s);
    else if(traverseDown(start,s)!=NULL)
        return traverseDown(start,s);
    else
    {
        return NULL;
        cout<<"***Not found***8";
    }
}

node* family::traverseDown(node* ptr, char s[50])
{
    ptr = ptr->fc;

    while(ptr!=NULL)
    {
        if(  strcmp(ptr->name,s)==0 )
            return ptr;
        else if(traverseRight(ptr,s)!=NULL)
            return traverseRight(ptr,s);
        else
            ptr = ptr->fc;
    }
    return NULL;
}

node* family::traverseRight(node* ptr, char s[50])
{
    ptr = ptr->ns;

    while(ptr!=NULL)
    {
        if(strcmp(ptr->name,s)==0)
            return ptr;
        else if (traverseDown(ptr,s)!=NULL)
            return traverseDown(ptr,s);
        else
            ptr = ptr->ns;
    }
    return NULL;
}

void family::addNew()
{
    node* temp = new node;
    temp->getData();

    if(start == NULL)
    {
        start = temp;
        temp->x=0;
    }

    else
    {
        cout<<"\nEnter any relation's name: ";
        char name[50];
        cin>>name;
        cout<<"\n1. Child\n2. Sibiling\n\n"<< temp->name <<" is ____ to "<<name<<" : ";
        int opt;
        cin>>opt;
        switch(opt)
        {
            case 1:
                    addChild(search(name),temp);
                    break;
            case 2:
                    addSib(search(name),temp);
                    break;

        }
    }
    cout<<"\nPerson sucessfully added.\n";
}

void family::addSib(node* a,node* b)
{

    while(a->ns!=NULL)
        a=a->ns;
    a->ns = b;

    b->x = a->x;
}

void family::addChild(node* a,node* b)
{
    if(a->fc==NULL)
        a->fc = b;
    else
        addSib(a->fc,b);

    b->x = a->x+1;
}

int main()
{
     
     welcome();
    family T[100];
    int opt,n,n1,n2;
    char c,name[50];
    cout<<"\nEnter the family tree number = ";
    cin>>n;
    while(1)
    {
#ifdef WINDOWS
        system("cls");
#endif // WINDOWS
#ifdef LINUX
        system("clear");
#endif // LINUX
        cout<<"\n\n\n\tFamily tree no = "<<n<<"\n\n\t1. Add new person\n\t2. Search\n\t3. Destroy\n\t4. Exit\n\n\tEnter your choice = ";
        cin>>opt;
        cout<<endl;

        switch(opt)
        {

        default:
                cout<<"Invalid input";
                break;
        case 1:
                T[n].addNew();
                break;
        case 2:
                cout<<"Enter name of person to search: ";
                cin>>name;
                T[n].show(T[n].search(name));
                break;
        case 3:
                T[n].destroy(T[n].start);
                cout<<"Tree "<<n<<" has been destroyed sucessfully";
                break;
        case 4:
            return 0;
        }
        cout<<"\n\nPress any key to continue.....";
        cin>>c;
        system("clear");
    }
}