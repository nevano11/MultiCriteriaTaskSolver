#ifndef DMLTESTER_SOLVESTATUS_H
#define DMLTESTER_SOLVESTATUS_H

#include <iostream>

enum DecisionStatus {
    None, //Решение не начато
    Process, //Решение выполняется (ожидается информация от ЛПР)
    Optimal, //Решение найдено оптимальное решение
    Feasible, //Решение окончено, несколько решений
    Infeasible, //Оптимальное решение не найдено
    InvalidModel, //Некорректно задана мат. модель / ограничения
    InvalidData, //Некорректная доп информация для методов
};

class SolveStatus {
protected:
    DecisionStatus decisionStatus;
    std::string message;
public:
    SolveStatus();
    SolveStatus(DecisionStatus decisionStatus);
    SolveStatus(DecisionStatus decisionStatus, std::string message);

    DecisionStatus getStatus();
    std::string getMessage();
    std::string toString();
};


#endif //DMLTESTER_SOLVESTATUS_H