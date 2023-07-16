#include "Query.h"
#include "NotQuery.h"
#include "BinaryQuery.h"


void runQuery(ifstream &file);

int main()
{
   /* void runQuery(ifstream &file); */

    ifstream file("file.txt");
    /* ifstream file("The_Holy_Bible.txt"); */


    runQuery(file);
    return 0;

}


ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() <<" times"<< endl;
    for (auto num:*(qr.lines))
    {
        os << "\t(line" << num + 1 << ") " << *(qr.file->begin() + num) << endl;
    }
    return os;
}

void runQuery(ifstream &file)
{
    TextQuery tq(file);
    while (true)
    {
        cout << "enter word to look for: ";
        string s1,s2,s3;
        cin>>s1>>s2>>s3;

        Query q0(s1);

        Query q=Query(s1)&Query(s2)|Query(s3);


        Query q1=~Query(s1);

        Query q2=Query(s1)|Query(s2);

        print(cout, q0.eval(tq)) << endl;

        print(cout, q.eval(tq)) << endl;

        print(cout, q1.eval(tq)) << endl;

        print(cout, q2.eval(tq)) << endl;
    }

}

