/*  Name    :   Vutlhari Doctor
    Surname :   Mashimbyi
    Course  :   Software Desing 1
    Practical
    Purpose :   Build an ATM Clone  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define SIZE_a 8 //A size for arrays
#define M1 25 //the length of profile string


int validateAcc(int*,int*,int [],int []);//This function validates Account and Pin
int Deposit(int,int []);
int printSlip(int,int [],int [],char [][25]);
int printSlip2(int,int [],int [],char [][25]);
int printSlip3(int,int [],int [],char [][25]);
int getName(int ,int [][M1]);
int Withdraw(int,int []);
int validateAcc2(int []);
void getAmount();
//Global variables...

int amount;
int AccountTrans;

int main(void)
{
        int sec=5;
        int AccountNo[SIZE_a];
        int PinCode[SIZE_a];
        char Profile[SIZE_a][M1];
        int Balance[SIZE_a];
        unsigned int fcount=0;
         int Account, Pin;
        int * pAccount = &Account;
        int * pPin = &Pin;
        int Acc,PinC,Bal;
        char Titt[3];
        char Ini[3];
        char Name[25];
        int k=0;
        int no=0;
        int choice, ch1,ch2,ch3,ch4;
    /*Data Base file Structure
        AccountNO Pin Tittle Initials Surname Balance */
         printf("Welcome!!!\n\n");
        FILE *dataBase;
        dataBase = fopen("database.txt","r"); //Open database file
        if(dataBase==NULL){
            puts("Unable to open the file");
        }else{
            while(!feof(dataBase)){ //Scan data from database file and store to arrays
                fscanf(dataBase,"%i %i %i\n",&Acc,&PinC,&Bal);
                fgets(Profile[fcount],M1,dataBase);
                AccountNo[fcount]=Acc;
                PinCode[fcount]=PinC;
                Profile[fcount][strlen(Profile[fcount])-1]='\0'; //To copy the string into Profile array
                Balance[fcount] =Bal;
               // printf("%i %i %i %s",AccountNo[fcount],PinCode[fcount],Balance[fcount],Profile[fcount]);
                fcount++;
            }

            //          Log in Section

    for(unsigned int i=1;i<=3;i++){
         printf("Enter Account Number :\n");
        scanf("%i",pAccount);
        printf("Enter your Pin :\n");
        scanf("%i",pPin);
        int index =validateAcc(pAccount, pPin,AccountNo,PinCode); //Get the index
        if(index!=-1){
            system("cls");
                //print the user profile
            printf("\nAccount Holder\t\t: %s ",Profile[index]);
            printf("\nYour Balance is\t\t: R %i\n", Balance[index]);

                //Display the menu
                do{ amount =0; //Set the amount to 0 for every cycle
                    printf("Select from the menu\n\n");
                    printf("1. Deposit\n2. Withdraw\n3. Transfer\n0. Exit\n");
                    scanf("%i",&choice);

                    switch(choice){
                    case 1:
                        system("cls");
                         printf("\nBalance : R %i\n\n",Balance[index]);
                         getAmount();
                        if(amount!=0){
                            Balance[index]=Deposit(index,Balance);  //Update user balance
                            printf("Your new balance is : R %i\n",Balance[index]);

                            printf("\nWould you like to print your receipt?\n1. Yes\n2. No\n");
                            scanf("%i",&ch2);
                                if(ch2==1){
                                    char name[25];
                                       // strcpy(name, Profile[i]);
                                    printSlip(index,AccountNo,Balance,Profile);
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }else{
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }
                        }
                        break;

                    case 2:
                          system("cls");
                            printf("\nBalance : R %i\n\n",Balance[index]);
                           getAmount();
                           /*   printf("Select Amount\n1. R 100\n2. R R500\n3. R 750\n4. R1000\n5. R 2500\n6. Own amount\n0. Cancel\n");

                        scanf("%i",&ch1);
                        if(ch1==1){
                            amount=100;
                        }else if(ch1==2){
                            amount =500;
                        }else if(ch1==3){
                            amount=750;
                        }else if(ch1==4){
                            amount=1000;
                        }else if(ch1==5){
                            amount=2500;
                        }
                        else if(ch1==6){
                            printf("Enter Your amount : R ");
                            scanf("%i",&amount);
                        }else{
                            system("cls");
                        }*/
                        if(amount!=0&&Withdraw(index,Balance)!=0){
                        Balance[index]=Withdraw(index,Balance); //Stores the new Balance
                        printf("\nNew Balance : R %i",Balance[index]);
                           printf("\nWould you like to print your receipt?\n1. Yes\n2. No\n");
                            scanf("%i",&ch2);
                                if(ch2==1){
                                    printSlip2(index,AccountNo,Balance,Profile);
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }else{
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }

                        }
                        break;

                    case 3:
                            system("cls");
                            int index2;   //To reference 2nd user
                            printf("Enter Account NO. ");
                            scanf("%i",&AccountTrans);
                           index2= validateAcc2(AccountNo);

                           if(index2!=-1&&index2!=index){ //Check if the user did not enter thier own account number
                           Balance[index]=Withdraw(index,Balance); //Check if the user has enough funds
                                if(Balance[index]!=0){
                          printf("\nBalance : R %i\n\n",Balance[index]);
                           int bal =Balance[index];
                           getAmount();
                        if(amount!=0&&amount<bal){
                        printf("Are you sure you want to send money to %s ?",Profile[index2]);
                        printf("\n1. Yes\n2. No\n");
                        scanf("%i",&ch3);
                        if(ch3==1){ //Allow the user to confirm before processing transaction
                            Balance[index]=Withdraw(index,Balance); //Stores the new Balance
                           Balance[index2]=Balance[index2]+amount;   //Update balance for the reciever
                           printf("\nNew Balance : R %i",Balance[index]);
                           printf("\nWould you like to print your reciept?\n1. Yes\n2. No\n");
                            scanf("%i",&ch2);
                                if(ch2==1){
                                    printSlip3(index,AccountNo,Balance,Profile);
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }else{
                                    printf("Transaction Successful!!\n");
                                    system("pause");
                                    system("cls");
                                }
                                        }else{
                                            system("cls");
                                        }

                                        }else {
                                                printf("\nYou do not have enough funds to complete transaction\n");
                                                system("pause");
                                                system("cls");
                                           }
                        }
                           }else if(index2==-1){
                                system("pause");
                                system("cls");
                           } else if(index2 ==index){
                                printf("\nYou cannot transfer money to your own account\n");
                                system("pause");
                                system("cls");
                           }
                        break;

                    case 0:
                        printf("The program is closing in 2 seconds");
                        sleep(2);
                        break;

                    default:
                        printf("\nInvalid Input!!");
                        system("pause");
                        system("cls");
                    }
                            //Update Database


                        FILE * upData;
                        upData=fopen("upData.txt","w");
                        if(upData==NULL){
                            printf("\nCould not Update Database\n");
                        }else{
                            for(unsigned int j=0;j<SIZE_a;j++){
                                fprintf(upData,"%i %i %i\n",AccountNo[j],PinCode[j],Balance[j]);
                                fprintf(upData,"%s\n",Profile[j]);
                            }
                        }
                        fflush(upData);
                        fclose(upData);

                }while(choice!=0);

            break; //Break out of the loop
        }else if(index==-1){
            printf("\nYou have %i attempts left\n",3-i);
            system("pause");
            system("cls");
            if(i==3){
            printf("\nYou have you used all your attempts, wait for 5 seconds and try again\n");

           do{          //Make the user to wait for 5 secondsafter using all attempts
            printf("%i\n",sec);
            sleep(1);  //delay for 1 second
            sec--;
            }while(sec!=0);
            i=1;        //resert the number of attempts
            sec=5;
             system("pause");
             system("cls");
        }
            continue;
        }

    }
        }
    fclose(dataBase);
    return (0);
}


//For Deposit

int Deposit(int i,int *arrBal){
    int newBalance=arrBal[i]+amount;
    return newBalance;
}
int printSlip(int i,int *AccNO,int * Bal,char Name[i][M1]){
        char *name;
        int account=AccNO[i];
        int balance=Bal[i];
//        Name[SIZE_a][M1];
//         Name[i][strlen(Name[i])-1]='\0';
        name=Name[i];

        SYSTEMTIME t;
        GetLocalTime(&t);   //Get system date and time

        FILE *fPtr;

        fPtr= fopen("Slip.txt","w");    //Create a file
        if(fPtr==NULL){
            printf("Could not create file");
        }else{
            fprintf(fPtr,"%s %s","Cash","Deposit\n\n");
            fprintf(fPtr,"%s\t %d%c%d%c%d","Date:",t.wDay,'/',t.wMonth,'/',t.wYear);
            fprintf(fPtr,"\n%s\t %d%c%d","Time:",t.wHour,':',t.wMinute);
            fprintf(fPtr,"\n\n%s\t %s ","Account Holder:",name);
 //          int results = fputs(Name, fPtr);
//            fwrite(name, sizeof(char), sizeof(name), fPtr);
            fprintf(fPtr,"\n%s\t %i","Account:",account);
            fprintf(fPtr,"\n%s\t%s %i","Payment:","+R",amount);
            fprintf(fPtr,"\n%s\t %c %i","Balance:",'R',balance);
            fprintf(fPtr,"\n\n%s %s","****************Thank","You*************************");
        }
        fflush(fPtr);
        fclose(fPtr);
}
int getName(int i,int Name[][M1]){

    return Name[i];
}

// For Withdrawal

int Withdraw(int i,int *Bal){
    int newBal;
    if(Bal[i]<amount){  //Check if the user have enough money
        printf("\nYou do not have enough funds to complete transaction\n");
        system("pause");system("cls");
        return 0;
    }else{
        newBal=Bal[i]-amount;

        return newBal; //Return new Balance
    }
}

int printSlip2(int i,int *AccNO,int * Bal,char Name[i][M1]){
        int account=AccNO[i];
        int balance=Bal[i];
        char *name;
        name=Name[i];
        //strcpy(name, getName(i,Name));
        SYSTEMTIME t;
        GetLocalTime(&t);   //Get system date and time

        FILE *fPtr;

        fPtr= fopen("Slip.txt","w");    //Create a file
        if(fPtr==NULL){
            printf("Could not create file");
        }else{
            fprintf(fPtr,"%s %s","Cash","Withdrawal\n\n");
            fprintf(fPtr,"%s\t %d%c%d%c%d","Date:",t.wDay,'/',t.wMonth,'/',t.wYear);
            fprintf(fPtr,"\n%s\t %d%c%d","Time:",t.wHour,':',t.wMinute);
            fprintf(fPtr,"\n%s\t %s","Account Holder:",name);
            fprintf(fPtr,"\n%s\t %i","Account:",account);
            fprintf(fPtr,"\n%s\t\t%s %i","Amount:","-R",amount);
            fprintf(fPtr,"\n%s\t %c %i","Balance:",'R',balance);
            fprintf(fPtr,"\n\n%s %s","****************Thank","You*************************");
        }
        fflush(fPtr);
        fclose(fPtr);
}

//Transfer

int validateAcc2(int *Acc){
    Acc[SIZE_a];
        for(int i=0; i<SIZE_a+1; i++){
        if(AccountTrans == Acc[i]){ //Check if AccNo is found
            return i; //return the index
            break;
        }
        else if(i==SIZE_a){    //If the account number is not in out database
            printf("\nAccount number not fount\n");
            return -1;
        }
    }
}

int printSlip3(int i,int *AccNO,int * Bal,char Name[i][M1]){
        int account=AccNO[i];
        int balance=Bal[i];
        char *name;
        name=Name[i];
        SYSTEMTIME t;
        GetLocalTime(&t);   //Get system date and time

        FILE *fPtr;

        fPtr= fopen("Slip.txt","w");    //Create a file
        if(fPtr==NULL){
            printf("Could not create file");
        }else{
            fprintf(fPtr,"%s %s","Cash","Transfer\n\n");
            fprintf(fPtr,"%s\t %d%c%d%c%d","Date:",t.wDay,'/',t.wMonth,'/',t.wYear);
            fprintf(fPtr,"\n%s\t %d%c%d","Time:",t.wHour,':',t.wMinute);
            fprintf(fPtr,"\n%s\t %s","Account Holder:",name);
            fprintf(fPtr,"\n%s\t %i","Account:",account);
            fprintf(fPtr,"\n%s\t\t%s %i","Amount:","-R",amount);
            fprintf(fPtr,"\n%s\t %c %i","Balance:",'R',balance);
            fprintf(fPtr,"\n\n%s %s","****************Thank","You*************************");
        }
        fflush(fPtr);
        fclose(fPtr);
}

void getAmount(){
                        int ch1;
                        printf("Select Amount\n1. R 100\n2. R 500\n3. R 750\n4. R1000\n5. R 2500\n6. Own amount\n0. Cancel\n");
                        scanf("%i",&ch1);
                        if(ch1==1){
                            amount=100;
                        }else if(ch1==2){
                            amount =500;
                        }else if(ch1==3){
                            amount=750;
                        }else if(ch1==4){
                            amount=1000;
                        }else if(ch1==5){
                            amount=2500;
                        }
                        else if(ch1==6){
                            printf("Enter Your amount : R ");
                            scanf("%i",&amount);
                        }else{
                            system("cls");
                        }
}
int validateAcc(int *Acc,int* pin,int*AccountNo,int*PinCode){
    AccountNo[SIZE_a];
    PinCode[SIZE_a];
    for(int i=0; i<SIZE_a+1; i++){
        if(*Acc == AccountNo[i] && *pin==PinCode[i]){ //Check if AccNo and pin match
            return i; //return the index
            break;
        }else if(*Acc==AccountNo[i] && *pin!=PinCode[i]){
            printf("\nInvalid Pin\n");
             return -1; //Return 1 if Acc and pin does not match
        }
        else if(i==SIZE_a){    //If the account number is not in out database
            printf("\nAccount number not found\n");
            return -1;
        }
    }
}
