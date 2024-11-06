#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
private:
    string name;
    double score;

public:
    Movie(string n, double s){
        name = n;
        score = s;
    }

    void display(){
        cout << name << ": " << score << endl;
    }
};

int main() {
    vector<Movie> movies = {
        Movie("titanic", 9.9),
        Movie("gone with the wind", 9.6),
        Movie("terminator", 9.7)
    };

    for (Movie& movie : movies) {
        movie.display();
    }
    return 0;
}

