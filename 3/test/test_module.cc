#include "gtest/gtest.h"
#include "../lib/headers/battleship_group.h"

TEST(TestBattleship, TestDefaultConstructor) {
    TBattleship b;

    EXPECT_DOUBLE_EQ(b.getSurvivability(), 0);
    EXPECT_EQ(b.getWeaponry().getDamage(), 0);
    EXPECT_EQ(b.getCrewMembersAmount(), 0);
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), 0);
    EXPECT_EQ(b.getName(), "");
    EXPECT_EQ(b.getCaptain()._experience, 0);
    EXPECT_EQ(b.getCaptain()._rank[0], 0);
    EXPECT_EQ(b.getCaptain()._name[0], 0);
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
    EXPECT_EQ(b.getCaptain()._rank[0], c._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], c._name[0]);
}

TEST(TestBattleship, TestConstructorWithoutCaptainInfo) {
    TCaptainInfo c;
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
    EXPECT_EQ(b.getCaptain()._experience, c._experience);
    EXPECT_EQ(b.getCaptain()._rank[0], c._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], c._name[0]);
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
    EXPECT_EQ(b.getCaptain()._rank[0], c._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], c._name[0]);
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
    EXPECT_EQ(b.getWeaponry().getDamage(), b2.getWeaponry().getDamage());
    EXPECT_EQ(b.getWeaponry().getName(), b2.getWeaponry().getName());
    EXPECT_EQ(b.getWeaponry().getAmmoName(), b2.getWeaponry().getAmmoName());
    EXPECT_EQ(b.getWeaponry().getAmmoAmount(), b2.getWeaponry().getAmmoAmount());
    EXPECT_EQ(b.getCrewMembersAmount(), b2.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(b.getSpeed(), 0);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), fuelUsage);
    EXPECT_EQ(b.getName(), name);
    EXPECT_EQ(b.getCaptain()._experience, c._experience);
    EXPECT_EQ(b.getCaptain()._rank[0], c._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], c._name[0]);
}

TEST(TestBattleship, TestGetters) {
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
    EXPECT_EQ(b.getCaptain()._rank[0], c._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], c._name[0]);
}

TEST(TestBattleship, TestSetters) {
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
    EXPECT_EQ(b.getCaptain()._rank[0], newCaptainInfo._rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], newCaptainInfo._name[0]);
    std::string another_cap_name = "Captain2";
    std::string another_cap_rank = "Captain2";
    size_t another_cap_exp = 0;
    b.setCaptain(another_cap_name, another_cap_rank, another_cap_exp);
    EXPECT_EQ(b.getCaptain()._experience, another_cap_exp);
    EXPECT_EQ(b.getCaptain()._rank[0], another_cap_rank[0]);
    EXPECT_EQ(b.getCaptain()._name[0], another_cap_name[0]);
    b.setName("Battleship2");
    std::string new_name = "Battleship2";
    for (size_t i = 0; i < new_name.size(); i++) {
        EXPECT_EQ(b.getName()[i], new_name[i]);
    }

    EXPECT_DOUBLE_EQ(b.getSurvivability(), newSurvivability);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), newFuelUsage);
    EXPECT_EQ(b.getCrewMembersAmount(), newCrewMembersAmount);
    EXPECT_DOUBLE_EQ(b.getSpeed(), newSpeed);
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

TEST(TestBattleship, TestDump) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    std::stringstream ss;

    b.dump(ss);
    std::string expected = "Name: Battleship\n"
                           "Speed: 0.0\n"
                           "Survivability: 0.5\n"
                           "Crew members amount: 0\n"
                           "Weaponry: \n"
                           "Fuel usage: 0.5\n"
                           "Captain: \n";
    std::string got = ss.str();
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(expected[i], got[i]);
    }
}

TEST(TestBattleship, TestRead) {
    std::string name = "Battleship";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TCaptainInfo c;
    size_t crewMembersAmount = 0;
    double speed = 0;
    TBattleship b(w, c, name, speed, survivability, crewMembersAmount, fuelUsage);
    std::stringstream ss;
    ss << "Battleship\n"
       << "0.0\n"
       << "0.5\n"
       << "0\n"
       << "\n"
       << "0.5\n"
       << "\n";
    b.read(ss);
    EXPECT_EQ(b.getName(), name);
    EXPECT_DOUBLE_EQ(b.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(b.getFuelUsage(), fuelUsage);
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
    EXPECT_EQ(b2.getCaptain()._name[0], c._name[0]);
    EXPECT_EQ(b2.getCaptain()._rank[0], c._rank[0]);
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
    EXPECT_EQ(b2.getCaptain()._name[0], c._name[0]);
    EXPECT_EQ(b2.getCaptain()._rank[0], c._rank[0]);
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
    EXPECT_EQ(c.getShipToCover().getName()[0], ""[0]);
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, 0);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank[0], 0);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name[0], 0);
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
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank[0], b.getCaptain()._rank[0]);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name[0], b.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c.getCaptain()._name[0], captainName[0]);
    EXPECT_EQ(c.getCaptain()._rank[0], captainRank[0]);
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
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank[0], b.getCaptain()._rank[0]);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name[0], b.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c2.getCaptain()._name[0], captainName[0]);
    EXPECT_EQ(c2.getCaptain()._rank[0], captainRank[0]);

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
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank[0], b.getCaptain()._rank[0]);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name[0], b.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c.getFuelUsage(), fuelUsage);
    EXPECT_EQ(c.getCaptain()._name[0], captainName[0]);
    EXPECT_EQ(c.getCaptain()._rank[0], captainRank[0]);
}

TEST(TestCoveringShip, TestGetters) {
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
    EXPECT_DOUBLE_EQ(c.getWeaponryDamage(), w.getDamage());
    TBattleship b2 = c.getShipToCover();
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSurvivability(), b2.getSurvivability());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getWeaponry().getDamage(), b2.getWeaponry().getDamage());
    EXPECT_EQ(c.getShipToCover().getCrewMembersAmount(), b2.getCrewMembersAmount());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getSpeed(), b2.getSpeed());
    EXPECT_DOUBLE_EQ(c.getShipToCover().getFuelUsage(), b2.getFuelUsage());
    std::string cCoverName = c.getShipToCover().getName();
    std::string b2Name = b2.getName();
    EXPECT_EQ(cCoverName.size(), b2Name.size());
    for (size_t i = 0; i < cCoverName.size(); ++i) {
        EXPECT_EQ(cCoverName[i], b2Name[i]);
    }
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, b2.getCaptain()._experience);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank[0], b2.getCaptain()._rank[0]);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name[0], b2.getCaptain()._name[0]);

}

TEST(TestCoveringShip, TestSetters) {
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
    std::string cCoverName = c.getShipToCover().getName();
    std::string b2Name2 = b2.getName();
    EXPECT_EQ(cCoverName.size(), b2Name2.size());
    for (size_t i = 0; i < cCoverName.size(); ++i) {
        EXPECT_EQ(cCoverName[i], b2Name2[i]);
    }
    EXPECT_EQ(c.getShipToCover().getCaptain()._experience, b2.getCaptain()._experience);
    EXPECT_EQ(c.getShipToCover().getCaptain()._rank[0], b2.getCaptain()._rank[0]);
    EXPECT_EQ(c.getShipToCover().getCaptain()._name[0], b2.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c.getWeaponryDamage(), 3.2);
    
}

TEST(TestCoveringShip, TestDump) {
    TBattleship b;
    TWeaponry w;
    std::string captainName = "Captain";
    std::string captainRank = "Captain rank";
    size_t experience = 0;
    double survivability = 0.5;
    double speed = 0;
    size_t crewMembersAmount = 0;
    TCoveringShip c(b, w, "Name", captainName, captainRank, experience, survivability, speed, crewMembersAmount, 0.5);
    std::stringstream out;
    c.dump(out);
    std::string expected = "Name: Battleship\n"
                           "Speed: 0.0\n"
                           "Survivability: 0.5\n"
                           "Crew members amount: 0\n"
                           "Weaponry: \n"
                           "Fuel usage: 0.5\n"
                           "Captain: \n"
                           "Ship to cover: \n";
    std::string actual = out.str();
    EXPECT_EQ(expected.size(), actual.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i], actual[i]);
    }

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
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank[0], b.getCaptain()._rank[0]);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name[0], b.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), 0.5);
    EXPECT_EQ(c2.getCaptain()._name[0], captainName[0]);
    EXPECT_EQ(c2.getCaptain()._rank[0], captainRank[0]);

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
    EXPECT_EQ(c2.getShipToCover().getCaptain()._rank[0], b.getCaptain()._rank[0]);
    EXPECT_EQ(c2.getShipToCover().getCaptain()._name[0], b.getCaptain()._name[0]);
    EXPECT_DOUBLE_EQ(c2.getSurvivability(), survivability);
    EXPECT_DOUBLE_EQ(c2.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(c2.getCrewMembersAmount(), crewMembersAmount);
    EXPECT_DOUBLE_EQ(c2.getSpeed(), speed);
    EXPECT_DOUBLE_EQ(c2.getFuelUsage(), 0.5);
    EXPECT_EQ(c2.getCaptain()._name[0], captainName[0]);
    EXPECT_EQ(c2.getCaptain()._rank[0], captainRank[0]);

}

TEST(TestAircraftCarrier, TestDefaultConstructor) {
    TAircraftCarrier a;
    EXPECT_EQ(a.getWeaponry().getDamage(), 0);
    EXPECT_EQ(a.getSurvivability(), 0);
    EXPECT_EQ(a.getFuelUsage(), 0);
    EXPECT_EQ(a.getName()[0], ""[0]);
    EXPECT_EQ(a.getCrewMembersAmount(), 0);
    EXPECT_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestConstructor) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), 0);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 0);
    EXPECT_EQ(a.getName()[0], ""[0]);
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
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0);
    EXPECT_EQ(a2.getName()[0], ""[0]);
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
    EXPECT_DOUBLE_EQ(a2.getSurvivability(), 0);
    EXPECT_DOUBLE_EQ(a2.getFuelUsage(), 0);
    EXPECT_EQ(a2.getName()[0], ""[0]);
    EXPECT_EQ(a2.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a2.getSpeed(), 0);
    EXPECT_EQ(a2.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestGetters) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), 0);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 0);
    EXPECT_EQ(a.getName()[0], ""[0]);
    EXPECT_EQ(a.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 0);
}

TEST(TestAircraftCarrier, TestSetters) {
    TPlaneGroup planes;
    TWeaponry w1(" ", " ", 10, 1.3, WeaponryType::light);
    TAircraftCarrier a(w1, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TWeaponry w2("w2", "22.5mm", 5, 1.5, WeaponryType::heavy);
    a.setWeaponry(w2);
    TPlaneGroup planes2;
    TPlane p("Plane", w2, 0.5, 0.5, TPlaneType::bomber);
    planes2.addPlane(p);
    a.setPlaneInfo(planes2);
    EXPECT_DOUBLE_EQ(a.getWeaponry().getDamage(), w2.getDamage());
    EXPECT_DOUBLE_EQ(a.getSurvivability(), 0.5);
    EXPECT_DOUBLE_EQ(a.getFuelUsage(), 0.5);
    EXPECT_EQ(a.getName()[0], ""[0]);
    EXPECT_EQ(a.getCrewMembersAmount(), 10);
    EXPECT_DOUBLE_EQ(a.getSpeed(), 0);
    EXPECT_EQ(a.getPlaneInfo().size(), 1);
}

TEST(TestAircraftCarrier, TestAddPlane) {
    TPlaneGroup planes;
    TWeaponry w;
    TAircraftCarrier a(w, planes, "Name", "Captain", "Captain rank", 10, 0.5, 0, 10, 0.5);
    TPlane p("Plane", w, 0.5, 0.5, TPlaneType::bomber);
    a.addPlane(p);
    EXPECT_EQ(a.getPlaneInfo().size(), 1);
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

TEST(TestPlane, TestGetters) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlaneType planeType = TPlaneType::bomber;
    TPlane p(name, w, survivability, fuelUsage, planeType);

    EXPECT_EQ(p.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(p.getSurvivability(), survivability);
    EXPECT_EQ(p.getFuelUsage(), fuelUsage);
    EXPECT_EQ(p.getName(), name);
    EXPECT_EQ(p.getType(), planeType);
}

TEST(TestPlane, TestSetters) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    TWeaponry w2;
    double survivability2 = 0.5;
    double fuelUsage2 = 0.5;
    p.setWeaponry(w2);
    p.setWeaponryType(WeaponryType::heavy);
    p.setSurvivability(survivability2);
    p.setFuelUsage(fuelUsage2);
    p.setName(name);
    p.setType(TPlaneType::fighter);
    EXPECT_EQ(p.getWeaponry().getDamage(), w2.getDamage());
    EXPECT_EQ(p.getWeaponry().getType(), WeaponryType::heavy);
    EXPECT_EQ(p.getSurvivability(), survivability2);
    EXPECT_EQ(p.getFuelUsage(), fuelUsage2);
    EXPECT_EQ(p.getName(), name);
    EXPECT_EQ(p.getType(), TPlaneType::fighter);
}

TEST(TestPlane, TestExceptions) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    EXPECT_THROW(TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber), std::logic_error);
    w.setType(WeaponryType::heavy);
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    EXPECT_THROW(p.setWeaponryType(WeaponryType::light), std::logic_error);
    EXPECT_THROW(p.setSurvivability(-1), std::logic_error);
    EXPECT_THROW(p.setFuelUsage(-1), std::logic_error);
    TWeaponry w2;
    EXPECT_THROW(p.setWeaponry(w2), std::logic_error);
}

TEST(TestPlane, TestDump) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    std::stringstream s;
    p.dump(s);
    std::string expected = name + " " + std::to_string(survivability) + " " + std::to_string(fuelUsage) + "\n";
    std::string actual = s.str();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(TestPlane, TestRead) {
    std::string name = "Plane";
    TWeaponry w;
    double survivability = 0.5;
    double fuelUsage = 0.5;
    TPlane p(name, w, survivability, fuelUsage, TPlaneType::bomber);
    std::stringstream s;
    p.dump(s);
    TPlane q;
    std::stringstream t(s.str());
    q.read(t);
    EXPECT_EQ(q.getWeaponry().getDamage(), w.getDamage());
    EXPECT_EQ(q.getSurvivability(), survivability);
    EXPECT_EQ(q.getFuelUsage(), fuelUsage);
    EXPECT_EQ(q.getName(), name);
}

TEST(TestPlane, CopyAssignment) {
    std::string name = "Plane";
    TWeaponry w;
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
    TPlane b1("bomber", std::move(w1), 10., 10., TPlaneType::bomber);
    auto &c1Planes = c1.getPlaneInfo();
    c1Planes.addPlane(b1);
    b.relocatePlane("bomber", TPlaneType::bomber, c1.getName(), c2.getName());
    auto &c2Planes = c2.getPlaneInfo();
    EXPECT_EQ(c2Planes.size(), 1);
    EXPECT_EQ(c1Planes.size(), 0);
    std::string planeName = "bomber";
    std::string c1PlaneName = c1.getPlaneInfo().getPlane(planeName, TPlaneType::bomber).getName();
    EXPECT_EQ(c1PlaneName.size(), planeName.size());
    for (size_t i = 0; i < planeName.size(); ++i) {
        EXPECT_EQ(c1PlaneName[i], planeName[i]);
    }
}

TEST(TestBattleshipGroup, TestRead) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    std::stringstream in;
    in << b;
    TBattleshipGroup b2;
    b2.read(in);
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
}

TEST(TestBattleshipGroup, TestDump) {
    std::string admiralName = "Admiral";
    std::string admiralRank = "Captain";
    size_t admiralExperience = 10;
    std::string startingPoint = "Earth";
    std::string destination = "Mars";
    double distance = 1000;
    TBattleshipGroup b(admiralName, admiralRank, admiralExperience, startingPoint, destination, distance);
    std::stringstream out;
    b.dump(out);
    out << std::endl;
    TBattleshipGroup b2;
    b2.read(out);
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
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
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
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
    EXPECT_EQ(b.getAdmiralInfo()._name, b2.getAdmiralInfo()._name);
    EXPECT_EQ(b.getAdmiralInfo()._rank, b2.getAdmiralInfo()._rank);
    EXPECT_EQ(b.getAdmiralInfo()._experience, b2.getAdmiralInfo()._experience);
    EXPECT_EQ(b.getStartingPoint(), b2.getStartingPoint());
    EXPECT_EQ(b.getDestination(), b2.getDestination());
    EXPECT_EQ(b.getDistance(), b2.getDistance());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
