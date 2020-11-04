# Locality-Sensitive-Hashing-Cpp

<h2>Setup and compilation:</h2>
The file lsh.cpp contains the code for the application.<br/>

Steps to run the application:<br/>

Clone the repository on your local storage.<br/>
Compile the file lsh.cpp. Eg, g++ lsh.cpp<br/>
Run the executable file that results.<br/>
The documentation is located in the "html" folder.<br/>
<br/>
<b>Datasets:</b><br/>
Move a new dataset in txt format in the "data" folder. To use this new dataset, enter the name of the file without .txt when prompted.<br/>
<br/>
<h2>Functionality:</h2>
<b>The application does the following:</b><br/>
1. Loads Documents from the dataset<br/>
2. Shingling<br/>
3. MinHashing<br/>
4. Signature Matrix Generation<br/>
5. Finds the candidate pairs<br/>
6. Returns the documents with respective DocIDs with a Jaccard Similarity ratio of atleast the threshold similarity ratio.<br/>
<br/>
<h2>Citation for the corpus:</h2>
<b>The test set used in this project is the dog_data.txt file obtained from https://www.kaggle.com/thomasnelson/datasets
