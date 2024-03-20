#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HopfieldNetwork {
private:
    int patternSize;
    vector<vector<int>> weights;

public:
    HopfieldNetwork(int size) : patternSize(size), weights(size, vector<int>(size, 0)) {}

    void train(const vector<vector<int>>& patterns) {
        for (const auto& pattern : patterns) {
            for (int i = 0; i < patternSize; ++i) {
                for (int j = 0; j < patternSize; ++j) {
                    if (i != j) {
                        weights[i][j] += (1 - (i == j)) * pattern[i] * pattern[j];
                    }
                }
            }
        }
    }
//aktualizacja
vector<int> update(const vector<int>& inputPattern) {
    vector<int> newPattern(patternSize, 0);

    for (int i = 0; i < patternSize; ++i) {
        int net = 0;
        for (int j = 0; j < patternSize; ++j) {
            net += weights[i][j] * inputPattern[j];
        }

        if (net > 0) {
            newPattern[i] = 1;
        } else if (net < 0) {
            newPattern[i] = -1;
        } else {
            newPattern[i] = inputPattern[i];
        }
    }

    return newPattern;
}

    vector<int> reconstructPattern(const vector<int>& distortedPattern, int maxIterations = 100) {
        vector<int> currentPattern = distortedPattern;

        for (int iteration = 0; iteration < maxIterations; ++iteration) {
            vector<int> newPattern = update(currentPattern);

            // Sprawdzenie stabilnosci
            if (newPattern == currentPattern) {
                return newPattern;
            }
            currentPattern = newPattern;
        }

        return currentPattern;
    }
};
int main() {
    //dane do treningu
    vector<vector<int>> patterns = {
        {1, 1, 1, 1, 1, 1, -1, -1, -1, 1, 1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, 1, 1, -1, -1, -1, 1, 1, -1, -1, -1, 1},
        {1, 1, 1, 1, 1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, 1, 1, 1},
        {1, -1, -1, -1, 1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1, -1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1, -1, 1, 1, -1, -1, -1, 1},
        {-1, 1, 1, 1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, 1, 1, 1, -1},
    };

    //Znieksztalcona litera
    vector<int> distortedLetter = {-1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, 1, 1, -1, -1};


                                        

    //Tworzenie  i nauka sieci
    HopfieldNetwork network(distortedLetter.size());
    network.train(patterns);

    // Odtworz oryginalny wzorzec
    vector<int> reconstructedPattern = network.reconstructPattern(distortedLetter);

    // Wyswietlanie wynikiow
    cout << "Znieksztalcona litera: ";
    for (int pixel : distortedLetter) {
        cout << pixel << " ";
    }
    cout << endl;

    cout << "Odtworzony wzorzec: ";
    for (int pixel : reconstructedPattern) {
        cout << pixel << " ";
    }
    cout << endl;
    int sum = 0;
    for (int pixel : reconstructedPattern) {
    sum += pixel;
    }
    int sum1 = 0;
    for (int pixel : patterns[0]) {
        sum1 += pixel;
    }
    int sum2 = 0;
    for (int pixel : patterns[1]) {
        sum2 += pixel;
    }
    int sum3 = 0;
    for (int pixel : patterns[2]) {
        sum3 += pixel;
    }
    int sum4 = 0;
    for (int pixel : patterns[3]) {
        sum4 += pixel;
    }
    if(sum==sum1){ cout<<"Jest to litera A"<<endl; }
    if(sum==sum2){ cout<<"Jest to litera C"<<endl; }
    if(sum==sum3){ cout<<"Jest to litera X"<<endl; }
    if(sum==sum4){ cout<<"Jest to litera I"<<endl; }
    else { cout<<"Litera nieznana (wzorzec niepodobny do zadnej z uczonych liter)"<<endl; }
    return 0;
}
