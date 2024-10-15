#include <gtest/gtest.h>
#include <cmath>
#include "../lib/cocktail.h"

TEST(TCocktailTest, DefaultConstructor) {
    TCocktail cocktail;
    EXPECT_EQ(cocktail.getName(), L"");
    EXPECT_EQ(cocktail.getAlcoholPercentage(), 0.);
    EXPECT_EQ(cocktail.getVolume(), 0.);
}

TEST(TCocktailTest, CustomConstructor) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    EXPECT_EQ(cocktail.getName(), name);
    EXPECT_EQ(cocktail.getAlcoholPercentage(), alc_percentage);
    EXPECT_EQ(cocktail.getVolume(), vol);
}

TEST(TCocktailTest, VolumeConstructor) {
    double vol = 100.;
    TCocktail cocktail(vol);
    EXPECT_EQ(cocktail.getName(), L"Water");
    EXPECT_EQ(cocktail.getAlcoholPercentage(), 0.);
    EXPECT_EQ(cocktail.getVolume(), vol);
}

TEST(TCocktailTest, MixWithDouble) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    cocktail = cocktail + 200.;
    EXPECT_EQ(cocktail.getVolume(), 300.);
}

TEST(TCocktailTest, GetName) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    EXPECT_EQ(cocktail.getName(), name);
}

TEST(TCocktailTest, GetAlcoholPercentage) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    EXPECT_EQ(cocktail.getAlcoholPercentage(), alc_percentage);
}

TEST(TCocktailTest, GetVolume) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    EXPECT_EQ(cocktail.getVolume(), vol);
}

TEST(TCocktailTest, SetName) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    std::wstring new_name = L"New Cocktail";
    cocktail.setName(new_name);
    EXPECT_EQ(cocktail.getName(), new_name);
}

TEST(TCocktailTest, SetAlcoholPercentage) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    double new_alc_percentage = 75.;
    cocktail.setAlcoholPercentage(new_alc_percentage);
    EXPECT_EQ(cocktail.getAlcoholPercentage(), new_alc_percentage);
}

TEST(TCocktailTest, SetVolume) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);
    double new_vol = 200.;
    cocktail.setVolume(new_vol);
    EXPECT_EQ(cocktail.getVolume(), new_vol);
}

TEST(TCocktailTest, OperatorPlus) {
    std::wstring name1 = L"Cocktail1";
    double alc_percentage1 = 50.;
    double vol1 = 100.;
    TCocktail cocktail1(name1, alc_percentage1, vol1);

    std::wstring name2 = L"Cocktail2";
    double alc_percentage2 = 75.;
    double vol2 = 200.;
    TCocktail cocktail2(name2, alc_percentage2, vol2);

    TCocktail result = cocktail1 + cocktail2;
    EXPECT_EQ(result.getName(), name1 + L" and " + name2);
    EXPECT_NEAR(result.getAlcoholPercentage(), (alc_percentage1 * vol1 + alc_percentage2 * vol2) / (vol1 + vol2), 0.01);
    EXPECT_EQ(result.getVolume(), vol1 + vol2);
}

TEST(TCocktailTest, OperatorRightShift) {
    std::wstring name1 = L"Cocktail1";
    double alc_percentage1 = 50.;
    double vol1 = 100.;
    TCocktail cocktail1(name1, alc_percentage1, vol1);

    std::wstring name2 = L"Cocktail2";
    double alc_percentage2 = 75.;
    double vol2 = 200.;
    TCocktail cocktail2(name2, alc_percentage2, vol2);

    cocktail1 >> cocktail2;
    EXPECT_EQ(cocktail1.getVolume(), 0.);
    EXPECT_EQ(cocktail2.getVolume(), vol2 + 100.);

    cocktail1.setVolume(200.);
    cocktail1 >> cocktail2;
    EXPECT_EQ(cocktail1.getVolume(), 100.);
    EXPECT_EQ(cocktail2.getVolume(), vol2 + 200.);
}

TEST(TCocktailTest, OperatorMultiply) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);

    double multiplier = 2.;
    TCocktail result = cocktail * multiplier;
    EXPECT_EQ(result.getName(), name);
    EXPECT_EQ(result.getAlcoholPercentage(), alc_percentage);
    EXPECT_EQ(result.getVolume(), vol * multiplier);
}

TEST(TCocktailTest, OperatorMultiplyReverse) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);

    const double multiplier = 2.;
    TCocktail result = multiplier * cocktail;
    EXPECT_EQ(result.getName(), name);
    EXPECT_EQ(result.getAlcoholPercentage(), alc_percentage);
    EXPECT_EQ(result.getVolume(), vol * multiplier);
}

TEST(TCocktailTest, Dump) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);

    std::wostringstream out;
    cocktail.dump(out);
    EXPECT_EQ(out.str(), name + L" - " + std::to_wstring(std::lround(alc_percentage)) + L"%" + L" - " + std::to_wstring(std::lround(vol)) + L"ml");
}

TEST(TCocktailTest, OperatorLeftShift) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;
    TCocktail cocktail(name, alc_percentage, vol);

    std::wostringstream out;
    out << cocktail;
    EXPECT_EQ(out.str(), name + L" - " + std::to_wstring(std::lround(alc_percentage)) + L"%" + L" - " + std::to_wstring(std::lround(vol)) + L"ml");
}

TEST(TCocktailTest, Read) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;

    std::wistringstream in;
    in.str(name + L" " + std::to_wstring(alc_percentage) + L" " + std::to_wstring(vol));
    TCocktail cocktail;
    in >> cocktail;
    EXPECT_EQ(cocktail.getName(), name);
    EXPECT_EQ(cocktail.getAlcoholPercentage(), alc_percentage);
    EXPECT_EQ(cocktail.getVolume(), vol);
}

TEST(TCocktailTest, OperatorRightShiftStream) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;

    std::wistringstream in;
    in.str(name + L" " + std::to_wstring(alc_percentage) + L" " + std::to_wstring(vol));
    TCocktail cocktail;
    in >> cocktail;
    EXPECT_EQ(cocktail.getName(), name);
    EXPECT_EQ(cocktail.getAlcoholPercentage(), alc_percentage);
    EXPECT_EQ(cocktail.getVolume(), vol);
}

TEST(TCocktailTest, InvalidAlcoholPercentage) {
    std::wstring name = L"Cocktail";
    double alc_percentage = -50.;
    double vol = 100.;

    EXPECT_THROW(TCocktail(name, alc_percentage, vol), std::invalid_argument);
}

TEST(TCocktailTest, InvalidVolume) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = -100.;

    EXPECT_THROW(TCocktail(name, alc_percentage, vol), std::invalid_argument);
}

TEST(TCocktailTest, InvalidMultiplier) {
    std::wstring name = L"Cocktail";
    double alc_percentage = 50.;
    double vol = 100.;

    double multiplier = -2.;
    EXPECT_THROW(TCocktail(name, alc_percentage, vol) * multiplier, std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
