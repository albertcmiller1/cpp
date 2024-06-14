#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Movie {
private:
    int id;
    string title;

public:
    Movie(int id, string title) {
        this->id = id;
        this->title = title;
    }

    int getId() {
        return this->id;
    }

    string getTitle() {
        return this->title;
    }
};

class User {
private:
    int id;
    string name;

public:
    User(int id, string name) {
        this->id = id;
        this->name = name;
    }

    int getId() {
        return this->id;
    }

    string getName() {
        return this->name;
    }
};

enum MovieRating {
    NOT_RATED,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

class RatingRegister {
private:
    unordered_map<int, vector<Movie*>> userMovies;
    unordered_map<int, unordered_map<int, MovieRating>> movieRatings;

    vector<Movie*> movies;
    vector<User*> users;

public:
    RatingRegister() {
        this->userMovies = unordered_map<int, vector<Movie*>>();
        this->movieRatings = unordered_map<int, unordered_map<int, MovieRating>>();

        this->movies = vector<Movie*>();
        this->users = vector<User*>();
    }

    void addRating(User* user, Movie* movie, MovieRating rating) {
        if (this->movieRatings.find(movie->getId()) == this->movieRatings.end()) {
            this->movieRatings[movie->getId()] = unordered_map<int, MovieRating>();
            this->movies.push_back(movie);
        }
        if (this->userMovies.find(user->getId()) == this->userMovies.end()) {
            this->userMovies[user->getId()] = vector<Movie*>();
            this->users.push_back(user);
        }
        this->userMovies[user->getId()].push_back(movie);
        this->movieRatings[movie->getId()][user->getId()] = rating;
    }

    double getAverageRating(Movie* movie) {
        if (this->movieRatings.find(movie->getId()) == this->movieRatings.end()) {
            return MovieRating::NOT_RATED;
        }
        unordered_map<int, MovieRating> ratings = this->movieRatings[movie->getId()];
        int sum = 0;
        for (auto rating : ratings) {
            sum += rating.second;
        }
        return (double) sum / ratings.size();
    }

    vector<User*> getUsers() {
        return this->users;
    }

    vector<Movie*> getMovies() {
        return this->movies;
    }

    vector<Movie*> getUserMovies(User* user) {
        if (this->userMovies.find(user->getId()) == this->userMovies.end()) {
            return vector<Movie*>();
        }
        return this->userMovies[user->getId()];
    }

    unordered_map<int, MovieRating> getMovieRatings(Movie* movie) {
        if (this->movieRatings.find(movie->getId()) == this->movieRatings.end()) {
            return unordered_map<int, MovieRating>();
        }
        return this->movieRatings[movie->getId()];
    }
};

class MovieRecommendation {
private:
    RatingRegister* ratingRegister;

    int getSimilarityScore(User* user1, User* user2) {
        int score = INT_MAX; // Lower is better

        for (Movie* movie : this->ratingRegister->getUserMovies(user2)) {
            unordered_map<int, MovieRating> ratings = this->ratingRegister->getMovieRatings(movie);
            // If user1 also rated the movie, add the difference in ratings
            if (ratings.find(user1->getId()) != ratings.end()) {
                score = (score == INT_MAX) ? 0 : score;
                score += abs(ratings[user1->getId()] - ratings[user2->getId()]);
            }
        }
        return score;
    }

    Movie* recommendUnwatchedMovie(User* user, User* reviewer) {
        Movie* bestMovie = nullptr;
        int bestRating = 0;

        for (Movie* movie : this->ratingRegister->getUserMovies(reviewer)) {
            unordered_map<int, MovieRating> ratings = this->ratingRegister->getMovieRatings(movie);
            // If user has not watched the movie, and the reviewer gave it a high rating, recommend it
            if (ratings.find(user->getId()) == ratings.end() && ratings[reviewer->getId()] > bestRating) {
                bestMovie = movie;
                bestRating = ratings[reviewer->getId()];
            }
        }
        return bestMovie;
    }

public:
    MovieRecommendation(RatingRegister* ratingRegister) {
        this->ratingRegister = ratingRegister;
    }

    string recommendMovie(User* user) {
        if (this->ratingRegister->getUserMovies(user).empty()) {
            return this->recommendMovieNewUser();
        } else {
            return this->recommendMovieExistingUser(user);
        }
    }

    // Recommend the movie with the highest average rating
    string recommendMovieNewUser() {
        Movie* bestMovie;
        double bestRating = 0;
        for (Movie* movie : this->ratingRegister->getMovies()) {
            double rating = this->ratingRegister->getAverageRating(movie);
            if (rating > bestRating) {
                bestMovie = movie;
                bestRating = rating;
            }
        }
        return bestMovie->getTitle();
    }

    // Recommend highest rated movie from another user with similar interest
    string recommendMovieExistingUser(User* user) {
        Movie* bestMovie;
        int similarityScore = INT_MAX; // Lower is better

        for (User* reviewer : this->ratingRegister->getUsers()) {
            if (reviewer->getId() == user->getId()) {
                continue;
            }
            int score = this->getSimilarityScore(user, reviewer);
            if (score < similarityScore) {
                similarityScore = score;
                Movie* recommendedMovie = this->recommendUnwatchedMovie(user, reviewer);
                if (recommendedMovie->getTitle() != "") {
                    bestMovie = recommendedMovie;
                }
            }
        }
        return bestMovie->getTitle();
    }
};

int main() {
    User user1(1, "User 1");
    User user2(2, "User 2");
    User user3(3, "User 3");

    Movie movie1(1, "Batman Begins");
    Movie movie2(2, "Liar Liar");
    Movie movie3(3, "The Godfather");

    RatingRegister ratings;
    ratings.addRating(&user1, &movie1, MovieRating::FIVE);
    ratings.addRating(&user1, &movie2, MovieRating::TWO);
    ratings.addRating(&user2, &movie2, MovieRating::TWO);
    ratings.addRating(&user2, &movie3, MovieRating::FOUR);

    MovieRecommendation recommender(&ratings);

    cout << recommender.recommendMovie(&user1) << endl; // The Godfather
    cout << recommender.recommendMovie(&user2) << endl; // Batman Begins
    cout << recommender.recommendMovie(&user3) << endl; // Batman Begins
};
