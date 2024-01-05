using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;
using MultiCriteriaLibraryApi.MathModelComponents;
using MultiCriteriaLibraryApi.MathModelComponents.Converters;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod.Method;

public class CriteriaAggregationMethod : AbstractOneStepMethod, IProgressingAllAlternativesMethod
{
    internal IntPtr _method;
    internal override IntPtr getPtr()
    {
        return _method;
    }
    
    public override MathModel MathModel
    {
        get
        {
            return new MathModel(CriteriaAggregationMethod_getMathModel(_method));
        }
        set
        {
            CriteriaAggregationMethod_setMathModel(_method, value._mathModelPtr);
        }
    }

    public override ICriteriaRelation CriteriaRelation
    {
        set
        {
            CriteriaAggregationMethod_setCriteriaRelation(_method, toIntPtr(value));
        }
    }
    public INormalizer Normalizer
    {
        set
        {
            CriteriaAggregationMethod_setNormalizer(_method, toIntPtr(value));
        }
    }

    public AbstractAggregationOperator Operator
    {
        set
        {
            CriteriaAggregationMethod_setOperator(_method, toIntPtr(value));
        }
    }

    public CriteriaAggregationMethod(AbstractAggregationOperator oper)
    {
        _method = CriteriaAggregationMethod_new(toIntPtr(oper));
    }
    
    public CriteriaAggregationMethod(AbstractAggregationOperator oper, INormalizer normalizer)
    {
        _method = CriteriaAggregationMethod_new_2(toIntPtr(oper), toIntPtr(normalizer));
    }
    
    public CriteriaAggregationMethod(MathModel mathModel, AbstractWeightCriteriaRelation relation, AbstractAggregationOperator oper)
    {
        
        _method = CriteriaAggregationMethod_new_3(mathModel._mathModelPtr, toIntPtr(relation), toIntPtr(oper));
    }
    
    public CriteriaAggregationMethod(MathModel mathModel, AbstractWeightCriteriaRelation relation, AbstractAggregationOperator oper, INormalizer normalizer)
    {
        _method = CriteriaAggregationMethod_new_4(
            mathModel._mathModelPtr, toIntPtr(relation), toIntPtr(oper), toIntPtr(normalizer));
    }

    ~CriteriaAggregationMethod()
    {
        CriteriaAggregationMethod_delete(_method);
    }

    public Dictionary<int, double> GetEstimateVectorWeight()
    {
        IntPtr keysPtr = CriteriaAggregationMethod_GetEstimateVectorWeight_Keys(_method);
        IntPtr valuesPtr = CriteriaAggregationMethod_GetEstimateVectorWeight_Values(_method);
        int size = CriteriaAggregationMethod_GetEstimateVectorWeight_Size(_method);
        
        int[] keys = new int[size];
        Marshal.Copy(keysPtr, keys, 0, size);
        double[] values = new double[size];
        Marshal.Copy(valuesPtr, values, 0, size);

        Dictionary<int, double> map = new Dictionary<int, double>();
        for (int i = 0; i < size; i++) {
            map.Add(keys[i], values[i]);
        }
        return map;
    }

    public override int GetBestEstimateVectorId()
    {
        return CriteriaAggregationMethod_GetBestEstimateVectorId(_method);
    }
    
    public override SolveStatus solve()
    {
        return new SolveStatus(CriteriaAggregationMethod_solve(_method));
    }
    
    public void solveWithProtocol(int protocolId)
    {
        CriteriaAggregationMethod_solve_protocol(_method, protocolId);
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_new(IntPtr oper);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_new_2(IntPtr oper, IntPtr normalizer);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_new_3(IntPtr mM, IntPtr cR, IntPtr oper);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_new_4(IntPtr mM, IntPtr cR,IntPtr oper, IntPtr normalizer);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_delete(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_getMathModel(IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_setMathModel(IntPtr method, IntPtr mm);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_setCriteriaRelation(IntPtr method, IntPtr cR);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_setNormalizer(IntPtr method, IntPtr normalizer);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_setOperator(IntPtr method, IntPtr oper);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_GetEstimateVectorWeight_Keys(IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_GetEstimateVectorWeight_Values(IntPtr method);
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int CriteriaAggregationMethod_GetEstimateVectorWeight_Size(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int CriteriaAggregationMethod_GetBestEstimateVectorId(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaAggregationMethod_solve(IntPtr method);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CriteriaAggregationMethod_solve_protocol(IntPtr method, int protocolNum);

    private IntPtr toIntPtr(INormalizer n)
    {
        return n.getPtr();
    }
    
    private IntPtr toIntPtr(ICriteriaRelation n)
    {
        return n.getPtr();
    }
    
    private IntPtr toIntPtr(AbstractAggregationOperator n)
    {
        var fieldInfo = n.GetType().GetField("_operatorPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        return (IntPtr) fieldInfo.GetValue(n);
    }
}