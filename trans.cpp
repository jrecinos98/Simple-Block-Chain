#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include "trans.h"


namespace trans_chain{
  Transaction::Transaction(double amount, std::string sender, std::string receiver, Transaction *next){
    this->amount= amount;
    this->sender=sender;
    this->receiver=receiver;
    this->next= next;
  
  }
  Transaction::~Transaction(){
  }
  std::string Transaction::generate_nonce(){
    srand(time(NULL));
    std::string temp="";
    while(true)
	  //Last char of temp is not valid
      {
	temp= char(rand()%26+97);
      }
      return temp;
    //check if nonce is valid.
  }
      

  std::string Transaction::getHash(){
  }

  std::ostream& operator << (std::ostream& out, const Transaction& t){
    out<<"Amount exchanged: $ "<< t.getAmount()<<"\n"
       <<"Sender: " + t.getSender()+ "\n"
       <<"Receiver: " + t.getReceiver() + "\n";
    return out;
  }



  
  
  Blockchain::Blockchain(){
    latest_trans= NULL;
  }
  void Blockchain::insert_transaction(const double amount, const std::string sender, const std::string receiver){
    if(latest_trans == NULL){
      latest_trans= new Transaction(amount, sender, receiver, NULL);
    }
    else{
      Transaction* temp = latest_trans;
      latest_trans= new Transaction(amount, sender, receiver, temp);
      delete temp;
    }
    
  }
  void Blockchain::find_transactions(const std::string sender) const{
    Transaction* temp= latest_trans;
    std::queue<trans_chain::Transaction*> sender_activity;
    while(temp != NULL){
      if(temp->getSender()== sender){
	sender_activity.push(temp);
	temp= temp->getPreviousTrans();
      }
      else
	temp= temp->getPreviousTrans();
    }
    if(sender_activity.size() == 0){
      std::cout<<"\nNo transactions under that name.\n";
    }
    while(sender_activity.size() != 0){
      std::cout<<std::endl
	       <<sender+"'s Transactions\n\n"
	       <<*sender_activity.front()<<std::endl; //The queue contains pointers. They have to be dereferenced
      sender_activity.pop();
    }
    delete temp;

  }
  bool Blockchain::verify_transactions() const{

  }

  
  void printOperations(){
    std::cout<<"\n1) Add a transaction to the chain.\n"
	     <<"2) Find a transaction with name of receiver or sender.\n"
	     <<"3) Verify and print the chain.\n"
	     <<"4) To exit.\n"<<std::endl;
  }
}
  
  
  
 
