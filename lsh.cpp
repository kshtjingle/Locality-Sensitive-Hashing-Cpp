#include<bits/stdc++.h>

using namespace std;

#define watch(x) cout << (#x) << " is " << (x) << endl

string constructShingle(deque<char> &shingle){
    
    string ret;

    for(int i = 0; i < 9; i++){

        ret += shingle[i];

    }

    return ret;

}

int main(){

    ifstream inpFile;

    inpFile.open("data\\dog_data.txt");
    //inpFile.open("data\\test.txt");

    if(!inpFile){

        cerr << "Unable to open";
        exit(1);

    }

    set<string> shingles;
    deque<char> shingle;

    char x;

    int docID = 0;
    int isDoc = 0;

    //int numDocs = 0;

    auto start = std::chrono::high_resolution_clock::now(); 

    while(inpFile >> x){

        if(x != 'A' && x != 'C' && x != 'G' && x != 'T'){

            shingle.clear();
            isDoc = 0;

        }

        else if(shingle.size() < 8){

            if(isDoc == 0){

                isDoc = 1;
                docID++;

                //numDocs++;

            }

            shingle.push_back(x);

        }

        else{

            shingle.push_back(x);

            shingles.insert(constructShingle(shingle));

            shingle.pop_front();

        }

    }

    auto stop = std::chrono::high_resolution_clock::now();

    for(string x : shingles){

        cout << x << endl;

    }

    //auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start); 

    cout << duration.count() << endl;

    cout << docID << endl;

    inpFile.close();

    return 0;

}