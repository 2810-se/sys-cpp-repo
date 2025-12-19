#include <iostream>
#include<string>
#include<cstdlib>
using namespace std;
class Date //date class
{
private:
    int date,month,year;
public:
    Date()
    {
        date=0;
        month=0;
        year=0;
    }
    void inputDate()
    {
        cout<<"Enter the DD/MM/YY ";
        cin>>date;
        cin>>month;
        cin>>year;
    }
    void displayDate()
    {
      cout<<date<<"/"<<month<<"/"<<year<<endl;
    }
};

class Person
{
protected:
    int age;
    long long cellNo;
    string name,address,sex,cnic;
    Date dob;
public:
    Person()
    {
        age=0;
        cellNo=0;
        name="NONAME";
        address="VACANT";
        sex="NOGEN";
        cnic="NULL";
    }
    void inputPerson() //person class
    {
        cout<<"Enter the name of a Person: ";
        getline(cin, name);
        cout<<"Enter age: "<<endl;
        cin>>age;
        cout<<"Enter gender of a Person: "<<endl;
        cin>>sex;
        cout<<"Enter Date Of Birth: "<<endl;
        dob.inputDate();
        cin.ignore();
        cout<<"Enter address of a Person: "<<endl;
        getline(cin, address);
        cout<<"Enter Cell Number of a Person: "<<endl;
        cin>>cellNo;
        cin.ignore();
        cout<<"Enter CNIC of a Person: "<<endl;
        getline(cin, cnic);
        system("cls");
    }
    void displayPerson()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Sex(M/F): "<<sex<<endl;
        cout<<"Date Of Birth: ";
        dob.displayDate();
        cout<<"Address: "<<address<<endl;
        cout<<"CellNO.: "<<cellNo<<endl;
        cout<<"CNIC: "<<cnic<<endl;
    }

    string getName(){return name;}
};

class Criminal : public Person
{
private:
    string crimeType,complainerName,investigatingOfficer;
    int punishmentYears;
    Date crimeDate;
    Date punishmentDate;
public:
    Criminal()
    {
        crimeType="NOCRIME";
        complainerName="NOCOMP";
        investigatingOfficer="NOSHO";
        punishmentYears=0;
    }
    void inputCriminal()
    {
        inputPerson();
        cout<<"Enter Crime Type: ";
        getline(cin,crimeType);
        cout<<"Enter Complainer's Name: "<<endl;
        getline(cin, complainerName);
        cout<<"Enter the Officer's Name: "<<endl;
        getline(cin, investigatingOfficer);
        cout<<"Enter punishment years: "<<endl;
        cin>>punishmentYears;
    }
    void displayCriminal()
    {
        displayPerson();
        cout<<"Crime Type: "<<crimeType<<endl;
        cout<<"Complainer's Name: "<<complainerName<<endl;
        cout<<"Officer's Name: "<<investigatingOfficer<<endl;
        cout<<"Punishment Years: "<<punishmentYears<<endl;
    }
    string getCrimeType(){return crimeType;}
    void setCrimeType(string c){crimeType=c;}
    void setPunishment(int p){punishmentYears=p;}

};

class Node
{
    public:
    Criminal data;
    Node*next;

    Node()
    {
        next=NULL;
    }
};

class PoliceRecordSystem
{
    private:
    Node*head;
    public:
    PoliceRecordSystem()
    {
        head=NULL;
    }

    void addCriminal()
    {
        Criminal c;
        c.inputCriminal();
        Node*newNode=new Node();
        newNode->data=c;
        newNode->next=NULL;

        if(head==NULL)
        {
            head=newNode;
        }
        else
        {
            Node*temp=head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=newNode;
        }
        cout<<"Record Added!"<<endl;
        
    }

    void displayCriminals()
    {
        if(head==NULL)
        {
            cout<<"OOPS!! NO RECORD FOUND"<<endl;
        }
        Node*temp=head;
        while(temp!=NULL)
        {
            temp->data.displayCriminal();
            temp=temp->next;        }
    }

    void search_Criminal_byName()
    {
        string target;
        cout<<"Enter the name to search: ";
        getline(cin, target);
        Node*temp=head;
        bool found=false;
        while(temp!=NULL)
        {
            if(temp->data.getName()==target)
            {
                cout<<"Record Found\n";
                temp->data.displayCriminal();
                found=true;
                break;
            }
           temp=temp->next; 
        }
        if(!found)
        cout<<"OOPS! CRIMINAL NOT FOUND\n";
    }

    void search_by_CrimeType()
    {
        string target;
        cout<<"Enter Crime Type to search: ";
        getline(cin, target);

        Node*temp=head;
        bool found=false;
        while(temp!=NULL)
        {
            if(temp->data.getCrimeType()==target)
            {
                temp->data.displayCriminal();
                found=true;
            }
            temp=temp->next;
        }
        if(!found)
        cout<<"NO CRIMINALS UNDER THIS CRIME!\n";
    }
    void delete_byName()
    {
        string target;
        cout<<"Enter name to delete: ";
        getline(cin, target);

        if(head==NULL)//target at start
        {
            cout<<"EMPTY\n";
            return;
        }
        if(head->data.getName()==target)
        {
            Node*todel=head;
            head=head->next;
            delete todel;
            cout<<"Deleted\n";
            return;
        }

        Node*cur=head;
        Node*pre=NULL;

        while(cur!=NULL && cur->data.getName()!=target)
        {
            pre=cur;
            cur=cur->next;
        }
        if(cur==NULL)
        {
            cout<<"Criminal not found\n";
        }
        else{
            pre->next=cur->next;
            delete cur;
            cout<<"DELETED\n";
        }
    }

    void showSpecificCrime(string crime) {
        cout << "\n--- Showing All " << crime << " Cases ---\n";
        Node* temp = head;
        bool found = false;
        while (temp != NULL) {
            // Basic string check
            if (temp->data.getCrimeType() == crime) {
                temp->data.displayCriminal();
                found = true;
            }
            temp = temp->next;
        }
        if (!found) cout << "No records found for " << crime << ".\n";
    }

    void updateCriminalRecord() {
        string target;
        cout << "Enter name of criminal to update: ";
        getline(cin, target);

        Node* temp = head;
        while (temp != NULL) {
            if (temp->data.getName() == target) {
                cout << "Record found! What do you want to update?\n";
                cout << "1. Crime Type\n2. Punishment Years\nOption: ";
                int choice;
                cin >> choice;
                cin.ignore(); // eat newline

                if (choice == 1) {
                    string newCrime;
                    cout << "Enter new crime type: ";
                    getline(cin, newCrime);
                    temp->data.setCrimeType(newCrime);
                } else if (choice == 2) {
                    int newYears;
                    cout << "Enter new punishment years: ";
                    cin >> newYears;
                    cin.ignore();
                    temp->data.setPunishment(newYears);
                }
                cout << "Record Updated.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Criminal not found.\n";
        system("pause");
    }
};




int main()
{
    h:
    PoliceRecordSystem sys;
    int choice;
    again:cout<<"POLICERECORDSYSTEM\n";
    cout << "1. Add Criminal\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Crime Type\n";
    cout << "4. Delete Criminal\n";
    cout << "5. Show Murder Cases\n";
    cout << "6. Show Theft Cases\n";
    cout << "7. Show All Criminals\n";
    cout << "8. Update Criminal Record\n";
    cout << "9. Exit\n";
    cout << "Enter Choice: ";
    cin >> choice;
    cin.ignore();

    switch(choice){
    case 1: sys.addCriminal(); break;
    case 2: sys.search_Criminal_byName(); break;
    case 3: sys.search_by_CrimeType(); break;
    case 4: sys.delete_byName(); break;
    case 5: sys.showSpecificCrime("Murder"); break;
    case 6: sys.showSpecificCrime("Theft"); break;
    case 7: sys.displayCriminals(); break;
    case 8: sys.updateCriminalRecord(); break;
    case 9: exit(0);
    default: cout<<"Invalid Option\n";
    goto again;
    }
    return 9;
}
