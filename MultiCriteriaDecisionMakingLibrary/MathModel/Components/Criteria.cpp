#include "Criteria.h"
#include <string>
#include <cstring>
#include <utility>

//#define Debug 1

extern "C" {
__declspec(dllexport) Criteria *Criteria_new(int id, char* name, int nameLength, int criteriaType) {
        std::string realName = std::string(name, nameLength);
        auto cr = new Criteria(id, realName, criteriaType == 1 ? CriteriaType::MAXIMIZATION : CriteriaType::MINIMIZATION);
#ifdef Debug
        std::cout << "cpp Criteria_new" << " input=[id=" << id << ", name=" << realName << "nL=" << nameLength << ", cT=" << criteriaType << std::endl;
        std::cout << "cpp INITRES: criteria: " << cr->getId() << " " << cr->getName() << " " << (cr->getType() == CriteriaType::MAXIMIZATION ? 1 : 0) << std::endl;
#endif
        return cr;
    }
__declspec(dllexport) Criteria *Criteria_new_copy(const Criteria &other) {
        return new Criteria(other);
    }
__declspec(dllexport) void Criteria_delete(Criteria *obj) {
        delete obj;
    }
__declspec(dllexport) int Criteria_getId(Criteria *obj) {
        int res = obj->getId();
#ifdef Debug
        std::cout << "cpp Criteria_getId return " << res << std::endl;
#endif
        return res;
    }
__declspec(dllexport) const char* Criteria_getName(Criteria *obj) {
        try {
            std::string str = obj->getName();
            char* buffer = new char[str.length() + 1];
            std::strcpy(buffer, str.c_str());
#ifdef Debug
            std::cout << "cpp Criteria_getName return " << buffer << std::endl;
#endif
            return buffer;
        }
        catch (const std::exception& e) {
            std::cerr << "Error in Criteria_getName: " << e.what() << std::endl;
            return nullptr;
        }
    }
__declspec(dllexport) int GetCriteriaType(Criteria *obj) {
        CriteriaType type = obj->getType();
        int res = type == CriteriaType::MAXIMIZATION ? 1 : 0;
#ifdef Debug
        std::cout << "cpp GetCriteriaType return " << res << std::endl;
#endif
        return res;
    }
}

Criteria::Criteria(int id, std::string name, CriteriaType criteriaType = CriteriaType::MAXIMIZATION) {
    this->id = id;
    this->name = std::move(name);
    this->type = criteriaType;
}

Criteria::Criteria(const Criteria &other) : id(other.id), name(other.name), type(other.type)
{
}

Criteria::~Criteria()
{
}

int Criteria::getId()
{
    return id;
}

std::string Criteria::getName() {
    return name;
}

CriteriaType Criteria::getType() {
    return type;
}
