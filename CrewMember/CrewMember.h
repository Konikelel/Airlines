#include <memory>
#include <vector>

#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

#include "../Flight/Flight.h"
#include "../Person/Person.h"
#include "Role.h"

class CrewMember : public Person {
   private:
    Role role;

    std::vector<std::shared_ptr<Flight>> flights;
};

#endif