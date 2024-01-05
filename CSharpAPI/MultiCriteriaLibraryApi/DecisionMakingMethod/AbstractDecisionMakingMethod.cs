namespace MultiCriteriaLibraryApi.DecisionMakingMethod;

public abstract class AbstractDecisionMakingMethod
{
    protected SolveStatus _solveStatus { get; }

    public abstract SolveStatus solve();
}