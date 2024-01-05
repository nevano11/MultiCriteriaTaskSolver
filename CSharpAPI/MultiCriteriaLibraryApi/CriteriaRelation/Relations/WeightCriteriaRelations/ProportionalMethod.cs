using System.Reflection;
using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.CriteriaRelation.Relations.WeightCriteriaRelations;

public class ProportionalMethod : AbstractWeightCriteriaRelation
{
    internal IntPtr _relationPtr { get; }

    public int criteriaCount => ProportionalMethod_getCriteriaCount(_relationPtr);

    public Dictionary<int, double> CriteriaIdWeightMap
    {
        get
        {
            int criteriaCount = this.criteriaCount;
            int[] keys = new int[criteriaCount];
            Marshal.Copy(ProportionalMethod_getCriteriaWeightMapKeys(_relationPtr), keys, 0, criteriaCount);

            double[] values = new double[criteriaCount];
            Marshal.Copy(ProportionalMethod_getCriteriaWeightMapValues(_relationPtr), values, 0, criteriaCount);

            Dictionary<int, double> map = new Dictionary<int, double>();
            for (int i = 0; i < criteriaCount; i++) {
                map.Add(keys[i], values[i]);
            }
            return map;
        }
    }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr ProportionalMethod_new(int criteriaCount, IntPtr keys, IntPtr values);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr ProportionalMethod_getCriteriaWeightMapKeys(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr ProportionalMethod_getCriteriaWeightMapValues(IntPtr relationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int ProportionalMethod_getCriteriaCount(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool ProportionalMethod_isValid(IntPtr relationPtr);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr ProportionalMethod_copy(IntPtr relationPtr);
    
    public ProportionalMethod(int criteriaCount, Dictionary<int, double> criteriaIdWeightMap) 
    {
        int size = criteriaCount * sizeof(int);
        IntPtr keysPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(criteriaIdWeightMap.Keys.ToArray(), 0, keysPtr, criteriaCount);
        
        size = criteriaCount * sizeof(double);
        IntPtr valuesPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(criteriaIdWeightMap.Values.ToArray(), 0, valuesPtr, criteriaCount);
        
        _relationPtr = ProportionalMethod_new(criteriaCount, keysPtr, valuesPtr);
        
        Marshal.FreeHGlobal(keysPtr);
        Marshal.FreeHGlobal(valuesPtr);
    }

    internal ProportionalMethod(IntPtr relationPtr)
    {
        _relationPtr = relationPtr;
    }

    internal override IntPtr getPtr()
    {
        return _relationPtr;
    }

    public override bool IsValid()
    {
        return ProportionalMethod_isValid(_relationPtr);
    }

    public override ICriteriaRelation Copy()
    {
        return new ProportionalMethod(ProportionalMethod_copy(_relationPtr));
    }

    public override string ToString()
    {
        string res = "ProportionalMethod: CriteriaIdWeightMap={";
        var map = CriteriaIdWeightMap;
        foreach (var (key, value) in map)
        {
            res += "{" + key + ", " + value + "}, ";
        }
        return res + "}";
    }
}