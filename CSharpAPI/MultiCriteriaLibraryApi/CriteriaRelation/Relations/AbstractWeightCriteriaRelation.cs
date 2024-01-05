namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations;

public abstract class AbstractWeightCriteriaRelation : ICriteriaRelation
{
    public int CriteriaCount { get; }
    public Dictionary<int, double> CriteriaIdWeightMap { get; }

    IntPtr ICriteriaRelation.getPtr() =>
        getPtr();

    internal abstract IntPtr getPtr();
    
    public abstract bool IsValid();
    public abstract ICriteriaRelation Copy();
}