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

    ios::sync_with_stdio(false);

    srand(time(0));

    string query;

    cout << "Enter query:" << " ";
    cin >> query;
    //cout << query << endl;

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

    int docID = -1;
    int isDoc = 0;

    //int numDocs = 0;

    auto start = std::chrono::high_resolution_clock::now(); 

    vector<string> documents;
    //documents.push_back("Indexing starts at 1, this is not a document");

    //documents[0] = query;

    //cout << documents[0] << endl;

    string inp = "";

    string data = query;
    data.push_back(' ');

    while(inpFile >> x){

        data.push_back(x);

    }

    for(char x : data){

        if(x != 'A' && x != 'C' && x != 'G' && x != 'T'){

            shingle.clear();

            if(isDoc == 1){documents.push_back(inp);
            //watch(inp);
            //watch(documents.size());
            inp.clear();}

            isDoc = 0;

        }

        else if(shingle.size() < 8){

            if(isDoc == 0){

                isDoc = 1;
                docID++;

                //numDocs++;

            }

            inp.push_back(x);

            shingle.push_back(x);

        }

        else{

            shingle.push_back(x);

            inp.push_back(x);

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

        //cout << itr->first << " ";
        total++;

        shinglesInd.push_back({ind, itr->first});
        ind++;

        /*for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

            cout << *itr2 << " ";

        }

        cout << endl;*/

    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start); 

    //cout << duration.count() << endl;

    //cout << docID << endl;

    inpFile.close();

    watch(total);

    vector<long long> acoeff, bcoeff;

    set<long long> aco, bco;

    for(int i = 0; i < 100; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(aco.count(r) > 0);

        acoeff.push_back((long long)r);

    }

    for(int i = 0; i < 100; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(bco.count(r) > 0);

        bcoeff.push_back((long long)r);

    }

    //Prime Number
    int c = 227011;
    //int c = 29;

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

        //watch(i);

        int j = 0;

        for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

            //watch(*itr2);

            for(int k = 0; k < 100; k++){

                long long ccpy = c;

                long long pot = (((i * acoeff[k]) + bcoeff[k])) % c;
                int potential = pot;

                /*watch(pot);
                watch(potential);*/

                if(potential < sigMatrix[*itr2][k]){

                    sigMatrix[*itr2][k] = potential;

                    //watch(potential);

                }

            }

            j++;

        }

        i++;

    }

    for(int i = 0; i < 831; i++){

        for(int j = 0; j < 100; j++){

            cout << sigMatrix[i][j] << " ";

        }

        cout << endl;

    }

    set<pair<int, int>> candidatePairs;

    //Number of Bands, to be replaced by a variable later
    int B = 20;

    //Band Size, ditto
    int R = 5;

    for(int b = 0; b < B; b++){

        map<vector<int>, set<int>> buckets;

        for(int c = 0; c < 831; c++){

            vector<int> band;

            for(int p = b * R; p < (b + 1) * R; p++){

                band.push_back(sigMatrix[c][p]);

            }

            if(buckets.count(band) == 0){

                set<int> tem;
                tem.insert(c);

                buckets.insert(pair<vector<int>, set<int>>(band, tem));

            }

            else{

                buckets[band].insert(c);

            }

        }

        for(auto itr = buckets.begin(); itr != buckets.end(); ++itr){

            if(itr->second.size() < 2){

                continue;

            }

            else{

                vector<int> similar;

                for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

                    similar.push_back(*itr2);

                }

                for(int i = 0; i < similar.size(); i++){

                    for(int j = i + 1; j < similar.size(); j++){

                        candidatePairs.insert({similar[i], similar[j]});

                    }

                }

            }

        }

    }

    for(auto itr = candidatePairs.begin(); itr != candidatePairs.end(); ++itr){

        pair<int, int> temp = *itr;

        cout << endl;

        cout << temp.first << " " << documents[temp.first] << "\n";
        cout << temp.second << " " << documents[temp.second] << "\n";

    }

    cout << endl << endl;

    for(int i = 0; i < 4; i++){

        cout << documents[i] << endl;

    }

    //watch(total);

    return 0;

}