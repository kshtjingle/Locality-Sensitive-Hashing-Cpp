# Locality-Sensitive-Hashing-Cpp

<h2>Setup and compilation:</h2>
The script consists of a Jupyter notebook.<br/>
The file "plag_check.py" is the same script as the Jupyter notebook, this file was used to generate the documentation.<br/>
The training files should be moved into the "texts" folder, and the testing files should be moved into the "test" folder.<br/>
The script checks similarity for ".txt" files as of now.<br/>
The documentation is located in the "html" folder.<br/>
<br/>
<b>Required modules:</b><br/>
If running the file "plag_check.py", the NLTK, num2words, pandas and numpy modules must be installed on the system.<br/>
<br/>
<h2>Functionality:</h2>
<b>The plagiarism checker does the following:</b><br/>
1. Loads files<br/>
2. Preprocessing (lowercase, removing punctuation, changing numbers to words, lemmatization, stemming)<br/>
3. Performs tf-idf vectorization on the contents of the files<br/>
4. Find cosine similarity between the resulting vectors<br/>
5. Ranks the training documents based on similarity to the testing set<br/>
6. Return the rank list with similarity percentage<br/>
<br/>
<h2>Citation for the corpus:</h2>
<b>The test set used in this project is the dog_dna.txt file obtained from https://www.kaggle.com/thomasnelson/datasets
