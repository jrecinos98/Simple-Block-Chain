#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include "trans.h"
#include "picosha2.h"


namespace trans_chain{
  Transaction::Transaction(double amount, 
                          std::string sender, 
                          std::string receiver, 
                          Transaction *next, 
                          std::string hash)
  {
    this->amount= amount;
    this->sender=sender;
    this->receiver=receiver;
    this->next= next;
    this->hash= hash;
    this-> updateNonce();
  }
  Transaction::~Transaction(){
  }
  void Transaction::updateNonce(int seed){
    srand(time(NULL)+ seed);
    nonce="";
    for(int i=0; i<5; i++){
      int randNum= (rand())%26;
      nonce+= char(randNum+97)+ char(randNum*2);
    }
  }
      

  std::string Transaction::generateNextHash(){
    std::string next_hash="";
    int counter=0;
    std::string og_src= getStringAmount()+sender+receiver+nonce;
    next_hash= picosha2::hash256_hex_string(og_src);
    while(!isFormatValid(next_hash)){
      updateNonce(counter);
      next_hash= picosha2::hash256_hex_string(getStringAmount()+ sender+receiver+ nonce);
      counter++;
    }
    return next_hash;
  }

  std::ostream& operator << (std::ostream& out, const Transaction& t){
    out<<"  Sender  : " + t.getSender()+ "\n"
       <<"  Receiver: " + t.getReceiver() + "\n"
       <<"  Amount  : $"<< t.getAmount()<<"\n"
       <<"  Hash    : "<<t.getHash()<<"\n";
    return out;
  }

  
  
  Blockchain::Blockchain(){
    latest_trans= NULL;
    next_hash= "NULL";
  }

  void Blockchain::updateNextHash(){
    next_hash= latest_trans->generateNextHash();
  }

  void Blockchain::insert_transaction(const double amount, const std::string sender, const std::string receiver){
    if(latest_trans == NULL){
      latest_trans= new Transaction(amount, sender, receiver, NULL, this-> next_hash);
    }
    else{
      Transaction* temp = latest_trans;
      latest_trans= new Transaction(amount, sender, receiver, temp, this-> next_hash);

    }
    updateNextHash();
    std::cout<<"\nTRANSACTION RECORDED SUCCESSFULLY.\n";
    
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
      std::cout<<"\nNO TRANSACTIONS UNDER THAT NAME.\n";
      return;
    }
    std::cout<<std::endl<<sender+"'s Transactions:\n__________________________________________________________\n";
    while(sender_activity.size() != 0){
      std::cout<<std::endl
	       <<*sender_activity.front()<<std::endl; //The queue contains pointers. They have to be dereferenced
      sender_activity.pop();
      if(sender_activity.size() != 0){
        std::cout<<"        |\n        |\n       \\|/\n        |\n\n";
      }
    }

  }
  bool Blockchain::verify_transactions() const{
    Transaction* temp= latest_trans;
    while(temp != NULL){
      if(temp->getPreviousTrans() != NULL){
        if(!isHashValid(temp)){

          std::cout<<"\n AN INVALID TRANSACTION HAS BEEN FOUND: \n"<<*temp<<std::endl;
          std::cout<<*temp->getPreviousTrans()<<std::endl;
          return false;
        }}
      temp= temp->getPreviousTrans();
    }
    temp= latest_trans;
    std::cout<< "\nALL TRANSACTIONS ARE VALID.\n\n";
    while(temp!= NULL){
      std::cout<<*temp<<std::endl;
      temp= temp->getPreviousTrans();
      if(temp != NULL){
        std::cout<<"        |\n        |\n       \\|/\n        |\n\n";
      }
    }
    return true;

  }

  
  void printOperations(){
    std::cout<<"\n__________________________________________________________\n";

    std::cout<<"\n1) Add a transaction to the chain.\n"
	     <<"2) Find a transaction with name of receiver or sender.\n"
	     <<"3) Verify and print the chain.\n"
	     <<"4) To exit.\n"<<std::endl;
       std::cout<<"\nWhich operation do you want to make?\n\n";
  }

  bool isFormatValid(std::string hash){
    char last_char = hash.at(hash.length()-1)-'0';
    return last_char <= 4 && last_char >= 0;


  }

  bool isHashValid(Transaction* t){
    return t->getHash() == t->getPreviousTrans()->generateNextHash();
  }
}
  
  
  
 
