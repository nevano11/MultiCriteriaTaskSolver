using System.Reflection;
using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations.WeightCriteriaRelations;

public class SimpleRankingMethod : AbstractWeightCriteriaRelation
{
    internal IntPtr _relationPtr { get; }

    public int criteriaCount => SimpleRankingMethod_getCriteriaCount(_relationPtr);

    public Dictionary<int, double> CriteriaIdWeightMap
    {
        get
        {
            int criteriaCount = this.criteriaCount;
            int[] keys = new int[criteriaCount];
            Marshal.Copy(SimpleRankingMethod_getCriteriaWeightMapKeys(_relationPtr), keys, 0, criteriaCount);

            double[] values = new double[criteriaCount];
            Marshal.Copy(SimpleRankingMethod_getCriteriaWeightMapValues(_relationPtr), values, 0, criteriaCount);

            Dictionary<int, double> map = new Dictionary<int, double>();
            for (int i = 0; i < criteriaCount; i++) {
                map.Add(keys[i], values[i]);
            }
            return map;
        }
    }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleRankingMethod_new(int criteriaCount, IntPtr keys, IntPtr values);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleRankingMethod_getCriteriaWeightMapKeys(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleRankingMethod_getCriteriaWeightMapValues(IntPtr relationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int SimpleRankingMethod_getCriteriaCount(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool SimpleRankingMethod_isValid(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SimpleRankingMethod_copy(IntPtr relationPtr);
    
    public SimpleRankingMethod(int criteriaCount, Dictionary<int, double> criteriaRankMap) 
    {
        int size = criteriaCount * sizeof(int);
        IntPtr keysPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(criteriaRankMap.Keys.ToArray(), 0, keysPtr, criteriaCount);
        
        size = criteriaCount * sizeof(double);
        IntPtr valuesPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(criteriaRankMap.Values.ToArray(), 0, valuesPtr, criteriaCount);
        
        _relationPtr = SimpleRankingMethod_new(criteriaCount, keysPtr, valuesPtr);
        
        Marshal.FreeHGlobal(keysPtr);
        Marshal.FreeHGlobal(valuesPtr);
    }

    internal SimpleRankingMethod(IntPtr relationPtr)
    {
        _relationPtr = relationPtr;
    }

    internal override IntPtr getPtr()
    {
        return _relationPtr;
    }

    public override bool IsValid()
    {
        return SimpleRankingMethod_isValid(_relationPtr);
    }

    public override ICriteriaRelation Copy()
    {
        return new ProportionalMethod(SimpleRankingMethod_copy(_relationPtr));
    }

    public override string ToString()
    {
        string res = "SimpleRankingMethod: CriteriaIdWeightMap={";
        var map = CriteriaIdWeightMap;
        foreach (var (key, value) in map)
        {
            res += "{" + key + ", " + value + "}, ";
        }
        return res + "}";
    }
}