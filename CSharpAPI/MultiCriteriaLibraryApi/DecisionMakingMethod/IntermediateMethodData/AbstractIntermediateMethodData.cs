namespace MultiCriteriaLibraryApi.DecisionMakingMethod.IntermediateMethodData;

public abstract class AbstractIntermediateMethodData
{
    internal IntPtr _method;

    internal AbstractIntermediateMethodData(IntPtr ptr)
    {
        _method = ptr;
    }
    
    public AbstractIntermediateMethodData() {}
}