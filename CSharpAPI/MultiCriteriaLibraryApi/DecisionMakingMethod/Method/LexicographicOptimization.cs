using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.MathModelComponents;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod.Method;

public class LexicographicOptimization : AbstractOneStepMethod, ISequentialNarrowingAlternativesMethod
{
    internal IntPtr _method;

    internal override IntPtr getPtr()
    {
        return _method;
    }

    public override MathModel MathModel
    {
        set => LexicographicOptimization_setMathModel(_method, value._mathModelPtr);
        get => new MathModel(LexicographicOptimization_getMathModel(_method)); 
    }

    public override ICriteriaRelation CriteriaRelation
    {
        set
        {
            var type = value.GetType();
            var fieldInfo = type.GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
            var res = (IntPtr) fieldInfo.GetValue(value);
            LexicographicOptimization_setRelation(_method, res);
        }
    }

    public override SolveStatus solve()
    {
        return new SolveStatus(LexicographicOptimization_solve(_method));
    }

    public LexicographicOptimization()
    {
        _method = LexicographicOptimization_new();
    }

    public LexicographicOptimization(MathModel mathModel, ICriteriaRelation relation)
    {
        var type = relation.GetType();
        var fieldInfo = type.GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        IntPtr res = (IntPtr)fieldInfo.GetValue(relation);
        _method = LexicographicOptimization_new_2(mathModel._mathModelPtr, res);
    }
    ~LexicographicOptimization()
    {
        LexicographicOptimization_delete(_method);
    }
    
    public override int GetBestEstimateVectorId()
    {
        return LexicographicOptimization_getBestEstimateVectorId(_method);
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr LexicographicOptimization_new();
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void LexicographicOptimization_delete(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr LexicographicOptimization_new_2(IntPtr mathModel, IntPtr relation);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr LexicographicOptimization_getMathModel(IntPtr method);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void LexicographicOptimization_setMathModel(IntPtr method, IntPtr mathModel);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void LexicographicOptimization_setRelation(IntPtr method, IntPtr relation);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr LexicographicOptimization_solve(IntPtr method);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int LexicographicOptimization_getBestEstimateVectorId(IntPtr method);
}