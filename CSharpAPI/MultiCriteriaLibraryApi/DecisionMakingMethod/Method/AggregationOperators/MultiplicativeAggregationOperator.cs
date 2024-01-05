using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;
using MultiCriteriaLibraryApi.MathModelComponents;

public class MultiplicativeAggregationOperator : AbstractAggregationOperator
{
    internal IntPtr _operatorPtr;

    public MultiplicativeAggregationOperator()
    {
        _operatorPtr = MultiplicativeAggregationOperator_new();
    }
    
    public override Dictionary<int, double> GetEstimateVectorMark(MathModel normalizedMathModel, AbstractWeightCriteriaRelation weightCriteriaRelation)
    {
        var type = weightCriteriaRelation.GetType();
        var fieldInfo = type.GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        var res = (IntPtr) fieldInfo.GetValue(weightCriteriaRelation);

        IntPtr keysPtr = MultiplicativeAggregationOperator_getEstimateVectorMark_Keys(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        IntPtr valuesPtr = MultiplicativeAggregationOperator_getEstimateVectorMark_Values(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        int size = MultiplicativeAggregationOperator_getEstimateVectorMark_Size(_operatorPtr, normalizedMathModel._mathModelPtr, res);
        
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
        return MultiplicativeAggregationOperator_GetBestValue(_operatorPtr);
    }

    public override int GetBestEstimateVectorId()
    {
        return MultiplicativeAggregationOperator_GetBestEstimateVectorId(_operatorPtr);
    }

    public override bool IsNeedNormalizedMathModel()
    {
        return MultiplicativeAggregationOperator_IsNeedNormalizedMathModel(_operatorPtr);
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiplicativeAggregationOperator_new();

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiplicativeAggregationOperator_getEstimateVectorMark_Keys(IntPtr oper, IntPtr mathModel, IntPtr relation);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MultiplicativeAggregationOperator_getEstimateVectorMark_Values(IntPtr oper, IntPtr mathModel, IntPtr relation);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MultiplicativeAggregationOperator_getEstimateVectorMark_Size(IntPtr oper, IntPtr mathModel, IntPtr relation);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double MultiplicativeAggregationOperator_GetBestValue(IntPtr oper);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MultiplicativeAggregationOperator_GetBestEstimateVectorId(IntPtr oper);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool MultiplicativeAggregationOperator_IsNeedNormalizedMathModel(IntPtr oper);
} 