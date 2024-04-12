#include "CrewMember.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"

TEST(CrewMemberClass, constructor) {
    Company* company = new (Company){"Test1"};

    CrewMember crewMember1{PILOT, 1, "Victor", "Alb", 1, MALE};
    CrewMember crewMember2{company, PILOT, 2, "Victor", "Alb", 1, MALE};
    // getCompany
    EXPECT_EQ(crewMember2.getCompany(), company);
    // getRole
    EXPECT_EQ(crewMember1.getRole(), PILOT);

    delete company;
}

TEST(CrewMemberClass, setters) {
    Company* company = new (Company){"Test1"};

    CrewMember crewMember{PILOT, 1, "Victor", "Alb", 1, MALE};
    // setCompany
    crewMember.setCompany(company);
    EXPECT_EQ(crewMember.getCompany(), company);
    EXPECT_THROW(crewMember.setCompany(nullptr), InvalidPointer);

    delete company;
}