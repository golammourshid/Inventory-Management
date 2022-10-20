// Source File Header
// homework.cpp
// Md. Fahim Alam, CISP 400
// 16/10/21

#include<iostream>

using namespace std;

//This is the structure class of the inventory system.
class dataDictionary
{
public:
    int itemIdNumber;
    int quantityAtHand;

    //set added date
    int addedDay=9, addedMonth=9, addedYear=99;
    double wholesaleCost;
    double retailCost;
    dataDictionary* next;

    //Default Constructor
    dataDictionary()
    {
        next = NULL;
    }

    //creating function that Overload the stream extraction operator and give the output
    friend ostream &operator << (ostream &output, const dataDictionary &d)
    {
        output<<d.itemIdNumber<<"                  ";
        output<<d.quantityAtHand<<"                  ";
        output<<d.wholesaleCost<<"             ";
        output<<d.retailCost<<"            "<<d.addedDay<<"/"<<d.addedMonth<<"/"<<d.addedYear<<endl;
        return output;
    }

    //creating function that Overload the stream insertion operator and scan the input
    friend istream & operator >> (istream &input, dataDictionary &d)
    {
        while(1)
        {
            cout<<"\nEnter Item ID number"<<endl;
            input>>d.itemIdNumber;
            //Specification B4 - Inventory Entry Input Validation
            if(d.itemIdNumber>99999)
            {
                cout<<"\nItem ID should not greater than 5 digit! Please try again."<<endl;
            }
            else
            {
                break;
            }
        }
        while(1)
        {
            cout<<"\nEnter number of quantity"<<endl;
            input>>d.quantityAtHand;
            //Specification B4 - Inventory Entry Input Validation
            if(d.quantityAtHand<0)
            {
                cout<<"\nNumber of quantity can't be negative! Please try again."<<endl;
            }
            else
            {
                break;
            }
        }
        while(1)
        {
            cout<<"\nEnter wholesale Cost"<<endl;
            input>>d.wholesaleCost;
            //Specification B4 - Inventory Entry Input Validation
            if(d.wholesaleCost<0)
            {
                cout<<"\nWholesale Cost can't be negative! Please try again."<<endl;
            }
            else
            {
                break;
            }
        }

        //Automatically calculate 100% markup for retail cost
        d.retailCost = 2* d.wholesaleCost;
        return input;
    }
};

//Specification B1 - Date class
class Date
{
private:
    //Specification C2 - Dynamic Array of link list
    dataDictionary *head;

    //set due date
    int dueDay, dueMonth, dueYear;

    //set added date
    int addedDay, addedMonth, addedYear;

    //initialize variable for counting total item.
    int countItem=0;

public:
    //Default Constructor
    Date()
    {
        head = NULL;
    }

    //Function Prototype
    void ProgramGreeting();

    //Specification B2 - ComponentTest method in Date
    void Due_Date_is_valid()
    {
        if(dueDay == 16 && dueMonth == 10 && dueYear == 2022)
        {
            cout<<"\nDue date is fine!\n"<<endl;
        }
    }
    //Specification B2 - ComponentTest method in Date
    void Added_Date_is_valid()
    {
        if(addedDay == 9 && addedMonth == 9 && addedYear == 99)
        {
            cout<<"\nAdded date is also fine! Lets start.\n"<<endl;
        }
    }

    //Function Prototype
    void AlphaMenu();
    //Output Main Menu to console
    void setDate();
    //Calculating Date
    void addInventory();
    //Add new item to inventory at the last, selected from Main Menu
    void showInventory();
    //Displays current items in inventory
    void editInventory();
    //Update any item from inventory
    void deleteInventory();
    //Delete the last item from the inventory, decrease array by 1
};



int main ()
{
    //creating an Date type object
    Date date;

    //setting due date and adding date
    date.setDate();
    //Showing welcome message
    date.ProgramGreeting();

    //Specification A4 - UnitTest() method in main()
    date.Due_Date_is_valid();
    date.Added_Date_is_valid();

    //Showing the main menu
    date.AlphaMenu();
    return 0;
}

void  Date:: ProgramGreeting()
{
    cout<<"********************************************************************************\n                                 ProgramGreetings\n"<<endl;
    cout<<"********************************************************************************"<<endl;
    cout<<"Welcome to our inventory management system. ";
    cout<<"This system is designed for add new\ninventory, edit any inventory and also delete any inventory from the system.\n";
    cout<<"It also allow you to show all the item list any time."<<endl;
    cout<<"Author Name: Md. Fahim Alam"<<endl;
    cout<<"Assignment Due Date: ";
    if(dueMonth==10)
    {
        cout<<"October "<<dueDay<<", "<<dueYear<<endl;
    }//October 16, 2022"<<endl;
    cout<<"********************************************************************************\n                                 ProgramGreetings\n"<<endl;
    cout<<"********************************************************************************"<<endl;
    cout<<""<<endl;
}

void Date:: AlphaMenu()
{
    while(1)
    {
        cout<<"\nDo you want to go Main Menu? (y/n)"<<endl;
        //Variable to get user input
        char userInput;
        cin>>userInput;
        //checking user input
        if(userInput=='y' || userInput == 'Y')
        {
            //Specification C1 - Alpha Menu
            cout<<"\nMain Menu.\n------------------"<<endl;
            cout<<"<A>dd Inventory\n<D>elete Inventory\n<E>dit Inventory\n<S>how Inventory\n<Q>uit Program"<<endl;
            cin>>userInput;
            //Specification B3 - Menu Input Validation
            if(userInput == 'A' || userInput == 'a')
            {
                addInventory();
            }
            else if(userInput == 'S' || userInput == 's')
            {
                showInventory();
            }
            else if (userInput == 'Q' || userInput == 'q')
            {
                cout<<"\nThanks for visiting!.\n"<<endl;
                return;
            }
            else if (userInput == 'D' || userInput == 'd')
            {
                deleteInventory();
            }
            else if (userInput == 'E' || userInput == 'e')
            {
                editInventory();
            }
        }
        else if(userInput=='n' || userInput == 'N')
        {
            cout<<"\nThanks for visiting!.\n"<<endl;
            return;
        }
        else
        {
            cout<<"\nPlease enter valid input.\n"<<endl;
        }
    }

}

void Date:: addInventory()
{
    //increasing number of item by 1
    countItem++;

    //create the new node with data
    dataDictionary* newNode = new dataDictionary ();

    //Specification A3 - Overload operator >>
    cin>>*newNode;

    //Assigning to head
    if(head == NULL)
    {
        head = newNode;
        cout<<"\nSuccessfully added new item!!\n"<<endl;
        return;
    }

    //Traverse Till end of list
    dataDictionary* temp = head;
    while(temp->next != NULL)
    {
        //update temp
        temp = temp->next;
    }

    //Specification C3 - Resize Array - add to end
    temp->next = newNode;

    cout<<"\nSuccessfully added new item!!\n"<<endl;
}

void Date:: showInventory()
{
    dataDictionary* temp = head;

    //check if the list is empty
    if(head == NULL)
    {
        cout<<"\nInventory is Empty. Nothing to show.\n"<<endl;
        return;
    }

    //Column Name
    cout<<"\nItem Id Number | Quantity at Hand | Wholesale Cost | Retail Cost | Added Date"<<endl;

    //Traverse the List
    while(temp != NULL)
    {
        //Specification A2 - Overload operator <<
        cout<<*temp;
        temp = temp->next;
    }

}

void Date:: setDate()
{
    //set due date
    dueDay=16, dueMonth=10, dueYear=2022;

    //set added date
    addedDay=9, addedMonth=9, addedYear=99;
}

void Date:: editInventory()
{
    int itemID, i;

    //variable to check if the item is exist in the list
    bool checkID = false;

    //check if the list is empty
    if(head == NULL)
    {
        cout<<"\nInventory is Empty. Nothing to edit.\n"<<endl;
        return;
    }

    cout<<"\nEnter item ID to edit that inventory: ";
    cin>>itemID;
    dataDictionary *temp = head;

    //traverse the full list
    for(i=0;i<countItem;i++)
    {
        //checking if match the item ID
        if(temp->itemIdNumber == itemID)
        {
            checkID = true;
            int quantity,costWholesale;
            //Specification A1 - Edit Inventory
            while(1)
            {
                cout<<"\nEnter new Quantity for item ID: "<<itemID<<endl;
                cin>>quantity;
                //Specification B4 - Inventory Entry Input Validation
                if(quantity<0)
                {
                    cout<<"\nNumber of quantity can't be negative! Please try again."<<endl;
                }
                else
                {
                    break;
                }
            }
            while(1)
            {
                cout<<"\nEnter new Wholesale Cost for item ID: "<<itemID<<endl;
                cin>>costWholesale;
                //Specification B4 - Inventory Entry Input Validation
                if(costWholesale<0)
                {
                    cout<<"\nWholesale cost can't be negative! Please try again."<<endl;
                }
                else
                {
                    break;
                }
            }

            temp->quantityAtHand = quantity;
            temp->wholesaleCost = costWholesale;

            //Automatically calculate 100% markup for retail cost
            temp->retailCost = costWholesale*2.0;
            cout<<"\nSuccessfully updated item: "<<itemID<<endl;
            return;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(checkID == false)
    {
        cout<<"\nThis item ID is not exist in the inventory.";
    }
}
void Date:: deleteInventory()
{
    //check if the list is empty
    if(head == NULL)
    {
        cout<<"\nInventory is Empty. Nothing to delete."<<endl;
        return;
    }

    //Traverse Till end of list
    dataDictionary* temp = head;
    while(1)
    {
        //check whether the list have only one item
        if(temp->next == NULL)
        {
            head = head->next;
            break;
        }

        //check whether the list have more than one item
        if(temp->next->next == NULL)
        {
            break;
        }
        temp = temp->next;
    }
    //Specification C4 - Resize Array - subtract from end
    temp->next = NULL;

    cout<<"\nSuccessfully deleted last item."<<endl;
}
