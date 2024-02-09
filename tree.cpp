//+------------------------------------------------------------------------------------
//                          Family Tree Management System
//
//                                  Minor Project 
//         Team: Aman Sheoran || Milan Singh || Mayank Garg || Steve Yadav 
//  

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

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

struct node
{
    char name[50];
    short int age,x;
    bool g;
    node* fc;
    node* ns;

    node();
    void getData();
};

node::node()
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
    node* traverseDown(node*,char[]);
    node* traverseRight(node*,char[]);
    node* search(char[]);
    void addSib(node*,node*);
    void addChild(node*,node*);
    void addNew();
    void find();
    void show(node*);
    void destroy(node*);
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

void family::find()
{
    char name1[50],name2[50];
    cout<<"Enter names of two persons:\n";
    cin>>name1>>name2;
    node* ptr1 = search(name1);
    node* ptr2 = search(name2);
    node* ptr;
    node* ptrk=ptr1;
    node* ptrk1=ptr2;

    switch(ptr1->x - ptr2->x)
    {
        case 0:
            char s[50];
            strcpy(s,"sister");
            if(ptr1->g)
                strcpy(s,"brother");

            ptr = ptr1;
            while(ptr!=NULL)
            {
                if(ptr==ptr2)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<s<<endl;
                    return;
                }
                ptr = ptr->ns;
            }
            ptr = ptr2;
            while(ptr!=NULL)
            {
                if(ptr==ptr1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<s<<endl;
                    return;
                }
                ptr = ptr->ns;
            }
            cout<<endl<<name1<<" and "<<name2<<" are Cousins";
            break;

        case 1:
            char str3[50];
            strcpy(str3,"daughter");
            if(ptr1->g)
                strcpy(str3,"son");
            ptr2 = ptr2->fc;
            while(ptr2!=NULL)
            {
                if(ptr2==ptr1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<str3;
                    return;
                }
                ptr2=ptr2->ns;
            }
            strcpy(str3,"niece");
            if(ptr1->g)
                strcpy(str3,"nephew");
            cout<<endl<<name1<<" is "<<name2<<"'s "<<str3;
            break;
        case -1:
            char str[10];
            strcpy(str,"mother");
            if(ptrk->g)
                strcpy(str,"father");

            ptr = ptrk->fc;
            while(ptr!=NULL)
            {
                if(ptr==ptrk1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<str;
                    return;
                }
                ptr=ptr->ns;
            }
            strcpy(str,"aunt");
            if(ptrk->g)
                strcpy(str,"uncle");
            cout<<endl<<name1<<" is "<<name2<<"'s "<<str;
            break;

        case 2:
            char str1[50];
            strcpy(str1,"daughter");
            if(ptr2->g)
                strcpy(str1,"son");
            ptr2 = ptr2->fc->fc;
            while(ptr2!=NULL)
            {
                if(ptr2==ptr1)
                {
                    cout<<endl<<name1<<" is grand "<<str1<<" of "<<name2;
                    return;
                }
                ptr2 = ptr2->ns;
            }
            break;
        case -2:
            char str2[50];
            strcpy(str2,"mother");

            if(ptr1->g)
                strcpy(str2,"father");

            ptr1 = ptr1->fc->fc;

            while(ptr1!=NULL)
            {
                if(ptr1==ptr2)
                {
                    cout<<endl<<name1<<" is grand "<<str2<<" of "<<name2;
                    return;
                }
                ptr1 = ptr1->ns;
            }

            break;
        default:
            cout<<"Too far relationship";
            break;
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
        cout<<"*Not found*8";
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
        cout<<"\n1. Child\n2. Sibling\n\n"<< temp->name <<" is ____ to "<<name<<" : ";
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
    cout<<"\nPerson successfully added.\n";
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
#endif 
#ifdef LINUX
        system("clear");
#endif 
        cout<<"\n\n\n\tFamily tree no = "<<n<<"\n\n\t1. Add new person\n\t2. Find relationship b/w two persons\n\t3. Search\n\t4. Destroy\n\t5. Change family tree\n\t6. Exit\n\n\tEnter your choice = ";
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
                T[n].find();
                break;

        case 3:
                cout<<"Enter name of person to search: ";
                cin>>name;
                T[n].show(T[n].search(name));
                break;

        case 4:
                T[n].destroy(T[n].start);
                cout<<"Tree "<<n<<" has been destroyed successfully";
                break;

        case 5:
                cout<<"Enter family tree number: ";
                cin>>n;
                break;

        case 6:
                return 0;

        }
        cout<<"\n\nPress any key to continue.....";
        cin>>c;
        system("clear");
    }
}
