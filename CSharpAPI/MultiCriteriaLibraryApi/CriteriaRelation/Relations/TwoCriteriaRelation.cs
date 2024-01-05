using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations;

public enum CriteriaConstraint
{
    More, MoreOrEquivalent, Equivalent, LessOrEquivalent, Less
}

public class TwoCriteriaRelation
{
    internal IntPtr _relationPtr;

    public int FirstCriteriaId => TwoCriteriaRelation_getFirstCriteriaId(_relationPtr);
    public int SecondCriteriaId => TwoCriteriaRelation_getSecondCriteriaId(_relationPtr);
    public CriteriaConstraint CriteriaConstraint =>
        (CriteriaConstraint)Enum.Parse(
            typeof(CriteriaConstraint),
            TwoCriteriaRelation_getConstraint(_relationPtr).ToString());
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr TwoCriteriaRelation_new(int firstId, int constraint, int secondId);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr TwoCriteriaRelation_new_copy(IntPtr obj);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int TwoCriteriaRelation_getFirstCriteriaId(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int TwoCriteriaRelation_getSecondCriteriaId(IntPtr relationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int TwoCriteriaRelation_getConstraint(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool TwoCriteriaRelation_isValid(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool TwoCriteriaRelation_isEqual(IntPtr relationPtr, IntPtr otherRelationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr TwoCriteriaRelation_invert(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int TwoCriteriaRelation_getInvertConstraint(IntPtr relationPtr, int constraint);
    
    public TwoCriteriaRelation(int firstId, CriteriaConstraint constraint, int secondId)
    {
        _relationPtr = TwoCriteriaRelation_new(firstId, (int)constraint, secondId);
    }

    public TwoCriteriaRelation(TwoCriteriaRelation relation)
    {
        _relationPtr = TwoCriteriaRelation_new_copy(relation._relationPtr);
    }

    internal TwoCriteriaRelation(IntPtr relationPtr)
    {
        _relationPtr = relationPtr;
    }

    public bool IsValid()
    {
        return TwoCriteriaRelation_isValid(_relationPtr);
    }

    public bool IsEqual(TwoCriteriaRelation otherRelation)
    {
        return TwoCriteriaRelation_isEqual(_relationPtr, otherRelation._relationPtr);
    }

    TwoCriteriaRelation Invert()
    {
        return new TwoCriteriaRelation(TwoCriteriaRelation_invert(_relationPtr));
    }

    CriteriaConstraint GetInvertCriteriaConstraint(CriteriaConstraint constraint)
    {
        return (CriteriaConstraint) Enum.Parse(
            typeof(CriteriaConstraint),
            TwoCriteriaRelation_getInvertConstraint(_relationPtr, (int) CriteriaConstraint).ToString());
    }

    public override string ToString()
    {
        string rel = "";
        switch (CriteriaConstraint)
        {
            case CriteriaConstraint.More:
                rel = ">";
                break;
            case CriteriaConstraint.MoreOrEquivalent:
                rel = ">=";
                break;
            case CriteriaConstraint.Equivalent:
                rel = "~";
                break;
            case CriteriaConstraint.LessOrEquivalent:
                rel = "<=";
                break;
            case CriteriaConstraint.Less:
                rel = "<";
                break;
            default:
                throw new ArgumentOutOfRangeException();
        }

        return $"{FirstCriteriaId} {rel} {SecondCriteriaId}";
    }
}