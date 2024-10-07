#include <gtest/gtest.h>
#include "../lib/cocktail_card.h"

TEST(TCocktailCardTest, DefaultConstructor) {
    TCocktailCard card;
    EXPECT_TRUE(card.isEmpty());
    EXPECT_EQ(card.size(), 0);
    EXPECT_EQ(card.capacity(), 0);
}

TEST(TCocktailCardTest, ConstructorWithCocktails) {
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail2", 20.0, 200.0);
    TCocktail *cocktails = new TCocktail[2]{cocktail1, cocktail2};
    TCocktailCard card(cocktails, 2);
    delete[] cocktails;
    EXPECT_FALSE(card.isEmpty());
    EXPECT_EQ(card.size(), 2);
    EXPECT_EQ(card.capacity(), 2);
}

TEST(TCocktailCardTest, AddCocktail) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    EXPECT_FALSE(card.isEmpty());
    EXPECT_EQ(card.size(), 1);
    EXPECT_EQ(card.capacity(), 1);
}

TEST(TCocktailCardTest, FindCocktail) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    EXPECT_EQ(card.findCocktail(L"Cocktail"), cocktail);
}

TEST(TCocktailCardTest, FindCocktailNotFound) {
    TCocktailCard card;
    EXPECT_THROW(card.findCocktail(L"Cocktail"), std::invalid_argument);
}

TEST(TCocktailCardTest, RemoveCocktail) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    card.removeCocktail(L"Cocktail");
    EXPECT_TRUE(card.isEmpty());
}

TEST(TCocktailCardTest, GetCocktailInRange) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Define the alcohol percentage range
    std::pair<const double, const double> alc_percentage_range(20.0, 30.0);

    // Define the volume
    double volume = 200.0;

    // Get the cocktail
    TCocktail result = card.getCocktail(alc_percentage_range, volume);

    // Check if the result is correct
    EXPECT_EQ(result.getAlcoholPercentage(), 20.0);
    EXPECT_EQ(result.getVolume(), volume);
}

TEST(TCocktailCardTest, GetCocktailOutOfRange) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Define the alcohol percentage range
    std::pair<const double, const double> alc_percentage_range(40.0, 50.0);

    // Define the volume
    double volume = 200.0;

    // Expect an exception to be thrown
    EXPECT_THROW(card.getCocktail(alc_percentage_range, volume), std::invalid_argument);
}

TEST(TCocktailCardTest, GetCocktailMixed) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 20.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Define the alcohol percentage range
    std::pair<const double, const double> alc_percentage_range(15.0, 19.0);

    // Define the volume
    double volume = 200.0;

    // Get the cocktail
    TCocktail result = card.getCocktail(alc_percentage_range, volume);

    // Check if the result is correct
    double expected_alc_percentage = (cocktail1.getAlcoholPercentage() * cocktail1.getVolume() + cocktail2.getAlcoholPercentage() * cocktail2.getVolume()) / (cocktail1.getVolume() + cocktail2.getVolume());
    EXPECT_NEAR(result.getAlcoholPercentage(), expected_alc_percentage, 0.01);
    EXPECT_EQ(result.getVolume(), volume);
}

TEST(TCocktailCardTest, GetCocktailEmptyCard) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Define the alcohol percentage range
    std::pair<const double, const double> alc_percentage_range(20.0, 30.0);

    // Define the volume
    double volume = 200.0;

    // Expect an exception to be thrown
    EXPECT_THROW(card.getCocktail(alc_percentage_range, volume), std::invalid_argument);
}

TEST(TCocktailCardTest, GetVolumeByQuartile) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail2", 20.0, 200.0);
    card += cocktail1;
    card += cocktail2;
    EXPECT_EQ(card.getVolumeByQuartile(std::make_pair(0.0, 25.0)), 300.0);
}

TEST(TCocktailCardTest, RenameCocktail) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    card.renameCocktail(L"Cocktail", L"NewCocktail");
    EXPECT_NO_THROW(card[L"NewCocktail"]);
    EXPECT_THROW(card[L"Cocktail"], std::invalid_argument);
}

TEST(TCocktailCardTest, OperatorPlusEqual) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    EXPECT_EQ(card.size(), 1);
}

TEST(TCocktailCardTest, OperatorIndex) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    EXPECT_EQ(card[L"Cocktail"], cocktail);
}

TEST(TCocktailCardTest, OperatorAssignment) {
    TCocktailCard card1;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card1 += cocktail;
    TCocktailCard card2;
    card2 = card1;
    EXPECT_EQ(card2.size(), 1);
}

TEST(TCocktailCardTest, PrintCard) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    std::wostringstream oss;
    card.dump(oss);
    EXPECT_EQ(oss.str(), L"Cocktail - 10% - 100ml\n");
}

TEST(TCocktailCardTest, OperatorOutput) {
    TCocktailCard card;
    TCocktail cocktail(L"Cocktail", 10.0, 100.0);
    card += cocktail;
    std::wostringstream oss;
    oss << card;
    EXPECT_EQ(oss.str(), L"Cocktail - 10% - 100ml\n");
}

TEST(TCocktailCardTest, OperatorInput) {
    TCocktailCard card;
    std::wistringstream iss(L"2\nCocktail1 10.0 100.0\nCocktail2 20.0 200.0");
    iss >> card;
    EXPECT_EQ(card.size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
