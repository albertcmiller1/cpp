#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum CardSuit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

class Card {
private:
    CardSuit suit;
    int value;

public:
    Card(CardSuit suit, int value) {
        this->suit = suit;
        this->value = value;
    }

    CardSuit getSuit() {
        return this->suit;
    }

    int getValue() {
        return this->value;
    }

    void print() {
        cout << getSuit() << " " << getValue() << endl;
    }
};

class Deck {
private:
    vector<Card*> cards;

public:
    Deck() {
        for (CardSuit suit = CardSuit::CLUBS; suit <= CardSuit::SPADES; suit = (CardSuit)(suit + 1)) {
            for (int value = 1; value <= 13; value++) {
                cards.push_back(new Card(suit, min(value, 10)));
            }
        }
    }

    void print() {
        for (Card* card : cards) {
            card->print();
        }
    }

    Card* draw() {
        Card* card = cards.back();
        cards.pop_back();
        return card;
    }

    void shuffle() {
        for (int i = 0; i < cards.size(); i++) {
            int j = rand() % 51; // random number between 0 and 50
            Card* temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }
};

class Hand {
private:
    vector<Card*> cards;
    int score;

public:
    Hand() {
        this->score = 0;
        this->cards = vector<Card*>();
    }

    // Note: there is a subtle bug here. 
    // If an ace is in the hand, which counts as an 11,
    // and the player draws another card, which makes the score > 21.
    void addCard(Card* card) {
        cards.push_back(card);
        if (card->getValue() == 1) {
            score += (score + 11 <= 21) ? 11 : 1;
        } else {
            score += card->getValue();
        }
    }

    int getScore() {
        return score;
    }

    vector<Card*> getCards() {
        return cards;
    }

    void print() {
        for (Card* card : cards) {
            cout << card->getSuit() << ", " << card->getValue() << endl;
        }
    }
};

class Player {
private:
    Hand* hand;

public:
    Player(Hand* hand) {
        this->hand = hand;
    }

    Hand* getHand() {
        return this->hand;
    }

    void clearHand() {
        this->hand = new Hand();
    }

    void addCard(Card* card) {
        this->hand->addCard(card);
    }

    virtual bool makeMove() = 0;
};

class UserPlayer : public Player {
private:
    int balance;

public:
    UserPlayer(int balance, Hand* hand) : Player(hand) {
        this->balance = balance;
    }

    int getBalance() {
        return balance;
    }

    int placeBet(int amount) {
        if (amount > balance) {
            throw "Insufficient funds";
        }
        balance -= amount;
        return amount;
    }

    void receiveWinnings(int amount) {
        balance += amount;
    }

    /** Overrides makeMove() in Player class */
    bool makeMove() {
        if (this->getHand()->getScore() > 21) {
            return false;
        }
        // read user input
        cout << "Draw card? [y/n] ";
        string move;
        cin >> move;
        return move == "y";
    }
};

class Dealer : public Player {
private:
    int targetScore;

public:
    Dealer(Hand* hand) : Player(hand) {
        this->targetScore = 17;
    }

    void updateTargetScore(int score) {
        this->targetScore = score;
    }

    bool makeMove() {
        return this->getHand()->getScore() < this->targetScore;
    }
};

class GameRound {
private:
    UserPlayer* player;
    Dealer* dealer;
    Deck* deck;

public:
    GameRound(UserPlayer* player, Dealer* dealer, Deck* deck) {
        this->player = player;
        this->dealer = dealer;
        this->deck = deck;
    }

    int getBetUser() {
        cout << "Enter a bet amount: ";
        int bet;
        cin >> bet;
        return bet;
    }

    void dealInitialCards() {
        for (int i = 0; i < 2; i++) {
            player->addCard(deck->draw());
            dealer->addCard(deck->draw());
        }
        cout << "Player hand:" << endl;
        player->getHand()->print();
        Card* dealerCard = dealer->getHand()->getCards()[0];
        cout << "Dealer's first card:" << endl;
        dealerCard->print();
    }

    void cleanupRound() {
        player->clearHand();
        dealer->clearHand();
        cout << "Player balance: " << player->getBalance() << endl;
    }

    void play() {
        deck->shuffle();

        if (player->getBalance() <= 0) {
            cout << "Player has no more money =)" << endl;
            return;
        }
        int userBet = getBetUser();
        player->placeBet(userBet);

        dealInitialCards();

        // User makes moves
        while (player->makeMove()) {
            Card* drawnCard = deck->draw();
            cout << "Player draws " << drawnCard->getSuit() << " " << drawnCard->getValue() << endl;
            player->addCard(drawnCard);
            cout << "Player score: " << player->getHand()->getScore() << endl;
        }
        if (player->getHand()->getScore() > 21) {
            cout << "Player loses" << endl;
            cleanupRound();
            return;
        }

        // Dealer makes moves
        dealer->updateTargetScore(player->getHand()->getScore());
        while (dealer->makeMove()) {
            dealer->addCard(deck->draw());
        }

        // Determine winner
        int dealerScore = dealer->getHand()->getScore();
        int playerScore = player->getHand()->getScore();
        if (dealerScore > 21 || playerScore > dealerScore) {
            cout << "Player wins" << endl;
            player->receiveWinnings(userBet * 2);
        } else if (dealerScore > playerScore) {
            cout << "Player loses" << endl;
        } else {
            cout << "Game ends in a draw" << endl;
            player->receiveWinnings(userBet);
        }
        cleanupRound();
    }
};

int main() {
    UserPlayer* player = new UserPlayer(1000, new Hand());
    Dealer* dealer = new Dealer(new Hand());
    while (player->getBalance() > 0) {
        GameRound(player, dealer, new Deck()).play();
    }
}
