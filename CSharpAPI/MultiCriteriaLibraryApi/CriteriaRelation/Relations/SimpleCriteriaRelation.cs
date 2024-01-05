using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations;

public class SimpleCriteriaRelation : ICriteriaRelation
{
    internal IntPtr _relationPtr { get; }

    public int CriteriaCount => SimpleCriteriaRelation_getCriteriaCount(_relationPtr);

    public int RelationCount => SimpleCriteriaRelation_getRelationCount(_relationPtr);

    public TwoCriteriaRelation[] Relations
    {
        get
        {
            IntPtr relationsPtr = SimpleCriteriaRelation_getTwoCriteriaRelationArray(_relationPtr);
            int relCount = RelationCount;
            TwoCriteriaRelation[] relations = new TwoCriteriaRelation[relCount];
            for (int i = 0; i < relCount; i++)
            {
                IntPtr relPtr = Marshal.ReadIntPtr(relationsPtr, i * IntPtr.Size);
                relations[i] = new TwoCriteriaRelation(relPtr);
            }
            return relations;
        }
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleCriteriaRelation_new(IntPtr twoCriteriaRelationArray, int criteriaCount, int relationCount);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void SimpleCriteriaRelation_delete(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleCriteriaRelation_getTwoCriteriaRelationArray(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int SimpleCriteriaRelation_getCriteriaCount(IntPtr relationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int SimpleCriteriaRelation_getRelationCount(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool SimpleCriteriaRelation_isValid(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleCriteriaRelation_copy(IntPtr relationPtr);

    public SimpleCriteriaRelation(TwoCriteriaRelation[] relations, int criteriaCount)
    {
        IntPtr[] relationPtrs = relations.Select(r => r._relationPtr).ToArray();
        _relationPtr =
            SimpleCriteriaRelation_new(ConvertToIntPtr(relationPtrs), criteriaCount, relations.Length);
    }

    internal SimpleCriteriaRelation(IntPtr relationPtr)
    {
        _relationPtr = relationPtr;
    }

    ~SimpleCriteriaRelation()
    {
        SimpleCriteriaRelation_delete(_relationPtr);
    }

    IntPtr ICriteriaRelation.getPtr()
    {
        return _relationPtr;
    }

    public bool IsValid()
    {
        return SimpleCriteriaRelation_isValid(_relationPtr);
    }

    public ICriteriaRelation Copy()
    {
        return new SimpleCriteriaRelation(SimpleCriteriaRelation_copy(_relationPtr));
    }

    public override string ToString()
    {
        var rC = RelationCount;
        var relations = Relations;
        var res = "SimpleCriteriaRelation: criteriaCount=" + CriteriaCount + ", relationCount=" + rC + " relations=[";
        for (int i = 0; i < rC; i++)
        {
            res += relations[i];
            if (i != rC - 1)
                res += ", ";
        }
        
        return res + "]";
    }

    private static IntPtr ConvertToIntPtr(IntPtr[] pointers)
    {
        int size = pointers.Length * IntPtr.Size;
        IntPtr ptr = Marshal.AllocHGlobal(size);
        for (int i = 0; i < pointers.Length; i++)
            Marshal.WriteIntPtr(ptr, i * IntPtr.Size, pointers[i]);
        return ptr;
    }
}