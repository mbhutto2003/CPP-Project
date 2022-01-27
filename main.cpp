#include<iostream>
#include<fstream>
#include<windows.h>
#include<dos.h>
#include<stdio.h>
#include<cstdlib>
#include<string>
#include<conio.h>
#include<iomanip>
using namespace std;

COORD coord={0,0};


void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Overall Inventory Item
int items[1000][3] ;

// Order Inventory Item
int orderItems[100][4] ;

// Ordered Item Names to display on bill
string orderItemNames[100] ;

int itemIndex ;
int orderItemIndex ;

int isAdmin = 0 ;

void billPage();
void empJump();
void billJump();
void handleCust();
void goToStorePage();
void goToLoginPage();

class Login;
class Store;
class Order;
class Billing;
class Admin;



// Class Store

class Store
{
    public:
        int userChoice;
        int itemCode ;
        char itemName[200] ;
        int itemPrice    ;
        int itemQuantity ;

        void showManageItemsPage();
        void displayItems();
        int showItems();
        void addNewItem();
        void removeItem();
        void updateItem();
        void storePageSwitch();
        void storePage()
        {
            storePageSwitch();
        }
};

void Store::storePageSwitch()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    if(isAdmin == 1)
    {
        cout<<"     1. Manage Items"<<endl;
        cout<<"     2. Take Order"<<endl;
        cout<<"     3. View Sales Record"<<endl;
        cout<<"     4. Go Back"<<endl;
        cout<<"     5. Exit"<<endl<<endl;
        cout<<"     Please enter your choice: " ;
        cin>>userChoice;
        while(userChoice !=1 || userChoice !=2 || userChoice !=3 || userChoice !=4 || userChoice !=5)
        {
            switch(userChoice)
            {
                case 1:
                    showManageItemsPage();
                    break;
                case 2:
                    handleCust();
                    break;
                case 3:
                    billJump();
                    break;
                case 4:
                    empJump();
                    break ;
                case 5:
                    exit(0);
                    break;
                default:
                    cout<<endl<<"     Invalid choice. Please enter your choice: ";
                    cin>>userChoice;
            }
        }
    }
    else if (isAdmin == 0)
    {
        cout<<"     1. Manage Items"<<endl;
        cout<<"     2. Take Order"<<endl;
        cout<<"     3. View Sales Record"<<endl;
        cout<<"     4. Logout"<<endl;
        cout<<"     5. Exit"<<endl<<endl;
        cout<<"     Please enter your choice: " ;
        cin>>userChoice;
        while(userChoice !=1 || userChoice !=2 || userChoice !=3 || userChoice !=4 || userChoice !=5)
        {
            switch(userChoice)
            {
                case 1:
                    showManageItemsPage();
                    break;
                case 2:
                    handleCust();
                    break;
                case 3:
                    billJump();
                    break;
                case 4:
                    goToLoginPage();
                    break;
                case 5:
                    exit(0);
                    break ;
                default:
                    cout<<endl<<"     Invalid choice. Please enter your choice: ";
                    cin>>userChoice;
            }
        }
    }

}


void Store::showManageItemsPage()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    cout<<"     1. View Items  "<<endl;
    cout<<"     2. Add New Item      "<<endl;
    cout<<"     3. Update Item      "<<endl;
    cout<<"     4. Remove Item  "<<endl;
    cout<<"     5. Go Back                      "<<endl;
    cout<<"     6. Exit                         "<<endl<<endl;
    cout<<"     Please enter your choice: ";
    cin>>userChoice;
    while(userChoice !=1 || userChoice !=2 || userChoice !=3 || userChoice !=4 || userChoice !=5 || userChoice !=6)
    {
        switch (userChoice)
        {
            case 1:
                displayItems();
                break;
            case 2:
                addNewItem();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                removeItem();
                break;
            case 5:
                storePageSwitch();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<endl<<"     Invalid choice. Please enter your choice: ";
                cin>>userChoice;
        }
    }
}




// Add New Item
void Store::addNewItem()
{
    // Add unique code logic
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    ofstream newItem("items.txt",ios::app);
    cout<<"     Please enter item name: ";
    cin>>itemName;
    cin.sync();
    cout<<"     Please enter item code: ";
    cin>>itemCode;
    cout<<"     Please enter item price: ";
    cin>>itemPrice;
    cout<<"     Please enter item quantity: ";
    cin>>itemQuantity;
    newItem<<itemName<<' '<<itemCode<<' '<<itemPrice<<' '<<itemQuantity<<endl;
    newItem.close();
    cout<<endl<<"     Item added successfully. Please press any key to continue...";
    getch();
    showManageItemsPage();
}

void Store::displayItems()
{
    showItems();
    cout<<endl<<"     Please press any key to continue...";
    getch();
    showManageItemsPage();
}

int Store::showItems()
{   system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"---------------"<<endl<<endl;
    ifstream item("items.txt");
    cout<<"     --------------------------------"<<endl;
    cout<<"      Item - Code - Qty  - Price"<<endl;
    cout<<"     --------------------------------"<<endl;

    int itemsCount = 0 ;
    while (item>>itemName>>itemCode>>itemPrice>>itemQuantity)
    {
        itemsCount++ ;
        cout<<"     "<<itemName<<" - "<<itemCode<<" - "<<itemQuantity<<" - "<<itemPrice<<endl ;
    }
    item.close();
    if(itemsCount == 0)
    {
        cout<<"     ---------No Items Found---------"<<endl;
    }
    cout<<"     --------------------------------"<<endl;
    return itemsCount;
}

void Store::removeItem()
{
    int totalItems = showItems();
    int tCode;
    int isItemFound = 0 ;
    if(totalItems > 0)
    {
        do
        {

            cout<<"\n     Please enter the code of item to remove: ";
            cin>>tCode;
            ifstream readItems("items.txt");
            while (readItems>>itemName>>itemCode>>itemPrice>>itemQuantity)
            {
                if(tCode == itemCode )
                {
                    isItemFound = 1 ;
                    break ;
                }
            }

            readItems.close();
            if(isItemFound == 0)
            {
                cout<<endl<<"     Unable to find item.";
            }
        }
        while(isItemFound != 1);

        ifstream getItems("items.txt");
        ofstream tempItems("temp_items.txt");
        while (getItems>>itemName>>itemCode>>itemPrice>>itemQuantity)
        {
        if(tCode != itemCode)
            {
                tempItems<<itemName<<' '<<itemCode<<' '<<itemPrice<<' '<<itemQuantity<<endl ;
            }
        }

        getItems.close();
        tempItems.close();
        remove("items.txt");
        rename("temp_items.txt","items.txt");
        cout<<endl<<"     Item removed successfully. Please press any key to continue...";

    }
    else
    {
        cout<<endl<<"     No Item exists. Please press any key to continue...";
    }
    getch();
    showManageItemsPage();
}

void Store::updateItem()
{
    int totalItems = showItems();
    int tCode, tItemPrice, tItemQuantity;
    char tItemName[200];
    int isItemFound = 0 ;
    if(totalItems > 0)
    {
        do
        {

            cout<<"\n     Please enter the code of item to update: ";
            cin>>tCode;
            ifstream updateItems("items.txt");
            while (updateItems>>itemName>>itemCode>>itemPrice>>itemQuantity)
            {
                if(tCode == itemCode )
                {
                    isItemFound = 1 ;
                    cout<<"     Please enter new name of item: ";
                    cin>>tItemName;
                    cin.sync();
                    cout<<"     Please enter new price of item: ";
                    cin>>tItemPrice;
                    cout<<"     Please enter new quantity of item: ";
                    cin>>tItemQuantity;
                    break ;
                }
            }

            updateItems.close();
            if(isItemFound == 0)
            {
                cout<<endl<<"     Unable to find item.";
            }
        }
        while(isItemFound != 1);


        ifstream getItems("items.txt");
        ofstream tempItems("temp_items.txt");
        while (getItems>>itemName>>itemCode>>itemPrice>>itemQuantity)
        {
            if(tCode == itemCode)
            {
               tempItems<<tItemName<<' '<<tCode<<' '<<tItemPrice<<' '<<tItemQuantity<<endl ;
            }
            else
            {
                tempItems<<itemName<<' '<<itemCode<<' '<<itemPrice<<' '<<itemQuantity<<endl ;
            }
        }
        getItems.close();
        tempItems.close();
        remove("items.txt");
        rename("temp_items.txt","items.txt");
        cout<<endl<<"     Item updated successfully. Please press any key to continue...";

    }
    else
    {
        cout<<endl<<"     No Item exists. Please press any key to continue...";
    }
    getch();
    showManageItemsPage();

}

class Billing
{
    public:

        Store store;
        string customerName;
        int totalAmount ;
        char userDecision;

        int itemCode       ;
        char itemName[200] ;
        int itemPrice      ;
        int itemQuantity   ;
        int totalPrice     ;

        void viewStats();
        void adjustInventory();
        string getItemName(int);

        Billing()
        {
            customerName = "" ;
            totalAmount = 0 ;
        }

        void bill()
        {
            system("CLS");
            gotoxy(40,1);cout<<" Student Canteen";
            gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
            cout<<"     Please enter customer name: ";
            cin>>customerName;
            cout<<endl;

            system("CLS");
            gotoxy(40,1);cout<<" Student Canteen";
            gotoxy(40,2);cout<<"-----------------"<<endl<<endl;

            ifstream item("items.txt");
            while (item>>itemName>>itemCode>>itemPrice>>itemQuantity)
            {
             //   cout << itemName << "," << itemCode<<endl ;
                for(int i = 0; i<= orderItemIndex; i++ )
                {
              //      cout << orderItems[i][0] << "," << itemCode<<endl ;
                    if(orderItems[i][0] == itemCode)
                    {
              //        cout << orderItems[i][0] << "," << itemCode<<endl ;
                        orderItemNames[i] = itemName ;
                    }
                }
            }

            item.close();
            cout<<"     Customer Name : "<<customerName<<endl;
            cout<<"     ----------------------------------"<<endl;
            cout<<"     Code - Item - Qty - Price - Amount"<<endl;
            cout<<"     ----------------------------------"<<endl;

            int total = 0 ;
            for(int i = 0; i<= orderItemIndex; i++ )
            {
                cout <<"     " <<orderItems[i][0] <<"   " <<orderItemNames[i] <<"    " << orderItems[i][1] <<"    " << orderItems[i][2] <<"      " << orderItems[i][3]  <<endl ;
                total += orderItems[i][3]  ;
            }
            cout<<"     ----------------------------------"<<endl;
            cout<<"     Total:                     "<<"Rs."<<total<<endl;
            cout<<"     ----------------------------------"<<endl;
            cout<<"     Thank You"<<endl;
            fstream billmod("sales_record.txt",ios::app);
            for(int i = 0; i<= orderItemIndex; i++ )
            {
                billmod<<customerName<<" "<<orderItemNames[i]<<" "<<orderItems[i][2]<<" "<<orderItems[i][1]<<" "<<orderItems[i][3]<<endl;
            }
            billmod.close();

            adjustInventory();

            cout<<endl<<endl<<"     Please press any key to continue...";
            getch();
            goToStorePage();
        }
};

void Billing::adjustInventory()
{
    ifstream items("items.txt");
    ofstream temp_items("temp_items.txt");
    while(items>>itemName >> itemCode >> itemPrice >> itemQuantity)
    {
        for(int i = 0; i<= orderItemIndex; i++ )
        {
            if(orderItems[i][0] == itemCode)
            {

                itemQuantity -= orderItems[i][1] ;
            }
        }
        temp_items<<itemName<<" "<<itemCode<<" "<<itemPrice<<" "<<itemQuantity<<endl;
    }
    items.close();
    temp_items.close();
    remove ("items.txt");
    rename("temp_items.txt","items.txt");
}

void Billing::viewStats()
{
//  cout <<"     " <<orderItems[i][0] <<"    " <<orderItemNames[i] <<"    " << orderItems[i][1] <<"    " << orderItems[i][2] <<"      " << orderItems[i][3]  <<endl ;

    system("CLS");
    gotoxy(40,1);cout<<" Student Canteen";
    gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
    ifstream viewSales("sales_record.txt");


    totalAmount = 0 ;
    int orderNumber = 1 ;
    string oldCustomerName = "" ;
    int sales_record = 0 ;


    while(viewSales>>customerName>>itemName>>itemPrice>>itemQuantity>>totalPrice)
    {
        sales_record++ ;
        if(sales_record != 1)
        {
            if(oldCustomerName != customerName)
            {
                cout<<"     ----------------------------"<<endl;
                cout<<"     Total:             Rs.  "<< totalAmount <<endl ;
                cout<<"     ----------------------------"<<endl;

                totalAmount = 0;
                orderNumber++ ;

                cout<<"\n\n     --------"<<endl;
                cout<<"     Order# " << orderNumber<<endl;
                cout<<"     --------"<<endl;
                cout<<"     Customer: "<<customerName<<endl ;
                cout<<"     ----------------------------"<<endl;
                cout<<"     Item  - Price - Qty - Amount"<<endl;
                cout<<"     ----------------------------"<<endl;

            }
        }
        else if(sales_record == 1)
        {
                cout<<"     --------"<<endl;
                cout<<"     Order# " << orderNumber<<endl;
                cout<<"     --------"<<endl;
                cout<<"     Customer: "<<customerName<<endl ;
                cout<<"     ----------------------------"<<endl;
                cout<<"     Item  - Price - Qty - Amount"<<endl;
                cout<<"     ----------------------------"<<endl;
        }

        totalAmount += totalPrice ;

        cout<<"     "<<itemName<<" - "<<itemPrice<<"  -  " <<itemQuantity<<"  -   "<<totalPrice<<endl;

        oldCustomerName = customerName ;
    }

    if(sales_record != 0)
    {
        cout<<"     ----------------------------"<<endl;
        cout<<"     Total:             Rs.  "<< totalAmount <<endl ;
        cout<<"     ----------------------------"<<endl;
    }
    else
    {
        cout<<"     -----------------------------"<<endl;
        cout<<"     ----No sales record found----"<<endl;
        cout<<"     -----------------------------"<<endl;
    }


    viewSales.close();
    cout<<endl<<endl<<endl<<"     Please press any key to continue...";
    getch();

    store.storePage();
}

string Billing::getItemName(int itemCode)
{
    string itemName ;
    cout << itemCode ;
    for(int i=0; i <= itemIndex; i ++)
    {
        if(items[i][0] == itemCode)
        {
            itemName = items[i][1] ;
            cout << items[i][0] ;
            cout << itemName ;
            break ;
        }
    }
    return itemName ;
}


// Class Order
class Order
{
    public:
        Billing billing;

        char userDecision;
        int userChoice;

        int orderItemCode     ;
        string orderItemName  ;
        int orderItemQuantity ;
        int orderItemPrice    ;
        int orderItemAmount   ;

        void orderPageSwitch();

        int itemCode ;
        char itemName[200] ;
        int itemPrice    ;
        int itemQuantity ;

      //  void displayItems();
        int checkItemCode(int);
        int getItemPrice(int);
        int checkItemQuantity(int, int);
        int showItems();

        void orderPage()
        {
            int itemsCount = showItems();

            if(itemsCount > 0)
            {
                do
                {
                    // Get Order Item Code From User
                    int isValidItemCode = 0 ;
                    int isValidItemQuantity = 0 ;

                    do
                    {
                        cout<<"\n\n     Please enter valid item code to order: ";
                        cin>>orderItemCode;

                        isValidItemCode = checkItemCode(orderItemCode);
                    }
                    while(isValidItemCode != 1);


                    // Get Order Item Quantity From User

                    do
                    {
                        cout<<"     Please enter item quantity to order: ";
                        cin>>orderItemQuantity;

                        isValidItemQuantity = checkItemQuantity(orderItemCode, orderItemQuantity);
                    }
                    while(isValidItemQuantity != 1);

                    // Get Order Item Price From Item Array
                    int orderItemPrice = getItemPrice(orderItemCode);
                    orderItemIndex++ ;
                    orderItems[orderItemIndex][0] = orderItemCode     ;
                    orderItems[orderItemIndex][1] = orderItemQuantity ;
                    orderItems[orderItemIndex][2] = orderItemPrice    ;
                    orderItems[orderItemIndex][3] = orderItemQuantity * orderItemPrice ;

                    cout<<"     Order another item? [Y/y] ";

                    cin>>userDecision;

                }
                while(userDecision == 'Y' || userDecision == 'y');
    /*
                // Order Items Logs
                for(int i = 0; i <= orderItemIndex; i++)
                {
                    cout<< orderItems[i][0] <<"," << orderItems[i][1] <<"," << orderItems[i][2] <<"," << orderItems[i][3] <<endl ;
                    getch();
                }
    */
                billing.bill();
            }
            else
            {
                cout<<endl<<"     No items exists. Please press any key to continue...";
                getch();
                goToStorePage();
            }
        }
};

int Order::showItems()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    ifstream item("items.txt");
    cout<<"     -----------------------------------"<<endl;
    cout<<"     Code  -  Item  -  Price  - Quantity"<<endl;
    cout<<"     -----------------------------------"<<endl;
    itemIndex = -1;
    orderItemIndex = -1;
    int itemsCount = 0 ;
    while (item>>itemName>>itemCode>>itemPrice>>itemQuantity)
    {
        itemsCount++ ;
        itemIndex++ ;
        cout<<"     "<<itemCode<<"  -  "<<itemName<<"  -   "<<itemPrice<<"   -  "<<itemQuantity<<endl ;
        items[itemIndex][0] = itemCode ;
        items[itemIndex][1] = itemQuantity ;
        items[itemIndex][2] = itemPrice ;

    }
    item.close();
    if(itemsCount == 0)
    {
        cout<<"     -----------No Items Found----------"<<endl;
    }
        cout<<"     -----------------------------------"<<endl;
    return itemsCount;
}

int Order::checkItemCode(int itemCode)
{
    int isValidItemCode = 0 ;
    for(int i=0; i <= itemIndex; i ++)
    {
        if(items[i][0] == itemCode)
        {
            isValidItemCode = 1 ;
            break ;
        }

    }
    return isValidItemCode ;
}

int Order::checkItemQuantity(int itemCode, int itemQuantity)
{
    int isValidItemQuantity = 0 ;
    for(int i=0; i <= itemIndex; i ++)
    {
        if(items[i][0] == itemCode)
        {
            if(items[i][1] >= itemQuantity)
            {
                isValidItemQuantity = 1;
            }
            break ;
        }

    }
    return isValidItemQuantity ;
}

int Order::getItemPrice(int itemCode)
{
    int itemPrice = 0 ;
    for(int i=0; i <= itemIndex; i ++)
    {
        if(items[i][0] == itemCode)
        {
            itemPrice = items[i][2] ;
            break ;
        }
    }
    return itemPrice ;
}

class Admin
{
    public:

  //    void goToLoginPage();
        int userChoice ;
        int employeeCode ;
        char employeeName[50];
        int employeeAge ;
        long int employeeSalary;
        char userDecision;

        void showAdminEmployeesPage();
        void displayEmployees();
        void addNewEmployee();
        void updateEmployee();
        void removeEmployee();
        int  showEmployees();

        void adminPageSwitch();
        void adminEmployeesPageSwitch();
        void clearStats();
        void adminPage();
};

void Admin::adminPage()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    cout<<"     1. Manage Employees          "<<endl;
    cout<<"     2. Clear Sales Record        "<<endl;
    cout<<"     3. Store                     "<<endl;
    cout<<"     4. Logout                      "<<endl;
    cout<<"     5. Exit                      "<<endl<<endl;
    cout<<"     Please enter your choice: ";
    cin>>userChoice;
    adminPageSwitch();
}

void Admin::adminPageSwitch()
{
    while(userChoice !=1 || userChoice !=2|| userChoice != 3 || userChoice != 4 || userChoice != 5)
    {
        switch(userChoice)
        {
            case 1:
                showAdminEmployeesPage();
                break;

            case 2:
                clearStats();
                break;

            case 3:
                Store store;
                store.storePage();
                break;

            case 4:
                goToLoginPage();
                break;

            case 5:
                exit(0);
                break;

            default:
                cout<<endl<<"     Invalid choice. Please enter your choice: ";
                cin>>userChoice;
        }
    }
}

void Admin::clearStats()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    cout<<"     Clear Sales Record [Y/y]: ";
    cin>>userDecision;
    if(userDecision == 'Y' || userDecision == 'y')
    {
        remove("sales_record.txt");
        cout<<endl<<"     Sales records cleared successfully. Please press any key to continue...";
        getch();
        adminPage();
    }
    else
    {
        cout<<endl<<"     Unable to clear sales record. Please press any key to continue...";
        getch();
        adminPage();

    }
}

void Admin::showAdminEmployeesPage()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    cout<<"     1. View Employee Records  "<<endl;
    cout<<"     2. Add New Employee Record      "<<endl;
    cout<<"     3. Update Employee Record      "<<endl;
    cout<<"     4. Remove Employee Record  "<<endl;
    cout<<"     5. Go Back                      "<<endl;
    cout<<"     6. Exit                         "<<endl<<endl;
    cout<<"     Please enter your choice: ";
    cin>>userChoice;
    adminEmployeesPageSwitch();
}

void Admin::adminEmployeesPageSwitch()
{
    while(userChoice !=1 || userChoice !=2||userChoice != 3 ||userChoice != 4 || userChoice != 5 || userChoice != 6)
    {
        switch(userChoice)
        {
            case 1:
                displayEmployees();
                break;
            case 2:
                addNewEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                removeEmployee();
                break;
            case 5:
                adminPage();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<endl<<"     Invalid choice. Please enter your choice: ";
                cin>>userChoice;
        }
    }
}

void Admin::displayEmployees()
{
    int totalEmployees = showEmployees();
    cout<<endl<<endl<<"     Please press any key to continue...";
    getch();
    showAdminEmployeesPage();
}

int Admin::showEmployees()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    ifstream employee("employees.txt");
    cout<<"     -------------------------------"<<endl;
    cout<<"     Code - Employee - Age - Salary"<<endl;
    cout<<"     -------------------------------"<<endl;

    int total = 0 ;
    while (employee>>employeeCode>>employeeName>>employeeAge>>employeeSalary)
    {
        total++ ;
        cout<<"     "<<employeeCode<<" - "<<employeeName<<"  - "<<employeeAge<<"  - "<<employeeSalary<<endl ;
    }
    employee.close();

    if(total == 0)
    {
        cout<<"     -------No Employee Found-------"<<endl;
        cout<<"     -------------------------------"<<endl;
    }
    return total ;
}

void Admin::addNewEmployee()
{
    system("CLS");
    gotoxy(40,1);
    cout<<" Student Canteen";
    gotoxy(40,2);
    cout<<"-----------------"<<endl<<endl;
    ofstream newEmployee("employees.txt",ios::app);
    cout<<"     Please enter code of employee: ";
    cin>>employeeCode;
    cout<<"     Please enter name of employee: ";
    cin>>employeeName;
    cin.sync();
    cout<<"     Please enter age of employee: ";
    cin>>employeeAge;
    cout<<"     Please enter salary of employee: ";
    cin>>employeeSalary;
    newEmployee<<employeeCode<<' '<<employeeName<<' '<<employeeAge<<' '<<employeeSalary<<endl;
    newEmployee.close();
    cout<<endl<<"     Employee added successfully. Please press any key to continue...";
    getch();
    showAdminEmployeesPage();
}

void Admin::removeEmployee()
{
    int totalEmployees = showEmployees();
    int tCode;
    int isEmployeeFound = 0 ;
    if(totalEmployees > 0)
    {
        do
        {

            cout<<"\n     Please enter the code of employee to remove: ";
            cin>>tCode;
            ifstream readEmployees("employees.txt");
            while(readEmployees>>employeeCode>>employeeName>>employeeAge>>employeeSalary)
            {
                if(tCode == employeeCode )
                {
                    isEmployeeFound = 1 ;
                    break ;
                }
            }

            readEmployees.close();
            if(isEmployeeFound == 0)
            {
                cout<<endl<<"     Unable to find employee.";
            }
        }
        while(isEmployeeFound != 1);

        ifstream getEmployees("employees.txt");
        ofstream tempEmployees("temp_employees.txt");
        while(getEmployees>>employeeCode>>employeeName>>employeeAge>>employeeSalary)
        {
        if(tCode != employeeCode)
        {

            tempEmployees<<employeeCode<<' '<<employeeName<<' '<<employeeAge<<' '<<employeeSalary<<endl;
        }
        }

        getEmployees.close();
        tempEmployees.close();
        remove("employees.txt");
        rename("temp_employees.txt","employees.txt");
        cout<<endl<<"     Employee removed successfully. Please press any key to continue...";

    }
    else
    {
        cout<<endl<<"     No employee exists. Please press any key to continue...";
    }
    getch();
    showAdminEmployeesPage();
}

void Admin::updateEmployee()
{
    int totalEmployees = showEmployees();
    int tCode, tEmployeeAge, tEmployeeSalary;
    char tEmployeeName[200];
    int isEmployeeFound = 0 ;
    if(totalEmployees > 0)
    {
        do
        {

            cout<<"\n     Please enter the code of employee to update: ";
            cin>>tCode;
            ifstream readEmployees("employees.txt");
            while(readEmployees>>employeeCode>>employeeName>>employeeAge>>employeeSalary)
            {
                if(tCode == employeeCode )
                {
                    isEmployeeFound = 1 ;
                    cout<<"     Please enter new name of employee: ";
                    cin>>tEmployeeName;
                    cin.sync();
                    cout<<"     Please enter new age of employee: ";
                    cin>>tEmployeeAge;
                    cout<<"     Please enter new salary of employee: ";
                    cin>>tEmployeeSalary;
                    break ;
                }
            }

            readEmployees.close();
            if(isEmployeeFound == 0)
            {
                cout<<endl<<"     Unable to find employee.";
            }
        }
        while(isEmployeeFound != 1);


        ifstream getEmployees("employees.txt");
        ofstream tempEmployees("temp_employees.txt");
        while(getEmployees>>employeeCode>>employeeName>>employeeAge>>employeeSalary)

        {
            if(tCode == employeeCode)
            {
               tempEmployees<<tCode<<' '<<tEmployeeName<<' '<<tEmployeeAge<<' '<<tEmployeeSalary<<endl ;
            }
            else
            {
                tempEmployees<<employeeCode<<' '<<employeeName<<' '<<employeeAge<<' '<<employeeSalary<<endl ;
            }
        }
        getEmployees.close();
        tempEmployees.close();
        remove("employees.txt");
        rename("temp_employees.txt","employees.txt");
        cout<<endl<<"     Employee updated successfully. Please press any key to continue...";

    }
    else
    {
        cout<<endl<<"     No employee exists. Please press any key to continue...";
    }
    getch();
    showAdminEmployeesPage();

}

// Class Login
class Login
{
  public:
      string password = "";
      int userChoice;
      char passwordChar;
      void loginPageSwitch();
      void employeeLogin();
      void adminLogin();

      void showEmployeeScreen();
      void showAdminScreen();

      void loginPage()
      {
          system("CLS");
          gotoxy(40,1);
          cout<<" Welcome To Student Canteen";
          gotoxy(40,2);
          cout<<" --------------------------"<<endl<<endl;
          cout<<"     1. Admin Login"<<endl;
          cout<<"     2. Employee Login"<<endl;
          cout<<"     3. Exit"<<endl<<endl;
          cout<<"     Please enter your choice: ";
          cin>>userChoice;
          loginPageSwitch();
      }
};

void Login::loginPageSwitch()
{
    while(userChoice !=1 || userChoice != 2 || userChoice != 3)
    {
        switch(userChoice)
        {
            case 1:
                adminLogin();
                break;
            case 2:
                employeeLogin();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<endl<<"     Invalid choice. Please enter your choice: ";
                cin>>userChoice;
        }
    }
}

void Login::adminLogin()
{
    while(password!="MADJ@21")
    {
        password="";
        cout<<"     Please enter admin password: ";
        passwordChar = _getch();
        while(passwordChar != 13)
        {
            password.push_back(passwordChar);
            cout<<"*";
            passwordChar = getch();
        }
        if(password == "admin")
         {
             cout<<endl<<"     Access granted! Please press any key to continue...";
             getch();
             showAdminScreen();
         }
        else
        {
            cout<<endl<<"     Invalid Password."<<endl;
        }
    }
}

void Login::employeeLogin()
{
    while(password != "employee")
    {
        password="";
        cout<<"     Please enter employee password: ";
        passwordChar = _getch();
        while(passwordChar != 13)
        {
            password.push_back(passwordChar);
            cout<<"*";
            passwordChar = getch();
        }
        if(password == "employee")
        {
            cout<<endl<<"     Access granted! Please press any key to continue...";
            getch();
            showEmployeeScreen();
        }
        else
        {
            cout<<endl<<"     Invalid Password!"<<endl;
        }
    }
}

void Login::showEmployeeScreen()
{
    isAdmin = 0 ;
    Store store;
    store.storePage();
}

void Login::showAdminScreen()
{
    isAdmin = 1 ;
    Admin admin;
    admin.adminPage();
}



void handleCust()
{
    Order order;
    order.orderPage();
}
void billJump()
{
    Billing billing;
    billing.viewStats();
}

void empJump()
{
    Admin admin;
    admin.adminPage();
}

void goToLoginPage()
{
    Login login;
    login.loginPage();
}

void goToStorePage()
{
    Store store;
    store.storePage();
}

void welcome()
{
   system("color 71");
   gotoxy(4,3);
   cout<<"-------------------------"<<endl;
   gotoxy(18,6);
   cout<<"CANTEEN MANAGEMENT SYSTEM"<<endl;
   gotoxy(32,9);
   cout<<"-------------------------"<<endl;
   gotoxy(46,12);
   cout<<"WELCOME TO STUDENT CANTEEN"<<endl;
   gotoxy(60,15);
   cout<<"-------------------------"<<endl;
   gotoxy(74,18);
   cout<<"LETS MANAGE YOUR CANTEEN ";
   gotoxy(88,21);
   cout<<"-------------------------"<<endl;
   cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
   getch();
}

int main()
{   system("title Canteen Management System");
    welcome();
    system("color 71");
    goToLoginPage();
    return 0;
}


