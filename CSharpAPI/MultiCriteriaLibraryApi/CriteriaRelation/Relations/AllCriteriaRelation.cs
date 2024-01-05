using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations;

public class AllCriteriaRelation : ICriteriaRelation
{
    internal IntPtr _relationPtr;

    public int[] idSequence
    {
        get
        {
            int seqSize = AllCriteriaRelation_getSequenceSize(_relationPtr);
            int[] idSeq = new int[seqSize];
            Marshal.Copy(AllCriteriaRelation_getIdSequence(_relationPtr), idSeq, 0, seqSize);
            return idSeq;
        }
    }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AllCriteriaRelation_new(int criteriaCount, IntPtr idSequence);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void AllCriteriaRelation_delete(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AllCriteriaRelation_getIdSequence(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int AllCriteriaRelation_getSequenceSize(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool AllCriteriaRelation_isValid(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AllCriteriaRelation_copy(IntPtr relationPtr);

    public AllCriteriaRelation(int criteriaCount, int[] idSequence)
    {
        int size = criteriaCount * sizeof(int);
        IntPtr idSeqPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(idSequence, 0, idSeqPtr, criteriaCount);

        _relationPtr = AllCriteriaRelation_new(criteriaCount, idSeqPtr);

        Marshal.FreeHGlobal(idSeqPtr);
    }

    internal AllCriteriaRelation(IntPtr relationPtr)
    {
        _relationPtr = relationPtr;
    }

    ~AllCriteriaRelation()
    {
        AllCriteriaRelation_delete(_relationPtr);
    }

    IntPtr ICriteriaRelation.getPtr()
    {
        return _relationPtr;
    }

    public bool IsValid()
    {
        return AllCriteriaRelation_isValid(_relationPtr);
    }

    public ICriteriaRelation Copy()
    {
        return new AllCriteriaRelation(AllCriteriaRelation_copy(_relationPtr));
    }

    public override string ToString()
    {
        string res = "AllCriteriaRelation: idSequence=[";
        var idSeq = idSequence;
        for (var i = 0; i < idSeq.Length; i++)
        {
            res += idSeq[i];
            if (i != idSeq.Length - 1)
            {
                res += ", ";
            }
        }
        return res + "]";
    }
}