#include <iostream>
#include <string>
#include "trans.h"

int main(int argc, char* arg[]){
  trans_chain::Blockchain* Transactions= new trans_chain::Blockchain();
  // trans_chain::Transaction T;
  //std::cout<<T.getAmount();
  int input=-1;
  // bool valid_op=false;
  std::cout<<"\nWelcome to the transaction-chain application...";
  while(input!=4){
    trans_chain::printOperations();
    std::cout<<"Which operation do you want to make?\n";
    std::cin>> input;
    while(input>4 || input <= 0){
      std::cout<<"Wrong operation! Please select only valid options:\n";
      trans_chain::printOperations();
      std::cin>> input;
    }
  
    switch(input){
      case 1:
        {
  	double amount=0;
  	std::string sender="";
  	std::string receiver="";
  	std::cout<<"\nInput the amount\n$";
  	std::cin>>amount;
  	std::cout<<"What is the name of the sender?\n";
  	std::cin>>sender;
  	std::cout<<"What is the name of the receiver?\n";
  	std::cin>>receiver;
  	Transactions->insert_transaction(amount, sender, receiver);
  	break;
        }
      case 2:
        {
  	int input;
  	std::string name;
  	if(Transactions->getLatestTrans() == NULL){
  	  std::cout<<"\nNo transactions have been recorded yet\n"<<std::endl;
  	  break;
  	}

  	std::cout<<"Enter the sender's name\n";
  	std::cin>>name;
  	Transactions->find_transactions(name);

  	break;
        }
      case 3:
        bool valid= Transactions->verify_transactions();
        std::cout<<valid<<std::endl;
        break;
      }
  }
}

