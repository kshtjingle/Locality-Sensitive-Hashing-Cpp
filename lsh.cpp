/** @file lsh.cpp
 * @brief Script that implements LSH algorithm to find similar DNA sequences
 *@author 2017A7PS1226H - Manognya Bhattaram
 *@author 2018A7PS0434H - Kshitij Ingle
 *@author 2018A7PS0179H - Rhytham Choudhary
*/

/**
*@author 2017A7PS1226H
*@author 2018A7PS0434H
*@author 2017A7PS0179H
*\mainpage Description
* The following project consists of a single C++ file which is the implementation of the LSH algorithm in the C++ language.<br>
* The input file used for testing was a file with DNA sequences.<br>
* The user inputs the shingle size, the number of hash functions to be used, the number of bands, and the threshold (percentage) above which strings are considered to be similar.<br>
* The user then inputs the query string.<br>
* The program outputs the DNA sequences which are similar to the query string based on the inputs given.<br>
*/

#include<bits/stdc++.h>

using namespace std;

int S; /*!< Shingle size*/


#define watch(x) cout << (#x) << " is " << (x) << endl
/*!<Utility Macro*/

/*! \file */
/*! string constructShingle(deque<char>)
 \brief Utility function to return a shingle at each step while reading the input file
 \param shingle a deque of characters which are the characters in the shingle
 \return A string representing the shingle
*/
string constructShingle(deque<char> &shingle){

    string ret;

    for(int i = 0; i < S; i++){

        ret += shingle[i];

    }

    return ret;

}
/*! \file */
/*! \brief The main algorithm implementation is in the main function<br>
  * The main function performs shingling on the input sequence, calculates the signature matrix by performing minhashing,<br>
  and computes the Jaccard Similarity between two sequences.
  \return int 0
*/
int main(){

    ios::sync_with_stdio(false);

    //Initializes the rand function with a different value each time using the current time
    srand(time(0));

    cout << "Enter Shingle Size: ";
    cin >> S;

    //Size of the signature matrix, same as Number of hash functions for minhashings
    int H;

    cout << "Enter a size for the signature matrix: ";
    cin >> H;

    //Band Size
    int R;
    cout << "Enter number of rows in a band (size of a band) : ";
    cin >> R;

    //Number of bands
    int B = H / R;

    //Threshold similarity percentage
    double T;
    cout << "Enter threshold similarity percentage: ";
    cin >> T;

    //For multiple queries
    char runAgain = 'Y';

    while(runAgain == 'Y' || runAgain == 'y'){

    /*-------------FILE INPUT-------------*/
    ifstream inpFile;

    inpFile.open("data\\dog_data.txt");

    if(!inpFile){

        cerr << "Unable to open";
        exit(1);

    }

    //To store the input query
    string query;

    //UI and Input of query input
    cout << "Enter query:" << " ";
    cin >> query;

    //Stores the shingles and the docIDs in which they appear
    map<string, set<int>> shingles;

    deque<char> shingle;

    char x;

    //Utility variables for storing documents from input
    int docID = -1;
    int isDoc = 0;

    auto start = std::chrono::high_resolution_clock::now();

    //Stores documents, the index is the docID, index 0 is the query document.
    vector<string> documents;


    string inp = "";

    string data = query;
    data.push_back(' ');

    while(inpFile >> x){

        data.push_back(x);

    }

    //Shingling
    for(char x : data){

        if(x != 'A' && x != 'C' && x != 'G' && x != 'T'){

            shingle.clear();

            if(isDoc == 1){documents.push_back(inp);
            inp.clear();}

            isDoc = 0;

        }

        else if(shingle.size() < S - 1){

            if(isDoc == 0){

                isDoc = 1;
                docID++;

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

    vector<pair<int, string>> shinglesInd;

    int ind = 0;

    long long total = 0;

    for(auto itr = shingles.begin(); itr != shingles.end(); ++itr){

        total++;

        shinglesInd.push_back({ind, itr->first});
        ind++;

    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    //cout << duration.count() << endl;

    //cout << docID << endl;

    inpFile.close();

    /*-------------Randomly generating H hash functions-------------*/
    vector<long long> acoeff, bcoeff;

    set<long long> aco, bco;

    for(int i = 0; i < H; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(aco.count(r) > 0);

        acoeff.push_back((long long)r);

    }

    for(int i = 0; i < H; i++){

        int r;

        do{

            r = rand() % (total + 1);

        } while(bco.count(r) > 0);

        bcoeff.push_back((long long)r);

    }

    //Prime Number
    int c = 227011;

    //Signature Matrix
    vector<vector<int>> sigMatrix(831, vector<int>(H, INT_MAX));

    int i = 0;

    //Minhashing
    for(auto itr = shingles.begin(); itr != shingles.end(); ++itr){

        int j = 0;

        for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){

            for(int k = 0; k < H; k++){

                long long ccpy = c;

                long long pot = (((i * acoeff[k]) + bcoeff[k])) % c;
                int potential = pot;

                if(potential < sigMatrix[*itr2][k]){

                    sigMatrix[*itr2][k] = potential;

                }

            }

            j++;

        }

        i++;

    }


    //Stores Candidate Pairs of Documents
    set<pair<int, int>> candidatePairs;

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

    cout << endl << "Documents similar to the query, with their DocIDs:" << endl;

    //LSH Step
    for(auto itr = candidatePairs.begin(); itr != candidatePairs.end(); ++itr){

        pair<int, int> temp = *itr;

        //If this candidate pair does not have the query as one of it's elements, then break out of the loop.
        if(temp.first != 0){

            break;

        }

        //Computing Jaccard Similarity of the candidate pair
        double similarity = 0;

        for(int i = 0; i < H; i++){

            if(sigMatrix[temp.first][i] == sigMatrix[temp.second][i]){

                similarity++;

            }

        }

        if(similarity / H >= T / 100){

            cout << endl;
            cout << "DocID: " << temp.second << endl;
            cout << documents[temp.second];

        }

    }

    cout << endl;

    cout << endl << "Do you want to enter another query? (Y/N) ";
    cin >> runAgain;

    }

    return 0;

}
