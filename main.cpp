#include <iostream>

#include "Company.hpp"
#include "CrewMember.hpp"
#include "Flight.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"

int main() {
    Company* pCompany = new (Company){"Emirates"};

    std::cout << *pCompany << std::endl;

    std::cout << "\n\n\tAdding planes to company...\n\n";

    Plane plane1{pCompany, "B737", 2, 1, 1};
    Plane plane2{pCompany, "A320", 2, 1, 1};

    std::cout << *pCompany << std::endl;

    std::cout << "\n\n\tEmploying pilots, stewardess...\n\n";

    CrewMember pilot1{pCompany, PILOT, "Terry", "Leblanc", 37, MALE};
    CrewMember pilot2{pCompany, PILOT, "Julie", "Curd", 25, FEMALE};

    CrewMember stewardess1{pCompany, STEWARDESS, "Patrica", "Mann", 21, FEMALE};
    CrewMember stewardess2{pCompany, STEWARDESS, "Annie", "Lewis", 34, FEMALE};

    Passenger passenger1{"Clarence", "White", 19, MALE};
    Passenger passenger2{"Linda", "Maloney", 43, FEMALE};
    Passenger passenger3{"Edgar", "Huff", 26, MALE};

    std::cout << *pCompany << std::endl;

    std::cout << "\n\n\tAdding flights, assign planes...\n\n";

    Flight& flight1 = pCompany->createFlight("EMS120", plane1, 1715051190910, 1715061190910, "Paris", "Berlin");
    Flight& flight2 = pCompany->createFlight("EMS256", plane2, 1714051190910, 1715071332733, "Dubai", "New York");

    std::cout << *pCompany << std::endl;
    std::cout << "Flight1 " << flight1;
    std::cout << "Flight2 " << flight2;

    std::cout << "\n\n\tAdding crew members to flights...\n\n";

    flight1.addCrewMember(pilot1);
    flight1.addCrewMember(stewardess1);
    flight2.addCrewMember(pilot2);

    std::cout << "Flight1 " << flight1;
    std::cout << "Flight2 " << flight2;
    std::cout << "Pilot1 " << pilot1;
    std::cout << "Pilot2 " << pilot2;

    std::cout << "\n\n\tOne flight is INCOMPLETE there is not enough stewardess to operate the flight\n"
              << "\tChecking for available stewardess to assign to the flight\n\n";

    std::cout << "\tAvailable stewardess in this time period:\n";

    flight2.addCrewMember(stewardess2);

    std::cout << "Flight1 " << flight1;
    std::cout << "Flight2 " << flight2;

    std::cout << "\n\n\tPopulating flights with passengers...\n\n";

    flight1.addPassenger(passenger1);
    flight1.addPassenger(passenger2);
    flight2.addPassenger(passenger3);

    std::cout << "Flight1 " << flight1;
    std::cout << "Flight2 " << flight2;
    std::cout << "Passenger1: " << passenger1;
    std::cout << "Passenger3: " << passenger3;

    std::cout << "\n\n\tDeleting flight from company...\n\n";

    pCompany->removeFlight(flight1);

    std::cout << *pCompany << std::endl;
    std::cout << "Pilot1: " << pilot1;
    std::cout << "Passenger1: " << passenger1;

    delete pCompany;

    return 0;
}