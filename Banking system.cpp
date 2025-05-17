#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
bool checkCin(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Wrong input."<<endl;
        return false;
    }
    return true;
}
class BankAccount{
    private:
    string name;
    float balance{0};
    public:
    string password;
    int id;
    BankAccount(string n, string p, int i) : name(n), password(p), id(i){}
    void withdraw(){
        float amount;
        if(balance>0){
            do{
            cout<<"How much would you like to withdraw: "; cin>>amount;
            while(!checkCin()){
                cin>>amount;
            }}while(amount<0);
            if(amount>balance){
                cout<<"You don't have that much money."<<endl;
                cout<<endl;
                return;
            }
            balance-=amount;
            cout<<amount<<"$ has been withdrawn from your balance."<<endl;
        }
        else cout<<"Not enough balance."<<endl;
        cout<<endl;
    }
    void deposit(){
        float amount;
            do{
            cout<<"How much would you like to deposit: "; cin>>amount;
        while(!checkCin()){
            cin>>amount;
        }
        }while(amount<0);
            balance+=amount;
            cout<<amount<<"$ has been added to your balance."<<endl;
            cout<<endl;
    }
    void showBalance(){
        cout<<"Your full name is "<<name<<endl;
        cout<<"Your account's id is "<<id<<endl;
        cout<<"Your balance is "<<balance<<"$"<<endl;
        cout<<endl;
    }
};
class Bank{
    public:
    int curr_index{-1};
    std::vector<BankAccount> acc;
    void createAcc(){
        if(curr_index==-1){
        string name, passwd;
        int i=rand()%20+1;
        cout<<"Enter full name (exit to stop): "; cin.ignore(); getline(cin, name);
        if(name!="exit"){
            cout<<"Create password (exit to stop): "; cin>>passwd;
            if(passwd!="exit"){
                cout<<"Your account has been created succesfully."<<endl;
                acc.push_back(BankAccount(name,passwd,i));
                cout<<"Account data:\nFull name: "<<name<<"\nId: "<<i<<"\nPassword: "<<passwd<<endl;
            }
        }}
        else cout<<"You can't do this while you're logged in."<<endl;
        cout<<endl;
    }
    void depositCurrent(){
        if(curr_index==-1){
            cout<<"You must be logged in to deposit."<<endl;
            cout<<endl;
            return;
        }
        acc[curr_index].deposit();
    }
    void withdrawCurrent(){
        if(curr_index==-1){
            cout<<"You must be logged in to withdraw."<<endl;
            cout<<endl;
            return;
        }
        acc[curr_index].withdraw();
    }
    void showbalanceCurrent(){
        if(curr_index==-1){
            cout<<"You must be logged in to show balance."<<endl;
            cout<<endl;
            return;
        }
        acc[curr_index].showBalance();
    }
    void login(){
        bool found=false;
        if(curr_index==-1){
        int id;
        string passw;
        cout<<"Type account id you'd want to login: "; cin>>id;
        while(!checkCin()){
            cin>>id;
        }
        for(int i=0; i<acc.size();i++){
            if(acc[i].id==id){
                found=true;
                while(passw!="exit"){
                cout<<"Enter password(type exit to stop): "; cin>>passw;
                while(!checkCin()){
                    cin>>passw;
                }
                if(acc[i].password==passw){
                    cout<<"You succesfully logged in."<<endl;
                    curr_index=i;
                }
                else cout<<"Wrong password."<<endl;
                cout<<endl;
            }
            }
            if(!found) cout<<"Account not found."<<endl;
        }}
        else cout<<"You are already logged in."<<endl;
        cout<<endl;
    }
    void logout(){
        if (curr_index>-1){ 
            curr_index=-1;
            cout<<"You succesfully logged out."<<endl;
        }
        else cout<<"You can't logout."<<endl;
        cout<<endl;
    }
    void deleteAccount(){
        string input;
        string p="a";
        if(curr_index!=-1){
            while(p!="exit"){
            cout<<"Enter account's password: ";
            cin>>p;
            while(!checkCin()) cin>>p;
                if(p==acc[curr_index].password){
                    cout<<"Are you sure you want to do this? y/n"<<endl;
                    cin>>input;
                    if(input=="y"){
                        cout<<"You succesfully deleted your account."<<endl;
                        acc.erase(acc.begin()+curr_index);
                        curr_index=-1;
                        cout<<endl;
                        return;
                    }
                    else if(input=="n"){
                        cout<<"Operation terminated."<<endl;
                        cout<<endl;
                        return;
                    }
                    else{
                        cout<<"Isn't allowed input."<<endl;
                        cout<<endl;
                        return;
                    }
                }
                else{
                    cout<<"Invalid password."<<endl;
                    cout<<endl;
                }
            }
        }
        else cout<<"You aren't logged in."<<endl;
        cout<<endl;
    }
};
int main(){
    srand(time(NULL));
    int answer;
    Bank bank;
    while(answer!=8){
    cout<<"=======================SIMPLE BANKING SYSTEM======================="<<endl;
    cout<<"=============================1.Login==============================="<<endl;
    cout<<"=========================2.Create Account=========================="<<endl;
    cout<<"============================3.Deposit=============================="<<endl;
    cout<<"============================4.Withdraw============================="<<endl;
    cout<<"==========================5.Show Info=============================="<<endl;
    cout<<"============================6.Logout==============================="<<endl;
    cout<<"=========================7.Delete Account=========================="<<endl;
    cout<<"=============================8.Exit================================"<<endl;
    cin>>answer;
    while(!checkCin()){
        cin>>answer;
    }
    if(answer==1) bank.login();
    if(answer==2) bank.createAcc();
    if(answer==3) bank.depositCurrent();
    if(answer==4) bank.withdrawCurrent();
    if(answer==5) bank.showbalanceCurrent();
    if(answer==7) bank.deleteAccount();
    if(answer==6) bank.logout();
    }
}