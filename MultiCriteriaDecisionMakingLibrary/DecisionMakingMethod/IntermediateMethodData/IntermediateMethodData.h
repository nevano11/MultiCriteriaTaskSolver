#ifndef DMLTESTER_INTERMEDIATEMETHODDATA_H
#define DMLTESTER_INTERMEDIATEMETHODDATA_H

class IntermediateMethodData {
public:
    virtual ~IntermediateMethodData() = default;
    virtual std::string toString() = 0;
};

#endif //DMLTESTER_INTERMEDIATEMETHODDATA_H
