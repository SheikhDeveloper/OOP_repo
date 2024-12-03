#include "gtest/gtest.h"
#include "../lib/headers/battleship_group.h"
#include "../lib/headers/plane_group.h"

TEST(TestBattleshipGroup, TestDefaultConstructor) {
    TBattleshipGroup b;

    EXPECT_EQ(b.getAdmiralInfo()._name, "");
    EXPECT_EQ(b.getAdmiralInfo()._rank, "");
    EXPECT_EQ(b.getAdmiralInfo()._experience, 0);
    EXPECT_EQ(b.getStartingPoint(), "");
    EXPECT_EQ(b.getDestination(), "");
    EXPECT_EQ(b.getDistance(), 0);
}

TEST(TestBattleshipGroup, TestConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);

    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), startingPoint);
    EXPECT_EQ(b.getDestination(), destination);
    EXPECT_EQ(b.getDistance(), distance);
}

TEST(TestBattleshipGroup, TestVectorConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    std::vector<TBattleship> v;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance, v);
    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), startingPoint);
    EXPECT_EQ(b.getDestination(), destination);
    EXPECT_EQ(b.getDistance(), distance);
}

TEST(TestBattleshipGroup, TestCaptainInfoConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    TCaptainInfo c(admiralName, admiralRank, admiralExperience);
    TBattleshipGroup b(c, "Earth", "Mars", 1000);
    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), "Earth");
    EXPECT_EQ(b.getDestination(), "Mars");
    EXPECT_EQ(b.getDistance(), 1000);
}

TEST(TestBattleshipGroup, TestCaptainInfoVectorConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    TCaptainInfo c(admiralName, admiralRank, admiralExperience);
    std::vector<TBattleship> v;
    TBattleshipGroup b(c, "Earth", "Mars", 1000, v);
    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), "Earth");
    EXPECT_EQ(b.getDestination(), "Mars");
    EXPECT_EQ(b.getDistance(), 1000);
}

TEST(TestBattleshipGroup, TestGetters) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), startingPoint);
    EXPECT_EQ(b.getDestination(), destination);
    EXPECT_EQ(b.getDistance(), distance);
}

TEST(TestBattleshipGroup, TestSetters) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b;
    auto admiral = TCaptainInfo(admiralName, admiralRank, admiralExperience);
    b.setAdmiral(admiral);
    b.setStartingPoint(startingPoint);
    b.setDestination(destination);
    b.setDistance(distance);
    EXPECT_EQ(b.getAdmiralInfo()._name, admiralName);
    EXPECT_EQ(b.getAdmiralInfo()._rank, admiralRank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, admiralExperience);
    EXPECT_EQ(b.getStartingPoint(), startingPoint);
    EXPECT_EQ(b.getDestination(), destination);
    EXPECT_EQ(b.getDistance(), distance);
}

TEST(TestBattleshipGroup, TestPlaneRelocation) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TAircraftCarrier c1, c2;
    TWeaponry w1;
    TPlane b1("bomber", std::move(w1), 10., 10., TPlaneType::fighter);
    c1.addPlane(b1);
    b.relocatePlane("bomber", TPlaneType::fighter, c1.getName(), c2.getName());
    auto &c2Planes = c2.getPlaneInfo();
    auto &c1Planes = c1.getPlaneInfo();
    EXPECT_EQ(c1Planes.size(), 1);
    EXPECT_EQ(c2Planes.size(), 0);
    std::string planeName = "bomber";
    std::string c1PlaneName = c1.getPlaneInfo().getPlane(planeName, TPlaneType::fighter).getName();
    EXPECT_EQ(c1PlaneName, planeName);
}

TEST(TestBattleshipGroup, TestCopyConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TBattleshipGroup b2(b);
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
}

TEST(TestBattleshipGroup, TestMoveConstructor) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TBattleshipGroup b2(std::move(b));
    EXPECT_EQ(admiralName, b2.getAdmiralInfo()._name);
    EXPECT_EQ(admiralRank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(admiralExperience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(startingPoint, b2.getStartingPoint());
    EXPECT_EQ(destination, b2.getDestination());
    EXPECT_EQ(distance, b2.getDistance());
}

TEST(TestBattleshipGroup, TestCopyAssignment) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TBattleshipGroup b2;
    b2 = b;
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
}

TEST(TestBattleshipGroup, TestMoveAssignment) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TBattleshipGroup b2;
    b2 = std::move(b);
    EXPECT_EQ(admiralName, b2.getAdmiralInfo()._name);
    EXPECT_EQ(admiralRank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(admiralExperience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(startingPoint, b2.getStartingPoint());
    EXPECT_EQ(destination, b2.getDestination());
    EXPECT_EQ(distance, b2.getDistance());
}

TEST(TestBattleshipGroup, TestAttackSimulation) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    TBattleship ship1(TWeaponry(),TCaptainInfo(), "Name", 3., 5., 10, 7.);
    b.addBattleship(ship1);
    TBattleship ship2(TWeaponry(),TCaptainInfo(), "Name2", 3., 5., 10, 7.);
    b.addBattleship(ship2);
    TPlaneGroup attackers;
    TWeaponry w1;
    w1.setType(WeaponryType::heavy);
    w1.setDamage(10.);
    TPlane p1("bomber", std::move(w1), 10., 10., TPlaneType::bomber);
    attackers.addPlane(p1);
    b.simulateAttack(attackers);
    EXPECT_EQ(b.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
