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
* The user inputs the shingle size, the number of hash functions to be used, the size of a band, and the threshold (percentage) above which strings are considered to be similar.<br>
* The user then inputs the query string.<br>
* The program outputs the DNA sequences which are similar to the query string based on the inputs given.<br>
*/

#include<bits/stdc++.h>

using namespace std;

int S;/*!< Shingle size*/

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
/*! double JaccardSimilarity(int, int, int, vector<vector<int>>)
  \brief To calculate the Jaccard Similarity between two sequences
  \param f is the first sequence
  \param s is the second sequence
  \param H is the size of the signature Matrix
  \param sigMatrix is the signature Matrix
  \return The similarity score
*/
double JaccardSimilarity(int f, int s, int H, vector<vector<int>> &sigMatrix){

    double similarity = 0;

        for(int i = 0; i < H; i++){

            if(sigMatrix[f][i] == sigMatrix[s][i]){

                similarity++;

            }

        }

        return similarity;

}

/*! \file */
/*! void Shingling(map<string, set<int>, long long)
  \brief To store all the unique shingles, as well as the corresponding set of document IDs contining each shingle
  \param shingles is a map with keys as k-character shingles, and values as the set of document IDs containing the shingle
  \param total is the total number of shingles
*/

void Shingling(map<string, set<int>> &shingles, long long total){

    vector<pair<int, string>> shinglesInd;

    int ind = 0;


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

}

/*! \file */
/*! void Minhashing(map<string, set<int>>, int, int, vector<long long>, vector<long long>, vector<vector<int>>)
  \brief Performs the min-hashing step of LSH
  \param shingles is a map with keys as k-character shingles, and values as the set of document IDs containing the shingle
  \param c is a prime number greater than the total number of unnique shingles in the dataset
  \param H is the size of the signature Matrix
  \param acoeff is the coefficient a in the hash function (ax+b)\%c
  \param bcoeff is the coefficient b in the function (ax+b)\%c
  \param sigMatrix is the signature Matrix
*/

void Minhashing(map<string, set<int>> &shingles, int H, int c, vector<long long> acoeff, vector<long long> bcoeff, vector<vector<int>> &sigMatrix){

    int i = 0;

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

}

/*! \file */
/*! \brief The main function calls the other functions of shingling, min-hashing and Jaccard similarity, and finally performs the LSH step of the algorithm
  \return int 0
*/
int main(){

    ios::sync_with_stdio(false);

    //Initializes the rand function with a different value each time using the current time
    srand(time(0));

    cout << "Enter Shingle Size: ";
    cin >> S;

    //Size of the signature matrix, same as Number of hash functions for minhashing
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
    //inpFile.open("data\\test.txt");

    if(!inpFile){

        cerr << "Unable to open";
        exit(1);

    }

    //To store the input query
    string query;

    //UI and Input of query input
    cout << "Enter query:" << " ";
    cin >> query;

    //cout << query << endl;

    //Stores the shingles and the docIDs in which they appear
    map<string, set<int>> shingles;

    deque<char> shingle;

    char x;

    //Utility variables for storing documents from input
    int docID = -1;
    int isDoc = 0;

    //int numDocs = 0;

    //auto start = std::chrono::high_resolution_clock::now();

    //Stores documents, the index is the docID, index 0 is the query document.
    vector<string> documents;
    //documents.push_back("Indexing starts at 1, this is not a document");

    //documents[0] = query;

    //cout << documents[0] << endl;

    string inp = "";

    string data = query;
    data.push_back(' ');

    auto start = std::chrono::high_resolution_clock::now();

    cout << "Shingling..." << endl;

    while(inpFile >> x){

        data.push_back(x);

    }

    //Shingling
    for(char x : data){

        if(x != 'A' && x != 'C' && x != 'G' && x != 'T'){

            shingle.clear();

            if(isDoc == 1){documents.push_back(inp);
            //watch(inp);
            //watch(documents.size());
            inp.clear();}

            isDoc = 0;

        }

        else if(shingle.size() < S - 1){

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

    long long total = 0;

    Shingling(shingles, total);

    auto stop = std::chrono::high_resolution_clock::now();

    cout << "Shingling Completed" << " ";

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "Time taken: " << duration.count() / 1000 << " seconds" << endl;

    //cout << duration.count() << endl;

    //cout << docID << endl;

    inpFile.close();

    cout << "Generating Signature Matrix..." << endl;

    start = std::chrono::high_resolution_clock::now();

    /*-------------Randomly generting H hash functions-------------*/
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
    //int c = 29;

    /*for(int i = 0; i < acoeff.size(); i++){
        cout << acoeff[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < bcoeff.size(); i++){
        cout << bcoeff[i] << " ";
    }
    cout << endl;*/

    //Signature Matrix
    vector<vector<int>> sigMatrix(831, vector<int>(H, INT_MAX));

    //int i = 0;

    //Minhashing
    Minhashing(shingles, H, c, acoeff, bcoeff, sigMatrix);

    stop = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "Signature Matrix Generation Completed. Time taken: " << duration.count() / 1000 << " seconds" << endl;

    //Uncomment this to output the whole signature matrix
    /*for(int i = 0; i < 831; i++){
        for(int j = 0; j < 100; j++){
            cout << sigMatrix[i][j] << " ";
        }
        cout << endl;
    }*/

    start = std::chrono::high_resolution_clock::now();

    cout << "Computing the candidate pairs and checking Jaccard similarity..." << endl;

    //Stroes Candidte Pairs of Documents
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
        double similarity = JaccardSimilarity(temp.first, temp.second, H, sigMatrix);

        /*for(int i = 0; i < H; i++){
            if(sigMatrix[temp.first][i] == sigMatrix[temp.second][i]){
                similarity++;
            }
        }*/

        if(similarity / H >= T / 100){

            cout << endl;
            cout << "DocID: " << temp.second << endl;
            cout << documents[temp.second];

        }

    }

    cout << endl;

    stop = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "LSH Step Completed. Time Taken: " << duration.count() / 1000 << " seconds" << endl;

    cout << endl << "Do you want to enter another query? (Y/N) ";
    cin >> runAgain;

    }

    return 0;

}
