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

TEST(TCocktailCardTest, CopyConstructor) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Create another TCocktailCard object by copying the first
    TCocktailCard anotherCard(card);

    // Check if the copy was successful
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);

    // Modify the first card
    card += TCocktail(L"Cocktail 3", 40.0, 200.0);

    // Check if the second card remains unchanged
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);
}

TEST(TCocktailCardTest, MoveConstructor) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Create another TCocktailCard object by moving the first
    TCocktailCard anotherCard(std::move(card));

    // Check if the move was successful
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);

    // Check if the first card is in a valid but unspecified state
    EXPECT_EQ(card.size(), 0);
}

TEST(TCocktailCardTest, CopyAssignment) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Create another TCocktailCard object
    TCocktailCard anotherCard;

    // Assign the first card to the second
    anotherCard = card;

    // Check if the assignment was successful
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);

    // Modify the first card
    card += TCocktail(L"Cocktail 3", 40.0, 200.0);

    // Check if the second card remains unchanged
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);
}

TEST(TCocktailCardTest, MoveAssignment) {
    // Create a TCocktailCard object
    TCocktailCard card;

    // Add some cocktails to the card
    TCocktail cocktail1(L"Cocktail 1", 20.0, 100.0);
    TCocktail cocktail2(L"Cocktail 2", 30.0, 150.0);
    card += cocktail1;
    card += cocktail2;

    // Create another TCocktailCard object
    TCocktailCard anotherCard;

    // Move assign the first card to the second
    anotherCard = std::move(card);

    // Check if the move assignment was successful
    EXPECT_EQ(anotherCard.size(), 2);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 1").getAlcoholPercentage(), 20.0);
    EXPECT_EQ(anotherCard.findCocktail(L"Cocktail 2").getAlcoholPercentage(), 30.0);

    // Check if the first card is in a valid but unspecified state
    EXPECT_EQ(card.size(), 0);
}

TEST(TCocktailCardTest, GetVolumeByPercentageRange_EmptyCard) {
    TCocktailCard card;
    EXPECT_EQ(card.getVolumeByPercentageRange({0., 100.}), 0.);
}

TEST(TCocktailCardTest, GetVolumeByPercentageRange_InvalidRange) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    card += cocktail1;
    EXPECT_THROW(card.getVolumeByPercentageRange({100., 0.}), std::invalid_argument);
    EXPECT_THROW(card.getVolumeByPercentageRange({-10., 100.}), std::invalid_argument);
    EXPECT_THROW(card.getVolumeByPercentageRange({0., 110.}), std::invalid_argument);
}

TEST(TCocktailCardTest, GetVolumeByPercentageRange_SingleCocktail) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    card += cocktail1;
    EXPECT_EQ(card.getVolumeByPercentageRange({0., 100.}), 100.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({0., 10.}), 100.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({10., 100.}), 100.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({20., 30.}), 0.0);
}

TEST(TCocktailCardTest, GetVolumeByPercentageRange_MultipleCocktails) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail2", 20.0, 200.0);
    TCocktail cocktail3(L"Cocktail3", 30.0, 300.0);
    card += cocktail1;
    card += cocktail2;
    card += cocktail3;
    EXPECT_EQ(card.getVolumeByPercentageRange({0., 100.}), 600.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({0., 20.}), 300.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({20., 30.}), 500.0);
    EXPECT_EQ(card.getVolumeByPercentageRange({30., 100.}), 300.0);
}

TEST(TCocktailCardTest, GetVolumeByQuartile_EmptyCard) {
    TCocktailCard card;
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q1), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q2), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q3), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q4), 0.);
}

TEST(TCocktailCardTest, GetVolumeByQuartile_InvalidQuartile) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    card += cocktail1;
    EXPECT_THROW(card.getVolumeByQuartile(static_cast<TQuartile>(5)), std::invalid_argument);
}

TEST(TCocktailCardTest, GetVolumeByQuartile_SingleCocktail) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    card += cocktail1;
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q1), 100.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q2), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q3), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q4), 0.);
}

TEST(TCocktailCardTest, GetVolumeByQuartile_MultipleCocktails) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail2", 20.0, 200.0);
    TCocktail cocktail3(L"Cocktail3", 30.0, 300.0);
    card += cocktail1;
    card += cocktail2;
    card += cocktail3;
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q1), 300.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q2), 300.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q3), 0.);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q4), 0.);
}

TEST(TCocktailCardTest, GetVolumeByQuartile_EqualVolumes) {
    TCocktailCard card;
    TCocktail cocktail1(L"Cocktail1", 10.0, 100.0);
    TCocktail cocktail2(L"Cocktail2", 26.0, 100.0);
    TCocktail cocktail3(L"Cocktail3", 55.0, 100.0);
    TCocktail cocktail4(L"Cocktail3", 76.0, 100.0);
    card += cocktail1;
    card += cocktail2;
    card += cocktail3;
    card += cocktail4;
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q1), 100.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q2), 100.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q3), 100.0);
    EXPECT_EQ(card.getVolumeByQuartile(TQuartile::Q4), 100.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
