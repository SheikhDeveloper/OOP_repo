#include "gtest/gtest.h"
#include "../lib/headers/battleship.h"
#include "../lib/headers/weaponry.h"
#include "../lib/headers/captain_info.h"
#include "../lib/headers/aircraft_carrier.h"
#include "../lib/headers/aircraft_cruiser.h"
#include "../lib/headers/covering_ship.h"
#include "../lib/headers/plane.h"

TEST(TestCaptainInfo, TestDefaultConstructor) {
    TCaptainInfo c;
    EXPECT_EQ(c._name, "");
    EXPECT_EQ(c._rank, "");
    EXPECT_EQ(c._experience, 0);
}

TEST(TestCaptainInfo, TestConstructor) {
    TCaptainInfo c("Admiral", "Captain", 10);
    EXPECT_EQ(c._name, "Admiral");
    EXPECT_EQ(c._rank, "Captain");
    EXPECT_EQ(c._experience, 10);
}

TEST(TestWeaponry, TestDefaultConstructor) {
    TWeaponry w;
    EXPECT_EQ(w.getName(), "");
    EXPECT_EQ(w.getAmmoName(), "");
    EXPECT_EQ(w.getAmmoAmount(), 0);
    EXPECT_DOUBLE_EQ(w.getDamage(), 0);
    EXPECT_EQ(w.getType(), WeaponryType::light);
}

TEST(TestWeaponry, TestConstructor) {
    TWeaponry w("Weaponry", "Ammo", 10, 10.0, WeaponryType::heavy);
    EXPECT_EQ(w.getName(), "Weaponry");
    EXPECT_EQ(w.getAmmoName(), "Ammo");
    EXPECT_EQ(w.getAmmoAmount(), 10);
    EXPECT_DOUBLE_EQ(w.getDamage(), 10.0);
    EXPECT_EQ(w.getType(), WeaponryType::heavy);
}

TEST(TestWeaponry, TestCopyConstructor) {
    TWeaponry w("Weaponry", "Ammo", 10, 10.0, WeaponryType::heavy);
    TWeaponry w2(w);
    EXPECT_EQ(w.getName(), w2.getName());
    EXPECT_EQ(w.getAmmoName(), w2.getAmmoName());
    EXPECT_EQ(w.getAmmoAmount(), w2.getAmmoAmount());
    EXPECT_DOUBLE_EQ(w.getDamage(), w2.getDamage());
    EXPECT_EQ(w.getType(), w2.getType());
}

TEST(TestWeaponry, TestMoveConstructor) {
    TWeaponry w("Weaponry", "Ammo", 10, 10.0, WeaponryType::heavy);
    TWeaponry w2(std::move(w));
    EXPECT_EQ(w.getName(), "");
    EXPECT_EQ(w.getAmmoName(), "");
    EXPECT_EQ(w2.getName(), "Weaponry");
    EXPECT_EQ(w2.getAmmoName(), "Ammo");
    EXPECT_EQ(w2.getAmmoAmount(), 10);
    EXPECT_DOUBLE_EQ(w2.getDamage(), 10.0);
    EXPECT_EQ(w2.getType(), WeaponryType::heavy);
}

TEST(TestWeaponry, TestGettersAndSetters) {
    TWeaponry w;
    w.setName("Weaponry");
    w.setAmmoName("Ammo");
    w.setAmmoAmount(10);
    w.setDamage(10.0);
    w.setType(WeaponryType::heavy);
    EXPECT_EQ(w.getName(), "Weaponry");
    EXPECT_EQ(w.getAmmoName(), "Ammo");
    EXPECT_EQ(w.getAmmoAmount(), 10);
    EXPECT_DOUBLE_EQ(w.getDamage(), 10.0);
    EXPECT_EQ(w.getType(), WeaponryType::heavy);
}

TEST(TestWeaponry, TestCopyAssignment) {
    TWeaponry w("Weaponry", "Ammo", 10, 10.0, WeaponryType::heavy);
    TWeaponry w2;
    w2 = w;
    EXPECT_EQ(w.getName(), w2.getName());
    EXPECT_EQ(w.getAmmoName(), w2.getAmmoName());
    EXPECT_EQ(w.getAmmoAmount(), w2.getAmmoAmount());
    EXPECT_DOUBLE_EQ(w.getDamage(), w2.getDamage());
    EXPECT_EQ(w.getType(), w2.getType());
}

TEST(TestWeaponry, TestMoveAssignment) {
    TWeaponry w("Weaponry", "Ammo", 10, 10.0, WeaponryType::heavy);
    TWeaponry w2;
    w2 = std::move(w);
    EXPECT_EQ(w.getName(), "");
    EXPECT_EQ(w.getAmmoName(), "");
    EXPECT_EQ(w2.getName(), "Weaponry");
    EXPECT_EQ(w2.getAmmoName(), "Ammo");
    EXPECT_EQ(w2.getAmmoAmount(), 10);
    EXPECT_DOUBLE_EQ(w2.getDamage(), 10.0);
    EXPECT_EQ(w2.getType(), WeaponryType::heavy);
}

TEST(TestBattleship, TestDefaultConstructor) {
    TBattleship b;

    EXPECT_DOUBLE_EQ(b.getSurvivability(), 0);
    EXPECT_EQ(b.getWeaponry().getDamage(), 0);
    EXPECT_EQ(b.getCrewMembersAmount(), 0);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), 0);
    EXPECT_EQ(b.getName(), "");
    EXPECT_EQ(b.getCaptain()._experience, 0);
    EXPECT_EQ(b.getCaptain()._rank, "");
    EXPECT_EQ(b.getCaptain()._name, "");
}

TEST(TestBattleship, TestConstructor) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);

    EXPECT_DOUBLE_EQ(b.getSurvivability(), survivability);
    EXPECT_EQ(b.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(b.getWeaponry().getName(), w.getName());
    EXPECT_EQ(b.getWeaponry().getAmmoName(), w.getAmmoName());
    EXPECT_EQ(b.getWeaponry().getAmmoAmount(), w.getAmmoAmount());
    EXPECT_EQ(b.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b.getName(), name);
    EXPECT_EQ(b.getCaptain()._experience, c._experience);
    EXPECT_EQ(b.getCaptain()._rank, c._rank);
    EXPECT_EQ(b.getCaptain()._name, c._name);
}

TEST(TestBattleship, TestConstructorWithoutCaptainInfo) {
    std::string name = "Battleship";
    std::string rank = "Captain";
    size_t experience = 0;
    std::string captainName = "Captain";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, name, captainName, rank, experience, speed, survivability, crewMembersAmount, fuelUsage);

    EXPECT_DOUBLE_EQ(b.getSurvivability(), survivability);
    EXPECT_EQ(b.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(b.getWeaponry().getName(), w.getName());
    EXPECT_EQ(b.getWeaponry().getAmmoName(), w.getAmmoName());
    EXPECT_EQ(b.getWeaponry().getAmmoAmount(), w.getAmmoAmount());
    EXPECT_EQ(b.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b.getName(), name);
    EXPECT_EQ(b.getCaptain()._experience, experience);
    EXPECT_EQ(b.getCaptain()._rank, rank);
    EXPECT_EQ(b.getCaptain()._name, captainName);
}

TEST(TestBattleship, TestCopyConstructor) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    TBattleship b2(b);

    EXPECT_DOUBLE_EQ(b.getSurvivability(), b2.getSurvivability());
    EXPECT_EQ(b.getWeaponry().getDamage(), b2.getWeaponry().getDamage());
    EXPECT_EQ(b.getWeaponry().getName(), b2.getWeaponry().getName());
    EXPECT_EQ(b.getWeaponry().getAmmoName(), b2.getWeaponry().getAmmoName());
    EXPECT_EQ(b.getWeaponry().getAmmoAmount(), b2.getWeaponry().getAmmoAmount());
    EXPECT_EQ(b.getCrewMembersAmount(), b2.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b.getName(), name);
    EXPECT_EQ(b.getCaptain()._experience, c._experience);
    EXPECT_EQ(b.getCaptain()._rank, c._rank);
    EXPECT_EQ(b.getCaptain()._name, c._name);
}

TEST(TestBattleship, TestMoveConstructor) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    TBattleship b2(std::move(b));

    EXPECT_DOUBLE_EQ(b.getSurvivability(), b2.getSurvivability());
    EXPECT_EQ(w.getDamage(), b2.getWeaponry().getDamage());
    EXPECT_EQ(w.getName(), b2.getWeaponry().getName());
    EXPECT_EQ(w.getAmmoName(), b2.getWeaponry().getAmmoName());
    EXPECT_EQ(w.getAmmoAmount(), b2.getWeaponry().getAmmoAmount());
    EXPECT_EQ(crewMembersAmount, b2.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(speed, b2.getSpeed());
    EXPECT_DOUBLE_EQ(b2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b2.getName(), name);
    EXPECT_EQ(b2.getCaptain()._experience, c._experience);
    EXPECT_EQ(b2.getCaptain()._rank, c._rank);
    EXPECT_EQ(b2.getCaptain()._name, c._name);
}

TEST(TestBattleship, TestGettersAndSetters) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);

    double newSurvivability = 0.3;
    double newFuelUsage = 0.3;
    size_t newCrewMembersAmount = 0;
    double newSpeed = 0;
    TCaptainInfo newCaptainInfo("Captain", "Captain", 0);
    b.setSurvivability(newSurvivability);
    b.setFuelUsage(newFuelUsage);
    b.setCrewMembersAmount(newCrewMembersAmount);
    b.setSpeed(newSpeed);
    b.setCaptain(newCaptainInfo);
    EXPECT_EQ(b.getCaptain()._experience, newCaptainInfo._experience);
    EXPECT_EQ(b.getCaptain()._rank, newCaptainInfo._rank);
    EXPECT_EQ(b.getCaptain()._name, newCaptainInfo._name);
    std::string another_cap_name = "Captain2";
    std::string another_cap_rank = "Captain2";
    size_t another_cap_exp = 0;
    b.setCaptain(another_cap_name, another_cap_rank, another_cap_exp);
    EXPECT_EQ(b.getCaptain()._experience, another_cap_exp);
    EXPECT_EQ(b.getCaptain()._rank, another_cap_rank);
    EXPECT_EQ(b.getCaptain()._name, another_cap_name);
    EXPECT_EQ(b.getName(), name);

    EXPECT_DOUBLE_EQ(b.getSurvivability(), newSurvivability);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), newFuelUsage);
    EXPECT_EQ(b.getCrewMembersAmount(), newCrewMembersAmount);
    EXPECT_DOUBLE_EQ(b.getSpeed(), newSpeed);
    EXPECT_EQ(b.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(b.getWeaponry().getName(), w.getName());
    EXPECT_EQ(b.getWeaponry().getAmmoName(), w.getAmmoName());
}

TEST(TestBattleship, TestMaxDistanceCalculation) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    EXPECT_DOUBLE_EQ(b.calcMaxDistance(100), 200);

    double newSurvivability = 0.3;
    double newFuelUsage = 25.;
    size_t newCrewMembersAmount = 0;
    double newSpeed = 0;
    TCaptainInfo newCaptainInfo("Captain", "Captain", 0);
    b.setSurvivability(newSurvivability);
    b.setFuelUsage(newFuelUsage);
    b.setCrewMembersAmount(newCrewMembersAmount);
    b.setSpeed(newSpeed);
    b.setCaptain(newCaptainInfo);
    EXPECT_DOUBLE_EQ(b.calcMaxDistance(100), 4);
}

TEST(TestBattleship, TestCoppyAssignment) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    TBattleship b2 = b;
    EXPECT_EQ(b2.getName(), name);
    EXPECT_EQ(b2.getSurvivability(), survivability);
    EXPECT_EQ(b2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_EQ(b2.getSpeed(), speed);
    EXPECT_EQ(b2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(b2.getCaptain()._name, c._name);
    EXPECT_EQ(b2.getCaptain()._rank, c._rank);
    EXPECT_EQ(b2.getCaptain()._experience, c._experience);
}

TEST(TestBattleship, TestMoveAssignment) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    TBattleship b2 = std::move(b);
    EXPECT_EQ(b2.getName(), name);
    EXPECT_DOUBLE_EQ(b2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(b2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(b2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(b2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(b2.getCaptain()._name, c._name);
    EXPECT_EQ(b2.getCaptain()._rank, c._rank);
    EXPECT_EQ(b2.getCaptain()._experience, c._experience);
}

TEST(TestBattleship, TestExceptions) {
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    EXPECT_THROW(TBattleship(w, c, "Name", -1, survivability, crewMembersAmount, fuelUsage), std::logic_error);
    EXPECT_THROW(TBattleship(w, c, "Name", speed, -1, crewMembersAmount, fuelUsage), std::logic_error);
    EXPECT_THROW(TBattleship(w, c, "Name", speed, survivability, crewMembersAmount, -1), std::logic_error);
    TBattleship b(w, c, "Name", speed, survivability, crewMembersAmount, fuelUsage);
    EXPECT_THROW(b.setSpeed(-1), std::logic_error);
    EXPECT_THROW(b.setSurvivability(-1), std::logic_error);
    EXPECT_THROW(b.setFuelUsage(-1), std::logic_error);
}

TEST(TestCoveringShip, TestDefaultConstructor) {
    TCoveringShip c;
    EXPECT_EQ(c.getShipToCover().getSurvivability(), 0);
    EXPECT_EQ(c.getShipToCover().getWeaponry().getDamage(), 0);
    EXPECT_EQ(c.getShipToCover().getCrewMembersAmount(), 0);
    EXPECT_EQ(c.getShipToCover().getSpeed(), 0);
    EXPECT_EQ(c.getShipToCover().getFuelUsage(), 0);
    EXPECT_EQ(c.getShipToCover().getName(), "");
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, 0);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank, "");
    EXPECT_EQ(c.getShipToCover().getCaptain()._name, "");
}

TEST(TestCoveringShip, TestConstructor) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    double fuelUsage = 0.5; 
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSurvivability(), b.getSurvivability());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getWeaponry().getDamage(), b.getWeaponry().getDamage());
    EXPECT_EQ(c.getShipToCover().getCrewMembersAmount(), b.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSpeed(), b.getSpeed());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getFuelUsage(), b.getFuelUsage());
    EXPECT_EQ(c.getShipToCover().getName(), b.getName());
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, b.getCaptain()._experience);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank, b.getCaptain()._rank);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name, b.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c.getCaptain()._name, captainName);
    EXPECT_EQ(c.getCaptain()._rank, captainRank);
    EXPECT_EQ(c.getCaptain()._experience, experience);
}

TEST(TestCoveringShip, TestCopyConstructor) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    double fuelUsage = 0.5; 
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    TCoveringShip c2(c);
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSurvivability(), b.getSurvivability());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getWeaponry().getDamage(), b.getWeaponry().getDamage());
    EXPECT_EQ(c2.getShipToCover().getCrewMembersAmount(), b.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSpeed(), b.getSpeed());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getFuelUsage(), b.getFuelUsage());
    EXPECT_EQ(c2.getShipToCover().getName(), b.getName());
    EXPECT_EQ(c2.getShipToCover().getCaptain()._experience, b.getCaptain()._experience);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank, b.getCaptain()._rank);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name, b.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c2.getCaptain()._name, captainName);
    EXPECT_EQ(c2.getCaptain()._rank, captainRank);

}

TEST(TestCoveringShip, TestMoveConstructor) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    double fuelUsage = 0.5; 
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    TCoveringShip c2(std::move(c));
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSurvivability(), b.getSurvivability());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getWeaponry().getDamage(), b.getWeaponry().getDamage());
    EXPECT_EQ(c.getShipToCover().getCrewMembersAmount(), b.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSpeed(), b.getSpeed());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getFuelUsage(), b.getFuelUsage());
    EXPECT_EQ(c.getShipToCover().getName(), b.getName());
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, b.getCaptain()._experience);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank, b.getCaptain()._rank);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name, b.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c.getCaptain()._name, captainName);
    EXPECT_EQ(c.getCaptain()._rank, captainRank);
}

TEST(TestCoveringShip, TestGettersAndSetters) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, 0.5);
    std::string b2Name = "Name2";
    TBattleship b2(w, TCaptainInfo(" ", " ", 0), b2Name, 0.5, 0.5, 0, 0);
    c.setShipToCover(b2);
    c.setWeaponryDamage(3.2);
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSurvivability(), b2.getSurvivability());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getWeaponry().getDamage(), b2.getWeaponry().getDamage());
    EXPECT_EQ(c.getShipToCover().getCrewMembersAmount(), b2.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSpeed(), b2.getSpeed());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getFuelUsage(), b2.getFuelUsage());
    EXPECT_EQ(c.getShipToCover().getName(), b2.getName());
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, b2.getCaptain()._experience);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank, b2.getCaptain()._rank);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name, b2.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c.getWeaponryDamage(), 3.2);
    
}

TEST(TestCoveringShip, CopyAssignment) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, 0.5);
    TCoveringShip c2 = c;
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSurvivability(), b.getSurvivability());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getWeaponry().getDamage(), b.getWeaponry().getDamage());
    EXPECT_EQ(c2.getShipToCover().getCrewMembersAmount(), b.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSpeed(), b.getSpeed());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getFuelUsage(), b.getFuelUsage());
    EXPECT_EQ(c2.getShipToCover().getName(), b.getName());
    EXPECT_EQ(c2.getShipToCover().getCaptain()._experience, b.getCaptain()._experience);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank, b.getCaptain()._rank);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name, b.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), 0.5);
    EXPECT_EQ(c2.getCaptain()._name, captainName);
    EXPECT_EQ(c2.getCaptain()._rank, captainRank);

}

TEST(TestCoveringShip, MoveAssignment) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, 0.5);
    TCoveringShip c2 = std::move(c);
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSurvivability(), b.getSurvivability());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getWeaponry().getDamage(), b.getWeaponry().getDamage());
    EXPECT_EQ(c2.getShipToCover().getCrewMembersAmount(), b.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getSpeed(), b.getSpeed());
    EXPECT_DOUBLE_EQ(c2.getShipToCover().getFuelUsage(), b.getFuelUsage());
    EXPECT_EQ(c2.getShipToCover().getName(), b.getName());
    EXPECT_EQ(c2.getShipToCover().getCaptain()._experience, b.getCaptain()._experience);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank, b.getCaptain()._rank);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name, b.getCaptain()._name);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), 0.5);
    EXPECT_EQ(c2.getCaptain()._name, captainName);
    EXPECT_EQ(c2.getCaptain()._rank, captainRank);

}

TEST(TestAircraftCarrier, TestDefaultConstructor) {
    TAircraftCarrier a;
    EXPECT_EQ(a.getWeaponry().getDamage(), 0);
    EXPECT_EQ(a.getSurvivability(), 0);
    EXPECT_EQ(a.getFuelUsage(), 0);
    EXPECT_EQ(a.getName(), "");
    EXPECT_EQ(a.getCrewMembersAmount(), 0);
    EXPECT_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestConstructor) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 0.5);
    EXPECT_EQ(a.getName(), "Name");
    EXPECT_EQ(a.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestCopyConstructor) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TAircraftCarrier a2(a);
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0.5);
    EXPECT_EQ(a2.getName(), "Name");
    EXPECT_EQ(a2.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), 0);
    EXPECT_EQ(a2.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestMoveConstructor) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TAircraftCarrier a2(std::move(a));
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0.5);
    EXPECT_EQ(a2.getName(), "Name");
    EXPECT_EQ(a2.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), 0);
    EXPECT_EQ(a2.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestGettersAndSetters) {
    TPlaneGroup planes;
    TWeaponry w1(" ", " ", 10, 1.3, WeaponryType::light);
    TAircraftCarrier a(w1, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TWeaponry w2("w2", "22.5mm", 5, 1.5, WeaponryType::light);
    TWeaponry w3("w3", "25.5mm", 10, 2.5, WeaponryType::heavy);
    a.setWeaponry(w2);
    TPlaneGroup planes2;
    TPlane p("Plane", w3, 0.5, 0.5, TPlaneType::bomber);
    planes2.addPlane(p);
    a.setPlaneInfo(planes2);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w2.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 0.5);
    EXPECT_EQ(a.getName(), "Name");
    EXPECT_EQ(a.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCarrier, TestAddPlane) {
    TPlaneGroup planes;
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TPlane p("Plane", w, 0.5, 0.5, TPlaneType::bomber);
    a.addPlane(p);
    EXPECT_EQ(a.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCarrier, TestDamageCalculation) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    EXPECT_DOUBLE_EQ(a.calcPlaneDamage(), 0);
}

TEST(TestAircraftCarrier, TestCopyAssignment) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TAircraftCarrier a2;
    a2 = a;
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0.5);
    EXPECT_EQ(a2.getName(), "Name");
    EXPECT_EQ(a2.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), 0);
    EXPECT_EQ(a2.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestMoveAssignment) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TAircraftCarrier a2;
    a2 = std::move(a);
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0.5);
    EXPECT_EQ(a2.getName(), "Name");
    EXPECT_EQ(a2.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), 0);
    EXPECT_EQ(a2.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCruiser, TestDefaultConstructor) {
    TAircraftCarryingCruiser a;

    EXPECT_DOUBLE_EQ(a.TCoveringShip::getWeaponry().getDamage(), 0);
    EXPECT_DOUBLE_EQ(a.TCoveringShip::getSurvivability(), 0);
    EXPECT_DOUBLE_EQ(a.TCoveringShip::getFuelUsage(), 0);
    EXPECT_EQ(a.TAircraftCarrier::getName(), "");
    EXPECT_EQ(a.TAircraftCarrier::getCrewMembersAmount(), 0);
    EXPECT_DOUBLE_EQ(a.TAircraftCarrier::getSpeed(), 0); 
    EXPECT_EQ(a.getShipToCover().getName(), "");
    EXPECT_EQ(a.getShipToCover().getCrewMembersAmount(), 0);
    EXPECT_DOUBLE_EQ(a.getShipToCover().getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCruiser, TestConstructor) {
    std::string name = "Name";
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 10;
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double fuelUsage = 0.5;
    double survivability = 0.5;
    size_t crewMembersAmount = 10;
    double speed = 0;
    TPlaneGroup planes;
    TPlane p("Plane", w, 0.5, 0.5, TPlaneType::bomber);
    planes.addPlane(p);
    TBattleship shipToCover;
    TAircraftCarryingCruiser a(w, planes, shipToCover, name, captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), fuelUsage);
    EXPECT_EQ(a.getName(), name);
    EXPECT_EQ(a.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(a.getSpeed(), speed);
    EXPECT_EQ(a.getShipToCover().getName(), shipToCover.getName());
    EXPECT_EQ(a.getShipToCover().getCrewMembersAmount(), shipToCover.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(a.getShipToCover().getSpeed(), shipToCover.getSpeed());
    EXPECT_EQ(a.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCruiser, TestCopyConstructor) {
    std::string name = "Name";
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 10;
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double fuelUsage = 0.5;
    double survivability = 0.5;
    size_t crewMembersAmount = 10;
    double speed = 0;
    TPlaneGroup planes;
    TPlane p("Plane", w, 0.5, 0.5, TPlaneType::bomber);
    planes.addPlane(p);
    TBattleship shipToCover;
    TAircraftCarryingCruiser a(w, planes, shipToCover, name, captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    TAircraftCarryingCruiser a2(a);
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(a2.getName(), name);
    EXPECT_EQ(a2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), speed);
    EXPECT_EQ(a2.getShipToCover().getName(), shipToCover.getName());
    EXPECT_EQ(a2.getShipToCover().getCrewMembersAmount(), shipToCover.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(a2.getShipToCover().getSpeed(), shipToCover.getSpeed());
    EXPECT_EQ(a2.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCruiser, TestMoveConstructor) {
    std::string name = "Name";
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 10;
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double fuelUsage = 0.5;
    double survivability = 0.5;
    size_t crewMembersAmount = 10;
    double speed = 0;
    TPlaneGroup planes;
    TPlane p("Plane", w, 0.5, 0.5, TPlaneType::bomber);
    planes.addPlane(p);
    TBattleship shipToCover;
    TAircraftCarryingCruiser a(w, planes, shipToCover, name, captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage);
    TAircraftCarryingCruiser a2(std::move(a));
    EXPECT_DOUBLE_EQ(a2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(a2.getName(), name);
    EXPECT_EQ(a2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), speed);
    EXPECT_EQ(a2.getShipToCover().getName(), shipToCover.getName());
    EXPECT_EQ(a2.getShipToCover().getCrewMembersAmount(), shipToCover.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(a2.getShipToCover().getSpeed(), shipToCover.getSpeed());
    EXPECT_EQ(a2.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCruiser, TestMoveAssignment) {
    TWeaponry w;
    TPlaneGroup planes;
    TBattleship shipToCover;
    TAircraftCarryingCruiser a(w, planes, shipToCover, "Name", "Captain", "Captain rank", 5, 3., 2., 2, 10.);
    TAircraftCarryingCruiser b;
    b = std::move(a);

    EXPECT_EQ(b.getPlaneInfo().size(), 0);
    EXPECT_EQ(b.getName(), "Name");
    EXPECT_EQ(b.getCrewMembersAmount(), 2);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 2.);
    EXPECT_DOUBLE_EQ(b.getSurvivability(), 3.);
    EXPECT_DOUBLE_EQ(b.getWeaponry().getDamage(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), 10.);
}

TEST(TestAircraftCruiser, TestCopyAssignment) {
    TWeaponry w;
    TPlaneGroup planes;
    TPlane p1;
    planes.addPlane(p1);
    TBattleship shipToCover;
    TAircraftCarryingCruiser a(w, planes, shipToCover, "Name", "Captain", "Captain rank", 5, 3., 2., 2, 10.);
    TAircraftCarryingCruiser b;
    b = a;

    EXPECT_EQ(a.getPlaneInfo().size(), 1);
    EXPECT_EQ(b.getPlaneInfo().size(), 1);

    EXPECT_EQ(a.getName(), "Name");
    EXPECT_EQ(b.getName(), "Name");

    EXPECT_EQ(a.getCrewMembersAmount(), 2);
    EXPECT_EQ(b.getCrewMembersAmount(), 2);

    EXPECT_DOUBLE_EQ(a.getSpeed(), 2.);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 2.);

    EXPECT_EQ(a.getSurvivability(), 3.);
    EXPECT_EQ(b.getSurvivability(), 3.);

    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), 0);
    EXPECT_DOUBLE_EQ(b.getWeaponry().getDamage(), 0);

    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 10.);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), 10.);
}

TEST(TestPlane, TestDefaultConstructor) {
    TPlane p;

    EXPECT_EQ(p.getWeaponry().getDamage(), 0);
    EXPECT_EQ(p.getSurvivability(), 0);
    EXPECT_EQ(p.getFuelUsage(), 0);
    EXPECT_EQ(p.getName(), "");
}

TEST(TestPlane, TestConstructor) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);

    EXPECT_EQ(p.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(p.getSurvivability(), survivability);
    EXPECT_EQ(p.getFuelUsage(), fuelUsage);
    EXPECT_EQ(p.getName(), name);
    EXPECT_EQ(p.getType(), TPlaneType::bomber);
}

TEST(TestPlane, TestCopyConstructor) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    TPlane q(p);

    EXPECT_EQ(q.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(q.getSurvivability(), survivability);
    EXPECT_EQ(q.getFuelUsage(), fuelUsage);
    EXPECT_EQ(q.getName(), name);
    EXPECT_EQ(q.getType(), TPlaneType::bomber);
}

TEST(TestPlane, TestMoveConstructor) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    TPlane q(std::move(p));

    EXPECT_EQ(q.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(q.getSurvivability(), survivability);
    EXPECT_EQ(q.getFuelUsage(), fuelUsage);
    EXPECT_EQ(q.getName(), name);
    EXPECT_EQ(q.getType(), TPlaneType::bomber);
}

TEST(TestPlane, TestGettersAndSetters) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::fighter);
    TWeaponry w2;
    double survivability2 = 0.5;
    double fuelUsage2 = 0.5;
    p.setWeaponry(w2);
    p.setWeaponryType(WeaponryType::heavy);
    p.setSurvivability(survivability2);
    p.setFuelUsage(fuelUsage2);
    p.setName(name);
    p.setType(TPlaneType::bomber);
    EXPECT_EQ(p.getWeaponry().getDamage(), w2.getDamage());
    EXPECT_EQ(p.getWeaponry().getType(), WeaponryType::heavy);
    EXPECT_EQ(p.getSurvivability(), survivability2);
    EXPECT_EQ(p.getFuelUsage(), fuelUsage2);
    EXPECT_EQ(p.getName(), name);
    EXPECT_EQ(p.getType(), TPlaneType::bomber);
}

TEST(TestPlane, TestExceptions) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    TWeaponry wLight;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    EXPECT_THROW(TPlane p(name, wLight, survivability, fuelUsage, TPlaneType::bomber), std::logic_error);
    w.setType(WeaponryType::heavy);
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    EXPECT_THROW(p.setWeaponryType(WeaponryType::light), std::logic_error);
    EXPECT_THROW(p.setSurvivability(-1), std::logic_error);
    EXPECT_THROW(p.setFuelUsage(-1), std::logic_error);
    TWeaponry w2;
    EXPECT_THROW(p.setWeaponry(w2), std::logic_error);
}

TEST(TestPlane, CopyAssignment) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    TPlane q = p;
    EXPECT_EQ(q.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(q.getSurvivability(), survivability);
    EXPECT_EQ(q.getFuelUsage(), fuelUsage);
    EXPECT_EQ(q.getName(), name);
    EXPECT_EQ(q.getType(), TPlaneType::bomber);
}

TEST(TestPlane, MoveAssignment) {
    std::string name = "Plane";
    TWeaponry w;
    w.setType(WeaponryType::heavy);
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    TPlane q = std::move(p);
    EXPECT_EQ(q.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(q.getSurvivability(), survivability);
    EXPECT_EQ(q.getFuelUsage(), fuelUsage);
    EXPECT_EQ(q.getName(), name);
    EXPECT_EQ(q.getType(), TPlaneType::bomber);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
