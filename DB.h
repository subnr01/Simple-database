//
// Created by wwjk2 on 2016/2/3.
//

#ifndef DATABASE_DB_H
#define DATABASE_DB_H
#include <unordered_map>
#include <iostream>
using namespace std;
class Database{
private:
    //using two hashmaps, One is used to record data, the other is to count for the same value.
    unordered_map<string,int> db;
    unordered_map<int,int> counter;
public:
    Database(){}
    void set(const string &variable,const int &value){
        if (db.find(variable)!=db.end()) {
            counter[db[variable]]--;
            }


            db[variable]=value;
            counter[value]++;

    }
    int get(const string &variable){
        if (db.find(variable)==db.end()) return INT_MIN;
        else return db[variable];
    }
    void unset(const string &variable){
        if (db.find(variable)==db.end()) cerr<<"NULL"<<endl;
        else {
            counter[db[variable]]--;
            db.erase(variable);
        }
    }
    int num_equal(const int &value){
        if (counter.find(value)==counter.end()) return 0;
        else return counter[value];
    }

};
//Define a new class block to record the original data value before changing it
class Block{
private:
    unordered_map<string,int> history;
    int moves;// record for transaction
public:
    Block(){moves=0;}
    ~Block(){history.clear();}
    void set(const string &var,const int &val ){
        history[var]=val;
        moves++;
    }
    bool operation(){//check whether there are transactions done
        return moves>0;
    }
    void transact(){
        moves++;
    }
    void undo(Database &db){//recover the original data value.
        unordered_map<string,int>::iterator it;
        for (it=history.begin();it!=history.end();it++){
            if (it->second==INT_MIN)
                db.unset(it->first);
            else
            db.set(it->first,it->second);
        }
    }

};
#endif //DATABASE_DB_H
