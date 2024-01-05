using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;
using MultiCriteriaLibraryApi.DecisionMakingMethod.IntermediateMethodData;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;

public abstract class AbstractMultiStepMethod : AbstractMultiCriteriaMethod
{
    public abstract SolveStatus MakeIteration(IDecisionMakerInfo decisionMakingInfo);
    public abstract AbstractIntermediateMethodData GetIntermediateMethodData();
}