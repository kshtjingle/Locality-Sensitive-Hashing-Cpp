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

    map<string, set<int>> shingles;
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

            string shingleStr = constructShingle(shingle);

            if(shingles.count(shingleStr) == 0){

                set<int> temp;
                temp.insert(docID);

                shingles.insert({shingleStr, temp});

            }

            else{
                
                shingles[shingleStr].insert(docID);
                
            }

            shingle.pop_front();

        }

    }

    //auto stop = std::chrono::high_resolution_clock::now();

    vector<pair<int, string>> shinglesInd;

    int ind = 0;

    long long total = 0;

    for(auto itr = shingles.begin(); itr != shingles.end(); ++itr){

        cout << itr->first << " ";
        total++;

        shinglesInd.push_back({ind, itr->first});
        ind++;

        for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

            cout << *itr2 << " ";

        }

        cout << endl;

    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start); 

    cout << duration.count() << endl;

    cout << docID << endl;

    inpFile.close();

    watch(total);

    vector<int> acoeff, bcoeff;

    set<int> aco, bco;

    for(int i = 0; i < 100; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(aco.count(r) > 0);

        acoeff.push_back(r);

    }

    for(int i = 0; i < 100; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(bco.count(r) > 0);

        bcoeff.push_back(r);

    }

    //Prime Number
    int c = 227011;

    for(int i = 0; i < acoeff.size(); i++){

        cout << acoeff[i] << " ";

    }

    cout << endl;

    for(int i = 0; i < bcoeff.size(); i++){

        cout << bcoeff[i] << " ";

    }

    cout << endl;

    vector<vector<int>> sigMatrix(831, vector<int>(100, INT_MAX));

    int i = 0;

    for(auto itr = shingles.begin(); itr != shingles.end(); ++itr){

        int j = 0;

        for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

            //watch(*itr2);

            for(int k = 0; k < 100; k++){

                long long pot = ((i * acoeff[k]) % c + bcoeff[k]) % c;
                int potential = pot;

                /*watch(pot);
                watch(potential);*/

                if(potential < sigMatrix[*itr2][k]){

                    sigMatrix[*itr2][k] = potential;

                }

            }

            j++;

        }

        i++;

    }

    for(int i = 0; i < 830; i++){

        for(int j = 0; j < 100; j++){

            cout << sigMatrix[i][j] << " ";

        }

        cout << endl;

    }



    return 0;

}