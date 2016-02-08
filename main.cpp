#include <iostream>
#include <stack>
#include "DB.h"
#include <fstream>
using namespace std;

int main(int argc,char *argv[]) {
   Database db;
    string command;
    string var;
    int val;
    stack<Block> st;//using a stack for blocks
    ifstream file;
    if (argc!=0) {//if there is a text file loaded
        file=ifstream(argv[1]);
    }

    do{
        if (file>>command){}//read from text file otherwise waiting for typing
    else cin>>command;
    if  (command=="SET"){
        if (file>>var>>val){}
        else
            cin>>var>>val;
        if (!st.empty()){


            st.top().set(var,db.get(var));//record original value before change it

        }
            db.set(var,val);

    }
    else if (command=="GET"){
        if (file>>var){}
        else
        cin>>var;
        if (!st.empty()){


            st.top().transact();

        }
        int out=db.get(var);
        if (out!=INT_MIN)
            cout<<out<<endl;
        else cout<<"NULL"<<endl;
    }
    else if (command=="UNSET"){
        if (file>>var){}
        else
            cin>>var;
        if (!st.empty()){


            st.top().set(var,db.get(var));

        }
        db.unset(var);
    }
    else if (command=="NUMEQUALTO"){
        if (file>>var){}
        else
            cin>>var;
        if (!st.empty()){


            st.top().transact();

        }
        cout<<db.num_equal(val)<<endl;
    }
        else if (command=="BEGIN"){

        st.push(Block());
    }
        else if (command=="ROLLBACK"){

        if (st.empty()){

        cout<<"NO TRANSACTION"<<endl;
            continue;}
            else if (!st.top().operation())
            cout<<"NO TRANSACTION"<<endl;
        else {
            st.top().undo(db);

        }
        st.pop();
    }
        else if (command=="COMMIT"){
        bool operation=false;
        while (!st.empty()){
            if (st.top().operation())
            {operation=true;
                break;}
            else st.pop();
        }
        while (!st.empty()) st.pop();
        if (!operation) cout<<"NO TRANSACTION"<<endl;
    }
        else if (command=="END") {
        file.close();
        exit(0);
    }

        else{
        cout<<"WRONG COMMAND"<<endl;
    }
    }while (1);


}