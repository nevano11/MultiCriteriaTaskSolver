namespace MultiCriteriaLibraryApi.DecisionMakingMethod.Method;

using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;
using MultiCriteriaLibraryApi.DecisionMakingMethod.IntermediateMethodData;
using MultiCriteriaLibraryApi.MathModelComponents;

public class SuccessiveConcessionsMethod : AbstractMultiStepMethod, ISequentialNarrowingAlternativesMethod
{
    internal IntPtr _method;

    internal override IntPtr getPtr()
    {
        return _method;
    }

    public override MathModel MathModel
    {
        get => new MathModel(SuccessiveConcessionsMethod_getMathModel(_method));
        set => SuccessiveConcessionsMethod_setMathModel(_method, value._mathModelPtr);
    }

    public override ICriteriaRelation CriteriaRelation
    {
        set => SuccessiveConcessionsMethod_setCriteriaRelation(_method, toIntPtr(value));
    }

    public SuccessiveConcessionsMethod()
    {
        _method = SuccessiveConcessionsMethod_new();
    }

    public SuccessiveConcessionsMethod(MathModel mathModel, ICriteriaRelation relation)
    {
        _method = SuccessiveConcessionsMethod_new_2(mathModel._mathModelPtr, toIntPtr(relation));
    }

    ~SuccessiveConcessionsMethod()
    {
        SuccessiveConcessionsMethod_delete(_method);
    }

    public override int GetBestEstimateVectorId()
    {
        return SuccessiveConcessionsMethod_GetBestEstimateVectorId(_method);
    }

    public override SolveStatus MakeIteration(IDecisionMakerInfo decisionMakingInfo)
    {
        return new SolveStatus(SuccessiveConcessionsMethod_makeIteration(_method, toIntPtr(decisionMakingInfo)));
    }
    
    public override SolveStatus solve()
    {
        return new SolveStatus(SuccessiveConcessionsMethod_solve(_method));
    }

    public override AbstractIntermediateMethodData GetIntermediateMethodData()
    {
        return new SuccessiveConcessionsIntermediateData(SuccessiveConcessionsMethod_getIntermediateMethodData(_method));
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_new();
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_new_2(IntPtr mM, IntPtr cR);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void SuccessiveConcessionsMethod_delete(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_getMathModel(IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void SuccessiveConcessionsMethod_setMathModel(IntPtr method, IntPtr mm);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void SuccessiveConcessionsMethod_setCriteriaRelation(IntPtr method, IntPtr cR);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_getIntermediateMethodData(IntPtr method);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int SuccessiveConcessionsMethod_GetBestEstimateVectorId(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_solve(IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsMethod_makeIteration(IntPtr method, IntPtr decisionMakerInfo);
    
    private IntPtr toIntPtr(ICriteriaRelation n)
    {
        var fieldInfo = n.GetType().GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        return (IntPtr) fieldInfo.GetValue(n);
    }
    
    private IntPtr toIntPtr(IDecisionMakerInfo n)
    {
        var fieldInfo = n.GetType().GetField("_makerInfo", BindingFlags.NonPublic | BindingFlags.Instance);
        return (IntPtr) fieldInfo.GetValue(n);
    }
}