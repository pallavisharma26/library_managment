#include<iostream>
#include<time.h>
#include<string>
using namespace std;

struct Book
{
    int bookId;
    string bookName;
    string authorName;
    int noOfCopy;
    Book *next;
    Book(){}
    Book(int id, string name, string authname, int num){
        bookId = id;
        bookName = name;
        authorName = authname;
        noOfCopy = num;
        next = NULL;
    }
};
Book *bookhead = NULL;

struct Student
{
    int roll;
    string name;
    string branch;
    int fine;
    Book *bookIssued[3];
    Student *next;
    Student(){}
    Student(int id, string stname, string branchname)
    {
        roll = id;
        name = stname;
        branch = branchname;
        fine = 0;
        next = NULL;
        for(int i=0;i<3;i++)
        bookIssued[i] = NULL;
    }
};
Student *studenthead = NULL;
void createBook(int id, string name, string authname, int num)
{
    Book *book = new Book(id, name, authname, num);
    if(bookhead == NULL)
        bookhead = book;
    else
    {
        book->next = bookhead;
        bookhead = book;
    }
   cout<<"Book instance is created"<<endl;
}

void createStudent(int id, string stname, string branchname)
{
    Student *s = new Student(id, stname, branchname);
    if(studenthead == NULL)
        studenthead = s;
    else
    {
        s->next = studenthead;
        studenthead = s;
    }
    cout<<"Student instance is created"<<endl;
}

void printBookDetail(Book *b)
{
    cout<<"___________________________________________________________"<<endl;
    cout<<"Book Id: "<<b->bookId<<"\t"<<"Book Name: "<<b->bookName<<"\n";
    cout<<"By:- "<<b->authorName<<endl;
    cout<<"___________________________________________________________"<<endl;
    
}

void printBookAll()
{
    Book *temp = bookhead;
    while(temp){
        cout<<"______________________________________________________________"<<endl;
        cout<<"Book Id: "<<temp->bookId<<"\t"<<"Book Name: "<<temp->bookName<<"\n";
        cout<<"By:- "<<temp->authorName<<"\tNumber of copy available: "<<temp->noOfCopy<<endl;
        cout<<"______________________________________________________________";
        cout<<endl;
        temp= temp->next;
    }
}
Book* searchBookId(int id)
{
    if(bookhead == NULL)
    {
        cout<<"Book is not available"<<endl;
        return NULL;
    }
    Book *temp = bookhead;
    while(temp){
        if(temp->bookId == id )
        {

            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Book* searchBookName(string name)
{
    if(bookhead == NULL)
    {
        cout<<"Book is not available"<<endl;
        return NULL;
    }
    Book *temp = bookhead;
    while(temp){
        if(temp->bookName == name)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

bool bookAvailability(int id)
{
    if(bookhead == NULL)
    {
        cout<<"Book is not available"<<endl;
        return false;
    }
    Book *temp = bookhead;
    while(temp){
        if(temp->bookId == id && temp->noOfCopy != 0)
        {
            cout<<"Book is available.\n"<<"Copies available: "<<temp->noOfCopy<<endl;
            return true;
        }
        temp = temp->next;
    }
    return false;

}
Student* searchStudentId(int id)
{
    if(studenthead == NULL)
    {
        cout<<"Student data is not available"<<endl;
        return NULL;
    }
    Student *temp = studenthead;
    while(temp)
    {
        if(temp->roll == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void printStudentDetail(Student *s)
{
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Roll No: "<<s->roll<<"\t"<<"Name: "<<s->name<<endl;
    cout<<"Branch: "<<s->branch<<endl;
    cout<<"Book issued:- "<<endl;
    for(int i =0;i<3;i++)
    {
        if(s->bookIssued[i] != NULL)
            printBookDetail(s->bookIssued[i]);
    }
    cout<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
}

void bookIssue(int rollno, int id)
{
   Student *s = searchStudentId(rollno);
   Book *b = searchBookId(id);
   if(s == NULL)
    cout<<"Student data is not available"<<endl;
   else if(b == NULL)
    cout<<"Book is not available"<<endl;
   else
   {
       int i;
       for(i=0;i<3;i++)
       {
           if(s->bookIssued[i] == NULL)
            break;
       }
       if(i == 3)
        cout<<"Your book limit exceeded"<<endl;
       else
       {
           if(b->noOfCopy == 0)
            cout<<"Currently book is not available"<<endl;
           else{
           b->noOfCopy -= 1;
           s->bookIssued[i] = b;
           cout<<"Your book is issued"<<endl;
           }
       }

   }

}

void returnBook(int rollno, int id)
{
    Student *s = searchStudentId(rollno);
    Book *b = searchBookId(id);
   if(s == NULL)
    cout<<"Student data is not available"<<endl;
    else if(b == NULL)
        cout<<"Book data is not available"<<endl;
    else{
        int i;
        for(i=0;i<3;i++)
        {
            if(s->bookIssued[i]->bookId == b->bookId){
                s->bookIssued[i] = NULL;
                break;
            }
        }
        b->noOfCopy += 1;
       cout<<"Your book is returned"<<endl;
    }
}

int main()
{
    while(1)
    {
        int option;
        cout<<"--------------------------- Welcome to Library Management System --------------------------"<<endl;
        cout<<"Choose from these option :-"<<endl;
        cout<<"1 for creating book instance\n";
        cout<<"2 for creating student instance\n";
        cout<<"3 for book issue\n";
        cout<<"4 for book return\n";
        cout<<"5 for print book detail\n";
        cout<<"6 for print all book available in library\n";
        cout<<"7 for print student detail\n";
        cout<<"8 for book availability\n";
        cout<<"9 for quit\n";
        cout<<"Enter option: ";
        cin>>option;
        switch(option)
        {
        case 1:
            {
                int id;
                string name;
                string authname;
                int num;
                cout<<"Enter book id: ";
                cin>>id;
                cout<<"Enter book name: ";
                //cin.sync();
                cin>>ws;
                getline(cin,name);

                cout<<"Enter author name: ";
                //cin.sync();
                cin>>ws;
                getline(cin,authname);

                cout<<"Total copies of "<<name<<": ";
                cin>>num;
                createBook(id, name, authname, num);
                break;
            }
        case 2:
            {
                int id;
                string stname;
                string branchname;
                cout<<"Enter roll number: ";
                cin>>id;
                cout<<"Enter student name: ";
                //cin.sync();
                cin>>ws;
                getline(cin, stname);
                cout<<"Enter branch name like (Computer Science as CS): ";
                cin>>branchname;
                createStudent(id, stname, branchname);
                break;
            }
        case 3:
            {
                int roll, bookid;
                cout<<"Enter Roll number of student: ";
                cin>>roll;
                cout<<"Enter book id: ";
                cin>>bookid;
                bookIssue(roll, bookid);
                break;
            }
        case 4:
            {
                int roll, bookid;
                cout<<"Enter Roll number of student: ";
                cin>>roll;
                cout<<"Enter book id: ";
                cin>>bookid;
                returnBook(roll, bookid);
                break;
            }
        case 5:
            {
                int bookid;
                cout<<"Enter book id: ";
                cin>>bookid;
                Book *b = searchBookId(bookid);
                printBookDetail(b);
                break;
            }
        case 6:
            {
                cout<<"All book in Library:- \n";
                printBookAll();
                break;
            }
        case 7:
            {
                int roll;
                cout<<"Enter roll number of student: ";
                cin>>roll;
                Student *s = searchStudentId(roll);
                printStudentDetail(s);
                break;
            }
        case 8:
            {
                int bookid;
                cout<<"Enter book id: ";
                cin>>bookid;
                bool avail = bookAvailability(bookid);

                break;
            }
        case 9:
            return 0;
        default:
            cout<<"Enter right choice";
        }
    }
    return 0;
}