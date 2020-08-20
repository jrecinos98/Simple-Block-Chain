#ifndef TRANS_H
#define TRANS_H
#include <string>
#include <sstream>
#include <iostream>


namespace trans_chain{
  class Transaction{
  public:
  
    Transaction(double amount=0,
		            std::string sender="", 
                std::string receiver="", 
                Transaction * next= NULL, 
                std::string hash="NULL");
    ~Transaction();
    //Not sure if this should be here. Need to understand better how hash is supposed to be assigned
    std::string generateNextHash();

    Transaction* getPreviousTrans(){return next;}
    std::string getSender() const {return sender;}
    std::string getReceiver() const {return receiver;}
    std::string getHash()const {return hash;}
    double getAmount() const {return amount;}
    std::string getStringAmount() const {
      std::ostringstream strs;
      strs<<amount;
      std::string amount= strs.str();
      return amount;
    }

  private:
    void updateNonce(int seed=0);
    Transaction * next;
    double amount;
    std::string sender;
    std::string receiver;
    std::string nonce;
    std::string hash;
  };

  std::ostream& operator << (std::ostream& out, const Transaction& t);
  void printOperations();
  bool isHashValid(Transaction* t);
  bool isFormatValid(std::string hash);
 

  class Blockchain{
  public:
    Blockchain();
    Transaction * getLatestTrans() const {return latest_trans;}
    void insert_transaction(const double amount, const std::string sender, const std::string receiver);
    void find_transactions(const std::string sender)const;
    bool verify_transactions() const;
  private:
    void updateNextHash();
    Transaction * latest_trans;  
    std::string next_hash;  
  };


}

#endif
