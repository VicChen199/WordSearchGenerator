/*
Word Search Generator

This program generates a word search puzzle
using random positioning and directions
when generating the locations of each word.

The results are outputted to a text file
*/

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <ctime>
using namespace std;

// Declares global variables
// Initializes the number of words and the grid size
const int gridSize = 26;
const int numWords = 30;
char grid[gridSize][gridSize];
ifstream fin;
ofstream fout;
int randomDirection;
int rowStart;
int rowMin;
int rowMax;
int colStart;
int colMin;
int colMax;
string wordList[50];
string word;

// Generates a random integer
int random(int min, int max){
    return rand() % (max - min + 1) + min;
}


// Resets the board
void reset(){
    for (int r = 0; r < gridSize; r++){
        for (int c =0; c < gridSize; c++){
            grid[r][c] = '-';
        }
    }
}

// Displays the board
void display(){
    for (int r = 0; r < gridSize; r++){
        for (int c =0; c < gridSize; c++){
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
}

// Outputs the board to a file
void printOut(){
    for (int r = 0; r < gridSize; r++){
        for (int c = 0; c < gridSize; c++){
            fout << grid[r][c] << " ";
        }
        fout << endl;
    }
}

// Places the word horizontally from left to right
void horizontalRight(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart][colStart + i] = word[wordIndex++];
    }
}

// Places the word horizontally from right to left
void horizontalLeft(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart][colStart - i] = word[wordIndex++];
    }
}

// Places the word vertically from up to down
void verticalDown(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart + i][colStart] = word[wordIndex++];
    }
}

// Places the word vertically from down to up
void verticalUp(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart - i][colStart] = word[wordIndex++];
    }
}

// Places the word diagonally from the upper left to lower right
void diagonalULR(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart + i][colStart + i] = word[wordIndex++];
    }
}

// Places the word diagonally from the lower right to upper left
void diagonalURL(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart - i][colStart - i] = word[wordIndex++];
    }
}

// Places the word diagonally from the lower left to upper right
void diagonalDLR(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart - i][colStart + i] = word[wordIndex++];
    }
}

// Places the word diagonally from the upper right to lower left
void diagonalDRL(){
    int wordIndex = 0;

    for (int i = 0; wordIndex < word.length(); i++){
        grid[rowStart + i][colStart - i] = word[wordIndex++];
    }
}

// Ensures that a word can fit into a certain spot without conflicting with another word
void isSafe(){

    // Initializes necessary variables
    bool loop = true;
    bool safe;

    // This loop ends once a valid row start and column start is found
    do{

        // Randomly generates the values of the row start and column start
        rowStart = (random(rowMin, rowMax));
        colStart = (random(colMin, colMax));
        safe = true;

        // Checks if there is a conflicting spot for the word to fit in
        for (int i = 0; i < word.length(); i++){
            if (randomDirection == 0){
                if (grid[rowStart][colStart + i] != word[i] && (grid[rowStart][colStart + i]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 1){
                if (grid[rowStart][colStart - i] != word[i] && (grid[rowStart][colStart - i]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 2){
                if (grid[rowStart + i][colStart] != word[i] && (grid[rowStart + i][colStart]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 3){
                if (grid[rowStart - i][colStart] != word[i] && (grid[rowStart - i][colStart]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 4){
                if (grid[rowStart + i][colStart + i] != word[i] && (grid[rowStart + i][colStart + i]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 5){
                if (grid[rowStart - i][colStart - i] != word[i] && (grid[rowStart - i][colStart - i]) != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 6){
                if (grid[rowStart - i][colStart + i] != word[i] && (grid[rowStart - i][colStart + i])  != '-'){
                    safe = false;
                }
            }
            else if (randomDirection == 7){
                if (grid[rowStart + i][colStart - i] != word[i] && (grid[rowStart + i][colStart - i]) != '-'){
                    safe = false;
                }
            }
        }

        // Ends the loop if a safe spot was found
        if (safe){
            loop = false;
        }
    }while(loop);
}

// Places all words into the grid
void placeWord(){

    // For (numWords) number of words, a random direction will be chosen
    for (int i = 0; i < numWords; i++){

        // Develop the word and direction
        word = wordList[i];
        randomDirection = random(0,7);

        if (randomDirection == 0){
            rowMin = 0;
            rowMax = gridSize - 1;
            colMin = 0;
            colMax = gridSize - word.length();
            isSafe();
            horizontalRight();
        }
        else if(randomDirection == 1){
            rowMin = 0;
            rowMax = gridSize - 1;
            colMin = word.length() - 1;
            colMax = gridSize - 1;
            isSafe();
            horizontalLeft();
        }
        else if(randomDirection == 2){
            rowMin = 0;
            rowMax = gridSize - word.length();
            colMin = 0;
            colMax = gridSize - 1;
            isSafe();
            verticalDown();
        }
        else if(randomDirection == 3){
            rowMin = word.length() - 1;
            rowMax = gridSize - 1;
            colMin = 0;
            colMax = gridSize - 1;
            isSafe();
            verticalUp();
        }
        else if(randomDirection == 4){
            rowMin = 0;
            rowMax = gridSize - word.length();
            colMin = 0;
            colMax = gridSize - word.length();
            isSafe();
            diagonalULR();
        }
        else if(randomDirection == 5){
            rowMin = word.length() - 1;
            rowMax = gridSize - 1;
            colMin = word.length() - 1;
            colMax = gridSize - 1;
            isSafe();
            diagonalURL();
        }
        else if(randomDirection == 6){
            rowMin = word.length() - 1;
            rowMax = gridSize - 1;
            colMin = 0;
            colMax = gridSize - word.length();
            isSafe();
            diagonalDLR();
        }
        else if(randomDirection == 7){
            rowMin = 0;
            rowMax = gridSize - word.length();
            colMin = word.length() - 1;
            colMax = gridSize - 1;
            isSafe();
            diagonalDRL();
        }
    }
}

// Fills the empty spaces of the board with a random letter
void fillBoard(){
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int r = 0; r < gridSize; r++){
        for (int c = 0; c < gridSize; c++){
            if (grid[r][c] == '-'){
                grid[r][c] = alphabet[random(0,25)];
            }
        }
    }
}

int main(){

    // Develops the file streams and seeds the program
    srand(time(0));
    fin.open("baseWordList.txt");
    fout.open("wordSearch.txt");

    // Resets the board
    reset();

    // Gathers an array of every word
    int f = 0;
    while (fin >> word){
        wordList[f] = word;
        f++;
    }

    // Places the words correctly into the grid
    placeWord();

    // Outputs the results before random characters are inputed
    cout << "Before Random Characters:\n\n";
    fout << "Before Random Characters: \n\n";
    display();
    printOut();
    cout << "\n\n";
    fout << "\n\n";

    // Fills the grid with random characters in applicable areas
    fillBoard();

    // Outputs the results after random characters are inputed
    cout << "After Random Characters:\n\n";
    fout << "After Random Characters: \n\n";
    display();
    printOut();
    cout << "\n\n";
    fout << "\n\n";

    // Outputs the list of words used in this word search
    cout << endl << "List of Words: " << endl << endl;
    fout << endl << "List of Words: " << endl << endl;
    for (int i = 0; i < numWords; i++){
        cout << wordList[i] << endl;
        fout << wordList[i] << endl;
    }
}