using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;
using MultiCriteriaLibraryApi.MathModelComponents;

public class AddictiveAggregationOperator : AbstractAggregationOperator
{
    internal IntPtr _operatorPtr;

    public AddictiveAggregationOperator()
    {
        _operatorPtr = AddictiveAggregationOperator_new();
    }
    
    public override Dictionary<int, double> GetEstimateVectorMark(MathModel normalizedMathModel, AbstractWeightCriteriaRelation weightCriteriaRelation)
    {
        var type = weightCriteriaRelation.GetType();
        var fieldInfo = type.GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        var res = (IntPtr) fieldInfo.GetValue(weightCriteriaRelation);

        IntPtr keysPtr = AddictiveAggregationOperator_getEstimateVectorMark_Keys(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        IntPtr valuesPtr = AddictiveAggregationOperator_getEstimateVectorMark_Values(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        int size = AddictiveAggregationOperator_getEstimateVectorMark_Size(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        
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

    public override double GetBestValue()
    {
        return AddictiveAggregationOperator_GetBestValue(_operatorPtr);
    }

    public override int GetBestEstimateVectorId()
    {
        return AddictiveAggregationOperator_GetBestEstimateVectorId(_operatorPtr);
    }

    public override bool IsNeedNormalizedMathModel()
    {
        return AddictiveAggregationOperator_IsNeedNormalizedMathModel(_operatorPtr);
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AddictiveAggregationOperator_new();

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AddictiveAggregationOperator_getEstimateVectorMark_Keys(IntPtr oper, IntPtr mathModel, IntPtr relation);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr AddictiveAggregationOperator_getEstimateVectorMark_Values(IntPtr oper, IntPtr mathModel, IntPtr relation);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int AddictiveAggregationOperator_getEstimateVectorMark_Size(IntPtr oper, IntPtr mathModel, IntPtr relation);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double AddictiveAggregationOperator_GetBestValue(IntPtr oper);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int AddictiveAggregationOperator_GetBestEstimateVectorId(IntPtr oper);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool AddictiveAggregationOperator_IsNeedNormalizedMathModel(IntPtr oper);
} 