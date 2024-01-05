using MultiCriteriaLibraryApi.CriteriaRelation.Relations;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;

public abstract class AbstractAggregationOperator
{
    protected Dictionary<int, double> _estimateVectorValue;

    public abstract Dictionary<int, double> GetEstimateVectorMark(MathModelComponents.MathModel normalizedMathModel,
        AbstractWeightCriteriaRelation weightCriteriaRelation);

    public abstract double GetBestValue();
    public abstract int GetBestEstimateVectorId();
    public abstract bool IsNeedNormalizedMathModel();
}