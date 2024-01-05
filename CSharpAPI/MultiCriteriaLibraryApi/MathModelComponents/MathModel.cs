using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.MathModelComponents.Components;

namespace MultiCriteriaLibraryApi.MathModelComponents;

public class MathModel
{
    internal IntPtr _mathModelPtr { get; }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate bool DeletePredicate(double value, double[] secondAttributes, int secondAttributesCount);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool MathModel_isValid(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool MathModel_isNormalized(IntPtr obj);

    public MathModel(Criteria[] criteriaArray, EstimateVector[] estimateVectorArray)
    {
        IntPtr[] criteriaPtrs = criteriaArray.Select(criteria => ConvertToIntPtr(criteria)).ToArray();
        IntPtr[] estimateVectorPtrs = estimateVectorArray.Select(ev => ConvertToIntPtr(ev)).ToArray();
        _mathModelPtr = MathModel_new(ConvertToIntPtr(criteriaPtrs), criteriaArray.Length, 
            ConvertToIntPtr(estimateVectorPtrs), estimateVectorArray.Length);
    }

    public MathModel(MathModel other)
    {
        _mathModelPtr = MathModel_new_copy(other._mathModelPtr);
    }

    internal MathModel(IntPtr mathModelPtr) =>
        _mathModelPtr = mathModelPtr;

    ~MathModel()
    {
        MathModel_delete(_mathModelPtr);
    }

    public Criteria[] CriteriaArray
    {
        get
        {
            try
            {
                IntPtr criteriaArrayPtr = MathModel_getCriteriaArray(_mathModelPtr);
                int criteriaCount = MathModel_getCriteriaCount(_mathModelPtr);
                Criteria[] criteriaArray = new Criteria[criteriaCount];
                for (int i = 0; i < criteriaCount; i++)
                {
                    IntPtr criteriaPtr = Marshal.ReadIntPtr(criteriaArrayPtr, i * IntPtr.Size);
                    criteriaArray[i] = new Criteria(criteriaPtr);
                }
                return criteriaArray;
            }
            catch (AccessViolationException e)
            {
                Console.WriteLine(e);
                return Array.Empty<Criteria>();
            }
        }
    }

    public EstimateVector[] EstimateVectorArray 
    {
        get
        {
            IntPtr estimateVectorArrayPtr = MathModel_getEstimateVectorArray(_mathModelPtr);
            int estimateVectorCount = MathModel_getEstimateVectorCount(_mathModelPtr);
            try
            {
                EstimateVector[] estimateVectorArray = new EstimateVector[estimateVectorCount];
                for (int i = 0; i < estimateVectorCount; i++)
                {
                    IntPtr estimateVectorPtr = Marshal.ReadIntPtr(estimateVectorArrayPtr, i * IntPtr.Size);
                    estimateVectorArray[i] = new EstimateVector(estimateVectorPtr);
                }
                return estimateVectorArray;
            }
            catch (AccessViolationException e)
            {
                Console.WriteLine(e);
                return Array.Empty<EstimateVector>();
            }
        }
    }

    public Criteria GetCriteriaById(int id)
    {
        IntPtr criteriaPtr = MathModel_getCriteriaById(_mathModelPtr, id);
        return new Criteria(criteriaPtr);
    }

    public Criteria GetCriteriaByName(string name)
    {
        IntPtr criteriaPtr = MathModel_getCriteriaByName(_mathModelPtr, name);
        return new Criteria(criteriaPtr);
    }

    public int FindCriteriaNumById(int criteriaId)
    {
        return MathModel_findCriteriaNumById(_mathModelPtr, criteriaId);
    }

    public int FindCriteriaNumByName(string criteriaName)
    {
        return MathModel_findCriteriaNumByName(_mathModelPtr, criteriaName);
    }

    public double SumByCriteria(int criteriaId)
    {
        return MathModel_sumByCriteria(_mathModelPtr, criteriaId);
    }

    public double MaxByCriteria(int criteriaId)
    {
        return MathModel_maxByCriteria(_mathModelPtr, criteriaId);
    }

    public double MinByCriteria(int criteriaId)
    {
        return MathModel_minByCriteria(_mathModelPtr, criteriaId);
    }

    public void DeleteEstimateVectorByPredicate(int criteriaNum, Func<double, double[], bool> deletePredicate,
        double[] secondAttributes)
    {
        DeletePredicate del = (value, attributes, count) => deletePredicate(value, attributes);
        MathModel_deleteEstimateVectorByPredicate(_mathModelPtr, criteriaNum, del, secondAttributes,
            secondAttributes.Length);
    }

    public bool IsValid()
    {
        return MathModel_isValid(_mathModelPtr);
    }

    public bool IsNormalized()
    {
        return MathModel_isNormalized(_mathModelPtr);
    }

    public override string ToString()
    {
        string res = "";
        foreach (Criteria c in CriteriaArray)
        {
            res += c + "\n";
        }
        foreach (EstimateVector eV in EstimateVectorArray)
        {
            res += eV + "\n";
        }
        return res;
    }
    
    private static IntPtr ConvertToIntPtr(IntPtr[] pointers)
    {
        int size = pointers.Length * IntPtr.Size;
        IntPtr ptr = Marshal.AllocHGlobal(size);
        for (int i = 0; i < pointers.Length; i++)
            Marshal.WriteIntPtr(ptr, i * IntPtr.Size, pointers[i]);
        return ptr;
    }
    private static IntPtr ConvertToIntPtr(Criteria criteria)
    {
        return criteria._criteriaPtr;
    }
    private static IntPtr ConvertToIntPtr(EstimateVector estimateVector)
    {
        return estimateVector._estimateVectorPtr;
    }
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_new(IntPtr criteriaArray, int criteriaCount,
        IntPtr estimateVectorArray, int estimateVectorCount);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_new_copy(IntPtr other);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MathModel_delete(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_getCriteriaArray(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_getEstimateVectorArray(IntPtr obj);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MathModel_getCriteriaCount(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MathModel_getEstimateVectorCount(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_getCriteriaById(IntPtr obj, int id);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MathModel_getCriteriaByName(IntPtr obj, string name);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MathModel_findCriteriaNumById(IntPtr obj, int criteriaId);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int MathModel_findCriteriaNumByName(IntPtr obj, string name);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double MathModel_sumByCriteria(IntPtr obj, int criteriaId);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double MathModel_maxByCriteria(IntPtr obj, int criteriaId);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double MathModel_minByCriteria(IntPtr obj, int criteriaId);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MathModel_deleteEstimateVectorByPredicate(IntPtr obj, int criteriaNum,
        DeletePredicate deletePredicate, double[] secondAttributes, int secondAttributesCount);
}