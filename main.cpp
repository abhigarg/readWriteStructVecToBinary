#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <memory>
#include <fstream>

using namespace std;

struct trieNode{
    char value;  //value of node in char  -- 1byte
    unsigned char nChildren; //number of children (max 26) --- 1 byte
    unsigned short int posChildren; //position of first child -- children will be positioned between posChildren and posChildren + nChildren -- 2bytes
    vector<pair<unsigned short int, unsigned char>> posBigrams; // any position possible and corresponding weight ---> (2,1) bytes
    unsigned short int posParent; //position of parent of node --> 2bytes
    unsigned char unigramWeight; //--> 1 byte
};

struct testStruct{
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
    unsigned short int val;
};


/*class cNode{
public:
    char value;
    unsigned char nChildren; //number of children (max 26) --- 1 byte
    unsigned short int posChildren; //position of first child -- children will be positioned between posChildren and posChildren + nChildren -- 2bytes
    vector<pair<unsigned short int, unsigned char>> posBigrams(3); // any position possible and corresponding weight ---> (2,1) bytes
    unsigned short int posParent; //position of parent of node --> 2bytes
    unsigned char unigramWeight; //--> 1 byte
    vector<int> anyVec(2);
};*/


int main() {

    int dummy = 1;
    unsigned char dum = (unsigned char) dummy;
    cout << "dummy: " << (int)dum << endl;


    trieNode tNode;
    tNode.value = 'h';
    tNode.nChildren = 10;
    tNode.posChildren = 100;
    tNode.posParent = 1000;
    tNode.unigramWeight = 200;


    vector<trieNode> tNodeVec;
    //tNodeVec[0] = tNode;
    //tNodeVec[1] = tNode;
    tNodeVec.push_back(tNode);


    trieNode tNode2;
    tNode2.value = 'a';
    tNode2.nChildren = 5;
    tNode2.posChildren = 200;
    tNode2.posParent = 2000;
    tNode2.unigramWeight = 50;
    tNodeVec.push_back(tNode2);
    for(int i = 0; i < 2; i++){

        vector<pair<unsigned short int, unsigned char>> bigramVec2(5);
        bigramVec2[0] = make_pair(210, 10);
        bigramVec2[1] = make_pair(308, 20);
        bigramVec2[2] = make_pair(253, 100);
        bigramVec2[3] = make_pair(120, 120);
        bigramVec2[4] = make_pair(220, 90);

        tNodeVec[i].posBigrams = bigramVec2;

    }



    //tNodeVec[1] = tNode2;
    //test struct
    testStruct t1;
    t1.val1 = 'a';
    t1.val2 = 'b';
    t1.val3 = 'c';
    t1.val = 200;

    // Write out a list to a disk file
    ofstream os ("test.bin", ios::binary);

    vector<trieNode>::size_type size1 = tNodeVec.size();

    os.write((char*)&size1, sizeof(size1));
    os.write((char*)&tNodeVec[0], tNodeVec.size() * sizeof(trieNode));

    //os.write((const char*)&t1, sizeof(testStruct));
    //os.write((const char*)&tNodeVec, sizeof(tNodeVec));
    //os.write((const char*)&tNode, sizeof(tNode));
    //os.write((const char*)&tNode2, sizeof(tNode2));
    os.close();

    cout << "done!" << endl;

    cout << "reading from file" << endl;

    vector<trieNode> newtNodeVec;

    trieNode newtNode;

    ifstream is("test.bin", ios::binary);

    vector<trieNode>::size_type size2 = 0;
    is.read((char*)&size2, sizeof(size2));
    newtNodeVec.resize(size2);
    is.read((char*)&newtNodeVec[0], newtNodeVec.size() * sizeof(trieNode));

    /*is.seekg(0,ifstream::end);
    long size2 = is.tellg();
    is.seekg(0,ifstream::beg);
    newtNodeVec.resize(size2);
    is.read((char*)&newtNodeVec, size2);*/

    //cout << "size of vector read: " << newtNodeVec.size() << endl;

    //newtNode = newtNodeVec[1];

    //cout << "new node value: " << newtNode.value << endl;
    cout << "new node value: " << newtNodeVec[0].value << endl;
    cout << "new node value: " << newtNodeVec[1].value << endl;
    /*cout << "new node nChildren: " << (int)newtNodeVec[1].nChildren << endl;
    cout << "new node parent: " << (int)newtNodeVec[1].posParent << endl;
    cout << "new node bigram at 0: " << (int)newtNodeVec[1].posBigrams[0].first << ", " << (int)newtNodeVec[1].posBigrams[0].second << endl;*/

    /*testStruct newt;
    ifstream is("test2.dat", ios::binary);

    is.seekg(0,ifstream::end);
    long size2 = is.tellg();
    is.seekg(0,ifstream::beg);
    //list2.resize(size2);
    is.read((char*)&newt, size2);


    //string val(newNode.value)

    cout << "newNode value: " << string(1,newt.val1) << endl;
    cout << "newNode nChildren: " << newt.val2 << endl;
    cout << "val: " << (int)newt.val << endl;*/


    return 0;
}