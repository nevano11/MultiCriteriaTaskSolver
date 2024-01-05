namespace MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod;

using MultiCriteriaLibraryApi.MathModelComponents;

public abstract class AbstractMultiCriteriaMethod : AbstractDecisionMakingMethod
{
    internal abstract IntPtr getPtr();
    
    public abstract MathModel MathModel { set; get; }
    public abstract ICriteriaRelation CriteriaRelation { set; }

    public abstract int GetBestEstimateVectorId();
}